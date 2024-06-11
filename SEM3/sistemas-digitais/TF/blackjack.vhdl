library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity blackJack is
    Port (
        KEY: in std_logic_vector(3 downto 0); 
        sw: in std_logic_vector(9 downto 0);
		ledR: out std_logic_vector(9 downto 0);
		ledG: out std_logic_vector(9 downto 0);
        hex0: out std_logic_vector(6 downto 0)
    );
end blackJack;

architecture behavblackJack of blackJack is
    
    process(KEY(0), sw(1))
    begin
				
        if (KEY(0)'EVENT and KEY(0) = '0') then  -- alt
            hex0 <= "1111111"; 
        end if; 
    end process;

end architecture behavblackJack; 