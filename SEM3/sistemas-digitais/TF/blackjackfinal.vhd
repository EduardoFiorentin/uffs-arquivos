-- antes de mudar para pontuação para vetores 

-- sistema principal --------------------------------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE ieee.numeric_std.all;

entity blackJack is
    Port (
      KEY: in std_logic_vector(3 downto 0); 
      sw: in std_logic_vector(9 downto 0);
		ledR: out std_logic_vector(9 downto 0);
		ledG: out std_logic_vector(7 downto 0);
      hex0: out std_logic_vector(6 downto 0);
		hex1: out std_logic_vector(6 downto 0);
		hex2: out std_logic_vector(6 downto 0);
		hex3: out std_logic_vector(6 downto 0)
		  
    );
end blackJack;

architecture behavblackJack of blackJack is
    signal card : std_logic_vector (3 downto 0) := "0000";
	
	type state_type is (START, DEAL_CARDS_P1, DEAL_CARDS_P2, DEAL_CARDS_D1, DEAL_CARDS_D2, PLAYER_TURN, PLAYER_HIT, DEALER_TURN, DEALER_HIT, FINAL_SCORE, WIN, TIE, LOSE);
    signal state : state_type := START;  
	signal score_dealer : integer range 0 to 31 := 0;
	signal score_player: integer range 0 to 31 := 0;

    -- display valor da carta
    signal card_to_display: std_logic_vector(3 downto 0);
    signal card_score: integer range 0 to 31 := 0;

	 -- codigos da pontuação 
	signal score_player_code_dec, score_player_code_un: std_logic_vector(6 downto 0) := "1111111"; 
	signal score_dealer_code_dec, score_dealer_code_un: std_logic_vector(6 downto 0) := "1111111"; 

	-- 1 - player tem A valendo 11 (pode haver um decrescimo de 10 caso a pontuação ultrapasse 21)
	-- 0 - não tem A valendo 11 
	signal dec_10_player, dec_10_dealer : std_logic := '0'; 
	 
    -- declaração componentes externos 
    component cardDisplay is 
    port (
        input_data: in std_logic_vector(3 downto 0);
        output_data: out std_logic_vector(6 downto 0)
    );
    end component; 

    component cardScore is 
    port (
        input_card: in std_logic_vector(3 downto 0);
        output_score: out integer range 0 to 31
    ); 
    end component; 
	 
	component scoreTo7Seg is 
	port (
		input_score: in integer range 0 to 31;
		output_dec: out std_logic_vector(6 downto 0);
		output_un: out std_logic_vector(6 downto 0)
	); 
	end component;

begin

	-- componentes externos 
    -- mapeamento do valor da carta para display 7seg
    card_display_map: cardDisplay port map (
        input_data => card_to_display, 
        output_data => hex0
    );

    -- mapeamento do valor da carta para pontuação inteira 
    card_score_map: cardScore port map (
        input_card => card,
        output_score => card_score
    );
	 
	 -- mapeamento da pontuação dos jogadores 
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


	card(0) <= sw(0);
	card(1) <= sw(1);
	card(2) <= sw(2);
	card(3) <= sw(3);

	
	-- controle de transição de estados
	process(KEY(0), KEY(1))
	begin
	
		if (KEY(1) = '0') then -- alt 	
				state <= START; 
				
        elsif (KEY(0)'EVENT and KEY(0) = '0') then  -- alt
				case state is 
					when START =>	
						score_dealer <= 0; 
						score_player <= 0;
						dec_10_player <= '0'; 
						dec_10_dealer <= '0'; 
						
						state <= DEAL_CARDS_P1;
						
					when DEAL_CARDS_P1 =>
						if card = "0001" then 
							-- se a primeira for A, sempre vai valer 11 
							dec_10_player <= '1'; 
							score_player <= score_Player + 11; 
						else 
							score_player <= score_player + card_score;
						end if; 
						state <= DEAL_CARDS_P2;
						
					when DEAL_CARDS_P2 =>
						-- se ganhar um A como segunda carta, valerá 11 se a pontuação atual for 10 ou menos 
						if card = "0001" then 
							if score_player <= 10 then
								dec_10_player <= '1'; 
								score_player <= score_Player + 11; 
							else 
								score_player <= score_Player + 1; 				
							end if;
						else 
							score_player <= score_player + card_score;
						end if; 

						state <= DEAL_CARDS_D1;

						
					when DEAL_CARDS_D1 =>
						if card = "0001" then 
							-- se a primeira for A, sempre vai valer 11 
							dec_10_dealer <= '1'; 
							score_dealer <= score_dealer + 11; 
						else 
							score_dealer <= score_dealer + card_score;
						end if; 
						
						state <= DEAL_CARDS_D2;

					when DEAL_CARDS_D2 =>
						-- se ganhar um A como segunda carta, valerá 11 se a pontuação atual for 10 ou menos 
						if card = "0001" then 
							if score_dealer <= 10 then
								dec_10_dealer <= '1'; 
								score_dealer <= score_dealer + 11; 
							else 
								score_dealer <= score_dealer + 1; 				
							end if;
						else 
							score_dealer <= score_dealer + card_score;
						end if; 
						
						state <= PLAYER_TURN;

					when PLAYER_TURN =>
						
							if (sw(4) = '1') then 
								 state <= PLAYER_HIT; 
							end if; 

							if (sw(5) = '1') then 
								 state <= DEALER_TURN; 
							end if; 

					when PLAYER_HIT =>	
					
						if card = "0001" then 
							if score_player <= 10 then 
								score_player <= score_player + 11;
								dec_10_player <= '1'; 
							else 
								score_player <= score_player + 1; 
							end if; 
						else 
							score_player <= score_player + card_score;
						end if; 

						
						-- se estoura 21 e tem um A valendo 11 - remove os 11 
						if (score_player + card_score) > 21 and dec_10_player = '1' then
							score_player <= score_player + card_score - 10;
							dec_10_player <= '0'; 	-- não pode mais perder 10 pontos caso estoure 21 
							state <= PLAYER_TURN;  

						elsif score_player + card_score > 21 then 
							state <= LOSE; 
						else 
							state <= PLAYER_TURN;
						end if; 
						

					when DEALER_TURN =>	
						if score_dealer >= 17 then 
							state <= FINAL_SCORE; 
						else
							state <= DEALER_HIT; 
						end if;
						

					when DEALER_HIT =>	
						if card = "0001" then 
							if score_dealer <= 10 then 
								score_dealer <= score_dealer + 11;
								dec_10_dealer <= '1'; 
							else 
								score_dealer <= score_dealer + 1; 
							end if; 
						else 
							score_dealer <= score_dealer + card_score;
						end if; 

						-- se estoura 21 e tem um A valendo 11 - remove os 11 
						if (score_dealer + card_score) > 21 and dec_10_dealer = '1' then
							score_dealer <= score_dealer + card_score - 10;
							dec_10_dealer <= '0'; 	-- não pode mais perder 10 pontos caso estoure 21 
							state <= DEALER_TURN;  

						elsif score_dealer + card_score > 21 then 
							state <= WIN; 
						else 
							state <= DEALER_TURN;
						end if; 
						

					when FINAL_SCORE =>	
						if score_player > score_dealer then
							state <= WIN; 
						elsif score_player < score_dealer then 
							state <= LOSE; 
						else 
							state <= TIE; 
						end if; 


					when WIN =>	
						state <= START;

					when TIE =>	
						state <= START;

					when LOSE =>	
						state <= START;

					when others => 
						state <= START; 
									
					end case; 
       end if; 
	
	  
	end process; 


	-- processamento de saídas 
	-- process(score_dealer, score_player, state)
	process(state)
	begin
	  case state is 
		when START =>
			hex1 <= "1111111";
			hex2 <= "1111111";
			hex3 <= "1111111"; 

			ledR <= "1000000000"; 
			ledG <= "00000000"; 
			
			
			
		when DEAL_CARDS_P1 =>
			hex2 <= score_player_code_dec;
			hex1 <= score_dealer_code_un; 
			hex3 <= "0001100";
			ledR <= "0000000000";
			
		when DEAL_CARDS_P2 =>
			hex1 <= score_player_code_un;
			hex2 <= score_player_code_dec;
			hex3 <= "0001100";
			ledR <= "0000000000";
			
		when DEAL_CARDS_D1 =>
			hex1 <= score_dealer_code_un;
			hex2 <= score_dealer_code_dec;
			hex3 <= "0100001";
			ledR <= "0000000000";

		when DEAL_CARDS_D2 =>	
			hex1 <= score_dealer_code_un;
			hex2 <= score_dealer_code_dec;
			hex3 <= "0100001";
			ledR <= "0000000000";


		when PLAYER_TURN =>	
			hex1 <= score_player_code_un;
			hex2 <= score_player_code_dec;
			hex3 <= "0001100";
			ledR <= "0000000000";


		when PLAYER_HIT =>
			hex1 <= score_player_code_un;
			hex2 <= score_player_code_dec;
			hex3 <= "0001001";

		when DEALER_TURN =>	
			hex1 <= score_dealer_code_un;
			hex2 <= score_dealer_code_dec;
			hex3 <= "0100001";

		when DEALER_HIT =>	
			hex1 <= score_dealer_code_un;
			hex2 <= score_dealer_code_dec;
			hex3 <= "0001001";

		when FINAL_SCORE =>	
			hex1 <= "1111111";
			hex2 <= "1111111";
			hex3 <= "1111111";
			ledR <= "0000000000";
			ledG <= "00000000";

		when WIN =>	
			ledG <= "11111111"; 
			ledR <= "0000000000";
			hex1 <= "1111111";
			hex2 <= "1111111";
			hex3 <= "1111111";
			
		when TIE =>	
			ledR <= "1111111111"; 
			ledG <= "11111111"; 
			hex1 <= "1111111";
			hex2 <= "1111111";
			hex3 <= "1111111";
			
		when LOSE =>	
			ledR <= "1111111111"; 
			ledG <= "00000000";
			hex1 <= "1111111";
			hex2 <= "1111111";
			hex3 <= "1111111";

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
end architecture behavCardDisplay; 


-- calcula pontuação da carta atual ---------------------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE ieee.numeric_std.all;

entity cardScore is 
port (
	input_card: in std_logic_vector(3 downto 0);
	output_score: out integer range 0 to 31
);
end cardScore; 

architecture behavCardScore of cardScore is 
begin
    output_score <= 1 when input_card = "0001" else
                    2 when input_card = "0010" else
                    3 when input_card = "0011" else
                    4 when input_card = "0100" else
                    5 when input_card = "0101" else
                    6 when input_card = "0110" else
                    7 when input_card = "0111" else
                    8 when input_card = "1000" else
                    9 when input_card = "1001" else
                    10 when input_card = "1010" else
                    10 when input_card = "1011" else
                    10 when input_card = "1100" else
                    10 when input_card = "1101" else 
                    0;

end architecture behavCardScore; 



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
			when "0001" => output_value <= 1; -- 1 ou 11
			when "0010" => output_value <= 2; -- 2
			when "0011" => output_value <= 3; -- 3
			when "0100" => output_value <= 4; -- 4
			when "0101" => output_value <= 5; -- 5 
			when "0110" => output_value <= 6; -- 6
			when "0111" => output_value <= 7; -- 7
			when "1000" => output_value <= 8; -- 8
			when "1001" => output_value <= 9; -- 9
			when "1010" => output_value <= 10; -- 10
			when "1011" => output_value <= 10; -- J
			when "1100" => output_value <= 10; -- Q
			when "1101" => output_value <= 10; -- K
			
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
	
	output_un <= unity_code; 

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

            when others => output_code <= "1111111"; -- Saída padrão
        end case;
	end process; 
end architecture behavIntTo7Seg; 