
import java.util.Random;

public class Carro {
    static class P {
        public P(double x, double y) {
            this.x = x;
            this.y = y;
        }

        protected double x, y;
    }

    static {
        System.loadLibrary("Carro");
    }

    public P centro;
    public P ponta;
    RNG rng;
    int classe;
    int id;// index
    int alive;
    double v;// velocidade
    double av;// velocidade angular
    double fe, fd;
    double dist[];
    double tempo_parado;
    double tempoTotal = 0;
    double points;

    /**
     * @param r   gerar numero aleatorios
     * @param rng rede neural
     */
    public Carro(Random r, RNG rng, int id) {
        if (r==null || rng == null){
            throw new NullPointerException("os argumentos nao podem ser nulos");
        }
        double angle = r.nextDouble() * Math.PI;
        dist = new double[5];
        centro = new P(Math.cos(angle) * Constantes.RAIO, Math.sin(angle) * Constantes.RAIO);
        ponta = new P(Math.cos(angle) * (Constantes.RAIO - Constantes.COMPRIMENTO / 2), Math.sin(angle) * (Constantes.RAIO - Constantes.COMPRIMENTO / 2));
        this.rng = rng;
        this.id = id;

    }

    public static native void update(Carro c1, Carro c2);

}
