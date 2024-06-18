import javax.xml.catalog.CatalogException;

class Animal {
    public void fazerSom() {
        System.out.println("Som generico de animal");
    }
}

class Cachorro extends Animal {
    @Override
    public void fazerSom() {
        System.out.println("Au Au");
    }
}

public class Teste {
    public static void main(String[] args) {
        
        Animal animal = new Animal();
        Cachorro cachorro = new Cachorro(); 

        animal.fazerSom();
        cachorro.fazerSom();

    }
}
