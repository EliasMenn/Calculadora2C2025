#include "Archivos.h"
void CrearIndice()
{
    FILE* fp;
    fp = fopen("ArchivosGuardados/indice.bin","ab");
    if(fp == NULL)
    {
        printf("Hubo un error al crear el indice");
        exit(-1);
    }
    fclose(fp);
}

int ContarCantArchivos(FILE* indice)
{
    fseek(indice,0,SEEK_SET);
    int i = 0;
    char NombreArch[MAX_LARGO_NOMBRE];
    while(fread(NombreArch,sizeof(char),MAX_LARGO_NOMBRE,indice))
    {
        i++;
    }
    fseek(indice,0,SEEK_SET);
    return i;
}

void AgregarArchivo(FILE* indice, char* NuevoArchivo)
{
    fseek(indice,0,SEEK_END);
    char buffer[MAX_LARGO_NOMBRE]= {'\0'};
    strncpy(buffer, NuevoArchivo, MAX_LARGO_NOMBRE-1);
    fwrite(buffer,sizeof(char),MAX_LARGO_NOMBRE, indice);
}

FILE* CrearArchivo(FILE* pf, FILE* indice)
{
    char nombreArchivo[MAX_LARGO_NOMBRE];
    char nombreCompleto[200];
    printf("\nIngrese el nombre de archivo a crear: ");
    if(fgets(nombreArchivo,sizeof(nombreArchivo),stdin)!=NULL)
    {
        size_t largo = strlen(nombreArchivo);
        if(largo > 0 && *(nombreArchivo+largo-1) == '\n')
        {
            *(nombreArchivo+largo-1) = '\0';
        }
    }
    while(*nombreArchivo == '\0')
    {
        printf("Nombre invalido, ingrese uno valido por favor: \n");
        printf("Ingrese el nombre de archivo a crear: ");
        if(fgets(nombreArchivo,sizeof(nombreArchivo),stdin)!=NULL)
        {
            size_t largo = strlen(nombreArchivo);
            if(largo > 0 && *(nombreArchivo+largo-1) == '\n')
            {
                *(nombreArchivo+largo-1) = '\0';
            }
        }
    }
    snprintf(nombreCompleto,sizeof(nombreCompleto),"%s%s.txt",carpeta,nombreArchivo);
    pf = fopen(nombreCompleto,"w");
    if(!pf)
    {
        printf("Hubo un error al crear el archivo.");
        getchar();
        fclose(indice);
        exit(-1);
    }
    if(buscarArchivo(indice,nombreArchivo)==0)
    {
        AgregarArchivo(indice,nombreArchivo);
    }
    return pf;
}

int buscarArchivo(FILE* indice, char* archivo)
{
    fseek(indice,0,SEEK_SET);
    char buffer[MAX_LARGO_NOMBRE];
    buffer[MAX_LARGO_NOMBRE-1]='\0';

    while(fread(buffer,sizeof(char),MAX_LARGO_NOMBRE,indice) == MAX_LARGO_NOMBRE)
    {
        if(strcmp(buffer,archivo) == 0)
        {
            return 1;
        }
    }
    fseek(indice,0,SEEK_SET);
    return 0;
}

void MostrarIndices(FILE* indice)
{
    int i = 1;
    char buffer[MAX_LARGO_NOMBRE];
    fseek(indice,0,SEEK_SET);
    while(fread(buffer,sizeof(char),MAX_LARGO_NOMBRE,indice))
    {
        printf("%d - %s\n", i, buffer);
        i++;
    }
    fseek(indice,0,SEEK_SET);
}


void LimpiarArchivos(FILE* indice)
{
    char buffer[MAX_LARGO_NOMBRE];
    char nombreCompleto[100];
    while(fread(buffer,sizeof(char),MAX_LARGO_NOMBRE,indice))
    {
        snprintf(nombreCompleto,sizeof(nombreCompleto),"%s%s.txt",carpeta,buffer);
        if(remove(nombreCompleto)==0)
        {
            printf("Archivo %s borrado exitosamente\n", buffer);
        }
        else
        {
            printf("Error al eliminar el archivo");
        }
    }

    freopen("ArchivosGuardados/indice.bin","wb",indice);
    fclose(indice);

}
