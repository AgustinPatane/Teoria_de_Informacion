#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ESCENARIO_1 32
#define ESCENARIO_2 128
#define ESCENARIO_3 512

void lectura(int vec[], int *tot, int n);
int binario_a_entero(char *cad);
void calcula_prob(float prob[],int vec[],int n,int tot);
void calcula_cant_info(float prob[],float info[], int n);
float cant_info(float info[], int n);
float entropia(float info[],float prob[],int n);
float sumatoria_columna(float prob_cond[][4], int col);
void matriz_prob_cond(float prob_cond[][4]);
void muestraMat(float prob[][4]);
void cant_info_simbolo(float info[], int n, int codigo);

int inecuacion_KRAFT_binaria(int longitud, int q);
float longitud_media(int longitud, int q, float vec[]);
float rendimiento(float entropia, float longitud);
float redundancia(float entropia, float longitud);

int main()
{
    int tot5 = 0; int tot7 = 0; int tot9 = 0;
    int vec5[ESCENARIO_1] = {0}; int vec7[ESCENARIO_2] = {0}; int vec9[ESCENARIO_3] = {0};
    float prob5[ESCENARIO_1], prob7[ESCENARIO_2], prob9[ESCENARIO_3];
    float info5[ESCENARIO_1], info7[ESCENARIO_2], info9[ESCENARIO_3];
    float entropia5, entropia7, entropia9;
    float prob_condicionales[4][4] = {0};

    lectura(vec5,&tot5,5);
    lectura(vec7,&tot7,7);
    lectura(vec9,&tot9,9);

    calcula_prob(prob5,vec5,ESCENARIO_1,tot5);
    calcula_prob(prob7,vec7,ESCENARIO_2,tot7);
    calcula_prob(prob9,vec9,ESCENARIO_3,tot9);

    calcula_cant_info(prob5,info5,ESCENARIO_1);
    calcula_cant_info(prob7,info7,ESCENARIO_2);
    calcula_cant_info(prob9,info9,ESCENARIO_3);

    entropia5 = entropia(info5,prob5,ESCENARIO_1);
    entropia7 = entropia(info7,prob7,ESCENARIO_2);
    entropia9 = entropia(info9,prob9,ESCENARIO_3);

    cant_info_simbolo(info5,ESCENARIO_1,5);
    printf("-------------------------------------------------------------------------\n");
    cant_info_simbolo(info7,ESCENARIO_2,7);
    printf("-------------------------------------------------------------------------\n");
    cant_info_simbolo(info9,ESCENARIO_3,9);
    printf("-------------------------------------------------------------------------\n");

    printf("La cantidad de informacion de la fuente en el escenario 1 es %4.5f bits\n",cant_info(info5,ESCENARIO_1));
    printf("La cantidad de informacion de la fuente en el escenario 2 es %4.5f bits\n",cant_info(info7,ESCENARIO_2));
    printf("La cantidad de informacion de la fuente en el escenario 3 es %4.5f bits\n",cant_info(info9,ESCENARIO_3));
    printf("-------------------------------------------------------------------------\n");

    printf("La entropia de la fuente en el escenario 1 es %4.5f bits\n",entropia5);
    printf("La entropia de la fuente en el escenario 2 es %4.5f bits\n",entropia7);
    printf("La entropia de la fuente en el escenario 3 es %4.5f bits\n",entropia9);
    printf("-------------------------------------------------------------------------\n");

    matriz_prob_cond(prob_condicionales);
    muestraMat(prob_condicionales);
    printf("-------------------------------------------------------------------------\n");



    if(inecuacion_KRAFT_binaria(5,ESCENARIO_1))
        printf("El codigo del escenario 1 cumple con la inecuacion de KRAFT\n");
    else
        printf("El codigo del escenario 1 no cumple con la inecuacion de KRAFT\n");

    if(inecuacion_KRAFT_binaria(7,ESCENARIO_2))
        printf("El codigo del escenario 2 cumple con la inecuacion de KRAFT\n");
    else
        printf("El codigo del escenario 2 no cumple con la inecuacion de KRAFT\n");

    if(inecuacion_KRAFT_binaria(9,ESCENARIO_3))
        printf("El codigo del escenario 3 cumple con la inecuacion de KRAFT\n");
    else
        printf("El codigo del escenario 3 no cumple con la inecuacion de KRAFT\n");
    printf("-------------------------------------------------------------------------\n");

    float longMedia5, longMedia7, longMedia9;
    longMedia5 = longitud_media(5,ESCENARIO_1,prob5);
    longMedia7 = longitud_media(7,ESCENARIO_2,prob7);
    longMedia9 = longitud_media(9,ESCENARIO_3,prob9);
    printf("Longitud media codigo 1: %.3f\n",longMedia5);
    printf("Longitud media codigo 2: %.3f\n",longMedia7);
    printf("Longitud media codigo 3: %.3f\n",longMedia9);
    printf("-------------------------------------------------------------------------\n");

    printf("Rendimiento codigo 1: %.6f\n",rendimiento(entropia5,longMedia5));
    printf("Redundancia codigo 1: %.6f\n",redundancia(entropia5,longMedia5));
    printf("Rendimiento codigo 2: %.6f\n",rendimiento(entropia7,longMedia7));
    printf("Redundancia codigo 2: %.6f\n",redundancia(entropia7,longMedia7));
    printf("Rendimiento codigo 3: %.6f\n",rendimiento(entropia9,longMedia9));
    printf("Redundancia codigo 3: %.6f\n",redundancia(entropia9,longMedia9));

    return 0;
}

void matriz_prob_cond(float prob_cond[][4])
{
    int ant, num; char cad[3];
    float totalColumna;
    FILE *arch;
    arch = fopen("grupo7.txt","rt");
    if(arch != NULL)
    {
        fgets(cad,3,arch);
        ant = binario_a_entero(cad);
        if(!feof(arch))
        {
            fgets(cad,3,arch);
            while(!feof(arch))
            {
                num = binario_a_entero(cad);
                prob_cond[num][ant] += 1;
                ant = num;
                fgets(cad,3,arch);
            }
        }
        for(int j=0;j<4;j++)
        {
            totalColumna = sumatoria_columna(prob_cond,j);
            for(int i=0;i<4;i++)
                prob_cond[i][j] = prob_cond[i][j] / totalColumna;
        }
        fclose(arch);
    }
}

float sumatoria_columna(float prob_cond[][4], int col)
{
    float aux = 0;
    for(int i=0;i<4;i++)
        aux += prob_cond[i][col];
    return aux;
}

void muestraMat(float prob[][4])
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
            printf("%f ",prob[i][j]);
        printf("\n");
    }
}


float entropia(float info[],float prob[],int n)
{
    float aux = 0;
    for(int i=0;i<n;i++)
        aux += (info[i] * prob[i]);
    return aux;
}

float cant_info(float info[], int n)  //todavia va?
{
    float aux = 0;
    for(int i=0;i<n;i++)
        aux += info[i];
    return aux;
}

void calcula_prob(float prob[],int vec[],int n,int tot)
{
    for(int i=0;i<n;i++)
        prob[i] = (float) vec[i] / tot;
}

int binario_a_entero(char *cad)
{
    int rta = 0, i = strlen(cad)-1, base2 = 1;
    while(i >= 0)
    {
        if(cad[i] == '1')
            rta += base2;
        base2 *= 2;
        i--;
    }
    return rta;
}

void lectura(int vec[], int *tot, int n)
{
    int num; char cad[n+1];
    FILE *arch;
    arch = fopen("grupo7.txt","rt");
    if(arch != NULL)
    {
        fgets(cad,n+1,arch);
        while(!feof(arch))
        {
            num = binario_a_entero(cad);
            vec[num]++;
            (*tot)++;
            fgets(cad,n+1,arch);
        }
    }
    fclose(arch);
}

void calcula_cant_info(float prob[],float info[], int n)
{
    for(int i=0;i<n;i++)
        if(prob[i] != 0)
            info[i] = -1 * log2(prob[i]);
        else
            info[i] = 0;
}

int inecuacion_KRAFT_binaria(int longitud, int q)
{
    float suma = 0;
    for(int i = 1; i<= q; i++)
        suma = suma + pow(2,longitud*-1);
    if(suma <= 1)
        return 1;
    else
        return 0;
}

float longitud_media(int longitud, int q, float vec[])
{
    float rta = 0, aux = (float) longitud;
    for(int i=0;i<q;i++)
        rta = rta + (aux * vec[i]);
    return rta;
}

float rendimiento(float entropia, float longitud)
{
    return (entropia/longitud);
}

float redundancia(float entropia, float longitud)
{
    return ((longitud-entropia)/longitud);
}

void cant_info_simbolo(float info[], int n, int codigo)
{
    int i;
    for(i=0;i<n;i++)
    {
        printf("I(");
        decabin(i,0,codigo);
        printf(")= %4.6f bits\n",info[i]);
    }
}

void decabin (int n, int cont, int cant_bits) {
    if (n) {
        decabin(n / 2, cont+1, cant_bits);
        printf("%d", n % 2);
    }
    else
    {
        for(int i = 0; i < cant_bits - cont;i++)
            printf("0");
    }
}

