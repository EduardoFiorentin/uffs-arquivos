import pyautogui
import time

def type_pattern(pattern, times):
    for _ in range(times):
        for num in pattern:
            pyautogui.write(str(num))  # Digita o número
            pyautogui.press('enter')  # Pressiona Enter após o número
            time.sleep(0.1)  # Pequena pausa para evitar erros de velocidade

# Padrões
pattern1 = [1, 2, 3]
pattern2 = [6, 5, 4]
pattern3 = [7, 8, 9]

# Aguardar alguns segundos antes de começar para dar tempo de trocar para o programa alvo
time.sleep(3)

# Digitar cada padrão 6 vezes
type_pattern(pattern1, 6)
type_pattern(pattern2, 6)
type_pattern(pattern3, 6)
