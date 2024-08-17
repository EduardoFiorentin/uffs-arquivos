library IEEE;
use IEEE.std_logic_1164.all;

entity BR_CONTROLLER is 
    port(

        -- manipulação do banco de registradores 
        da: in std_logic_vector(7 downto 0);            -- entrada do dado que sai do da do banco para o controller
        db: in std_logic_vector(7 downto 0);            -- entrada do dado que sai do db do banco para o controller
        din: out std_logic_vector(7 downto 0);          -- saída do dado que vai pro banco 
        we: out std_logic;                              -- comando pro banco salvar o dado 
        rw: out std_logic_vector (2 downto 0);          -- seletor do endereço do banco para salvar dados 
        ra: out std_logic_vector(2 downto 0);           -- seleciona o endereço no banco que terá como saída Da
        rb: out std_logic_vector(2 downto 0);           -- seleciona o endereço no banco que terá como saída Db
        
        -- manipulação da RAM
        a: out std_logic_vector(2 downto 0);            -- seleção do endereço de memória a ser gravado ou lido 
        ram : out std_logic_vector(7 downto 0);         -- dado a ser armazenado na memória RAM
        str: out std_logic;                             -- quando em 1, na borda de subida do clock os dados da saída ram serão armazenados 
        id: out std_logic;                              -- quando em 1, os dados do endereço selecionado na RAM ficam viziveis

        -- dados de instrução 
        reg_dest:  in std_logic_vector(2 downto 0);     -- qual o registrador de destino do resultado da instrução corrente
        reg_a: in std_logic_vector(2 downto 0);         -- qual registrador contêm o valor que é usado no A da ula na instrução
        reg_b: in std_logic_vector(2 downto 0);         -- qual registrador contêm o valor que é usado no B da ula na instrução
        inst:  in std_logic_vector(2 downto 0);         -- codigo da instrução corrente 
        cnst: in std_logic_vector(7 downto 0);          -- entrada da constante da instrução de carregamento de constante 
        
        -- saidas de dados para a ULA
        ula_a : out std_logic_vector(7 downto 0);       -- saida dado A na ula 
        ula_b : out std_logic_vector(7 downto 0);       -- saida dado B na ula 
        
        -- entrada de dados vindos da ula / ram
        value_in : in std_logic_vector(7 downto 0);     -- valor que vem da ram ou ULA e vai pro registrador
        value_in_select: out std_logic;                  -- seleciona se o dado de entrada (value_in) vem da ULA ou RAM
        end_process: out std_logic;                     -- acende quando a execução acaba 

        valid_clk: in std_logic
    );
end BR_CONTROLLER; 

architecture behav_BR_CONTROLLER of BR_CONTROLLER is
begin
    -- marcador de programa finalizado 
    end_process <= '1' when inst = "111" else 
                   '0'; 

    -- busca dado na RAM
    a <= reg_a when inst = "000" else               -- rd <- (e)
        reg_a when inst = "001" else                -- (e) <- rd
        "111"; -- c

    -- libera dados da RAM
    id <= '1' when inst = "000" else '0';           -- rd <- (e)

    -- value_in recebe dado da RAM ou da ULA 
    value_in_select <= '1' when inst = "000" else   -- rd <- (e)
        '0' when inst = "010" else                  -- rd <- a + b
        '0' when inst = "011" else                  -- rd <- a - b
        '0' when inst = "100" else                  -- rd <- a x b
        '0' when inst = "101" else                  -- rd <- a % b
    '0'; 

    -- definir Ra
    ra <= reg_dest when inst = "001" else          -- (e) <- rd 
        reg_a when inst = "010" else                -- rd <- a + b
        reg_a when inst = "011" else                -- rd <- a - b
        reg_a when inst = "100" else                -- rd <- a x b
        reg_a when inst = "101" else                -- rd <- a % b
    "000"; 

    -- definir Rb
    rb <= reg_b; 

    -- definir saída A da ULA
    ula_a <= da when inst = "010" else              -- rd <- a + b
        da when inst = "011" else              -- rd <- a - b
        da when inst = "100" else              -- rd <- a x b
        da when inst = "101" else              -- rd <- a % b
    "00000000";
    
    -- definir saída A da ULA
    ula_b <= db when inst = "010" else              -- rd <- a + b
        db when inst = "011" else              -- rd <- a - b
        db when inst = "100" else              -- rd <- a x b
        db when inst = "101" else              -- rd <- a % b
    "00000000";
    
    -- guardando no registrador
    rw <= reg_dest;

    -- libera o banco de registradores para receber dados
    we <= '0' when inst = "001" or valid_clk = '0' else '1';           -- rd <- (e)

    -- ajusta saída que vai pra entrada de dados do banco 
    din <= value_in when inst = "000" else          -- rd <- (e)
        cnst when inst = "110" else                 -- rd <- c 
        value_in when inst = "010" else              -- rd <- a + b
        value_in when inst = "011" else              -- rd <- a - b
        value_in when inst = "100" else              -- rd <- a x b
        value_in when inst = "101" else              -- rd <- a % b
    "00000000";

    -- ajustar entrada de dados da RAM
    ram <= da when inst = "001" else                -- (e) <- rd
    "00000000"; 

    -- permitir gravação na RAM
    str <= '1' when inst = "001" else '0'; 

end behav_BR_CONTROLLER;