#include "soluciones.h"

int IngresarEcuacion(TDAecuacion** StrucEcuacion)
{
    printf("Ingrese la ecuacion que desee escribir: ");
    int total, cantVar;
    char buffer[MAX];
    fgets(buffer,sizeof(buffer),stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    total = VerificarEcuaciones(buffer,&cantVar);
    if(total != TODO_OK)
    {
        printf("\nSyntax Error");
        return CARACTER_INVALIDO;
    }
    *StrucEcuacion = IniciarTDAecuacion(buffer,strlen(buffer)+1,cantVar);
    if(StrucEcuacion==NULL)
    {
        printf("Hubo un error al guardar la ecuacion");
    }

    return 0;
}

int VerificarEcuaciones(char* buffer, int* cantVar)
{
    const char* allowedChars = "+-*/@#";
    int total = 0, i = 0, flagX = 0, flagY = 0;
    char c, next, prev ='(';
    while(*(buffer+i)!='\0' && total>=0)
    {
        c = *(buffer+i);
        next = *(buffer+i+1);
        if(c == 'x' || c == 'X')
        {
            flagX = 1;
            if(!strchr(allowedChars,prev) && prev!='(')
            {
                return CARACTER_INVALIDO;
            }
            if(!strchr(allowedChars,next) && next!=')')
            {
                return CARACTER_INVALIDO;
            }
            if(c=='x')
            {
                *(buffer+i)='X';
            }
        }
        else if(c == 'y' || c == 'Y')
        {
            flagY = 2;
            if(!strchr(allowedChars,prev) && prev!='(')
            {
                return CARACTER_INVALIDO;
            }
            if(!strchr(allowedChars,next) && next!=')')
            {
                return CARACTER_INVALIDO;
            }
            if(c=='y')
            {
                *(buffer+i)='Y';
            }
        }
        else if(strchr(allowedChars,c))
        {
            if(strchr(allowedChars,prev))
            {
                return CARACTER_INVALIDO;
            }
            if(strchr(allowedChars,next))
            {
                return CARACTER_INVALIDO;
            }
            if(c == '/' && next == '0')
            {
                return CARACTER_INVALIDO;
            }

        }
        else if(c=='(')
        {
            total++;
        }
        else if(c==')')
        {
            total--;
        }
        else if(!isdigit(c) && !strchr(allowedChars,c))
        {
            printf("Se ingreso un caracter no valido");
            return CARACTER_INVALIDO;
        }
        prev = c;
        i++;
    }
    *cantVar = flagX+flagY;
    if(total==0)
        return TODO_OK;
    return ERROR_PARENTESIS;
}

int CargarEcuMem (TDAvector* vec)
{
    TDAecuacion* ecu;
    int i = IngresarEcuacion(&ecu);
    if(ecu==NULL)
    {
        LimpiarMemoria(vec);
        exit(-1);
    }
    else if(i != CARACTER_INVALIDO)
    {
        int j = AgregarElement(vec,(void*)ecu);
        if(j != 0)
        {
            printf("Fallo al asignar la ecuacion en memoria, Por favor elija una de las siguientes para sobreescribir: \n");
            MostrarEcuaciones(vec);
            printf("11- Descartar Ecuacion Actual\n");
            printf("Ingrese una opcion: ");
            ReemplazarEcuacion(vec, ecu);
        }
        else
        {
            LiberarTDAecuacion(ecu);
        }
        return 0;
    }
    return -1;
}

void VaciarMemoria(TDAvector* vec)
{
    if(vec==NULL)
    {
        exit(0);
    }
    LimpiarMemoria(vec);
    DestruirVector(vec);
}

void LimpiarMemoria(TDAvector* vec)
{
    void* ecu;
    if(vec==NULL)
    {
        exit(0);
    }
    int i = DevolverCantElem(vec)-1;
    while(i>=0)
    {
        ecu = DevolverElementoVec(vec,i);
        LimpiarTDAecuacion(ecu);
        QuitarElement(vec, i);
        i = DevolverCantElem(vec)-1;
    }
}
void MostrarEcuaciones(TDAvector* vec)
{
    TDAecuacion* ecu;
    int i = 0;
    int j = DevolverCantElem(vec);
    while(i<j)
    {
        ecu = DevolverElementoVec(vec,i);
        printf("%d - ",i+1);
        MostrarEcuacion(ecu);
        i++;
    }
}

void ReemplazarEcuacion(TDAvector* vec, TDAecuacion* ecu)
{
    int numEcu;
    scanf("%d", &numEcu);
    getchar();
    while(numEcu<=0 || numEcu>12)
    {
        printf("Por favor ingrese un valor de ecuacion valido: ");
        scanf("%d", &numEcu);
        getchar();
    }
    if(numEcu == 11)
    {
        LimpiarTDAecuacion(ecu);
    }
    QuitarElement(vec, numEcu-1);
    AgregarElement(vec,(void*)ecu);
}

void CargarArchivo(TDAvector* vec)
{
    FILE* indice = fopen("ArchivosGuardados/indice.bin","r+b");
    if(!indice)
    {
        printf("Hubo un error");
        getchar();
        exit(-1);
    }
    FILE* archivo = NULL;
    if(ContarCantArchivos(indice)<10)
    {
        archivo = CrearArchivo(archivo, indice);
        int i = DevolverCantElem(vec)-1;
        void* ecu;
        while(i>=0)
        {
            ecu = DevolverElementoVec(vec,i);
            MostrarEcuacion(ecu);
            GuardarEcuacionTxT(ecu,archivo);
            QuitarElement(vec, i);
            i = DevolverCantElem(vec)-1;
        }
        LimpiarTDAecuacion(ecu);
        fclose(archivo);
        fclose(indice);
        }
}

void DescargarArchivos(TDAvector* vec)
{
    char linea[256];
    char nombreCompleto[100];
    char buffer[MAX_LARGO_NOMBRE];
    FILE* indice = fopen("ArchivosGuardados/indice.bin","r+b");
    if(!indice)
    {
        printf("Hubo un error");
        getchar();
        exit(-1);
    }

    if(ContarCantArchivos(indice) == 0)
    {
        printf("No hay archivos cargados");
        return;
    }

    MostrarIndices(indice);

    printf("\nIngrese el archivo que desea cargar: ");
    if(fgets(buffer,sizeof(buffer),stdin)!=NULL)
    {
        size_t largo = strlen(buffer);
        if(largo > 0 && *(buffer+largo-1) == '\n')
        {
            *(buffer+largo-1) = '\0';
        }
    }

    while(*buffer == '\0' || buscarArchivo(indice,buffer) == 0)
        {
            printf("Ingrese el nombre de archivo a abrir: ");
            if(fgets(buffer,sizeof(buffer),stdin)!=NULL)
            {
                size_t largo = strlen(buffer);
                if(largo > 0 && *(buffer+largo-1) == '\n')
                {
                    *(buffer+largo-1) = '\0';
                }
            }
        }
    snprintf(nombreCompleto,sizeof(nombreCompleto),"%s%s.txt",carpeta,buffer);

    FILE* fp = fopen(nombreCompleto,"r");
    if(!fp)
    {
        fclose(indice);
        printf("Hubo un error");
        getchar();
        exit(-1);
    }
    LimpiarMemoria(vec);
    TDAecuacion* ecu;
    while(fgets(linea,sizeof(linea),fp))
    {
        size_t largo = strlen(linea);
        if(largo > 0 && linea[largo-1] == '\n') linea[largo-1] = '\0';
        ecu = CargarEcuacionTxT(ecu, linea);
        MostrarEcuacion(ecu);
        AgregarElement(vec,ecu);
    }
    fclose(indice);
    fclose(fp);
}

void SeleccionarEcu(TDAvector* vec)
{
    int i;
    printf("Por favor seleccione una ecuacion para resolver: ");
    MostrarEcuaciones(vec);
    scanf("%d", &i);
    getchar();
    while(i<0 || i>10)
    {
        printf("Por favor ingrese un valor valido: ");
        scanf("%d", &i);
        getchar();
    }
    TDAecuacion* ecu = DevolverElementoVec(vec,i-1);
    int res = Evaluar(ecu);
    printf("El resultado la ecuacion es: %d", res);
    LimpiarTDAecuacion(ecu);
}
