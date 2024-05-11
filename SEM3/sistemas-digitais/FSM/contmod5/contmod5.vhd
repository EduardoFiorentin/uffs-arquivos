library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity contmod5 is 
port (
    -- S = 0 - decrementa 
    -- S = 1 - incrementa 
    S, CLK, reset: in std_logic;
    cont: out std_logic_vector(2 downto 0)
);
end entity contmod5;



architecture behav_contmod5 of contmod5 is 
type states is (A, B, C, D, E); 
signal state: states := A; 

begin
    process(reset, CLK, S)
    begin
        if reset = '1' then
            state <= A; 
        elsif (CLK'EVENT and CLK = '1') then 
            case state is 
                when A => 
                    if S = '0' then 
                        state <= E;
                    else 
                        state <= B;
                    end if; 

                when B => 
                    if S = '0' then 
                        state <= A;
                    else 
                        state <= C;
                    end if; 

                when C => 
                    if S = '0' then 
                        state <= B;
                    else 
                        state <= D;
                    end if; 

                when D => 
                    if S = '0' then 
                        state <= C;
                    else 
                        state <= E;
                    end if; 

                when E => 
                    if S = '0' then 
                        state <= D;
                    else 
                        state <= A;
                    end if; 

                when others => 
                    state <= A; 
            end case; 
        end if;
    end process; 

    process(state)
    begin
        case state is 
            when A => 
                cont <= "000";
            when B => 
                cont <= "001"; 
            when C => 
                cont <= "010"; 
            when D => 
                cont <= "011"; 
            when E => 
                cont <= "100"; 
            when others => 
                cont <= "111";
        end case;                 
    end process;

end architecture behav_contmod5; 