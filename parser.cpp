#include "parser.h"

std::unique_ptr<IExpression> ParseExpression(const std::vector<Token>& tokens, size_t& pos) {
  if (pos >= tokens.size()) {
    throw WrongExpressionError{};
  }
  auto operand = ParseAddendum(tokens, pos);
  while (pos < tokens.size()) {
    Token token = tokens[pos];
    ++pos;
    if (std::holds_alternative<UnknownToken>(token)) {
      throw UnknownSymbolError{};
    }
    bool flag = false;
    if (std::holds_alternative<PlusToken>(token)) {
      operand = std::make_unique<Sum>(std::move(operand), ParseAddendum(tokens, pos));
      flag = true;
    } else if (std::holds_alternative<MinusToken>(token)) {
      operand = std::make_unique<Subtract>(std::move(operand), ParseAddendum(tokens, pos));
      flag = true;
    } else if (std::holds_alternative<ClosingBracketToken>(token)) {
      --pos;
      return operand;
    }
    if (!flag) {
      throw WrongExpressionError{};
    }
  }
  if (pos == tokens.size()) {
    return operand;
  }
  throw WrongExpressionError{};
}

std::unique_ptr<IExpression> ParseAddendum(const std::vector<Token>& tokens, size_t& pos) {
  if (pos >= tokens.size() || std::holds_alternative<ClosingBracketToken>(tokens[pos])) {
    throw WrongExpressionError{};
  }
  auto operand = ParseMultiplier(tokens, pos);
  while (pos < tokens.size()) {
    Token token = tokens[pos];
    ++pos;
    if (std::holds_alternative<UnknownToken>(token)) {
      throw UnknownSymbolError{};
    }
    if (std::holds_alternative<PlusToken>(token)) {
      --pos;
      return operand;
    }
    if (std::holds_alternative<MinusToken>(token)) {
      --pos;
      return operand;
    }
    if (std::holds_alternative<ClosingBracketToken>(token)) {
      --pos;
      return operand;
    }
    if (std::holds_alternative<MultiplyToken>(token)) {
      operand = std::make_unique<Multiply>(std::move(operand), ParseMultiplier(tokens, pos));
    } else if (std::holds_alternative<DivideToken>(token)) {
      operand = std::make_unique<Divide>(std::move(operand), ParseMultiplier(tokens, pos));
    } else if (std::holds_alternative<ResidualToken>(token)) {
      operand = std::make_unique<Residual>(std::move(operand), ParseMultiplier(tokens, pos));
    } else {
      throw WrongExpressionError{};
    }
  }
  if (pos == tokens.size()) {
    return operand;
  }
  throw WrongExpressionError{};
}

std::unique_ptr<IExpression> ParseMultiplier(const std::vector<Token>& tokens, size_t& pos) {
  if (pos >= tokens.size()) {
    throw WrongExpressionError{};
  }
  Token token = tokens[pos];
  ++pos;
  if (std::holds_alternative<UnknownToken>(token)) {
    throw UnknownSymbolError{};
  }
  if (std::holds_alternative<NumberToken>(token)) {
    return std::make_unique<Constant>(std::get<NumberToken>(token).value);
  }
  if (std::holds_alternative<OpeningBracketToken>(token)) {
    auto operand = ParseExpression(tokens, pos);
    ++pos;
    return operand;
  }
  throw WrongExpressionError{};
}