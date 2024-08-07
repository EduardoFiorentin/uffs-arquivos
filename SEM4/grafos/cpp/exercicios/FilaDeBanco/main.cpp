#include "Sistema.h"
#include <iostream>

using namespace std;

int main() {
    Sistema sistema; 

    Cliente cl1(1, false);
    Cliente cl2(2, true);

    sistema.adicionar(cl1); 
    sistema.adicionar(cl2);

    cout << "Chamada 1: " << sistema.proximo().getId() << endl;
    cout << "Chamada 2: " << sistema.proximo().getId() << endl;
}