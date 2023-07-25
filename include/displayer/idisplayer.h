#pragma once

class IDisplayer {      
    public: 
        virtual ~IDisplayer() = default;
        virtual void EventLoop() = 0;
        virtual void OnLuggageMove(unsigned int const id, unsigned int const beltId, float position) = 0;
};