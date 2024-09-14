# ----------------------- 
# Nome: Eduardo Fiorentin
# Matricula: 2211100002
# -----------------------
.data 
	
	# integers
	config_num_players: 	.word 	2
	config_board_size: 	.word 	2
	config_difficulty: 	.word 	1
	count_player_a: 	.word 	4
	count_player_b: 	.word 	4
	count_machine: 		.word 	4
	
	board: 			.space 216	# maximo: Tabuleiro 9x6 - 4 bytes cada valor
	
	# Strings
	log_main_menu: 		.asciz 	"Menu\n\t[1] - Configuracoes\n\t[2] - Jogar\n\t[3] - Sair\n"
	log_invalid_input: 	.asciz  "Valor invalido! Tente novamente.\n"
	log_user_option: 	.asciz  "\nOpcao: "
	log_endl:		.asciz	"\n"
	log_space: 		.asciz  " "
	
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
	
	log_play_empty: 	.asciz	"-"
	log_play_player1: 	.asciz	"&"
	log_play_player2: 	.asciz 	"#"
	
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
	
	
# Inicialização do tabuleiro
# Parametros: 
#	a0 - endereço do elemento 1
#	a1 - num de colunas 
# Retorno: Nao
board_begin: 
	# t0 - iterador 
	# t1 - quantidade de colunas 
	# t2 - numero de elementos 
	# t3 - endereco prim elemento 
	
	li t0, 0
	mv t1, a1
	li t2, 54
	mv t3, a0
	li t4, 0
	
	board_begin_loop:
		beq t0, t2, end_board_begin_loop
		
		sw t4, 0(t3)
		addi t3, t3, 4
		addi t0, t0, 1
		
		j board_begin_loop
	end_board_begin_loop:
	
	ret


# Print do tabuleiro 
# Parametros: 
#	a0 - endereco primeiro elemento 
#	a1 - num colunas 
# Retorno: Nao
board_print: 

	mv t0, a0	# endereco 
	mv t1, a1	# Num colunas 
	li t2, 0	# Iterador loop colunas 
	li t3, 0	# Iterador loop de linhas 
	li t4, 6	# Numero maximo de linhas 
	
	li a7, 4
	board_print_col_loop:
		
		li a7, 4
		beq t3, t4, end_board_print_col_loop
		
		board_print_line_loop:
			
			beq t2, t1, end_board_print_line_loop
			
			# PADRAO DE PRINT
			# 0 - slot vazio ->  -
			# 1 - player 1 	 ->  & 
			# 2 - player 2   ->  #
			
			lw t5, 0(t0)
			li t6, 0
			bne t5, t6, player_1_print
				
			la a0, log_play_empty
			ecall
			j end_print_chars
			
			player_1_print: 
			li t6, 1
			bne t5, t6, player_2_print
				
			la a0, log_play_player1
			ecall
			j end_print_chars
			
			player_2_print: 
				
			la a0, log_play_player2
			ecall
			j end_print_chars
			
			end_print_chars: 
			addi t0, t0, 4
			
			# print espaço 
			li a7, 4
			la a0, log_space
			ecall 
			
			addi t2, t2, 1
			
			j board_print_line_loop
		end_board_print_line_loop: 
	
		# print endl
		la a0, log_endl
		ecall
		
		addi t3, t3, 1
		li t2, 0
		
		j board_print_col_loop
		
	end_board_print_col_loop: 
	
	ret 
	
	
play: 
	# s10 - retorno da chamada de play
	mv s10, ra
	
	la a0, board	# carrega prim elemento tabuleiro
	
	lw t1, config_board_size
	li t2, 1
	# 1 - 7 colunas 
	# 2 - 9 colunas
	bne t1, t2, nine_cols
		li a1, 7
		j end_num_cols
	
	nine_cols: 
		li a1, 9
	
	end_num_cols: 
	
	call board_begin
	
	call board_print
	
	j end_program 
	
end_program: 
	li a7, 10
	ecall
