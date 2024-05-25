library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity busArbiter is
    Port (
        KEY: in std_logic_vector(3 downto 0); 
        sw: in std_logic_vector(9 downto 0);
		  ledR: out std_logic_vector(9 downto 0)
    );
end busArbiter;

architecture behavBusArbiter of busArbiter is
    type state_type is (IDLE, PREF0, PREF1, PREF2, PREF3);
    signal state, next_state : state_type := IDLE;                  -- ?
begin
    process(KEY(0), sw(1))

    -- controle de saídas 
    begin
        if (KEY(1) = '0') then -- alt
				state <= IDLE; 
				
        elsif (KEY(0)'EVENT and KEY(0) = '0') then  -- alt
            state <= IDLE; 
        
            state <= next_state; 
        
        end if; 
    end process;
    
    
    -- transição de estados 
        -- mudanças possiveis: 
            -- de IDLE para algum dos dispositivos  
            -- de um dos dispositivos para IDLE   
        
        -- manter estado atual 

    process(state, sw(0), sw(1), sw(2), sw(3)) 
    begin
        -- manter estado atual 
        next_state <= state;   
        case state is 

            -- de IDLE para algum dos outros 
            when IDLE => 
                if sw(0) = '1' then 
                    next_state <= PREF0; 
                elsif sw(1) = '1' then 
                    next_state <= PREF1; 
                elsif sw(2) = '1' then 
                    next_state <= PREF2; 
                elsif sw(3) = '1' then 
                    next_state <= PREF3; 
                else 
                    next_state <= IDLE; 
                end if;

            when PREF0 => 
                if sw(0) = '0' then
                    next_state <= IDLE;
                end if;
            when PREF1 => 
                if sw(1) = '0' then
                    next_state <= IDLE;
                end if;
            when PREF2 => 
                if sw(2) = '0' then
                    next_state <= IDLE;
                end if;
            when PREF3 => 
                if sw(3) = '0' then
                    next_state <= IDLE;
                end if;

            when others => 
                next_state <= IDLE; 
        end case; 
    end process;

    process(state)
    begin
        case state is
             when IDLE => 
                 ledR(0) <= '0';
                 ledR(1) <= '0';
                 ledR(2) <= '0';
                 ledR(3) <= '0';

            when PREF0 =>
                ledR(0) <= '1';
                ledR(1) <= '0';
                ledR(2) <= '0';
                ledR(3) <= '0';

            when PREF1 =>
                ledR(1) <= '1';
                ledR(0) <= '0';
                ledR(2) <= '0';
                ledR(3) <= '0';

            when PREF2 =>
                ledR(2) <= '1';
                ledR(0) <= '0';
                ledR(1) <= '0';
                ledR(3) <= '0';

            when PREF3 =>
                ledR(3) <= '1';
                ledR(0) <= '0';
                ledR(1) <= '0';
                ledR(2) <= '0';
            when others =>
                null;
        end case;
    end process;
end architecture behavBusArbiter; 