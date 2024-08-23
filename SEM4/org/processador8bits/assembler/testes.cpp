#include <iostream>
#include <bitset>
using namespace std;

int main() {
    int num;
    cout << "Digite o número a converter e pressione ENTER: ";
    cin >> num;

    cout << "Número a converter: " << num << endl;

    bitset<6> binario(num); // 32 é o tamanho máximo do número

    cout << "Número convertido em binário: " << binario << endl;

    return 0;
}