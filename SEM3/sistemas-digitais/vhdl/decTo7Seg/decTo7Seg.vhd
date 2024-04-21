library IEEE; 
use IEEE.std_logic_1164.all;

entity decoder_decTo7Seg is 
    port (
        I : in std_logic_vector (7 downto 0);
        O0 : out std_logic; 
        O1 : out std_logic; 
        O2 : out std_logic; 
        O3 : out std_logic; 
        O4 : out std_logic; 
        O5 : out std_logic; 
        O6 : out std_logic; 
        O7 : out std_logic
);
end entity decoder_decTo7Seg; 

architecture behav_decoder_decTo7Seg of decoder_decTo7Seg is 
begin

    process(I)
    begin 

    O0 <= '0';
    O1 <= '0';
    O2 <= '0';
    O3 <= '0';
    O4 <= '0';
    O5 <= '0';
    O6 <= '0';
    O7 <= '0';

    case I is 
        when "00000000" => -- nenhum 
            null; 

        when "00000001" =>  -- 0
            O0 <= '1'; 
            O1 <= '1'; 
            O2 <= '1'; 
            O3 <= '1'; 
            O4 <= '1'; 
            O5 <= '1'; 

            
        when "00000010" =>  -- 1
            O1 <= '1';  
            O2 <= '1'; 

            
        when "00000100" => -- 2
            o0 <= '1';
            o3 <= '1';
            o1 <= '1';
            o4 <= '1';
            o6 <= '1';


        when "00001000" => -- 3
            o0 <= '1';
            o3 <= '1';
            o6 <= '1';
            o1 <= '1';
            o2 <= '1';


        when "00010000" => -- 4
            o5 <= '1';
            o1 <= '1';
            o6 <= '1';
            o2 <= '1';


        when "00100000" => -- 5
            o0 <= '1';
            o3 <= '1';
            o6 <= '1';
            o5 <= '1';
            o2 <= '1';


        when "01000000" => -- 6
            o5 <= '1';
            o4 <= '1';
            o3 <= '1';
            o2 <= '1';
            o6 <= '1';

        when "10000000" => -- 7
            o0 <= '1';
            o1 <= '1';
            o2 <= '1';


        when others => 
            o7 <= '1'; 

    end case; 
    end process;
end behav_decoder_decTo7Seg;



-- 0 - hor sup
-- 1 - vert sup dir
-- 2 - vert inf dir
-- 3 - hor inf 
-- 4 - vert inf esq
-- 5 - vert sup esq 
-- 6 - central