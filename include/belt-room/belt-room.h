#include "belt/ibelt.h"
#include "displayer/displayer.h"
#include "input-dispatcher/input-dispatcher.h"
#include <vector>

class BeltRoom {

  std::vector<std::shared_ptr<IBelt>> _belts;
  std::unique_ptr<IInputDispatcher> _inputDispatcher =
      std::make_unique<InputDispatcher>();
  std::shared_ptr<IDisplayer> _displayer = std::make_shared<Displayer>();
  unsigned int _id_counter = 1;

public:
  void BuildBeltRoom(unsigned int const number);
  void DropLuggage(std::unique_ptr<Luggage> luggage);
  std::weak_ptr<IBelt> GetBelt(unsigned int const index);
  void EventLoop();
};