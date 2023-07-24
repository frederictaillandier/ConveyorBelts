#pragma once
#include <thread>
#include <atomic>
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

        void EventLoop();
        void Update();

    public:
        void Resume() override;
        void Pause() override;
        ~Belt() override;
        float GetBeltPosition() const override;
    friend class BeltFactory;
};