class ContaCorrente {
    private Titular titular; 
    private double saldo, limite, limiteDisponivel, saldoDevedor; 
    private int numeroConta, digitoVerificador; 
    private String senha, numeroBanco; 
    private boolean bloqueado; 


    private Titular getTitular()            {return this.titular;}
    private double getSaldo()               {return this.saldo;}
    private double getSaldoDevedor()        {return this.saldoDevedor;}
    private double getLimite()              {return this.limite;}
    private double getLimiteDisponivel()    {return this.limiteDisponivel;}
    private int getNumeroConta()            {return this.numeroConta;}
    private int getDigitoVerificador()      {return this.digitoVerificador;}
    private String getSenha()               {return this.senha;}
    private String getNumeroBanco()         {return this.numeroBanco;}
    private boolean isBloqueado()           {return this.bloqueado;}

    
    private void setTitular(Titular titular)                        {this.titular = titular;}
    private void setSaldo(double saldo)                             {this.saldo = saldo;}
    private void setSaldoDevedor(double saldoDevedor)               {this.saldoDevedor = saldoDevedor;}
    private void setLimite(double limite)                           {this.limite = limite;}
    private void setLimiteDisponivel(double limiteDisponivel)       {this.limiteDisponivel = limiteDisponivel;}
    private void setNumeroConta(int numeroConta)                    {this.numeroConta = numeroConta;}
    private void setSenha(String senha)                             {this.senha = senha;}
    private void setNumeroBanco(String numeroBanco)                 {this.numeroBanco = numeroBanco;}
    private void setBloqueado(boolean bloqueado)                    {this.bloqueado = bloqueado;}
    
    private void setDigitoVerificador(int digitoVerificador, int numeroConta) {

        if (numeroConta % 100 != digitoVerificador) {
            mensagemErro("Digito verificador inválido!");
            throw new Error("Digito verificador inválido"); 
        }
        
        this.digitoVerificador = digitoVerificador;
    }
    

    public ContaCorrente (Titular titular, 
                    int numeroConta, 
                    int digitoVerificador, 
                    String senha, 
                    String numeroBanco) 
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
        setLimiteDisponivel(getLimite());
    }

    // métodos internos  
    private void calcularLimite() {
        setLimite(getTitular().getSalario() * 30 / 100);
    }
    
    private void resetarLimite() {
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
    public void manutencaoDiaria() {
        setSaldoDevedor(getSaldoDevedor() + (getSaldoDevedor() / 100 * 0.5));
    }

    
    public void viraMes() {
        // adicionar o valor gasto no crédito a fatura
        setSaldoDevedor( getSaldoDevedor() + (getLimite() - getLimiteDisponivel()));
    
        calcularLimite();

        resetarLimite(); 
    }
    
    // pagamento usando saldo e limite
    public void pagamentoDebito(double valor, String senha) {
        if (!validarSenha(senha)) {
            mensagemErro("Senha incorreta!");
            return; 
        }
        if (isBloqueado()) {
            mensagemErro("Esta conta está bloqueada e não pode efetuar pagamentos!");
            return; 
        }
        if (valor > getSaldo()) {
            mensagemErro("Saldo insuficiente para realizar o pagamento!");
            return;
        }; 
        if (valor < 0) {
            mensagemErro("Valor do pagamento não pode ser negativo!");
            return; 
        }; 
        
        removerSaldo(valor);
        mensagemSucesso("Pagamento realizado com sucesso!"); 
        
    }

    public void pagamentoCredito(double valor, String senha) {
        if (!validarSenha(senha)) {
            mensagemErro("Senha incorreta!");
            return; 
        }
        if (isBloqueado()) {
            mensagemErro("Esta conta está bloqueada e não pode efetuar pagamentos!");
        }
        if (valor > getLimiteDisponivel()) {
            mensagemErro("Crédito insuficiente para realizar o pagamento!");
            return; 
        }; 
        if (valor < 0) {
            mensagemErro("Valor do pagamento não pode ser negativo!");
            return; 
        }; 
        
        setLimiteDisponivel(getLimiteDisponivel() - valor);
        mensagemSucesso("Pagamento realizado com sucesso!");
    } 

    public void depositarValor(double valor) {
        if (isBloqueado()) {
            mensagemErro("Esta conta está bloqueada e não pode receber depositos!");
            return;
        }
        if (valor < 0) {
            mensagemErro("Valor do deposito não pode ser negativo!");
            return; 
        }; 

        acrescentarSaldo(valor);
        mensagemSucesso("O valor de R$" + valor + " foi depositado com sucesso!");
    }
    
    public void sacarValor(double valor, String senha) {
        if (!validarSenha(senha)) {
            mensagemErro("Senha incorreta!");
            return; 
        }
        if (isBloqueado()) {
            mensagemErro("Esta conta está bloqueada e não pode efetuar saques!");
            return; 
        }
        if (valor > getSaldo()) {
            mensagemErro("Saldo insuficiente para realizar o saque!");
            return;
        }; 
        if (valor < 0) {
            mensagemErro("Valor de saque não pode ser negativo!");
            return; 
        }; 
        
        removerSaldo(valor);
        mensagemSucesso("Saque realizado com sucesso!");
    }

    public void pagarFatura() {
        
        if (getSaldoDevedor() == 0) {
            mensagemErro("Não há fatura para ser paga!");
            return;
        }
        if (getSaldo() < getSaldoDevedor()) {
            mensagemErro("Saldo insuficiente para pagar a fatura!");
            return; 
        }

        removerSaldo(getSaldoDevedor());
        setSaldoDevedor(0);
        mensagemSucesso("Fatura paga com sucesso!");
    }

    public boolean validarSenha(String senha) {
        if (senha == getSenha()) return true; 
        return false; 
    };

    public void exibirSaldo() {
        System.out.printf("Saldo em conta: ---------------\n\tConta: %d\n\tTitular: %s\n\tSaldo:%.2f, \n\tLimite Disponivel: %.2f\n", this.numeroConta, this.titular.nome, this.saldo, this.limiteDisponivel);
    }

    public void exibirInformacoes() {
        System.out.printf("Conta: %d\n\tTitular: %s - %s\n\tSaldo:%.2f \n\tSalário:%.2f \n\tLimite Disponivel: %.2f \n\tLimite total: %.2f\n\tFatura: %.2f\n", 
        getNumeroConta(), 
        getTitular().getNome(), 
        getTitular().getCpf(), 
        getSaldo(), 
        getTitular().getSalario(), 
        getLimiteDisponivel(), 
        getLimite(),
        getSaldoDevedor()
        );
    }
    

    
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
            System.out.println("\u001B[1;31m"+ "Remetente não possui saldo suficiente para transferencia!" + "\u001B[0m");
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
    private void setNome(String nome) {this.nome = nome;}
    private void setCpf(String cpf) {this.cpf = cpf;}
    private void setSalario(double salario) {this.salario = salario;}
    
    public String getNome() {return this.nome;}
    public String getCpf() {return this.cpf;}
    public double getSalario() {return this.salario;}
}

public class ContaBancaria {
    public static void main(String[] args) throws Exception {

        Titular titularA = new Titular("NomeA", "xxx.xxx.xxx-xx", 1000); 
        ContaCorrente contaA = new ContaCorrente(titularA, 123123, 23, "aabnnde", "134"); 

        Titular titularB = new Titular("NomeB", "yyy.yyy.yyy-yy", 10000); 
        ContaCorrente contaB = new ContaCorrente(titularB, 4937, 37, "abbnnde", "134"); 


        contaA.exibirInformacoes();
        contaB.exibirInformacoes();
        
        contaA.depositarValor(1000);
        contaB.depositarValor(10000);
        
        contaA.exibirInformacoes();
        contaB.exibirInformacoes();


        contaA.pagamentoDebito(500, "aabnnde");
        contaA.pagamentoDebito(300, "aabnnde");

        ContaCorrente.transferirValor(contaA, contaB, 200);

        contaA.pagamentoCredito(200, "aabnnde");

        contaB.sacarValor(1000, "abbnnde");

        
        contaA.exibirInformacoes();
        contaB.exibirInformacoes();
        
        System.out.println("\n\nVirada do Mês ----------------------------------------------------------");
        contaA.viraMes();
        contaB.viraMes();

        contaA.depositarValor(1000);
        contaB.depositarValor(10000);
        
        contaA.exibirInformacoes();
        contaB.exibirInformacoes();
        
        System.out.println("\n\nManutenção diária ----------------------------------------------------------");
        contaA.manutencaoDiaria();
        contaB.manutencaoDiaria();
        
        contaA.exibirInformacoes();
        contaB.exibirInformacoes();
        
        System.out.println("\n\nPagamento da fatura ----------------------------------------------------------");
        contaA.pagarFatura();
        contaB.pagarFatura();

        contaA.exibirInformacoes();
        contaB.exibirInformacoes();
    }
}


// Desenvolver um sistema simplificado de banco em JAVA para gerenciar contas
// correntes. O sistema deverá permitir a criação de novas contas, bem como operações
// de depósito, saque e transferência de valores entre contas.
// 1. Abertura de Conta: O sistema deve validar o número da conta e seu dígito
// verificador antes de criar uma nova conta. A validação do dígito verificador segue a
// regra de que o resto da divisão do número da conta por 100 deve corresponder ao
// dígito verificador;
// 2. Considerar um limite de crédito para a conta de 30% do salário de seu titular;
// 3. Operações Financeiras:
// a. Depósito: Adicionar um valor ao saldo da conta;
// b. Saque: Retirar um valor do saldo da conta após a validação da senha do
// titular. Não é possível efetuar saques sem saldo ou saque maior que o saldo
// da conta e o seu limite;
// c. Transferência: Permitir a transferência de valores entre contas. A operação
// deve ser atômica, e a transferência só será realizada se os dados da conta de
// origem e destino estiverem corretos e a senha for validada para a conta de
// origem;
// 4. Manutenção Diária: Aplicar um juros de 0,5% sobre o saldo devedor da conta (se
// houver uso do limite).
//  Não utilizar construtores na classe ContaCorrente. As operações sobre a conta
// devem ser realizadas por métodos;
//  Não é necessário implementar funcionalidade para emissão de extratos bancários;
//  A passagem de parâmetros em Java é por cópia para tipos primitivos e por referência
// para objetos;
//  No método main, instancie pelo menos duas contas correntes e demonstre as
// operações de depósito, saque e transferência;
//  Considere o titular da conta como uma associação de classes Titular e
// ContaCorrente;
//  Exiba o saldo atual de cada conta após as operações. 