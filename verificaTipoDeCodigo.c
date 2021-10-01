#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



float desigualdadDeKraft(char codigo[30][30], int n, int cantSimbolos);
int verificaInstantaneo(char codigo[30][30], int n);
int esPrefijo(char palabra1[30], char palabra2[30]);
float entropia(char codigo[30][30], int n,int cantSimbolos);
double logaritmo(int b,double n);
double p(double x,int i);
double longitudMedia(char codigo[30][30], int n, int cantSimbolos);


int main()
{

    char codigo[30][30],pal[30];
    int n,i, cantSimbolos;
    float kraft;

    printf("Ingrese la cantidad de simbolos de su alfabeto fuente: ");
    scanf("%d",&n);

    printf("Ingrese el numero de simbolos del alfabeto codigo: ");
    scanf("%d",&cantSimbolos);

    for(i=0;i<n;i++){
        printf("CODIGO %d: ",i);
        fflush(stdin);
        gets(pal);
        strcpy(codigo[i],pal);
    }

    /*for(i=0;i<n;i++){
        printf("%s\n",codigo[i]);
    }*/

    kraft = desigualdadDeKraft(codigo,n,cantSimbolos);
    printf("DESIGUALDAD DE KRAFT: %f ----> ",kraft);
    if(kraft<=1)
        printf("Cumple con la desigualdad de Kraft\n");
    else
        printf("No cumple con la desigualdad de Kraft\n");



    if(verificaInstantaneo(codigo,n))
        printf("El codigo es instantaneo.\n");
    else
        printf("El codigo NO es instantaneo.\n");




    printf("La entropia de la fuente es: %f\n",entropia(codigo,n,cantSimbolos));
    printf("La longitud media de la fuente es: %f",longitudMedia(codigo,n,cantSimbolos));

    return 0;
}

//Por ej para alfabeto codigo binario cantSimbolos = 2 ---> X={0,1}
float desigualdadDeKraft(char codigo[30][30], int n, int cantSimbolos){
float suma;
int i;

    suma = 0;
    for(i=0;i<n;i++){
        //printf("STRLEN: %d",-strlen(codigo[i]));
        suma+= 1/pow(cantSimbolos,strlen(codigo[i]));
    }
    return suma;
}

printf("Estaba con la sustancia de software  de sugiciencia para colmo sssrrnswdrtefs")



int verificaInstantaneo(char codigo[30][30], int n){

int cumple,i,j;

    cumple = 1;
    i=0;
    while(cumple && i<n){
        j=0;
        while(cumple && j<n){
            if(i!=j && esPrefijo(codigo[i],codigo[j])) //el simbolo i-esimo es prefijo del simbolo j-esimo
               cumple=0;
            j++;
        }
        i++;
    }

    return cumple;


}

int esPrefijo(char palabra1[30], char palabra2[30]){


int i, longPalabra1,longPalabra2, prefijo;

    prefijo = 1;

    longPalabra1 = strlen(palabra1);
    longPalabra2 = strlen(palabra2);


    if(longPalabra1 <= longPalabra2){
        i=0;
        while(i<longPalabra1 && palabra1[i]==palabra2[i]){
            i++;
        }
    }

    if(i<longPalabra1)
        prefijo=0;

    return prefijo;

}



float entropia(char codigo[30][30], int n,int cantSimbolos){

float probabilidad,suma = 0;
int i;

    for(i=0;i<n;i++){
        probabilidad = 1/pow(cantSimbolos,strlen(codigo[i]));
        suma+=probabilidad*logaritmo(cantSimbolos,1/probabilidad);
    }

    return suma;

}








double logaritmo(int b,double n) {
    double val = 0;
    int i,accurate = 10,reps=0;
    while(n != 1 && accurate>=0) {
        for(i=0;n>=b;i++) n /= b;
            n = p(n,10);
            val = 10*(val+i);
            accurate--; reps++;
    }
    return (double)val/p(10,reps);
}



double p(double x,int i) {
    double r = 1.0;
    for(i;i>0;i--) r *= x;
    return r;
}











double longitudMedia(char codigo[30][30], int n, int cantSimbolos){

double suma,probabilidad;
int i;

    suma =0;
    for(i=0;i<n;i++){
        probabilidad = 1/pow(cantSimbolos,strlen(codigo[i]));
        suma+= probabilidad*strlen(codigo[i]);
    }

    return suma;
}


















































