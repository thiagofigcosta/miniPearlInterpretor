#ifndef LEXICAL_ANALYSIS_H
#define LEXICAL_ANALYSIS_H

#include <cstdio>
#include <string>
#include "StateType.hpp"
#include "TokenType.hpp"
#include "SymbolTable.hpp"

struct Lexeme {
   std::string token;
   enum TokenType type;
};

class LexicalAnalysis {
public:
    LexicalAnalysis(const char* filename);
    virtual ~LexicalAnalysis();

    int line() const;

    Lexeme nextToken();
    void printTokens();
    std::map<std::string, TokenType> getSymbolMap();
private:
    int fline;
    char* filename;
    FILE* file;
    SymbolTable symbols;

};

#endif
