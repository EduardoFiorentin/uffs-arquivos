package veiculo;

public class VeiculoCombustao extends VeiculoAutomotor {
    
    private double quantidadeCombustivel; 
    private double capacidadeTanque; 
    private double consumoPorKm;

    public double getQuantidadeCombustivel ()               {return quantidadeCombustivel;}
    public double getCapacidadeTanque()                     {return capacidadeTanque;}
    public double getConsumoPorKm()                         {return consumoPorKm;}

    private void setCapacidadeTanque(double capacidadeTanque)                           {this.capacidadeTanque = capacidadeTanque;}
    private void setConsumoPorHora(double consumoPorKmm)                                {this.consumoPorKm = consumoPorKmm;}
    
    protected void setQuantidadeCombustivel (double novaQuantidade) {
        if (novaQuantidade < 0) {
            mensagemErro("! Quantidade de combustivel não pode ser negativa!");
            return; 
        }
        if (novaQuantidade > getCapacidadeTanque()) {
            mensagemErro("! Nova quantidade de combustível excede a capacidade do tanque!");
        }
        quantidadeCombustivel = novaQuantidade;
        
    }
    

    public VeiculoCombustao(double limiteVelocidade, double capacidadeAceleracao, double capacidadeTanque, double consumoPorKm) {
        super(limiteVelocidade, capacidadeAceleracao); 
        setCapacidadeTanque(capacidadeTanque);
        setConsumoPorHora(consumoPorKm);
        setQuantidadeCombustivel(0);
    }

    protected boolean podeDeslocar(double distancia) {
        if (distancia == 0) {
            
        }

        if (getQuantidadeCombustivel() == 0) {
            mensagemErro("! Abasteça o veiculo para deslocar!");
            return false; 
        }
        // if ()

        return true;
    };

    public void mostrarStatus() {
        System.out.println("----------* Veículo a combustão *----------");
        System.out.println("Ligado: " + (isLigado() ? "Sim":"Não"));
        System.out.println("Velocidade: " + getVelocidadeAtual() + '/' + getLimiteVelocidade() + "Km/h");
        System.out.println("Combustivel: " + getQuantidadeCombustivel() + " / " + getCapacidadeTanque() + " L");
        System.out.println("Consumo: " + getConsumoPorKm() + " L/km");
        System.out.println("-------------------------------------------");
    }; 

    
    public void andar(double distancia) {
        if (!isLigado()) {
            mensagemErro("! Ligue o veículo para andar!");
            return; 
        }
        if (getQuantidadeCombustivel() < getConsumoPorKm() * distancia) { 
            mensagemErro("! Não há combustivel suficiente para andar por esta distância!");
        }
        if (!podeDeslocar()) {
            mensagemErro("Veículo sem combustivel");
            return; 
        }
        setQuantidadeCombustivel(getQuantidadeCombustivel() - (getConsumoPorKm() * distancia));
        mensagemSucesso("Veículo andou por " + distancia + " Km. Combustível: " + getQuantidadeCombustivel() + " / " + getCapacidadeTanque());
    }; 


    public void abastecer(double quantidadeAbastecida) {
        if (quantidadeAbastecida <= 0) {
            mensagemErro("! Não é possível abastecer quantidades negativas.");
            return;
        }
        if (quantidadeAbastecida + getQuantidadeCombustivel() > getCapacidadeTanque()) {
            mensagemErro("! A quantidade a ser abastecida não pode exceder o limite do tanque!");
            return; 
        }

        setQuantidadeCombustivel(getQuantidadeCombustivel() + quantidadeAbastecida);
    };



}
