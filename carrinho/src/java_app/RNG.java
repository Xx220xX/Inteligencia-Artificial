
public class RNG {
    public int arquitetura[];
    public double dna[];
    public double pontuacao;

    /**
     * @param arquitetura
     */
    public RNG(int []arquitetura) {
        if(arquitetura.length<2)throw new IllegalArgumentException("A arquitetura deve ser maior que 2,sendo a camaada de entrada e a camada de saida");
        this.arquitetura = arquitetura;
        dna = new double[0];
        init();
        for (double d:dna) System.out.print(d+" ");
        System.out.println(dna.length);
    }

    static {
        System.loadLibrary("RNG");
    }

    private native void init();

}
