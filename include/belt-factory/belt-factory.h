#include <memory>
#include "ibelt-factory.h"
#include "displayer/idisplayer.h"

class BeltFactory : public IBeltFactory {
    float _speed = 1;
    mutable unsigned int _id_counter = 0; //mutable as we need to increment it in a const method
    std::shared_ptr<IDisplayer> _displayer;

    public:
        std::unique_ptr<IBelt> build() const override;
        IBeltFactory &withSpeed(float speed) override;
        IBeltFactory &withDisplayer(std::shared_ptr<IDisplayer> displayer) override; 
};