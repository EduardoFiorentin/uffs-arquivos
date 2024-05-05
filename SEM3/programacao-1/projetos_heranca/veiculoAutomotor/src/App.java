import veiculo.VeiculoCombustao;
import veiculo.VeiculoEletrico;

public class App {
    public static void main(String[] args) throws Exception {
        VeiculoCombustao combustao = new VeiculoCombustao(120, 20, 130, 0.5);
        VeiculoEletrico eletrico = new VeiculoEletrico(50, 10, 100000, 3000); 


        combustao.mostrarStatus();
        
        combustao.abastecer(130);
        combustao.partida();
        combustao.andar(50);

        combustao.desligar();
        
        combustao.mostrarStatus();


        
    }
}
