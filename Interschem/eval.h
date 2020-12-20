#pragma once
#include <math.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>
#define infinit INT_MAX
#define epsi 0.0001
#define  MAX 100
#define MAX1 20
#include <stdio.h>

int top1, top2; // varfurile celor doua stive
const int max_stiva = 100;

double Opd[max_stiva]; // stiva operanzilor
char Op[max_stiva]; // stiva operatorilor

char OperatiiBinare[200] = "+-*/^<>=#";
char OperatiiUnare[200] = "scarel";
char Operatii[200] = "+-*/^<>=#scarel";

int Prioritate(char c)  // prioritate operatorilor
{
    if (c == '(' || c == ')')
        return 0;
    if (c == '+' || c == '-')
        return 1;
    if (c == '*' || c == '/')
        return 2;
    if (c == '^')
        return 3;
    if (c == '=' || c == '#' || c == '<' || c == '>')
        return 4;
    if (c == 'c' || c == 's' || c == 'l' || c == 'e' || c == 't' || c == 'a' || c == 'r')
        return 5;
}

const float pi = 3.1415926; // se da sub forma literei q

bool DifInf(float x)
{
    return fabs(infinit - fabs(x)) > infinit / 2.0;
}

float Logaritm(float x)
{
    if (x > epsi && DifInf(x))
        return log(x);
    else
        return infinit;
}

float Exponential(float x)
{
    if (DifInf(x)) return exp(x);
    else return infinit;
}

float Inmultit(float x, float y)
{
    if (fabs(x < epsi) || fabs(y) < epsi) return 0;
    else if (DifInf(x) && DifInf(y)) return x * y;
    else return infinit;
}

float Putere(float x, float y)
{
    // float p;
    if (x == 0) return 0;
    else if (y == 0) return 1;
    else if (x == infinit || y == infinit) return infinit;
    else
        return pow(x, y);
}

float Egal(float x, float y)
{
    return x == y;
}

float Diferit(float x, float y)
{
    return x != y;
}

float MaiMic(float x, float y)
{
    return x < y;
}

bool MaiMare(float x, float y)
{
    return x > y;
}

float Plus(float x, float y)
{
    if (DifInf(x) && DifInf(y))  return x + y;
    else return infinit;
}

float Minus(float x, float y)
{
    if (DifInf(x) && DifInf(y))  return x - y;
    else return infinit;
}

float Impartit(float x, float y)
{
    if (fabs(y) > epsi) return x / y;
    else return infinit;
}

float Sinus(float x)
{
    if (DifInf(x))  return sin(x);
    else return infinit;
}

float Cosinus(float x)
{
    if (DifInf(x))  return cos(x);
    else return infinit;
}

float Modul(float x)
{
    if (DifInf(x)) return fabs(x);
    else return infinit;
}

float Radical(float x)
{
    if (DifInf(x) && (x > epsi)) return sqrt(x);
    else return infinit;
}

bool EsteNumar(char sir[MAX1])
{
    return (atof(sir) != 0.0 &&
        strchr("0123456789", sir[0]));
}

struct functie
{
    char expresie[300];
    char vect[MAX + 1][MAX1];
    // vectorul cuprinzand “cuvintele”ce formeaza expresia}
    int lung; // lungimea efectiva a vectorului
    float a, b; // intervalul de evaluare a functiei
    int n; //numarul de puncte de evaluare
};

void depanare()
{
    printf("Stiva operanzilor: ");
    for (int i = 1; i <= top1; i++)
        printf("%f,", Opd[i]);
    printf("\nStiva operatorilor: ");
    for (int i = 1; i <= top2; i++)
        printf("%c,", Op[i]);
    printf("\n");
}

double ValoareFunctie(functie E, double x)
{
    int i;
    // returneaza valoarea functiei E in punctul x
    double valo, x_1, x_2;
    //calculul expresiei
    for (i = 1; i <= max_stiva; i++)
    {
        Opd[i] = 0;
        Op[i] = '@';
    }
    top1 = 0;
    top2 = 1;
    Op[top2] = '(';
    i = 0;
    while (i <= E.lung && top2 > 0)
    {
        i++;
        if (EsteNumar(E.vect[i]))
        {
            // printf("\nE.vect[%d]=%s\n",i,E.vect[i]);
            top1++;
            valo = atof(E.vect[i]);
            Opd[top1] = valo;
            // depanare();
        }
        else
            switch (E.vect[i][0]) {
                /* constanta pi=3.1415926 se da sub forma literei q */
            case 'q': top1++; Opd[top1] = pi; break;
            case 'X': /* variabila x */ top1++; Opd[top1] = x;
                /* printf("\n-->x=%f\n",x); */ break;
            case '(': /* inceput de bloc */ top2++; Op[top2] = '('; break;
            default:
                /* operatii binare si unare */
                while ((top2 > 0) && !(strchr("()", Op[top2])) &&
                    Prioritate(Op[top2]) >= Prioritate(E.vect[i][0]))
                {
                    if (top1 > 1) x_1 = Opd[top1 - 1];
                    x_2 = Opd[top1];
                    // depanare();
                    /* functii scrise in OPERATII */
                    switch (Op[top2]) {
                    case '=': valo = Egal(x_1, x_2); break;
                    case '#': valo = Diferit(x_1, x_2); break;
                    case '<': valo = MaiMic(x_1, x_2); break;
                    case '>': valo = MaiMare(x_1, x_2); break;
                    case '+': valo = Plus(x_1, x_2); break;
                    case '-': valo = Minus(x_1, x_2); break;
                    case '*': valo = Inmultit(x_1, x_2); break;
                    case '/': valo = Impartit(x_1, x_2); break;
                    case '^': valo = Putere(x_1, x_2); break;
                    case 's': valo = Sinus(x_2); break;
                    case 'c': valo = Cosinus(x_2); break;
                    case 'l': valo = Logaritm(x_2); break;
                    case 'e': valo = Exponential(x_2); break;
                    case 'a': valo = Modul(x_2); break;
                    case 'r': valo = Radical(x_2); break;
                    } //operator[top2]
                    if (strchr(OperatiiBinare, Op[top2])) top1--;
                    if (strchr(Operatii, Op[top2])) Opd[top1] = valo;
                    top2--;
                }
                // depanare();
                if (top2 > 0)
                    if ((Op[top2] != '(') || (strcmp(E.vect[i], ")")))
                    {
                        top2++; Op[top2] = E.vect[i][0];
                    }
                    else top2--;
            }
    }
    if (top2 == 0) return Opd[1];
    else return infinit;
}

void parseExpresion(std::string expression, functie &Functie) {
    strcpy(Functie.expresie, expression.c_str());
    strcat(Functie.expresie, ")");
    int len = strlen(Functie.expresie);

    strcpy(Functie.vect[0], "("); //!!!
    for (int i = 1; i <= len; i++) {
        strcpy(Functie.vect[i], expression.substr(i - 1, 1).c_str());
    }
    strcpy(Functie.vect[len], ")"); //!!!
    Functie.lung = len;

    //std::cout << "Expresie: " << Functie.expresie<<std::endl;
    //std::cout << "Lungime: "<< Functie.lung << std::endl;
    //std::cout << "Vector: ";
    //for (int i = 0; i <= Functie.lung; i++)std::cout << Functie.vect[i];
    //std::cout << std::endl;
}

double valoare(std::string expression, double x) {
    functie F;
    parseExpresion(expression, F);
    return ValoareFunctie(F, x);
}
