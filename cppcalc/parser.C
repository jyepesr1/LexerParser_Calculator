#include "parser.h"
#include "calcex.h"
#include <string>
#include <sstream>
#include "token.h"

Parser::Parser(istream* in) {
   scan = new Scanner(in);
}

Parser::~Parser() {
   try {
      delete scan;
   } catch (...) {}
}

AST* Parser::parse() {
   return Prog();
}

// AST* Parser::Prog() {
//    AST* result = Expr();
//    Token* t = scan->getToken();

//    if (t->getType() != eof) {
//       cout << "Syntax Error: Expected EOF, found token at column " << t->getCol() << endl;
//       throw ParseError;
//    }

//    return result;
// }

AST* Parser::Prog(){
   AST* result = Stmts(NULL);
   
   Token* t = scan->getToken();

  if (t->getType() != eof) {
     cout << "Syntax Error: Expected EOF, found token at column " << t->getCol() << endl;
     throw ParseError;
  }

  return result;
}

AST* Parser::Stmts(AST* e){

   Token* t = scan->getToken();

   if(t->getType() == identifier){
      scan->putBackToken();
      return Stmts(Stmt());
   } 
   scan->putBackToken();
   return e;
 }

AST* Parser::Stmt(){
    Token* t = scan->getToken();
    
    if(t->getType() == identifier){
        t= scan->getToken();
        if(t->getType() == equals){
            AST* result = Expr();
            t=scan->getToken();
            if(t->getType() == semicolon){
              return result;  
            }else{
              cout << "Expected ';' found: " 
              << t->getType() << " at line: "
              << t->getLine() << " at Col: "
              << t->getCol() 
              << endl;

          throw ParseError;    
            }
            
        }else{
          cout << "Expected '=' found: " 
          << t->getType() << " at line: "
          << t->getLine() << " at Col: "
          << t->getCol() 
          << endl;

          throw ParseError; 
        }
    }else{
        cout << "Expected 'identifier' found: " 
          << t->getType() << " at line: "
          << t->getLine() << " at Col: "
          << t->getCol() 
          << endl;

          throw ParseError; 
    }
}

AST* Parser::Expr() {
   return RestExpr(Term());
}

AST* Parser::RestExpr(AST* e) {
   Token* t = scan->getToken();

   if (t->getType() == add) {
      return RestExpr(new AddNode(e,Term()));
   }

   if (t->getType() == sub)
      return RestExpr(new SubNode(e,Term()));

   scan->putBackToken();

   return e;
}

AST* Parser::Term() {
   return RestTerm(Storable());
   //write your Term() code here. This code is just temporary
   //so you can try the calculator out before finishing it.
//   Token* t = scan->getToken();
//
//  if (t->getType() == number) {
//    istringstream in(t->getLex());
//    int val;
//    in >> val;
//    return new NumNode(val);
//   }
//
//  cout << "Term not implemented" << endl;
//
//  throw ParseError; 
}

AST* Parser::RestTerm(AST* e) {
   Token* t = scan->getToken();

   if (t->getType() == times) {
      return RestTerm(new TimesNode(e,Storable()));
   }

   if (t->getType() == divide)
      return RestTerm(new DivideNode(e,Storable()));

   if (t->getType() == mod)
      return RestTerm(new ModNode(e,Storable()));

   scan->putBackToken();

   return e;
}

AST* Parser::Storable() {
    
  return MemOperation(Factor());
}

AST* Parser::MemOperation(AST* e){
    Token* t= scan->getToken();
    
    if(t->getType()==keyword){
        if(t->getLex().compare("S")==0){
            return new StoreNode(e);
        }
        if(t->getLex().compare("P")==0){
            return new PlusNode(e);
        }
        if(t->getLex().compare("M")==0){
            return new MinusNode(e);
        }
    }else{
       cout << "Expected 'keyword' found: " 
            << t->getType() << " at line: "
            << t->getLine() << " at Col: "
            << t->getCol() 
            << endl;

      throw ParseError; 
    }
    
   scan->putBackToken();
}

AST* Parser::Factor() {
  Token *t = scan->getToken();

  
  if (t->getType() == number) {
    istringstream in(t->getLex());
    int val;
    in >> val;
    return new NumNode(val);
  }

  if(t->getType() == keyword){
    if(t->getLex().compare("R") == 0){
      return new RecallNode(); 
    }
    else{
      cout << "Expected R found: " 
           << t->getType() << " at line: "
           << t->getLine() << " at Col: "
      	   << t->getCol() 
      	   << endl;

      throw ParseError; 
    }
  }

  // if(t->getType() == identifier){
  //   return new IdentifierNode();
  // }

  if(t->getType() == keyword){
    if(t->getLex().compare("C") == 0){
      return new ClearNode(); 
    }
    else{
      cout << "Expected C found: " 
           << t->getType() << " at line: "
           << t->getLine() << " at Col: "
           << t->getCol() 
           << endl;

      throw ParseError; 
    }
  }
  
  if(t->getType() == lparen){
    AST* result = Expr();
    t = scan->getToken();
    if(t->getType() == rparen){
      return result;
    }
    else{
      cout << "Expected ) found: " 
           << t->getType() << " at line: "
           << t->getLine() << " at Col: "
	   << t->getCol() 
	   << endl;
      
      throw ParseError;
    }
  }
  // cout << "Expected number or R or ( found: " 
  //      << t->getType() << " at line: "
  //      << t->getLine() << " at Col: "
  //      << t->getCol() 
  //      << endl;
      
  //     throw ParseError;
       
}
   
