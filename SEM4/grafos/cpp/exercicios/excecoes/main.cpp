#include <iostream>
#include <string> 
#include <vector> 

class Carro {
public: 
    Carro(std::string name, double cap_combustivel) {
        if (cap_combustivel <= 0) throw "Capacidade invalida"; 

        cap_combustivel_ = cap_combustivel; 
    }

    void acelerar() {
        std::cout << "O carro acelerou!" << "\n";
    }

private:
    double cap_combustivel_; 
    std::string name; 


};

int main() {

    try {

        // Carro carro1("Carro 1", -10); 
        // carro1.acelerar(); 
        // "Excecao char: ..."

        // teste com array
        // int arr[] = {1, 2, 3};
        // std::cout << "Elemento em pos inv.:" << arr[4] << std::endl; 
        // sem excecao 

        // teste com vector 
        std::vector<int> vec_int;   
        vec_int.push_back(1);
        vec_int.push_back(2);
        std::cout << vec_int.at(2) << std::endl;
        // excecao geral


    }
    catch (const char* ex) {
        std::cout << "Excecao char: " << ex << std::endl; 
    }

    catch(std::exception& ex) {
        std::cout << "Excecao geral: " << ex.what() << std::endl; 
    }


}