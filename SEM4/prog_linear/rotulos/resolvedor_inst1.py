from pulp import *

def main():
    modelo = LpProblem("Problema do Rotulos - Instancia 1", LpMaximize)

    x1 = LpVariable("x1", 0, 1, LpInteger)
    x2 = LpVariable("x2", 0, 1, LpInteger)
    x3 = LpVariable("x3", 0, 1, LpInteger)

    modelo += (x1 + x2 + x3, "Funcao objetivo")

    modelo += (x1 + x2 <= 1, "Restricao de intersecao dos rotulos 1 e 2")

    modelo.writeLP("problema_dos_rotulos.lp")

    modelo.solve()

    print("Status:", LpStatus[modelo.status])

    for x in modelo.variables():
        print(x.name, "=", x.value())

    print("Valor otimo:", value(modelo.objective))

if __name__ == "__main__":
    main()
