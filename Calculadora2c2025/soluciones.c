#include "soluciones.h"

int IngresarEcuacion(TDAecuacion** StrucEcuacion)
{
    printf("Ingrese la ecuacion que desee escribir: ");
    int total, cantVar,i;
    char buffer[MAX];
    fgets(buffer,sizeof(buffer),stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    total = VerificarEcuaciones(buffer,&cantVar);
    if(total != TODO_OK)
    {
        printf("\nSyntax Error");
        return CARACTER_INVALIDO;
    }
    printf("Desea editar la ecuacion %s? (1 = si, 0 = no)\n", buffer);
    scanf("%d", &i);
    getchar();
    while(i==1)
    {
        modificarString(buffer);
        total = VerificarEcuaciones(buffer,&cantVar);
        if(total != TODO_OK)
        {
            printf("\nSyntax Error");
            return CARACTER_INVALIDO;
        }
        printf("Desea editar la ecuacion %s? (1 = si, 0 = no)\n", buffer);
        scanf("%d", &i);
        getchar();
    }
    *StrucEcuacion = IniciarTDAecuacion(buffer,strlen(buffer)+1,cantVar);
    if(StrucEcuacion==NULL)
    {
        printf("Hubo un error al guardar la ecuacion");
    }

    return 0;
}

void modificarString(char* buffer)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* win = SDL_CreateWindow("Editor",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        400, 10, 0);

    SDL_RaiseWindow(win);

    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    SDL_StartTextInput();

    int editando = 1;
    int cursor = strlen(buffer);

    while (editando) {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                editando = 0;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                SDL_Keycode key = e.key.keysym.sym;
                if (key == SDLK_ESCAPE)
                {
                    editando = 0;
                }
                else if (key == SDLK_RETURN || key == SDLK_KP_ENTER)
                {
                  editando = 0;
                }
                else if (key == SDLK_BACKSPACE)
                {
                    if (cursor > 0)
                    {
                        memmove(buffer + cursor - 1, buffer + cursor, strlen(buffer) - cursor + 1);
                        cursor--;
                    }
                }
                else if (key == SDLK_LEFT)
                {
                    if (cursor > 0) cursor--;
                }
                else if (key == SDLK_RIGHT)
                {
                    if (cursor < (int)strlen(buffer)) cursor++;
                }
            }
            else if (e.type == SDL_TEXTINPUT)
            {
                const char* txt = e.text.text;
                if (strlen(buffer) + strlen(txt) < MAX)
                {
                    memmove(buffer + cursor + strlen(txt), buffer + cursor, strlen(buffer) - cursor + 1);
                    memcpy(buffer + cursor, txt, strlen(txt));
                    cursor += strlen(txt);
                }
            }
        }

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        SDL_SetWindowTitle(win, buffer);
        SDL_RenderPresent(ren);
    }

    SDL_StopTextInput();
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
int VerificarEcuaciones(char* buffer, int* cantVar)
{
    const char* allowedChars = "+-*/@#.";
    int total = 0, i = 0, flagX = 0, flagY = 0;
    char c, next, prev ='(';
    while(*(buffer+i)!='\0' && total>=0)
    {
        c = *(buffer+i);
        next = *(buffer+i+1);
        if(c == 'x' || c == 'X')
        {
            flagX = 1;
            if((!strchr(allowedChars,prev) && prev!='(') || prev == '.')
            {
                return CARACTER_INVALIDO;
            }
            if((!strchr(allowedChars,next) && next!=')') || next == '.')
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
            if((!strchr(allowedChars,prev) && prev!='(') || prev == '.')
            {
                return CARACTER_INVALIDO;
            }
            if((!strchr(allowedChars,next) && next!=')') || next == '.')
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
        void* ecu = NULL;
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
    VaciarMemoria(vec);
    TDAecuacion* ecu = NULL;
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
    if(DevolverCantElem(vec) == 0)
    {
        printf("No hay ninguna ecuacion para solucionar.\n");
        return;
    }
    printf("Por favor seleccione una ecuacion para resolver: \n");
    MostrarEcuaciones(vec);
    scanf("%d", &i);
    getchar();
    while(i<0 || i>DevolverCantElem(vec))
    {
        printf("Por favor ingrese un valor valido: ");
        scanf("%d", &i);
        getchar();
    }
    TDAecuacion* ecu = DevolverElementoVec(vec,i-1);
    Evaluar(ecu);
    LiberarTDAecuacion(ecu);
}

void BuscarRaices(TDAvector* vec)
{
    int i,j=20, flag = 0;
    double raizPrev;
    printf("Por favor seleccione una ecuacion para buscar las raices: \n");
    MostrarEcuaciones(vec);
    scanf("%d", &i);
    getchar();
    while(i<0 || i>DevolverCantElem(vec))
    {
        printf("Por favor ingrese un valor valido: ");
        scanf("%d", &i);
        getchar();
    }
    TDAecuacion* ecu = DevolverElementoVec(vec,i-1);
    char* ecuacion = RetornarEcuacion(ecu);
    char* ecuacionAux = ecuacion;
    if(RetornarCantVariables(ecu) == 3)
    {
        printf("La busqueda de raices para una funcion de 2 variables no esta soportada. \n");
    }
    else if(RetornarCantVariables(ecu) == 3)
    {
        printf("No se pueden buscar raices para una funcion sin variables. \n");
    }
    else
    {
        for(double PuntoInicial = -50; PuntoInicial<=50; PuntoInicial+=5)
        {
            double raiz = CalcularRaiz(PuntoInicial,ecuacion,ecuacionAux,j);
            if(!isnan(raiz) && !comparar2decimales(raiz,raizPrev))
            {
                flag = 1;
                printf("La raiz es %.2lf\n", raiz);
                raizPrev = raiz;
            }
        }
    }
    if(flag == 0)
    {
      printf("En el intervalo de evaluacion la funcion no tiene raices\n");
    }
    LiberarTDAecuacion(ecu);
}

double CalcularRaiz(double PuntoInicial,char* Ecu, char* EcuAux, int cont)
{
    if(cont == 0)
    {
        return NAN;
    }
    cont--;
    double Xh, X;
    double Derivada, Res;
    X = EvaluarExpr(&Ecu,PuntoInicial,PuntoInicial);
    Ecu = EcuAux;
    if(X>=-0.01 && X<=0.01)
    {
        return PuntoInicial;
    }
    Xh = EvaluarExpr(&Ecu,PuntoInicial+0.001,PuntoInicial+0.001);
    Ecu = EcuAux;
    Derivada = (Xh-X)/0.001;
    Res = PuntoInicial - (X/Derivada);
    return CalcularRaiz(Res,Ecu,EcuAux, cont);
}

void MostrarGrafico(double* xs, double* ys, int largo)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL no se puede inicializar! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Grafico",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        printf("No se pudo crear la ventana! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    int margenIzq = 50;
    int ancho = 700, alto = 500;
    int x0 = margenIzq, y0 = 550;


    // Buscar máximos y mínimos
    double minX = *xs, maxX = *xs;
    double minY = *ys, maxY = *ys;
    for (double* px = xs, *py = ys; px < xs + largo; px++, py++) {
        if (*px < minX) minX = *px;
        if (*px > maxX) maxX = *px;
        if (*py < minY) minY = *py;
        if (*py > maxY) maxY = *py;
    }

    // Normalización segura
    double rangoX = (maxX - minX == 0) ? 1 : (maxX - minX);
    double rangoY = (maxY - minY == 0) ? 1 : (maxY - minY);

    // Calculamos donde está el eje Y y el eje X (si entran en el rango)
    int ejeYx = (0 >= minX && 0 <= maxX)
        ? x0 + (int)((0 - minX) / rangoX * ancho)
        : x0; // Si 0 no está en rango, lo dejamos al borde

    int ejeYy = (0 >= minY && 0 <= maxY)
        ? y0 - (int)((0 - minY) / rangoY * alto)
        : y0; // idem para eje X

    // Dibujar ejes
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, x0, ejeYy, x0 + ancho, ejeYy); // Eje X
    SDL_RenderDrawLine(renderer, ejeYx, y0, ejeYx, y0 - alto);  // Eje Y

    // Dibujar marcas
    int numXTicks = 10, numYTicks = 10;
    for (int i = 0; i <= numXTicks; i++) {
        int x = x0 + i * (ancho / numXTicks);
        SDL_RenderDrawLine(renderer, x, ejeYy - 5, x, ejeYy + 5);
    }
    for (int i = 0; i <= numYTicks; i++) {
        int y = y0 - i * (alto / numYTicks);
        SDL_RenderDrawLine(renderer, ejeYx - 5, y, ejeYx + 5, y);
    }

    // Graficar
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (double *pX1 = xs, *pY1 = ys, *pX2 = xs + 1, *pY2 = ys + 1;
         pX2 < xs + largo; pX1++, pY1++, pX2++, pY2++) {

        int x1 = x0 + (int)((*pX1 - minX) / rangoX * ancho);
        int y1 = y0 - (int)((*pY1 - minY) / rangoY * alto);
        int x2 = x0 + (int)((*pX2 - minX) / rangoX * ancho);
        int y2 = y0 - (int)((*pY2 - minY) / rangoY * alto);

        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    }

    SDL_RenderPresent(renderer);

    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = 1;
        }
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void ElegirYGraficar(TDAvector* vec)
{
    if(DevolverCantElem(vec) == 0)
    {
        printf("No hay ninguna ecuacion para graficar.\n");
        return;
    }
    int i;
    double valoresX[50], valoresY[50];
    printf("Por favor seleccione una ecuacion para graficar: \n");
    MostrarEcuaciones(vec);
    scanf("%d", &i);
    getchar();
    while(i<0 || i>DevolverCantElem(vec))
    {
        printf("Por favor ingrese un valor valido: ");
        scanf("%d", &i);
        getchar();
    }
    TDAecuacion* ecu = DevolverElementoVec(vec,i-1);
    if(RetornarCantVariables(ecu)!=1)
    {
        printf("Solo se permiten ecuaciones con variable en X para graficar.\n");
        LiberarTDAecuacion(ecu);
        return;
    }
    char* ecuacion = RetornarEcuacion(ecu);
    char* ecuacionAux = ecuacion;
    for(int j = 0; j<50; j++)
    {
        *(valoresX+j) = j-15;
        *(valoresY+j) = EvaluarExpr(&ecuacion,j-15,j-15);
        ecuacion = ecuacionAux;
    }
    MostrarGrafico(valoresX, valoresY, 50);
    LiberarTDAecuacion(ecu);
}

int comparar2decimales(double a, double b)
{
    return round(a * 100) - round(b * 100);
}

