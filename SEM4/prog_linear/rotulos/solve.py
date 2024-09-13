from pulp import * 

modelo = LpProblem("Problema dos rotulos", LpMaximize)

x1 = LpVariable("x1", 0, 1, LpInteger) # nome, menor e maior valor da variavel 
x2 = LpVariable("x2", 0, 1, LpInteger) # nome, menor e maior valor da variavel 
x3 = LpVariable("x3", 0, 1, LpInteger) # nome, menor e maior valor da variavel 

modelo += (x1 + x2 <= 1, "Restricao 1 e 2")     #adicao da restricao 

modelo += (x1 + x2 + x3, "Funcao objetivo")

modelo.solve() 

print(f"Valor máximo: {value(modelo.objective())}")

for x in modelo.variables: 
    print(x.name, " = ", x.value())