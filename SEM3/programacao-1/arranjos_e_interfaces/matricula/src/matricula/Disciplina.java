package matricula;

public class Disciplina {
    String nome; 
    Professor professor; 
    Aluno[] alunos; 


    public String getNome() {
        return this.nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public Professor getProfessor() {
        return this.professor;
    }

    public void setProfessor(Professor professor) {
        this.professor = professor;
    }

    public Aluno[] getAlunos() {
        return this.alunos;
    }

    public void setAlunos(Aluno[] alunos) {
        this.alunos = alunos;
    }


    public Disciplina(String nome, Professor professor, Aluno[] alunos ) {
        setNome(nome);
        setProfessor(professor);
        setAlunos(alunos);
    }
}
