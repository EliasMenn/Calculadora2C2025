#include "parser.h"

double EvaluarNum(char** Ecu)
{
    char* Fin;
    double val = strtod(*Ecu, &Fin);
    *Ecu = Fin;
    return val;
}

double EvaluarFactor(char** Ecu, double X, double Y)
{
    double base;
    if(**Ecu == '(')
    {
        (*Ecu)=(*Ecu)+1;
        base = EvaluarExpr(Ecu, X, Y);
        if(**Ecu == ')')
        {
            (*Ecu)=(*Ecu)+1;
        }
    }
    else if(**Ecu == '+')
    {
        (*Ecu=(*Ecu)+1);
        return EvaluarFactor(Ecu,X,Y);
    }
    else if(**Ecu == '-')
    {
        (*Ecu=(*Ecu)+1);
        return -EvaluarFactor(Ecu,X,Y);
    }

    else if(**Ecu == 'X')
    {
        (*Ecu)=(*Ecu)+1;
        base = X;
    }

    else if(**Ecu == 'Y')
    {
        (*Ecu)=(*Ecu)+1;
        base = Y;
    }

    else if (isdigitP((unsigned char)**Ecu))
    {
        base = EvaluarNum(Ecu);
    }
    else
    {
        printf("Caracter no soportado %c\n.", **Ecu);
        exit(-1);
    }
    if(**Ecu == '@')
    {
        (*Ecu)=(*Ecu)+1;
        double exponente = EvaluarFactor(Ecu,X,Y);
        if(exponente>=0)
            base = pow(base,exponente);
        else
        {
            printf("Se ingreso una potencia negativa... Devolviendo 0.\n");
            return 0.0;
        }
    }

    if(**Ecu == '#')
    {
        (*Ecu)=(*Ecu)+1;
        double raiz = EvaluarFactor(Ecu,X,Y);
        if(raiz>=0 && base >=0)
            base = pow(base,1/raiz);
        else
        {
            printf("Se ingreso una raiz negativa... Devolviendo 0.\n");
            return 0.0;
        }
    }


    return base;
}

double EvaluarTerm(char** Ecu, double X, double Y)
{
    int i = 1;
    double val = EvaluarFactor(Ecu,X,Y);
    while(i == 1)
    {
        if(**Ecu == '*')
        {
            (*Ecu)=(*Ecu)+1;
            val = val * EvaluarFactor(Ecu,X,Y);
        }
        else if(**Ecu == '/')
        {
            (*Ecu)=(*Ecu)+1;
            double d = EvaluarTerm(Ecu,X,Y);
            if(d == 0)
            {
                printf("Division por cero no permitida.\n");
                exit(-1);
            }
            val = val / d;
        }
        else
            i = 0;
    }
    return val;
}

double EvaluarExpr(char** Ecu, double X, double Y)
{
    int i = 1;
    double val = EvaluarTerm(Ecu, X, Y);
    while(i == 1)
    {
        if(**Ecu == '+')
        {
            (*Ecu)=(*Ecu)+1;
            val = val + EvaluarTerm(Ecu,X,Y);
        }
        else if(**Ecu == '-')
        {
            (*Ecu)=(*Ecu)+1;
            val = val - EvaluarTerm(Ecu,X,Y);
        }
        else
            i =0;
    }
    return val;
}
void Evaluar(TDAecuacion* EstrucEcu)
{
    char Aux;
    int j;
    double X = 0, Y = 0, Xaux, Yaux;
    char* ecu, *ecuAux;
    double Res;
    ecu = RetornarEcuacion(EstrucEcu);
    ecuAux = ecu;
    int i = RetornarCantVariables(EstrucEcu);
    if(i==0)
    {
            printf("\nLa ecuacion no tiene variables, procedemos a resolver");
            Res =  EvaluarExpr(&ecu,X,Y);
            printf("El resultado es %.2lf", Res);
            free(ecu);
            return;
    }
    printf("Por favor ingrese el metodo de resolucion:\n"
           "1- Ingresar multiples valores.\n"
           "2- Ingresar un solo valor.\n");
    scanf("%d", &j);
    getchar();
    while(j<0 || j>2)
    {
        printf("Por favor ingrese un valor valido: ");
        scanf("%d", &j);
        getchar();
    }
    if (j == 1)
    {
        do
        {
            if(i==1)
            {
                printf("\nPor favor ingrese el valor para X: ");
                scanf("%lf", &X);
                getchar();
                Res = EvaluarExpr(&ecu,X,Y);
            }
            else if(i==2)
            {
                printf("\nPor favor ingrese el valor para Y: ");
                scanf("%lf", &Y);
                getchar();
                Res = EvaluarExpr(&ecu,X,Y);
            }
            else
            {
                printf("\nPor favor ingrese el valor para X: ");
                scanf("%lf", &X);
                getchar();
                printf("\nPor favor ingrese el valor para Y: ");
                scanf("%lf", &Y);
                getchar();
                Res = EvaluarExpr(&ecu,X,Y);
            }
            ecu = ecuAux;
            printf("El resultado fue de %.2lf, desea ingresar nuevos valores para X e Y? (Y para si, N para no)",Res);
            scanf("%c", &Aux);
            getchar();
            while(Aux != 'Y' && Aux != 'N')
            {
                printf("Ingreso no valido. ");
                scanf("%c", &Aux);
                getchar();
            }
        }while(Aux != 'N');
    }
    if (j == 2)
    {
        if(i==1)
        {
            printf("\nPor favor ingrese el valor para X: ");
            scanf("%lf", &X);
            getchar();
            for(Xaux = X-5; Xaux <= X+5; Xaux++)
            {
                Res = EvaluarExpr(&ecu,Xaux,Y);
                printf("X: %.2lf f(X): %.2lf\n", Xaux, Res);
                ecu = ecuAux;
            }
        }
        else if(i==2)
        {
            printf("\nPor favor ingrese el valor para Y: ");
            scanf("%lf", &Y);
            getchar();
            for(Yaux = Y-5; Yaux <= Y+5; Yaux++)
            {
                Res = EvaluarExpr(&ecu,X,Yaux);
                printf("Y: %.2lf f(Y): %.2lf\n", Yaux, Res);
                ecu = ecuAux;
            }
        }
        else
        {
            printf("\nPor favor ingrese el valor para X: ");
            scanf("%lf", &X);
            getchar();
            printf("\nPor favor ingrese el valor para Y: ");
            scanf("%lf", &Y);
            getchar();
            for(Xaux = X-5; Xaux <= X+5; Xaux++)
            {
                for(Yaux = Y-5;Yaux <= Y+5;Yaux++)
                {
                    Res = EvaluarExpr(&ecu,Xaux,Yaux);
                    printf("(X,Y): (%.2lf, %.2lf) f(X,Y): %.2lf\n", Xaux, Yaux, Res);
                    ecu = ecuAux;
                }
            }
        }
    }
    free(ecu);
}
