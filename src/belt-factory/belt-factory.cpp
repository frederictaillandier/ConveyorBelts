#include "belt-factory/belt-factory.h"

std::unique_ptr<IBelt> BeltFactory::build() const {
    auto belt = std::make_unique<Belt>();
    belt->_beltSpeed = _speed;
    return belt;
}

IBeltFactory &BeltFactory::withSpeed(float speed) {
    _speed = speed;
    return *this;
}