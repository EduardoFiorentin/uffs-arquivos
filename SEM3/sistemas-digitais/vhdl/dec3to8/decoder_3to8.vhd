library IEEE;
use IEEE.std_logic_1164.all;

entity decoder_3to8 is
    port (
    A : in std_logic_vector (2 downto 0); -- Decoder Input
    Y : out std_logic_vector (7 downto 0) -- Decoder Output
);
end entity decoder_3to8;

-- tem 3 abordagens diferentes - tentar com as 3 
architecture behav_decoder_3to8 of decoder_3to8 is 
begin
        
        -- abordagem de fluxo
        -- Y <= "10000000" when A = "000" else
        --      "01000000" when A = "001" else
        --      "00100000" when A = "010" else
        --      "00010000" when A = "011" else
        --      "00001000" when A = "100" else
        --      "00000100" when A = "101" else
        --      "00000010" when A = "110" else
        --      "00000001" when A = "111";

        -- abordagem algoritmica
        -- process(A)
        -- begin 
        --     if A = "000" then Y <= "00000001"; 
        --     elsif A = "001" then Y <= "00000010"; 
        --     elsif A = "010" then Y <= "00000100"; 
        --     elsif A = "011" then Y <= "00001000"; 
        --     elsif A = "100" then Y <= "00010000"; 
        --     elsif A = "101" then Y <= "00100000"; 
        --     elsif A = "110" then Y <= "01000000"; 
        --     else Y <= "10000000"; 
        --     end if;
        -- end process; 

        -- abordagem algoritmica usando case 

    process(A)
    begin 
        case A is 
            when "000" => 
                Y <= "00000001";
            when "001" => 
                Y <= "00000010";
            when "010" => 
                Y <= "00000100";
            when "011" => 
                Y <= "00001000";
            when "100" => 
                Y <= "00010000";
            when "101" => 
                Y <= "00100000";
            when "110" => 
                Y <= "01000000";
            when others => 
                Y <= "10000000";
        end case; 
    end process; 
end behav_decoder_3to8;


-- NOTAS 

-- ifs: precisam de um else no final 
-- cases: precisam de um when others no final 


-- 0 - hor sup
-- 1 - vert sup dir
-- 2 - vert inf dir
-- 3 - hor inf 
-- 4 - vert inf esq
-- 5 - vert sup esq 
-- 6 - central