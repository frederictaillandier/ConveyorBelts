#include "belt/ibelt.h"
#include "luggage/luggage.h"
#include <memory>

class IBeltRoom {
public:
  /*
   * Builds connects the previously given belts together.
   */
  virtual void BuildBeltRoom() = 0;

  /*
   * Adds a belt to the belt room.
   */
  virtual void AddBelt(std::unique_ptr<IBelt> belt) = 0;

  /*
   * Adds a luggage to the first belt.
   */
  virtual void AddLuggage(std::unique_ptr<Luggage> luggage) = 0;

  /*
   * Returns a weak pointer to the belt at the given index.
   */
  virtual std::weak_ptr<IBelt> GetBelt(unsigned int const index) const = 0;

  /*
   * Starts the event loop.
   */
  virtual void EventLoop() = 0;
  virtual ~IBeltRoom() = default;
};