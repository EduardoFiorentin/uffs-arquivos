library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity contmod5 is 
port (
    S, CLK, reset: in std_logic, 
    cont: out std_logic_vector(3 downto 0)
);
end entity contmod5;



architecture behav_contmod5 of contmod5 is 
type states is (A, B, C, D, E); 
signal state: A; 
begin
    process(reset, CLK, S)
    begin
        if reset = '1' then
            state <= A; 
        elsif (CLK'EVENT and clock = '1') then 
            -- case state is 
            --     when A => 

            -- end case; 
            state <= B;       
        end if;
            

    end process; 

    process(state)
    begin
        case state is 
            when A => 
                cont <= "000";
            when B => 
                cont <= "001"; 
            when others => 
                cont <= "111";
    end process;

end behav_contmod5; 

-- case A is 
--     when "000" => 
--         Y <= "00000001";
--     when "001" => 
--         Y <= "00000010";
--     when "010" => 
--         Y <= "00000100";
--     when "011" => 
--         Y <= "00001000";
--     when "100" => 
--         Y <= "00010000";
--     when "101" => 
--         Y <= "00100000";
--     when "110" => 
--         Y <= "01000000";
--     when others => 
--         Y <= "10000000";
-- end case; 