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

  calc = new Calculator();

  try{

    do {

      cout << "> ";

      getline(cin, line);
      // line + '\n';
      int result = calc->eval(line);

      cout << "= " << result << endl;
    }while(cin);

  }catch(Exception ex) {
    cout << "Program Aborted due to exception!" << endl;
  }
  
  delete calc;
}
   
