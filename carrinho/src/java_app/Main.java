

import java.util.Random;

public class Main {
    static int NUMERO_DE_DUPLAS = 100;

    public static void main(String[] args) {

        int[] arquitetura = {7, 2, 4};
        RNG redes_a[] = new RNG[NUMERO_DE_DUPLAS];
        RNG redes_b[] = new RNG[NUMERO_DE_DUPLAS];
        Duplas[] duplas = new Duplas[NUMERO_DE_DUPLAS];
        Random r = new Random();
        RNG.seed = System.currentTimeMillis();
        for (int i = 0; i < NUMERO_DE_DUPLAS; i++) {
            redes_a[i] = new RNG(arquitetura);
            redes_b[i] = new RNG(arquitetura);
            duplas[i] = new Duplas(r,i,redes_a[i],redes_b[i]);
        }

//        RNG r = new RNG(arquitetura);

//        System.out.println(Constantes.BORDA);
    }
}
//java -Djava.library.path= "C:\Users\PC\Desktop\Henrique\Inteligencia-Artificial\carrinho\src\java_app" Teste
