#include "Cliente.h"

Cliente::Cliente(int id, bool preference) {
    id_ = id;
    preference_ = preference;
}

bool Cliente::isPreference() {
    return preference_; 
}

int Cliente::getId() {
    return id_;
}

