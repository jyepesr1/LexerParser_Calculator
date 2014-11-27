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
  bool compilador=false;

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
          var= vars.substr(0,1);
          istringstream ss(vars.substr(2));
          ss >> valor;
          calc->setVar(var, valor);
        }
      }

      if(opcion.compare("-c")==0){
        compilador=true;

        if(i==argc-1){
          hayFichero=true;
          string comp="";

          while(cin){

            cout << "> ";

            getline(cin, line);

            if(line.length()==0){
              cout << "\n" << endl;
              break;
            }

            var = line.substr(0, 1);

            comp+= calc->compile(line);

            int result = calc->eval(line);

            calc->setVar(var, result);
            
          }

          comp+= "end: halt\n";
          comp+= "equ  memory      M[0]\n";
          comp+= "equ  one         M[1]\n";
          comp+= "equ  zero        M[2]\n";
          comp+= "equ  operator1   M[3]\n";
          comp+= "equ  operator2   M[4]\n";
          comp+= "equ  sp          M[5]\n";

          comp+= calc->recorrerMapa();
          comp+= "equ  stack       M[1000]\n\n";

          char *s = new char[comp.length() + 1];

          FILE *fp;

          strcpy(s,comp.c_str());

          fp = fopen ( "a.ewe", "w" );

          fputs(s, fp); 

          fclose ( fp );
        }

      }

      if(compilador and argc>2){

        if(opcion.find(".calc") != string::npos){
          hayFichero= true;
          ifstream entrada;
          string line;
          string var;
          entrada.open(argv[i]);
          string comp="";

          while(!entrada.eof()){

            getline(entrada, line);

            if(line.length()==0){
              break;
            }

            var = line.substr(0, 1);

            comp+= calc->compile(line);

            int result = calc->eval(line);

            calc->setVar(var, result);

          }

          entrada.close();

          comp+= "end: halt\n";
          comp+= "equ  memory      M[0]\n";
          comp+= "equ  one         M[1]\n";
          comp+= "equ  zero        M[2]\n";
          comp+= "equ  operator1   M[3]\n";
          comp+= "equ  operator2   M[4]\n";
          comp+= "equ  sp          M[5]\n";
          comp+= calc->recorrerMapa();
          comp+= "equ  stack       M[1000]\n\n";

          char *s = new char[comp.length() + 1];

          FILE *fp;

          strcpy(s,comp.c_str());

          string nombre= argv[i];
          nombre = nombre.substr(0,nombre.find('.'));
          nombre+=".ewe";

          fp = fopen (nombre.c_str(), "w" );

          fputs(s, fp); 

          fclose ( fp );

        }

      }

      if(compilador==false){
        hayFichero= true;
        ifstream entrada;
        string line;
        string var;
        entrada.open(argv[i]);

        while(!entrada.eof()){

          getline(entrada, line);

          if(line.length()==0){
            break;
          }

          int result = calc->eval(line);

          var = line.substr(0, 1);

          calc->setVar(var, result);

          cout << "= " << var <<  " <- " << result << endl;               
        }

        entrada.close();
      }
    }
  }

  try{

    while(cin and !hayFichero){


      cout << "> ";

      getline(cin, line);

      if(line.length()==0){
        cout << "\n" << endl;
        break;
      }
      
      int result = calc->eval(line);

      var = line.substr(0, 1);

      calc->setVar(var, result);

      cout << "= " << var <<  " <- " << result << endl;
    }

  }catch(Exception ex) {
    cout << "Program Aborted due to exception!" << endl;
  }
  
  delete calc;

  return 0;
}
   
