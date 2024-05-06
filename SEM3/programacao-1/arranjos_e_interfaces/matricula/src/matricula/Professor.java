package matricula;

public class Professor extends Pessoa {
    int cargaHoraria; 

    public int getCargaHoraria ()                     { return cargaHoraria; }
    public void setCargaHoraria (int cargaHoraria)    { this.cargaHoraria = cargaHoraria; }
    
    public Professor ( String nome, int cargaHoraria) {
        super(nome); 
        setCargaHoraria(cargaHoraria);
    } 

}
