#ifndef SOLUCIONES_H_INCLUDED
#define SOLUCIONES_H_INCLUDED

#define isdigit(c)  ((unsigned char)(c) >= '0' && (unsigned char)(c) <= '9')
#define MAX 512
#include "Ecuaciones.h"
#include "Vector.h"
#include "Archivos.h"
#include "Parser.h"
int IngresarEcuacion(TDAecuacion** StrucEcuacion);
int VerificarEcuaciones(char* buffer, int*cantVariables);
int VerificarParentesis(char* buffer);
void VaciarMemoria(TDAvector* vec); //Destruye el Vec
void LimpiarMemoria(TDAvector* vec); //No Destruye el Vec
void MostrarEcuaciones(TDAvector* vec);
int CargarEcuMem(TDAvector* vec);
void ReemplazarEcuacion(TDAvector* vec, TDAecuacion* ecu);
void CargarArchivo(TDAvector* vec);
void DescargarArchivos(TDAvector* vec);
void SeleccionarEcu(TDAvector* vec);

#endif // SOLUCIONES_H_INCLUDED
