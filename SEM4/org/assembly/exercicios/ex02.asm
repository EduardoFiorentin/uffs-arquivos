# Programa que pega três valores e encontra o maior
.text 
	# leitura dos valores do teclado 
	li a7, 5
	
	ecall
	mv s0, a0
	
	ecall
	mv s1, a0
	
	ecall 
	mv s2, a0

verifica_s0_s1:
		
	# Se s0 <= s1 - pula troca_s0_s1
	# se s1 >= s0 
	bge s1, s0, verifica_s1_s2
	
	
troca_s0_s1: # se s0 > s1
	mv s3, s0
	mv s0, s1
	mv s1, s3
	
verifica_s1_s2: 
	# Se s1 <= s2 - pula troca_s1_s2
	# Se s2 >= s1
	bge s2, s1, fim
	
troca_s1_s2: 
	mv s3, s1
	mv s1, s2
	mv s2, s3

fim: 
	li a7, 1
	mv a0, s2
	ecall
