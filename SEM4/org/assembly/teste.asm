.text

     li a1, 8
     li a2, 4
     
     li a4, 1
     li a5, 0
     
     # se a4 = a5 - pula pra soma
     beq a4, a5, sum

     # se a4 < a5 - pula pra sub
     blt a4, a5, sub
     
     # se a4 > a5 - pula pro fim 
     blt a5, a4, end
     
sum: 
    add a0, a1, a2
    jal end

sub: 
    sub a0, a1, a2


end: 
     nop
    