#include "tCiudad.h"
#include <stdio.h>
#include <string.h>

char *ciudades[NUM_CIUDADES] = {"Madrid", "Londres", "Roma", "Atenas", "Berlin", "Amsterdam", "Paris", "Dublin"};

tCiudad ciudadDesdeNombre(char* nombre) {
    int i;
    for (i = 0; i < NUM_CIUDADES; i++) {
        if (strcmp(ciudades[i], nombre) == 0) {
            return i;
        }
    }
    return -1;
}

void imprimirCiudad(tCiudad c) {
    if (c >= 0 && c < NUM_CIUDADES) {
        printf("%s", ciudades[c]);
    } else {
        printf("Ciudad no aplicable");
    }
}

int compararCiudad(tCiudad a, tCiudad b) {
    return a == b;
}
