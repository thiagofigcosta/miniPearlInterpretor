#include <cstdlib>
#include <string>
#include "SyntacticalAnalysis.hpp"

#include "../interpreter/expr/Expr.hpp"
#include "../interpreter/expr/ConstExpr.hpp"
#include "../interpreter/value/IntegerValue.hpp"
#include "../interpreter/value/StringValue.hpp"
#include "../interpreter/command/Command.hpp"
#include "../interpreter/command/CommandsBlock.hpp"
#include "../interpreter/command/ActionCommand.hpp"
#include "../interpreter/command/PrintCommand.hpp"

SyntacticalAnalysis::SyntacticalAnalysis(LexicalAnalysis& lex):lex(lex), current(lex.nextToken()) {
}

SyntacticalAnalysis::~SyntacticalAnalysis() {
}
void SyntacticalAnalysis::start(){
	procStatements(); 
    matchToken(TOKEN_END_OF_FILE);
}
void SyntacticalAnalysis::matchToken(TokenType token){
    if (token == current.type) {
        current = lex.nextToken();
    } else {
        showError(token);
    }
}
bool SyntacticalAnalysis::testToken(TokenType token){
    return token==current.type;
}
void SyntacticalAnalysis::consumeToken(){
    current = lex.nextToken();
}


void SyntacticalAnalysis::showError() {
    showError("");
}
void SyntacticalAnalysis::showError(TokenType token) {
    std::string err;
    err="Unkown token";
    for(auto &i:lex.getSymbolMap()){
        if(i.second==token){
            err=i.first;
            break;
        }
    }
    showError(err);
}
void SyntacticalAnalysis::showError(std::string err) {
    showError(err,current.type,lex.line());
}

void SyntacticalAnalysis::showError(std::string err, TokenType t,int line) {
    switch (t) {
        case TOKEN_INVALID:
            printf("Lexical Error - Invalid Token at:%d\n",line);
            break;
        case TOKEN_UNEXPECTED_EOF:
            printf("Lexical Error - Unexpected EOF at:%d\n",line);
            break;
        case TOKEN_END_OF_FILE:
            printf("Syntactical Error - EOF at:%d\n",line);
            break;
        default:
            if(err=="") err="Something";
            printf("Syntactical Error - Expected %s at:%d\n",err.c_str(),line);
            break;
    }
    exit(1);
}

void SyntacticalAnalysis::showError(std::string err,int line) {
    if(err=="") err="Something";
    printf("Syntactical Error - Expected %s at:%d\n",err.c_str(),line); 
    exit(1);
}

// <statements> ::= <cmd> { <cmd> }
Command* SyntacticalAnalysis::procStatements() {
    CommandsBlock* cmds = new CommandsBlock();
    cmds->addCommand(procCmd());

    while (testToken(TOKEN_SVAR) || 
           testToken(TOKEN_LVAR) || 
           testToken(TOKEN_HVAR) || 
           testToken(TOKEN_PRINT) || 
           testToken(TOKEN_PRINTLN) || 
           testToken(TOKEN_PUSH) || 
           testToken(TOKEN_UNSHIFT) || 
           testToken(TOKEN_IF) || 
           testToken(TOKEN_WHILE) || 
           testToken(TOKEN_DO) || 
           testToken(TOKEN_FOREACH)) {
        cmds->addCommand(procCmd());
    }

    return cmds;
}

// <cmd> ::= <assign> | <action> | <if> | <while> | <do-while> | <foreach>
Command* SyntacticalAnalysis::procCmd() {
    Command* c = 0;
    switch (current.type) {
        case TOKEN_SVAR:
        case TOKEN_LVAR:
        case TOKEN_HVAR:
            procAssign();
            break;
        case TOKEN_PRINT:
        case TOKEN_PRINTLN:
        case TOKEN_PUSH:
        case TOKEN_UNSHIFT:
            procAction();
            break;
        case TOKEN_IF:
            procIf();
            break;
        case TOKEN_WHILE:
            procWhile();
            break;
        case TOKEN_DO:
            procDo();
            break;
        case TOKEN_FOREACH:
            procForeach();
            break;
        default:
            showError("command");
            break;
    }
}

//<assign> ::= <lhs> '=' <rhs> [ <post> ] ';'
void SyntacticalAnalysis::procAssign(){
    procLHS();
    matchToken(TOKEN_ASSIGN);
    procRHS();
    //procPost();
    matchToken(TOKEN_DOT_COMMA);
}

//<action> ::= (print <rhs> | println [<rhs>] | push <rhs> ',' <rhs> | unshift <rhs> [ ',' <rhs> ]) [ <post> ] ';'
Command* SyntacticalAnalysis::procAction() {
    int line;
    ActionCommand* ac = 0;

    if (testToken(TOKEN_PRINT)) {
        // FIXME: print <rhs>
    } else if (testToken(TOKEN_PRINTLN)) {
        line = lex.line();

        matchToken(TOKEN_PRINTLN);

        Expr* expr = 0;
        if (testToken(TOKEN_NUMBER) ||
            testToken(TOKEN_STRING) ||
            testToken(TOKEN_OPENTHEBRA) ||
            testToken(TOKEN_OPENTHECUR) ||
            testToken(TOKEN_SVAR) ||
            testToken(TOKEN_LVAR) ||
            testToken(TOKEN_HVAR) ||
            testToken(TOKEN_INPUT) ||
            testToken(TOKEN_SIZE) ||
            testToken(TOKEN_SORT) ||
            testToken(TOKEN_REVERSE) ||
            testToken(TOKEN_KEYS) ||
            testToken(TOKEN_VALUES) ||
            testToken(TOKEN_EMPTY) ||
            testToken(TOKEN_POP) ||
            testToken(TOKEN_SHIFT) ||
            testToken(TOKEN_OPENTHEPAR)) {
            expr = procRHS();
        }

        ac = new PrintCommand(expr, true, line);
    } else if (testToken(TOKEN_PUSH)) {
        // FIXME: push <rhs> ',' <rhs>
    } else if (testToken(TOKEN_UNSHIFT)) {
        // FIXME: unshift <rhs> [ ',' <rhs> ])
    } else {
        showError();
    }

    // FIXME: [ <post> ]

    matchToken(TOKEN_DOT_COMMA);

    return ac;
}

//<if> ::= <if-head> '{' <statements> '}' [ else '{' <statements> '}' ]
void SyntacticalAnalysis::procIf(){
    procIfHead();
    if(testToken(TOKEN_OPENTHECUR)){
        matchToken(TOKEN_OPENTHECUR);
        procStatements();
        matchToken(TOKEN_CLOSETHECUR);
    }else{
        procStatements();
    }
    if(testToken(TOKEN_ELSE)){
        matchToken(TOKEN_ELSE);
        if(testToken(TOKEN_OPENTHECUR)){
            matchToken(TOKEN_OPENTHECUR);
            procStatements();
            matchToken(TOKEN_CLOSETHECUR);
        }else{
            procStatements();
        }
    }
}

//<while> ::= while '(' <boolexpr> ')' '{' <statements> '}'
void SyntacticalAnalysis::procWhile(){
    matchToken(TOKEN_WHILE);
    matchToken(TOKEN_OPENTHEPAR);
    procBoolExpr();
    matchToken(TOKEN_CLOSETHEPAR);
    if(testToken(TOKEN_OPENTHECUR)){
        matchToken(TOKEN_OPENTHECUR);
        procStatements();
        matchToken(TOKEN_CLOSETHECUR);
    }else{
        procStatements();
    }
}

//<do-while> ::= do '{' <statements> '}' while '(' <boolexpr> ')' ';'
void SyntacticalAnalysis::procDo(){
    matchToken(TOKEN_DO);
    if(testToken(TOKEN_OPENTHECUR)){
        matchToken(TOKEN_OPENTHECUR);
        procStatements();
        matchToken(TOKEN_CLOSETHECUR);
    }else{
        procStatements();
    }
    matchToken(TOKEN_WHILE);
    matchToken(TOKEN_OPENTHEPAR);
    procBoolExpr();
    matchToken(TOKEN_CLOSETHEPAR);
    matchToken(TOKEN_DOT_COMMA);
}

//<foreach> ::= <foreach-head> '{' <statements> '}'
void SyntacticalAnalysis::procForeach(){
    procForeachHead();
    if(testToken(TOKEN_OPENTHECUR)){
        matchToken(TOKEN_OPENTHECUR);
        procStatements();
        matchToken(TOKEN_CLOSETHECUR);
    }else{
        procStatements();
    }
}

//<post> ::= <if-head> | <foreach-head>
void SyntacticalAnalysis::procPost(){
    switch (current.type) {
        case TOKEN_IF:
            procIfHead();
            break;
        case TOKEN_FOREACH:
            procForeachHead();
            break;
        default:
            showError("(if|foreach) head");
            break;
    }
}

//<if-head> ::= if '(' <boolexpr> ')'
void SyntacticalAnalysis::procIfHead(){
    matchToken(TOKEN_IF);
    matchToken(TOKEN_OPENTHEPAR);
    procBoolExpr();
    matchToken(TOKEN_CLOSETHEPAR);
}

//<foreach-head> ::= foreach <scalar-var> '(' <rhs> ')'
void SyntacticalAnalysis::procForeachHead(){
    matchToken(TOKEN_FOREACH);
    matchToken(TOKEN_SVAR);
    matchToken(TOKEN_OPENTHEPAR);
    procRHS();
    matchToken(TOKEN_CLOSETHEPAR);
}

//<boolexpr> ::= [not] <cmpexpr> [ (and | or) <boolexpr> ]
void SyntacticalAnalysis::procBoolExpr(){
    if(testToken(TOKEN_NOT))
        matchToken(TOKEN_NOT);
    procCmpExpr();
    if(testToken(TOKEN_AND)||testToken(TOKEN_OR)){
        consumeToken();
        procBoolExpr();
    }
}

//<cmpexpr> ::= <sexpr> <relop> <sexpr>
void SyntacticalAnalysis::procCmpExpr(){
    procSExpr();
    procBoolOp();
    procSExpr();
}

//<relop> ::= '==' | '!=' | '<' | '>' | '<=' | '>='
void SyntacticalAnalysis::procBoolOp(){
    switch (current.type) {
        case TOKEN_EQUAL:
        case TOKEN_DIFF:
        case TOKEN_LESS:
        case TOKEN_GREATHER:
        case TOKEN_LESS_EQUAL:
        case TOKEN_GREATHER_EQUAL:
            consumeToken();
            break;
        default:
            showError("('=='|'!='|'<'|'>'|'<='|'>=')");
            break;
    }
}

//<lhs> ::= <scalar-var> | <list-var> [ '[' <rhs> ']' ] | <hash-var> [ '{' <rhs> '}' ]
void SyntacticalAnalysis::procLHS(){
    switch (current.type) {
        case TOKEN_SVAR:
            consumeToken();
            break;
        case TOKEN_LVAR:
            consumeToken();
            if(testToken(TOKEN_OPENTHEBRA)){
                matchToken(TOKEN_OPENTHEBRA);
                procRHS();
                matchToken(TOKEN_CLOSETHEBRA);
            }
            break;
        case TOKEN_HVAR:
            consumeToken();
            if(testToken(TOKEN_OPENTHECUR)){
                matchToken(TOKEN_OPENTHECUR);
                procRHS();
                matchToken(TOKEN_CLOSETHECUR);
            }
            break;
        default:
            showError("var");
            break;
    }
}

//<rhs> ::= <sexpr> [ '[' <rhs> ']' | '{' <rhs> '}' ]
Expr*  SyntacticalAnalysis::procRHS(){
    Expr* e = procSExpr();
    if(testToken(TOKEN_OPENTHECUR)){
        matchToken(TOKEN_OPENTHECUR);
        procRHS();
        matchToken(TOKEN_CLOSETHECUR);
    }else if(testToken(TOKEN_OPENTHEBRA)){
        matchToken(TOKEN_OPENTHEBRA);
        procRHS();
        matchToken(TOKEN_CLOSETHEBRA);
    }
    return e;
}

//<sexpr> ::= <expr> { '.' <expr> }
Expr* SyntacticalAnalysis::procSExpr(){
    Expr* e=nullptr;
    do{
        e=procExpr();
        if(testToken(TOKEN_DOT))
            consumeToken();
        else break;
    }while(true);
    return e;
}

//<expr> ::= <term> { ('+' | '-') <term> }
Expr* SyntacticalAnalysis::procExpr(){
    Expr* e=nullptr;
    do{
        e=procTerm();
        if(testToken(TOKEN_PLUS)||testToken(TOKEN_MINUS))
            consumeToken();
        else break;
    }while(true);
    return e;
}

//<term> ::= <factor> { ('*' | '/' | '%') <factor> }
Expr* SyntacticalAnalysis::procTerm(){
    Expr* e=nullptr;
    do{
        e=procFactor();
        if(testToken(TOKEN_TIMES)||testToken(TOKEN_DIV)||testToken(TOKEN_MOD))
            consumeToken();
        else break;
    }while(true);
    return e;
}

//<factor> ::= <number> | <string> | <function> | <var> | <list> | <hash> | '(' <sexpr> ')'
Expr* SyntacticalAnalysis::procFactor(){
    Expr* e = 0;
    switch (current.type) {
        case TOKEN_NUMBER:
            e=procNumber();
            break;
        case TOKEN_STRING:
            e=procString();
            break;
        case TOKEN_INPUT:
        case TOKEN_SIZE:
        case TOKEN_SORT:
        case TOKEN_REVERSE:
        case TOKEN_KEYS:
        case TOKEN_VALUES:
        case TOKEN_EMPTY:
            e=procFunction();
            break;
        case TOKEN_SVAR:
            e=procVar();
            break;    
        case TOKEN_LVAR:
            e=procList();
            break;
        case TOKEN_HVAR:
            e=procHash();
            break;
        case TOKEN_OPENTHEPAR:
            matchToken(TOKEN_OPENTHEPAR);
            e=procSExpr();
            matchToken(TOKEN_CLOSETHEPAR);
            break;
        default:
            showError("factor");
            break;
    }
    return e;
}

//<function> ::= (input | size | sort | reverse | keys | values | empty) <rhs>
Expr* SyntacticalAnalysis::procFunction(){
    Expr* e = 0;
    switch (current.type) {
        case TOKEN_INPUT:
        case TOKEN_SIZE:
        case TOKEN_SORT:
        case TOKEN_REVERSE:
        case TOKEN_KEYS:
        case TOKEN_VALUES:
        case TOKEN_EMPTY:
            consumeToken();
            procRHS();
            break;
        default:
            showError("function");
            break;
    }
    return e;
}

//<var> ::= <scalar-var> | <list-var> | <hash-var>
Expr* SyntacticalAnalysis::procVar(){
    Expr* e = 0;
    switch (current.type) {
        case TOKEN_SVAR:
        case TOKEN_LVAR:
        case TOKEN_HVAR:
            consumeToken();
            break;
        default:
            showError("var");
            break;
    }
    return e;
}

//<list> ::= '[' [ <rhs> { ',' <rhs> } ] ']'
Expr* SyntacticalAnalysis::procList(){
    Expr* e = 0;
    matchToken(TOKEN_OPENTHEBRA);
    do{
        procRHS();
        if(testToken(TOKEN_COMMA))
            consumeToken();
        else break;
    }while(true);
    matchToken(TOKEN_CLOSETHEBRA);
    return e;
}

//<hash> ::= '{' [ <rhs> '=>' <rhs> { ',' <rhs> '=>' <rhs> } ] '}'
Expr* SyntacticalAnalysis::procHash(){
    Expr* e = 0;
    matchToken(TOKEN_OPENTHECUR);
    do{
        procRHS();
        matchToken(TOKEN_BIND);
        procRHS();
        if(testToken(TOKEN_COMMA))
            consumeToken();
        else break;
    }while(true);
    matchToken(TOKEN_CLOSETHECUR);
    return e;
}

// <number>
Expr* SyntacticalAnalysis::procNumber(){
    int line=lex.line();
    std::string n=current.token;
    matchToken(TOKEN_NUMBER);
    IntegerValue* iv=new IntegerValue(atoi(n.c_str()), line);
    Expr* e=new ConstExpr((Value*)iv, line);
    return e;
}

// <string>
Expr* SyntacticalAnalysis::procString(){
    int line=lex.line();
    std::string n=current.token;
    matchToken(TOKEN_STRING);
    StringValue* sv=new StringValue(n,line);
    Expr* e=new ConstExpr((Value*)sv,line);
    return e;
}