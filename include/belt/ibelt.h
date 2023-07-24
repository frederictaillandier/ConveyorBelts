
# pragma once
#include <memory>
#include "luggage/luggage.h"

/*
 @brief Belt class interface
 */
class IBelt
{
    public:      
        virtual ~IBelt() = default;
        /*
        @brief resumes belt's movement
        */
        virtual void Resume() = 0;
        /*
        @brief pauses belt's movement
        */
        virtual void Pause() = 0;
        /*
        @brief returns belt's at a given moment
        */
        virtual float GetBeltPosition() const = 0;
        /*
        @brief sets the next belt in the chain
        */
        virtual void SetNextBelt(std::weak_ptr<IBelt> nextBelt) = 0;
        /*
        @brief sets the previous belt in the chain
        */
        virtual void SetPreviousBelt(std::weak_ptr<IBelt> previousBelt) = 0;
        /*
        @brief drop luggage on the belt
        */
        virtual void DropLuggageFront(std::unique_ptr<Luggage> luggage) = 0;
        /*
        @brief luggage on the belt
        */
        virtual void DropLuggageBack(std::unique_ptr<Luggage> luggage) = 0;
        /*
        @brief returns the number of luggages on the belt
        */
        virtual size_t GetLuggageNumber() const = 0;
};
