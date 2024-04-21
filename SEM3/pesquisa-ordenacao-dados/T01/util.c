void swap (Tlist *vector, int i, int j) {
    // printf("antes: i: %d / j: %d", vector[i].value, vector[j].value);
    Tlist ref = vector[i];
    vector[i] = vector[j];
    vector[j] = ref;
    // printf("depois: i: %d / j: %d", vector[i].value, vector[j].value);
}

void intSwap (int *vector, int i, int j) {
    int ref = vector[i];
    vector[i] = vector[j];
    vector[j] = ref;
}

void copy(Tlist *vector, Tlist *v, int size) {
    for (int i = 0; i < size; i++) {
            v[i] = vector[i];
    }
}