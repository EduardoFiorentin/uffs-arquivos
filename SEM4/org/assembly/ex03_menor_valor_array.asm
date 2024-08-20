.data 
	vec: .word 2, 3, 4, -1, 44, -20
	
.text 	
	
	# t0 - menor valor 
	# t1 - indice do menor valor 
	
	# a1 - variavel de controle do laço 
	# a2 - aux (determina parada do laço) 
	# a3 - posicao inicial do vetor 
	
	li a1, 1 
	li a2, 5
	
	la a3, vec
	
	# Definir primeiro elemento como maior 
	lw t0, 0(a3)
	li t1, 0
	
			
LACO: 	beq a1, a2, FIM_LACO
	
	
	
	addi a1, a1, 1		# incremento do laço 
	j LACO 
	
FIM_LACO:

	li a7, 1
	mv a0, a1
	ecall 
	
