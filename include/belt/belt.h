#pragma once
#include <thread>

#include "mutexed-variable/mutexed-variable.h"
#include "belt/ibelt.h"

class Belt : public IBelt
{
    private:
        std::thread thread;
        constexpr static float beltSize = 10;
        const float _beltSpeed = 1;

        MutexedVariable<float> _beltPosition = 0.0f;
        MutexedVariable<bool> _killCalled = false;
        MutexedVariable<bool> _paused = false;

        void EventLoop();
        void Update();

    public:
        Belt();
        void Resume() override;
        void Pause() override;
        ~Belt() override;
        float GetBeltPosition() const override;
};