#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define isdigitP(c)  ((unsigned char)(c) >= '0' && (unsigned char)(c) <= '9')

#include "Vector.h"
#include "Ecuaciones.h"
double EvaluarNum(char** Ecu);
double EvaluarFactor(char** Ecu, double X, double Y);
double EvaluarTerm(char** Ecu, double X, double Y);
double EvaluarExpr(char** Ecu, double X, double Y);
void Evaluar(TDAecuacion* EstrucEcu);




#endif // PARSER_H_INCLUDED
