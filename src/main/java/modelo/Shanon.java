package modelo;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;



public class Shanon extends Compresor{


	 
	 
	public Shanon(HashMap<Character,ElementoDiccionario> tablaCodigo, long cantidadDeElementos){
		super(tablaCodigo, cantidadDeElementos);
	}
	
	
	
	
	

	   
	   
	   @Override
	   public void generaCodificacion() {
		   this.algoritmoShanon(simbolos.size(),0,simbolos.size()-1,1);
	   }
	   
	 //n = tama�o del array;  inicio = 0 ;  fin = tama�o del array-1; probTotal = 1
	   private  void algoritmoShanon(int n, int inicio, int fin, float probTotal) {
		   Simbolo s;
		   
		   if(n<=2) {
			 s =  simbolos.get(inicio);
			 s.setCodigo(s.getCodigo()+"1");
			 s =  simbolos.get(fin);
			 s.setCodigo(s.getCodigo()+"0");
		   }
		   else{
			 int i,j;
			 i = inicio;
			 float sumProb = 0;
			 
			 while(sumProb < probTotal/2) {
				 s = simbolos.get(i);
				 sumProb+= s.getProbabilidad();
				 s.setCodigo(s.getCodigo()+"1");
				 i++;
			 }
			 
			 algoritmoShanon(i-inicio, inicio, i-1, sumProb);
			 
			 for(j=i;j<=fin;j++) {
				 s = simbolos.get(j);
				 s.setCodigo(s.getCodigo()+"0");
			 }
			 
			 algoritmoShanon(fin-inicio-1, i, fin, probTotal-sumProb);
			 
		   }
		   
	   }






	
	
	
}
