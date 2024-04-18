void swap (int *vector, int i, int j) {
    int ref = vector[i];
    vector[i] = vector[j];
    vector[j] = ref;
}

void copy(int *vector, int *v, int size) {
    for (int i = 0; i < size; i++) {
            v[i] = vector[i];
    }
}