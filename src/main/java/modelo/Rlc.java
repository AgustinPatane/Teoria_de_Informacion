package modelo;

import interf.LecturaEscrituraArch;

import java.io.*;
import java.nio.ByteBuffer;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;

public class Rlc implements LecturaEscrituraArch {
    @Override
    public void leeArchivo(String path) {

    }

    public void leeYEscribeRaw(String path) {
        int cont=0;
        byte numAnt;
        byte numAct;
        short tamaño;
        try {
            File file =new File(path);
            Scanner scanner =new Scanner(file);
            String ruta=path.replaceFirst("[.][a-zA-Z]+$",".rlc");
            File fileWrite = new File(ruta);
            FileOutputStream fileOutputStream =new FileOutputStream(fileWrite);
            ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream(5);
            byteArrayOutputStream.reset();
            ByteBuffer byteBuffer;
            tamaño=scanner.nextShort();
            byteBuffer =ByteBuffer.allocate(2*Short.BYTES);
            byteBuffer.putShort(tamaño);
            tamaño=scanner.nextShort();
            byteBuffer.putShort(tamaño);
            byte [] b=byteBuffer.array();
            byteArrayOutputStream.write(b);
            byteBuffer =ByteBuffer.allocate(Byte.BYTES+Integer.BYTES);
            numAnt=scanner.nextByte();
            while(scanner.hasNextBigInteger()){
                do{
                    cont++;
                    numAct=scanner.nextByte();
                } while(numAct==numAnt && scanner.hasNextBigInteger());
                byteBuffer.put(numAnt);
                byteBuffer.putInt(cont);
                b=byteBuffer.array();
                byteArrayOutputStream.write(b);
                byteBuffer.clear();
                cont=0;
                numAnt=numAct;
            }
            scanner.close();
            byteArrayOutputStream.writeTo(fileOutputStream);
            byteArrayOutputStream.flush();
            byteArrayOutputStream.close();
            fileOutputStream.flush();
            fileOutputStream.close();
        } catch (IOException e) {
            System.out.println("Error en escritura de archivo");
        }

    }

    @Override
    public void escribeArchivo(String path) {

    }
}
