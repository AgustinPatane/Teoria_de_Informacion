package modelo;

public class ElementoDiccionario {
    private PalabraCodigo palabraCodigo;
    private long nroDeAparicion= 0;
    

    public long getNroDeAparicion() {
		return nroDeAparicion;
	}
	public PalabraCodigo getPalabraCodigo() {
		return palabraCodigo;
	}
	public ElementoDiccionario(PalabraCodigo palabraCodigo) {
		super();
		this.palabraCodigo = palabraCodigo;
	}
	public double calculaProb(Long totCodigos){
        return ((double)getNroDeAparicion()/totCodigos);
    }
    public void aumentaAparicion(){ nroDeAparicion++;}
}

