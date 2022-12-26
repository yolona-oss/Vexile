#pragma once

#include "Vexile/Core/System/NonCopyable.hpp"
#include <cstdarg>

namespace Vexile {

template<typename T>
class ScopedInstance : NonCopyable {
protected:
        ScopedInstance(T i): _instance(i) { }
        T _instance;

public:
        virtual ~ScopedInstance() {}
        virtual T getInstance() {
                return _instance;
        }
};

}
