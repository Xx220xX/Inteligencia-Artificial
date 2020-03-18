

import java.io.*;
import java.util.*;

public class Main {
    static int NUMERO_DE_DUPLAS = 100;
    static String init = "..\\..\\stream\\init.car";
    static String update = "..\\..\\stream\\updade.car";
    static Map<Integer, Duplas> buff = new HashMap<>(NUMERO_DE_DUPLAS);

    public static void main(String[] args) throws IOException {
        int[] arquitetura = {7, 2, 4};
        RNG redes_a[] = new RNG[NUMERO_DE_DUPLAS];
        RNG redes_b[] = new RNG[NUMERO_DE_DUPLAS];
        Duplas[] duplas = new Duplas[NUMERO_DE_DUPLAS];
        initDuplas(duplas, redes_a, redes_b, arquitetura);

        LinkedList<Duplas> all = new LinkedList<>();
        all.addAll(Arrays.asList(duplas));

        while (all.size()>0){
            Duplas a = all.getFirst();
            a.update();
            buff.put(a.id,a);
            if(buff.size()>2)save();
        }
        System.out.println("end");
//        RNG r = new RNG(arquitetura);

//        System.out.println(Constantes.BORDA);
    }

    public static void initDuplas(Duplas[] duplas, RNG[] redes_a, RNG[] redes_b, int[] arquitetura) throws IOException {
        File f = new File(init);
        BufferedWriter bf = new BufferedWriter(new FileWriter(f));
        Random r = new Random();
        RNG.seed = System.currentTimeMillis();
        for (int i = 0; i < NUMERO_DE_DUPLAS; i++) {
            redes_a[i] = new RNG(arquitetura);
            redes_b[i] = new RNG(arquitetura);
            duplas[i] = new Duplas(r, i, redes_a[i], redes_b[i]);
            bf.write(duplas[i].getInit());
            bf.newLine();
            bf.flush();
        }
        bf.close();
    }

    public static void updateDuplas(Duplas d) {
        buff.put(d.id, d);
    }

    public synchronized static void save() {
        synchronized (buff) {
            File f = new File(update);
            try {
                BufferedWriter bf = new BufferedWriter(new FileWriter(f));
                for (Duplas d : buff.values()) {
                    bf.write(d.getUpdate());
                    bf.newLine();
                    bf.flush();
                }
                bf.close();
            } catch (IOException e) {
                e.printStackTrace();

            }
        }
    }
}
//java -Djava.library.path= "C:\Users\PC\Desktop\Henrique\Inteligencia-Artificial\carrinho\src\java_app" Teste
