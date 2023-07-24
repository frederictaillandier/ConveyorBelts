#include <vector>
#include "belt/ibelt.h"
#include "input-dispatcher/input-dispatcher.h"

class BeltRoom {

    std::vector<std::shared_ptr<IBelt>> _belts;
    std::unique_ptr<IInputDispatcher> _inputDispatcher = std::make_unique<InputDispatcher>();

    public: 
        void BuildBeltRoom(unsigned int const number);
        void DropLuggage(std::unique_ptr<Luggage> luggage);
        std::weak_ptr<IBelt> GetBelt(unsigned int const index);
        void EventLoop();
};