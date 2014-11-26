#ifndef calculator_h
#define calculator_h

#include <string>
#include <map>
 
using namespace std;


class Calculator {
 public:
   Calculator();

   int eval(string expr);
   string compile(string expr);
   void store(int val);
   int recall();
   int getVar(string id);
   void setVar(string id, int a);
   void setEnv(char* env[]);
   string recorrerMapa();
   string recorrerVariables();

 private:
   int memory;
   map<string, int> variables;
};

extern Calculator* calc;

#endif

