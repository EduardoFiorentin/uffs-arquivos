library IEEE;
use IEEE.std_logic_1164.all;


entity CONTROLL is 
port (

    inst: in std_logic_vector(3 downto 0);
    zero: in std_logic; 

    branch  : out std_logic; 
    mem_write: out std_logic;
    mem_read: out std_logic; 
    mem_to_reg: out std_logic; 
    alu_op: out std_logic_vector(3 downto 0);
    alu_in_src: out std_logic;
    reg_write: out std_logic

);
end CONTROLL; 

architecture behav_CONTROLL of CONTROLL is 
begin

    branch <= '1' when inst = "1111" else '0';


    mem_write <= '0'; 


    mem_read <= '0'; 


    mem_to_reg <= '0' when inst = "0101" else
                '1'; 

    
    alu_in_src <= '1' when inst = "1101" 
                else '0';



    reg_write <= '0' when inst = "0110" or inst = "0111" or  inst = "1000" or  inst = "1001" or  inst = "1010" or  inst = "1011" or  inst = "1100" or  inst = "1111"  else 
                '1'; 

    -- Imutáveis 
    alu_op <= inst; 

end behav_CONTROLL; 