import java.util.Date;
import java.time.LocalDate;

import produtos.*;

public class App {
    public static void main(String[] args) throws Exception {
        
        System.out.printf("Antes: %d", Produto.getQuantidade());
        
        LocalDate data = LocalDate.now(); 
        Eletronico elet1 = new Eletronico("Sansung Galaxi A8 5G", "1732.2235.5531", 1899.99, true, data, "Sansung", "A8");
        Eletronico elet2 = new Eletronico("Geladeira", "1732.2235.5532", 4899.99, true, data, "Brastemp", "BRM442HB");
        
        System.out.printf("\nDurante: %d\n", Produto.getQuantidade());
        
        elet1.imprimeProduto();
        elet2.imprimeProduto();

        elet1 = null; 
        System.out.printf("\nDepois: %d", Produto.getQuantidade());
    }
}

// Uma classe abstract pai denominada classe Produto, em sua generalização para
// especializações, possui um método static que retorna a quantidade de estoque de
// produtos em geral, não especificadamente de um produto em si. Não há possibilidade
// de instanciar um produto por esta classe e sim por suas derivações.

// Nesta classe Produto, algumas características são notáveis:
// A quantidade de estoque é um atributo static e o seu valor representa a quantidade
// geral de produtos no estoque - que representa a quantidade de objetos instanciados
// de produtos.

// O nome do produto é um atributo String private e é uma constante (final). Deve ser
// possível pelas derivações saber o nome do produto.

// Os produtos, sejam quais forem, são herança da classe pai Produto.

// No construtor da sua classe filha ou classes filhas que representam produtos em si,
// incremente o estoque.

// No finalizador de sua classe (método referenciado no material teórico da disciplina),
// decremente o estoque de produtos.

// Crie produtos diversos por herança. Dê uma propriedade de atributo particular a este
// produto, e use um construtor filho para alimentar este atributo. Não esqueça de
// referenciar o super, construtor da classe pai Produto.

// Instancie na sua aplicação diversos objetos de produtos distintos e ao final exiba o
// estoque de produtos pelos métodos da classe Pai, estáticos.
// Teste o acréscimo e o decréscimo de estoque. Force a finalização do objeto e atribua
// null a ele para que “morra”.

// Para este fim, faça uso de declarações das classes em um pacote e arquivos distintos
// e sua aplicação deve importar este pacote e classes.

// Não deixe de evidenciar o encapsulamento na sua implementação!