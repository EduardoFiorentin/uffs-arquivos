library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity mux4x2 is 
port (

    D0, D1, D2, D3 : in std_logic; 
    s0, s1: in std_logic; 
    y: out std_logic

); 
end mux4x2; 

architecture behav_mux4x2 of teste is

    signal sel : std_logic_vector(1 downto 0) := "00"; 

begin
    
    sel <= s1 & s0; 
    y <= '1'; 
    
end architecture behav_mux4x2;  