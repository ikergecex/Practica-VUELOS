#include "tGrafo.h"
#include <stdio.h>
#include <stdlib.h>

void cargarVuelos(tGrafo *g, char* fichero) {
    FILE *f = fopen(fichero, "r");
    if (f == NULL) {
        printf("Error.\n");
        return;
    }
    char origen[100], destino[100], compania[100];
    int tiempo;
    float precio;

    while (fscanf(f, "%s", origen) == 1) {
        fscanf(f, "%s", destino);
        fscanf(f, "%s", compania);
        fscanf(f, "%d", &tiempo);
        fscanf(f, "%f", &precio);

        printf("\n");
        printf("  Origen: %s\n", origen);
        printf("  Destino: %s\n", destino);
        printf("  Compania: %s\n", compania);
        printf("  Tiempo: %d\n", tiempo);
        printf("  Precio: %.2f\n", precio);


        tCiudad c_origen  = ciudadDesdeNombre(origen);
        tCiudad c_destino = ciudadDesdeNombre(destino);

        if (c_origen != -1 && c_destino != -1) {
            tVuelo v;
            crearVuelo(&v, c_destino, compania, tiempo, precio);
            insertarVuelo(g, c_origen, v);
        }
    }
    printf("\nVuelos cargados correctamente en el grafo.\n");
    fclose(f);
}



void insertarVuelo(tGrafo *g, tCiudad origen, tVuelo v) {
    NodoL* actual = *g;

    while (actual != NULL && actual->ciudad != origen) {
        actual = actual->sig;
    }
    if (actual == NULL) {
        NodoL *nuevoVertice = (NodoL *)malloc(sizeof(NodoL));
        nuevoVertice->ciudad = origen;
        nuevoVertice->ady = NULL;
        nuevoVertice->sig = *g;
        *g = nuevoVertice;
        actual = nuevoVertice;
    }

    NodoAdy* nuevoAdy = (NodoAdy*)malloc(sizeof(NodoAdy));
    nuevoAdy->vuelo = v;
    nuevoAdy->sig = actual->ady;
    actual->ady = nuevoAdy;
}


void destinosDesdeCiudad(tGrafo g, tCiudad origen) {
    tGrafo actual = g;
    while (actual != NULL && !compararCiudad(actual->ciudad, origen)) {
        actual = actual->sig;
    }
    if (actual == NULL) {
        printf("La ciudad no esta en el grafo\n");
        return;
    }
    int impreso[NUM_CIUDADES] = {0}; //para qu no hayan destinos repetidos *
    printf("\nDesde ");
    imprimirCiudad(origen);
    printf(" se puede ir a:\n");

    NodoAdy* ady = actual->ady;
    while (ady != NULL) {
        tCiudad destino = ady->vuelo.destino;  // *
        if (!impreso[destino]) {
            imprimirCiudad(destino);
            printf("\n");
            impreso[destino] = 1;
        }
        ady = ady->sig;
    }
}


void dfsConexo(tGrafo g, tCiudad c, int visitado[]) {
    visitado[c] = 1;
    NodoL *v = g;
    while (v != NULL && v->ciudad != c) {
        v = v->sig;
    }
    if (v == NULL) return;
    NodoAdy *a = v->ady;
    while (a != NULL) {
        if (!visitado[a->vuelo.destino]) {
            dfsConexo(g, a->vuelo.destino, visitado);
        }
        a = a->sig;
    }
}

int esConexo(tGrafo g) {
    if (g == NULL) return 1;
    int visitado[NUM_CIUDADES] = {0};
    dfsConexo(g, g->ciudad, visitado);
    for (int i = 0; i < NUM_CIUDADES; i++) {
        if (!visitado[i]) {
            return 0;
        }
    }
    return 1;
}

int hayVueloDirecto(tGrafo g, tCiudad origen, tCiudad destino) {
    tGrafo actual = g;
    while (actual != NULL && !compararCiudad(actual->ciudad, origen)) {
        actual = actual->sig;
    }
    if (actual == NULL) return 0;
    NodoAdy* ady = actual->ady;
    while (ady != NULL && !compararCiudad(ady->vuelo.destino, destino)) {
        ady = ady->sig;
    }
    if (ady == NULL) return 0;
    return 1;
}

void mostrarTodasLasRutas(tGrafo g, tCiudad origen, tCiudad destino) {

}