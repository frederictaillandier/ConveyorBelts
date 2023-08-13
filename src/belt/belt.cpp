#include "belt/belt.h"
#include <algorithm>
#include <iostream>
#include <mutex>
#include <unistd.h>

void Belt::EventLoop() {
  while (!_killCalled) {
    if (!_paused)
      Update();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

Belt::~Belt() noexcept {
  _killCalled = true;
  thread.join();
  std::cout << "Belt destroyed" << std::endl;
}

unsigned int Belt::GetId() const { return _id; }

void Belt::ProcessFallingLuggages() {
  std::scoped_lock lock(_fallingLuggagesMutex);
  _luggages.insert(_luggages.end(),
                   std::make_move_iterator(_fallingLuggages.begin()),
                   std::make_move_iterator(_fallingLuggages.end()));
  _fallingLuggages.clear();
}

void Belt::ProcessLuggagesOnBelt() {

  auto end_iterator = std::ranges::remove_if(_luggages, [this](auto &luggage) {
    luggage->position += _beltSpeed * 0.1f;
    if (luggage->position > BELT_SIZE && _nextBelt.lock()) {
      luggage->position = 0;
      _nextBelt.lock()->DropLuggageFront(std::move(luggage));
      return true;
    } else if (luggage->position < -0.01f && _previousBelt.lock()) {
      luggage->position = BELT_SIZE;
      _previousBelt.lock()->DropLuggageBack(std::move(luggage));
      return true;
    } else if (_displayer) {
      _displayer->OnLuggageMove(luggage->id, _id, luggage->position);
    }
    return false;
  });
  _luggages.erase(end_iterator.begin(), _luggages.end());
  _luggagesCount = _luggages.size();
}

void Belt::Update() {
  ProcessFallingLuggages();
  ProcessLuggagesOnBelt();
}

void Belt::Resume() { _paused = false; }

void Belt::Pause() { _paused = true; }

void Belt::Reverse() { _beltSpeed = -_beltSpeed; }

void Belt::SwitchOnOff() { _paused = !_paused; }

void Belt::SetNextBelt(std::weak_ptr<IBelt> nextBelt) { _nextBelt = nextBelt; }

void Belt::SetPreviousBelt(std::weak_ptr<IBelt> previousBelt) {
  _previousBelt = previousBelt;
}

void Belt::DropLuggageFront(std::unique_ptr<Luggage> luggage) {
  std::scoped_lock lock(_fallingLuggagesMutex);
  _fallingLuggages.emplace_back(std::move(luggage));
}

void Belt::DropLuggageBack(std::unique_ptr<Luggage> luggage) {
  std::scoped_lock lock(_fallingLuggagesMutex);
  _fallingLuggages.emplace_back(std::move(luggage));
}

size_t Belt::GetLuggageNumber() const { return _luggagesCount; }