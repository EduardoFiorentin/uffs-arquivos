package produtos;

import java.time.LocalDate;
import java.util.Date;

public class Eletronico extends Produto {
    private String marca, modelo; 


    public String getMarca() { return this.marca; }
    public String getModelo() { return this.modelo; }

    public void setMarca(String marca) { this.marca = marca; }
    public void setModelo(String modelo) { this.modelo = modelo; }
    
    
    public Eletronico(String nome, String id, double preco, boolean disponivel, LocalDate dataCadastro, String marca, String modelo) {
        super(nome, id, preco, disponivel, dataCadastro); 
        setMarca(marca);
        setModelo(modelo);

    }
}
