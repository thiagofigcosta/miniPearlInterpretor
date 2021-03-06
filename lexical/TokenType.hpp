#ifndef TOKENTYPE_H
#define TOKENTYPE_H

enum TokenType {
    // special tokens
    TOKEN_INVALID=-2,
    TOKEN_UNEXPECTED_EOF=-1,
    TOKEN_END_OF_FILE=0,

    // symbols
    TOKEN_ASSIGN,//=
	TOKEN_DOT_COMMA,//=;
	TOKEN_COMMA,//,
	TOKEN_OPENTHECUR,//{
	TOKEN_CLOSETHECUR,//}
	TOKEN_OPENTHEPAR,//(
	TOKEN_CLOSETHEPAR,//)
	TOKEN_OPENTHEBRA,//[
	TOKEN_CLOSETHEBRA,//]
	TOKEN_BIND,//=>
	
    // keywords
    TOKEN_PRINT,
	TOKEN_PRINTLN,
	TOKEN_PUSH,
	TOKEN_UNSHIFT,
	TOKEN_IF,
	TOKEN_ELSE,
	TOKEN_WHILE,
	TOKEN_DO,
	TOKEN_FOREACH,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_NOT,
	TOKEN_INPUT,
	TOKEN_SIZE,
	TOKEN_SORT,
	TOKEN_REVERSE,
	TOKEN_KEYS,
	TOKEN_VALUES,
	TOKEN_EMPTY,
	TOKEN_POP,
	TOKEN_SHIFT,
	
    // operators
    TOKEN_EQUAL,//==
	TOKEN_DIFF,//!=
	TOKEN_LESS,//<
	TOKEN_GREATHER,//>
	TOKEN_LESS_EQUAL,//<=
	TOKEN_GREATHER_EQUAL,//>=
	TOKEN_CONCAT,//.
	TOKEN_PLUS,//+
	TOKEN_MINUS,//-
	TOKEN_TIMES,//*
	TOKEN_DIV,///
	TOKEN_MOD,//%

    // others
    TOKEN_NUMBER,//
	TOKEN_STRING,//""
	TOKEN_SVAR,//$
	TOKEN_LVAR,//@
	TOKEN_HVAR//%
};

#endif
