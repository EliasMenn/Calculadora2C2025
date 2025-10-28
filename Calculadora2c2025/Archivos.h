#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LARGO_NOMBRE 50
#define carpeta "ArchivosGuardados/"

void CrearIndice();
int ContarCantArchivos(FILE* indice);
int buscarArchivo(FILE* indice, char* archivo);
void AgregarArchivo(FILE* indice, char* NuevoArchivo);
FILE* CrearArchivo(FILE* pf, FILE* indice);
void MostrarIndices(FILE* indice);
void LimpiarArchivos(FILE* indice);
#endif // ARCHIVOS_H_INCLUDED
