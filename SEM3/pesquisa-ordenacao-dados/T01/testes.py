import random

valores = [] 
for i in range(0, 50):  
    valores.append(random.randint(0, 50))
    
print(str(valores).replace("[", "{").replace("]", "}"))