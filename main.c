#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbol.h"

int main(int argc, char *argv[]) {

  Arbol equipo1 = creaABB(argv[1], 1);
  Arbol equipo2 = creaABB(argv[1], 2);  

  crea_parejas(equipo1, equipo2, argv[2]);
  
  printf(":)\n");
  return 0;
}
