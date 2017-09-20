#ifndef SYNTACTICAL_ANALYSIS_H
#define SYNTACTICAL_ANALYSIS_H

#include "../interpreter/expr/Expr.hpp"
#include "../interpreter/boolexpr/BoolExpr.hpp"
#include "../interpreter/boolexpr/PostCondition.hpp"
#include "../interpreter/boolexpr/ForeachHead.hpp"
#include "../interpreter/boolexpr/IfHead.hpp"
#include "../interpreter/boolexpr/SingleBoolExpr.hpp"
#include "../interpreter/command/Command.hpp"
#include "../interpreter/command/IfCommand.hpp"
#include "../interpreter/command/DoWhileCommand.hpp"
#include "../interpreter/command/ForeachCommand.hpp"
#include "../interpreter/command/WhileCommand.hpp"
#include "../lexical/TokenType.hpp"
#include "../lexical/LexicalAnalysis.hpp"

class SyntacticalAnalysis {
public:
    explicit SyntacticalAnalysis(LexicalAnalysis& lex);
    virtual ~SyntacticalAnalysis();

    static void showError(std::string err,int line);
    static void showError(std::string err,TokenType t,int line);
    void start();
    void execute();
private:
	LexicalAnalysis &lex;
	Lexeme current;
	Command* program;

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
	IfCommand* procIf();
	WhileCommand* procWhile();
	DoWhileCommand* procDo();
	ForeachCommand* procForeach();

	// PostCondition*
	PostCondition* procPost();
	IfHead* procIfHead();
	ForeachHead* procForeachHead();

	// BoolExpr*
	BoolExpr* procBoolExpr();
	BoolExpr* procCmpExpr();
	SingleBoolExpr::RelOp procBoolOp();

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
