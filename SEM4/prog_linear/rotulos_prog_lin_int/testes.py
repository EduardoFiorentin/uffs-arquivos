# def bron_kerbosch(R, P, X, cliques, adjacencia):
#     if not P and not X:
#         cliques.append(R)
#         return R
    
#     while P:
#         v = P.pop()
#         bron_kerbosch(R.union([v]), P.intersection(adjacencia[v]), X.intersection(adjacencia[v]), cliques, adjacencia)
#         X = X.union({v})


# def encontrar_cliques(adjacencia, num_vertices):
#     cliques = []
#     P = set(range(1, num_vertices + 1))  
#     R = set()  
#     X = set() 
#     bron_kerbosch(R, P, X, cliques, adjacencia)
#     return cliques



def eh_vizinho(v1, v2, grafo):
    return (v1 in grafo[v2]) and (v2 in grafo[v1])

def gera_clique(G: dict):
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
                    if u != viz and not eh_vizinho(u, viz, grafo):
                        Q.remove(u) 
                        remover = True 
                        break
                if remover:
                    break
        
        if len(Q) > 1 and Q not in cliques:
            cliques.append(Q)
    
    return cliques


grafo = {
    1: set({2, 3, 4, 5}),
    2: set({1}),
    3: set({1}),
    4: set({1}),
    5: set({1})
}

cliques = gera_clique(grafo)
print(cliques)

