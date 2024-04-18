import java.util.Scanner;

class PessoaF {
    String nome = ""; 
    String cpf = ""; 
    String telefone = "";
    Endereco endereco = new Endereco();

    void imprimirDados() {
        System.out.printf("Nome: %s \n\tCpf: %s \n\tTelefone: %s", nome, cpf, telefone);
        endereco.mostrarEndereco();
    }
}

class PessoaJ {
    String razaoSocial = "";
    String cnpj = ""; 
    PessoaF ceo = new PessoaF(); 
    Endereco endereco = new Endereco();

    void imprimirDados() {
        System.out.printf("Razão social: %s \n\tCnpj: %s \n\tCeo: %s", razaoSocial, cnpj, ceo.nome);
        endereco.mostrarEndereco();
    }
}

class Endereco {
    String logradouro = "";
    String numero = "";
    String complemento = "";
    String bairro = "";
    String cidade = "";
    String estado = "";
    String codigoPostal = "";

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
        System.out.printf("\nEndereço:\n\tEstado: %s\n\tCidade: %s\n\tBairro: %s, Rua %s - %s (%s)\n\tComplemento: %s\n", estado, cidade, bairro, logradouro, numero, codigoPostal, complemento);
    }
}

public class App {
    public static void main(String[] args) throws Exception {

        PessoaF pesF1 = new PessoaF(); 
        pesF1.nome = "AAAAAA";
        pesF1.cpf = "123.456.789-00";
        pesF1.telefone = "(12) 3456-7890";

        // pesF1.endereco = new Endereco(); 
        pesF1.endereco.cadastrarEndereco("E", "150", "comp", "Novo At", "São Paulo", "SP", "99790-262");

        PessoaJ empresa = new PessoaJ(); 
        empresa.ceo = pesF1; 
        empresa.razaoSocial = "XXXXXXX";
        empresa.cnpj = "46.379.400/0001-50"; 
        empresa.endereco.cadastrarEndereco("Avila", "1540", "Em frente ao posto", "Alvorada", "Chapecó", "SC", "99700-034");
        
        empresa.imprimirDados();

        // bill gates + microsoft
        PessoaF bill = new PessoaF();
        bill.nome = "William Henry Gates III";
        bill.cpf = ""; 
        bill.telefone = "+1 408 000 0000";
        bill.endereco.cadastrarEndereco("Rua", "num", "cmp", "bairro", "Medina", "Washington", "");

    }
}
