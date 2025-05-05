-- Triggers
-- Funções executadas automaticamente quando um evento ocorre no banco de dados 
-- Eventos : 
--      Insert 
--      Update 
--      Delete 
--
-- Quando é executado: 
--      Antes
--      Depois
-- 
-- Referência aos valores das colunas:  
--      Valores antigos:    OLD     (OLD.nome_coluna)
--      Valores novos:      NEW     (NEW.nome_coluna)
--      OBS: Insert não tem valor antigo e delete não tem valor novo 
-- 
-- ESTRUTURA: 
-- create trigger <nome>
-- { before / after / instead of } { insert / update / delete { or ... } }  
-- on <table / view>
-- [ for each < row / statement >]
-- execute procedure <nome_função(argumentos)>
-- 
-- OBS:
-- for each row -           executa cada linha como uma transação 
-- for each statement -     executa cada comando como uma transação 
--                          (se estamos executando modificação em 10000 linhas e cai a energia, nenhuma sobra)


-- imprime no console cada vez que um livro é adicionado
create or replace function fofoqueiro()
returns trigger as $$
declare
begin
    raise notice 'Livro adicionado: %', NEW.titulo; 
    return NEW;
end;
$$ language plpgsql;

-- drop trigger tg_fofoqueiro;
create or replace trigger tg_fofoqueiro after insert on livros 
for each row execute procedure fofoqueiro(); 