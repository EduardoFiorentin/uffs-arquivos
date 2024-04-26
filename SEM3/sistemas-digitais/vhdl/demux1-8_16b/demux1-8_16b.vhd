-- demux : entrada A - 16 bits 
--         entrada Ch - 4 bits 
-- saida S 1 bit 


library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity demux1_8_16b is
    port (
        A : in std_logic_vector(15 downto 0); 
        Ch : in std_logic_vector(3 downto 0); 
        S : out std_logic
    );
end entity demux1_8_16b;

architecture behav_demux1_8_16b of demux1_8_16b is 
begin
    process(A, Ch)
    begin 

        case Ch is 
            when "0000" => 
                S <= A(0); 
            when "0001" => 
                S <= A(1); 
            when "0010" => 
                S <= A(2); 
            when "0011" => 
                S <= A(3); 
            when "0100" => 
                S <= A(4); 
            when "0101" => 
                S <= A(5); 
            when "0110" => 
                S <= A(6); 
            when "0111" => 
                S <= A(7); 
            when "1000" => 
                S <= A(8); 
            when "1001" => 
                S <= A(9); 
            when "1010" => 
                S <= A(10); 
            when "1011" => 
                S <= A(11); 
            when "1100" => 
                S <= A(12); 
            when "1101" => 
                S <= A(13); 
            when "1110" => 
                S <= A(14); 
            when "1111" => 
                S <= A(15); 
            when others => 
                S <= '0'; 
            end case;

    end process; 

end behav_demux1_8_16b; 