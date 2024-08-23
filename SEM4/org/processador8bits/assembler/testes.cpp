#include <iostream>
#include <bitset>
using namespace std;

std::string toBinary(int number) {
    // Convertendo para binário usando bitset de 6 bits e conversão explícita
    return std::bitset<6>(static_cast<unsigned long long>(number)).to_string();
}

int main() {
    int num;
    cout << "Digite o número a converter e pressione ENTER: ";
    cin >> num;

    cout << "Número a converter: " << num << endl;

    string binario = toBinary(num);

    cout << "Número convertido em binário: " << binario << endl;

    return 0;
}