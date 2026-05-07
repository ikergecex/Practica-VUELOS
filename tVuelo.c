#include "tVuelo.h"
#include <stdio.h>
#include <string.h>

void crearVuelo(tVuelo *v, tCiudad destino, char* compania, int tiempo, float precio) {
    v->destino = destino;
    strcpy(v->compania, compania);
    v->tiempo = tiempo;
    v->precio = precio;
}

void imprimirVuelo(tVuelo v) {
    printf("Ciudad: ");
    imprimirCiudad(v.destino);
    printf("\nCompania: %s\n", v.compania);
    printf("\nTiempo: %d\n", v.tiempo);
    printf("\nPrecio: %.2f\n", v.precio);
}

int compararPrecio(tVuelo a, tVuelo b) {
    if (a.precio < b.precio) return -1;
    if (a.precio > b.precio) return 1;
    return 0;
}

int compararTiempo(tVuelo a, tVuelo b) {
    return (a.tiempo - b.tiempo);
}
