import javax.xml.catalog.CatalogException;

class Animal {
    public String nome = "generico"; 
    public void fazerSom() {
        System.out.println("Som generico de animal");
    }
}

class Cachorro extends Animal {
    public String nome = "cachorro"; 

    @Override
    public void fazerSom() {
        System.out.println("Au Au");
    }
    
    public void late() {
        
        System.out.println("latido");
    }
}



public class App {
    public static void main(String[] args) throws Exception {
        
        Animal animal = new Cachorro();
        Cachorro cachorro = new Cachorro(); 

        animal.fazerSom();
        cachorro.fazerSom();

        // cachorro.late();
        // animal.late(); 

        System.out.println(((Cachorro)animal).nome); // downcasting
        System.out.println(cachorro.nome);
    }
}
