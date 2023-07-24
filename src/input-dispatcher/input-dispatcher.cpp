#include "input-dispatcher/input-dispatcher.h"
#include "utils/my-getch.h"

void InputDispatcher::SetOnKeyPressedCallback(char c, std::function<void()> const &callback)
{
    _callbacks[c] = callback;
}

void InputDispatcher::EventLoop()
{
    while (true)
    {
        char keyPressed = my_getch();
        if (keyPressed == 'q')
            return;
        if (_callbacks.find(keyPressed) != _callbacks.end()) {
                    _callbacks[keyPressed]();
        }       
    } 
}