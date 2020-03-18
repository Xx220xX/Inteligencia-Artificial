import java.util.Random;

public class Duplas {
    private Carro c1, c2;
    public long seed;
    public int id;
    public Duplas(Random r, int id, RNG rnga, RNG rngb) {
        this.c1 = new Carro(r, rnga, id, 'a');
        this.c2 = new Carro(r, rngb, id, 'b');
        this.id =  id;
    }


    public String getUpdate() {
        return c1.getState2Stream() + c2.getState2Stream();
    }

    public String getInit() {
        return c1.new_carroStream() + c2.new_carroStream();
    }

    public void update() {
        seed = Carro.update(c1, c2, seed);
    }
}
