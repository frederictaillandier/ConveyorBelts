#pragma once
#include <thread>
#include <atomic>
#include <vector>
#include "belt/ibelt.h"
#include "displayer/idisplayer.h"

class Belt : public IBelt
{
    private:
        unsigned int _id;
        
        std::thread thread = std::thread(&Belt::EventLoop, this);
        constexpr static float beltSize = 10;
        float _beltSpeed = 1;

        std::atomic<bool> _killCalled = false;
        std::atomic<bool> _paused = false;

        std::weak_ptr<IBelt> _nextBelt;
        std::weak_ptr<IBelt> _previousBelt;
        std::shared_ptr<IDisplayer> _displayer;
        
        std::vector<std::unique_ptr<Luggage>> _luggages;
        std::vector<std::unique_ptr<Luggage>> _fallingLuggages;
        std::mutex _fallingLuggagesMutex;

        void EventLoop();
        void Update();
        void ProcessFallingLuggages();

    public:
        unsigned int GetId() const override;
        void Resume() override;
        void Pause() override;
        void Reverse() override;
        void SwitchOnOff() override;
        ~Belt() override;
        void SetNextBelt(std::weak_ptr<IBelt> nextBelt) override;
        void SetPreviousBelt(std::weak_ptr<IBelt> previousBelt) override;
        void DropLuggageFront(std::unique_ptr<Luggage> luggage) override;
        void DropLuggageBack(std::unique_ptr<Luggage> luggage) override;
        size_t GetLuggageNumber() const override;
    friend class BeltFactory;
};