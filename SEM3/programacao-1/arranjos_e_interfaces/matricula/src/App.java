import matricula.*;

public class App {
    public static void main(String[] args) throws Exception {

        Professor professor = new Professor("Nome", 25);

        Aluno[] alunos = {
            new Aluno("Nome 1", "000001"),
            new Aluno("Nome 2", "000002"),
            new Aluno("Nome 3", "000002"),
            new Aluno("Nome 4", "000002"),
        };

        Disciplina disciplina = new Disciplina("Nome disc.", professor, alunos);
    }
}
