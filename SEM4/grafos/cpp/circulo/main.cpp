#include "Circulo.h"
#include <stack> 
#include <queue>
#include <iostream>

using namespace std; 

int main() {

    try {
        Circulo circ1(2); 
        Circulo circ2(-3);

        circ1.imprime_area(); 
        circ2.imprime_area(); 

        circ1.imprime_perimetro();
    } 
    catch(exception &err) {
        cerr << err.what() << "\n";     // imprimir excessões
        // cerr - impressão de erros 
    }



// pilha
    stack<int> pilha; 



    pilha.push(2);
    pilha.push(1);
    
    cout << "el 1: " << pilha.top() << endl;
    pilha.pop();
    cout << "el 2: " << pilha.top() << endl;
    pilha.pop();

// fila

    queue<int> fila; 

    fila.push(1); 
    fila.push(3); 

    cout << "el 1: " << fila.front() << endl; 
    fila.pop();
    
    cout << "el 2: " << fila.front() << endl; 
    fila.pop();

    

    return 0;  

}