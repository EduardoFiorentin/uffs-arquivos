library IEEE;
use IEEE.std_logic_1164.all;

entity INST_DECODER is 
    port(
        operation : in std_logic_vector(11 downto 0);    -- entrada da tripa de instrução completa
        reg_dest : out std_logic_vector(2 downto 0);     -- registrador de destino da operação
        reg_a : out std_logic_vector(2 downto 0);        -- registrador do operador A da operação
        reg_b : out std_logic_vector(2 downto 0);        -- registrador do operador B da operação 
        inst_code : out std_logic_vector(2 downto 0);     -- codigo da instrução 
        cnst : out std_logic_vector(7 downto 0)         -- gera uma constante com os bits reg_a e reg_b (usado na instrução de carregamento de constante)
    );
end INST_DECODER; 

architecture behav_INST_DECODER of INST_DECODER is
begin
    inst_code <= operation(11) & operation(10) & operation(9);
    reg_dest <= operation(8) & operation(7) & operation(6);
    reg_a <= operation(5) & operation(4) & operation(3);
    reg_b <= operation(2) & operation(1) & operation(0);
    cnst <= "00" & reg_a & reg_b; 
end behav_INST_DECODER;