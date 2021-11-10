package modelo;

public class PalabraCodigo {
    private char simboloMensaje;
    private int codigo;
    
    public char getSimboloMensaje() {
		return simboloMensaje;
	}

	public void setSimboloMensaje(char simboloMensaje) {
		this.simboloMensaje = simboloMensaje;
	}

	public int getCodigo() {
		return codigo;
	}

	public void setCodigo(int codigo) {
		this.codigo = codigo;
	}

	public int devuelveBin() {
        return Integer.parseInt(Integer.toBinaryString((int)simboloMensaje));
    }
}

