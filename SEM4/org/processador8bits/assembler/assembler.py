import re

def carregar_arquivo(nome_arquivo):
    with open(nome_arquivo, 'r') as file:
        conteudo = file.read()
    return conteudo

def substituir_termos(conteudo):
    # Substitua os termos da linguagem usando regex
    substituicoes = {
        r'\bldmr\b': '000',
        r'\bldrm\b': '001',
        r'\badd\b': '010',
        r'\bsub\b': '011',
        r'\bmul\b': '100',
        r'\bdiv\b': '101',
        r'\blct\b': '110',
        r',': ' ',
    }
    
    conteudo = conteudo.split("\n")  # Divide o conteúdo em linhas
    
    for i in range(len(conteudo)):
        linha = conteudo[i]
        for padrao, substituto in substituicoes.items():
            linha = re.sub(padrao, substituto, linha)
        
        # Completar o ldmr e ldrm
        linha = re.sub(r'(^00[01][\w\s]+;$)', lambda match: f"{match.group(1)}000", linha)
        
        # Substitui números não cercados por letras pelo seu equivalente em 6 bits binários
        linha = re.sub(r'(^110\s[rd]\d+[\s]?)[\s]?+(\d+);', lambda match: f"{match.group(1)}{format(int(match.group(2)), '06b')}", linha)
        
        # Substitui 'rX' ou 'mX' por 'X' em binário de 3 bits
        linha = re.sub(r'([\w\s]?+)([rm])(\d+)([\w\s]?+)', lambda match: f"{match.group(1)}{format(int(match.group(3)), '03b')}{match.group(4)}", linha)
        
        # Remover espaços e ;
        linha = re.sub(r'[\s]+', "", linha)
        linha = re.sub(r'[;]', "", linha)

        conteudo[i] = linha  # Atualiza a linha na lista de conteúdo
    
    conteudo = '\n'.join(conteudo)  # Junta todas as linhas com quebras de linha
    return conteudo

def formatar_instrucoes(conteudo):
    instrucoes = conteudo.split()  # Divide o conteúdo em instruções
    # print("Aqui:", instrucoes)
    
    inst_formatadas = []
    
    for inst in instrucoes:
        inst_formatadas.append((hex(int(inst, 2))))
        
    if len(inst_formatadas) < 32: 
        inst_formatadas.append("0xe00")
        
    # print(inst_formatadas)
    
    linhas_formatadas = []
    
    for i in range(0, len(inst_formatadas), 4):
        linha = '\t'.join(inst_formatadas[i:i+4])  # Junta 5 instruções por linha com tabulação
        linhas_formatadas.append(linha)
    
    return '\n'.join(linhas_formatadas)  # Junta todas as linhas com quebra de linha


def salvar_arquivo(conteudo, nome_arquivo_saida):
    with open(nome_arquivo_saida, 'w') as file:
        file.write(conteudo)

if __name__ == '__main__':
    # Carregue o conteúdo do arquivo .horn
    conteudo = carregar_arquivo('main.horn')

    # Substitua os termos da linguagem
    conteudo_modificado = substituir_termos(conteudo)
    
    # Formate as instruções conforme solicitado
    conteudo_formatado = formatar_instrucoes(conteudo_modificado)
    

    # Salve o conteúdo formatado no arquivo .hornExe
    salvar_arquivo(conteudo_formatado, 'instruction.hornExe')
