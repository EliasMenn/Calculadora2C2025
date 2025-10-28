#ifndef ECUACIONES_H_INCLUDED
#define ECUACIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CARACTER_INVALIDO -1
#define ERROR_PARENTESIS -2
#define TODO_OK 0

typedef struct{
    char* ecuacion;
    size_t largo;
    int cantVar;
}TDAecuacion;

TDAecuacion* IniciarTDAecuacion(char* ecuacion, size_t largo, int cantVar);
void MostrarEcuacion(TDAecuacion* ecu);
void* LiberarTDAecuacion(void* element); // Libera solo el TDA
void* LimpiarTDAecuacion(void* element); //Libera el TDA y el puntero interior
void GuardarEcuacionTxT(TDAecuacion* ecu, FILE* archivo);
TDAecuacion* CargarEcuacionTxT(TDAecuacion* ecu, char* linea);
#endif // ECUACIONES_H_INCLUDED
