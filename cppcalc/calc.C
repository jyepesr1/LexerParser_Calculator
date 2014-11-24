#include <iostream>
#include <sstream>
#include <string>
#include "calcex.h"
#include "calculator.h"
#include <cstdlib>
#include <fstream>

using namespace std;

Calculator* calc;

int main(int argc, char* argv[], char* env[]) {
  string line;
  string var;
  bool hayFichero=false;

  calc = new Calculator();

  calc->setEnv(env);

  if(argc>1){
    string opcion = "";
    string var="";
    int valor=0;
    for(int i=1; i<argc; i++){
      opcion=argv[i];
      if(opcion.compare("-v")==0){
        if(++i < argc){
          string vars = argv[i];
          var= vars.at(0);
          istringstream ss(vars.substr(2));
          ss >> valor;
          calc->setVar(var, valor);
        }
      }else {
        hayFichero= true;
        ifstream entrada;
        string line;
        string var;
        entrada.open(argv[i]);

        do{

          getline(entrada, line);

          int result = calc->eval(line);

          var = line.substr(0, 1);

          calc->setVar(var, result);

          cout << "= " << var <<  " <- " << result << endl;               
        }while(!entrada.eof());

        entrada.close();

      }
    }
  }

  try{

    while(cin and !hayFichero){

      cout << "> ";

      getline(cin, line);

      int result = calc->eval(line);

      var = line.substr(0, 1);

      calc->setVar(var, result);

      cout << "= " << var <<  " <- " << result << endl;
    }

  }catch(Exception ex) {
    cout << "Program Aborted due to exception!" << endl;
  }
  
  delete calc;
}
   
