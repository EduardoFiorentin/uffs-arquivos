library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity busArbiter is
    Port (
        clk    : in STD_LOGIC;
        reset  : in STD_LOGIC;
        req0   : in STD_LOGIC;
        req1   : in STD_LOGIC;
        req2   : in STD_LOGIC;
        req3   : in STD_LOGIC;
        aut0   : out STD_LOGIC;
        aut1   : out STD_LOGIC;
        aut2   : out STD_LOGIC;
        aut3   : out STD_LOGIC
    );
end busArbiter;

architecture behavBusArbiter of busArbiter is
    type state_type is (IDLE, PREF0, PREF1, PREF2, PREF3);
    signal state, next_state : state_type := IDLE;                  -- ?
begin

    -- controle de saídas 
    process(clk, reset)
    begin
        if (reset = '1') then 
            state <= IDLE; 
        
        elsif (clk'EVENT and clk = '1') then 
            state <= next_state; 
        
        end if; 
    end process;
    
    
    -- transição de estados 
        -- mudanças possiveis: 
            -- de IDLE para algum dos dispositivos  
            -- de um dos dispositivos para IDLE   
        
        -- manter estado atual 

    process(state, req0, req1, req2, req3) 
    begin
        -- manter estado atual 
        next_state <= state;   
        case state is 

            -- de IDLE para algum dos outros 
            when IDLE => 
                if req0 = '1' then 
                    next_state <= PREF0; 
                elsif req1 = '1' then 
                    next_state <= PREF1; 
                elsif req2 = '1' then 
                    next_state <= PREF2; 
                elsif req3 = '1' then 
                    next_state <= PREF3; 
                else 
                    next_state <= IDLE; 
                end if;

            when PREF0 => 
                if req0 = '0' then
                    next_state <= IDLE;
                end if;
            when PREF1 => 
                if req1 = '0' then
                    next_state <= IDLE;
                end if;
            when PREF2 => 
                if req2 = '0' then
                    next_state <= IDLE;
                end if;
            when PREF3 => 
                if req3 = '0' then
                    next_state <= IDLE;
                end if;

            when others => 
                next_state <= IDLE; 
        end case; 
    end process;

    process(state)
    begin
        aut0 <= '0';
        aut1 <= '0';
        aut2 <= '0';
        aut3 <= '0';
        case state is
            -- when IDLE => 
            --     aut0 <= '0';
            --     aut1 <= '0';
            --     aut2 <= '0';
            --     aut3 <= '0';

            when PREF0 =>
                aut0 <= '1';
                -- aut1 <= '0';
                -- aut2 <= '0';
                -- aut3 <= '0';

            when PREF1 =>
                aut1 <= '1';
                -- aut0 <= '0';
                -- aut2 <= '0';
                -- aut3 <= '0';

            when PREF2 =>
                aut2 <= '1';
                -- aut0 <= '0';
                -- aut1 <= '0';
                -- aut3 <= '0';

            when PREF3 =>
                aut3 <= '1';
                -- aut0 <= '0';
                -- aut1 <= '0';
                -- aut2 <= '0';
            when others =>
                null;
        end case;
    end process;

end architecture behavBusArbiter; 