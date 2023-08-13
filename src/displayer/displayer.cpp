#include "displayer/displayer.h"
#include "belt/ibelt.h"
#include "luggage/luggage.h"
#include <iostream>
#include <mutex>

void Displayer::ClearScreen() {
#ifndef NODISPLAYER
  std::cout << "\033[2J";
  std::cout << _displayCache.str();
  _displayCache.str("");
#endif
}

Displayer::~Displayer() {
  _killCalled = true;
  _thread.join();
  std::cout << "Displayer destroyed" << std::endl;
}

void Displayer::GenerateDisplay() {
  std::stringstream display_luggages;
  std::stringstream display_belts;

  if (_luggages.empty()) {
    _displayCache << "No luggages" << std::endl;
    return;
  }
  std::map<int, int> luggages_on_belts;

  for (auto const &[luggage_id, luggage] : _luggages) {
    auto const &[beltId, position] = luggage;

    if (luggages_on_belts.contains(beltId) == false) {
      luggages_on_belts[beltId] = 0;
    }
    luggages_on_belts[beltId]++;

    display_luggages << "L" << luggage_id << " " << beltId << " " << position
                     << std::endl;
  }
  for (auto const &[beltId, luggage_count] : luggages_on_belts) {
    display_belts << "B" << beltId << " " << luggage_count << " ";
  }
  _displayCache << display_belts.str() << std::endl;
  _displayCache << display_luggages.str() << std::endl;
}

void Displayer::EventLoop() {
  while (!_killCalled) {
    ClearScreen();
    TreatEvents();
    GenerateDisplay();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

void Displayer::TreatEvents() {
  std::scoped_lock lock(_event_queue_mutex);
  for (auto const &func : _event_queue) {
    func();
  }
  _event_queue.clear();
}

void Displayer::OnLuggageMove(unsigned int const id, unsigned const beltId,
                              float const position) {
  std::scoped_lock lock(_event_queue_mutex);
  _event_queue.emplace_back([this, id, beltId, position]() {
    UpdateLuggagePosition(id, beltId, position);
  });
}

void Displayer::UpdateLuggagePosition(unsigned int const id,
                                      unsigned const beltId,
                                      float const position) {
  _luggages[id] = {beltId, position};
}