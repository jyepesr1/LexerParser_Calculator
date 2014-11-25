#include "calculator.h"
#include "parser.h"
#include "ast.h"
#include <string>
#include <iostream>
#include <sstream>
#include <map>

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

string Calculator::compile(string expr){

   static int i=1;

   stringstream ss;
   ss << i;

   Parser* parser = new Parser(new istringstream(expr));
   
   AST* tree = parser->parse();

   string var = expr.substr(0, 1);

   string comp = "#Expresion "+expr+"\n";
   comp+= "expr"+ss.str()+"\n";

   comp+= "# Instrucciones antes del recorrido del arbol abstracto sintactico\n";
   comp+= "   sp      := 1000\n";
   comp+= "   one     := 1\n";
   comp+= "   zero    := 0\n";
   comp+= "   memory  := zero\n";
   comp+= "# Comienza el recorrido del arbol en postorden\n";

   comp+= tree->toEwe();

   comp+= "# Assign\n";
   comp+= "   "+var+" := M[sp+0]\n";
   comp+= "# Write Result\n";
   comp+= "   operator1 := M[sp+0]\n";
   comp+= "   sp := sp - one\n";
   comp+= "   writeInt(operator1)\n";
   
   i++;
   
   delete tree;
   
   delete parser;
   
   return comp;
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
