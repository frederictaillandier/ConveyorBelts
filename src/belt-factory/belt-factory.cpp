#include "belt-factory/belt-factory.h"

std::unique_ptr<IBelt> BeltFactory::Build() const {
  auto belt = std::make_unique<Belt>();
  belt->_id = _id_counter++;
  belt->_beltSpeed = _speed;
  belt->_displayer = _displayer;
  return belt;
}

IBeltFactory &BeltFactory::WithSpeed(float speed) {
  _speed = speed;
  return *this;
}

IBeltFactory &
BeltFactory::WithDisplayer(std::shared_ptr<IDisplayer> displayer) {
  _displayer = displayer;
  return *this;
}