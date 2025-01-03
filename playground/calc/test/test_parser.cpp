#include <memory>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "node.hpp"
#include "parser.hpp"

class ParserTest : public ::testing::Test {
protected:
    std::unique_ptr<Calc::Parser> parser_;

    virtual void SetUp() { parser_ = std::make_unique<Calc::Parser>(); }

    virtual void TearDown() {}

    template <class... T>
    std::vector<std::string> createTokens(T... tokens) {
        return std::vector<std::string>{tokens...};
    }
};

TEST_F(ParserTest, EvaluateOne) {
    auto tokens = createTokens("1");
    auto expr = parser_->parse(tokens);

    EXPECT_EQ(1, expr->eval());
}

TEST_F(ParserTest, EvaluateOnePlusTwo) {
    auto tokens = createTokens("1", "+", "2");
    auto expr = parser_->parse(tokens);

    EXPECT_EQ(3, expr->eval());
}

TEST_F(ParserTest, EvaluateOneMinusTwo) {
    auto tokens = createTokens("1", "-", "2");
    auto expr = parser_->parse(tokens);

    EXPECT_EQ(-1, expr->eval());
}

TEST_F(ParserTest, EvaluateOneTimesTwo) {
    auto tokens = createTokens("1", "*", "2");
    auto expr = parser_->parse(tokens);

    EXPECT_EQ(2, expr->eval());
}

TEST_F(ParserTest, EvaluateOneDividedByTwo) {
    auto tokens = createTokens("1", "/", "2");
    auto expr = parser_->parse(tokens);

    EXPECT_EQ(0.5, expr->eval());
}

TEST_F(ParserTest, EvaluateOnePlusTwoMinusThree) {
    auto tokens = createTokens("1", "+", "2", "-", "3");
    auto expr = parser_->parse(tokens);

    EXPECT_EQ(0, expr->eval());
}

TEST_F(ParserTest, EvaluateOnePlusTwoTimesThree) {
    auto tokens = createTokens("1", "+", "2", "*", "3");
    auto expr = parser_->parse(tokens);

    EXPECT_EQ(7, expr->eval());
}

TEST_F(ParserTest, EvaluateOnePlusTwoDivideByThree) {
    auto tokens = createTokens("1", "+", "2", "/", "3");
    auto expr = parser_->parse(tokens);

    EXPECT_DOUBLE_EQ(1.666666666666666, expr->eval());
}

TEST_F(ParserTest, EvaluateOneTimesTwoPlusThree) {
    auto tokens = createTokens("1", "*", "2", "+", "3");
    auto expr = parser_->parse(tokens);

    EXPECT_DOUBLE_EQ(5, expr->eval());
}

TEST_F(ParserTest, EvaluateOnePlusTwoTimesThreeTimesFour) {
    auto tokens = createTokens("1", "+", "2", "*", "3", "*", "4");
    auto expr = parser_->parse(tokens);

    EXPECT_EQ(25, expr->eval());
}

TEST_F(ParserTest, EvaluateOnePlusTwoTimesThreePlusFour) {
    auto tokens = createTokens("1", "+", "2", "*", "3", "+", "4");
    auto expr = parser_->parse(tokens);

    EXPECT_EQ(11, expr->eval());
}

TEST_F(ParserTest, EvaluateOneDividedByTwoPlusThreeTimesFour) {
    auto tokens = createTokens("1", "/", "2", "+", "3", "*", "4");
    auto expr = parser_->parse(tokens);

    EXPECT_EQ(12.5, expr->eval());
}
