-- library IEEE; 
-- use IEEE.std_logic_1164.all;

-- entity incrementador is 
--     port (
--         data_in: in std_logic_vector(31 downto 0); -- Tamanho específico de 32 bits para integer
--         data_out: out std_logic_vector(31 downto 0) -- Tamanho específico de 32 bits para integer
--     );
-- end incrementador; 

-- architecture behav_incrementador of incrementador is
--     constant valor : integer := 3;
-- begin
    
--     data_out <= std_logic_vector(signed(data_in) + valor);
    
-- end architecture behav_incrementador;


------------------------------------------------------

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all; -- Adicionando a biblioteca numeric_std

entity incrementador is 
    port (
        data_in: in std_logic_vector(31 downto 0); -- Tamanho específico de 32 bits para integer
        data_out: out std_logic_vector(31 downto 0) -- Tamanho específico de 32 bits para integer
    );
end incrementador; 

architecture behav_incrementador of incrementador is
    constant valor : integer := 3;
begin
    
    -- Conversão para o tipo integer para realizar a operação
    data_out <= std_logic_vector(signed(data_in) + valor);  
    
end architecture behav_incrementador;