#pragma once

#include <optional>
#include <memory>
#include <vector>
#include <ionir/lexical/token_kind.h>

namespace ionir {
    template<typename T>
    using Ptr = std::shared_ptr<T>;

    template<typename T>
    using CPtr = Ptr<const T>;

    template<typename T>
    using OPtr = std::optional<Ptr<T>>;

    typedef std::vector<TokenKind> TokenKindVector;
}
