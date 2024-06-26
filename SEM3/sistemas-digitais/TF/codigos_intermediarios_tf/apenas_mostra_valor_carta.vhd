-- implementação do controle do A 
--		se ganhou um A - hasA = 1
--		se a pontuação excede 21 e tem A - (pontuação - 10)
-- 		

-- remover estado de PLAYER_SCORE 
-- remover estado de DEALER_SCORE 


-- sistema principal --------------------------------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE ieee.numeric_std.all;

entity blackJack is
    Port (
      KEY: in std_logic_vector(3 downto 0); 
      sw: in std_logic_vector(9 downto 0);
		ledR: out std_logic_vector(9 downto 0);
		ledG: out std_logic_vector(9 downto 0);
      hex0: out std_logic_vector(6 downto 0);
		hex1: out std_logic_vector(6 downto 0);
		hex2: out std_logic_vector(6 downto 0);
		hex3: out std_logic_vector(6 downto 0)
		  
    );
end blackJack;

architecture behavblackJack of blackJack is
    signal card : std_logic_vector (3 downto 0) := "0000";
	
	type state_type is (START, DEAL_CARDS_P1, DEAL_CARDS_P2, DEAL_CARDS_D1, DEAL_CARDS_D2, PLAYER_TURN, PLAYER_HIT, DEALER_TURN, DEALER_HIT, FINAL_SCORE, WIN, TIE, LOSE);
    signal state, next_state : state_type := START;  
	signal score_player, score_dealer: integer range 0 to 31 := 0;

    -- display valor da carta
    signal card_to_display: std_logic_vector(3 downto 0);

    
    -- declaração componentes externos 
    component cardDisplay is 
    port (
        input_data: in std_logic_vector(3 downto 0);
        output_data: out std_logic_vector(6 downto 0)
    );
    end component; 

begin

	-- componentes externos 
    card_display_map: cardDisplay port map (
        input_data => card_to_display, 
        output_data => hex0
    );


	-- transição de estados no clock
	process(KEY(0), KEY(1))
	begin 
	
		if (KEY(1) = '0') then -- alt 	
				state <= START; 
				
        elsif (KEY(0)'EVENT and KEY(0) = '0') then  -- alt
        -- elsif (rising_edge(KEY(0))) then  -- alt
        -- elsif (rising_edge(CLK)) then  -- alt
            state <= next_state; 
			-- hex3 <= "1111111";
       end if; 
	
	end process; 

	card(0) <= sw(0);
	card(1) <= sw(1);
	card(2) <= sw(2);
	card(3) <= sw(3);

	
	-- controle de transição de estados
	-- process(state, hit, stay, key(1), key(2))
	process(state, key(2), key(3))
	begin
	  case state is 
		when START =>	
			next_state <= DEAL_CARDS_P1;
			score_dealer <= 0; 
			score_player <= 0;
			
		when DEAL_CARDS_P1 =>	
			 

			next_state <= DEAL_CARDS_P2;
			
		when DEAL_CARDS_P2 =>	
			-- se ganhar um A como segunda carta, valerá 11 se a pontuação atual for 10 ou menos 
			
			next_state <= DEAL_CARDS_D1;

			
		when DEAL_CARDS_D1 =>	

		next_state <= DEAL_CARDS_D2;

		when DEAL_CARDS_D2 =>
			
			next_state <= PLAYER_TURN;

		when PLAYER_TURN =>
			

		when PLAYER_HIT =>	
		
			-- if score_player + cards_score > 21 then 
			-- 	next_state <= LOSE; 
			-- else 
			-- 	next_state <= PLAYER_TURN;
			-- end if; 
			

		when DEALER_TURN =>	
			if score_dealer >= 17 then 
				next_state <= FINAL_SCORE; 
			else
				next_state <= DEALER_HIT; 
			end if;
			

		when DEALER_HIT =>	

			-- if score_dealer + cards_score > 21 then 
			-- 	next_state <= WIN; 
			-- else 
			-- 	next_state <= DEALER_TURN;
			-- end if; 
			

		when FINAL_SCORE =>	
			-- if score_player > score_dealer then
			-- 	next_state <= WIN; 
			-- elsif score_player < score_dealer then 
			-- 	next_state <= LOSE; 
			-- else 
			-- 	next_state <= TIE; 
			-- end if; 


		when WIN =>	
			next_state <= START;

		when TIE =>	
			next_state <= START;

		when LOSE =>	
			next_state <= START;

		when others => 
			next_state <= START; 
						
		end case; 
	end process; 


	-- processamento de saídas 
	-- process(score_dealer, score_player, state)
	process(state, card, card_display_output)
	begin
	  case state is 
		when START =>	
			-- hex0 <= "1001111";
			hex1 <= "1111111";
			hex2 <= "1111111";
			hex3 <= "1111111"; 

			-- hex3 <= "0000000";
			ledR <= "1000000000"; 
			ledG <= "0000000000"; 
			
		when DEAL_CARDS_P1 =>
			ledR <= "0100000000";
			
		when DEAL_CARDS_P2 =>

			-- hex3 <= "1111111";
			ledR <= "0010000000";

			
		when DEAL_CARDS_D1 =>
			-- hex3 <= "0000000";
			ledR <= "0001000000";

		when DEAL_CARDS_D2 =>	
			-- hex3 <= "0000000";
			ledR <= "0000100000";


		when PLAYER_TURN =>	
			ledR <= "0000010000";
			ledG <= "1000000000";


		when PLAYER_HIT =>
			ledR <= "0000001000";
			ledG <= "1000000000";
			

		when DEALER_TURN =>	
			ledR <= "0000000100";
			ledG <= "0100000000";

		when DEALER_HIT =>	

			ledR <= "0000000010";
			ledG <= "0100000000";

		when FINAL_SCORE =>	
			hex1 <= "1111111";
			hex2 <= "1111111";
			-- hex3 <= "1111111";
			ledR <= "0000000001";
			ledG <= "0000000000";

		when WIN =>	
			ledG <= "1111111111"; 
			ledR <= "0000000000";
			hex1 <= "1111111";
			hex2 <= "1111111";
			
		when TIE =>	
			ledR <= "1111111111"; 
			ledG <= "1111111111"; 
			hex1 <= "1111111";
			hex2 <= "1111111";
			
		when LOSE =>	
			ledR <= "1111111111"; 
			ledG <= "0000000000";
			hex1 <= "1111111";
			hex2 <= "1111111";

		when others => 
			hex3 <= "0000000";
			ledR <= "1000000001";
			
		end case; 

		-- controle de exibição da carta atual 
		if (state = START or state = DEAL_CARDS_P1 or state = DEAL_CARDS_P2 or state = DEAL_CARDS_D1 or state = DEAL_CARDS_D2 or state = PLAYER_HIT or state = DEALER_HIT) then 
            card_to_display <= card;
        else
            card_to_display <= "1111";
        end if;

		-- hex0 <= card_display_output; 

	end process; 
			
end architecture behavblackJack; 



-- mostrar valor da carta no hit ---------------------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE ieee.numeric_std.all;

entity cardDisplay is 
port (
	input_data: in std_logic_vector(3 downto 0);
	output_data: out std_logic_vector(6 downto 0)
);
end cardDisplay; 

architecture behavCardDisplay of cardDisplay is 
begin
    output_data <= "1111001" when input_data = "0001" else 
                "0100100" when input_data = "0010" else -- 2
                "0110000" when input_data = "0011" else -- 3
                "0011001" when input_data = "0100" else -- 4
                "0010010" when input_data = "0101" else -- 5
                "0000010" when input_data = "0110" else -- 6
                "1111000" when input_data = "0111" else -- 7
                "0000000" when input_data = "1000" else -- 8
                "0010000" when input_data = "1001" else -- 9
                "0001000" when input_data = "1010" else -- A
                "0000011" when input_data = "1011" else -- b
                "1000110" when input_data = "1100" else -- C
                "0100001" when input_data = "1101" else "1111111";-- d



	-- process(inputData)
	-- begin
	-- 	case inputData is
	-- 		-- when "0000" => outputData <= "0000001"; -- 0
	-- 		when "0001" => outputData <= "1111001"; -- 1
	-- 		when "0010" => outputData <= "0100100"; -- 2
	-- 		when "0011" => outputData <= "0110000"; -- 3
	-- 		when "0100" => outputData <= "0011001"; -- 4
	-- 		when "0101" => outputData <= "0010010"; -- 5
	-- 		when "0110" => outputData <= "0000010"; -- 6
	-- 		when "0111" => outputData <= "1111000"; -- 7
	-- 		when "1000" => outputData <= "0000000"; -- 8
	-- 		when "1001" => outputData <= "0010000"; -- 9
	-- 		when "1010" => outputData <= "0001000"; -- A
	-- 		when "1011" => outputData <= "0000011"; -- b
	-- 		when "1100" => outputData <= "1000110"; -- C
	-- 		when "1101" => outputData <= "0100001"; -- d
			
	-- 		when others => outputData <= "1111111"; -- Default to all segments off
	-- 	end case;
	-- end process; 
end architecture behavCardDisplay; 