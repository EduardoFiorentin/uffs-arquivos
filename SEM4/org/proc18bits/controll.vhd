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

    branch <= '0';


    mem_write <= '0'; 


    mem_read <= '0'; 


    mem_to_reg <= '1' when inst = "1101" else
                '0'; 

    
    alu_in_src <= '1' when inst = "1101" 
                else '0';



    reg_write <= '1' when inst = "1101" else 
                '0'; 

    -- Imutáveis 
    alu_op <= inst; 

end behav_CONTROLL; 