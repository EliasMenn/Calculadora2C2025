#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void* datos;
    int CE;
    size_t capacidad;
    size_t tamElem;
} TDAvector;

TDAvector* CrearVector(size_t tamElem, int cantElem);
int AgregarElement(TDAvector* vec, void* elem);
void RecorrerVector(TDAvector* vec, void accion(void* element));
void* DestruirVector(TDAvector* vec);
void* DevolverElementoVec(TDAvector* vec, int numElem);
int QuitarElement(TDAvector* vec, int numElem);
int DevolverCantElem(TDAvector* vec);


#endif // VECTOR_H_INCLUDED
