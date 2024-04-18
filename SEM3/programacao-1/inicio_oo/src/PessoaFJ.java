class PessoaF {
    String nome; 
    String cpf; 
    String telefone;
    Endereco endereco = new Endereco();

    void imprimirDados() {
        System.out.printf("Nome: %s \n\tCpf: %s \n\tTelefone: %s", nome, cpf, telefone);
        endereco.mostrarEndereco();
    }
}

class PessoaJ {
    String razaoSocial;
    String cnpj; 
    PessoaF ceo = new PessoaF(); 
    Endereco endereco = new Endereco();

    void imprimirDados() {
        System.out.printf("Informações da empresa: \n\tRazão social: %s \n\tCnpj: %s \n\tCeo: %s", razaoSocial, cnpj, ceo.nome);
        endereco.mostrarEndereco();
    }
}

class Endereco {
    String logradouro;
    String numero;
    String complemento;
    String bairro;
    String cidade;
    String estado;
    String codigoPostal;

    void cadastrarEndereco(String logradouro, String numero, String complemento, String bairro, String cidade, String estado, String codigoPostal) {
        this.logradouro =       logradouro;
        this.numero =           numero;
        this.complemento =      complemento;
        this.bairro =           bairro;
        this.cidade =           cidade;
        this.estado =           estado;
        this.codigoPostal =     codigoPostal;
    }

    void mostrarEndereco() {
        System.out.printf("\nEndereço:\n\tEstado: %s\n\tCidade: %s\n\tBairro: %s, %s - %s (%s)\n\tComplemento: %s\n", estado, cidade, bairro, logradouro, numero, codigoPostal, complemento);
    }
}

public class PessoaFJ {
    public static void main(String[] args) throws Exception {

        PessoaF bill = new PessoaF(); 
        bill.nome = "William Henry Gates III";
        bill.cpf = "123.456.789-00";
        bill.telefone = "(12) 3456-7890";

        // pesF1.endereco = new Endereco(); 
        bill.endereco.cadastrarEndereco("Rua E", "150", "comp", "Novo At", "São Paulo", "SP", "99790-262");

        PessoaJ microsoft = new PessoaJ(); 
        microsoft.ceo = bill; 
        microsoft.razaoSocial = "Microsoft Corporation";
        microsoft.cnpj = "46.379.400/0001-50"; 
        microsoft.endereco.cadastrarEndereco("One Microsoft Way", "1", "", "Microsoft Campus", "Redmond", "Washington", "98052-7329");
        
        microsoft.imprimirDados();
    }
}
