#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include "SyntacticalAnalysis.hpp"

#include "../interpreter/boolexpr/IfHead.hpp"
#include "../interpreter/boolexpr/ForeachHead.hpp"
#include "../interpreter/boolexpr/CompositeBoolExpr.hpp"
#include "../interpreter/boolexpr/NotBoolExpr.hpp"
#include "../interpreter/boolexpr/SingleBoolExpr.hpp"
#include "../interpreter/command/AssignCommand.hpp"
#include "../interpreter/command/ActionCommand.hpp"
#include "../interpreter/command/CommandsBlock.hpp"
#include "../interpreter/command/IfCommand.hpp"
#include "../interpreter/command/ForeachCommand.hpp"
#include "../interpreter/command/WhileCommand.hpp"
#include "../interpreter/command/PrintCommand.hpp"
#include "../interpreter/command/PushCommand.hpp"
#include "../interpreter/command/UnshiftCommand.hpp"
#include "../interpreter/value/IntegerValue.hpp"
#include "../interpreter/value/StringValue.hpp"
#include "../interpreter/value/ListValue.hpp"
#include "../interpreter/value/HashValue.hpp"
#include "../interpreter/expr/HashIndexExpr.hpp"
#include "../interpreter/expr/ListIndexExpr.hpp"
#include "../interpreter/expr/ScalarVariable.hpp"
#include "../interpreter/expr/HashVariable.hpp"
#include "../interpreter/expr/ListVariable.hpp"
#include "../interpreter/expr/ConstExpr.hpp"
#include "../interpreter/expr/IntegerExpr.hpp"
#include "../interpreter/expr/FunctionExpr.hpp"
#include "../interpreter/expr/StringconcatExpr.hpp"
#include "../interpreter/expr/Variable.hpp"

SyntacticalAnalysis::SyntacticalAnalysis(LexicalAnalysis& lex):lex(lex), current(lex.nextToken()) {
}

SyntacticalAnalysis::~SyntacticalAnalysis() {
}
void SyntacticalAnalysis::start(){
    program=procStatements(); 
    matchToken(TOKEN_END_OF_FILE);
}
void SyntacticalAnalysis::execute(){
    program->execute();
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
    err="Unkown token("+std::to_string(token)+")";
    for(auto &i:lex.getSymbolMap()){
        if(i.second==token){
            err="\'"+i.first+"\'";
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
    CommandsBlock* cmds=new CommandsBlock();
    while (testToken(TOKEN_SVAR)|| 
           testToken(TOKEN_LVAR)|| 
           testToken(TOKEN_HVAR)|| 
           testToken(TOKEN_PRINT)|| 
           testToken(TOKEN_PRINTLN)|| 
           testToken(TOKEN_PUSH)|| 
           testToken(TOKEN_UNSHIFT)|| 
           testToken(TOKEN_IF)|| 
           testToken(TOKEN_WHILE)|| 
           testToken(TOKEN_DO)|| 
           testToken(TOKEN_FOREACH)){
        cmds->addCommand(procCmd());
    }
    return cmds;
}

// <cmd> ::= <assign> | <action> | <if> | <while> | <do-while> | <foreach>
Command* SyntacticalAnalysis::procCmd() {
    Command* c=nullptr;
    switch (current.type) {
        case TOKEN_SVAR:
        case TOKEN_LVAR:
        case TOKEN_HVAR:
            c=procAssign();
            break;
        case TOKEN_PRINT:
        case TOKEN_PRINTLN:
        case TOKEN_PUSH:
        case TOKEN_UNSHIFT:
            c=procAction();
            break;
        case TOKEN_IF:
            c=procIf();
            break;
        case TOKEN_WHILE:
            c=procWhile();
            break;
        case TOKEN_DO:
            c=procDo();
            break;
        case TOKEN_FOREACH:
            c=procForeach();
            break;
        default:
            showError("command");
            break;
    }
    return c;
}

//<assign> ::= <var> '=' <rhs> [ <post> ] ';' 
Command* SyntacticalAnalysis::procAssign(){
    Command* ac=nullptr;
    Expr* var=procVar();
    matchToken(TOKEN_ASSIGN);
    Expr* e=procRHS();
    ac=new AssignCommand((SetExpr*)var,e,lex.line());
    if(testToken(TOKEN_IF)){
        IfHead* post=procIfHead();
        ac=new IfCommand(post,ac,lex.line());
    }
    matchToken(TOKEN_DOT_COMMA);
    return ac;
}

//<action> ::= (print <rhs> | println [<rhs>] | push <rhs> ',' <rhs> | unshift <rhs> [ ',' <rhs> ]) [ <post> ] ';'
Command* SyntacticalAnalysis::procAction() {
    int line=lex.line();
    Command* ac=nullptr;
    if (testToken(TOKEN_PRINT)) {
        matchToken(TOKEN_PRINT);
        Expr* expr=nullptr;
        if (testToken(TOKEN_NUMBER)||
            testToken(TOKEN_STRING)||
            testToken(TOKEN_OPENTHEBRA)||
            testToken(TOKEN_OPENTHECUR)||
            testToken(TOKEN_SVAR)||
            testToken(TOKEN_LVAR)||
            testToken(TOKEN_HVAR)||
            testToken(TOKEN_INPUT)||
            testToken(TOKEN_SIZE)||
            testToken(TOKEN_SORT)||
            testToken(TOKEN_REVERSE)||
            testToken(TOKEN_KEYS)||
            testToken(TOKEN_VALUES)||
            testToken(TOKEN_EMPTY)||
            testToken(TOKEN_POP)||
            testToken(TOKEN_SHIFT)||
            testToken(TOKEN_OPENTHEPAR)){
            expr = procRHS();
        }
        ac=new PrintCommand(expr, false, line);
    } else if (testToken(TOKEN_PRINTLN)) {
        matchToken(TOKEN_PRINTLN);
        Expr* expr=nullptr;
        if (testToken(TOKEN_NUMBER)||
            testToken(TOKEN_STRING)||
            testToken(TOKEN_OPENTHEBRA)||
            testToken(TOKEN_OPENTHECUR)||
            testToken(TOKEN_SVAR)||
            testToken(TOKEN_LVAR)||
            testToken(TOKEN_HVAR)||
            testToken(TOKEN_INPUT)||
            testToken(TOKEN_SIZE)||
            testToken(TOKEN_SORT)||
            testToken(TOKEN_REVERSE)||
            testToken(TOKEN_KEYS)||
            testToken(TOKEN_VALUES)||
            testToken(TOKEN_EMPTY)||
            testToken(TOKEN_POP)||
            testToken(TOKEN_SHIFT)||
            testToken(TOKEN_OPENTHEPAR)){
            expr = procRHS();
        }
        ac=new PrintCommand(expr, true, line);
    } else if (testToken(TOKEN_PUSH)) {
        matchToken(TOKEN_PUSH);
        Expr* expr0=procRHS();
        matchToken(TOKEN_COMMA);
        Expr* expr1=procRHS();
        ac=new PushCommand(expr0,expr1,line);
    } else if (testToken(TOKEN_UNSHIFT)) {
        matchToken(TOKEN_UNSHIFT);
        Expr* expr0=procRHS();
        matchToken(TOKEN_COMMA);
        Expr* expr1=procRHS();
        ac=new UnshiftCommand(expr0,expr1,line);
    } else {
        showError();
    }
    if(testToken(TOKEN_IF)){
        IfHead* post=procIfHead();
        ac=new IfCommand(post,ac,line);
    }
    matchToken(TOKEN_DOT_COMMA);
    return ac;
}

//<if> ::= <if-head> '{' <statements> '}' [ else '{' <statements> '}' ]
IfCommand* SyntacticalAnalysis::procIf(){
    int line=lex.line();
    IfHead* cond=procIfHead();
    Command* then=nullptr;
    Command* elsi=nullptr; 
    if(testToken(TOKEN_OPENTHECUR)){
        matchToken(TOKEN_OPENTHECUR);
        then=procStatements();
        matchToken(TOKEN_CLOSETHECUR);
    }else{
        then=procCmd();
    }
    if(testToken(TOKEN_ELSE)){
        matchToken(TOKEN_ELSE);
        if(testToken(TOKEN_OPENTHECUR)){
            matchToken(TOKEN_OPENTHECUR);
            elsi=procStatements();
            matchToken(TOKEN_CLOSETHECUR);
        }else{
            elsi=procCmd();
        }
    }
    if(elsi==nullptr)
        return new IfCommand(cond,then,line);
    else 
        return new IfCommand(cond,then,elsi,line);
}

//<while> ::= while '(' <boolexpr> ')' '{' <statements> '}'
WhileCommand* SyntacticalAnalysis::procWhile(){
    Command* cmd=nullptr;
    matchToken(TOKEN_WHILE);
    matchToken(TOKEN_OPENTHEPAR);
    BoolExpr* boolxp=procBoolExpr();
    matchToken(TOKEN_CLOSETHEPAR);
    if(testToken(TOKEN_OPENTHECUR)){
        matchToken(TOKEN_OPENTHECUR);
        cmd=procStatements();
        matchToken(TOKEN_CLOSETHECUR);
    }else{
        cmd=procCmd();
    }
    return new WhileCommand(boolxp,cmd,lex.line());
}

//<do-while> ::= do '{' <statements> '}' while '(' <boolexpr> ')' ';'
DoWhileCommand* SyntacticalAnalysis::procDo(){
    Command* cmd=nullptr;
    matchToken(TOKEN_DO);
    if(testToken(TOKEN_OPENTHECUR)){
        matchToken(TOKEN_OPENTHECUR);
        cmd=procStatements();
        matchToken(TOKEN_CLOSETHECUR);
    }else{
        cmd=procCmd();
    }
    matchToken(TOKEN_WHILE);
    matchToken(TOKEN_OPENTHEPAR);
    BoolExpr* boolxp=procBoolExpr();
    matchToken(TOKEN_CLOSETHEPAR);
    matchToken(TOKEN_DOT_COMMA);
    return new DoWhileCommand(boolxp,cmd,lex.line());
}

//<foreach> ::= <foreach-head> '{' <statements> '}'
ForeachCommand* SyntacticalAnalysis::procForeach(){
    Command* cmd=nullptr;
    ForeachHead* fh=procForeachHead();
    if(testToken(TOKEN_OPENTHECUR)){
        matchToken(TOKEN_OPENTHECUR);
        cmd=procStatements();
        matchToken(TOKEN_CLOSETHECUR);
    }else{
        cmd=procCmd();
    }
    return new ForeachCommand(fh,cmd,lex.line());
}

//<post> ::= <if-head> | <foreach-head>
PostCondition* SyntacticalAnalysis::procPost(){
    PostCondition* pc=nullptr;
    switch (current.type) {
        case TOKEN_IF:
            pc=procIfHead();
            break;
        case TOKEN_FOREACH:
            pc=procForeachHead();
            break;
        default:
            showError("(if|foreach) head");
            break;
    }
    return pc;
}

//<if-head> ::= if '(' <boolexpr> ')'
IfHead* SyntacticalAnalysis::procIfHead(){
    BoolExpr* expr=nullptr;
    matchToken(TOKEN_IF);
    if(testToken(TOKEN_OPENTHEPAR)){
        matchToken(TOKEN_OPENTHEPAR);
        expr=procBoolExpr();
        matchToken(TOKEN_CLOSETHEPAR);
    }else
        expr=procBoolExpr();
    return new IfHead(expr,lex.line());
}

//<foreach-head> ::= foreach <scalar-var> '(' <rhs> ')'
ForeachHead* SyntacticalAnalysis::procForeachHead(){
    matchToken(TOKEN_FOREACH);
    if(!testToken(TOKEN_SVAR)) matchToken(TOKEN_SVAR);
    Expr* var=procVar();
    matchToken(TOKEN_OPENTHEPAR);
    Expr* e=procRHS();
    matchToken(TOKEN_CLOSETHEPAR);
    return new ForeachHead((Variable*)var,e,lex.line());
}

//<boolexpr> ::= [not] <cmpexpr> [ (and | or) <boolexpr> ]
BoolExpr* SyntacticalAnalysis::procBoolExpr(){
    BoolExpr* be0=nullptr;
    bool negate=false;
    if(testToken(TOKEN_NOT)){
        matchToken(TOKEN_NOT);
        negate=true;
    }
    be0=procCmpExpr();
    if(negate)
        be0=new NotBoolExpr(be0,lex.line());
    if(testToken(TOKEN_AND)||testToken(TOKEN_OR)){
        CompositeBoolExpr::BoolOp op;
        if(testToken(TOKEN_AND))
            op=CompositeBoolExpr::And;
        else
            op=CompositeBoolExpr::Or;
        consumeToken();
        BoolExpr* be1=procBoolExpr();
        be0=new CompositeBoolExpr(be0,op,be1,lex.line());
    }
    return be0;
}

//<cmpexpr> ::= <sexpr> <relop> <sexpr>
BoolExpr* SyntacticalAnalysis::procCmpExpr(){
    Expr* e0=procSExpr();
    if(testToken(TOKEN_EQUAL)||testToken(TOKEN_DIFF)||testToken(TOKEN_LESS)||testToken(TOKEN_GREATHER)||testToken(TOKEN_LESS_EQUAL)||testToken(TOKEN_GREATHER_EQUAL)){
        SingleBoolExpr::RelOp op=procBoolOp();
        Expr* e1=procSExpr();
        return new SingleBoolExpr(e0,op,e1,lex.line());
    }else{
        return new SingleBoolExpr(e0,SingleBoolExpr::NotEqual,new ConstExpr(new IntegerValue(0,lex.line()),lex.line()),lex.line());
    }
}

//<relop> ::= '==' | '!=' | '<' | '>' | '<=' | '>='
SingleBoolExpr::RelOp SyntacticalAnalysis::procBoolOp(){
    SingleBoolExpr::RelOp op;
    switch (current.type) {
        case TOKEN_EQUAL:
            op=SingleBoolExpr::Equal;break;
        case TOKEN_DIFF:
            op=SingleBoolExpr::NotEqual;break;
        case TOKEN_LESS:
            op=SingleBoolExpr::LowerThan;break;
        case TOKEN_GREATHER:
            op=SingleBoolExpr::GreaterThan;break;
        case TOKEN_LESS_EQUAL:
            op=SingleBoolExpr::LowerEqual;break;
        case TOKEN_GREATHER_EQUAL:
            op=SingleBoolExpr::GreaterEqual;break;
        default:
            showError("('=='|'!='|'<'|'>'|'<='|'>=')");
            break;
    }
    consumeToken();
    return op;
}

//<rhs> ::= <sexpr> [ '[' <rhs> ']' | '{' <rhs> '}' ]
Expr*  SyntacticalAnalysis::procRHS(){
    Expr* e0=procSExpr();
    Expr* e1=nullptr;
    if(testToken(TOKEN_OPENTHECUR)){
        matchToken(TOKEN_OPENTHECUR);
        e1=procRHS();
        matchToken(TOKEN_CLOSETHECUR);
        e0=new HashIndexExpr(e0,e1,lex.line());
    }else if(testToken(TOKEN_OPENTHEBRA)){
        matchToken(TOKEN_OPENTHEBRA);
        e1=procRHS();
        matchToken(TOKEN_CLOSETHEBRA);
        e0=new ListIndexExpr(e0,e1,lex.line());
    }
    return e0;
}

//<sexpr> ::= <expr> { '.' <expr> }
Expr* SyntacticalAnalysis::procSExpr(){
    Expr* e0=procExpr();
    do{
        if(testToken(TOKEN_CONCAT)){
            consumeToken();
            Expr* e1=procExpr();
            e0=new StringconcatExpr(e0,e1,lex.line());
        }else break;
    }while(true);
    return e0;
}

//<expr> ::= <term> { ('+' | '-') <term> }
Expr* SyntacticalAnalysis::procExpr(){
    Expr* e0=procTerm();
    do{
        if(testToken(TOKEN_PLUS)||testToken(TOKEN_MINUS)){
            Expr* e1=nullptr;
            IntegerExpr::IntegerOp op;
            if(testToken(TOKEN_PLUS))
                op=IntegerExpr::Add;
            else
                op=IntegerExpr::Sub;
            consumeToken();
            e1=procTerm();
            e0=new IntegerExpr(e0,op,e1,lex.line());
        }else break;
    }while(true);
    return e0;
}

//<term> ::= <factor> { ('*' | '/' | '%') <factor> }
Expr* SyntacticalAnalysis::procTerm(){
    Expr* e0=procFactor();
    do{
        if(testToken(TOKEN_TIMES)||testToken(TOKEN_DIV)||testToken(TOKEN_MOD)){
            Expr* e1=nullptr;
            IntegerExpr::IntegerOp op;
            if(testToken(TOKEN_TIMES))
                op=IntegerExpr::Mul;
            else if(testToken(TOKEN_DIV))
                op=IntegerExpr::Div;
            else
                op=IntegerExpr::Mod;
            consumeToken();
            e1=procFactor();
            e0=new IntegerExpr(e0,op,e1,lex.line());
        }else break;
    }while(true);
    return e0;
}

//<factor> ::= <number> | <string> | <function> | <var> | <list> | <hash> | '(' <sexpr> ')'
Expr* SyntacticalAnalysis::procFactor(){
    Expr* e=nullptr;
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
        case TOKEN_LVAR:
        case TOKEN_HVAR:
            e=procVar();
            break;    
        case TOKEN_OPENTHEBRA:
            e=procList();
            break;
        case TOKEN_OPENTHECUR:
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
    FunctionExpr::FunctionType op;
    switch (current.type) {
        case TOKEN_INPUT:
            op=FunctionExpr::Input;break;
        case TOKEN_SIZE:
            op=FunctionExpr::Size;break;
        case TOKEN_SORT:
            op=FunctionExpr::Sort;break;
        case TOKEN_REVERSE:
            op=FunctionExpr::Reverse;break;
        case TOKEN_KEYS:
            op=FunctionExpr::Keys;break;
        case TOKEN_VALUES:
            op=FunctionExpr::Values;break;
        case TOKEN_EMPTY:
            op=FunctionExpr::Empty;break;
        default:
            showError("function");
            break;
    }
    consumeToken();
    Expr* e=procRHS();
    return new FunctionExpr(op,e,lex.line());
}

//<var> ::= <scalar-var> | <list-var> | <hash-var>
Expr* SyntacticalAnalysis::procVar(){
    Expr* e=nullptr;
    Expr* idx=nullptr;
    switch (current.type) {
        case TOKEN_SVAR:
        case TOKEN_LVAR:
        case TOKEN_HVAR:
            break;
        default:
            showError("var");
            break;
    }
    if(globalScope.find(current.token)!=globalScope.end()){
        e=(Expr*)globalScope[current.token];
        if(testToken(TOKEN_HVAR)){
            consumeToken();
            if(testToken(TOKEN_OPENTHECUR)){
                matchToken(TOKEN_OPENTHECUR);
                idx=procRHS();
                matchToken(TOKEN_CLOSETHECUR);
                e=new HashIndexExpr(e,idx,lex.line());
            }
        }else if(testToken(TOKEN_LVAR)){
            consumeToken();
            if(testToken(TOKEN_OPENTHEBRA)){
                matchToken(TOKEN_OPENTHEBRA);
                idx=procRHS();
                matchToken(TOKEN_CLOSETHEBRA);
                e=new ListIndexExpr(e,idx,lex.line());
            }
        }else consumeToken();
    }else{
        if(testToken(TOKEN_SVAR))
            e=new ScalarVariable(current.token);
        else if(testToken(TOKEN_LVAR))
            e=new ListVariable(current.token);
        else
            e=new HashVariable(current.token);
        globalScope[current.token]=(Variable*)e;
        consumeToken();
    }
    return e;
}

//<list> ::= '[' [ <rhs> { ',' <rhs> } ] ']'
Expr* SyntacticalAnalysis::procList(){
    std::vector<Value*> e;
    matchToken(TOKEN_OPENTHEBRA);
    if(!testToken(TOKEN_CLOSETHEBRA)){ 
        e.push_back(procRHS()->expr());
        do{
            if(testToken(TOKEN_COMMA)){
                consumeToken();
                e.push_back(procRHS()->expr());
            }
            else break;
        }while(true);
    }
    ListValue* lv=new ListValue(e,lex.line());
    matchToken(TOKEN_CLOSETHEBRA);
    return new ConstExpr((Value*)lv,lex.line());
}

//<hash> ::= '{' [ <rhs> '=>' <rhs> { ',' <rhs> '=>' <rhs> } ] '}'
Expr* SyntacticalAnalysis::procHash(){
    std::map<std::string,Value*> e;
    matchToken(TOKEN_OPENTHECUR);
    if(!testToken(TOKEN_CLOSETHECUR)){ 
        StringValue* sv=(StringValue*)procRHS()->expr();
        std::string s=sv->value();
        matchToken(TOKEN_BIND);
        e[s]=procRHS()->expr();
        do{
            if(testToken(TOKEN_COMMA)){
                consumeToken();
                sv=(StringValue*)procRHS()->expr();
                std::string s=sv->value();
                matchToken(TOKEN_BIND);
                e[s]=procRHS()->expr();
            }
            else break;
        }while(true);
    }
    HashValue* hv=new HashValue(e,lex.line());
    matchToken(TOKEN_CLOSETHECUR);
    return new ConstExpr((Value*)hv,lex.line());
}

// <number>
Expr* SyntacticalAnalysis::procNumber(){
    std::string n=current.token;
    matchToken(TOKEN_NUMBER);
    IntegerValue* iv=new IntegerValue(atoi(n.c_str()), lex.line());
    return new ConstExpr((Value*)iv, lex.line());
}

// <string>
Expr* SyntacticalAnalysis::procString(){
    std::string n=current.token;
    matchToken(TOKEN_STRING);
    StringValue* sv=new StringValue(n,lex.line());
    return new ConstExpr((Value*)sv,lex.line());
}