class ContaCorrente {
    private Titular titular; 
    private double saldo, limite, limiteDisponivel, saldoDevedor; 
    private int numeroConta, digitoVerificador; 
    private String senha, numeroBanco; 
    private boolean bloqueado; 


    public Titular getTitular() {return this.titular;}
    private double getSaldo() {return this.saldo;}
    private double getSaldoDevedor() {return this.saldoDevedor;}
    private double getLimite() {return this.limite;}
    private double getLimiteDisponivel() {return this.limiteDisponivel;}
    public int getNumeroConta() {return this.numeroConta;}
    public int getDigitoVerificador() {return this.digitoVerificador;}
    private String getSenha() {return this.senha;}
    private String getNumeroBanco() {return this.numeroBanco;}
    private boolean isBloqueado() {return this.bloqueado;}

    
    private void setTitular(Titular titular) {this.titular = titular;}
    private void setSaldo(double saldo) {this.saldo = saldo;}
    private void setSaldoDevedor(double saldoDevedor) {this.saldoDevedor = saldoDevedor;}
    private void setLimite(double limite) {this.limite = limite;}
    private void setLimiteDisponivel(double limiteDisponivel) {this.limiteDisponivel = limiteDisponivel;}
    private void setNumeroConta(int numeroConta) {this.numeroConta = numeroConta;}
    private void setSenha(String senha) {this.senha = senha;}
    private void setNumeroBanco(String numeroBanco) {this.numeroBanco = numeroBanco;}
    private void setBloqueado(boolean bloqueado) {this.bloqueado = bloqueado;}
    
    private void setDigitoVerificador(int digitoVerificador, int numeroConta) {

        if (numeroConta % 100 != digitoVerificador) {
            mensagemErro("Digito verificador inválido!");
            return; 
        }
        
        this.digitoVerificador = digitoVerificador;
    }
    

    public ContaCorrente (Titular titular, 
                    int numeroConta, 
                    int digitoVerificador, 
                    String senha, 
                    String numeroBanco,
                    double salario) 
    { 
        
        setTitular(titular);
        setNumeroBanco(numeroBanco);
        setNumeroConta(numeroConta);
        setDigitoVerificador(digitoVerificador, numeroConta);
        setSenha(senha);
        setBloqueado(false);
        setSaldoDevedor(0);
        setSaldo(0);

        calcularLimite();
    }

    // métodos de gerenciamento interno 
    private void calcularLimite() {
        // setLimite(titular.getSalario() * 30 / 100); 
        setLimite(getTitular().getSalario() * 30 / 100);
    }
    
    private void resetarLimite() {
        // this.limiteDisponivel = this.limite; 
        setLimiteDisponivel(getLimite());
    }

    private void removerSaldo(double valor) {
        if (valor < 0) {
            mensagemErro("Valor inválido de saldo para remover!");
        }
        if (valor > getSaldo()) {
            mensagemErro("Não há saldo suficiente para remover!");
        }
        setSaldo(getSaldo() - valor);
    }

    private void acrescentarSaldo(double valor) {
        if (valor < 0) {
            mensagemErro("Valor de saldo inválido para acrescentar!");
        }
        setSaldo(getSaldo() + valor);
    }


    
    // métodos públicos 
    public void viraMes() {
        // calcular saldo devedor 
        setSaldoDevedor( getSaldoDevedor() + (limite - limiteDisponivel));

        // recalcular limite disponível 
        calcularLimite();

        // resetar limite
        resetarLimite(); 
    }
    
    // saque usando saldo e limite
    public boolean sacarValor(double valor) {
        if (valor >= (getSaldo() + getLimiteDisponivel())) return false; 
        
        if (valor <= getSaldo()) {
            setSaldo(getSaldo() - valor);
            return true; 
        }

        double diferenca = valor - getSaldo(); 
        setSaldo(0);; 
        setLimiteDisponivel(getLimiteDisponivel() - diferenca);
        return true;



        // if (valor >= (this.saldo + this.limiteDisponivel)) return false; 
        // else {
        //     if (valor <= this.saldo) {
        //         this.saldo -= valor; 
        //     }
        //     else {
        //         double diferenca = valor - this.saldo; 
        //         this.saldo = 0; 
        //         this.limiteDisponivel -= diferenca; 
        //     }
        //     return true; 
        // }
    }
    public boolean depositarValor(double valor) {
        if (isBloqueado()) {
            return false; 
        }

        setSaldo(getSaldo() + valor);
        return true; 
    }
    
    public boolean validarSenha(String senha) {
        if (senha == getSenha()) return true; 
        return false; 
    };

    public void exibirSaldo() {
        System.out.printf("Saldo em conta: ---------------\n\tConta: %d\n\tTitular: %s\n\tSaldo:%.2f, \n\tLimite Disponivel: %.2f\n", this.numeroConta, this.titular.nome, this.saldo, this.limiteDisponivel);
    }

    public void exibirInformacoes() {
        System.out.printf("Conta: %d\n\tTitular: %s - %s\n\tSaldo:%.2f \n\tSalário:%.2f \n\tLimite Disponivel: %.2f \n\tLimite total: %.2f\n", this.numeroConta, this.titular.nome, this.titular.cpf, this.saldo, this.titular.salario, this.limiteDisponivel, this.limite);
    }
    

    // metodos estáticos 
    
    // remetente - quem transfere
    // destinatario - quem recebe a transforencia
    static public void transferirValor(ContaCorrente remetente, ContaCorrente destinatario, double valor) {
        if (remetente.isBloqueado()) {
            System.out.println("\u001B[1;31m"+ "Contas bloqueadas não podem transferir valores!" + "\u001B[0m");
            return; 
        }

        if (destinatario.isBloqueado()) {
            System.out.println("\u001B[1;31m"+ "Contas bloqueadas não podem receber transferencias!" + "\u001B[0m");
            return; 
        }
        
        if (remetente.getSaldo() < valor) {
            System.out.println("\u001B[1;31m"+ "Remetente não tem saldo suficiente!" + "\u001B[0m");
            return; 
        }

        remetente.removerSaldo(valor);
        destinatario.acrescentarSaldo(valor);
        
        System.out.println("\u001B[1;32m"+ "Transferência realizada com sucesso!" + "\u001B[0m");
    }

    // métodos auxiliares 
    void mensagemSucesso (String mensagem) {
        System.err.println("\u001B[1;32m"+ mensagem + "\u001B[0m");
    }
    
    void mensagemErro (String mensagem) {
        System.err.println("\u001B[1;31m"+ mensagem + "\u001B[0m");
        
    }
}

class Titular {
    String nome; 
    String cpf; 
    double salario; 

    public Titular(String nome, String cpf, double salario) {
        setNome(nome);
        setCpf(cpf);
        setSalario(salario);
    }


    // getters / setters 
    public void setNome(String nome) {this.nome = nome;}
    public void setCpf(String cpf) {this.cpf = cpf;}
    public void setSalario(double salario) {this.salario = salario;}
    
    public String getNome() {return this.nome;}
    public String getCpf() {return this.cpf;}
    public double getSalario() {return this.salario;}
}

public class ContaBancaria {
    public static void main(String[] args) throws Exception {

        Titular titularA = new Titular("Nome", "xxx.xxx.xxx-xx", 13050.25); 
        ContaCorrente contaA = new ContaCorrente(titularA, 123123, 23, "aabnnde", "134", 135.02); 

        // titularA.nome = "Eduardo"; 
        // titularA.cpf = "038.824.330-94"; 

        // contaA.abrirConta(titularA, 4432, 32, "aabn6495", "138", 1200); 

        System.out.printf("%s %d %d", contaA.getTitular().getNome(), contaA.getNumeroConta(), contaA.getDigitoVerificador());

        // contaA.exibirInformacoes();
        // contaA.depositarValor(150.0); 
        // contaA.exibirInformacoes();
        // contaA.sacarValor(100.0);
        // contaA.exibirInformacoes();
    }


}
