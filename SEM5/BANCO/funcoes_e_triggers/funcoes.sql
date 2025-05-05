-- procedures 
-- codigos executados dentro do banco de dados 
-- servem para validação, processamentos de dados complexos, processamento de consultas complexas, etc. 
--
-- vantagem:        Independente do software acessando, as regras serão seguidas
--                  Melhora o trafego entre aplicações e servidor do banco 
--                  Mesma lógica pode ser aproveitada por várias aplicações
--
-- desvantagem:     Oculta as regras da aplicação - dificulta entendimento e manutenção
--                  Requer pessoal mais especializado para manutenção 
--                  Dificuldade de depuração do código se der algo errado 
--                  Perda de portabilidade caso precise mudar de sgbd



drop function soma;
create function soma(a integer, b integer)
returns integer as $$
declare 
    total integer;
begin
    total := a + b;
    raise notice 'valor a: %\nValor b: %\nTotal: %\n\n', a, b, total;
    return total;
end;
$$ language plpgsql;

-- record = guarda uma linha de uma tabela (com a separação de colunas)

drop function conta_livros_autor;
create function conta_livros_autor(id_autor INT)
returns text as $$
declare
    dados record;
begin
    select into dados count(*) as qtd_livros  from livros l where l.autor_id = id_autor;
    return 'Autor com id ' || id_autor || ' tem ' ||  dados.qtd_livros || ' livros ';
end;
$$ language plpgsql;

-- podemos usar as funções para gerar colunas no select tbm (o valor retornado será a linha de cada linha)
-- select a.*, conta_livros_autor(a.id) from autores a;


drop function categorizar_autor;
create function categorizar_autor(id_autor INT)
returns text as $$
declare
    qtd_livros record;
begin
    select into qtd_livros count(*) from livros l where l.autor_id = id_autor;
    if (qtd_livros.count < 10) then
        return 'Bronze';
    elsif (qtd_livros.count >= 10 and qtd_livros.count < 15) then
        return 'Prata';
    else 
        return 'Ouro';
    end if;
end;
$$ language plpgsql;

-- usar a função trigger para categorizar o autor 
select a.*, categorizar_autor(a.id) from autores a;


-- procedure que atualiza todos os campos de uma coluna em uma tabela 
drop function popular_qtd_autores;
create function popular_qtd_autores()
returns void as $$
declare 
    dados record;
begin
    
    for dados in select l.autor_id, count(*) as qtd_livros from livros l group by l.autor_id loop
        update autores set qtdLivros = dados.qtd_livros where autores.id = dados.autor_id;
    end loop;

end;
$$ language plpgsql;

