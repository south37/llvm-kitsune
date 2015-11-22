#include <vector>
#include <iostream>
#include "./Token.cc"
#include "../APP.h"

class TokenStream {
private:
  std::vector<Token*> Tokens;
  int CurIndex;

public:
  TokenStream() : CurIndex(0) {};
  ~TokenStream();

  bool ungetToken(int TImes = 1);
  bool getNextToken();
  bool pushToken(Token *token) {
    Tokens.push_back(token);
    return true;
  }
  Token getToken();

  TokenType getCurType() {
    return Tokens[CurIndex]->getTokenType();
  }

  std::string getCurString() {
    return Tokens[CurIndex]->getTokenString();
  }

  int getCurNumVal() {
    return Tokens[CurIndex]->getNumberValue();
  }

  int getCurIndex() {
    return CurIndex;
  }

  bool applyTokenIndex(int index) {
    CurIndex = index;
    return true;
  }

  bool printTokens();
};

/**
 * Destructor
 */
TokenStream::~TokenStream() {
  for (int i = 0; i < Tokens.size(); i++) {
    SAFE_DELETE(Tokens[i]);
  }
  Tokens.clear();
}

/**
 * Get Token
 * @return Token at CurIndex.
 */
Token TokenStream::getToken() {
  return *Tokens[CurIndex];
}

/**
 * Increment CurIndex
 * @return success: true, failure: false
 */
bool TokenStream::getNextToken() {
  int size = Tokens.size();
  if (CurIndex >= size - 1) {
    return false;
  } else {
    CurIndex++;
    return true;
  }
}

/**
 * Revert CurIndex by times
 */
bool TokenStream::ungetToken(int times) {
  if (CurIndex >= times) {
    CurIndex -= times;
    return true;
  } else {
    CurIndex = 0;
    return false;
  }
}

/**
 * Display Tokens
 */
bool TokenStream::printTokens() {
  std::vector<Token*>::iterator iter = Tokens.begin();
  while (iter != Tokens.end()) {
    std::cout << (*iter)->getTokenType() << ":";
    if((*iter)->getTokenType() != TOK_EOF) {
      std::cout << " " << (*iter)->getTokenString().c_str() << std::endl;
    }
    ++iter;
  }
  return true;
}
