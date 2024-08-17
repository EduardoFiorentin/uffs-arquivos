library IEEE;
use IEEE.std_logic_1164.all;

entity INSTRUCTION_MEMORY is 
    port(
	    clk : in std_logic; 
        instruction : out std_logic_vector(11 downto 0);
        start : in std_logic;
        valid_clk: out std_logic
    );
end INSTRUCTION_MEMORY; 

architecture behav_INSTRUCTION_MEMORY of INSTRUCTION_MEMORY is
    signal pc: integer range -1 to 30 := -1; 
begin

    process (clk)
    begin
        if ( clk'event and clk = '1' and start = '1' ) then 
            if pc < 30 then 
                pc <= pc + 1; 
            end if; 
        end if;
    end process;


	process(pc)
	begin
		case pc is
            when 0 => 
                instruction <= "110000000110";
            when 2 => 
                instruction <= "110001000100";
            when 4 => 
                instruction <= "110010000010";
            when 6 => 
                instruction <= "010011000001";
            when 8 => 
                instruction <= "010011011010";
            when 10 => 
                instruction <= "001011000000";
            when 12 => 
                instruction <= "111001000010";
            -- when 14 => 
            --     instruction <= "001001000010";
            -- when 16 => 
            --     instruction <= "001001000010";
            -- when 18 => 
            --     instruction <= "001001000010";
            -- when 20 => 
            --     instruction <= "001001000010";
            -- when 22 => 
            --     instruction <= "001001000010";
            -- when 24 => 
            --     instruction <= "001001000010";
            -- when 26 => 
            --     instruction <= "001001000010";
            -- when 28 => 
            --     instruction <= "001001000010";
            -- when 30 => 
            --     instruction <= "001001000010";
            when others => 
                instruction <= "111000000000";
        end case; 
        valid_clk <= '1' when pc mod 2 = 0 else '0'; 
	end process;
    
end behav_INSTRUCTION_MEMORY;