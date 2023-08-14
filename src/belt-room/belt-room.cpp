#include "belt-room/belt-room.h"
#include "belt-factory/belt-factory.h"
#include "input-dispatcher/input-dispatcher.h"
#include <memory>
#include <vector>

void BeltRoom::BuildBeltRoom() {
  for (size_t i = 0; i < _belts.size(); ++i) {
    _belts[i]->SetNextBelt(_belts[(i + 1) % _belts.size()]);
    _belts[i]->SetPreviousBelt(_belts[(i - 1 + _belts.size()) % _belts.size()]);
  }
  _inputDispatcher->SetOnKeyPressedCallback(
      IInputDispatcher::LUGGAGE_KEY, [this]() {
        auto luggage = std::make_unique<Luggage>();
        luggage->id = _id_counter++;
        AddLuggage(std::move(luggage));
      });
  for (unsigned char i = 0; i <= _belts.size(); ++i) {
    _inputDispatcher->SetOnKeyPressedCallback(
        IInputDispatcher::BELT_1_KEY + i,
        [this, i]() { _belts[i]->SwitchOnOff(); });
  }
  _inputDispatcher->SetOnKeyPressedCallback(IInputDispatcher::REVERSE_BELTS,
                                            [this]() {
                                              for (auto const &belt : _belts) {
                                                belt->Reverse();
                                              }
                                            });
}

void BeltRoom::AddBelt(std::unique_ptr<IBelt> belt) {
  _belts.emplace_back(std::move(belt));
}

void BeltRoom::AddLuggage(std::unique_ptr<Luggage> luggage) {
  _belts[0].get()->DropLuggageFront(std::move(luggage));
}

std::weak_ptr<IBelt> BeltRoom::GetBelt(unsigned int const index) const {
  return _belts[index];
}

void BeltRoom::EventLoop() { _inputDispatcher->EventLoop(); }
