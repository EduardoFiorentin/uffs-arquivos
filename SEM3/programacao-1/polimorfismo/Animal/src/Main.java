class Animal {
    void fazerSom() {
        System.out.println("Som genérico de animal");
    }
}

class Cachorro extends Animal {
    void fazerSom() {
        System.out.println("Latindo...");
    }
}

class Gato extends Animal {
    void fazerSom() {
        System.out.println("Miando...");
    }
}

public class Main {
    public static void main(String[] args) {
    Animal animal1 = new Cachorro(); //upcasting
    Animal animal2 = new Gato();

    // animal1.fazerSom(); 
    // animal2.fazerSom(); 

    Animal animais[] = {animal1, animal2};

    animais[0].fazerSom();
    animais[1].fazerSom();

    for (Animal animal : animais) {
        if (animal instanceof Cachorro) {
            System.out.println("Cachorro");
        }
        else if (animal instanceof Gato) {
            System.out.println("Gato");
        }
    }

    }
}