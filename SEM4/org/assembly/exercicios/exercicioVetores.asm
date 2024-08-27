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
 	vec_size:		.word 	9
 	vec: 			.word 	6, 2, 5, 4, 8, 43, -4, 33, 412
 	
 	txt_intro:		.asciz	"\n\nEscolha uma das opções a seguir: "
 	txt_options:		.asciz 	"\nOpcoes:\n   [1] - Imprimir vetor\n   [2] - Encontrar menor valor\n   [3] - Encontrar maior valor\n   [4] - Swap\n   [5] - Ordenar\n"
 	txt_choise:		.asciz 	"Escolha: "
 	txt_space: 		.asciz 	"  "
 	txt_break_l: 		.asciz 	"\n"
 	
 	# Textos operação 1
 	txt_vector: 		.asciz 	"Vetor: "
 	
 	# Textos operação 2 e 3
 	txt_menor:		.asciz	"Menor elemento: "
 	txt_maior:		.asciz	"Maior elemento: "
 	txt_idx	:	.asciz	"Index: "
 	
 	# Textos operação 4
 	txt_swap_int:		.asciz	"Digite as posições a serem trocadas\n"
 	txt_idx_1:		.asciz	"Idx 1:  "
 	txt_idx_2:		.asciz	"Idx 2:  "
 	txt_swap_ok:		.asciz 	"Swap realizado!\n"
 	txt_no_swap:		.asciz	"Nao eh possivel fazer swap\n"
 
 .text
 
 	MAIN: 
 		# print menu
 		li a7, 4 
 		la a0, txt_intro
 		ecall 
 		
 		la a0, txt_options 
 		ecall 
 		
 		la a0, txt_choise 
 		ecall 
 
 		# escolha do usu�rio 
 		li a7, 5
 		ecall 
 		
 		mv s0, a0	# s0 <- op��o escolhida pelo usu�rio 
 		
 		# Opcao 1 - imprime vetor 
 		li s1, 1
 		beq s0, s1, PREPARA_IMPRIME_VETOR
 		
 		# Opcao 2 - encontra menor valor 
 		li s1, 2
 		beq s0, s1, PREPARA_ENCONTRA_MENOR
 		
 		# Opcao 3 - encontra maior 
 		li s1, 3
 		beq s0, s1, PREPARA_ENCONTRA_MAIOR
 		
 		# Opcao 4 - swap 
 		li s1, 4
 		beq s0, s1, PREPARA_SWAP
 		
 		# Opcao 5 - ordenacao 
 		li s1, 5
 		beq s0, s1, PREPARA_ORDENACAO
 		
 		# Outros - finaliza programa
 		j FIM 
 		
 		
 	PREPARA_IMPRIME_VETOR:
 		la a0, vec
 		lw a1, vec_size 
 		call IMPRIME_VETOR
 		j MAIN
 		
 	
 	PREPARA_ENCONTRA_MENOR:
 		la a0, vec
 		lw a1, vec_size 
 		call ENCONTRA_MENOR
 		
 		# a0 <- menor valor 
 		# a1 <- index 
 		
 		# coletar retornos da funcao
 		mv s2, a0
 		mv s3, a1
 		
 		# print retorno
 		li a7, 4
 		la a0, txt_menor
 		ecall
 		li a7, 1
 		mv a0, s2
 		ecall
 		
 		# quebra de linha
 		li a7, 4
 		la a0, txt_break_l
 		ecall  		
 		
 		# print texto do index index
 		li a7, 4
 		la a0, txt_idx
 		ecall 
 		
 		# print index 
 		li a7, 1
 		mv a0, s3
 		ecall
 		
 		j MAIN
 	
 	
 	PREPARA_ENCONTRA_MAIOR:
 		la a0, vec
 		lw a1, vec_size 
 		
 		call ENCONTRA_MAIOR
 		
 		# a0 <- menor valor 
 		# a1 <- index 
 		
 		# coletar retornos da funcao
 		mv s2, a0
 		mv s3, a1
 		
 		# print retorno
 		li a7, 4
 		la a0, txt_maior
 		ecall
 		li a7, 1
 		mv a0, s2
 		ecall
 		
 		# quebra de linha
 		li a7, 4
 		la a0, txt_break_l
 		ecall  		
 		
 		# print texto do index index
 		li a7, 4
 		la a0, txt_idx
 		ecall 
 		
 		# print index 
 		li a7, 1
 		mv a0, s3
 		ecall
 		
 		j MAIN
 	
 	PREPARA_SWAP:
 		# a2 <- index 1
 		# a3 <- index 2
 		
 		# Impressao menu
 		li a7, 4
 		la a0, txt_swap_int
 		ecall
 		
 		# coleta primeiro index
 		la a0, txt_idx_1
 		ecall
 		li a7, 5
 		ecall 
 		mv a2, a0
 		
 		# coleta index 2
 		li a7, 4
 		la a0, txt_idx_2
 		ecall
 		li a7, 5
 		ecall  
 		mv a3, a0
 		
 		
 		# carregar vetor e tamanho
 		la a0, vec
 		lw a1, vec_size
 		
 		
 		call SWAP
 		
 		j MAIN
 		
 		
 	PREPARA_ORDENACAO:
  		la a0, vec
 		lw a1, vec_size
 		
 		call ORDENACAO
 
 
 # Funcoes
 
 	IMPRIME_VETOR: 
 		li s0, 0
 		li t0, 0
 		mv t1, a0
 		
 		# impressao label
 		li a7, 4
 		la a0, txt_vector
 		
 		LOOP_IMPRESSAO:
 			bge t0, a1, FIM_LOOP_IMPRESSAO
 			
 			# imprime valor do endereco atual
 			li a7, 1
 			lw a0, 0(t1) 
 			ecall
 		
 			# imprime espa�o
 			li a7, 4
 			la a0, txt_space
 			ecall 
 			
 			addi t1, t1, 4 		# atualiza endere�o de t1 para o proximo item do vetor 	
 			addi t0, t0, 1		# incrementa iterador do loop
 			
 			j LOOP_IMPRESSAO
 		
 		FIM_LOOP_IMPRESSAO: 
 			
 			ret
 
 
 
 	ENCONTRA_MENOR:
 		li t0, 1	# iterador do loop <- 1
 		mv t1, a0	# salvar end. inicio vetor 
 		
 		lw s2, 0(t1) 
 		li s3, 0	# index primeiro elemento
 		
 		LOOP_ENCONTRA_MENOR:
 		
 			bge t0, a1, FIM_LOOP_ENCONTRA_MENOR
 			
 			addi t1, t1, 4
 			
 			# condi��o de troca
 			lw t2, 0(t1) 
 			bge t2, s2, NAO_TROCA_MENOR
 			
 			mv s2, t2	# atualiza item
 			mv s3, t0	# atualiza index
 			
 			NAO_TROCA_MENOR:
 			
 			addi t0, t0, 1
 			j LOOP_ENCONTRA_MENOR
 		
 		FIM_LOOP_ENCONTRA_MENOR: 
 			
 			# troca os dados para registrador de retorno
 			mv a0, s2
 			mv a1, s3
 			ret
 	
 	
 	
 	ENCONTRA_MAIOR: 
 		li t0, 1	# iterador do loop <- 1
 		mv t1, a0	# salvar end. inicio vetor 
 		
 		lw s2, 0(t1) 
 		li s3, 0	# index primeiro elemento
 		
 		LOOP_ENCONTRA_MAIOR:
 			bge t0, a1, FIM_LOOP_ENCONTRA_MAIOR
 			
 			# Atualiza endereco para o proximo elemento do vetor  
 			addi t1, t1, 4
 			
 			lw t2, 0(t1)
 			bge s2, t2, NAO_TROCA_MAIOR
 			
 			# Trocar maior item conhecido do vetor 
 			mv s2, t2
 			mv s3, t0
 			
 			NAO_TROCA_MAIOR: 
 			
 			addi t0, t0, 1		# atualiza iterador do loop
 			j LOOP_ENCONTRA_MAIOR
 		
 		FIM_LOOP_ENCONTRA_MAIOR: 
 			
 			# a0 <- maior valor encontrado 
 			# a1 <- indice do valor
 			
 			mv a0, s2
 			mv a1, s3
 			ret
 		
 		
 	SWAP: 
 		# a0 <- primeiro indice vetor 
 		# a1 <- tamanho vetor
 		# a2 <- index troca 1
 		# a3 <- index troca 2
 		
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
 		
 		lw a2, 0(t1)
 		lw a3, 0(t2)
 		
 		sw a2, 0(t2) 
 		sw a3, 0(t1) 
 		
 		li a0, 1
 		ret
 		
 		NO_SWAP: 
 		li a0, 0
 		ret
 		
 		
 	ORDENACAO: 
 		
 		# a0 <- posicao atual prim elemento
 		# a1 <- tam vetor 
 		# s10 <- elemento inicial do vetor 
 		# s9 <- tamanho do vetor 
 		
 		mv s10, a0
 		mv s9, a1


 			
 		LOOP_ORDENACAO: 
 			beqz s9, FIM_LOOP_ORDENACAO
 			
 			# Encontra proximo menor valor
 				# prepara encontra_menor
 			mv a0, s10
 			mv a1, s9
 			
 			call ENCONTRA_MENOR
 			# a0 <- maior elemento
 			# a1 <- indice do menor 
 			
 			# Swap entre o inicio aual do vetor e menor valor atual
 				# prepara swap 
 				# a2 <- index 1
 				# a3 <- index 2
 				
 			mv a0, s10
 			mv a3, a1
 			mv a1, s9
 			li a2, 0
 			
 			call SWAP
 			# a0 <- 1 ou 0 
 			
 			
 			# Atualiza inicio do vetor 
 			addi s10, s10, 4
 			
 			# atualiza tamanho do vetor
 			addi s9, s9, -1
 			
 			j LOOP_ORDENACAO
 			
 		FIM_LOOP_ORDENACAO: 
 		 		
 		FIM_ORDENACAO: 
 			j MAIN
 
 	FIM: 
 		li a7, 10
 		ecall 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

  
