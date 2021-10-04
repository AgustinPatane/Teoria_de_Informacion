#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ESCENARIO_1 32
#define ESCENARIO_2 128
#define ESCENARIO_3 512



typedef struct{
    float prob;
    char numBinario[20];
    int valor_original;
}TTT;




void lectura(int vec[], int *tot, int n);
int binario_a_entero(char *cad);
void calcula_prob(float prob[],int vec[],int n,int tot);
void calcula_cant_info(float prob[],float info[], int n);
float cant_info(float info[], int n);
float entropia(float info[],float prob[],int n);
float sumatoria_columna(float prob_cond[][4], int col);
void genera_matriz_prob_cond(float prob_cond[][4]);
void muestraMat(float prob[][4]);
void muestra_cantInfo_simbolos(float info[], int n, int codigo);
void decabin (int n, int cont, int cant_bits) ;


void generaYMuestraVectorEstacionario(float prob[][4], int tam, float vectorEstacionario[4]);
float entropia_vector_estacionario(float estacionario[], float prob_cond[][4]);

int inecuacion_KRAFT_binaria(int longitud, int q);
float longitud_media(int longitud, int q, float vec[]);
float rendimiento(float entropia, float longitud);
float redundancia(float entropia, float longitud);


void codigoHuffman(TTT prob[], int n);
int acomodar(float numA_Acomodar, int n, TTT prob[]);
void ordena(TTT arreglo[], int n);
void almacenaEnHuffman(TTT huffman[], int n, float prob[]);


void escribe_Archivo(char cad_aux[], int longSimbolo, TTT vector[], int n);
int esCompacto(float prob[],int n, int longitud);

void solucion(float prob[][4], int tam);

int main()
{
    int tot5 = 0; int tot7 = 0; int tot9 = 0;
    int vec5[ESCENARIO_1] = {0}; int vec7[ESCENARIO_2] = {0}; int vec9[ESCENARIO_3] = {0};
    float prob5[ESCENARIO_1], prob7[ESCENARIO_2], prob9[ESCENARIO_3];
    float info5[ESCENARIO_1], info7[ESCENARIO_2], info9[ESCENARIO_3];
    float entropia5, entropia7, entropia9;
    float prob_condicionales[4][4] = {0};
    float auxProbCond[4][4]={0};
    float vectorEstacionario[4];



    //////////////////////////////////////////////////PARTE 1 - INCISO A/////////////////////////////////////////////////////////////////////////////

    lectura(vec5,&tot5,5); //almacena en vec5 las frecuencias de cada simbolo (del 0 al 31)
    lectura(vec7,&tot7,7); //almacena en vec7 las frecuencias de cada simbolo (del 0 al 127)
    lectura(vec9,&tot9,9); //almacena en vec9 las frecuencias de cada simbolo (del 0 al 511)

    calcula_prob(prob5,vec5,ESCENARIO_1,tot5); //almacena en prob5 las probabilidades de cada simbolo del escenario 5
    calcula_prob(prob7,vec7,ESCENARIO_2,tot7); //almacena en prob7 las probabilidades de cada simbolo del escenario 7
    calcula_prob(prob9,vec9,ESCENARIO_3,tot9); //almacena en prob9 las probabilidades de cada simbolo del escenario 9

    calcula_cant_info(prob5,info5,ESCENARIO_1); //almacena en info5 la cantidad de informacion de cada simbolo del escenario 5
    calcula_cant_info(prob7,info7,ESCENARIO_2); //almacena en info7 la cantidad de informacion de cada simbolo del escenario 7
    calcula_cant_info(prob9,info9,ESCENARIO_3); //almacena en info9 la cantidad de informacion de cada simbolo del escenario 9

    entropia5 = entropia(info5,prob5,ESCENARIO_1); //calcula la entropia de la fuente del escenario 5
    entropia7 = entropia(info7,prob7,ESCENARIO_2); //calcula la entropia de la fuente del escenario 7
    entropia9 = entropia(info9,prob9,ESCENARIO_3); //calcula la entropia de la fuente del escenario 9



    printf("----------------CANTIDAD DE INFORMACION DE CADA SIMBOLO DEL ESCENARIO 1----------------\n");
    muestra_cantInfo_simbolos(info5,ESCENARIO_1,5);
    printf("\n\n----------------CANTIDAD DE INFORMACION DE CADA SIMBOLO DEL ESCENARIO 2----------------\n");
    muestra_cantInfo_simbolos(info7,ESCENARIO_2,7);
    printf("\n\n----------------CANTIDAD DE INFORMACION DE CADA SIMBOLO DEL ESCENARIO 3----------------\n");
    muestra_cantInfo_simbolos(info9,ESCENARIO_3,9);
    printf("-----------------------------------------------------------------------------------------\n");

    printf("La entropia de la fuente en el escenario 1 es %4.5f bits\n",entropia5);
    printf("La entropia de la fuente en el escenario 2 es %4.5f bits\n",entropia7);
    printf("La entropia de la fuente en el escenario 3 es %4.5f bits\n",entropia9);
    printf("-------------------------------------------------------------------------\n\n\n");







    //////////////////////////////////////////////////PARTE 1 - INCISO B/////////////////////////////////////////////////////////////////////////////

    genera_matriz_prob_cond(prob_condicionales);
    printf("-------------------------MATRIZ DE PROBABILIDADES CONDICIONALES-------------------------\n");
    muestraMat(prob_condicionales);







    //////////////////////////////////////////////////PARTE 1 - INCISO C/////////////////////////////////////////////////////////////////////////////

    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            auxProbCond[i][j] = prob_condicionales[i][j];



    generaYMuestraVectorEstacionario(auxProbCond,4,vectorEstacionario);


    printf("\nEntropia: %.5f\n\n",entropia_vector_estacionario(vectorEstacionario,prob_condicionales));
    printf("-------------------------------------------------------------------------\n");








    //////////////////////////////////////////////////PARTE 2 - INCISO B/////////////////////////////////////////////////////////////////////////////


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



    //////////////////////////////////////////////////PARTE 2 - INCISO B/////////////////////////////////////////////////////////////////////////////

    printf("Rendimiento codigo 1: %.6f\n",rendimiento(entropia5,longMedia5));
    printf("Redundancia codigo 1: %.6f\n",redundancia(entropia5,longMedia5));
    printf("Rendimiento codigo 2: %.6f\n",rendimiento(entropia7,longMedia7));
    printf("Redundancia codigo 2: %.6f\n",redundancia(entropia7,longMedia7));
    printf("Rendimiento codigo 3: %.6f\n",rendimiento(entropia9,longMedia9));
    printf("Redundancia codigo 3: %.6f\n",redundancia(entropia9,longMedia9));









    //////////////////////////////////////////////////PARTE 2 - INCISO D/////////////////////////////////////////////////////////////////////////////

    TTT huffman5[ESCENARIO_1], huffman7[ESCENARIO_2],huffman9[ESCENARIO_3];

    almacenaEnHuffman(huffman5,ESCENARIO_1,prob5);
    almacenaEnHuffman(huffman7,ESCENARIO_2,prob7);
    almacenaEnHuffman(huffman9,ESCENARIO_3,prob9);

    codigoHuffman(huffman5,ESCENARIO_1);
    codigoHuffman(huffman7,ESCENARIO_2);
    codigoHuffman(huffman9,ESCENARIO_3);

    escribe_Archivo("escenario1.txt",5,huffman5,ESCENARIO_1);
    escribe_Archivo("escenario2.txt",7,huffman7,ESCENARIO_2);
    escribe_Archivo("escenario3.txt",9,huffman9,ESCENARIO_3);

    /*printf("PROBABILIDADES\n");
    for(int i=0;i<512;i++){
        printf("%.6f\n",prob9[i]);
    }

    printf("HUFFMAN\n");
    for(int i=0;i<512;i++){
        printf("Simbolo: %d ---->   Codigo binario: %s\n",huffman9[i].valor_original,huffman9[i].numBinario);
    }*/


    return 0;
}






void genera_matriz_prob_cond(float prob_cond[][4])
{
    int ant, num; char cad[3];
    float totalColumna;
    FILE *arch;
    arch = fopen("grupo7.txt","rt");
    if(arch != NULL){
        fgets(cad,3,arch);
        ant = binario_a_entero(cad);
        if(!feof(arch)){
            fgets(cad,3,arch);
            while(!feof(arch)){
                num = binario_a_entero(cad);
                prob_cond[num][ant] += 1;
                ant = num;
                fgets(cad,3,arch);
            }
        }
        for(int j=0;j<4;j++){
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
    printf("        00       01       10       11\n ");
    for(int i=0;i<4;i++)
    {
        decabin(i,0,2);
        printf(" |");
        for(int j=0;j<4;j++)
            printf("%f ",prob[i][j]);
        printf("|\n ");
    }
}









float entropia(float info[],float prob[],int n)
{
    float aux = 0;
    for(int i=0;i<n;i++)
        aux += (info[i] * prob[i]);
    return aux;
}

void calcula_prob(float prob[],int vec[],int n,int tot) //
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

void muestra_cantInfo_simbolos(float info[], int n, int codigo)
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

void generaYMuestraVectorEstacionario(float prob[][4], int tam, float vectorEstacionario[4]){

    int res,i,j,k,m;
    float col_pivote,x,mat[5][6]={0}; //"mat" tiene una columna de mas ya que es donde se almacenaran los resultados de la cada incognita


    for(i=0;i<tam;i++){ //almacena  en mat ---> prob - identidad
        for(j=0;j<tam;j++){
            mat[i][j] = prob[i][j];
            if(i==j)
                mat[i][j]--;
        }
    }



    for(j=0;j<tam+2;j++){ //agrega en la ultima fila la ecuacion restante (sumatoria igual a 1)
        if(j!=tam)
            mat[tam][j]=1;
    }

    for(j=0;j<5;j++)
        mat[j][4] = 0.0001;

    tam++; //al agregar la ecuacion de sumatoria igual a 1 se incrementa el tamaño de la matriz


    for(i=0;i<tam;i++)
    {
        res=0;m=i;
        while(res==0)
        {
           if((mat[m][i]>0.0000001)||((mat[m][i]<-0.0000001)) )
                res=1;
            else
                m++;
        }

        col_pivote=mat[m][i];

        for(j=0;j<(tam+1);j++)
        {
            x=mat[m][j];
            mat[m][j]=mat[i][j];
            mat[i][j]=x/col_pivote;
        }

        for(k=i+1;k<tam;k++)
        {
            x=mat[k][i];
            for(j=i;j<(tam+1);j++)
                mat[k][j]=mat[k][j]-x*mat[i][j];
        }

    }

    for(i=tam-1;i>=0;i--)
        for(j=(i-1);j>=0;j--)
        {
            mat[j][tam]=mat[j][tam]-mat[j][i]*mat[i][tam];
            mat[j][i]=0;
        }



    printf("\n\n\nVector estacionario: {");

    for(i=0;i<tam-1;i++){
        vectorEstacionario[i] = mat[i][tam];
        printf("%.4f, ",vectorEstacionario[i]);
    }
    printf("}\n\n");


}

// a esta funcion se le pasa por parametro el vector estacionario junto con la matriz de probabilidades
// condicionales y devuelve la entropia markoviana (parte 1 c)
float entropia_vector_estacionario(float estacionario[], float prob_cond[][4])
{
    float rta = 0, aux;
    for(int i = 0; i<4; i++)
    {
        aux = 0;
        for(int j = 0; j<4; j++)
            if(prob_cond[j][i]>0)
                aux += prob_cond[j][i] * -1 * log2(prob_cond[j][i]);
        rta += aux * estacionario[i];
    }
    return rta;
}

///////////////////////////////////////////FUNCIONES PARA HUFFMAN///////////////////////////////////////
void codigoHuffman(TTT prob[], int n){

    int pos;


    if(n>2){

       prob[n-2].prob+= prob[n-1].prob;

       pos=acomodar(prob[n-2].prob,n,prob);
       codigoHuffman(prob,n-1);

       TTT AUX[n];

       strcpy(AUX[n-1].numBinario,prob[pos].numBinario);
       strcpy(AUX[n-2].numBinario,prob[pos].numBinario);
       strcat(AUX[n-1].numBinario,"0");
       strcat(AUX[n-2].numBinario,"1");


       for(int i=0;i<pos;i++){
          strcpy(AUX[i].numBinario,prob[i].numBinario);
       }

       for(int i=pos;i<=n-3;i++){
                strcpy(AUX[i].numBinario,prob[i+1].numBinario);
       }

       for(int i=0;i<n;i++)
            strcpy(prob[i].numBinario,AUX[i].numBinario);

    }
    else{
        strcpy(prob[0].numBinario,"0");
        strcpy(prob[1].numBinario,"1");
    }


}

int acomodar(float numA_Acomodar, int n, TTT prob[]){

    int i;
    i=n-3;

    while(i>=0 && numA_Acomodar>=prob[i].prob){
        prob[i+1].prob=prob[i].prob;
        i--;
    }

    prob[i+1].prob=numA_Acomodar;
    return i+1;

}

void ordena(TTT arreglo[], int n)
{
    int i, j, aux2;
    float aux;
    for(i=1; i<n; i++)
    {
        j = i;
        aux = arreglo[i].prob;
        aux2 = arreglo[i].valor_original;
        while(j>0 && aux>arreglo[j-1].prob) {
            arreglo[j].prob = arreglo[j-1].prob;
            arreglo[j].valor_original = arreglo[j-1].valor_original;
            j=j-1;
        }
        arreglo[j].prob = aux;
        arreglo[j].valor_original = aux2;
    }
}

void almacenaEnHuffman(TTT huffman[], int n, float prob[]){
int i;

    for(i=0;i<n;i++){
        huffman[i].prob = prob[i];
        huffman[i].valor_original=i;
    }

}

///////////////////////////////ARCHIVO////////////////////////////////////

void escribe_Archivo(char cad_aux[], int longSimbolo, TTT vector[], int n)
{

    int i;
    FILE *leer, *escribir ;
    int num;
    char cad[longSimbolo+1];
    char huffman[n][30];

    for(i = 0; i< n;i++)
        strcpy(huffman[vector[i].valor_original],vector[i].numBinario);



    //escribir = fopen(cad_aux,"wt");
    //fclose(escribir);
    escribir = fopen(cad_aux,"wt");
    leer = fopen("grupo7.txt","rt");
    if(leer != NULL)
    {
        fgets(cad,longSimbolo+1,leer);
        while(!feof(leer))
        {
            num = binario_a_entero(cad);
            fprintf(escribir,"%s",huffman[num]);

            fgets(cad,longSimbolo+1,leer);
        }
        fclose(leer);
    }
    fclose(escribir);

}





