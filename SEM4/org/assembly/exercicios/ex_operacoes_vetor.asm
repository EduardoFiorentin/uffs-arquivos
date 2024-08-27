# implementar um menu para operacoes em um vetor: 
# 1 - Imprime vetor ()
# 2 - mostra menor valor e mostra sua posição 
# 3 - Mostra maior valor e sua posição 
# 4 - Fazer o swap entre 2 indices 
# 5 - Ordenar vetor

# Passagem de parametros: para todas as funções: 
# a0 <- endereço do primeiro elemento 
# a1 <- tamanho do vetor 
	# para a func 3
# a2 <- indice 1
# a3 <- indice 2

 # Retorno
 # func 1 - nenhum
 # func 2 - a0 <- menor, a1 <- indice 
 # func 3 - a0 <- maior, a1 <- indice 
 # func 4 - a0 <- 1 se der certo, a0 <- 0 se nao
 # func 5 - sem retorno 
 
 .data 
 	vec_size:		.word 	5
 	vec: 			.word 	1, 2, 3, 4, 5
 	
 	txt_intro:			.asciz	"\n\nEscolha uma das opções a seguir: "
 	txt_options:		.asciz 	"\nOpcoes:\n   [1] - Imprimir vetor\n   [2] - Encontrar menor valor\n   [3] - Encontrar maior valor\n   [4] - Swap\n   [5] - Ordenar\n"
 	txt_chose:		.asciz 	"Escolha: "
 	txt_space: 		.asciz 	"  "
 	txt_break_l: 		.asciz 	"\n"
 	
 	# Textos operação 1
 	txt_vector: 		.asciz 	"Vetor: "
 	
 	# Textos operação 2 e 3
 	txt_menor:		.asciz	"Menor elemento: "
 	txt_maior:		.asciz	"Maior elemento: "
 	txt_menor_idx	:	.asciz	"Index: "
 	
 	# Textos operação 4
 	txt_swap_int:		.asciz	"Digite as posições a serem trocadas\n"
 	txt_idx_1:		.asciz	"Idx 1:  "
 	txt_idx_2:		.asciz	"Idx 2:  "
 	txt_swap_ok:		.asciz 	"Swap realizado!\n"
 	txt_no_swap:		.asciz	"Nao eh possivel fazer swap\n"
 	
 	
 .text
 	USER_OPTIONS: 
 		# print do menu
 		li a7, 4
 		la a0, txt_intro
 		ecall

		la a0, txt_options
		ecall
		
		la a0, txt_chose
		ecall
		
		# Pegar opcao do usuario -> s0 
		li a7, 5
		ecall
		
		mv s0, a0
		
		# Carregar informacoes 
		la a0, vec
		#li a1, 5
		lw a1, vec_size
		
		# Chamadas de funcao
		li s1, 1
		beq s0, s1, IMPRIME_VETOR	# se s0 = 1 -> imprime vetor 
		
		li s1, 2
		bne s0, s1, PULA_MENOR
			# Chamada da função de encontrar o menor 
			call ENCONTRA_MENOR_VALOR
			
			# coletar retornos da função 
			mv s2, a0
			mv s3, a1
			
			# printar retorno 
			li a7, 4
			la a0, txt_menor
			ecall 
			
			# print do valor 
			li a7, 1
			mv a0, s2
			ecall
			
			# print quebra de linha 
			li a7, 4
			la a0, txt_break_l
			ecall 
			
			# print texto index 
			li a7, 4
			la a0, txt_menor_idx
			ecall 
			
			# print index do menor  
			li a7, 1
			mv a0, s3
			ecall 
			
			j USER_OPTIONS
		
		PULA_MENOR: 
		
		li s1, 3
		bne s0, s1, PULA_MAIOR
			# Chamada da função de encontrar o maior valor 
			call ENCONTRA_MAIOR_VALOR
			
			# coletar retornos da função 
			mv s2, a0
			mv s3, a1
			
			# printar retorno 
			li a7, 4
			la a0, txt_maior
			ecall 
			
			# print do valor 
			li a7, 1
			mv a0, s2
			ecall
			
			# print quebra de linha 
			li a7, 4
			la a0, txt_break_l
			ecall 
			
			# print texto index 
			li a7, 4
			la a0, txt_menor_idx
			ecall 
			
			# print index do maior  
			li a7, 1
			mv a0, s3
			ecall 
			
			j USER_OPTIONS
		
		PULA_MAIOR: 
		
		li s1, 4
		bne s0, s1, PULA_SWAP
		
			call SWAP
		
			# impressão do menu do swap
			
			
			li a7, 4
			la a0, txt_swap_int
			ecall
			

			
			#coleta do primeiro index
			la a0, txt_idx_1
			ecall
			
			li a7, 5
			ecall
			
			mv a2, a0
			
			# Coleta do segundo index
			li a7, 4
			la a0, txt_idx_2
			ecall
			
			li a7, 5
			ecall
			
			mv a3, a0
			la a0, vec
			
			call SWAP
			
			beq a0, zero, SWAP_NAO_OCORREU
				li a7, 4
				la a0, txt_swap_ok
				ecall
				
				j END_SWAP 
				
			SWAP_NAO_OCORREU: 
				li a7, 4
				la a0, txt_no_swap
				ecall	

		END_SWAP: 
			j USER_OPTIONS
		
		PULA_SWAP: 
		
		j FIM 
		
# Funções 

# Função de impressão de vetor 
	IMPRIME_VETOR: 
		li s0, 0
		li t0, 0
		mv t1, a0	
		
		# Impressão do vetor 
		li a7, 4
		la a0, txt_vector
		ecall
		
		LOOP_IMPRESSAO: 
			bge t0, a1, FIM_LOOP_IMPRESSAO	# quando iterador (t0)  ficar iguai o tamanho do vetor (a1) acaba 
			
			li a7, 1 		
			lw a0, 0(t1)	# Elemento atual do vetor vai para a0 
			ecall
			
			li a7, 4
			la a0, txt_space
			ecall
			
			addi t1, t1, 4	# passar para o proximo elemento 
			addi t0, t0, 1	# Incrementar iterador do for 
			
			j LOOP_IMPRESSAO
			
		FIM_LOOP_IMPRESSAO: 
			j USER_OPTIONS
		

# Função encontrar menor valor 
	ENCONTRA_MENOR_VALOR: 
		li t0, 1	# iterator = 1
		mv t1, a0 	# Cópia do inicio do vetor 
		
		 
		
		lw s2, 0(t1)	# primeiro elemento começa como maior 	
		li s3, 0 		# index prim elemento 
		
		LOOP_MENOR: 
			# Confere condição de finalização 
			bge t0, a1, FIM_LOOP_MENOR
			
			# conferir próximo elemento na memória 
			addi t1, t1, 4 	
			
			# Confere se o iterado é menor do que o menor atual 
			lw t2, 0(t1)
			bge t2, s2, NAO_TROCA_MENOR
			
				mv s2, t2
				mv s3, t0
			
			NAO_TROCA_MENOR: 
			
			addi t0, t0, 1
			j LOOP_MENOR
			
		FIM_LOOP_MENOR: 
			# a0 <- menor valor 
			# a1 <- indice 
			mv a0, s2
			mv a1, s3
			
			ret
			
# Encontrar maior valor 
	ENCONTRA_MAIOR_VALOR: 
		li t0, 1	# iterator = 1
		mv t1, a0 	# Cópia do inicio do vetor 
		
		 
		
		lw s2, 0(t1)	# primeiro elemento começa como maior 	
		li s3, 0 		# index prim elemento 
		
		LOOP_MAIOR: 
			# Confere condição de finalização 
			bge t0, a1, FIM_LOOP_MAIOR
			
			# conferir próximo elemento na memória 
			addi t1, t1, 4 	
			
			# Confere se o iterado é maior do que o maior atual 
			lw t2, 0(t1)
			bge s2, t2, NAO_TROCA_MAIOR
			
				mv s2, t2
				mv s3, t0
			
			NAO_TROCA_MAIOR: 
			
			addi t0, t0, 1
			j LOOP_MAIOR
			
		FIM_LOOP_MAIOR: 
			# a0 <- maior valor 
			# a1 <- indice 
			mv a0, s2
			mv a1, s3
			
			ret
	
	
	SWAP: 
		blt a2, zero, NO_SWAP
		bge a2, a1, NO_SWAP
		blt a3, zero, NO_SWAP
		bge a3, a1, NO_SWAP
		
		li t0, 4
		mv t1, a2
		mv t2, a3
		mul t1, t1, t0
		mul t2, t2, t0
		
		add t1, a0, t1
		add t2, a0, t2
		
		# Carregar valores do vetor pro registrador 	
		lw a2, 0(t1) 
		lw a3, 0(t2)
		
		sw a2, 0(t2) 
		sw a3, 0(t1)                                                                                                                                                                                                                                                                                                                                             
		
		li a0, 1
		ret
			
		NO_SWAP: 
			li a0, 0
			ret
		
		
		
		
	
	
	
	
	FIM: 
		li a7, 10
		ecall
	
	
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
