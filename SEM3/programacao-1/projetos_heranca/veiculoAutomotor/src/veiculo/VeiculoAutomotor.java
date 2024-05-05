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
    public double getVelocidadeAtual ()             {return velocidadeAtual;}
    public double getLimiteVelocidade ()            {return limiteVelocidade;}
    public boolean isLigado ()                      {return ligado;}
    public double getCapacidadeAceleracao ()        {return capacidadeAceletacao;}
    
    
    private void setLigado (boolean ligado)                                   {this.ligado = ligado;}
    private void setLimiteVelocidade (double limiteVelocidade)                {this.limiteVelocidade = limiteVelocidade;}
    private void setCapacidadeAceleracao (double capacidadeAceleracao)        {this.capacidadeAceletacao = capacidadeAceleracao;}
    private void setVelocidadeAtual (double novaVelocidade) {
        // velocidade mínima = 0
        if (novaVelocidade < 0)                             velocidadeAtual = 0;
        
        // velocidade máxima - limite de velocidade 
        else if (novaVelocidade > getLimiteVelocidade())    velocidadeAtual = getLimiteVelocidade();
    
        // valor válido 
        else                                                velocidadeAtual = novaVelocidade;
    }
    
    
    // métodos obrigatórios para classes derivadas 
    protected abstract boolean podeGerarForcaMotriz();              // verifica se tem a energia/combustível necessário 
    protected abstract boolean temForcaMotrizSuficiente(double distancia);      // verifica se tem energia suficiente para deslocar a distância 
    protected abstract void removerCapacidadeMotriz(double distancia); 
    public abstract void mostrarStatus();                           

    public VeiculoAutomotor (double limiteVelocidade, double capacidadeAceleracao) {
        setVelocidadeAtual(0);
        setLimiteVelocidade(limiteVelocidade);
        setCapacidadeAceleracao(capacidadeAceleracao);
    }

    public void andar(double distancia) {
        if (!isLigado()) {
            mensagemErro("! Ligue o veículo para andar!");
            return; 
        }
        if (!temForcaMotrizSuficiente(distancia)) { 
            mensagemErro("! Não há combustivel/carga suficiente para andar por esta distância!");
            return; 
        }
        if (!podeGerarForcaMotriz()) {
            mensagemErro("! Abasteça/carregue o veículo!");
            return; 
        }

        removerCapacidadeMotriz(distancia);
        mensagemSucesso("Veículo andou por " + distancia + " Km. Combustível: ");
    }; 
    
    
    public void acelerar () {
        // se estiver desligado
        if (!isLigado()) {
            mensagemErro("! Veículo está desligado!");
            return;
        }
        
        // se não tem combustivel
        if (!podeGerarForcaMotriz()) {
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

        if (!podeGerarForcaMotriz()) {
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
