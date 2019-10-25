#pragma once

#include "syntax/stream.hpp"

namespace ionir::testing
{
Token bootstrapToken(int id)
{
    Token token = Token(TokenType::Unknown, std::string("test_" + std::to_string(id)), id);

    return token;
}

TokenStream bootstrapTokenStream(int amountOfItems = 1)
{
    std::vector<Token> tokens = {};

    // Populate the tokens vector.
    for (int i = 0; i < amountOfItems; i++)
    {
        tokens.push_back(bootstrapToken(i));
    }

    // Create the Stream and provide the tokens.
    TokenStream stream = TokenStream(tokens);

    return stream;
}
} // namespace ionir::testing
