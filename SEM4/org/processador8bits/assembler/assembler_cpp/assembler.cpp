#include <iostream>
#include <fstream> 
#include <string>
#include <regex>
#include <iterator>
#include <bitset>
#include <chrono> 
#include <cmath>

using namespace std;

string generate_bitset_const(int value) {
    return std::bitset<6>(static_cast<unsigned long long>(value)).to_string();
}

string generate_bitset_address(int value) {
    return std::bitset<3>(static_cast<unsigned long long>(value)).to_string();
}

std::vector<std::string> loadInstructions(const std::string& input_filename) {
    std::vector<std::string> instructions;
    std::ifstream file(input_filename);
    std::string line;
    
    if (file.is_open()) {
        while (std::getline(file, line)) {
            instructions.push_back(line);
        }
        file.close();
    } else {
        std::cerr << "File has not found: " << input_filename << std::endl;
    }
    
    return instructions;
}

void saveInstructions(const std::vector<std::string>& instructions, const std::string& input_filename) {
    std::ofstream outfile(input_filename);
    
    if (outfile.is_open()) {
        for (const auto& instruction : instructions) {
            outfile << instruction;
        }
        outfile.close();
    } else {
        std::cerr << "The system could not create a new file: " << input_filename << std::endl;
    }
}

vector<string> substitute(vector<string> instructions) {

    // regras:
    vector<pair<regex, string>> rules = {
        
        // substituir identificadores
        pair<regex, string> { regex{ "ldmr" }, "000" }, 
        pair<regex, string> { regex{ "ldrm" }, "001" }, 
        pair<regex, string> { regex{ "add" }, "010" },
        pair<regex, string> { regex{ "sub" }, "011" },
        pair<regex, string> { regex{ "mul" }, "100" },
        pair<regex, string> { regex{ "div" }, "101" },
        pair<regex, string> { regex{ "lct" }, "110" }
    }; 

    // alterações de tradução simples
    for (int i = 0; i < rules.size(); i++) {
        for (int j = 0; j < instructions.size(); j++) {

            instructions[j] = regex_replace(instructions[j], rules[i].first, rules[i].second); 
        }
    }


    // substituições envolvendo grupos

    int num; 


    // numeros de constantes para binário 
    regex const_pattern     ("\\s(\\d+);");
    for (auto &text: instructions) {
        
        std::smatch matches; 
        
        while (regex_search(text, matches, const_pattern)) {
            num = stoi(matches.str()); 
            text = regex_replace(text, const_pattern, generate_bitset_const(num), regex_constants::format_first_only);
        }
    }

    // adicionar endereços de registradores e memória
    regex reg_mem_pattern   ("[rm](\\d+)");
    for (auto &text: instructions) {
        std::smatch storage_matches; 
        while (regex_search(text, storage_matches, reg_mem_pattern)) {
            num = stoi(storage_matches[1].str());
            text = regex_replace(text, reg_mem_pattern, generate_bitset_address(num), regex_constants::format_first_only);
        }
    }   


    // remover , ; e espaços
    regex operators_pattern("[\\s;,]+");
    for (auto &text: instructions) {
        text = std::regex_replace(text, operators_pattern, "");
    }

    // completar instruções com bits faltando 
        // instruções de carregamento registrador / memória necessitam apenas de 9 bits, tendo os 3 últmos como 'don't care' 
    for (auto &text: instructions) {
        if (text.length() < 12) text += "000"; 
    }

    return instructions; 
}

// Formata as instruções para 5 instruções por linha, separadas por tabulação
// Permite copiar e colar as instruções na memória no programa "digital"
vector<string> formatInstructions(vector<string> instructions) {
    int instr_position = 0;
    string instr_line;
    vector<string> instructions_formated;


    for (int i = 0; i < instructions.size(); i++) {
        instructions[i] = "0b" + instructions[i]; 
        instr_line += instructions[i];

        if ((i + 1) % 4 == 0) { // Modifiquei para (i + 1) para garantir que só após 5 instruções a linha seja adicionada
            instr_line += "\n"; 
            instructions_formated.push_back(instr_line);
            instr_line = ""; // Limpa instr_line para a próxima linha de instruções
        } else {
            instr_line += "\t"; // Adiciona uma tabulação entre as instruções
        }
    }

    // Adiciona qualquer instrução restante que não completou um grupo de 5
    if (!instr_line.empty()) {
        instructions_formated.push_back(instr_line);
    }

    return instructions_formated;
}



int main(int argc, char* argv[]) {

    auto inicio = chrono::high_resolution_clock::now();

    string input_filename, output_filename; 

    if (argc > 1) {
        input_filename = argv[1]; 
    }
    else input_filename = "index";

    if (argc > 2) {
        output_filename = argv[2]; 
    }
    else output_filename = "instructions";

    vector<string> instructions, new_instructions, formated_instructions;
    
    instructions = loadInstructions(input_filename);
    new_instructions = substitute(instructions);

    // adição da instrução que dita a finalização do programa 
    new_instructions.push_back("111000000000");


    formated_instructions = formatInstructions(new_instructions);

    saveInstructions(formated_instructions, output_filename); 

    auto time = chrono::high_resolution_clock::now() - inicio;
    long double seconds = chrono::duration_cast<std::chrono::milliseconds>(time).count();
    std::cout << "Compile time: " << seconds / 1000 << " secs" << endl; 

    return 0; 
}