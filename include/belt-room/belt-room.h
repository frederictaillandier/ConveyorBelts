#include "belt-room/ibelt-room.h"
#include "belt/ibelt.h"
#include "displayer/displayer.h"
#include "input-dispatcher/input-dispatcher.h"
#include <vector>

class BeltRoom : public IBeltRoom {
  std::vector<std::shared_ptr<IBelt>> _belts;
  std::unique_ptr<IInputDispatcher> _inputDispatcher =
      std::make_unique<InputDispatcher>();
  unsigned int _id_counter = 1;
  std::shared_ptr<IDisplayer> _displayer;

public:
  void BuildBeltRoom() override;
  void AddBelt(std::unique_ptr<IBelt> belt) override;
  void AddLuggage(std::unique_ptr<Luggage> luggage) override;
  std::weak_ptr<IBelt> GetBelt(unsigned int const index) const override;
  void EventLoop() override;
};