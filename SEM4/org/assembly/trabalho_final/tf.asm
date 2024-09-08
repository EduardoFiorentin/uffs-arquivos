.data 
	
	# integers
	config_num_players: 	.word 	2
	config_board_size: 	.word 	1
	config_difficulty: 	.word 	1
	count_player_a: 	.word 	4
	count_player_b: 	.word 	4
	count_machine: 		.word 	4
	
	
	# Strings
	log_main_menu: 		.asciz 	"Menu\n\t[1] - Configuracoes\n\t[2] - Jogar\n\t[3] - Sair\n"
	log_invalid_input: 	.asciz  "Valor invalido! Tente novamente.\n"
	log_user_option: 	.asciz  "\nOpcao: "
	log_endl:		.asciz	"\n"
	
	log_config_menu: 	.asciz  "Configuracoes\n\t[1] - Numero de jogadores\n\t[2] - Tamanho do tabuleiro\n\t[3] - Dificuldade\n\t[4] - Zerar contadores\n\t[5] - Ver configuracoes e contadores\n\t[6] - Voltar ao menu"
	log_num_players: 	.asciz 	"Jogadores:\n\t[1] - 1 jogador\n\t[2] - 2 jogadores\n"
	log_board_size: 	.asciz 	"Tamanho do tabuleiro\n\t[1] - 7x6\n\t[2] - 9x6\n"
	log_difficulty: 	.asciz 	"Dificuldade:\n\t[1] - Facil\n\t[2] - Dificil\n"
	
	log_show_configs: 	.asciz 	"Configurações:\n"
	log_show_num_players:	.asciz 	"Numero de jogadores: \t"
	log_show_board_size:	.asciz 	"Tamanho do tabuleiro: \t"
	log_show_difficulty:	.asciz 	"Dificuldade: \t\t"
	log_show_score_a:	.asciz 	"Pontos jogador A: \t"
	log_show_score_b:	.asciz 	"Pontos jogador B: \t"
	log_show_score_machine:	.asciz 	"Pontos da maquina: \t"
	
	log_board_9x6: 		.asciz	"9x6\n"
	log_board_7x6: 		.asciz	"7x6\n"
	log_dif_easy: 		.asciz	"Facil\n"
	log_dif_hard: 		.asciz	"Dificil\n"
	
	
	debug: 			.asciz  "Debug\n" 
.text 


main: 
	
	call render_main_menu 
	
	# Opcao no menu principal
	li a0, 3
	call get_user_option_range
	
	
	# [1] - configuracoes
	li t0, 1
	beq t0, a0, configurations
	
	# [2] - jogar
	li t0, 2
	beq t0, a0, play
	
	# [3] - Sair
	li t0, 3
	beq a0, t0, end_program
	
	j main
	
# Menu functions 
get_user_option_main_menu: 
	call render_main_menu
	li a7, 5
	ecall 
	
	
# log functions 

# Função print do menu principal 
# Não recebe paramentros 
# Não retorna parametros 
render_main_menu: 
	la a0, log_main_menu
	li a7, 4
	ecall
	
	ret
	
	
# Função que pega input inteiro de um usuário	
# Permite valores de 1 ao passado em a0
# Parametro: 	a0 - máximo permitido (valor incluso)
# Retorno:	a0 - valor digitado pelo usuário
get_user_option_range: 
	# Valor limite fica salvo em t0
	mv t0, a0 	# Valor máximo (incluso) 
	li t1, 1 	# Valor minimo (incluso)
	
	li a7, 4
	la a0, log_user_option 
	ecall
	
	
	input:
	li a7, 5
	ecall 
	
	li t2, 1
	blt a0, t2, invalid_input 
	bgt a0, t0, invalid_input
	ret
	
	# Se opcao escolhida for invalida
	invalid_input: 
	li a7, 4
	la a0, log_invalid_input
	ecall
	la a0, log_user_option 
	ecall 
	j input
	

# Funcao de configuracoes 
# Parametros: Nao
# Retorno: Nao 
configurations: 

	mv s11, ra
	
	li a7, 4
	la a0, debug
	ecall 
	
	
	config_range: 
	li a7, 4
	la a0, log_config_menu
	ecall
	
	li a0, 6
	call get_user_option_range # a0 <- opcao do usuario
	
	
	# [1] - Qtd jogadores
	li t0, 1
	bne a0, t0, not_qtd_players
	
		la a0, log_num_players
		li a7, 4
		ecall 
		
		li a0, 2
		call get_user_option_range # a0 - 1 ou 2
		
		li t0, 1
		bne t0, a0, set_two_players
			li t0, 1
			la t1, config_num_players
			sw t0, 0(t1)
			j config_range
		set_two_players: 
			li t0, 2
			la t1, config_num_players
			sw t0, 0(t1)
			j config_range
	
	
	not_qtd_players:
	# [2] - tamanho tabuleiro
	li t0, 2
	bne a0, t0, not_board_size
	
		la a0, log_board_size
		li a7, 4
		ecall 
		
		li a0, 2
		call get_user_option_range # a0 - 1 ou 2
		
		li t0, 1
		la t1, config_board_size	
		bne t0, a0, set_9x6_board
			li t0, 1
			sw t0, 0(t1)
			j config_range
		set_9x6_board: 
			li t0, 2
			sw t0, 0(t1)
			j config_range
	
	not_board_size: 
	# [3] - dificuldade
	li t0, 3
	bne a0, t0, not_difficulty
	
		la a0, log_difficulty
		li a7, 4
		ecall 
		
		li a0, 2
		call get_user_option_range # a0 - 1 ou 2
		
		li t0, 1
		la t1, config_difficulty	
		bne t0, a0, set_dif_2
			li t0, 1
			sw t0, 0(t1)
			j config_range
		set_dif_2: 
			li t0, 2
			sw t0, 0(t1)
			j config_range
	
	not_difficulty:
	# [4] - zerar contadores
	li t0, 4
	bne a0, t0, not_reset_count
	
		li t1, 0
		la t0, count_player_a
		sw t1, 0(t0)
		
		la t0, count_player_b
		sw t1, 0(t0)
		
		la t0, count_machine
		sw t1, 0(t0)
		
		j config_range
	
	not_reset_count:
	# [5] - mostrar configuracoes
	li t0, 5
	bne a0, t0, not_show_config
	
	call show_configs
	
	not_show_config:
	# [6] - Voltar ao menu principal
	li t0, 6
	beq a0, t0, return
	
	
	
	j config_range
	
	return: 
	mv ra, s11
	ret
	
	

# Funcao que mostra as configuracoes atuais 
# Parametros: 	nao 
# Retornos: 	nao	
show_configs: 
	la a0, log_show_configs
	li a7, 4
	ecall
	
	# print numero de jogadores 
	la a0, log_show_num_players
	ecall
	
	la t0, config_num_players
	li a7, 1
	lw a0, 0(t0)
	ecall

	la a0, log_endl
	li a7, 4
	ecall

	# print tamanho do tabuleiro 
	la a0, log_show_board_size
	ecall
	
	li t0, 1
	la t1, config_board_size
	lw t2, 0(t1)	
	li a7, 4
	
	bne t0, t2, print_9x6_board
		# print 7x6
		la a0, log_board_7x6
		ecall
		j end_print_board_size
		
	print_9x6_board: 
		# print 9x6
		la a0, log_board_9x6
		ecall
		j end_print_board_size
	
	end_print_board_size:
	
	
	# print dificuldade
	li a7, 4
	la a0, log_show_difficulty
	ecall
	
	
	la t0, config_difficulty
	lw t0, 0(t0) 
	li t1, 1
	bne t0, t1, print_dif_hard 
		la a0, log_dif_easy
		ecall 
		j end_print_dif
	
	print_dif_hard: 
		la a0, log_dif_hard
		ecall 
		j end_print_dif
	
	end_print_dif: 
	
	# print pontos jogador A
	li a7, 4
	la a0, log_show_score_a
	ecall

	li a7, 1
	la t0, count_player_a
	lw a0, 0(t0) 
	ecall 
	
	li a7, 4
	la a0, log_endl
	ecall

	# print pontos jogador B
	li a7, 4
	la a0, log_show_score_b
	ecall
	
	li a7, 1
	la t0, count_player_b
	lw a0, 0(t0) 
	ecall 
	
	li a7, 4
	la a0, log_endl
	ecall
	
	
	# print pontos maquina
	li a7, 4
	la a0, log_show_score_machine
	ecall
	
	li a7, 1
	la t0, count_machine
	lw a0, 0(t0) 
	ecall 
	
	li a7, 4
	la a0, log_endl
	ecall
	
	
	# quebra de linha 
	li a7, 4
	la a0, log_endl
	ecall
	ret
	
	
	
play: 
	j end_program 
	
end_program: 
	li a7, 10
	ecall
