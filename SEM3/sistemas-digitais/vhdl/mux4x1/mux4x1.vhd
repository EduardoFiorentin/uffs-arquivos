library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity mux is
    port (
        I : in std_logic_vector (3 downto 0); 
        SEL : in std_logic_vector (1 downto 0); 
        Y : out std_logic 
    );
end entity mux;

architecture behav_mux of mux is 
begin 

    -- Y <= I(0) when SEL = "00" else
    --     I(1) when SEL = "01" else 
    --     I(2) when SEL = "10" else 
    --     I(3) when SEL = "11"; 

    process(I, SEL)
    begin 
        case SEL is 
            when "00" => 
                Y <= I(0); 
            when "01" => 
                Y <= I(1);
            when "10" => 
                Y <= I(2); 
            when "11" => 
                Y <= I(3); 
            when others => 
                Y <= '0'; 
        end case;
    end process;

end architecture behav_mux; 