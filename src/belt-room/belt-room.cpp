#include "belt-room/belt-room.h"
#include "belt-factory/belt-factory.h"
#include "input-dispatcher/input-dispatcher.h"
#include <memory>
#include <vector>

void BeltRoom::BuildBeltRoom(unsigned int const number) {

  auto beltFactory = std::make_unique<BeltFactory>(); // GCOVR_EXCL_LINE

  std::shared_ptr<IDisplayer> displayer = _displayer;

  beltFactory->withDisplayer(displayer);
  beltFactory->withSpeed(1);
  for (size_t i = 0; i < number - 1; ++i)
    _belts.emplace_back(beltFactory->build());
  _belts.emplace_back(beltFactory->withSpeed(2).build());

  for (size_t i = 0; i < _belts.size(); ++i) {
    _belts[i]->SetNextBelt(_belts[(i + 1) % _belts.size()]);
    _belts[i]->SetPreviousBelt(_belts[(i - 1 + _belts.size()) % _belts.size()]);
  }
}

void BeltRoom::DropLuggage(std::unique_ptr<Luggage> luggage) {
  _belts[0].get()->DropLuggageFront(std::move(luggage));
}

std::weak_ptr<IBelt> BeltRoom::GetBelt(unsigned int const index) {
  return _belts[index];
}

void BeltRoom::EventLoop() {
  _inputDispatcher->SetOnKeyPressedCallback(
      IInputDispatcher::LUGGAGE_KEY, [this]() {
        auto luggage = std::make_unique<Luggage>();
        luggage->id = _id_counter++;
        DropLuggage(std::move(luggage));
      });
  for (unsigned char i = 0; i <= BELT_NUMBER; ++i) {
    _inputDispatcher->SetOnKeyPressedCallback(
        IInputDispatcher::BELT_1_KEY + i,
        [this, i]() { _belts[i]->SwitchOnOff(); });
  }

  _inputDispatcher->EventLoop();
}