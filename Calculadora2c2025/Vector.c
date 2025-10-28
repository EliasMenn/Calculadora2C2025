#include "vector.h"

TDAvector* CrearVector(size_t tamElem, int cantElem)
{
    TDAvector* vec;
    vec = malloc(sizeof(TDAvector));
    if(vec == NULL)
    {
        exit(-1);
    }
    vec->datos = malloc(tamElem*cantElem);
    if(vec->datos == NULL)
    {
        free(vec);
        exit(-1);
    }
    vec->capacidad = cantElem;
    vec->CE = 0;
    vec->tamElem = tamElem;
    return vec;
}

int AgregarElement(TDAvector* vec, void* elem)
{
    if(vec->CE < vec->capacidad)
    {
        void* destino = (char*)vec->datos + vec->CE * vec->tamElem;
        memcpy(destino, elem, vec->tamElem);
        vec->CE++;
        return 0;
    }
    return -1;
}

int QuitarElement(TDAvector* vec, int numElem)
{
    if(vec->CE == 0 || numElem < 0 || numElem >= vec->CE) {
        printf("Hubo un error al quitar el elemento\n");
        return -1;
    }

    for(int i = numElem; i < vec->CE - 1; i++) {
        void* dest = (char*)vec->datos + i * vec->tamElem;
        void* src  = (char*)vec->datos + (i + 1) * vec->tamElem;
        memcpy(dest, src, vec->tamElem);
    }

    vec->CE--;
    return 0;
}

 void RecorrerVector(TDAvector* vec, void accion(void* element))
 {
     int i = 0;
     void* aux;
     while(i<vec->CE)
     {
         aux = (char*)vec->datos + (i*vec->tamElem);
         accion(aux);
         i++;
     }
 }

 void* DestruirVector(TDAvector* vec)
 {
     free(vec->datos);
     free(vec);
     vec = NULL;
     return vec;
 }

 void* DevolverElementoVec(TDAvector* vec, int numElem)
 {
    void* ret = malloc(vec->tamElem);
    if(!ret)
    {
        exit(-1);
    }
    void* aux = (char*)vec->datos+(numElem*vec->tamElem);
    memcpy(ret,aux,vec->tamElem);
    return ret;
 }

 int DevolverCantElem(TDAvector* vec)
 {
     return vec->CE;
 }



