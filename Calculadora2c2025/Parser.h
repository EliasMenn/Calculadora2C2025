#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define isdigitP(c)  ((unsigned char)(c) >= '0' && (unsigned char)(c) <= '9')

#include "Vector.h"
#include "Ecuaciones.h"
int EvaluarNum(char** Ecu);
int EvaluarFactor(char** Ecu, int X, int Y);
int EvaluarTerm(char** Ecu, int X, int Y);
int EvaluarExpr(char** Ecu, int X, int Y);
int Evaluar(TDAecuacion* EstrucEcu);




#endif // PARSER_H_INCLUDED
