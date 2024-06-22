-- implementação do controle do A 
--		se ganhou um A - hasA = 1
--		se a pontuação excede 21 e tem A - (pontuação - 10)
-- 		


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

	-- display valor da carta
	signal card_to_display: std_logic_vector(3 downto 0);
    signal card_display_output: std_logic_vector(6 downto 0);

	-- controle de pontuação de cartas 
	signal cards_score: integer range 0 to 11; 

	-- display da carta recebida 
	component cardDisplay is 
	port (
		inputData: in std_logic_vector(3 downto 0);
		outputData: out std_logic_vector(6 downto 0)
	);
	end component; 

	-- calculadora da pontuação de cartas 
	component scoreConverter is 
	port (
		input_card: in std_logic_vector(3 downto 0);
		input_score: in integer range 0 to 31;
		output_value: out integer range 0 to 11
	); 
	end component; 

	-- conversor de pontuação para 7seg
	component scoreTo7Seg is 
	port (
		input_score: in integer range 0 to 31;
		output_dec: out std_logic_vector(6 downto 0);
		output_un: out std_logic_vector(6 downto 0)
	); 
	end component;

	-- codigos da pontuação 
	signal score_player_code_dec, score_player_code_un: std_logic_vector(6 downto 0) := "1111111"; 
	signal score_dealer_code_dec, score_dealer_code_un: std_logic_vector(6 downto 0) := "1111111"; 

begin

	-- instancias dos elementos externos 
    cardDisplay_inst: cardDisplay port map (
        inputData => card_to_display,
        outputData => card_display_output
    );

	cardsScore_player: scoreConverter port map (
		input_card => card,
		input_score => score_player,
		output_value => cards_score
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
			if score_dealer >= 17 then 
				next_state <= FINAL_SCORE; 
			else
				next_state <= DEALER_HIT; 
			end if;
			

		when DEALER_HIT =>	
			score_dealer <= score_dealer + to_integer(unsigned(card));
			next_state <= DEALER_SCORE;
			

		when DEALER_SCORE =>	
			if score_dealer > 21 then
				next_state <= WIN;  
			else
				next_state <= DEALER_TURN;
			end if; 
			

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
	
	-- conversores para mostrar pontuação 
	score_convert_player: scoreTo7Seg port map (
		input_score => score_player,
		output_dec => score_player_code_dec,
		output_un => score_player_code_un 
	); 

	score_convert_dealer: scoreTo7Seg port map (
		input_score => score_dealer,
		output_dec => score_dealer_code_dec,
		output_un => score_dealer_code_un 
	); 

	-- processamento de saídas 
	-- process(score_dealer, score_player, state)
	process(score_player_code_dec, score_player_code_un, score_dealer_code_dec, score_dealer_code_un, score_dealer, score_player, state)
	begin
	  case state is 
		when START =>	
			-- hex0 <= "1001111";
			hex1 <= "1111111";
			hex2 <= "1111111";

			hex3 <= "0000000";
			ledR <= "0000000000"; 
			ledG <= "0000000000"; 
			
		when DEAL_CARDS_P1 =>	
			hex1 <= score_player_code_un;
			hex2 <= score_player_code_dec;
			-- hex0 <= "0010010";
			-- hex2 <= "1001111";
			ledR <= "0000000000";
			
		when DEAL_CARDS_P2 =>
			hex1 <= score_player_code_un;
			hex2 <= score_player_code_dec;
			-- if score_player = 3 then 
			-- 	hex1 <= "1111111";
			-- else 
			-- 	hex1 <= "0000000";
			-- end if; 
			-- hex0 <= "0000110";
			-- hex2 <= "0010010";
			hex3 <= "1111111";
			ledR <= "0000000000";

			
		when DEAL_CARDS_D1 =>	
			hex1 <= score_dealer_code_un;
			hex2 <= score_dealer_code_dec;
			-- hex0 <= "0011001";
			-- hex1 <= "0000000";
			-- hex2 <= "0000110";
			hex3 <= "0000000";
			ledR <= "0000000000";

		when DEAL_CARDS_D2 =>	
			hex1 <= score_dealer_code_un;
			hex2 <= score_dealer_code_dec;
			-- hex0 <= "0011001";
			-- hex1 <= "0000000";
			-- hex2 <= "1001100";
			hex3 <= "0000000";
			ledR <= "0000000000";


		when PLAYER_TURN =>	
			hex1 <= score_player_code_un;
			hex2 <= score_player_code_dec;
			ledR <= "1000000000";
			ledG <= "1000000000";
		

		when PLAYER_HIT =>	
			hex1 <= score_player_code_un;
			hex2 <= score_player_code_dec;
			ledR <= "0100000000";
			ledG <= "1000000000";
			

		when PLAYER_SCORE =>	
			hex1 <= score_player_code_un;
			hex2 <= score_player_code_dec;
			ledR <= "0010000000";
			ledG <= "1000000000";
			

		when DEALER_TURN =>	
			hex1 <= score_dealer_code_un;
			hex2 <= score_dealer_code_dec;
			ledR <= "0111111111";
			ledG <= "0100000000";

		when DEALER_HIT =>	
			hex1 <= score_dealer_code_un;
			hex2 <= score_dealer_code_dec;
			ledR <= "1011111111";
			ledG <= "0100000000";

		when DEALER_SCORE =>	
			hex1 <= score_dealer_code_un;
			hex2 <= score_dealer_code_dec;
			ledR <= "1101111111";
			ledG <= "0100000000";

		when FINAL_SCORE =>	
			hex1 <= "1111111";
			hex2 <= "1111111";
			hex3 <= "1111111";
			ledR <= "0000000000";
			ledG <= "0000000000";

		when WIN =>	
			ledG <= "1111111111"; 
			hex1 <= "1111111";
			hex2 <= "1111111";
			
		when TIE =>	
			ledR <= "1111111111"; 
			ledG <= "1111111111"; 
			hex1 <= "1111111";
			hex2 <= "1111111";
			
		when LOSE =>	
			ledR <= "1111111111"; 
			hex1 <= "1111111";
			hex2 <= "1111111";

		when others => 
			hex3 <= "0000000";
						
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
			when "0001" => outputData <= "1111001"; -- 1
			when "0010" => outputData <= "0100100"; -- 2
			when "0011" => outputData <= "0110000"; -- 3
			when "0100" => outputData <= "0011001"; -- 4
			when "0101" => outputData <= "0010010"; -- 5
			when "0110" => outputData <= "0000010"; -- 6
			when "0111" => outputData <= "1111000"; -- 7
			when "1000" => outputData <= "0000000"; -- 8
			when "1001" => outputData <= "0010000"; -- 9
			when "1010" => outputData <= "0001000"; -- A
			when "1011" => outputData <= "0000011"; -- b
			when "1100" => outputData <= "1000110"; -- C
			when "1101" => outputData <= "0100001"; -- d
			
			when others => outputData <= "1111111"; -- Default to all segments off
		end case;
	end process; 
end architecture behavCardDisplay; 


-- calculadora de pontuação -----------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE ieee.numeric_std.all;

entity scoreConverter is 
port (
	input_card: in std_logic_vector(3 downto 0);
	input_score: in integer range 0 to 31;
	output_value: out integer range 0 to 11
);
end scoreConverter; 

architecture behavScoreConverter of scoreConverter is 
begin
	process(input_card)
	begin
		case input_card is
			-- when "0000" => outputData <= "0000001"; -- 0
			when "0000" => output_value <= 1; -- 1 ou 11
			when "0001" => output_value <= 2; -- 2
			when "0010" => output_value <= 3; -- 3
			when "0011" => output_value <= 4; -- 4
			when "0100" => output_value <= 5; -- 5 
			when "0101" => output_value <= 6; -- 6
			when "0110" => output_value <= 7; -- 7
			when "0111" => output_value <= 8; -- 8
			when "1000" => output_value <= 9; -- 9
			when "1001" => output_value <= 10; -- 10
			when "1010" => output_value <= 10; -- J
			when "1011" => output_value <= 10; -- Q
			when "1100" => output_value <= 10; -- K
			-- when "1101" => output_value <= 10; -- d
			
			when others => output_value <= 0; -- Default
		end case;
	end process; 
end architecture behavScoreConverter; 

-- se score <= 9 : (0, score)
-- se score <= 19 : (1, score - 10)
-- se score <= 29 : (2, score - 20)
-- senao (3, score - 30)

-- 0 ate 9 - 09 
-- 10 ate 19 - 1X
-- 20 ate 29 - 2X
-- 30 ate 31 - 3X

-- conversor score/7seg -----------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE ieee.numeric_std.all;

entity scoreTo7Seg is 
port (
	input_score: in integer range 0 to 31;
	output_dec: out std_logic_vector(6 downto 0);
	output_un: out std_logic_vector(6 downto 0)
	
);
end scoreTo7Seg; 

architecture behavScoreTo7Seg of scoreTo7Seg is 

	component intTo7Seg is
	port (	
		input_int: in integer range 0 to 9;
		output_code: out std_logic_vector(6 downto 0)
	);
	end component; 

	-- numero da unidade 
	signal unity : integer range 0 to 9 := 0; 
	signal unity_code : std_logic_vector(6 downto 0) := "1111111"; 

begin

	conv_dec: intTo7Seg port map (
		input_int => unity,
		output_code => unity_code
	); 

	process(input_score)
	begin
		if (input_score <= 9) then 
			output_dec <= "1000000";
			unity <= input_score;

		
		elsif (input_score <= 19) then 
			output_dec <= "1111001";
			unity <= (input_score - 10);
	
		elsif (input_score <= 29) then 
			output_dec <= "0100100";
			unity <= (input_score - 20);
	
		else
			output_dec <= "0110000";
			unity <= (input_score - 30);

		end if;
	end process;
	
	process(unity_code)
	begin 		
		output_un <= unity_code; 
	end process; 

end architecture behavScoreTo7Seg; 


-- conversor num/7seg -----------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE ieee.numeric_std.all;

entity intTo7Seg is 
port (
	input_int: in integer range 0 to 9;
	output_code: out std_logic_vector(6 downto 0)
);
end intTo7Seg; 

architecture behavIntTo7Seg of intTo7Seg is 
begin
	process(input_int)
	begin
		case input_int is
            when 0 => output_code <= "1000000"; -- 0
            when 1 => output_code <= "1111001"; -- 1
            when 2 => output_code <= "0100100"; -- 2
            when 3 => output_code <= "0110000"; -- 3
            when 4 => output_code <= "0011001"; -- 4
            when 5 => output_code <= "0010010"; -- 5
            when 6 => output_code <= "0000010"; -- 6
            when 7 => output_code <= "1111000"; -- 7
            when 8 => output_code <= "0000000"; -- 8
            when 9 => output_code <= "0010000"; -- 9

            when others => output_code <= "1111111"; -- Default to all segments off
        end case;
	end process; 
end architecture behavIntTo7Seg; 

-- codigos corrigidos para fpga
-- process(input_int)
-- 	begin
-- 		case input_int is
-- 			when 0 => hex0 <= "1000000"; -- 0
-- 			when 1 => hex0 <= "1111001"; -- 1
-- 			when 2 => hex0 <= "0100100"; -- 2
-- 			when 3 => hex0 <= "0110000"; -- 3
-- 			when 4 => hex0 <= "0011001"; -- 4
-- 			when 5 => hex0 <= "0010010"; -- 5
-- 			when 6 => hex0 <= "0000010"; -- 6
-- 			when 7 => hex0 <= "1111000"; -- 7
-- 			when 8 => hex0 <= "0000000"; -- 8
-- 			when 9 => hex0 <= "0010000"; -- 9
-- 			when 10 => hex0 <= "0001000"; -- A
-- 			when 11 => hex0 <= "0000011"; -- b
-- 			when 12 => hex0 <= "1000110"; -- C
-- 			when 13 => hex0 <= "0100001"; -- d
-- 			when 14 => hex0 <= "0000110"; -- E
-- 			when 15 => hex0 <= "0001110"; -- F
-- 			when others => hex0 <= "1111111"; -- Default to all segments off
--         end case;
-- end process; 