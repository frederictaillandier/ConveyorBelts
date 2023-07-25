#pragma once
#include <thread>
#include <vector>
#include <functional>
#include <map>
#include <sstream>
#include "displayer/idisplayer.h"

class Displayer : public IDisplayer {

    std::thread _thread = std::thread(&Displayer::EventLoop, this);
    std::atomic<bool> _killCalled = false;

    std::mutex _event_queue_mutex;
    std::vector<std::function<void()>> _event_queue;

    std::map<unsigned int, std::tuple<unsigned int, float>> _luggages;
    std::stringstream _displayCache;


    void UpdateLuggagePosition(unsigned int const id, unsigned int const beltId, float const position);
    void TreatEvents();
    void GenerateDisplay();
    void ClearScreen();
    public:
        ~Displayer();
        void EventLoop() override;
        void OnLuggageMove(unsigned int const id, unsigned int const beltId, float const position) override;
};