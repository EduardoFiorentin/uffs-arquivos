-- somador 3 bits ---------------------------------------- 
library IEEE;
use IEEE.std_logic_1164.all;

entity adder_3b is
    port (
        A1: in std_logic;
        A2: in std_logic;
        A3: in std_logic;
        B1: in std_logic;
        B2: in std_logic;
        B3: in std_logic;
        Ci1: in std_logic;
        S1: out std_logic;
        S2: out std_logic;
        S3: out std_logic;
        Co: out std_logic
    );
end entity adder_3b;

architecture behav_adder_3b of adder_3b is 

    signal Co1: std_logic;
    signal Co2: std_logic; 

    component full_adder is 
    port(
        fa_A: in std_logic;
        fa_B: in std_logic;
        fa_Ci: in std_logic;
        fa_S: out std_logic;
        fa_Co: out std_logic
    );
    end component; 
    begin

        full_add_1: full_adder port map (
            fa_A => A1,
            fa_B => B1,
            fa_Ci => Ci1,
            fa_S => S1,
            fa_Co => Co1
        );

        full_add_2: full_adder port map (
            fa_A => A2,
            fa_B => B2,
            fa_Ci => Co1,
            fa_S => S2,
            fa_Co => Co2
        );

        full_add_3: full_adder port map (
            fa_A => A3,
            fa_B => B3,
            fa_Ci => Co2,
            fa_S => S3,
            fa_Co => Co
        );
    end behav_adder_3b;


--somador completo  ----------------------------------
library IEEE;
use IEEE.std_logic_1164.all;

entity full_adder is
    port (
        fa_A: in std_logic;
        fa_B: in std_logic;
        fa_Ci: in std_logic;
        fa_S: out std_logic;
        fa_Co: out std_logic
    );
end entity full_adder;

architecture behav_full_adder of full_adder is 

    signal ha1_Co: std_logic; 
    signal ha1_S: std_logic;
    -- signal ha2_S: std_logic; 
    signal ha2_Co: std_logic; 

    component half_adder is port(
        ha_A, ha_B: in std_logic; 
        ha_S, ha_Co: out std_logic
        );
    end component; 
    begin
        half_add_1:  half_adder port map(
            ha_A => fa_A, 
            ha_B => fa_B, 
            ha_S => ha1_S, 
            ha_Co => ha1_Co
        );

        half_add_2: half_adder port map(
            ha_A => fa_Ci, 
            ha_B => ha1_S, 
            ha_S => fa_S, 
            ha_Co => ha2_Co
        );

        fa_Co <= ha2_Co or ha1_Co;
    end behav_full_adder;



--meio somador ------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;

entity half_adder is 
port (
    ha_A: in std_logic;
    ha_B: in std_logic;
    ha_S: out std_logic;
    ha_Co: out std_logic
);
end half_adder;

architecture behav_half_adder of half_adder is
begin 
    ha_S <= ha_A xor ha_B; 
    ha_Co <= ha_A and ha_B; 
end behav_half_adder;




DEAL_CARDS_D2, PLAYER_TURN, PLAYER_HIT, PLAYER_SCORE, DEALER_TURN, DEALER_HIT, DEALER_SCORE, FINAL_SCORE, WIN, TIE, LOSE);