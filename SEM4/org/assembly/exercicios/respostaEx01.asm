.data
	A:	.word	0
	B:	.word	0
	C:	.word	0
	TXT: 	.asciz	"Entre com um valor inteiro: " 
	TXT2: 	.asciz	"O resultado da soma eh: "
	
.text 
main: 
	# primeiro valor 
	li a7, 4	# ecall print de string
	la, a0, TXT
	ecall 
	
	li a7, 5	# ecall de ler inteiro
	ecall
	
	mv t0, a0	# t0 recebe primeiro valor 
	
	la s0, A	# carrega endereço de A (RAM)
	sw a0, 0(s0) 	# salva valor de a0 em A
	
	# segundo valor 
	li a7, 4
	la a0, TXT
	ecall
	
	li a7, 5
	ecall 
	
	mv t1, a0
	la s0, B
	
	sw a0, 0(s0)
	
	# terceiro valor 
	li a7, 4
	la a0, TXT
	ecall
	
	li a7, 5
	ecall 
	
	mv t2, a0
	la s0, C
	sw a0, 0(s0)
	add t0, t0, t1
	add t0, t0, t2
	
	# impressão 
	li a7, 4	# Chamada de print string
	la a0, TXT2
	ecall 
	
	li a7, 1	# Chamada de impressão de inteiro 
	mv a0, t0
	ecall 
	
	li a7, 10 	# Chamada que encerra a execução do programa 
	ecall 
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
