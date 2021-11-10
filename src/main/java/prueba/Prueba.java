package prueba;

import modelo.Diccionario;

public class Prueba {

    public static void main(String[] args) {
        Diccionario diccionario = new Diccionario();
        diccionario.leeArchivo("src/main/resources/files/Argentina.txt");
        diccionario.muestraPalyProb();
        System.out.println("Cantidad de caracteres: "+diccionario.getcantElem());
        System.out.println("Suma de probabilidades: "+diccionario.sumProb());
        
        System.out.println("ACA");

    }

}
