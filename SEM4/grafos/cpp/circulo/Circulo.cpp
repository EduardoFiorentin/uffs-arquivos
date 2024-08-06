#include "./Circulo.h"
#include <iostream>

using namespace std;

Circulo::Circulo(double raio) {
    if (raio <= 0) throw(invalid_argument("Raio inválido"));
    
    raio_ = raio;
}

double Circulo::calcula_area() {
    return 3.14 * this->raio_ * this->raio_;
}

void Circulo::imprime_area() {
    cout << "Área do circulo: " << this->calcula_area() << "\n"; 
}

double Circulo::calcula_perimetro() {
    return 2 * 3.14 * raio_;
}

void Circulo::imprime_perimetro() {
    cout << "Perimetro: " << 2 * 3.14 * raio_ << endl;
}