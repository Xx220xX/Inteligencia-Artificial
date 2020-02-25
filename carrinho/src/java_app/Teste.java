

import java.lang.reflect.Field;
import java.util.Random;

public class Teste {
    public static void main(String[] args) {
        int[] arquitetura = {7,2,4};
        Carro c1 = new Carro(new Random(),new RNG(arquitetura),0);
        Carro c2 = new Carro(new Random(),new RNG(arquitetura),1);
        Class c = Carro.class;

        Carro.update(c1,c2);

//        System.out.println(Constantes.BORDA);
    }
}
//java -Djava.library.path= "C:\Users\PC\Desktop\Henrique\Inteligencia-Artificial\carrinho\src\java_app" Teste
