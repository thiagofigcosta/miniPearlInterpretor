#include <cstdio>
#include "LexicalAnalysis.hpp"

LexicalAnalysis::LexicalAnalysis(const char* filename) : fline(1) {
    this->filename=(char*)filename;
    file = fopen(filename, "r");
    if (!file)
        throw "Unable to open file";
}

LexicalAnalysis::~LexicalAnalysis() {
    fclose(file);
}

int LexicalAnalysis::line() const {
    return fline;
}

Lexeme LexicalAnalysis::nextToken() {//dar nome pros estados
    Lexeme lex={"",TOKEN_END_OF_FILE};
    int state=STATE_BEGIN;
    while(state!=STATE_END_UNKNOWNTYPE&&state!=STATE_END_KNOWNTYPE){
    	int c=getc(file);
    	switch(state){
    		case STATE_BEGIN:
    			if(c==' '||c=='\r'||c=='\t'||c=='\n'){
    				state=STATE_BEGIN;
    				if(c=='\n')
    					fline++;
    			}else if(c=='#')
    				state=STATE_COMMENTARY;
    			else if(isdigit(c)){
    				lex.token+=(char)c;
    				lex.type=TOKEN_NUMBER;
    				state=STATE_NUMBER;
    			}else if(c=='!'){
    				lex.token+=(char)c;
    				state=STATE_NEGATE;
    			}else if(c=='='){
    				lex.token+=(char)c;
    				state=STATE_EQUALITY;
    			}else if(c=='<'||c=='>'){
    				lex.token+=(char)c;
    				state=STATE_INEQUALITY;
    			}else if(c==';'||c==':'||c=='.'||c==','||
    					 c=='('||c==')'||c=='{'||c=='}'||
    					 c=='['||c==']'||c=='+'||c=='-'||
    					 c=='*'||c=='/'){
    				lex.token+=(char)c;
    				state=STATE_END_UNKNOWNTYPE;
    			}else if(isalpha(c)){
    				lex.token+=(char)c;
    				state=STATE_WORD;
    			}else if(c=='\"'){
    				lex.type=TOKEN_STRING;
    				state=STATE_STRING;
    			}else if(c=='%'){
    				lex.token+=(char)c;
    				state=STATE_HVAR_OR_RAMAINER;
    			}else if(c=='$'){
    				lex.token+=(char)c;
    				lex.type=TOKEN_SVAR;
    				state=STATE_SVAR_OR_LVAR;
    			}else if(c=='@'){
    				lex.token+=(char)c;
    				lex.type=TOKEN_LVAR;
    				state=STATE_SVAR_OR_LVAR;
    			}else if(c==-1){
    				state=STATE_END_KNOWNTYPE;
    			}else{
    				lex.token+=(char)c;
    				lex.type=TOKEN_INVALID;
    				state=STATE_END_KNOWNTYPE;
    			}
    		break;

    		case STATE_COMMENTARY:
    			if(c=='\n'){
    				state=STATE_BEGIN;
                    fline++;
    			}
    		break;

    		case STATE_NUMBER:
    			if(isdigit(c)){
    				lex.token+=(char)c;
    				lex.type=TOKEN_NUMBER;
    			}else{
    				if(c!=-1)
    					ungetc(c, file);
    				state=STATE_END_KNOWNTYPE;
    			}
    		break;

    		case STATE_NEGATE:
    			if(c=='='){
    				lex.token+=(char)c;
    				state=STATE_END_UNKNOWNTYPE;
    			}else{
    				lex.type=TOKEN_INVALID;
    				state=STATE_END_KNOWNTYPE;
    			}
			break;

    		case STATE_EQUALITY:
    			if(c=='>'||c=='='){
    				lex.token+=(char)c;
    				state=STATE_END_UNKNOWNTYPE;
    			}else{
    				if(c!=-1)
    					ungetc(c, file);
    				state=STATE_END_UNKNOWNTYPE;
    			}
			break;

			case STATE_INEQUALITY:
    			if(c=='='){
    				lex.token+=(char)c;
    				state=STATE_END_UNKNOWNTYPE;
    			}else{
    				if(c!=-1)
    					ungetc(c, file);
    				state=STATE_END_UNKNOWNTYPE;
    			}
			break;

    		case STATE_WORD:
    			if(isalpha(c)||isdigit(c)){
    				lex.token+=(char)c;
    			}else{
    				if(c!=-1)
    					ungetc(c, file);
    				state=STATE_END_UNKNOWNTYPE;
    			}
			break;

			case STATE_STRING://TODO: criar estado para tratar '\''t' '\''n' '\''0'
    			if(c=='\"'){
    				state=STATE_END_KNOWNTYPE;
    			}else{
    				if(c==-1)
    					lex.type=TOKEN_UNEXPECTED_EOF;
    				else
    					lex.token+=(char)c;
    				if(c=='\n')
    					fline++;
    			}
			break;

			case STATE_HVAR_OR_RAMAINER:
    			if(isalpha(c)||isdigit(c)){
    				lex.token+=(char)c;
                    lex.type=TOKEN_HVAR;
    				state=STATE_XVAR_WORD;
    			}else{
    				if(c!=-1)
    					ungetc(c, file);
    				state=STATE_END_UNKNOWNTYPE;
    			}
			break;

			case STATE_SVAR_OR_LVAR:
    			if(isalpha(c)||isdigit(c)){
    				lex.token+=(char)c;
    				state=STATE_XVAR_WORD;
    			}
			break;


			case STATE_XVAR_WORD:
    			if(isalpha(c)||isdigit(c)){
    				lex.token+=(char)c;
    				state=STATE_XVAR_WORD;
    			}else{
    				if(c!=-1)
    					ungetc(c, file);
    				state=STATE_END_KNOWNTYPE;
    			}
			break;
    	}
    }
    if(state==STATE_END_UNKNOWNTYPE){
    	lex.type=symbols.find(lex.token);
    }
    return lex;
}

void LexicalAnalysis::printTokens(){
    LexicalAnalysis l(filename);
    Lexeme lex;
    while ((lex = l.nextToken()).type>0) {
        printf("(\"%s\", %d)\n", lex.token.c_str(), lex.type);
    }

    switch (lex.type) {
        case TOKEN_INVALID:
            printf("%02d: Lexema inválido [%s]\n", l.line(), lex.token.c_str());
            break;
        case TOKEN_UNEXPECTED_EOF:
            printf("%02d: Fim de arquivo inesperado\n", l.line());
            break;
        default:
            printf("(\"%s\", %d)\n", lex.token.c_str(), lex.type);
            break;
    }
}

std::map<std::string, TokenType> LexicalAnalysis::getSymbolMap(){
    return symbols.getSymbolMap();
}