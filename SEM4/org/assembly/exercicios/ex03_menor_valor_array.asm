.data 
	vec: .word -82, -300, 4, -1, 44, -2000
	
.text 	
	
	# t0 - menor valor 
	# t1 - indice do menor valor 
	# t2 - elemento atual sendo comparado 
	
	# a1 - variavel de controle do laço 
	# a2 - aux (determina parada do laço) 
	# a3 - posicao inicial do vetor 
	
	li a1, 1 
	li a2, 6
	
	la a3, vec
	
	# Definir primeiro elemento como maior 
	lw t0, 0(a3)
	li t1, 0
	 
	
			
LACO: 	beq a1, a2, FIM_LACO
	
	# Acessar posição no vetor
	addi a3, a3, 4		# Como o primeiro elemento já foi conciderado, partimos pro segundo
	lw t2, 0(a3) 
	
	bge t2, t0, ELEMENTO_MAIOR # if (novo elemento < menor_atual)
	
	# Se o novo elemento for menor 
	mv t0, t2
	mv t1, a1
	
ELEMENTO_MAIOR: 
	
	addi a4, a4, 4
	addi a1, a1, 1		# incremento do laço 
	j LACO 
	
FIM_LACO:

	li a7, 1
	mv a0, t0
	ecall 
	
