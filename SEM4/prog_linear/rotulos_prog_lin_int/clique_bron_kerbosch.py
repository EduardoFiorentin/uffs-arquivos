from pyscipopt import Model, quicksum

def bron_kerbosch(R, P, X, cliques, adjacencia):
    if not P and not X:
        cliques.append(R)
    while P:
        v = P.pop()
        bron_kerbosch(R.union([v]), P.intersection(adjacencia[v]), X.intersection(adjacencia[v]), cliques, adjacencia)
        X.add(v)


def encontrar_cliques(adjacencia, num_vertices):
    cliques = []
    P = set(range(1, num_vertices + 1))  
    R = set()  
    X = set() 
    bron_kerbosch(R, P, X, cliques, adjacencia)
    return cliques



def main():
    modelo = Model("Problema do Conjunto Independente Maximo com Restricoes de Cliques")

    path = 'instancias_conjunto_independente_maximo\\'
    nome = '4_keller4.clq'
    arq = open(path + nome)

    num_vertices = 0
    adjacencia = {}

    data = list()
    x = {}


    for linha in arq:
        data = linha.split()
        if data[0] == 'p':
            num_vertices = int(data[2])  
            for i in range(1, num_vertices + 1):
                adjacencia[i] = set()  
            break

    
    for i in range(1, num_vertices + 1):
        x[i] = modelo.addVar(f"x_{i}", vtype="INTEGER", lb=0, ub=1)


    for linha in arq:
        data = linha.split()
        if data[0] == 'e':
            i = int(data[1])
            j = int(data[2])
            adjacencia[i].add(j)
            adjacencia[j].add(i)
            modelo.addCons(x[i] + x[j] <= 1, f"Restricao_x{i}_x{j}")


    cliques = encontrar_cliques(adjacencia, num_vertices)

    print(f"Cliques encontrados: {cliques}")


    for clique in cliques:
        modelo.addCons(quicksum(x[v] for v in clique) <= 1, f"Restricao_Clique_{clique}")


    modelo.setObjective(quicksum(x[i] for i in range(1, num_vertices + 1)), sense="maximize")

    modelo.setParam("presolving/maxrounds", 0)
    modelo.setParam("separating/maxrounds", 0)


    modelo.optimize()

    soma = 0
    print("Solução:")
    for var in modelo.getVars():
        print(var.name, "=", modelo.getVal(var))
        soma += modelo.getVal(var)

    print(f"Solução ótima: {soma}")

if __name__ == "__main__":
    main()
