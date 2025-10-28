#include "parser.h"

int EvaluarNum(char** Ecu)
{
    char* Fin;
    int val = strtol(*Ecu, &Fin, 10);
    *Ecu = Fin;
    return val;
}

int EvaluarFactor(char** Ecu, int X, int Y)
{
    int base;
    if(**Ecu == '(')
    {
        (*Ecu)=(*Ecu)+1;
        base = EvaluarTerm(Ecu, X, Y);
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
        return X;
    }

    else if(**Ecu == 'Y')
    {
        (*Ecu)=(*Ecu)+1;
        return Y;
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
        int exponente = EvaluarFactor(Ecu,X,Y);
        if(exponente>=0)
            base = pow(base,exponente);
        else return 0;
    }

    if(**Ecu == '#')
    {
        (*Ecu)=(*Ecu)+1;
        int raiz = EvaluarFactor(Ecu,X,Y);
        if(raiz>=0 && base >=0)
            base = pow(raiz,1/base);
        else return 0;
    }


    return base;
}

int EvaluarTerm(char** Ecu, int X, int Y)
{
    int val = EvaluarFactor(Ecu,X,Y);
    while(1)
    {
        if(**Ecu == '*')
        {
            (*Ecu)=(*Ecu)+1;
            val = val * EvaluarFactor(Ecu,X,Y);
        }
        else if(**Ecu == '/')
        {
            (*Ecu)=(*Ecu)+1;
            int d = EvaluarTerm(Ecu,X,Y);
            if(d == 0)
            {
                printf("Division por cero no permitida.\n");
                exit(-1);
            }
            val = val / d;
        }
        else
            break;
    }
    return val;
}

int EvaluarExpr(char** Ecu, int X, int Y)
{
    int val = EvaluarTerm(Ecu, X, Y);
    while(1)
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
            break;
    }
    return val;
}

int Evaluar(TDAecuacion* EstrucEcu)
{
    int X = 0, Y = 0;
    char* ecu;
    int Res;
    ecu = RetornarEcuacion(EstrucEcu);
    int i = RetornarCantVariables(EstrucEcu);
    if(i==0)
    {
        printf("\nLa ecuacion no tiene variables, procedemos a resolver");
    }
    else if(i==1)
    {
        printf("\nPor favor ingrese el valor para X: ");
        scanf("%d", &X);
        getchar();
    }
    else if(i==2)
    {
        printf("\nPor favor ingrese el valor para Y: ");
        scanf("%d", &Y);
        getchar();
    }
    else
    {
        printf("\nPor favor ingrese el valor para X: ");
        scanf("%d", &X);
        getchar();
        printf("\nPor favor ingrese el valor para Y: ");
        scanf("%d", &Y);
        getchar();
    }
    Res = EvaluarExpr(&ecu,X,Y);
    return Res;
}
