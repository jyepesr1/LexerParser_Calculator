#include <iostream>
#include <sstream>
#include <string>
#include "calcex.h"
#include "calculator.h"
#include <cstdlib>
using namespace std;

Calculator* calc;

int main(int argc, char* argv[], char* env[]) {
  string line;
  string var;

  calc = new Calculator();

  calc->setEnv(env);

  if(argc>1){
    string opcion = "";
    string var="";
    int valor=0;
    for(int i=0; i<argc; ++i){
      opcion=argv[i];
      if(opcion.compare("-v")){
        if(i++ < argc){
          string vars = argv[i+1];
          var= vars.at(0);
          istringstream ss(vars.substr(2));
          ss >> valor;
          calc->setVar(var, valor);
        }
      }
    }
  }


  try{

    do {

      cout << "> ";

      getline(cin, line);

      int result = calc->eval(line);

      var = line.substr(0, 1);

      calc->setVar(var, result);

      cout << "= " << var <<  " <- " << result << endl;
    }while(cin);

  }catch(Exception ex) {
    cout << "Program Aborted due to exception!" << endl;
  }
  
  delete calc;
}
   
