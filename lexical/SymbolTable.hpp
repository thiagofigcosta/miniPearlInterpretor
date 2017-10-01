#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <map>
#include <string>

#include "TokenType.hpp"

class SymbolTable {
public:
    SymbolTable();
    virtual ~SymbolTable();

    bool contains(std::string token);
    TokenType find(std::string token);

    std::map<std::string, TokenType> getSymbolMap();
private:
    std::map<std::string, TokenType> m_st;

};

#endif

