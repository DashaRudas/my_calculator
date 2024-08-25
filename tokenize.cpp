#include "tokenize.h"

bool PlusToken::operator==(const PlusToken&) const {
  return true;
}

bool MinusToken::operator==(const MinusToken&) const {
  return true;
}

bool MultiplyToken::operator==(const MultiplyToken&) const {
  return true;
}

bool DivideToken::operator==(const DivideToken&) const {
  return true;
}

bool ResidualToken::operator==(const ResidualToken&) const {
  return true;
}

bool OpeningBracketToken::operator==(const OpeningBracketToken&) const {
  return true;
}

bool ClosingBracketToken::operator==(const ClosingBracketToken&) const {
  return true;
}

bool SqrToken::operator==(const SqrToken&) const {
  return true;
}

bool MaxToken::operator==(const MaxToken&) const {
  return true;
}

bool MinToken::operator==(const MinToken&) const {
  return true;
}

bool AbsToken::operator==(const AbsToken&) const {
  return true;
}

bool NumberToken::operator==(const NumberToken& other) const {
  return value == other.value;
}

NumberToken::NumberToken(const int& number) {
  value = number;
}

UnknownToken::UnknownToken(const std::string& str) {
  value = str;
}

bool UnknownToken::operator==(const UnknownToken& other) const {
  return value == other.value;
}

void CheckWhich(std::string& i, Token& cur, std::vector<Token>& answer, bool& check) {
  if (i == "+") {
    cur = PlusToken();
    answer.push_back(cur);
    return;
  }
  if (i == "-") {
    cur = MinusToken();
    answer.push_back(cur);
    return;
  }
  if (i == "*") {
    cur = MultiplyToken();
    answer.push_back(cur);
    return;
  }
  if (i == "/") {
    cur = DivideToken();
    answer.push_back(cur);
    return;
  }
  if (i == "%") {
    cur = ResidualToken();
    answer.push_back(cur);
    return;
  }
  if (i == "(") {
    cur = OpeningBracketToken();
    answer.push_back(cur);
    return;
  }
  if (i == ")") {
    cur = ClosingBracketToken();
    answer.push_back(cur);
    return;
  }
  if (i == "sqr") {
    cur = SqrToken();
    answer.push_back(cur);
    return;
  }
  if (i == "max") {
    cur = MaxToken();
    answer.push_back(cur);
    return;
  }
  if (i == "min") {
    cur = MinToken();
    answer.push_back(cur);
    return;
  }
  if (i == "abs") {
    cur = AbsToken();
    answer.push_back(cur);
    return;
  }
  check = false;
}

std::vector<Token> Tokenize(std::string_view str) {
  std::vector<Token> answer;
  std::vector<std::string> sq;
  if (str.empty()) {
    return answer;
  }
  std::string tmp;
  for (size_t i = 0; i < str.size(); ++i) {
    if (str[i] != ' ') {
      tmp.push_back(str[i]);
    } else if (!tmp.empty()) {
      sq.push_back(tmp);
      tmp = "";
    }
  }
  if ((str[str.size() - 1] != ' ') && !tmp.empty()) {
    sq.push_back(tmp);
  }
  Token cur;
  bool number = true;
  for (size_t i = 0; i < sq.size(); ++i) {
    bool check = true;
    CheckWhich(sq[i], cur, answer, check);
    if (check) {
      continue;
    }
    number = true;
    for (size_t k = 0; k < sq[i].size(); ++k) {
      if (sq[i][k] < '0' || sq[i][k] > '9') {
        if (k != 0) {
          number = false;
        } else if (sq[i][k] != '-' && sq[i][k] != '+') {
          number = false;
        }
      }
    }
    if (number) {
      int current = 0;
      size_t j = 0;
      int sign = 1;
      if (sq[i][j] == '-' || sq[i][j] == '+') {
        if (sq[i][j] == '-') {
          sign = -1;
        }
        ++j;
      }
      for (; j < sq[i].size(); ++j) {
        current = 10 * current + static_cast<int>(sq[i][j] - '0');
      }
      current *= sign;
      cur = NumberToken(current);
      answer.push_back(cur);
    } else {
      cur = UnknownToken(sq[i]);
      answer.push_back(cur);
    }
  }
  return answer;
}