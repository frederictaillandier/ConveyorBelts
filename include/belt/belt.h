#pragma once
#include <thread>
#include <atomic>
#include <vector>
#include "belt/ibelt.h"

class Belt : public IBelt
{
    private:
        std::thread thread = std::thread(&Belt::EventLoop, this);
        constexpr static float beltSize = 10;
        float _beltSpeed = 1;

        std::atomic<float> _beltPosition = 0.0f;
        std::atomic<bool> _killCalled = false;
        std::atomic<bool> _paused = false;

        std::weak_ptr<IBelt> _nextBelt;
        std::weak_ptr<IBelt> _previousBelt;

        void EventLoop();
        void Update();

        std::vector<std::unique_ptr<Luggage>> _luggages;
    public:
        void Resume() override;
        void Pause() override;
        void SwitchOnOff() override;
        ~Belt() override;
        float GetBeltPosition() const override;
        void SetNextBelt(std::weak_ptr<IBelt> nextBelt) override;
        void SetPreviousBelt(std::weak_ptr<IBelt> previousBelt) override;
        void DropLuggageFront(std::unique_ptr<Luggage> luggage) override;
        void DropLuggageBack(std::unique_ptr<Luggage> luggage) override;
        size_t GetLuggageNumber() const override;
    friend class BeltFactory;
};