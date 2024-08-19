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
	
	la vec, a3
	
LACO: 	beq a1, a2, FIM_LACO
	
	
	
FIM_LACO:
	nop 
	