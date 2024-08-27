import re

SOURCE_FILE = "main"
TARGET_FILE = "instruction"

def load_file(input_file_name):
    with open(input_file_name, 'r') as file:
        content = file.read()
    return content

def replace_expressions(content):
    # Substitui os termos da linguagem usando regex
    changes = {
        r'\bldmr\b': '000',
        r'\bldrm\b': '001',
        r'\badd\b': '010',
        r'\bsub\b': '011',
        r'\bmul\b': '100',
        r'\bdiv\b': '101',
        r'\blct\b': '110',
        r',': ' ',
    }
    
    content = content.split("\n") # Separa o conteúdo em uma lista com cada item sendo uma linha 
    
    for i in range(len(content)):
        row = content[i]
        for pattern, substitute in changes.items():
            row = re.sub(pattern, substitute, row)
        
        # Completar o ldmr e ldrm com zeros no final
        row = re.sub(r'(^00[01][\w\s]+;$)', lambda match: f"{match.group(1)}000", row)
        
        # Substitui numero da instrução lct pelo equivalente em binário formatado para 6 digitos
        row = re.sub(r'(^110\s[rd]\d+[\s]?)[\s]?+(\d+);', lambda match: f"{match.group(1)}{format(int(match.group(2)), '06b')}", row)
        
        # Substitui valores vindos com letras 'r' ou 'm' para o equivalente binário do número
        # Substitui a notação de registrador e memória por seu endereço equivalente
        row = re.sub(r'([\w\s]?+)([rm])(\d+)([\w\s]?+)', lambda match: f"{match.group(1)}{format(int(match.group(3)), '03b')}{match.group(4)}", row)
        
        # Remover espaços e ';'
        row = re.sub(r'[\s]+', "", row)
        row = re.sub(r'[;]', "", row)

        content[i] = row 
    
    content = '\n'.join(content)  # Junta todas as linhas com quebras de linha
    print(content)
    return content

def format_instructions(content):
    instructions = content.split()  # Divide o conteúdo em instruções
    # print(instrucoes)
    
    # formated_instructions = []
    formated_instructions = instructions
    
    # for inst in instructions:
    #     formated_instructions.append((hex(int(inst, 2))))
        
    if len(formated_instructions) < 32: 
        formated_instructions.append("111000000000") # instrução que define o ponto de parada da execução no circuito 
        
    # print(inst_formatadas)
    
    formatted_rows = []
    
    for i in range(0, len(formated_instructions), 4):
        row = '\t'.join(formated_instructions[i:i+4])  # Junta 5 instruções por linha com tabulação
        formatted_rows.append(row)
    
    return '\n'.join(formatted_rows)  # Junta todas as linhas com quebra de linha


def save_file(content, file_name):
    with open(file_name, 'w') as file:
        file.write(content)

if __name__ == '__main__':
    # Carregue o conteúdo do arquivo .horn
    content = load_file(SOURCE_FILE)

    # Substitui os termos da sintaxe pelos codigos binários correspondentes 
    modified_content = replace_expressions(content)
    
    # Transforma as instruções de binário para exadecimal
    formated_content = format_instructions(modified_content)
    

    # Salve o conteúdo formatado no arquivo .hornExe
    save_file(formated_content, TARGET_FILE)
