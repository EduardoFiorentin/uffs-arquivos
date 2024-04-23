library IEEE;
use IEEE.std_logic_1164.all;

entity decoder_2to4en is
    port (
    EN : in std_logic;
    A : in std_logic_vector (1 downto 0);
    Y_L : out std_logic_vector (3 downto 0)
    );
end entity decoder_2to4en;

architecture behav_decoder_2to4en of decoder_2to4en is
begin

    process(A, EN)
    begin

        if EN = '0' then Y_L <= "0000";
        else 

            if A = "00" then Y_L <= "0001"; 
            elsif A = "01" then Y_L <= "0010";
            elsif A = "10" then Y_L <= "0100";
            elsif A = "11" then Y_L <= "1000";
            else Y_L <= "0000";
            end if;

        end if;

    end process; 
end behav_decoder_2to4en;
