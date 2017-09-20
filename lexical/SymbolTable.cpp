#include "SymbolTable.hpp"

SymbolTable::SymbolTable() {
    m_st["="]=TOKEN_ASSIGN; 
    m_st[";"]=TOKEN_DOT_COMMA;
	m_st[","]=TOKEN_COMMA;
	m_st["{"]=TOKEN_OPENTHECUR;
	m_st["}"]=TOKEN_CLOSETHECUR;
	m_st["("]=TOKEN_OPENTHEPAR;
	m_st[")"]=TOKEN_CLOSETHEPAR;
	m_st["["]=TOKEN_OPENTHEBRA;
	m_st["]"]=TOKEN_CLOSETHEBRA;
	m_st["=>"]=TOKEN_BIND;
	
	m_st["print"]=TOKEN_PRINT;
	m_st["println"]=TOKEN_PRINTLN;
	m_st["push"]=TOKEN_PUSH;
	m_st["unshift"]=TOKEN_UNSHIFT;
	m_st["if"]=TOKEN_IF;
	m_st["else"]=TOKEN_ELSE;
	m_st["while"]=TOKEN_WHILE;
	m_st["do"]=TOKEN_DO;
	m_st["foreach"]=TOKEN_FOREACH;
	m_st["and"]=TOKEN_AND;
	m_st["or"]=TOKEN_OR;
	m_st["not"]=TOKEN_NOT;
	m_st["input"]=TOKEN_INPUT;
	m_st["size"]=TOKEN_SIZE;
	m_st["sort"]=TOKEN_SORT;
	m_st["reverse"]=TOKEN_REVERSE;
	m_st["keys"]=TOKEN_KEYS;
	m_st["values"]=TOKEN_VALUES;
	m_st["empty"]=TOKEN_EMPTY;
	m_st["pop"]=TOKEN_POP;
	m_st["shift"]=TOKEN_SHIFT;
	
	m_st["=="]=TOKEN_EQUAL;
	m_st["!="]=TOKEN_DIFF;
	m_st["<"]=TOKEN_LESS;
	m_st[">"]=TOKEN_GREATHER;
	m_st["<="]=TOKEN_LESS_EQUAL;
	m_st[">="]=TOKEN_GREATHER_EQUAL;
	m_st["."]=TOKEN_CONCAT;
	m_st["+"]=TOKEN_PLUS;
	m_st["-"]=TOKEN_MINUS;
	m_st["*"]=TOKEN_TIMES;
	m_st["/"]=TOKEN_DIV;
	m_st["%"]=TOKEN_MOD;
}

SymbolTable::~SymbolTable() {
}

bool SymbolTable::contains(std::string token) {
    return m_st.find(token) != m_st.end();
}

TokenType SymbolTable::find(std::string token) {
    return this->contains(token) ?
              m_st[token] : TOKEN_INVALID;
}

std::map<std::string, TokenType> SymbolTable::getSymbolMap(){
    return m_st;
}