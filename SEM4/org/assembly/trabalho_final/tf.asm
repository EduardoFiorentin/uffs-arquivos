# ----------------------- 
# Nome: Eduardo Fiorentin
# Matricula: 2211100002
# -----------------------

# Jogo 4 em linha
.data 
	
	# inteiros
	config_num_players: 	.word 	1
	config_board_size: 	.word 	2
	config_difficulty: 	.word 	1
	count_player_a: 	.word 	0
	count_player_b: 	.word 	0
	count_machine: 		.word 	0
	
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
	log_difficulty: 	.asciz 	"Dificuldade:\n\t[1] - Facil\n\t[2] - Medio\n"
	
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
	log_dif_hard: 		.asciz	"Medio\n"
	
	log_play_empty: 	.asciz	"-"
	log_play_player1: 	.asciz	"&"
	log_play_player2: 	.asciz 	"#"
	
	log_endgame: 		.asciz 	"\nJogo Finalizado!\n"
	log_win_player1: 	.asciz 	"Jogador 1 venceu\n"
	log_win_player2: 	.asciz	"Jogador 2 venceu\n"
	log_tie: 		.asciz	"Empate\n"
	
	log_time_player1: 	.asciz "\nJogada do Player 1\n"
	log_time_player2: 	.asciz "\nJogada do Player 2\n" 
	log_time_machine:  	.asciz "\nJogada do Bot\n"
	
	log_board_7: 		.asciz "\n1 2 3 4 5 6 7\n"
	log_board_9: 		.asciz "\n1 2 3 4 5 6 7 8 9\n"
			
	
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
	

# Função print do menu principal 
# Não recebe paramentros 
# Não retorna parametros 
render_main_menu: 
	la a0, log_main_menu
	li a7, 4
	ecall
	
	ret
	
	
# Função de input de inteiro de usuario
# Permite valores de 1 ao passado em a0
# Parametro: 	a0 - máximo permitido (valor incluso)
# Retorno:	a0 - valor valido digitado pelo usuário
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
	

# Loop de jogo 
# Sem parametros 
# Sem retorno
play: 
	
	mv s10, ra
	
	# inicializacao do tabuleiro
	la a0, board	# carrega end prim elemento tabuleiro
	call board_begin
	
	# configuracao de registradores salvos  
	# s1 - jogador atual 
	# s0 - numero de colunas 
	# s2 - coluna escolhida pelo jogador
	# s3 - linha em que a última jogada foi inserida
	# s4 - modo de jogo (1 ou 2 players) 
	# s5 - ultima jogada player humano 
	# S6 - contador usado para referencia de quantidade de tentativas 
	# s7 - guarda resultado ao final do jogo 
	# s10 - retorno da chamada de play
	
	la s4, config_num_players
	lw s4, 0(s4)
	
	li s1, 1
	lw t1, config_board_size
	
	# Pegar numero de colunas
	# 1 - 7 linhas 
	# 2 - 9 linhas
	li t2, 1
	bne t1, t2, nine_cols
		li a1, 7
		j end_num_cols
	nine_cols: 
		li a1, 9
	
	end_num_cols: 
	mv s0, a1

	
	# Printa o tabuleiro inicial com numeros das colunas ---------------
	li a7, 4	
	li a0, 9
	beq s0, a0, print_header_9_2
	la a0, log_board_7
	ecall 
	j end_print_header_2
	print_header_9_2: 
	la a0, log_board_9
	ecall 
	end_print_header_2: 
	
	# Printa tabuleiro
	la a0, board
	mv a1, s0
	call board_print
		
	# ---------------------------------------------
	
	
	gameloop: 
		# Se nao eh o modo de jogo player x maquina (1)
		li t0, 2
		beq s4, t0, chooseplayer_loop
		
		# Se eh a vez do player escolher - passa pelo loop 
		li t0, 1
		beq t0, s1, chooseplayer_loop
		
		# Escolha do modo autonomo medio (Escolha ao redor da ultima jogada do player 1) 
		# Tenta escolher uma das casas ao redor da utima jogada do player
		# Se nenhuma for valida escolhe outra aleatoria 
		
		# Se for modo easy - pula para machine_random_choice
		la t0, config_difficulty
		lw t0, 0(t0)
		li t1, 1
		beq t0, t1, machine_random_choice	# Escolha do modo facil 
		
		# s5 - ultima coluna escolhida pelo jogador 
		# t2 - numero de tentativas (maximo 10) 
		# S6 - contador usado para referencia de quantidade de tentativas 
		li s6, 0
		mv s5, s2
		machine_medium_choice:
			addi s6, s6, 1
			li t3, 20
			bgt s6, t3, machine_random_choice 	# Se nao consegue escolher no local, escolhe outra posicao aleatoria
			 
			# t0 <- Random de -1 a 1
			li a7, 42
			li a1, 3
			ecall 
			
			addi a0, a0, -1
			add t1, a0, s5
			
			# Verificacao se a escolha aleatoria eh valida
			li t0, 1
			blt t1, t0, machine_medium_choice 	# Se a escolha for menor que 1 (coluna invalida)
			bgt t1, s0, machine_medium_choice 	# Se a escolha for maior que num_cols (coluna invalida)
			
			# Tenta insercao (mesmo valida, ainda pode ser coluna cheia)
			mv a0, t1
			mv a1, s1
			mv a2, s0
			la a3, board
			call board_insert
			
			# SUCESSO : jal para end_machine_random_choice para salvar a escolha 
			li t0, 1
			beq a0, t0, end_machine_random_choice
			
			# FRACASSO: jal machine_random_choice para escolher outra posicao aleatoria
			j machine_medium_choice
			
		end_machine_medium_choice:
		
		
		# Escolha do modo autonomo facil 
		machine_random_choice: 
			# Pega numero aleatorio de 0 a cols-1 
			li a7, 42
			mv t1, s0
			#addi t1, t1, -1
			mv a1, t1
			ecall
			
			# Coloca no intervalo [1, cols]
			addi a0, a0, 1
			mv s2, a0
			
			# Insercao no tabuleiro 
			# a0 - coluna escolhida
			# a1 - player (1 ou 2)
			# a2 - numero de colunas
			# a3 - endereco primeiro elemento do vetor
			mv a0, s2
			mv a1, s1
			mv a2, s0
			la a3, board
			call board_insert
		
			beq a0, zero, machine_random_choice 	# Se a escolha foi invalida repete
			
		end_machine_random_choice: 
		
		# Atualizacao de variaveis de controle
		mv s3, a1	# salva linha de insercao
		
		j end_chooseplayer_loop
		
		# Se for o modo de jogo de dois players 
		# pega opcao do jogador 
		# Se a jogada eh valida: insere no tabuleiro 
		# escolha: [1 -> 6] && primeiro elemento da coluna vazio 
		chooseplayer_loop: 
			
			# Printa tabuleiro para escolha 
			
			mv a0, s0
			# Funcao ja garante valores de 1 a t1
			# a0 <- opcao escolhida
			call get_user_option_range
			mv s2, a0
			
			
			# Tentar insercao no tabuleiro 
			mv a0, s2
			mv a1, s1
			mv a2, s0
			la a3, board
			call board_insert
			# a0 <- 0 (jogada invalida) ou 1 (jogada valida)]
			# a1 <- linha em que a inserção ocorreu (caso ocorreu) 
			mv s3, a1
			
			bne a0, zero, end_chooseplayer_loop
			
			# Print de jogada invalida
			li a7, 4
			la a0, log_invalid_input
			ecall
			
			j chooseplayer_loop
			
		end_chooseplayer_loop: 
		
		# Printa o rotulo do tabuleiro -------------------------------
		li a7, 4
		li t0, 2
		beq s1, t0, player2_log_play
		la a0, log_time_player1
		ecall
		j end_log_play
		
		player2_log_play: 
		li t0, 1
		beq s4, t0, machine_log_play
		la a0, log_time_player2
		ecall
		j end_log_play
		
		machine_log_play:
		la a0, log_time_machine
		ecall
		end_log_play: 
		
		li a0, 9
		beq s0, a0, print_header_9
		la a0, log_board_7
		ecall 
		j end_print_header
		print_header_9: 
		la a0, log_board_9
		ecall 
		end_print_header: 
		
		# Printa tabuleiro
		la a0, board
		mv a1, s0
		call board_print
		
		# ---------------------------------------------

		
		# Verifica vitória 
		# a0 <- coluna jogada 
		# a1 <- linha jogada 
		# a2 <- numero de colunas
		# a3 <- addrs primeiro elemento do vetor 
		# a4 <- player jogando 
		mv a0, s2
		mv a1, s3
		mv a2, s0
		la a3, board
		mv a4, s1
		call win_check
		# a0 <- 0 <- continuar jogo
		# 	1 <- player atual venceu
		# 	2 <- empate 
		
		# Se foi vitoria ou empate - sai do loop 
		bne a0, zero, end_gameloop
		
		# alterna jogador 
		li t1, 1
		beq s1, t1, player_two 
			li s1, 1
			j player_selected
		player_two: 
			li s1, 2
		player_selected:
		
		
				
		
		
		j gameloop
		
	end_gameloop: 
	
	# Printa tabuleiro
	la a0, board
	mv a1, s0
	call board_print
	
	# Altera valor do player atual para zero caso seja um empate
	li t1, 2
	bne a0, t1, not_tie
		li s1, 0
	not_tie: 
	
	
	li a7, 4
	la a0, log_endgame
	ecall
	
	
	la a0, board
	mv a1, s0
	call board_print
	mv ra, s10
	
	# s1 <- jogador atual
	# 0 - empate
	# 1 - jogador 1
	# 2 - jogador 2
	
	li a7, 4
	
	tie: 
	bne s1, zero, player1_wins
	la a0, log_tie
	ecall
	ret
	
	player1_wins: 
	li t0, 1
	bne s1, t0, player2_wins
	la a0, log_win_player1
	ecall
	
	# Atualiza contador de vitoria player 1 
	la t0, count_player_a
	lw t1, 0(t0)
	addi t1, t1, 1
	sw t1, 0(t0)
	ret
	
	player2_wins: 
	la a0, log_win_player2
	ecall
	
	# Atualiza contador de vitorias player 2 / computador 
	li t1, 1
	beq s4, t1, machine_playing
	
	la t0, count_player_b
	lw t1, 0(t0)
	addi t1, t1, 1
	sw t1, 0(t0)
	ret 
	
	machine_playing: 
	la t0, count_machine
	lw t1, 0(t0)
	addi t1, t1, 1
	sw t1, 0(t0)	
	ret


# Funcao de verificacao de vitoria de um jogador
# Parametros	: a0 - coluna jogada 
#		  a1 - linha jogada 
# 		  a2 - numero de colunas 
# 		  a3 - endereco primeiro elemento vetor 
# 		  a4 - player jogando 
# Retorno 	: a0 - 1 -> jogador ganhou
# 		       0 -> jogador nao ganhou
# 		       2 -> empate 
win_check: 
	mv t0, a2
	
	# pega primeiro elemento da linha (a2 * L) - L - linha da jogada (a1) 
	# t1 <- endereco primeiro elemento da linha jogada 
	# t2 <- controle do loop
	# t3 <- numero de jogadas consecutivas para vitoria 
	# t4 <- numero de jogadas do player encontradas consecutivas em linha
	mul t1, a2, a1
	li t3, 4
	mul t1, t1, t3
	add t1, t1, a3
	li t2, 0
	
	# compara com o player jogando e add + 4
	# vai ate t2 == a2
				
	li t3, 4
	li t4, 0
	horizontal_check_loop:
		beq t4, t3, win
		beq t2, a2, end_horizontal_check_loop
		
		lw t5, 0(t1) 		# carrega elemento atual do vetor
		bne t5, a4, horizontal_check_loop_current_play_not_player		# se o elemento atual nao eh igual ao do player 
		
		# se o elemento atual do vetor eh do player 
		addi t4, t4, 1
		j horizontal_check_loop_next 
		
		# se o elemento atual do vetor nao eh do player
		horizontal_check_loop_current_play_not_player: 
		li t4, 0
		
		horizontal_check_loop_next: 
		addi t1, t1, 4
		addi t2, t2, 1
		j horizontal_check_loop
	end_horizontal_check_loop:
	
	
	# Checagem vertical na coluna em que ocorreu a jogada 
	li t3, 4	# numero de jogadas consecutivas para ganhar 
	li t4, 0	# numero de jogadas consecutivas do player encontradas 
	li t2, 5	# Iteracao atual do loop (linha sendo verificada) 
	li t5, 0	# Elemento atual da matriz sendo verificado 
	# t1 - endereço dos elementos no vetor 
	# a3 - addrs prim elemento vetor 
	# a0 - coluna jogada
	# a2 - numero de colunas 
	# a4 - player jogando 
	vertical_check: 
		beq t4, t3, win
		blt t2, zero, end_vertical_check
		
		# carregar elemento 
		mv t1, a0
		addi t1, t1, -1
		mv t0, a2
		mul t0, t0, t2
		add t1, t1, t0
		li t0, 4
		mul t1, t1, t0	# t1 <- endereço do elemento
		add t1, t1, a3
		
		lw t5, 0(t1) 
		
		# Se igual ao player: incrementa
		bne t5, a4, vertical_check_loop_current_play_not_player 
		addi t4, t4, 1
		j vertical_check_loop_next
		
		vertical_check_loop_current_play_not_player: 
		li t4, 0
		
		# Incrementos do loop 
		vertical_check_loop_next: 
		
		addi t2, t2, -1
		j vertical_check
	
	end_vertical_check: 
	
	# Verificacao das diagonais no sentido da secundaria 
	li t3, 4	# numero de jogadas consecutivas para ganhar 
	li t4, 0	# numero de jogadas consecutivas do player encontradas 
	mv t2, a1	# Linha atual 
	mv t6, a0	# Coluna atual 
	li t5, 0	# Elemento atual da matriz sendo verificado 
	# t1 - endereço dos elementos no vetor 
	# a3 - addrs prim elemento vetor 
	# a0 - coluna jogada
	# a1 - linha jogada 
	# a2 - numero de colunas 
	# a4 - player jogando 
	li t1, 5
	sec_diagonal_prepare: 
		beq t2, t1, end_sec_diagonal_prepare
		beq t6, zero, end_sec_diagonal_prepare
		
		addi t2, t2, 1
		addi t6, t6, -1
		
		j sec_diagonal_prepare
	end_sec_diagonal_prepare: 
	
	# t2 - Linha atual 
	# t6 - Coluna atual 
	sec_diagonal_check: 
	
		# carregar elemento 
		mv t1, t6
		addi t1, t1, -1
		mv t0, a2
		mul t0, t0, t2
		add t1, t1, t0
		li t0, 4
		mul t1, t1, t0	# t1 <- endereço do elemento
		add t1, t1, a3
		
		lw t5, 0(t1) 
		
		# Se igual ao player: incrementa
		bne t5, a4, sec_check_loop_current_play_not_player 
		addi t4, t4, 1
		beq t4, t3, win		# Se a soma fecha 4 - jogador ganhou 
		j sec_check_loop_next
		
		sec_check_loop_current_play_not_player: 
		li t4, 0
		
		sec_check_loop_next: 
		
		# Verificacoes de finalizacao da procura 
		beq t2, zero, end_sec_diagonal_check
		beq t6, a2, end_sec_diagonal_check
		
		# Incrementos do loop 
		addi t2, t2, -1
		addi t6, t6, 1
		
		j sec_diagonal_check
	
	end_sec_diagonal_check: 
	
	
	# Verificacao das diagonais no sentido da primaria  
	li t3, 4	# numero de jogadas consecutivas para ganhar 
	li t4, 0	# numero de jogadas consecutivas do player encontradas 
	mv t2, a1	# Linha atual 
	mv t6, a0	# Coluna atual 
	li t5, 0	# Elemento atual da matriz sendo verificado 
	# t1 - endereço dos elementos no vetor 
	# a3 - addrs prim elemento vetor 
	# a0 - coluna jogada
	# a1 - linha jogada 
	# a2 - numero de colunas 
	# a4 - player jogando 
	li t1, 5
	main_diagonal_prepare: 
		beq t2, t1, end_main_diagonal_prepare		# quando a linha == 5
		beq t6, a2, end_main_diagonal_prepare		# quando a coluna == num_colunas
		
		addi t2, t2, 1
		addi t6, t6, 1
		
		j main_diagonal_prepare
	end_main_diagonal_prepare: 
	
	# t2 - Linha atual 
	# t6 - Coluna atual 
	main_diagonal_check: 
	
		# carrega elemento
		mv t1, t6
		addi t1, t1, -1
		mv t0, a2
		mul t0, t0, t2
		add t1, t1, t0
		li t0, 4
		mul t1, t1, t0	# t1 <- endereço do elemento
		add t1, t1, a3
		
		lw t5, 0(t1) 
		
		# Se igual ao player: Incrementa
		bne t5, a4, main_check_loop_current_play_not_player 
		addi t4, t4, 1
		beq t4, t3, win		# Se a soma fecha 4 - jogador ganhou 
		j main_check_loop_next
		
		main_check_loop_current_play_not_player: 
		li t4, 0
		
		main_check_loop_next: 
		
		# Verificacoes de finalizacao da procura 
		beq t2, zero, end_main_diagonal_check
		beq t6, zero, end_main_diagonal_check
		
		# Incrementos do loop 
		addi t2, t2, -1
		addi t6, t6, -1
		
		j main_diagonal_check
		
	end_main_diagonal_check: 
	
	
	# Verificacao de empate - se o tabuleiro for completo e ninguem fechar 4 em linha
	# t0 - iterador (1 ate num_cols)
	# t2 - endereco no vetor 
	# t3 - elemento carregado 
	li t0, 1
	mv t2, a3	# Endereco primeiro elemento 
	
	# Verifica se houve empate (primeira linha preenchida)
	tie_loop: 
		# carrega elemento
		lw t3, 0(t2)
		
		# Se for igual a zero - end_loop
		beq t3, zero, end_tie_loop
		
		# Se chegar ao fim da primeira linha e nao tem zero - tie 
		beq t0, a2, wincheck_tie
		
		addi t0, t0, 1
		addi t2, t2, 4
		
		j tie_loop
	end_tie_loop:
	
	
	
	continue: 
		li a0, 0
		ret
	
	win: 
		li a0, 1
		ret 
	
	wincheck_tie: 
		li a0, 2
		ret
	
	
	
# Funcao de insercao de jogada no tabuleiro
# Parametros	 : a0 - coluna escolhida pelo player para inserção
#		   a1 - player (1 ou 2)
#		   a2 - numero de colunas usadas
# 		   a3 - endereco primeiro elemento vetor 

# retorno: 	 : a0 - 1 -> Inserido
#	              - 0 -> Jogada inválida
# 		:  a1 - linha em que a jogada foi inserida
board_insert: 
	# Logica: 
	# k - coluna escolhida pelo player 
	# L - linha atual 
	# Acesso a coluna es
	
	# verifica se jogada eh invalida 
	mv t0, a0
	addi t0, t0, -1		# t0 <= k-1
	li t2, 4
	mul t0, t0, t2		# Vetor de inteiros - cada um com 4 bytes
	mv t1, a3		
	add t1, t1, t0 
	lw t1, 0(t1)
	beq t1, zero, valid_play
	
	li a0, 0
	ret
	
	# Se a jogada for valida: 
	valid_play:

	li t0, 5 # linha atual 
	
	insertion_loop:
		# Acesso da coluna escolhida na linha L : K + (7|9 * L) - (num_cols - 1)
		# Formula: (K - 1) + 7|9*L
		addi t1, a0, -1		# K - 1
		mul t2, a2, t0		# 7\9 * L
		
		add t1, t1 ,t2
		
		
		li t2, 4
		mul t1, t1, t2		# t1 <= Endereco do elemento da coluna escolhida e linha t0
		
		add t1, a3, t1
		lw t2, 0(t1) 
		beq t2, zero, end_insertion_loop
		
		addi t0, t0, -1
		j insertion_loop
	
	end_insertion_loop:
	
	# t1 <- endereço da inserção da jogada 
	# t0 <- linha em que a inserção ocorre 
	sw a1, 0(t1)

	li a0, 1
	mv a1, t0
	ret
	
	
	
end_program: 
	li a7, 10
	ecall


