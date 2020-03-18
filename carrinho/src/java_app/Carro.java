
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
    char classe;
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
    public Carro(Random r, RNG rng, int id, char classe) {
        if (r == null || rng == null) {
            throw new NullPointerException("os argumentos nao podem ser nulos");
        }
        double angle = r.nextDouble() * Math.PI;
        dist = new double[5];
        centro = new P(Math.cos(angle) * (Constantes.RAIO - Constantes.COMPRIMENTO / 2), Math.sin(angle) * (Constantes.RAIO - Constantes.COMPRIMENTO / 2));
        ponta = new P(Math.cos(angle) * (Constantes.RAIO - Constantes.COMPRIMENTO), Math.sin(angle) * (Constantes.RAIO - Constantes.COMPRIMENTO));
        centro.x += Constantes.RAIO;
        centro.y += Constantes.RAIO;
        ponta.x += Constantes.RAIO;
        ponta.y += Constantes.RAIO;
        this.rng = rng;
        this.id = id;
        this.classe = classe;
    }

    public static native long update(Carro c1, Carro c2, long seed);

    public String new_carroStream() {
        return classe + "," + id + "," + centro.x + "," + centro.y + "," + ponta.x + "," + ponta.y + "\n";
    }

    public String getState2Stream() {
        return classe + "," + id + "," + ponta.x + " , " + ponta.y + ")\n" + "carros_" + classe + "[" + id + "].centro = PVector(" + centro.x + " , " + centro.y + ")\n";
    }
}
