#include "Ecuaciones.h"
TDAecuacion* IniciarTDAecuacion(char* ecuacion, size_t largo, int cantVar)
{
    TDAecuacion* StruEcuacion;
    StruEcuacion = malloc(sizeof(TDAecuacion));
    if(StruEcuacion == NULL)
    {
        return NULL;
    }
    StruEcuacion->ecuacion = malloc(largo);
    if(StruEcuacion->ecuacion == NULL)
    {
        free(StruEcuacion);
        return NULL;
    }
    strcpy(StruEcuacion->ecuacion,ecuacion);
    StruEcuacion->largo = largo;
    StruEcuacion->cantVar = cantVar;
    return StruEcuacion;
}

void* LimpiarTDAecuacion(void* element)
{
    TDAecuacion* StruEcuacion = (TDAecuacion*) element;
    free(StruEcuacion->ecuacion);
    LiberarTDAecuacion(StruEcuacion);
    return StruEcuacion;
}

void* LiberarTDAecuacion(void* element)
{
    TDAecuacion* StruEcuacion = (TDAecuacion*) element;
    free(StruEcuacion);
    StruEcuacion = NULL;
    return StruEcuacion;
}

void MostrarEcuacion(TDAecuacion* ecu)
{
    printf("%s \n", ecu->ecuacion);
}

void GuardarEcuacionTxT(TDAecuacion* ecu, FILE* archivo)
{
    TDAecuacion* ecuac = ecu;
    fprintf(archivo, "%d|%lu|%s\n", ecuac->cantVar, (unsigned long)ecuac->largo, ecuac->ecuacion);

}

TDAecuacion* CargarEcuacionTxT(TDAecuacion* ecu, char* linea)
{
    char* Punt, *ecuacion;
    int largo, cantVar;
    Punt = strrchr(linea,'|');
    ecuacion = Punt+1;
    *Punt = '\0';
    Punt = strrchr(linea,'|');
    largo = atoi(Punt+1);
    *Punt = '\0';
    cantVar = atoi(linea);
    ecu = IniciarTDAecuacion(ecuacion,largo,cantVar);
    return ecu;
}
