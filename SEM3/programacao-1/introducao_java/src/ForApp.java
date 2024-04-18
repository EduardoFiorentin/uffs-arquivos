import java.util.Scanner;

public class ForApp {
    public static void main(String[] args) throws Exception {
        
        Scanner charSc = new Scanner(System.in);
        Scanner intSc = new Scanner(System.in);
        
        int userSum = 0;
        int cont = 0; 
        char continuar = 'S'; 

        

        for (
                // execução de entrada do for
                System.out.println("Digite um número: "),
                userSum += intSc.nextInt(), 
                cont++,

                System.out.println("Deseja continuar digitando valores? [S/N] "),
                continuar = charSc.nextLine().charAt(0)  
                ;
                
                // condição de permanência
                continuar == 'S';        

                // ao final de cada iteração
                System.out.println("Digite outro número: "),
                userSum += intSc.nextInt(),
                cont++,

                System.out.println("Deseja continuar digitando valores? [S/N] "),
                continuar = charSc.nextLine().charAt(0)  
            )
            
            {
                // Sem bloco principal
            }

        System.out.printf("Foram digitados %d valores e sua soma é: %d\n", 
                            cont, userSum);

        charSc.close();
        intSc.close(); 
    }
}