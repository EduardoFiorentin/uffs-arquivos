.data 
	
	# integers
	config_num_players: 	.word 	0
	config_board_size: 	.word 	0
	config_difficulty: 	.word 	0
	
	
	# Strings
	log_main_menu: 		.asciz 	"Menu\n\t[1] - Configuracoes\n\t[2] - Jogar\n\t[3] - Sair\n"
	log_user_option: 	.asciz  "\nOpcao: "
	log_config_menu: 	.asciz  "Configuracoes\n\t[1] - Numero de jogadores\n\t[2] - Tamanho do tabuleiro\n\t[3] - Dificuldade\n\t[4] - Zerar contadores\n\t[5] - Ver configuracoes e contadores\n"
	
.text 


main: 
	
	call render_main_menu 
	j end_program
	
	
	
# Menu functions 
get_user_option_main_menu: 
	call render_main_menu
	li a7, 5
	ecall 
	
	
# log functions 

# Render function
# Não recebe paramentros 
# Não retorna parametros 
render_main_menu: 
	la a0, log_main_menu
	call print_string
	
	la a0, log_user_option 
	call print_string
	
	ret
	
	
	
	
	
	
	
	
# Funcao generica de print de strings
# Parametros: 
#	a0 - endereço da string 
# Retorno: nao 
print_string: 
	li a7, 4
	ecall
	
	
	
end_program: 
	li a7, 10
	ecall