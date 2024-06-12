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
    type state_type is (START, DEAL_CARDS_P1, DEAL_CARDS_P2, DEAL_CARDS_D1, DEAL_CARDS_D2);
    signal state, next_state : state_type := START;  
	 signal score_player, score_dealer: integer range 0 to 31 := 0; 
begin
	
	-- transição de estados no clock
	process(KEY(0), KEY(1))
	begin 
	
		if (KEY(1) = '0') then -- alt 	
				state <= START; 
				
        elsif (KEY(0)'EVENT and KEY(0) = '0') then  -- alt
            state <= next_state; 
       end if; 
	
	end process; 
	
	-- controle de proximo estado 
	process(state)
	begin
	  case state is 
		when START =>	
			next_state <= DEAL_CARDS_P1;
			score_dealer <= 0; 
			score_player <= 0;
			
		when DEAL_CARDS_P1 =>	
			score_player <= score_player + to_integer(unsigned(sw(3 downto 0)));
			next_state <= DEAL_CARDS_P2;
			
		when DEAL_CARDS_P2 =>	
			next_state <= DEAL_CARDS_D1;
			
		when DEAL_CARDS_D1 =>	
			next_state <= START;

		when others => 
			next_state <= START; 
						
			end case; 
	end process; 
	
	
	-- processamento de saídas 
	process(score_dealer, score_player)
	begin
	  case state is 
		when START =>	
			hex0 <= "1111001";
			hex1 <= "0000000";
			hex2 <= "0000000";
			hex3 <= "0000000";
			ledR <= "0000000000";
			
		when DEAL_CARDS_P1 =>	
			hex0 <= "0100100";
			ledR <= "0000000000";
			
		when DEAL_CARDS_P2 =>	
			if score_player =  then 
				hex1 <= "1111111";
			else 
				hex1 <= "0000000";
			end if; 
			hex0 <= "0110000";
			hex2 <= "0000000";
			hex3 <= "1111111";
			ledR <= "0000000000";

			
		when DEAL_CARDS_D1 =>	
			hex0 <= "0011001";
			hex1 <= "0000000";
			hex2 <= "0000000";
			hex3 <= "0000000";
			ledR <= "0000000000";

		when others => 
			ledR <= "1111111111"; 
						
			end case; 
	end process; 
	
	
	-- mostra pontuação player e dealer 
	
end architecture behavblackJack; 


--hex0 <= "1111001";
--hex1 <= "0000000";
--hex2 <= "0000000";

--ledG <= "1111111111";
--ledR <= "1111111111";