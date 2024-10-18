from pyscipopt import Model, quicksum
import numpy as np


def main():
    modelo = Model("Problema do Conjunto Independente Maximo - Instancia de Exemplo")

    path = 'instancias_conjunto_independente_maximo\\'
    nome = '8_san400_0.9_1.clq'
    arq = open(path + nome)

    num_vertices = 0
    data = list()
    x = {}

    for linha in arq:
      data = linha.split()
      if data[0] == 'p':
        num_vertices = int(data[2])
        break

    for i in range(1, num_vertices+1):
      x[i] = modelo.addVar(f"x_{i}", vtype="INTEGER", lb=0, ub=1)

    for linha in arq:
      data = linha.split()
      if data[0] == 'e':
        i = int(data[1])
        j = int(data[2])
        modelo.addCons(x[i] + x[j] <= 1, f"Restricao x{i} x{j}")


    modelo.setObjective(quicksum(x[i] for i in range(1, num_vertices+1)), sense="maximize")

    #modelo.writeProblem(filename="problema_do_conjunto_independente_maximo.lp")

    modelo.setParam("presolving/maxrounds", 0)
    modelo.setParam("separating/maxrounds", 0)

    modelo.optimize()

    soma = 0
    print("Solucao:")
    for x in modelo.getVars():
      print(x.name, "=", modelo.getVal(x))
      soma += modelo.getVal(x)

    print(f"Solução ótima: {soma}")

if __name__ == "__main__":
    main()
