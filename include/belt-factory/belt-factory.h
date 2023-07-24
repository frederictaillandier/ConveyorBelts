#include "ibelt-factory.h"

class BeltFactory : public IBeltFactory {
    float _speed = 1;

    public:
        std::unique_ptr<IBelt> build() const override;
        IBeltFactory &withSpeed(float speed) override;
};