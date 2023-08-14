#include "displayer/idisplayer.h"
#include "ibelt-factory.h"
#include <memory>

class BeltFactory : public IBeltFactory {
  float _speed = 1;
  mutable unsigned int _id_counter =
      0; // mutable as we need to increment it in a const method
  std::shared_ptr<IDisplayer> _displayer;

public:
  std::unique_ptr<IBelt> Build() const override;
  IBeltFactory &WithSpeed(float speed) override;
  IBeltFactory &WithDisplayer(std::shared_ptr<IDisplayer> displayer) override;
};