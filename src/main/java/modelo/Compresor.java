package modelo;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Iterator;

public abstract class Compresor {

	 private HashMap<Character,ElementoDiccionario> tablaCodigo = new HashMap<>();
	 protected ArrayList<Simbolo> simbolos = new ArrayList<>();
	 private long cantidadDeElementos;
	
	 
	 
	 
	public Compresor(HashMap<Character,ElementoDiccionario> tablaCodigo, long cantidadDeElementos){
		this.tablaCodigo = tablaCodigo;
		this.cantidadDeElementos=cantidadDeElementos;
		this.creaYOrdena();
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
				 System.out.println(simbolos.get(i).getCaracter() + "     "+simbolos.get(i).getProbabilidad()+ "       "+simbolos.get(i).getCodigo());
			  }	
		}
	 
	 
	 
	 public abstract void generaCodificacion();
	
}
