#ifndef SYNTACTICAL_ANALYSIS_H
#define SYNTACTICAL_ANALYSIS_H

#include "../interpreter/expr/Expr.hpp"
#include "../interpreter/command/Command.hpp"
#include "../lexical/TokenType.hpp"
#include "../lexical/LexicalAnalysis.hpp"

class SyntacticalAnalysis {
public:
    explicit SyntacticalAnalysis(LexicalAnalysis& lex);
    virtual ~SyntacticalAnalysis();

    static void showError(std::string err,int line);
    static void showError(std::string err,TokenType t,int line);
    void start();
private:
	LexicalAnalysis &lex;
	Lexeme current;

	void matchToken(TokenType token);
	bool testToken(TokenType token);
	void consumeToken();
	void showError();
	void showError(std::string err);
	void showError(TokenType token);
	
	Command* procStatements();
	Command* procCmd();
	Command* procAssign();
	Command* procAction();

	 // Command*
	PostCondition* procIf();
	PostCondition* procWhile();
	PostCondition* procDo();
	PostCondition* procForeach();

	// PostCondition*
	PostCondition* procPost();
	PostCondition* procIfHead();
	PostCondition* procForeachHead();

	// BoolExpr*
	Expr* procBoolExpr();
	Expr* procCmpExpr();
	RelOp procBoolOp();

	Expr* procRHS();
	Expr* procSExpr();
	Expr* procExpr();
	Expr* procTerm();
	Expr* procFactor();
	Expr* procFunction();
	Expr* procVar();
	Expr* procList();
	Expr* procHash();
	Expr* procNumber();
	Expr* procString();
};

#endif
