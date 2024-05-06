package matricula;

public class Aluno extends Pessoa {

    String matricula; 

    public void setMatricula(String matricula) {
        this.matricula = matricula;
    }
    public String getMatricula() {
        return matricula;
    }

    public Aluno( String nome, String matricula ) {

        super(nome);
        setMatricula(matricula);

    }

}
