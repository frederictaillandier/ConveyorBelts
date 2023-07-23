
# pragma once

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
};
