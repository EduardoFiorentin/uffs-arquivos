#include <queue>
#include "Cliente.h"

class Sistema {

public:
    Sistema(); 
    void adicionar(Cliente cliente); 
    Cliente proximo(); 

private:
    std::queue<Cliente> queue_; 
    std::queue<Cliente> preference_queue_; 
};