#ifndef UNTITLED7_TGRAFO_H
#define UNTITLED7_TGRAFO_H
#include "tVuelo.h"
#include "tCiudad.h"

typedef struct NodoAdy {
    tVuelo vuelo;
    struct NodoAdy* sig;
} NodoAdy;

typedef NodoAdy* ListaAdy;

typedef struct NodoL {
    tCiudad ciudad;
    NodoAdy* ady;
    struct NodoL* sig;
} NodoL;

typedef NodoL* tGrafo;


void cargarVuelos(tGrafo *g, char* fichero);

void insertarVuelo(tGrafo *g, tCiudad origen, tVuelo v);

void destinosDesdeCiudad(tGrafo g, tCiudad origen);

void dfsConexo(tGrafo g, tCiudad c, int visitado[]);
int esConexo(tGrafo g);

int hayVueloDirecto(tGrafo g, tCiudad origen, tCiudad destino);

void mostrarTodasLasRutas(tGrafo g, tCiudad origen, tCiudad destino);


#endif //UNTITLED7_TGRAFO_H