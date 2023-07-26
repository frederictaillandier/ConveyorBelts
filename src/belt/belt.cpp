#include <iostream>
#include <mutex>
#include <unistd.h>
#include "belt/belt.h"

void Belt::EventLoop()
{
    while (!_killCalled)
    {
        if (!_paused)
            Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

Belt::~Belt()
{
    _killCalled = true;
    thread.join();
    std::cout << "Belt destroyed" << std::endl;
}

unsigned int Belt::GetId() const
{
    return _id;
}

void Belt::ProcessFallingLuggages()
{
    std::scoped_lock lock(_fallingLuggagesMutex);
    _luggages.insert(_luggages.end(), 
        std::make_move_iterator(_fallingLuggages.begin()), 
        std::make_move_iterator(_fallingLuggages.end())
    );
    _fallingLuggages.clear();
}

void Belt::Update()
{
    ProcessFallingLuggages();
    for (unsigned int i = 0; i < _luggages.size(); ++i)
    {
        _luggages[i]->position += _beltSpeed * 0.1f;
        if (_luggages[i]->position > beltSize)
        {
            auto l = std::move(_luggages[i]);
            l->position = 0;
            _luggages.erase(_luggages.begin() + i);
            if (_nextBelt.lock()) {
                _nextBelt.lock()->DropLuggageFront(std::move(l));
            }            
        }
        else if (_luggages[i]->position < 0)
        {
            auto l = std::move(_luggages[i]);
            l->position = beltSize;
            _luggages.erase(_luggages.begin() + i);
            if (_previousBelt.lock()) {
                _previousBelt.lock()->DropLuggageBack(std::move(l));
            }
        }
        else {
            if (_displayer)
                _displayer->OnLuggageMove(_luggages[i]->id, _id, _luggages[i]->position);
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

void Belt::Reverse()
{
    _beltSpeed = -_beltSpeed;
}

void Belt::SwitchOnOff()
{
    _paused = !_paused;
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
    std::scoped_lock lock(_fallingLuggagesMutex);
    _fallingLuggages.emplace_back(std::move(luggage));
}

void Belt::DropLuggageBack(std::unique_ptr<Luggage> luggage)
{
    std::scoped_lock lock(_fallingLuggagesMutex);
    _fallingLuggages.emplace_back(std::move(luggage));
}

size_t Belt::GetLuggageNumber() const
{
    return _luggages.size();
}