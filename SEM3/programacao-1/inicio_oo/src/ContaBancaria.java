class ContaCorrente {
    Titular titular; 
    double saldo, limite, limiteDisponivel = 0; 
    int numeroConta = 0; 
    int digitoVerificador = 0; 
    String senha, numeroBanco = ""; 

    void abrirConta(Titular titular, 
                    int numeroConta, 
                    int digitoVerificador, 
                    String senha, 
                    String numeroBanco,
                    double salario) 
    { 
        
        // validar digito verificador
        // System.out.printf("%d\n\n", this.numeroConta % 100);
        if (numeroConta % 100 != digitoVerificador) throw new Error("Digito verificador inválido!"); 
        
        // gravar valores
        this.titular            = titular; 
        this.numeroBanco        = numeroBanco; 
        this.numeroConta        = numeroConta; 
        this.digitoVerificador  = digitoVerificador; 
        this.senha              = senha; 
        this.titular.salario    = salario; 
        
        // calcular limite 
        this.calcularLimite();
    }
    
    void calcularLimite() {
        this.limite = (this.titular.salario * 30 / 100); 
    }
    
    void resetarLimite() {
        this.limiteDisponivel = this.limite; 
    }

    boolean sacarValor(double valor) {
        if (valor >= (this.saldo + this.limiteDisponivel)) return false; 
        else {
            if (valor <= this.saldo) {
                this.saldo -= valor; 
            }
            else {
                double diferenca = valor - this.saldo; 
                this.saldo = 0; 
                this.limiteDisponivel -= diferenca; 
            }
            return true; 
        }
    }
    
    boolean depositarValor(double valor) {
        this.saldo += valor; 
        return true; 
    }
    
    boolean validarSenha(String senha) {
        if (senha == this.senha) return true; 
        return false; 
    };

    void exibirSaldo() {
        System.out.printf("Saldo em conta: ---------------\n\tConta: %d\n\tTitular: %s\n\tSaldo:%.2f, \n\tLimite Disponivel: %.2f\n", this.numeroConta, this.titular.nome, this.saldo, this.limiteDisponivel);
    }

    void exibirInformacoes() {
        System.out.printf("Conta: %d\n\tTitular: %s - %s\n\tSaldo:%.2f \n\tSalário:%.2f \n\tLimite Disponivel: %.2f \n\tLimite total: %.2f\n", this.numeroConta, this.titular.nome, this.titular.cpf, this.saldo, this.titular.salario, this.limiteDisponivel, this.limite);
    }

}

class Titular {
    String nome; 
    String cpf; 
    double salario; 
}

public class ContaBancaria {
    public static void main(String[] args) throws Exception {

        Titular titularA = new Titular(); 
        ContaCorrente contaA = new ContaCorrente(); 

        titularA.nome = "Eduardo"; 
        titularA.cpf = "038.824.330-94"; 

        contaA.abrirConta(titularA, 4432, 32, "aabn6495", "138", 1200); 

        System.out.printf("%s %d %d", contaA.titular.nome, contaA.numeroConta, contaA.digitoVerificador);

        contaA.exibirInformacoes();
        contaA.depositarValor(150.0); 
        contaA.exibirInformacoes();
        contaA.sacarValor(100.0);
        contaA.exibirInformacoes();
    }


}
