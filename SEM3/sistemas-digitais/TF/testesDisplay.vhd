library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE ieee.numeric_std.all;

entity teste is 
port (
    clk: in std_logic; 
    hex0: out std_logic_vector(6 downto 0)
);
end teste; 

architecture behavTeste of teste is 
    signal input_int : integer range 0 to 15 := 0; 
begin 
    process(clk)
	begin 
		if clk'EVENT and clk = '1' then 
			input_int <= input_int + 1;
		end if; 
	end process;

    process(input_int)
        begin
            case input_int is
                when 0 => hex0 <= "1000000"; -- 0
                when 1 => hex0 <= "1111001"; -- 1
                when 2 => hex0 <= "0100100"; -- 2
                when 3 => hex0 <= "0110000"; -- 3
                when 4 => hex0 <= "0011001"; -- 4
                when 5 => hex0 <= "0010010"; -- 5
                when 6 => hex0 <= "0000010"; -- 6
                when 7 => hex0 <= "1111000"; -- 7
                when 8 => hex0 <= "0000000"; -- 8
                when 9 => hex0 <= "0010000"; -- 9
                when 10 => hex0 <= "0001000"; -- A
                when 11 => hex0 <= "0000011"; -- b
                when 12 => hex0 <= "1000110"; -- C
                when 13 => hex0 <= "0100001"; -- d
                when 14 => hex0 <= "0000110"; -- E
                when 15 => hex0 <= "0001110"; -- F
                when others => hex0 <= "1111111"; -- Default to all segments off
            end case;
    end process; 
end architecture behavTeste; 
