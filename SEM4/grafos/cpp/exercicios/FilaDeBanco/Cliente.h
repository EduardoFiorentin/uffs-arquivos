#ifndef CLIENTE
#define CLIENTE

class Cliente {

public: 
    Cliente(int id, bool preference);
    bool isPreference(); 
    int getId();

private: 
    int id_; 
    bool preference_; 
};

#endif