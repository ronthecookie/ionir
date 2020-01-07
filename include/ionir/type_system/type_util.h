#pragma once

#include <exception>
#include <ionir/construct/type.h>

namespace ionir {
    class TypeUtil {
    public:
        static bool isAtomicTypesCompatible(TypeKind typeKindA, TypeKind typeKindB);
    };
}