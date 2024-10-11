from pyscipopt import Model, quicksum

def main():
    modelo = Model("Problema do Conjunto Independente Maximo - Instancia de Exemplo")

    x1 = modelo.addVar(f"x_1", vtype="INTEGER", lb=0, ub=1)
    x2 = modelo.addVar(f"x_2", vtype="INTEGER", lb=0, ub=1)
    x3 = modelo.addVar(f"x_3", vtype="INTEGER", lb=0, ub=1)

    modelo.addCons(x1 + x2 <= 1, f"Restricao x1 x2")

    modelo.setObjective(x1 + x2 + x3, sense="maximize")

    modelo.writeProblem(filename="problema_do_conjunto_independente_maximo.lp")

    modelo.setParam("presolving/maxrounds", 0)
    modelo.setParam("separating/maxrounds", 0)

    modelo.optimize()

    print("Solucao:")
    for x in modelo.getVars():
        print(x.name, "=", modelo.getVal(x))

if __name__ == "__main__":
    main()

# pra deixar generico
#modelo.addCons(x[i + 1] + x[j + 1] <= 1, f"Restricao x{i + 1} x{j + 1}")

#modelo.setObjective(quicksum(x[i] for i in range(1, (num_vertices + 1))), sense="maximize")
