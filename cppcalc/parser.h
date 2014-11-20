#ifndef parser_h
#define parser_h

#include "ast.h"
#include "scanner.h"

class Parser {
 public:
   Parser(istream* in);
   ~Parser();

   AST* parse();

 private:
   AST* Prog();
   AST* Stmts(AST* e);
   AST* Stmt();
   AST* Expr();
   AST* RestExpr(AST* e);
   AST* Term();
   AST* RestTerm(AST* e);
   AST* Storable();
   AST* MemOperation(AST* e);
   AST* Factor();

   Scanner* scan;
};


#endif   
