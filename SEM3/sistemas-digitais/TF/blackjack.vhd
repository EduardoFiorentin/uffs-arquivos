-- sistema principal --------------------------------------------------------------------------------------------------------
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
		card: in std_logic_vector(3 downto 0);
		hit: in std_logic; 
		stay: in std_logic
		  
    );
end blackJack;
-- mudar:
-- trocar clock para key(0)

architecture behavblackJack of blackJack is
    type state_type is (START, DEAL_CARDS_P1, DEAL_CARDS_P2, DEAL_CARDS_D1, DEAL_CARDS_D2, PLAYER_TURN, PLAYER_HIT, PLAYER_SCORE, DEALER_TURN, DEALER_HIT, DEALER_SCORE, FINAL_SCORE, WIN, TIE, LOSE);
    signal state, next_state : state_type := START;  
	signal score_player, score_dealer: integer range 0 to 31 := 0; 

	-- sinais intermediarios 
	signal card_to_display: std_logic_vector(3 downto 0);
    signal card_display_output: std_logic_vector(6 downto 0);

	-- display da carta recebida 
	component cardDisplay is 
	port (
		inputData: in std_logic_vector(3 downto 0);
		outputData: out std_logic_vector(6 downto 0)
	);
	end component; 

begin

	-- instancias dos elementos externos 
    cardDisplay_inst: cardDisplay port map (
        inputData => card_to_display,
        outputData => card_display_output
    );


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
	process(state, hit, stay)
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
			next_state <= PLAYER_TURN;
			score_dealer <= score_dealer + to_integer(unsigned(card));

		when PLAYER_TURN =>

			if hit'event and hit = '1' then 
				next_state <= PLAYER_HIT;
			end if; 

			if stay'event and stay = '1' then 
				next_state <= DEALER_TURN; 
			end if; 
			

		when PLAYER_HIT =>	
			score_player <= score_player + to_integer(unsigned(card));
			next_state <= PLAYER_SCORE;
			

		when PLAYER_SCORE =>	
			if score_player > 21 then
				next_state <= LOSE;  
			else
				next_state <= PLAYER_TURN;
			end if; 
			

		when DEALER_TURN =>	
			next_state <= START;
			

		when DEALER_HIT =>	
			next_state <= START;
			

		when DEALER_SCORE =>	
			next_state <= START;
			

		when FINAL_SCORE =>	
			if score_player > score_dealer then
				next_state <= WIN; 
			elsif score_player < score_dealer then 
				next_state <= LOSE; 
			else 
				next_state <= TIE; 
			end if; 

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
	process(score_dealer, score_player, state)
	begin
	  case state is 
		when START =>	
			-- hex0 <= "1001111";
			hex1 <= "0000000";
			hex2 <= "0000001";
			hex3 <= "0000000";
			ledR <= "0000000000"; 
			ledG <= "0000000000"; 
			
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


		when PLAYER_TURN =>	
			ledR <= "0000000000";
		

		when PLAYER_HIT =>	
			ledR <= "0000000000";
			

		when PLAYER_SCORE =>	
			ledR <= "0000000000";
			

		when DEALER_TURN =>	
			ledR <= "0000000000";

		when DEALER_HIT =>	
			ledR <= "0000000000";
			

		when DEALER_SCORE =>	
			ledR <= "0000000000";
			

		when FINAL_SCORE =>	
			ledR <= "0000000000";
	

		when WIN =>	
			ledG <= "1111111111"; 
			
		when TIE =>	
			ledR <= "1111111111"; 
			ledG <= "1111111111"; 
			
		when LOSE =>	
			ledR <= "1111111111"; 

		when others => 
			ledR(0) <= '1'; 
			ledG(0) <= '1'; 
						
			end case; 
	end process; 
	

	-- display dos valores de cartas e pontuação 

	-- mostra o valor atual da carta 
	process(state, card)
    begin
		if (state = DEAL_CARDS_P1 or state = DEAL_CARDS_P2 or state = DEAL_CARDS_D1 or state = DEAL_CARDS_D2 or state = PLAYER_HIT or state = DEALER_HIT) then 
            card_to_display <= card;
        else
            card_to_display <= "1111";
        end if;
	end process;

	-- atualizar valor do display 
	process(card_display_output) 
	begin 
		hex0 <= card_display_output; 
	end process; 


			
end architecture behavblackJack; 



-- mostrar valor da carta no hit ---------------------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE ieee.numeric_std.all;

entity cardDisplay is 
port (
	inputData: in std_logic_vector(3 downto 0);
	outputData: out std_logic_vector(6 downto 0)
);
end cardDisplay; 

architecture behavCardDisplay of cardDisplay is 
begin
	process(inputData)
	begin
		case inputData is
			-- when "0000" => outputData <= "0000001"; -- 0
			when "0001" => outputData <= "1001111"; -- 1
			when "0010" => outputData <= "0010010"; -- 2
			when "0011" => outputData <= "0000110"; -- 3
			when "0100" => outputData <= "1001100"; -- 4
			when "0101" => outputData <= "0100100"; -- 5
			when "0110" => outputData <= "0100000"; -- 6
			when "0111" => outputData <= "0001111"; -- 7
			when "1000" => outputData <= "0000000"; -- 8
			when "1001" => outputData <= "0000100"; -- 9
			when "1010" => outputData <= "0001000"; -- A
			when "1011" => outputData <= "1100000"; -- b
			when "1100" => outputData <= "0110001"; -- C
			when "1101" => outputData <= "1000010"; -- D
			
			when others => outputData <= "1111111"; -- Default to all segments off
		end case;
	end process; 
end architecture behavCardDisplay; 