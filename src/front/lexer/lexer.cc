#include <cctype>
#include <fstream>
#include "./TokenStream.cc"

TokenStream *LexicalAnalysis(std::string input_filename) {
  TokenStream *tokens = new TokenStream();
  std::ifstream ifs;
  std::string cur_line;
  std::string token_str;
  int line_num = 0;
  bool iscomment = false;

  ifs.open(input_filename.c_str(), std::ios::in);
  if (!ifs) {
    return nullptr;
  }
  while(ifs && getline(ifs, cur_line)) {
    char next_char;
    Token *next_token;
    int index = 0;
    int length = cur_line.length();

    while (index < length) {
      next_char = cur_line[index++];

      // Ignore Comment
      if (iscomment) {
        if ((length - index) < 2
            || (cur_line[index] != '*')
            || (cur_line[index++] != '/')) {
          continue;
        } else {
          iscomment = false;
        }
      }

      // EOF
      if (next_char == EOF) {
        token_str = EOF;
        next_token = new Token(token_str, TOK_EOF, line_num);
      }

      // Ignore space
      else if (std::isspace(next_char)) {
        continue;
      }

      // IDENTIFIER
      else if (std::isalpha(next_char)) {
        token_str += next_char;
        next_char = cur_line[index++];
        while (std::isalnum(next_char)) {
          token_str += next_char;
          next_char = cur_line[index++];
          if (index == length) {
            break;
          }
        }
        index--;

        if (token_str == "int") {
          next_token = new Token(token_str, TOK_INT, line_num);
        } else if (token_str == "return") {
          next_token = new Token(token_str, TOK_RETURN, line_num);
        } else {
          next_token = new Token(token_str, TOK_IDENTIFIER, line_num);
        }
      }

      // Number
      else if (std::isdigit(next_char)) {
        if (next_char == '0') {
          token_str += next_char;
          next_token = new Token(token_str, TOK_DIGIT, line_num);
        } else {
          token_str += next_char;
          next_char = cur_line[index++];
          while (std::isdigit(next_char)) {
            token_str += next_char;
            next_char = cur_line[index++];
          }
          next_token = new Token(token_str, TOK_DIGIT, line_num);
          index--;
        }
      }

      // Comment or Division
      else if (next_char == '/') {
        token_str += next_char;
        next_char = cur_line[index++];

        // Single-Line Comment
        if (next_char == '/') {
          break;  // go to next line
        }

        // Multi-Line Comment
        else if (next_char == '*') {
          iscomment = true;
          continue;
        }

        // Division
        else {
          index--;
          next_token = new Token(token_str, TOK_SYMBOL, line_num);
        }
      }

      // Others
      else {
        if (next_char == '*' ||
            next_char == '+' ||
            next_char == '-' ||
            next_char == '=' ||
            next_char == ';' ||
            next_char == ',' ||
            next_char == '(' ||
            next_char == ')' ||
            next_char == '{' ||
            next_char == '}') {
          token_str += next_char;
          next_token = new Token(token_str, TOK_SYMBOL, line_num);
        }

        // Analysis Failure
        else {
          fprintf(stderr, "unclear Token: %c", next_char);
          SAFE_DELETE(tokens);
          return NULL;
        }
      }

      tokens->pushToken(next_token);
      token_str.clear();
    }

    token_str.clear();
    line_num++;
  }

  // Confirm EOF
  if (ifs.eof()) {
    tokens->pushToken(
      new Token(token_str, TOK_EOF, line_num)
    );
  }

  ifs.close();
  return tokens;
}

