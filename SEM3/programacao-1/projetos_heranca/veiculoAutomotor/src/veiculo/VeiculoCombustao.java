package veiculo;

public class VeiculoCombustao extends VeiculoAutomotor {
    
    private double quantidadeCombustivel; 
    private double capacidadeTanque; 
    private double consumoPorKm;

    private double getQuantidadeCombustivel ()               {return quantidadeCombustivel;}
    private double getCapacidadeTanque()                     {return capacidadeTanque;}
    private double getConsumoPorKm()                         {return consumoPorKm;}

    private void setCapacidadeTanque(double capacidadeTanque)                           {this.capacidadeTanque = capacidadeTanque;}
    private void setConsumoPorHora(double consumoPorKmm)                                {this.consumoPorKm = consumoPorKmm;}
    
    
    public VeiculoCombustao(double limiteVelocidade, double capacidadeAceleracao, double capacidadeTanque, double consumoPorKm) {
        super(limiteVelocidade, capacidadeAceleracao); 
        setCapacidadeTanque(capacidadeTanque);
        setConsumoPorHora(consumoPorKm);
        setQuantidadeCombustivel(0);
    }
    

    // metodos obrigatórios implementados 
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


    protected boolean podeGerarForcaMotriz() {
        if (getQuantidadeCombustivel() == 0) {
            mensagemErro("! Abasteça o veiculo para deslocar!");
            return false; 
        }

        return true;
    };

    protected boolean temForcaMotrizSuficiente(double distancia) {
        if (getQuantidadeCombustivel() < getConsumoPorKm() * distancia) { 
            return false; 
        }
        return true; 
    }

    protected void removerCapacidadeMotriz(double distancia) {
        setQuantidadeCombustivel(getQuantidadeCombustivel() - (getConsumoPorKm() * distancia));
    }

    public void mostrarStatus() {
        System.out.println("----------* Veículo a combustão *----------");
        System.out.println("Ligado: " + (isLigado() ? "Sim":"Não"));
        System.out.println("Velocidade: " + getVelocidadeAtual() + '/' + getLimiteVelocidade() + "Km/h");
        System.out.println("Combustivel: " + getQuantidadeCombustivel() + " / " + getCapacidadeTanque() + " L");
        System.out.println("Consumo: " + getConsumoPorKm() + " L/km");
        System.out.println("-------------------------------------------");
    }; 


    // métodos do funcionamento da classe 
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
