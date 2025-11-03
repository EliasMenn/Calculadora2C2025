#include "Menu.h"

void MenuPrincipal(TDAvector* vec)
{
    char opcion;
    char* permitidos = "A,B,C,D,E,F,G,H,X";
    do
    {
        printf("Bienvenido: \n"
                "[A] - Escribir Ecuacion\n"
                "[B] - Ver Ecuaciones De Esta Sesion\n"
                "[C] - Guardar Y Reiniciar Sesion\n"
                "[D] - Leer Ecuaciones Guardadas\n"
                "[E] - Borrar Ecuaciones Guardadas\n"
                "[F] - Resolver Ecuacion\n"
                "[G] - Graficar Ecuacion\n"
                "[H] - Ayuda\n"
                "[X] - Salir\n"
                "Por favor ingrese una opcion: ");
        scanf("%c",&opcion);
        getchar();
        while(!strchr(permitidos,opcion))
        {
            printf("\nPor favor, ingrese una opcion valida: ");
            scanf("%c",&opcion);
            getchar();
        }
        switch(opcion)
        {
        case 'A':
            OpcionA(vec);
            break;
        case 'B':
            OpcionB(vec);
            break;
        case 'C':
            OpcionC(vec);
            break;
        case 'D':
            OpcionD(vec);
            break;
        case 'E':
            OpcionE();
            break;
        case 'F':
            OpcionF(vec);
            break;
        case 'G':
            OpcionG(vec);
            break;
        case 'H':
            OpcionH();
            break;
        }
    }while(opcion!='X');
    OpcionX(vec);
}

void OpcionA(TDAvector* vec)
{
    CargarEcuMem(vec);
    printf("\nPresione cualquier tecla para continuar\n");
    getchar();
}

void OpcionB(TDAvector* vec)
{
    MostrarEcuaciones(vec);
    printf("\nPresione cualquier tecla para continuar\n");
    getchar();
}

void OpcionC(TDAvector* vec)
{
    CargarArchivo(vec);
    printf("\nPresione cualquier tecla para continuar\n");
    getchar();
}

void OpcionD(TDAvector* vec)
{
    DescargarArchivos(vec);
    printf("\nPresione cualquier tecla para continuar\n");
    getchar();
}

void OpcionE()
{
    FILE* indice;
    indice = fopen("ArchivosGuardados/indice.bin","rb");
    if(!indice)
    {
        printf("Ocurrio un error");
        getchar();
        exit(-1);
    }
    LimpiarArchivos(indice);
    printf("\nPresione cualquier tecla para continuar\n");
    getchar();
}

void OpcionF(TDAvector* vec)
{
    int i;
    printf("Ingrese la accion deseada 1-resolver, 2-buscar raices: ");
    scanf("%d", &i);
    getchar();
    if(i!=1 && i!=2)
    {
        printf("Ingrese una opcion valida: ");
        scanf("%d", &i);
        getchar();
    }
    else if (i == 1)
    {
        SeleccionarEcu(vec);
    }
    else if (i == 2)
    {
        BuscarRaices(vec);
    }
    printf("\nPresione cualquier tecla para continuar\n");
    getchar();
}

void OpcionG(TDAvector* vec)
{
    ElegirYGraficar(vec);
    printf("\nPresione cualquier tecla para continuar\n");
    getchar();
}

void OpcionH()
{
    printf("-Ayuda-\n"
           "1- Los simbolos asignados para las potencias y raices son @ y # respectivamente.\n"
           "2- Si se fuera a ingresar un valor negativo para una potencia o raiz, el parser \ndevolvera ese termino como 0.00 tras dar un aviso al usuario\n"
           "3- Si se ingresase un 0 tras un simbolo de division (/) durante la resolucion (ya que al momento de escribir la ecuacion no esta permitido) se le avisara "
           "al usuario y se cerrara el programa.\n"
           "4- Al guardar un archivo, si tiene un nombre que ya se encuentre en nuestro indice el archivo previo sera sobreescrito.");
            printf("\nPresione cualquier tecla para continuar\n");
            getchar();
}
void OpcionX(TDAvector* vec)
{
    LimpiarMemoria(vec);
}
