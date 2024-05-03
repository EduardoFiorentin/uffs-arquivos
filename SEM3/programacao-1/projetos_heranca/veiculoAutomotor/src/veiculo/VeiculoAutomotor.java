package veiculo;

abstract class VeiculoAutomotor {
    private double velocidadeAtual; 
    // private double quantidadeCombustivel; 
    // private double capacidadeTanque; 
    private double limiteVelocidade; 

    private boolean ligado;
    private double capacidadeAceletacao; // quanto a velocidade varia a cada aceleração ou desaceleração  
    // private double consumoPorHora; 

    
    // setters / getters
    public double getVelocidadeAtual ()            {return velocidadeAtual;}
    // public double getQuantidadeCombustivel ()      {return quantidadeCombustivel;}
    // public double getCapacidadeTanque ()           {return capacidadeTanque;}
    public double getLimiteVelocidade ()           {return limiteVelocidade;}
    public boolean isLigado ()                    {return ligado;}
    public double getCapacidadeAceleracao ()       {return capacidadeAceletacao;}
    // public double getConsumoPorHora ()             {return consumoPorHora; }
    
    
    private void setLigado (boolean ligado)                                   {this.ligado = ligado;}
    private void setLimiteVelocidade (double limiteVelocidade)                {this.limiteVelocidade = limiteVelocidade;}
    private void setCapacidadeAceleracao (double capacidadeAceleracao)        {this.capacidadeAceletacao = capacidadeAceleracao;}
    

    
    // private void setQuantidadeCombustivel (double novaQuantidade) {
    //     // quantidade mínima = 0 litros 
    //     if (novaQuantidade < 0) {
    //         mensagemErro("! Valor inválido para quantidade de combustível"); 
    //         return; 
    //     }

    //     // quantidade máxima - capacidade do tanque
    //     if (novaQuantidade > getCapacidadeTanque()) {
    //         mensagemErro("! A quantidade de combustível excede o limite do tanque! [" + getCapacidadeTanque() +" L]"); 
    //         return; 
    //     }
        
    //     quantidadeCombustivel = novaQuantidade;
    // }
    
    protected abstract boolean podeDeslocar(double distancia);
    // protected abstract void setQuantidadeCombustivel(double novaQuantidade);
    public abstract void mostrarStatus(); 
    public abstract void andar(double distancia); 
    // protected abstract boolean podeDeslocar(double distancia);

    
    private void setVelocidadeAtual (double novaVelocidade) {
        // velocidade mínima = 0
        if (novaVelocidade < 0)                             velocidadeAtual = 0;
        
        // velocidade máxima - limite de velocidade 
        else if (novaVelocidade > getLimiteVelocidade())    velocidadeAtual = getLimiteVelocidade();

        // valor válido 
        else                                                velocidadeAtual = novaVelocidade;
    }


    public VeiculoAutomotor (double limiteVelocidade, double capacidadeAceleracao) {
        setVelocidadeAtual(0);
        setLimiteVelocidade(limiteVelocidade);
        setCapacidadeAceleracao(capacidadeAceleracao);
    }
    
    
    public void acelerar () {
        // se estiver desligado
        if (!isLigado()) {
            mensagemErro("! Veículo está desligado!");
            return;
        }
        
        // se não tem combustivel
        if (!podeDeslocar(0)) {
            mensagemErro("! Veículo está sem combustivel/descarregado!");
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

    public void partida () { 
        if (isLigado()) {
            mensagemErro("! Veículo já está ligado!");
            return; 
        }

        if (!podeDeslocar(0)) {
            mensagemErro("! Veículo sem energia/combustivel!");
            return;
        }

        setLigado(true);
        mensagemSucesso("Veículo ligado!\n");
    }

    
    public void desligar () { 
        if (!isLigado()) {
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

    // métodos auxiliares 
    protected void mensagemSucesso (String mensagem) {
        System.err.println("\u001B[1;32m"+ mensagem + "\u001B[0m");
    }
    
    protected void mensagemErro (String mensagem) {
        System.err.println("\u001B[1;31m"+ mensagem + "\u001B[0m");
        
    }

}
