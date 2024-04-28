package produtos;

import java.time.LocalDate;

public abstract class Produto {
    protected final String nome;
    private static int quantidade = 0;  
    private String id; 
    private double preco; 
    private boolean disponivel; 
    private LocalDate dataCadastro; 


    public String getNome() { return nome; }
    public String getId() { return id; }
    public double getPreco() { return preco; }
    public boolean isDisponivel() { return disponivel; }
    public boolean getDisponivel() { return disponivel; }
    public LocalDate getDataCadastro() { return dataCadastro; }
    public static int getQuantidade() { return quantidade; }

    private void setId(String id) { this.id = id; }
    private void setPreco(double preco) { this.preco = preco; }
    private void setDisponivel(boolean disponivel) { this.disponivel = disponivel; }
    private void setDataCadastro(LocalDate dataCadastro) { this.dataCadastro = dataCadastro; }

    protected void incrementaEstoque() { quantidade++; };
    protected void decrementaEstoque() { quantidade--; };

    public Produto(String nome, String id, double preco, boolean disponivel, LocalDate dataCadastro) {
        this.nome = nome;
        setId(id);
        setPreco(preco);
        setDisponivel(disponivel);
        setDataCadastro(dataCadastro);
        incrementaEstoque();
    }


    @Override
    protected void finalize() throws Throwable {
        // TODO Auto-generated method stub
        decrementaEstoque();
        super.finalize();
    }





}
