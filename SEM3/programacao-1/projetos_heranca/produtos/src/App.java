import java.util.Date;
import java.time.LocalDate;

import produtos.*;

public class App {
    public static void main(String[] args) throws Exception {
        
        System.out.printf("Antes: %d", Produto.getQuantidade());
        
        LocalDate data = LocalDate.now(); 
        Eletronico elet1 = new Eletronico("Sansung Galaxi A8 5G", "1732.2235.5531", 1899.99, true, data, "Sansung", "A8");
        System.out.printf("\nDurante: %d\n", Produto.getQuantidade());
        
        System.out.println(elet1.getDataCadastro());
        
        elet1 = null; 
        
        System.out.printf("Depois: %d", Produto.getQuantidade());
    }
}