#include <vector>
#include "belt/ibelt.h"

class BeltRoom {

    std::vector<std::shared_ptr<IBelt>> _belts;

    public: 
        void BuildBeltRoom(unsigned int const number);
        void DropLuggage(std::unique_ptr<Luggage> luggage);
        std::weak_ptr<IBelt> GetBelt(unsigned int const index);
};