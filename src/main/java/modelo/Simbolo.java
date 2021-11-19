package modelo;

public class Simbolo {

	private String codigo;
	private char caracter;
	private double probabilidad;
	
	
	
	public Simbolo() {
		
	}
	
	public Simbolo(char caracter, double probabilidad) {
		this.caracter = caracter;
		this.probabilidad = probabilidad;
		this.codigo="";
	}


	public char getCaracter() {
		return caracter;
	}




	public double getProbabilidad() {
		return probabilidad;
	}


	public void setProbabilidad(double probabilidad) {
		this.probabilidad = probabilidad;
	}


	public String getCodigo() {
		return codigo;
	}


	public void setCodigo(String codigo) {
		this.codigo = codigo;
	}

	

}
