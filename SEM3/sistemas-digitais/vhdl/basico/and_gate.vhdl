library IEEE;
use IEEE.std_logic_1164.all;

entity AND_GATE is 
    port(
        A, B        :   in std_logic;
        S           :   out std_logic
    );
end AND_GATE; 

architecture AND_GATE_CPT of AND_GATE is
begin
    S <=  A and B;
end AND_GATE_CPT; 