#include <ionir/lexical/token_type.h>

namespace ionir {
    std::ostream &operator<<(std::ostream &stream, const ionir::TokenType &tokenType) {
        return stream << "TokenType(" << (int) tokenType << ")";
    }
}
