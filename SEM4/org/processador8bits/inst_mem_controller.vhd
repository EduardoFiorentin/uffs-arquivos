library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity INST_MEM_CONTROLLER is 
    port(
	    clk : in std_logic; 
        instruction_addrs : out std_logic_vector(4 downto 0);
        start : in std_logic;
        din: out std_logic_vector(11 downto 0);     -- dados a serem gravados
        str: out std_logic;     -- quando '1' permite que dados sejam gravados
        id: out std_logic;      -- '1' - saída da memória fica visivel
        valid_clk: out std_logic;
        finalize: in std_logic
    );
end INST_MEM_CONTROLLER; 

architecture behav_INST_MEM_CONTROLLER of INST_MEM_CONTROLLER is
    signal pc: integer range -1 to 30 := -1; 
    signal addrs: integer range 0 to 31 := 0; 
begin

    din <= "000000000000";
    str <= '0';
    id <= '1'; 

    process (clk)
    begin
        if ( clk'event and clk = '1' and start = '1' ) then 
            if pc < 29 then 
                pc <= pc + 1; 
            end if; 

            if pc mod 2 = 0 and finalize = '0' then 
                addrs <= addrs + 1; 
            end if;

        end if;
    end process;


	-- process(pc)
	-- begin
	-- 	case pc is
    --         when 0 => 
    --             instruction_adds <= "00000";
    --         when 2 => 
    --             instruction_adds <= "00001";
    --         when 4 => 
    --             instruction_adds <= "00010";
    --         when 6 => 
    --             instruction_adds <= "00011";
    --         when 8 => 
    --             instruction_adds <= "00100";
    --         when 10 => 
    --             instruction_adds <= "00101";
    --         when 12 => 
    --             instruction_adds <= "00110";
    --         when others => 
    --             instruction_adds <= "00111";
    --     end case; 
    -- end process; 
    valid_clk <= '1' when pc mod 2 = 0 else '0';
    instruction_addrs <= std_logic_vector(to_signed(addrs, instruction_addrs'length)); 
    
end behav_INST_MEM_CONTROLLER;