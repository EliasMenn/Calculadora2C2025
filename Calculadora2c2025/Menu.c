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
            break;
        case 'H':
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
    SeleccionarEcu(vec);
    printf("\nPresione cualquier tecla para continuar\n");
    getchar();
}
void OpcionX(TDAvector* vec)
{
    LimpiarMemoria(vec);
}
