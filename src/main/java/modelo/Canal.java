package modelo;

public class Canal
{
	private String nombre; 			      // * Nombre del canal (no es necesario en absoluto, pero nos sirve para
									      // identificar cada uno de los canales con los que vamos a trabajar)
	private int cantSimbolosEntrada;      // * Cantidad de simbolos del alfabeto de entrada
	private int cantSimbolosSalida;       // * Cantidad de sombolos del alfabeto de salida
	private double matrizCanal[][];       // * Matriz de probabilidades condicionales P(bj/Si) (pasada por paramtero)
	private double probEntrada[]; 	      // * Arreglo compuesto por cada P(Si) (pasado por parametro)
	private double probSalida[]; 	      // * Arreglo compuesto por cada P(bj)
	private double probAPosteriori[][];   // * Probabilidades a posteriori P(Si/bj)
	private double probSimultaneas[][];   // * Probabilidades simultaneas
	private double entropiaAPriori;       // * Entropia a priori (la de siempre) H(S) = sumatoria( P(ai) *log (1/P(Si)) )
	private double entropiaSalida;        // * Entropia H(B) = sumatoria( P(bj) *log (1/P(bj))
	private double entropiasAPosteriori[];// * Entropia a posteriori H(S/bj) = sumatoria( P(S/bj) * log(1/P(S/bj)) )
	private double equivocacion;          // * Equivocacion del canal H(S/B)
	private double entropiaAfin;          // * H(S,B)
	private double perdida;               // * H(B/A)
	
	private double infoMutua;             // * Informacion mutua del canal
	

	public Canal(double aux[][], double prob[], int cantEntrada, int cantSalida, String nomb)
	{
		this.cantSimbolosEntrada = cantEntrada;
		this.cantSimbolosSalida = cantSalida;
		this.matrizCanal = aux;
		this.probEntrada = prob;
		this.nombre = nomb;
		
		this.probSalida = new double[cantSalida];
		this.probAPosteriori = new double[cantSalida][cantEntrada];
		this.entropiasAPosteriori = new double[cantSalida];
		this.probSimultaneas = new double[cantEntrada][cantSalida];
		
		this.entropiaAPriori = this.calculaEntropiaAPriori();
		this.calculaProbSalida();
		this.entropiaSalida = this.calculaEntropiaSalida();
		this.calculaProbAPosteriori();
		this.calculaEntropiasAPosteriori();
		this.calculaProbSimultaneas();
		
		this.entropiaAfin = this.calculaEntropiaAfin();
		this.equivocacion = this.calculaEquivocacion();
		this.infoMutua = this.calculaInfoMutua();
		this.perdida = this.calculaPerdida();
	}
	
	private double calculaEntropiaAfin()
	{
		double rta = 0;
		for(int j=0;j<this.cantSimbolosSalida;j++)
			for(int i=0;i<this.cantSimbolosEntrada;i++)
				if(this.probSimultaneas[i][j] != 0)
					rta += this.probSimultaneas[i][j] * -1 * Util.log2(this.probSimultaneas[i][j]);
		return rta;
	}
	
	private double calculaInfoMutua() //I(S,B)
	{
		double rta = 0;
		for(int j=0;j<this.cantSimbolosSalida;j++)
			for(int i=0;i<this.cantSimbolosEntrada;i++)
				if(this.probSimultaneas[i][j] != 0)
					rta += this.probSimultaneas[i][j] * Util.log2(this.probSimultaneas[i][j]/(this.probEntrada[i]*this.probSalida[j]));
		return rta;
	}
	
	private double calculaEquivocacion()  //H(S/B)
	{
		double rta = 0;
		for(int i=0;i<this.cantSimbolosSalida;i++)
			rta += this.probSalida[i] * this.entropiasAPosteriori[i];
		return rta;
	}
	
	private double calculaPerdida()  //H(B/S)
	{
		double rta = 0;
		for(int j=0;j<this.cantSimbolosSalida;j++)
			for(int i=0;i<this.cantSimbolosEntrada;i++)
				if(this.matrizCanal[i][j] != 0)
					rta += this.probSimultaneas[i][j] * -1 * Util.log2(this.matrizCanal[i][j]);
		return rta;
	}
	
	
	
	private double calculaEntropiaAPriori()  //H(S)
	{
		double rta = 0;
		for(int i=0;i<this.cantSimbolosEntrada;i++)
			if(this.probEntrada[i] != 0)
				rta += this.probEntrada[i] * -1 * Util.log2(this.probEntrada[i]);
		return rta;
	}
	
	private double calculaEntropiaSalida()  //H(B)
	{
		double rta = 0;
		for(int j=0;j<this.cantSimbolosSalida;j++)
			if(this.probSalida[j] != 0)
				rta += this.probSalida[j] * -1 * Util.log2(this.probSalida[j]);
		return rta;
	}
	
	private void calculaEntropiasAPosteriori()  //H(S/B1), H(S/B2), H(S/B3).....
	{
		double aux;
		for(int j=0;j<this.cantSimbolosSalida;j++)
		{
			aux = 0;
			for(int i=0;i<this.cantSimbolosEntrada;i++)
				if(this.probAPosteriori[j][i] != 0)
					aux += this.probAPosteriori[j][i] * -1 * Util.log2(this.probAPosteriori[j][i]);
			this.entropiasAPosteriori[j] = aux;
		}
	}
	
	private void calculaProbSimultaneas()  //P(S1,B1), P(S1,B2), P(S1,B3).....
	{
		for(int j=0;j<this.cantSimbolosSalida;j++)
			for(int i=0;i<this.cantSimbolosEntrada;i++)
				this.probSimultaneas[i][j] = this.matrizCanal[i][j] * this.probEntrada[i];
	}
	
	private void calculaProbSalida()  //P(B1), P(B2), P(B3).....
	{
		double aux;
		for(int j=0;j<this.cantSimbolosSalida;j++) //recorro cada posicion del vector probSalida
		{
			aux = 0;
			for(int i=0;i<this.cantSimbolosEntrada;i++)
				aux += this.probEntrada[i] * this.matrizCanal[i][j];
			this.probSalida[j] = aux;
		}	
	}
	
	private void calculaProbAPosteriori()  //P(S1/B1), P(S1/B2), P(S1/B3).....
	{
		for(int i=0;i<this.cantSimbolosEntrada;i++)
			for(int j=0;j<this.cantSimbolosSalida;j++)
				this.probAPosteriori[j][i] = (this.matrizCanal[i][j] * this.probEntrada[i]) / this.probSalida[j];
	}
	
	public String muestraDatos()
	{
		int i, j;
		
		StringBuilder str = new StringBuilder();
		
		str.append("|-----------------------------------------------------------------|\n");
		str.append("|-----------------------------" + this.nombre + "-----------------------------|\n");
		str.append("|-----------------------------------------------------------------|\n");
		str.append("|Matriz del canal:\n");
		for (i = 0; i < this.cantSimbolosEntrada; i++)
			for (j = 0; j < this.cantSimbolosSalida; j++)
				str.append("P(B" + (j+1) + "/S" + (i+1) + ") = " + this.matrizCanal[i][j]+"\n");
		
		str.append("|-----------------------------------------------------------------|\n");
		str.append("|Probabilidades de entrada del canal:\n");
		for (i = 0; i < this.cantSimbolosEntrada; i++)
			str.append("P(S" + (i + 1) + ") = " + this.probEntrada[i] +"\n");
		
		str.append("|-----------------------------------------------------------------|\n");
		str.append("|Probabilidades de salida del canal:\n");
		for (i = 0; i < this.cantSimbolosSalida; i++)
			str.append("P(B" + (i + 1) + ") = " + this.probSalida[i] + "\n");
		
		str.append("|-----------------------------------------------------------------|\n");
		str.append("|Probabilidades a-posteriori del canal:\n");
		for (i = 0; i < this.cantSimbolosEntrada; i++)
			for (j = 0; j < this.cantSimbolosSalida; j++)
				str.append("P(S" + (i+1) + "/B" + (j+1) + ") = " + this.probAPosteriori[j][i] + "\n");
		
		str.append("|-----------------------------------------------------------------|\n");
		str.append("|Entropias de entrada y salida del canal:\n");
		str.append("H(S) = " + this.entropiaAPriori + " bits\n");
		str.append("H(B) = " + this.entropiaSalida + " bits\n");
		
		str.append("|-----------------------------------------------------------------|\n");
		str.append("|Etropias a posteriori del canal:\n");
		for(i=0;i<this.cantSimbolosSalida;i++)
			str.append("H(S/B"+ (i+1) +") = " + this.entropiasAPosteriori[i] + "\n");
		
		str.append("|-----------------------------------------------------------------|\n");
		str.append("|Probabilidades simultaneas del canal:\n");
		for (i = 0; i < this.cantSimbolosEntrada; i++)
			for (j = 0; j < this.cantSimbolosSalida; j++)
				str.append("P(S" + (i+1) + ",B" + (j+1) + ") = " + this.probSimultaneas[i][j] + "\n");
		
		str.append("|-----------------------------------------------------------------|\n");
		str.append("Entropia Afin del canal H(S,B) = " + this.entropiaAfin + " bits\n");
		
		str.append("|-----------------------------------------------------------------|\n");
		str.append("Eqivocacion del canal H(S/B) = " + this.equivocacion + " bits\n");
		
		str.append("|-----------------------------------------------------------------|\n");
		str.append("Perdida del canal H(B/S) = " + this.perdida + " bits\n");
		
		str.append("|-----------------------------------------------------------------|\n");
		str.append("Informacion mutua = " + this.infoMutua + " bits\n");
		str.append("|-----------------------------------------------------------------|\n\n\n");
		
		return str.toString();
	}
	
}
