#ifndef PARSER_H
#define PARSER_H

#include <stdexcept>
#include "../polish_notation/expressions.h"
#include <vector>
#include "../tokenize/tokenize.h"

class UnknownSymbolError : public std::runtime_error {
 public:
  explicit UnknownSymbolError(const std::string& symbol = "") : std::runtime_error("UnknownSymbolError: " + symbol) {
  }
};

class WrongExpressionError : public std::runtime_error {
 public:
  explicit WrongExpressionError(const std::string& msg = "") : std::runtime_error("WrongExpressionError: " + msg) {
  }
};

std::unique_ptr<IExpression> ParseExpression(const std::vector<Token>& tokens, size_t& pos);
std::unique_ptr<IExpression> ParseAddendum(const std::vector<Token>& tokens, size_t& pos);
std::unique_ptr<IExpression> ParseMultiplier(const std::vector<Token>& tokens, size_t& pos);

#endif