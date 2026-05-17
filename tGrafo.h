#ifndef UNTITLED7_TGRAFO_H
#define UNTITLED7_TGRAFO_H
#include "tVuelo.h"
#include "tCiudad.h"
#include "tPila.h"

typedef struct NodoAdy {
    tVuelo vuelo;
    struct NodoAdy* sig;
} NodoAdy;

typedef NodoAdy* ListaAdy;

typedef struct NodoL {
    tCiudad ciudad;
    int visitado;
    NodoAdy* ady;
    struct NodoL* sig;
} NodoL;

typedef NodoL* tGrafo;


void resetearVisitados(tGrafo g);

NodoL* buscarNodo(tGrafo g, tCiudad c);


void crearGrafoVacio(tGrafo *g);

void cargarVuelos(tGrafo *g, char* fichero);

void insertarVuelo(tGrafo *g, tCiudad origen, tVuelo v);

void destinosDesdeCiudad(tGrafo g, tCiudad origen);

void dfsConexo(tGrafo g, tCiudad c);
int esConexo(tGrafo g);

int hayVueloDirecto(tGrafo g, tCiudad origen, tCiudad destino);

void mostrarTodasLasRutas(tGrafo g, tCiudad origen, tCiudad destino);

void ciudadesFuenteSumidero(tGrafo g);


void dfsRutas(tGrafo g, tCiudad actual, tCiudad destino, tPila *camino);

void dfsPrecio(tGrafo g, tCiudad actual, tCiudad destino, tPila* camino, float precioActual);

void trayectoMasCaroYBarato(tGrafo g, tCiudad origen, tCiudad destino);

void dfsTiempo(tGrafo g, tCiudad actual, tCiudad destino, tPila *camino, int tiempoActual);

void trayectoMasRapidoYLento(tGrafo g, tCiudad origen, tCiudad destino);

#endif //UNTITLED7_TGRAFO_H
