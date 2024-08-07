#ifndef SISTEMA
#define SISTEMA
#include "Sistema.h"
#include <queue>
#include "Cliente.h"
#include <iostream>

using namespace std; 

Sistema::Sistema() {
    queue_ = std::queue<Cliente>();
    preference_queue_ = std::queue<Cliente>();
}

void Sistema::adicionar(Cliente cliente) {
    if (cliente.isPreference()) {
        preference_queue_.push(cliente);
    }
    else {
        queue_.push(cliente);
    }
}

Cliente Sistema::proximo() {
    if (!preference_queue_.empty()) {
        const Cliente proximo = preference_queue_.front();
        preference_queue_.pop();
        return proximo; 
    }

    else {
        if (!queue_.empty()) {
            const Cliente proximo = queue_.front();
            queue_.pop();
            return proximo; 
        }
        // else throw(_exception());
    }
}
#endif