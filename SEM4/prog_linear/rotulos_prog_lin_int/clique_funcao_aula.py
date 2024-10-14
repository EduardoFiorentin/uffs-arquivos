from pyscipopt import Model, quicksum

# Função para gerar um clique a partir de um vértice V
def gera_clique(grafo, V):
    # Adiciona todos os vizinhos de V a Q
    Q = set(grafo[V])  # Q contém os vizinhos de V
    
    # Itera sobre todos os vértices u em Q
    for u in list(Q):  # Usamos list(Q) para evitar problemas de modificação em tempo de execução
        # Verifica se u não é vizinho de algum vértice em Q
        for v in Q:
            if u != v and u not in grafo[v]:  # u não é vizinho de v
                Q.remove(u)
                break  # sai do loop se encontrar que u não é vizinho

    return Q

def main():
    modelo = Model("Problema do Conjunto Independente Máximo com Restrições de Clique")

    # Caminho para a instância do problema
    path = 'instancias_conjunto_independente_maximo\\'
    nome = '4_keller4.clq'
    arq = open(path + nome)

    num_vertices = 0
    adjacencia = {}

    # Inicializa a lista de adjacência
    for linha in arq:
        data = linha.split()
        if data[0] == 'p':
            num_vertices = int(data[2])  # Número de vértices
            for i in range(1, num_vertices + 1):
                adjacencia[i] = set()  # Inicializa a lista de adjacência
            break

    # Cria variáveis binárias x_i para cada vértice
    x = {}
    for i in range(1, num_vertices + 1):
        x[i] = modelo.addVar(f"x_{i}", vtype="INTEGER", lb=0, ub=1)

    # Lê as arestas e constrói a lista de adjacência
    for linha in arq:
        data = linha.split()
        if data[0] == 'e':
            i = int(data[1])
            j = int(data[2])
            adjacencia[i].add(j)
            adjacencia[j].add(i)
            modelo.addCons(x[i] + x[j] <= 1, f"Restricao_x{i}_x{j}")

    # Encontra cliques a partir de cada vértice
    for v in range(1, num_vertices + 1):
        clique = gera_clique(adjacencia, v)
        if clique:  # Se um clique for encontrado, adicionar restrição
            modelo.addCons(quicksum(x[u] for u in clique) <= 1, f"Restricao_Clique_{clique}")

    # Função objetivo: Maximizar o número de vértices escolhidos no conjunto independente
    modelo.setObjective(quicksum(x[i] for i in range(1, num_vertices + 1)), sense="maximize")

    # Parâmetros do modelo (opcionais)
    modelo.setParam("presolving/maxrounds", 0)
    modelo.setParam("separating/maxrounds", 0)

    # Resolver o modelo
    modelo.optimize()

    # Exibir a solução
    soma = 0
    print("Solução:")
    for var in modelo.getVars():
        print(var.name, "=", modelo.getVal(var))
        soma += modelo.getVal(var)

    print(f"Solução ótima: {soma}")

if __name__ == "__main__":
    main()
