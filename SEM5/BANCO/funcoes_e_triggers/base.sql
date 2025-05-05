-- CREATE TABLE autores (
--     id SERIAL PRIMARY KEY,
--     nome VARCHAR(100) NOT NULL,
--     nacionalidade VARCHAR(50),
--     data_nascimento DATE,
--     biografia TEXT
-- );

-- INSERT INTO autores (nome, nacionalidade, data_nascimento, biografia) VALUES
-- ('J.K. Rowling', 'Britânica', '1965-07-31', 'Autora da famosa série Harry Potter.'),
-- ('George R.R. Martin', 'Americana', '1948-09-20', 'Criador de As Crônicas de Gelo e Fogo.'),
-- ('Machado de Assis', 'Brasileira', '1839-06-21', 'Um dos maiores escritores da literatura brasileira.'),
-- ('Gabriel García Márquez', 'Colombiana', '1927-03-06', 'Vencedor do Nobel e autor de Cem Anos de Solidão.'),
-- ('Clarice Lispector', 'Brasileira', '1920-12-10', 'Autora modernista brasileira, conhecida por sua escrita introspectiva.');

-- CREATE TABLE livros (
--     id SERIAL PRIMARY KEY,
--     titulo VARCHAR(150) NOT NULL,
--     genero VARCHAR(50),
--     ano_publicacao INT,
--     autor_id INT REFERENCES autores(id)
-- );

-- INSERT INTO livros (titulo, genero, ano_publicacao, autor_id) VALUES
-- ('Harry Potter e a Pedra Filosofal', 'Fantasia', 1997, 1),
-- ('Harry Potter e a Câmara Secreta', 'Fantasia', 1998, 1),

-- ('A Guerra dos Tronos', 'Fantasia', 1996, 2),
-- ('Fúria dos Reis', 'Fantasia', 1998, 2),

-- ('Dom Casmurro', 'Romance', 1899, 3),
-- ('Memórias Póstumas de Brás Cubas', 'Romance', 1881, 3),

-- ('Cem Anos de Solidão', 'Realismo Mágico', 1967, 4),
-- ('O Amor nos Tempos do Cólera', 'Romance', 1985, 4),

-- ('A Hora da Estrela', 'Ficção', 1977, 5),
-- ('Perto do Coração Selvagem', 'Ficção', 1943, 5);

-- INSERT INTO livros (titulo, genero, ano_publicacao, autor_id) VALUES
-- ('Harry Potter e o Prisioneiro de Azkaban', 'Fantasia', 1999, 1),
-- ('Harry Potter e o Cálice de Fogo', 'Fantasia', 2000, 1),
-- ('Harry Potter e a Ordem da Fênix', 'Fantasia', 2003, 1),
-- ('Harry Potter e o Enigma do Príncipe', 'Fantasia', 2005, 1),
-- ('Harry Potter e as Relíquias da Morte', 'Fantasia', 2007, 1),
-- ('Os Contos de Beedle, o Bardo', 'Fantasia', 2008, 1),
-- ('Morte Súbita', 'Drama', 2012, 1),
-- ('O Chamado do Cuco', 'Mistério', 2013, 1),
-- ('O Bicho-da-Seda', 'Mistério', 2014, 1),
-- ('Vocação para o Mal', 'Mistério', 2015, 1);

-- INSERT INTO livros (titulo, genero, ano_publicacao, autor_id) VALUES
-- ('A Tormenta de Espadas', 'Fantasia', 2000, 2),
-- ('O Festim dos Corvos', 'Fantasia', 2005, 2),
-- ('A Dança dos Dragões', 'Fantasia', 2011, 2),
-- ('Sangue e Fogo', 'Fantasia', 2018, 2),
-- ('O Cavaleiro dos Sete Reinos', 'Fantasia', 2015, 2),
-- ('Nightflyers', 'Ficção Científica', 1980, 2),
-- ('Sonho Febril', 'Terror', 1982, 2),
-- ('Wild Cards I', 'Fantasia', 1987, 2),
-- ('Wild Cards II', 'Fantasia', 1988, 2),
-- ('Wild Cards III', 'Fantasia', 1989, 2),
-- ('The Armageddon Rag', 'Mistério', 1983, 2),
-- ('The Ice Dragon', 'Fantasia', 1980, 2),
-- ('Dying of the Light', 'Ficção Científica', 1977, 2),
-- ('Hunter’s Run', 'Ficção Científica', 2007, 2),
-- ('Songs of the Dying Earth', 'Fantasia', 2009, 2);

-- INSERT INTO livros (titulo, genero, ano_publicacao, autor_id) VALUES ('Harry Potter e a Branca de Neve', 'Fantasia', 1999, 1);

CREATE TABLE produtos (
    id serial PRIMARY KEY,
    nome text,
    preco numeric
);

CREATE TABLE log_produtos (
    produto_id int,
    mensagem text,
    criado_em timestamp default now()
);

CREATE OR REPLACE FUNCTION trg_produto_insert()
RETURNS trigger AS $$
DECLARE
    texto_log text;
    preco_minimo numeric := 10.00;
    r record; -- usado no FOR
BEGIN
    -- Verifica se o preço é baixo
    IF NEW.preco < preco_minimo THEN
        texto_log := format('Produto %s inserido com preço baixo: %s', NEW.nome, NEW.preco);

        INSERT INTO log_produtos (produto_id, mensagem)
        VALUES (NEW.id, texto_log);

        RAISE NOTICE 'Produto com preço abaixo do mínimo inserido: %', NEW.nome;
    ELSE
        -- PERFORM
        PERFORM pg_sleep(0.01);

        -- EXECUTE dinâmico
        EXECUTE format('INSERT INTO log_produtos (produto_id, mensagem) VALUES (%s, %L)', NEW.id, 'Produto normal');
    END IF;

    -- FOR loop: percorre produtos já existentes e registra no log
    FOR r IN SELECT id, nome FROM produtos LOOP
        RAISE NOTICE 'Produto existente: % (%)', r.nome, r.id;

        INSERT INTO log_produtos (produto_id, mensagem)
        VALUES (r.id, format('Produto listado em loop: %s', r.nome));
    END LOOP;

    -- Bloco com tratamento de erro
    BEGIN
        IF NEW.nome IS NULL THEN
            RAISE EXCEPTION 'Nome do produto não pode ser nulo!';
        END IF;
    EXCEPTION
        WHEN others THEN
            RAISE NOTICE 'Erro ao validar nome: %', SQLERRM;
    END;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_after_insert_produto
AFTER INSERT ON produtos
FOR EACH ROW
EXECUTE FUNCTION trg_produto_insert();

INSERT INTO produtos (nome, preco) VALUES ('Bala', 5.00);
INSERT INTO produtos (nome, preco) VALUES ('Teclado', 50.00);
INSERT INTO produtos (nome, preco) VALUES (NULL, 25.00); -- Gera erro