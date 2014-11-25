#include <iostream>
#include <sstream>
#include <cstring>
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
      }else if(opcion.compare("-c")==0){
        hayFichero=true;
        string lista=""; 
        string comp="";

        while(cin){

          cout << "> ";

          getline(cin, line);

          int result = calc->eval(line);

          var = line.substr(0, 1);

          lista += var; 

          calc->setVar(var, result);

          comp+= calc->compile(line);
        }

        comp+= "end: halt\n";
            comp+= "equ  memory      M[0]\n";
            comp+= "equ  one         M[1]\n";
            comp+= "equ  zero        M[2]\n";
            comp+= "equ  operator1   M[3]\n";
            comp+= "equ  operator2   M[4]\n";
            comp+= "equ  sp          M[5]\n";

            stringstream ss;
            string var="";
            int a=6;
            for(int i=0; i<lista.length()-1; i++){
              ss << a;
              var =lista.at(i);
              comp+="equ  "+var+"           M["+ss.str()+"]\n";
              a++;
            }

            comp+= "equ  stack       M[1000]\n";

            char *s = new char[comp.length() + 1];

            FILE *fp;

            strcpy(s,comp.c_str());

            fp = fopen ( "a.ewe", "w" );

            fputs(s, fp); 

            fclose ( fp );

        delete calc;


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

        delete calc;

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
   
