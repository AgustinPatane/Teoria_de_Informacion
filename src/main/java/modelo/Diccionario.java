package modelo;

import interf.LecturaEscrituraArch;


import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Iterator;

public class Diccionario implements LecturaEscrituraArch {
   private HashMap<Character,ElementoDiccionario> tablaCodigo = new HashMap<>();
   private long cantElem=0;
   public void agregaPalabra(PalabraCodigo palabraCodigo){
      if(!tablaCodigo.containsKey(palabraCodigo.getSimboloMensaje()))
         tablaCodigo.put(palabraCodigo.getSimboloMensaje(),new ElementoDiccionario(palabraCodigo));
      ElementoDiccionario elementoDiccionario =tablaCodigo.get(palabraCodigo.getSimboloMensaje());
      elementoDiccionario.aumentaAparicion();
      tablaCodigo.replace(palabraCodigo.getSimboloMensaje(),elementoDiccionario);
      cantElem++;
   }
   
   

   public long getCantElem() {
	return cantElem;
}




@Override
   public void leeArchivo(String path) {
      try {
         FileReader fileReader = new FileReader(path);
         int i;
         while((i=fileReader.read())!=-1){
            PalabraCodigo palabraCodigo = new PalabraCodigo();
            palabraCodigo.setSimboloMensaje((char)i);
            palabraCodigo.setCodigo(palabraCodigo.devuelveBin());
            agregaPalabra(palabraCodigo);
         }
         fileReader.close();

      } catch (IOException e) {
         System.out.println("Error archivo");
      }
   }

   @Override
   public void escribeArchivo(String path) {

   }
   public void muestraPalyProb(){
      Iterator <ElementoDiccionario> it = tablaCodigo.values().iterator();
      ElementoDiccionario elementoDiccionario;
      while(it.hasNext()){
         elementoDiccionario=it.next();
         System.out.println("Caracter: "+
                 elementoDiccionario.getPalabraCodigo().getSimboloMensaje()
                 +" numero de apariciones: "
                 +elementoDiccionario.getNroDeAparicion() + " Prob de aparicion "+elementoDiccionario.calculaProb(cantElem));
      }
   }

   public long getcantElem(){
      return cantElem;
   }

   public double sumProb() {
      Iterator<ElementoDiccionario> it = tablaCodigo.values().iterator();
      ElementoDiccionario elementoDiccionario;
      double acu=0;
      while (it.hasNext()) {
         elementoDiccionario=it.next();
         acu+=elementoDiccionario.calculaProb(getcantElem());
      }
      return  acu;
   }
}
