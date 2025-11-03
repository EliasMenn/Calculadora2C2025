#include <stdio.h>
#include <stdlib.h>
#include "Menu.h"

int main(int argc, char *argv[])
{
    CrearIndice();
    TDAvector* vec;
    vec = CrearVector(sizeof(TDAecuacion),MAXELEMENTOS);
    MenuPrincipal(vec);
    return 0;
}

