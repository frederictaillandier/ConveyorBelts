#include "belt/belt.h"

class IBeltFactory {
    public: 
        virtual std::unique_ptr<IBelt> build() const = 0;
        virtual IBeltFactory &withSpeed(float speed) = 0;
        virtual ~IBeltFactory() = default;
};