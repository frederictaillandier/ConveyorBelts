#include <iostream>
#include "luggage/luggage.h"
#include "belt/ibelt.h" 
#include "displayer/displayer.h"

void Displayer::ClearScreen()
{
    std::cout << "\033[2J";
    std::cout << _displayCache.str();
    _displayCache.str("");
}

Displayer::~Displayer()
{
    _killCalled = true;
    _thread.join();
    std::cout << "Displayer destroyed" << std::endl;
}

void Displayer::GenerateDisplay()
{
    std::map<int, int> numberOnBelts;

    for (auto const &l : _luggages) {
        _displayCache << "L" << l.first << " " << std::get<0>(l.second) << " " << std::get<1>(l.second) << std::endl;
    }
}

void Displayer::EventLoop()
{
    while (!_killCalled)
    {
        ClearScreen();
        TreatEvents();
        GenerateDisplay();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void Displayer::TreatEvents() {
    std::lock_guard<std::mutex> lock(_event_queue_mutex);
    for (auto func : _event_queue) {
        func();
    }
    _event_queue.clear();
}

void Displayer::OnLuggageMove(unsigned int const id, unsigned const beltId, float const position)
{
    std::lock_guard<std::mutex> lock(_event_queue_mutex);
    _event_queue.push_back([this, id, beltId, position](){
        UpdateLuggagePosition(id, beltId, position);
    });
}

void Displayer::UpdateLuggagePosition(unsigned int const id, unsigned const beltId, float const position) {

    _luggages[id] = {beltId, position};
}


