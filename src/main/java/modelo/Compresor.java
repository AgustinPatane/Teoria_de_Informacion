package modelo;

import java.io.*;
import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;
import java.text.DecimalFormat;
import java.util.*;

public abstract class Compresor {

	 private HashMap<Character,ElementoDiccionario> tablaCodigo = new HashMap<>();
	 protected ArrayList<Simbolo> simbolos = new ArrayList<>();
	 private long cantidadDeElementos;
	
	 
	 
	 
	public Compresor(HashMap<Character,ElementoDiccionario> tablaCodigo, long cantidadDeElementos){
		this.tablaCodigo = tablaCodigo;
		this.cantidadDeElementos=cantidadDeElementos;
		this.creaYOrdena();
	}


	public ArrayList<Simbolo> getSimbolos() {
		return simbolos;
	}

	public void setSimbolos(ArrayList<Simbolo> simbolos) {
		this.simbolos = simbolos;
	}

	private void creaYOrdena(){
		   
		  int i,j;
		  Simbolo s;
	      Iterator <ElementoDiccionario> it = tablaCodigo.values().iterator();
	      ElementoDiccionario elementoDiccionario;
	      
	      while(it.hasNext()){
	         elementoDiccionario = it.next();
	         s = new Simbolo(elementoDiccionario.getPalabraCodigo().getSimboloMensaje(), elementoDiccionario.calculaProb(this.cantidadDeElementos));
	         simbolos.add(s);
	         
	      }  
	      
	      
	      Collections.sort(simbolos, new Comparator<Simbolo>() {
	    		@Override
	    		public int compare(Simbolo s1, Simbolo s2) {
	    			// Aqui esta el truco, ahora comparamos p2 con p1 y no al reves como antes
	    			return new Double(s2.getProbabilidad()).compareTo(new Double(s1.getProbabilidad()));
	    		}
	    	});
	          
	   }
	
	 
	 

		public void muestraCodificacion() {
			
			 System.out.println("Simbolo        Probabilidad      Codigo");
			 for(int i=0; i<simbolos.size();i++) {
				 System.out.println("   " +simbolos.get(i).getCaracter() + "             "+new DecimalFormat("#.###").format(simbolos.get(i).getProbabilidad())+ "                "+simbolos.get(i).getCodigo());
			  }	
		}
	 
	 
	 
	 public abstract void generaCodificacion();
	public void comprimeArchivo(String path,String newPath){
		File file = new File(path);
		if(simbolos.size()==0)
			System.out.println("Primero debe tener los elementos codificados");
		else {
			try {
				FileReader fileReader = new FileReader(path);
				FileOutputStream fileOutputStream =new FileOutputStream(newPath);
				ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream(Byte.BYTES);
				ByteBuffer byteBuffer=ByteBuffer.allocate(Byte.BYTES);
				int i;
				char caracter;
				byte b=0;
				byte [] byteArray,byteArrayWrite;
				int bits_libres=8;
				while ((i=fileReader.read())!=-1){
					caracter=(char)i;
					Iterator<Simbolo> it =simbolos.iterator();
					Simbolo simbolo=it.next();
					while(it.hasNext() && simbolo.getCaracter()!=caracter) {
						simbolo=it.next();
					}
						byteArray=simbolo.getCodigo().getBytes(StandardCharsets.UTF_8);
						for(int k=0;k<byteArray.length;k++){
							if(bits_libres==0){
								byteBuffer.put(b);
								//byteArrayWrite=byteBuffer.array();
								byteArrayOutputStream.write(b);
								byteBuffer.clear();
								bits_libres=8;
								b=0;
							}
							if(byteArray[k]==49)
								b= (byte) (b|1<<bits_libres-1);
							bits_libres--;
						}
					}
				if(bits_libres!=8){
					byteBuffer.put(b);
					byteArrayWrite=byteBuffer.array();
					byteArrayOutputStream.write(byteArrayWrite);
				}
				byteArrayOutputStream.writeTo(fileOutputStream);
				byteArrayOutputStream.flush();
				byteArrayOutputStream.close();
				fileOutputStream.flush();
				fileOutputStream.close();
				fileReader.close();
				} catch (FileNotFoundException e) {
				e.printStackTrace();

				} catch (IOException e) {
				System.out.println("Error al intentar escribir arhivo");
			}

		}
	}
}
