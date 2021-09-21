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

int main()
{
    int tot5 = 0; int tot7 = 0; int tot9 = 0;
    int vec5[ESCENARIO_1] = {0}; int vec7[ESCENARIO_2] = {0}; int vec9[ESCENARIO_3] = {0};
    float prob5[ESCENARIO_1], prob7[ESCENARIO_2], prob9[ESCENARIO_3];
    float info5[ESCENARIO_1], info7[ESCENARIO_2], info9[ESCENARIO_3];
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

    printf("La cantidad de informacion de la fuente en el escenario 1 es %4.5f bits\n",cant_info(info5,ESCENARIO_1));
    printf("La cantidad de informacion de la fuente en el escenario 2 es %4.5f bits\n",cant_info(info7,ESCENARIO_2));
    printf("La cantidad de informacion de la fuente en el escenario 3 es %4.5f bits\n",cant_info(info9,ESCENARIO_3));
    printf("-------------------------------------------------------------------------\n");

    printf("La entropia de la fuente en el escenario 1 es %4.5f bits\n",entropia(info5,prob5,ESCENARIO_1));
    printf("La entropia de la fuente en el escenario 2 es %4.5f bits\n",entropia(info7,prob7,ESCENARIO_2));
    printf("La entropia de la fuente en el escenario 3 es %4.5f bits\n",entropia(info9,prob9,ESCENARIO_3));
    printf("-------------------------------------------------------------------------\n");

    matriz_prob_cond(prob_condicionales);
    muestraMat(prob_condicionales);




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

float cant_info(float info[], int n)
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

