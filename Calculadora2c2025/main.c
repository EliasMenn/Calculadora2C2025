#include <stdio.h>
#include <stdlib.h>
#include "Menu.h"
int main()
{
    CrearIndice();
    TDAvector* vec;
    vec = CrearVector(sizeof(TDAecuacion),MAXELEMENTOS);
    MenuPrincipal(vec);
    return 0;
}
