package prueba;

import modelo.*;

import java.io.*;
import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;

public class Prueba {
    public static void main(String[] args) {

        Diccionario diccionario = new Diccionario();
        diccionario.leeArchivo("src/main/resources/files/Argentina.txt");
        System.out.println("Cantidad de caracteres: "+diccionario.getcantElem());
        System.out.println("Suma de probabilidades: "+diccionario.sumProb());





        Compresor c1 = new Shanon(diccionario.getTablaCodigo(), diccionario.getcantElem());
        c1.generaCodificacion();
        c1.muestraCodificacion();
        c1.comprimeArchivo("src/main/resources/files/Argentina.txt","src/main/resources/files/Argentina.Fan");



        System.out.println("CODIFICACION CON HUFFMAN");
        Compresor c2 = new Huffman(diccionario.getTablaCodigo(),diccionario.getcantElem());

        ArrayList<Simbolo> simbolosOriginal = new ArrayList<>();
        //en el metodo generaCodificacion se altera el arreglo de probabilidades. Este auxilizar (simbolosOriginal) se usa para mostrar luego la tabla de codigos con sus probabilidades
        Simbolo s=null;
        for(int i=0; i<c2.getSimbolos().size();i++) {
            s = new Simbolo(c2.getSimbolos().get(i).getCaracter(),c2.getSimbolos().get(i).getProbabilidad());
            simbolosOriginal.add(s);
        }


        c2.generaCodificacion();
        for(int i=0; i<c2.getSimbolos().size();i++) {
            simbolosOriginal.get(i).setCodigo(c2.getSimbolos().get(i).getCodigo());;
        }

        c2.setSimbolos(simbolosOriginal);
        c2.muestraCodificacion();
        c2.comprimeArchivo("src/main/resources/files/Argentina.txt","src/main/resources/files/Argentina.Huf");



        Rlc rlc = new Rlc();
        rlc.leeYEscribeRaw("src/main/resources/files/imagen.raw");
        rlc.leeyEscribeTxt("src/main/resources/files/Latin.txt");
        rlc.leeyEscribeTxt("src/main/resources/files/Argentina.txt");




        ////////////////Segunda parte//////////////////

        int cantEntrada, cantSalida;

        //--------------------CANAL-1---------------------

        cantEntrada = 5;
        cantSalida = 3;
        double[][] mat1 = new double[cantEntrada][cantSalida];
        double[] prob1 = new double[cantEntrada];

        prob1[0] = 0.35;
        prob1[1] = 0.2;
        prob1[2] = 0.2;
        prob1[3] = 0.105;
        prob1[4] = 0.145;

        mat1[0][0]= 0.3   ; mat1[0][1]= 0.105 ; mat1[0][2]= 0.595;
        mat1[1][0]= 0.14  ; mat1[1][1]= 0.4   ; mat1[1][2]= 0.46;
        mat1[2][0]= 0.3   ; mat1[2][1]= 0.105 ; mat1[2][2]= 0.595;
        mat1[3][0]= 0.105 ; mat1[3][1]= 0.4   ; mat1[3][2]= 0.495;
        mat1[4][0]= 0.3   ; mat1[4][1]= 0.14  ; mat1[4][2]= 0.56;

        Canal canal1 = new Canal(mat1,prob1,cantEntrada,cantSalida,"Canal 1");
        System.out.println(canal1.muestraDatos());



        //--------------------CANAL-2---------------------

        cantEntrada = 4;
        cantSalida = 4;
        double[][] mat2 = new double[cantEntrada][cantSalida];
        double[] prob2 = new double[cantEntrada];

        prob2[0] = 0.35;
        prob2[1] = 0.105;
        prob2[2] = 0.2;
        prob2[3] = 0.345;


        mat2[0][0]= 0.2   ; mat2[0][1]= 0.105 ; mat2[0][2]= 0.2   ; mat2[0][3]= 0.495;
        mat2[1][0]= 0.105 ; mat2[1][1]= 0.3   ; mat2[1][2]= 0.2   ; mat2[1][3]= 0.395;
        mat2[2][0]= 0.105 ; mat2[2][1]= 0.2   ; mat2[2][2]= 0.2   ; mat2[2][3]= 0.495;
        mat2[3][0]= 0.105 ; mat2[3][1]= 0.3   ; mat2[3][2]= 0.105 ; mat2[3][3]= 0.49;

        Canal canal2 = new Canal(mat2,prob2,cantEntrada,cantSalida,"Canal 2");
        System.out.println(canal2.muestraDatos());


        //--------------------CANAL-3---------------------

        cantEntrada = 6;
        cantSalida = 4;
        double[][] mat3 = new double[cantEntrada][cantSalida];
        double[] prob3 = new double[cantEntrada];

        prob3[0] = 0.35;
        prob3[1] = 0.2;
        prob3[2] = 0.1;
        prob3[3] = 0.105;
        prob3[4] = 0.2;
        prob3[5] = 0.045;

        mat3[0][0]= 0.2   ; mat3[0][1]= 0.105 ; mat3[0][2]= 0.2   ; mat3[0][3]= 0.495;
        mat3[1][0]= 0.105 ; mat3[1][1]= 0.105 ; mat3[1][2]= 0.3   ; mat3[1][3]= 0.49;
        mat3[2][0]= 0.2   ; mat3[2][1]= 0.2   ; mat3[2][2]= 0.105 ; mat3[2][3]= 0.495;
        mat3[3][0]= 0.105 ; mat3[3][1]= 0.3   ; mat3[3][2]= 0.2   ; mat3[3][3]= 0.395;
        mat3[4][0]= 0.2   ; mat3[4][1]= 0.105 ; mat3[4][2]= 0.105 ; mat3[4][3]= 0.59;
        mat3[5][0]= 0.2   ; mat3[5][1]= 0.105 ; mat3[5][2]= 0.3   ; mat3[5][3]= 0.395;

        Canal canal3 = new Canal(mat3,prob3,cantEntrada,cantSalida,"Canal 3");
        System.out.println(canal3.muestraDatos());


    }
}