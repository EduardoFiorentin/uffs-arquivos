# Foto no grupo da resposta 

# Programa que pega tr�s valores e encontra o maior 
# (Usando estruturas parecidas com ifs de linguagens alto nivel) 
.data
	A: .word 2
	B: .word 3
	C: .word 1
	TXT_AM:	.asciz	"A � o maior: "
	TXT_BM:	.asciz	"B � o maior: "
	TXT_CM: .asciz	"C � o maior: "

.text 
	# Carregar valores 
	la t0, A
	lw t0, 0(t0)
	
	la t1, B
	lw t1, 0(t1)
	
	la t2, C
	lw t2, 0(t2)
	
	# Calcular maior
	
	ble t0, t1, AMenIB	# Mant�m se a > b
	
	ble t0, t2, AMenIC	# Mant�m se a > c
	
	# a � o maior 
	li a7, 4	# ecall print de string
	la, a0, TXT_AM
	ecall 
	
	j Final
AMenIB: 
		
	ble t1, t2, BMenIC	# Mant�m se b > c
	
	# B � o maior 
	li a7, 4	# ecall print de string
	la, a0, TXT_BM
	ecall 
	
	j Final
	
AMenIC: 
	
	# C � o maior 
	li a7, 4	# ecall print de string
	la, a0, TXT_CM
	ecall 

	j Final
BMenIC:
	# C � o maior 
	li a7, 4	# ecall print de string
	la, a0, TXT_CM
	ecall 
	j Final
	
Final: 
	li a7, 10	# Finalizar programa 
	ecall

	