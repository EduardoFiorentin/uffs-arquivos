library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE ieee.numeric_std.all;

entity blackJack is
    Port (
        KEY: in std_logic_vector(9 downto 0); 
        sw: in std_logic_vector(9 downto 0);
		ledR: out std_logic_vector(9 downto 0);
		ledG: out std_logic_vector(9 downto 0);
        hex0: out std_logic_vector(6 downto 0);
		hex1: out std_logic_vector(6 downto 0);
		hex2: out std_logic_vector(6 downto 0);
		hex3: out std_logic_vector(6 downto 0);

		CLK: in std_logic; 

		card: in std_logic_vector(3 downto 0)
		  
    );
end blackJack;
-- mudar:
-- trocar clock para key(0)

architecture behavblackJack of blackJack is
    type state_type is (START, DEAL_CARDS_P1, DEAL_CARDS_P2, DEAL_CARDS_D1, DEAL_CARDS_D2, PLAYER_TURN, PLAYER_HIT, PLAYER_SCORE, DEALER_TURN, DEALER_HIT, DEALER_SCORE, FINAL_SCORE, WIN, TIE, LOSE);
    signal state, next_state : state_type := START;  
	signal score_player, score_dealer: integer range 0 to 31 := 0; 
begin
	
	-- transição de estados no clock
	process(KEY(0), KEY(1), CLK)
	begin 
	
		if (KEY(1) = '0') then -- alt 	
				state <= START; 
				
        -- elsif (KEY(0)'EVENT and KEY(0) = '0') then  -- alt
        -- elsif (rising_edge(KEY(0))) then  -- alt
        elsif (rising_edge(CLK)) then  -- alt
            state <= next_state; 
			-- hex3 <= "1111111";
       end if; 
	
	end process; 
	
	-- controle de transição de estados
	process(state)
	begin
	  case state is 
		when START =>	
			next_state <= DEAL_CARDS_P1;
			score_dealer <= 0; 
			score_player <= 0;
			
		when DEAL_CARDS_P1 =>	
			score_player <= score_player + to_integer(unsigned(card));
			next_state <= DEAL_CARDS_P2;
			
		when DEAL_CARDS_P2 =>	
			next_state <= DEAL_CARDS_D1;
			score_player <= score_player + to_integer(unsigned(card));
			
		when DEAL_CARDS_D1 =>	
			next_state <= DEAL_CARDS_D2;
			score_dealer <= score_dealer + to_integer(unsigned(card));

		when DEAL_CARDS_D2 =>	
			next_state <= START;
			score_dealer <= score_dealer + to_integer(unsigned(card));

		

		when others => 
			next_state <= START; 
						
		end case; 
	end process; 
	
	
	-- processamento de saídas 
	process(score_dealer, score_player, state)
	begin
	  case state is 
		when START =>	
			-- hex0 <= "1001111";
			hex1 <= "0000000";
			hex2 <= "0000001";
			hex3 <= "0000000";
			ledR <= "0000000000";
			
		when DEAL_CARDS_P1 =>	
			-- hex0 <= "0010010";
			hex2 <= "1001111";
			ledR <= "0000000000";
			
		when DEAL_CARDS_P2 =>
			if score_player = 3 then 
				hex1 <= "1111111";
			else 
				hex1 <= "0000000";
			end if; 
			-- hex0 <= "0000110";
			hex2 <= "0010010";
			hex3 <= "1111111";
			ledR <= "0000000000";

			
		when DEAL_CARDS_D1 =>	
			-- hex0 <= "0011001";
			hex1 <= "0000000";
			hex2 <= "0000110";
			hex3 <= "0000000";
			ledR <= "0000000000";

		when DEAL_CARDS_D2 =>	
			-- hex0 <= "0011001";
			hex1 <= "0000000";
			hex2 <= "1001100";
			hex3 <= "0000000";
			ledR <= "0000000000";

		when others => 
			ledR <= "1111111111"; 
						
			end case; 
	end process; 
	
	
	-- mostra o valor atual da carta 
	process(state, card)
    begin
		hex0 <= "1111111";
		if (state = DEAL_CARDS_P1 or state = DEAL_CARDS_P2 or state = DEAL_CARDS_D1 or state = DEAL_CARDS_D2 or state = PLAYER_HIT or state = DEALER_HIT) then 
        	case card is
				when "0000" => hex0 <= "0000001"; -- 0
				when "0001" => hex0 <= "1001111"; -- 1
				when "0010" => hex0 <= "0010010"; -- 2
				when "0011" => hex0 <= "0000110"; -- 3
				when "0100" => hex0 <= "1001100"; -- 4
				when "0101" => hex0 <= "0100100"; -- 5
				when "0110" => hex0 <= "0100000"; -- 6
				when "0111" => hex0 <= "0001111"; -- 7
				when "1000" => hex0 <= "0000000"; -- 8
				when "1001" => hex0 <= "0000100"; -- 9
				when "1010" => hex0 <= "0001000"; -- A
				when "1011" => hex0 <= "1100000"; -- b
				
				when others => hex0 <= "1111111"; -- Default to all segments off
			end case;
		end if; 
	end process;
			
end architecture behavblackJack; 


--hex0 <= "1111001";
--hex1 <= "0000000";
--hex2 <= "0000000";

--ledG <= "1111111111";
--ledR <= "1111111111";