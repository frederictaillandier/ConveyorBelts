#include <vector>
#include <memory>
#include "belt-room/belt-room.h"
#include "belt-factory/belt-factory.h"

void BeltRoom::BuildBeltRoom(unsigned int const number)
{
    auto beltFactory = std::make_unique<BeltFactory>();
    
    beltFactory->withSpeed(1);
    for (size_t i = 0; i < number -1; ++i)
        _belts.push_back(beltFactory->build());
    _belts.push_back(beltFactory->withSpeed(2).build());

    for (size_t i = 0; i < _belts.size(); ++i) {
        _belts[i]->SetNextBelt(_belts[(i + 1) % _belts.size()]);
        _belts[i]->SetPreviousBelt(_belts[(i - 1 + _belts.size()) % _belts.size()]);
    }
}

void BeltRoom::DropLuggage(std::unique_ptr<Luggage> luggage)
{
    _belts[0].get()->DropLuggageFront(std::move(luggage));
}

std::weak_ptr<IBelt> BeltRoom::GetBelt(unsigned int const index) 
{
    return _belts[index];
}