#include "calculator.h"

int CalculateExpression(std::string_view input) {
  std::vector<Token> tokens = Tokenize(input); 
  size_t pos = 0;
  std::unique_ptr<IExpression> root = nullptr;
  if (!tokens.empty()) {
    root = ParseExpression(tokens, pos);
  }
  if (pos < tokens.size() || tokens.empty()) {
    throw WrongExpressionError{};
  }
  if (root != nullptr) {
    int result = 0;
    result = root->Calculate();
    return result;
  }
  return 0;
}