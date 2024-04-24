import java.util.Scanner;

class Veiculo {
    private double velocidadeAtual; 
    private double quantidadeCombustivel; 
    private double capacidadeTanque; 
    private double limiteVelocidade; 

    private boolean ligado;
    private double capacidadeAceletacao; // quanto a velocidade varia a cada aceleração ou desaceleração  
    private double consumoPorHora; 

    
    // setters / getters
    public double getVelocidadeAtual ()            {return velocidadeAtual;}
    public double getQuantidadeCombustivel ()      {return quantidadeCombustivel;}
    public double getCapacidadeTanque ()           {return capacidadeTanque;}
    public double getLimiteVelocidade ()           {return limiteVelocidade;}
    public boolean getLigado ()                    {return ligado;}
    public double getCapacidadeAceleracao ()       {return capacidadeAceletacao;}
    public double getConsumoPorHora ()             {return consumoPorHora; }
    
    
    private void setLigado (boolean ligado)                                   {this.ligado = ligado;}
    private void setCapacidadeTanque (double capacidadeTanque)                {this.capacidadeTanque = capacidadeTanque;}
    private void setLimiteVelocidade (double limiteVelocidade)                {this.limiteVelocidade = limiteVelocidade;}
    private void setCapacidadeAceleracao (double capacidadeAceleracao)        {this.capacidadeAceletacao = capacidadeAceleracao;}
    private void setConsumoPorHora (double consumoPorHora)                     {this.consumoPorHora = consumoPorHora; }
    

    private void setQuantidadeCombustivel (double novaQuantidade) {
        // quantidade mínima = 0 litros 
        if (novaQuantidade < 0) {
            mensagemErro("! Valor inválido para quantidade de combustível"); 
            return; 
        }

        // quantidade máxima - capacidade do tanque
        if (novaQuantidade > getCapacidadeTanque()) {
            mensagemErro("! A quantidade de combustível excede o limite do tanque! [" + getCapacidadeTanque() +" L]"); 
            return; 
        }
        
        quantidadeCombustivel = novaQuantidade;
    }
    
    private void setVelocidadeAtual (double novaVelocidade) {
        // velocidade mínima = 0
        if (novaVelocidade < 0)                             velocidadeAtual = 0;
        
        // velocidade máxima - limite de velocidade 
        else if (novaVelocidade > getLimiteVelocidade())    velocidadeAtual = getLimiteVelocidade();

        // valor válido 
        else                                                velocidadeAtual = novaVelocidade;
    }


    public Veiculo (double capacidadeTanque) {

        setCapacidadeTanque(capacidadeTanque);
        setQuantidadeCombustivel(0);
        setVelocidadeAtual(0);
        setLimiteVelocidade(120);
        setCapacidadeAceleracao(20);
        setConsumoPorHora(16);
    }
    
    
    public void acelerar () {
        // se estiver desligado
        if (!getLigado()) {
            mensagemErro("! Veículo está desligado!");
            return;
        }
        
        // se não tem combustivel
        if (getQuantidadeCombustivel() == 0) {
            mensagemErro("! Veículo está sem combustivel!");
            return;    
        }
        
        // se atingiu a velocidade máxima 
        if (getVelocidadeAtual() >= getLimiteVelocidade()) {
            mensagemErro("! Velocidade máxima atingida!");
            return;
        }

        setVelocidadeAtual( getVelocidadeAtual() + getCapacidadeAceleracao() );
        mensagemSucesso("Acelerando... ["+getVelocidadeAtual()+"/"+getLimiteVelocidade()+"] km/h");
    }
    
    public void desacelerar () {
        
        if ((getVelocidadeAtual() - getCapacidadeAceleracao()) <= 0 && getVelocidadeAtual() == 0) {
            mensagemErro("! Velocidade mínima atingida!");
            return; 
        }
        
        setVelocidadeAtual( getVelocidadeAtual() - getCapacidadeAceleracao() );
        mensagemSucesso("Desacelerando... ["+getVelocidadeAtual()+"/"+getLimiteVelocidade()+"] km/h");
    }

    public void abastecer () {
        
        if (getVelocidadeAtual() > 0) {
            mensagemErro("! Pare o veículo para abastecer.");
            return; 
        }
        if (getLigado()) {
            mensagemErro("! Desligue o veículo para abastecer.");
            return; 
        }
        

        Scanner inputUsuario = new Scanner(System.in); 
        double quantidadeAbastecida = 0; 

        System.out.println("----------* Abastecimento *-----------");
        System.out.println("Quanto combustível deseja abastecer? :");
        quantidadeAbastecida = inputUsuario.nextDouble(); 

        double qtdCombustivelAnterior = getQuantidadeCombustivel();
        setQuantidadeCombustivel(getQuantidadeCombustivel() + quantidadeAbastecida);
        
        // confirmação do abastecimento 
        if (getQuantidadeCombustivel() > qtdCombustivelAnterior) {
            mensagemSucesso("Abastecendo... ["+getQuantidadeCombustivel()+"/"+getCapacidadeTanque()+"]");
        }
    }

    public void partida () { 
        if (getLigado()) {
            mensagemErro("! Veículo já está ligado!");
            return; 
        }

        if (getQuantidadeCombustivel() == 0) {
            mensagemErro("! Veículo está sem combustivel!");
            return;    
        }

        setLigado(true);
        mensagemSucesso("Veículo ligado!\n");
    }

    
    public void desligar () { 
        if (!getLigado()) {
            mensagemErro("! Veículo já está desligado.");
            return; 
        }
        if (getVelocidadeAtual() > 0) {
            mensagemErro("! Desacelere o veículo para desligar.");
            return; 
        }
        
        setLigado(false);
        mensagemSucesso("Veículo desligado!\n");
        
    }

    // simula 1 hora de deslocamento - consumo de 16L de combustível 
    public void andar () {
        if (!getLigado()) {
            mensagemErro("! Ligue o veículo!");
            return; 
        }
        if (getQuantidadeCombustivel() < getConsumoPorHora()) {
            mensagemErro("O combustível restante não é suficiente para andar por 1 hora. ["+getQuantidadeCombustivel()+"/"+getCapacidadeTanque()+"]");
            return; 
        }

        setQuantidadeCombustivel( getQuantidadeCombustivel () - getConsumoPorHora () );
        mensagemSucesso("Veículo andou por 1 hora... Combustível:["+getQuantidadeCombustivel()+"/"+getCapacidadeTanque()+"]");
    }

    // mostra velocidade atual e qtd de combustível
    public void mostrarStatus () {
        System.err.println(
            "\nVelocidade Atual: [" + getVelocidadeAtual() + " / " + getLimiteVelocidade() + "] Km/h" +
            "\nQuantidade de combustível: [" + getQuantidadeCombustivel() + " / " + getCapacidadeTanque() + "] L"
        );
    }


    // métodos auxiliares 
    public void mensagemSucesso (String mensagem) {
        System.err.println("\u001B[1;32m"+ mensagem + "\u001B[0m");
    }
    
    public void mensagemErro (String mensagem) {
        System.err.println("\u001B[1;31m"+ mensagem + "\u001B[0m");
        
    }

}

public class VeiculoAutomotor {
    public static void main(String[] args) {

        Veiculo veiculo = new Veiculo(120); 
        boolean rodando = true; 
        Scanner charSc = new Scanner(System.in); 
        Scanner doubleSc = new Scanner(System.in);
        char opcao; 

        do {

            System.err.println("OPÇÕES: \n\t[0] - Finalizar programa\n\t[1] - Ligar veículo\n\t[2] - Desligar veículo\n\t[3] - Acelerar\n\t[4] - Desacelerar\n\t[5] - Abastecer\n\t[6] - Rodar por 1 hora\n\t[7] - Mostrar Informações\n");
            
            opcao = charSc.nextLine().charAt(0);


            switch (opcao) {
                case '0': // finaliza o programa
                    rodando = false; 
                    break;
                    
                case '1':
                    System.out.println("- Opção de ligar veículo.");
                    veiculo.partida();
                    break;

                case '2':
                    System.out.println("- Opção de desligar veículo.");
                    veiculo.desligar();
                    break;

                case '3':
                    System.out.println("- Opção de acelerar.");
                    veiculo.acelerar();
                    break;

                case '4':
                    System.out.println("- Opção de desacelerar.");
                    veiculo.desacelerar();
                    break;

                case '5':
                    System.out.println("- Opção de abastecer.");
                    veiculo.abastecer();
                    break;
                    
                case '6':
                    System.out.println("- Opção de rodar por 1 hora.");
                    veiculo.andar();
                    break;
                    
                case '7':
                    System.out.println("- Opção de mostrar status do veículo.");
                    veiculo.mostrarStatus();
                    break;
                    
            
                default:
                    System.err.println("\u001B[1;31m-------* Opção inválida! *-------\u001B[0m");
                    break;
            }

        } while (rodando); 


        veiculo.mostrarStatus();
        System.err.println("Programa finalizado!");
        
        charSc.close();
        doubleSc.close();

    }
}


// Estudo de caso prático 3
// Implementar uma classe VeiculoAutomotor em Java, aplicando os conceitos de
// abstração e encapsulamento para modelar de forma simplificada um veículo automotor,
// controlando seu estado interno e expondo operações seguras.

// Você foi designado para desenvolver uma parte do sistema de uma montadora de
// veículos, que necessita de uma representação de veículos automotores. Cada veículo
// deve ser capaz de acelerar, desacelerar, e abastecer, além de manter controle sobre
// seu estado atual, como velocidade e quantidade de combustível.


// Requisitos:
// Atributos da classe : velocidadeAtual, quantidadeCombustivel, e capacidadeTanque,
// dentre outros que julgar necessário para controlar o “estado interno do objeto”.
// Ao ser construído, uma mensagem inicial deve ser enviada ao objeto inicializa a
// capacidade do tanque e define a quantidade inicial de combustível e a velocidade atual
// como zero. O limite de velocidade do veículo é de 120 km por hora.


// Outros métodos:
// Acelerar (aumentando a velocidade em uma quantidade específica de 20 km por hora).
// Desacelerar (diminuindo a velocidade em uma quantidade específica de 20 km por
// hora).
// Abastecer.
// Obter a velocidade atual e a quantidade de combustível.
// Dar partida e desligar o veículo.
// Andar com o veículo, sabendo que o consumo de combustível é de 16 km por hora e
// que enquanto andando ele consome combustível. O método andar prevê andar com o
// veículo por 1 hora. E então simule um estacionamento e parada do veículo.

// Faça um laço de menu de operação do veículo com cada opção que julgar necessária
// e “ande com o veículo” e observe os acontecimentos sobre a sua abstração. 
