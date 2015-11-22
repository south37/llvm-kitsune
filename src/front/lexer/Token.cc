#include <string>
#include <cstdlib>

enum TokenType {
  TOK_IDENTIFIER,
  TOK_DIGIT,
  TOK_SYMBOL,
  TOK_INT,
  TOK_RETURN,
  TOK_EOF
};

class Token {
private:
  std::string TokenString;
  TokenType Type;
  int Line;
  int Number;
public:
  Token(std::string string, TokenType type, int line)
    : TokenString(string), Type(type), Line(line) {
    if (type == TOK_DIGIT) {
      Number = std::atoi(string.c_str());
    } else {
      Number = 0x7fffffff;
    }
  };
  TokenType getTokenType() { return Type; };
  std::string getTokenString() { return TokenString; };
  int getNumberValue() { return Number; };
  int getLine() { return Line; };
};

