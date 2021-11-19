package prueba;

import modelo.*;

import java.io.*;
import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class Prueba {
    public static void main(String[] args) {
        Diccionario diccionario = new Diccionario();
        diccionario.leeArchivo("src/main/resources/files/Argentina.txt");
        System.out.println("Cantidad de caracteres: "+diccionario.getcantElem());
        System.out.println("Suma de probabilidades: "+diccionario.sumProb());



      //System.out.println("--------------------------------------------------------------------------------------------------------------------");

        Compresor c1 = new Shanon(diccionario.getTablaCodigo(),diccionario.getcantElem());
        c1.generaCodificacion();
        c1.muestraCodificacion();



        Compresor c2 = new Huffman(diccionario.getTablaCodigo(),diccionario.getcantElem());
        c2.generaCodificacion();
        c2.muestraCodificacion();
        //Compresor c3 = new CRL(diccionario.getTablaCodigo(),diccionario.getcantElem());

        boolean s;
       /* System.out.println();
        Rlc rlc =new Rlc();
        rlc.leeYEscribeRaw("src/main/resources/files/imagen.raw");
        File file =new File("src/main/resources/files/imagen.rlc");
        try {
            byte [] b;
            FileInputStream fileInputStream =new FileInputStream(file);
            ByteBuffer byteBuffer=ByteBuffer.allocate(Short.BYTES);
           // ByteArrayInputStream byteArrayInputStream =new ByteArrayInputStream(byteBuffer.array());
            BufferedInputStream bufferedInputStream =new BufferedInputStream(fileInputStream);
          b= bufferedInputStream.readAllBytes();
            byteBuffer =ByteBuffer.allocate(b.length);
            byteBuffer.put(b);
          int n= byteBuffer.getShort(0);
          System.out.println(n);
          n=byteBuffer.getShort(Short.BYTES);
            System.out.println(n);
            n=byteBuffer.get(2*Short.BYTES);
            System.out.println(n);
            n=byteBuffer.getInt(2*Short.BYTES+1);
            //byteBuffer.putShort();
          System.out.println(n);
            //System.out.println(b[1]);


        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

            */
    }
}
