public class RNG {
    public int[] arquitetura;
    public double[] dna;
    public double pontuacao;
    static long seed;

    /**
     * @param arquitetura
     */
    public RNG(int[] arquitetura) {
        if (arquitetura.length < 2)
            throw new IllegalArgumentException("A arquitetura deve ser maior que 2,sendo a camaada de entrada e a camada de saida");
        this.arquitetura = arquitetura;
        seed = init(seed);
    }

    static {
        System.loadLibrary("RNG");
    }

    private native long init(long seed);

}
