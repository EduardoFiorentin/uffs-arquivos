class PessoaF {
    private String nome; 
    private String cpf; 
    private String telefone;
    private Endereco endereco;

    public  PessoaF(String nome, String cpf, String telefone, Endereco endereco) {
        this.nome = nome; 
        this.cpf = cpf; 
        this.telefone = telefone; 
        this.endereco = endereco; 
    }

    public void imprimirDados() {
        System.out.printf("Nome: %s \n\tCpf: %s \n\tTelefone: %s", nome, cpf, telefone);
        endereco.mostrarEndereco();
    }

    public String getNome() {
        return this.nome; 
    }
}

class PessoaJ {
    private String razaoSocial;
    private String cnpj; 
    private PessoaF ceo; 
    private Endereco endereco;

    public PessoaJ (String razaoSocial, String cnpj, PessoaF ceo, Endereco endereco) {
        this.razaoSocial = razaoSocial;
        this.cnpj = cnpj;
        this.ceo = ceo;
        this.endereco = endereco;
    }

    void imprimirDados() {
        System.out.printf("Informações da empresa: \n\tRazão social: %s \n\tCnpj: %s \n\tCeo: %s", razaoSocial, cnpj, ceo.getNome());
        endereco.mostrarEndereco();
    }

}

class Endereco {
    private String logradouro;
    private String numero;
    private String complemento;
    private String bairro;
    private String cidade;
    private String estado;
    private String codigoPostal;

    public Endereco (String logradouro, String numero, String complemento, String bairro, String cidade, String estado, String codigoPostal) {
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

    String getLogradouro()                        {return this.logradouro;}
    String getNumero()                            {return this.numero;}
    String getComplemento()                       {return this.complemento;}
    String getBairro()                            {return this.bairro;}
    String getCidade()                            {return this.cidade;}
    String getEstado()                            {return this.estado;}
    String getCodigoPostal()                      {return this.codigoPostal;}

    void setLogradouro(String logradouro)         {this.logradouro = logradouro;}
    void setNumero(String numero)                 {this.numero = numero;}
    void setComplemento(String complemento)       {this.complemento = complemento;}
    void setBairro(String bairro)                 {this.bairro = bairro;}
    void setCidade(String cidade)                 {this.cidade = cidade;}
    void setEstado(String estado)                 {this.estado = estado;}
    void setCodigoPostal(String codigoPostal)     {this.codigoPostal = codigoPostal;}
}

public class PessoaFJ {
    public static void main(String[] args) throws Exception {

        Endereco enderecoBill = new Endereco("Rua E", "150", "comp", "Novo At", "São Paulo", "SP", "99790-262"); 
        PessoaF bill = new PessoaF("William Henry Gates III", "123.456.789-00", "(12) 3456-7890", enderecoBill); 


        System.out.println("------------"+enderecoBill.getComplemento());

        Endereco enderecoMicrosoft = new Endereco("One Microsoft Way", "1", "comp", "Microsoft Campus", "Redmond", "Washington", "98052-7329");
        PessoaJ microsoft = new PessoaJ("Microsoft Corporation", "46.379.400/0001-50", bill, enderecoMicrosoft);  


        microsoft.imprimirDados();
    }
}
