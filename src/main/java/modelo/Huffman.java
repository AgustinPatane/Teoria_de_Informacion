package modelo;

import java.util.ArrayList;
import java.util.HashMap;

public class Huffman extends Compresor{

	
	
	public Huffman(HashMap<Character, ElementoDiccionario> tablaCodigo, long cantidadDeElementos) {
		super(tablaCodigo, cantidadDeElementos);
		
	}

	
	@Override
	public void generaCodificacion() {
		this.codigoHuffman(simbolos,simbolos.size());
		
	}


	
	
	
	
	
	
	
	
	
	private void codigoHuffman(ArrayList<Simbolo> simbolos, int n){

	    int pos;
	   
	    
	    if(n>2){

	    		
	       simbolos.get(n-2).setProbabilidad(simbolos.get(n-1).getProbabilidad()+simbolos.get(n-2).getProbabilidad());	 
	       pos=acomodar(simbolos.get(n-2).getProbabilidad(),n,simbolos);
	  
	      codigoHuffman(simbolos,n-1);
	       
	      Simbolo aux[] = new Simbolo[n];
	      
	      for(int i=0; i<n;i++)
	    	  aux[i] = new Simbolo();
	      

	      System.out.println(aux[n-1].getCaracter()); 
	      aux[n-1].setCodigo(simbolos.get(pos).getCodigo());

	      aux[n-2].setCodigo(simbolos.get(pos).getCodigo());

	      aux[n-1].setCodigo(aux[n-1].getCodigo()+"0");
	     
	      
	      aux[n-2].setCodigo(aux[n-2].getCodigo()+"1");

	       for(int i=0;i<pos;i++)
	    	   aux[i].setCodigo(simbolos.get(i).getCodigo());


	       for(int i=pos;i<=n-3;i++)
	    	   	aux[i].setCodigo(simbolos.get(i+1).getCodigo());
	        

	       for(int i=0;i<n;i++)
	    	    simbolos.get(i).setCodigo(aux[i].getCodigo());
	    

	    }
	    else{
	    	simbolos.get(0).setCodigo("0");
	    	simbolos.get(1).setCodigo("1");
	    }


	}







	private int acomodar(double num_A_Acomodar, int n, ArrayList<Simbolo> simbolos){

	    int i;
	    i=n-3;
	    
	    
	    
	    while(i>=0 && num_A_Acomodar>=simbolos.get(i).getProbabilidad()){
	    	simbolos.get(i+1).setProbabilidad(simbolos.get(i).getProbabilidad());
	        i--;
	    }

	    simbolos.get(i+1).setProbabilidad(num_A_Acomodar);
	    return i+1;

	}




	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

}











