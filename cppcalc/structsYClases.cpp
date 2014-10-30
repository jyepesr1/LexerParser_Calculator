/*
 * fichero: Estructura-01
 * compilar: $ g++ -o Estructura-01 Estructura-01.C
 * ejecutar: $ ./Estructura-01
 * proposito: Mostrar estructuras 
 */
#include <iostream>

using namespace std;
struct Empleado {
  char nombre[30];
  char id[30];
  int tipoID;
};

struct Empleado2 {
  char *nombre;
  char *id;
  int tipoID;
};

int
main() {

  struct Empleado emp1 = { "Juan", "XXXX", 1 };
  Empleado emp2 = { "Diego", "YYYY", 1 };
  Empleado2 emp3 = { "Alejandro", "WWWW", 1 };
  Empleado* pEmp;

  pEmp = &emp1;
  pEmp->tipoID = 2;
  cout << pEmp->nombre << " " << pEmp->tipoID << endl;

  pEmp = &emp2;
  
  pEmp->tipoID = 2;
  cout << pEmp->nombre << " " << pEmp->tipoID << endl;

  return 0;
}
