#include <iostream>
#include <unistd.h>
#include "belt/belt.h"

Belt::Belt()
{
    thread = std::thread(&Belt::EventLoop, this);
}

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
}

void Belt::Update()
{
    _beltPosition += _beltSpeed;
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