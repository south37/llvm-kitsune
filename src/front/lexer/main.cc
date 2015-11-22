#include "./lexer.cc"

int main(int argc, char** argv) {
  if (argc == 2) {
    TokenStream *tokens = LexicalAnalysis(argv[1]);
    tokens->printTokens();
  } else {
    std::cout << "Number of args must be 1: it must be an input filename" << std::endl;
  }
}
