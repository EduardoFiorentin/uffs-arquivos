from pyscipopt import Model, quicksum


def eh_vizinho(v1, v2, grafo):
    return (v1 in grafo[v2]) and (v2 in grafo[v1])

def gera_cliques(G: dict):
    cliques = []
    
    for v in G: 
        Q = set({v})
        for u in G[v]:
            Q.add(u)
        

        remover = True
        while remover:
            remover = False
            for u in list(Q):
                for viz in Q:
                    if u != viz and not eh_vizinho(u, viz, G):
                        Q.remove(u) 
                        remover = True 
                        break
                if remover:
                    break
        
        if len(Q) > 1 and Q not in cliques:
            cliques.append(Q)
    
    return cliques



def main():
    modelo = Model("Problema do Conjunto Independente Máximo com Restrições de Clique")

    path = 'instancias_conjunto_independente_maximo\\'
    nome = '8_san400_0.9_1.clq'
    arq = open(path + nome)

    num_vertices = 0
    adjacencia = {}

    for linha in arq:
        data = linha.split()
        if data[0] == 'p':
            num_vertices = int(data[2]) 
            for i in range(1, num_vertices + 1):
                adjacencia[i] = set() 
            break

    x = {}
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



    cliques = gera_cliques(adjacencia)
    print("Cliques: ", len(cliques))
    for clique in cliques:
        modelo.addCons(quicksum(x[u] for u in clique) <= 1, f"Restricao_Clique_{clique}")


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
