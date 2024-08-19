.data 
	

.text 
	li a7, 5
	
	ecall
	mv s0, a0
	
	ecall
	mv s1, a0
	
	ecall 
	mv s2, a0
	
	add s0, s0, s1
	add s0, s0, s2
	
	mv a0, s0
	li a7, 1
	ecall