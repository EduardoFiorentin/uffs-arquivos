import java.util.Scanner;

public class DoWhile {
    public static void main(String[] args) throws Exception {
        
        Scanner charSc = new Scanner(System.in);
        Scanner intSc = new Scanner(System.in);
        
        int userSum = 0;
        int cont = 0; 
        char continuar = 'S';

        do {

            System.out.println("Digite um número: ");
            userSum += intSc.nextInt();
            cont++; 

            System.out.println("Deseja continuar digitando valores? [S/N] ");
            continuar = charSc.nextLine().charAt(0);
        } while(continuar == 'S');

        System.out.printf("Foram digitados %d valores e sua soma é: %d\n", cont, userSum);

        charSc.close();
        intSc.close();

    }
}
