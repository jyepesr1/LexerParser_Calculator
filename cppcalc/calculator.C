#include "calculator.h"
#include "parser.h"
#include "ast.h"
#include <string>
#include <iostream>
#include <sstream>

Calculator::Calculator():
   memory(0)
{}

int Calculator::eval(string expr) {

   Parser* parser = new Parser(new istringstream(expr));
   
   AST* tree = parser->parse();
   
   int result = tree->evaluate();
   
   delete tree;
   
   delete parser;
   
   return result;
}

void Calculator::store(int val) {
   memory = val;
}

int Calculator::recall() {
   return memory;
}

int Calculator::getVar(string a){
	return variables[a];
}

void Calculator::setVar(string id, int a){
   variables[id] = a;
}

void Calculator::setEnv(char* env[]){
   int i=0;
   string vars="";
   string var="";
   int valor=0;
   while(env[i] != NULL){
      vars = env[i];
      if(vars.find("CALCVAR_")==0){
         var= vars.at(8);
         istringstream ss(vars.substr(10));
         ss >> valor;
         variables[var]=valor;
         break;
      }
      i++;
   }
}
