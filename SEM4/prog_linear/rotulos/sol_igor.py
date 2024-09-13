from pulp import *
import matplotlib.pyplot as plt
import matplotlib.patches as pltp

EPSILON = 0.001

class Rectangle:
  def __init__(self, x0, y0, x1, y1):
    self.x0 = x0
    self.y0 = y0
    self.x1 = x1
    self.y1 = y1

def sobrepoe(a, b):
  if(a.x1 < b.x0 or a.y1 < b.y0 or a.x0 > b.x1 or a.y0 > b.y1):
    return False
  return True

def calcula_limites_coords_retgs(retgs):
  xmin = None
  xmax = None
  ymin = None
  ymax = None

  for retg in retgs:
    if (xmin is None) or (retg.x0 < xmin):
        xmin = retg.x0
    if (xmax is None) or (retg.x1 > xmax):
        xmax = retg.x1
    if (ymin is None) or (retg.y0 < ymin):
        ymin = retg.y0
    if (ymax is None) or (retg.y1 > ymax):
        ymax = retg.y1

    return [0, xmax, 0, ymax]

def plota_sol(modelo, num_rotulos, retgs_rotulos):
    limites_coords = calcula_limites_coords_retgs(retgs_rotulos)

    fig, ax = plt.subplots()

    for retg in retgs_rotulos:
        ax.add_patch(pltp.Rectangle(
            (retg.x0, retg.y0), (retg.x1 - retg.x0),
            (retg.y1 - retg.y0), edgecolor="black", fill=False,
            lw=2))

    x = modelo.variablesDict()
    for i in range(num_rotulos):
        if abs(x[f"x_{i}"].value() - 1) <= EPSILON: 
            retg = retgs_rotulos[i]
            ax.add_patch(pltp.Rectangle(
                (retg.x0, retg.y0),
                (retg.x1 - retg.x0),
                (retg.y1 - retg.y0), edgecolor="blue",
                fill=False, lw=2))

    ax.set_xlim(limites_coords[0] - 10, limites_coords[1] + 10)
    ax.set_ylim(limites_coords[2] - 10, limites_coords[3] + 10)

    plt.show()


def main():

  model = LpProblem("Problema dos Rótulos", LpMaximize)

  qt = int(input())

  x = LpVariable.dicts("x", range(qt), 0, 1, LpInteger)

  rectangles = []

  for i in range(qt):
    linha = [float(n) for n in input().split()]
    rectangles.append(Rectangle(*linha[1:]))

  model += (lpSum([x[i] for i in range(qt)]), "Funcão Objetivo")

  for i in range(qt): 
    for j in range(i + 1, qt):
      if(sobrepoe(rectangles[i], rectangles[j])):
        model += (x[i] + x[j] <= 1) 

  model.solve()

  result = model.variables()

  print(value(model.objective))

  for i in range(qt):
    if(result[i].value()):
      print(f"{result[i].name} {rectangles[i].x0} {rectangles[i].y0} {rectangles[i].x1} {rectangles[i].y1}")

  plota_sol(model, qt, rectangles)


if __name__ == "__main__":
    main()
