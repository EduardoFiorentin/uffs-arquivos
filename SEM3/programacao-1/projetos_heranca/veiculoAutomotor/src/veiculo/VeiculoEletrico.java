package veiculo;

public class VeiculoEletrico extends VeiculoAutomotor {
    
    private double quantidadeCarga; 
    private double capacidadeBateria; 
    private double consumoPorKm;

    private double getQuantidadeCarga ()               {return quantidadeCarga;}
    private double getCapacidadeBateria()                     {return capacidadeBateria;}
    private double getConsumoPorKm()                         {return consumoPorKm;}

    private void setCapacidadeBateria(double capacidadeTanque)                           {this.capacidadeBateria = capacidadeTanque;}
    private void setConsumoPorHora(double consumoPorKmm)                                {this.consumoPorKm = consumoPorKmm;}
    
    
    public VeiculoEletrico(double limiteVelocidade, double capacidadeAceleracao, double capacidadeBateria, double consumoPorKm) {
        super(limiteVelocidade, capacidadeAceleracao); 
        setCapacidadeBateria(capacidadeBateria);
        setConsumoPorHora(consumoPorKm);
        setQuantidadeCarga(0);
    }
    

    // metodos obrigatórios implementados 
    protected void setQuantidadeCarga (double novaQuantidade) {
        if (novaQuantidade < 0) {
            mensagemErro("! Quantidade de bateria não pode ser negativa!");
            return; 
        }
        if (novaQuantidade > getCapacidadeBateria()) {
            mensagemErro("! Nova quantidade de carga excede a capacidade da bateria!");
        }
        quantidadeCarga = novaQuantidade;
    }


    protected boolean podeGerarForcaMotriz() {
        if (getQuantidadeCarga() == 0) {
            mensagemErro("! Abasteça o veiculo para deslocar!");
            return false; 
        }

        return true;
    };

    protected boolean temForcaMotrizSuficiente(double distancia) {
        if (getQuantidadeCarga() < getConsumoPorKm() * distancia) { 
            return false; 
        }
        return true; 
    }

    protected void removerCapacidadeMotriz(double distancia) {
        setQuantidadeCarga(getQuantidadeCarga() - (getConsumoPorKm() * distancia));
    }

    public void mostrarStatus() {
        System.out.println("----------* Veículo a combustão *----------");
        System.out.println("Ligado: " + (isLigado() ? "Sim":"Não"));
        System.out.println("Velocidade: " + getVelocidadeAtual() + '/' + getLimiteVelocidade() + "Km/h");
        System.out.println("Combustivel: " + getQuantidadeCarga() + " / " + getCapacidadeBateria() + " L");
        System.out.println("Consumo: " + getConsumoPorKm() + " L/km");
        System.out.println("-------------------------------------------");
    }; 


    // métodos do funcionamento da classe 
    public void carregar(double quantidadeCarga) {
        if (quantidadeCarga <= 0) {
            mensagemErro("! Não é possível abastecer quantidades negativas.");
            return;
        }
        if (quantidadeCarga + getQuantidadeCarga() > getCapacidadeBateria()) {
            mensagemErro("! A quantidade a ser abastecida não pode exceder o limite do tanque!");
            return; 
        }

        setQuantidadeCarga(getQuantidadeCarga() + quantidadeCarga);
    };



}
