
#include "belt/belt.h"
#include "displayer/idisplayer.h"

class IBeltFactory {
public:
  virtual std::unique_ptr<IBelt> build() const = 0;
  virtual IBeltFactory &withSpeed(float speed) = 0;
  virtual IBeltFactory &
  withDisplayer(std::shared_ptr<IDisplayer> displayer) = 0;
  virtual ~IBeltFactory() = default;
};