
#include "belt/belt.h"
#include "displayer/idisplayer.h"

class IBeltFactory {
public:
  /*
   * Builds a belt with the given parameters.
   */
  virtual std::unique_ptr<IBelt> Build() const = 0;

  /*
   * Sets the speed of the next belt to be built.
   */
  virtual IBeltFactory &WithSpeed(float speed) = 0;

  /*
   * Sets the displayer of the next belt to be built.
   */
  virtual IBeltFactory &
  WithDisplayer(std::shared_ptr<IDisplayer> displayer) = 0;
  virtual ~IBeltFactory() = default;
};