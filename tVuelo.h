#ifndef UNTITLED7_TVUELO_H
#define UNTITLED7_TVUELO_H

#include "tCiudad.h"

typedef struct {
    tCiudad destino;
    char compania[50];
    int tiempo;
    float precio;
} tVuelo;

void crearVuelo(tVuelo *v, tCiudad destino, char* compania, int tiempo, float precio);

void imprimirVuelo(tVuelo v);

int compararPrecio(tVuelo a, tVuelo b);

int compararTiempo(tVuelo a, tVuelo b);


#endif //UNTITLED7_TVUELO_H