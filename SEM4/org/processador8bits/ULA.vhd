--------------------------------------------------------------------------------
-- HEIG-VD, institute REDS, 1400 Yverdon-les-Bains
-- Project :
-- File    :
-- Autor   :
-- Date    :
--
--------------------------------------------------------------------------------
-- Description :
--
--------------------------------------------------------------------------------

library IEEE;
use IEEE.std_logic_1164.all;

entity ULA is 
    port(
        VALUE_IN : in std_logic_vector(7 downto 0);
	OP : in std_logic_vector(1 downto 0); -- 0 - gravar no banco / 1 - selecionar no banco
        RAM, ULA_A, ULA_B : out std_logic_vector(7 downto 0)

    );
end ULA; 

architecture behav_ULA of ULA is
begin
    RAM <=  VALUE_IN and VALUE_IN;
end behav_ULA;