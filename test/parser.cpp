#include <string>
#include <vector>
#include <ionir/const/const_name.h>
#include <ionir/construct/insts/inst.h>
#include <ionir/const/const.h>
#include <ionir/syntax/parser.h>
#include "test_api/bootstrap.h"
#include "pch.h"

using namespace ionir;

TEST(ParserTest, ParseInt) {
    Parser parser = test::bootstrap::parser({
        Token(TokenType::LiteralInt, "5"),
    });

    auto integer = parser.parseInt();

    EXPECT_EQ(integer->getValue(), 5);
}

TEST(ParserTest, ParseChar) {
    Parser parser = test::bootstrap::parser({
        Token(TokenType::LiteralCharacter, "a"),
    });

    auto character = parser.parseChar();

    EXPECT_EQ(character->getValue(), 'a');
}

TEST(ParserTest, ParseIdentifier) {
    Parser parser = test::bootstrap::parser({
        Token(TokenType::Identifier, "test"),
    });

    std::string identifier = parser.parseId();

    EXPECT_EQ(identifier, "test");
}

TEST(ParserTest, ParseType) {
    Parser parser = test::bootstrap::parser({
        Token(TokenType::Identifier, "type"),
    });

    auto type = parser.parseType();

    EXPECT_EQ(type->getId(), "type");
    EXPECT_FALSE(type->getIsPointer());
}

TEST(ParserTest, ParsePointerType) {
    Parser parser = test::bootstrap::parser({
        Token(TokenType::Identifier, "type"),
        Token(TokenType::SymbolStar, "*"),
    });

    auto type = parser.parseType();

    EXPECT_EQ(type->getId(), "type");
    EXPECT_TRUE(type->getIsPointer());
}

TEST(ParserTest, ParseArg) {
    Parser parser = test::bootstrap::parser({
        Token(TokenType::Identifier, "type"),
        Token(TokenType::Identifier, "test"),
    });

    Arg arg = parser.parseArg();

    EXPECT_EQ(arg.first->getId(), "type");
    EXPECT_FALSE(arg.first->getIsPointer());
    EXPECT_EQ(arg.second, "test");
}

TEST(ParserTest, ParseEmptyBlock) {
    Parser parser = test::bootstrap::parser({
        Token(TokenType::SymbolBraceL, "{"),
        Token(TokenType::SymbolBraceR, "}"),
    });

    auto block = parser.parseBlock(nullptr);

    EXPECT_EQ(block->getSections().size(), 0);
}

TEST(ParserTest, ParseEmptyPrototype) {
    Parser parser = test::bootstrap::parser({
        Token(TokenType::Identifier, Const::foobar),
        Token(TokenType::SymbolParenthesesL, "("),
        Token(TokenType::SymbolParenthesesR, ")"),
        Token(TokenType::SymbolArrow, "->"),
        Token(TokenType::Identifier, "type"),
    });

    auto prototype = parser.parsePrototype();
    auto returnType = prototype->getReturnType();
    auto args = prototype->getArgs();

    // Verify return type.
    EXPECT_EQ(returnType->getId(), "type");
    EXPECT_FALSE(returnType->getIsPointer());

    // Verify prototype.
    EXPECT_EQ(prototype->getId(), Const::foobar);

    // Verify prototype's arguments.
    EXPECT_EQ(args->getItems().size(), 0);
    EXPECT_FALSE(args->getIsInfinite());
}

TEST(ParserTest, ParseAllocaInst) {
    Parser parser = test::bootstrap::parser({
        Token(TokenType::Identifier, ConstName::instAlloca),
        Token(TokenType::Identifier, Const::foobar),
        Token(TokenType::Identifier, ConstName::typeInt32),
    });

    Ptr<Inst> inst = parser.parseInst(nullptr);

    EXPECT_EQ(inst->getInstKind(), InstKind::Alloca);
}

TEST(ParserTest, ParseExtern) {
    Parser parser = test::bootstrap::parser({
        Token(TokenType::KeywordExtern, "extern"),
        Token(TokenType::Identifier, Const::foobar),
        Token(TokenType::SymbolParenthesesL, "("),
        Token(TokenType::SymbolParenthesesR, ")"),
        Token(TokenType::SymbolArrow, "->"),
        Token(TokenType::Identifier, "type"),
    });

    auto externConstruct = parser.parseExtern();
    auto prototype = externConstruct->getPrototype();
    auto args = prototype->getArgs();

    // Verify prototype.
    EXPECT_EQ(prototype->getId(), Const::foobar);

    // Verify prototype's arguments.
    EXPECT_EQ(args->getItems().size(), 0);
    EXPECT_FALSE(args->getIsInfinite());
}
