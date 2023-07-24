#include <iostream>
#include <unistd.h>
#include "belt/belt.h"

void Belt::EventLoop()
{
    while (!_killCalled)
    {
        if (!_paused)
            Update();
        sleep(1);
    }
}

Belt::~Belt()
{
    _killCalled = true;
    thread.join();
    std::cout << "Belt destroyed" << std::endl;
}

void Belt::Update()
{
    _beltPosition = _beltPosition + _beltSpeed;
    for (unsigned int i = 0; i < _luggages.size(); ++i)
    {
        _luggages[i]->position += _beltSpeed;
        if (_luggages[i]->position >= beltSize)
        {
            auto l = std::move(_luggages[i]);
            _luggages.erase(_luggages.begin() + i);
            if (_nextBelt.lock())
                _nextBelt.lock()->DropLuggageFront(std::move(l));
        }
    }

}

void Belt::Resume()
{
    _paused = false;
}

void Belt::Pause()
{
    _paused = true;
}

float Belt::GetBeltPosition() const
{
    return _beltPosition;
}

void Belt::SetNextBelt(std::weak_ptr<IBelt> nextBelt)
{
    _nextBelt = nextBelt;
}

void Belt::SetPreviousBelt(std::weak_ptr<IBelt> previousBelt)
{
    _previousBelt = previousBelt;
}

void Belt::DropLuggageFront(std::unique_ptr<Luggage> luggage)
{
    luggage->position = 0;
    _luggages.insert(_luggages.begin(), std::move(luggage));
    std::cout << "Drop Front" << std::endl;
}

void Belt::DropLuggageBack(std::unique_ptr<Luggage> luggage)
{
    luggage->position = 10;
    _luggages.push_back(std::move(luggage));
    std::cout << "Drop Back" << std::endl;
}

size_t Belt::GetLuggageNumber() const
{
    return _luggages.size();
}