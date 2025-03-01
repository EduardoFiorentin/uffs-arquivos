from pulp import *

def sobreposicao_retangulo(x1, y1, x2, y2, x3, y3, x4, y4): 
    if (x3 > x2 or y4 < y1 or x4 < x1 or y3 > y2): return False
    return True

num_rotulos = int(input())
retangulos = [] 


modelo = LpProblem("Problema dos rotulos", LpMaximize)
x = LpVariable.dicts("x", range(num_rotulos), 0, 1, LpInteger)

# input triangulos 
for i in range(0, num_rotulos):
    retangulos.append(list(map(float, input().split())))
    
print(retangulos)


# adição das restrições
for i in range(num_rotulos):
    for j in range(i+1, num_rotulos): 
        
        # se sobrepõe triangulos[i] com triangulos[j]
        if (sobreposicao_retangulo(retangulos[i][1], retangulos[i][2], retangulos[i][3], retangulos[i][4], retangulos[j][1], retangulos[j][2], retangulos[j][3], retangulos[j][4])): 
            modelo += (x[i] + x[j] <= 1) 



modelo += (lpSum([x[i] for i in range(num_rotulos)]), "Funcao objetivo")

modelo.solve() 

print(f"Valor máximo: {value(modelo.objective)}")   

for x in modelo.variables(): 
    print(x.name, " = ", x.value())