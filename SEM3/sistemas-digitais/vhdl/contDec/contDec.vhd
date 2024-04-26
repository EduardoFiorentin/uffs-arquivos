library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;


entity counter_dec is 
   port (
        CE : in std_logic;      -- cheap enable
        CLK : in std_logic;     -- clock    
        RST : in std_logic;     -- reset
        OV : out std_logic;     -- overflow
        COUNT : out std_logic_vector(3 downto 0)    -- resultado
    );
end entity counter_dec; 


architecture behav_counter_dec of counter_dec is 

    signal counter : unsigned(3 downto 0) := "0000";

begin

    process(CLK, RST) 
    begin

        if RST = '1' then -- reset
            COUNT <= "0000"; 
            counter <= "0000";

        elsif rising_edge(CLK) then -- borda de subida do clock

            if CE = '0' and counter /= "01010" then

                -- logica contador 
                counter <= counter + 1; 
                
                
            else 
                counter <= "0000"; 
            end if; 

            -- COUNT <= counter; 
            -- else COUNT <= "0001"; 

            for i in 0 to 3 loop 
                COUNT(i) <= counter(i); 
            end loop; 

        end if; 
    end process;

end behav_counter_dec; 