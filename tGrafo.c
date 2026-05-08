#include "tGrafo.h"
#include <stdio.h>
#include <stdlib.h>
#include "tPila.h"

void resetearVisitados(tGrafo g) {
    NodoL *aux = g;
    while (aux != NULL) {
        aux->visitado = 0;
        aux = aux->sig;
    }
}

NodoL* buscarNodo(tGrafo g, tCiudad c) {
    while (g != NULL && !compararCiudad(g->ciudad, c)) {
        g = g->sig;
    }
    return g;
}


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
        tCiudad destino = vueloDestino(ady->vuelo);  // *
        if (!impreso[destino]) {
            imprimirCiudad(destino);
            printf("\n");
            impreso[destino] = 1;
        }
        ady = ady->sig;
    }
}


void dfsConexo(tGrafo g, tCiudad c) {
    NodoL* nodo = buscarNodo(g, c);
    if (nodo == NULL) return;
    nodo->visitado = 1;

    NodoAdy *a = nodo->ady;
    while (a != NULL) {
        NodoL* dest = buscarNodo(g, vueloDestino(a->vuelo));
        if (dest != NULL && !dest->visitado) {
            dfsConexo(g, vueloDestino(a->vuelo));
        }
        a = a->sig;
    }
}

int esConexo(tGrafo g) {
    if (g == NULL) return 1;
    resetearVisitados(g);
    dfsConexo(g, g->ciudad);
    NodoL* aux = g;
    while (aux != NULL) {
        if (!aux->visitado) {
            return 0;
        }
        aux = aux->sig;
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
    while (ady != NULL && !compararCiudad(vueloDestino(ady->vuelo), destino)) {
        ady = ady->sig;
    }
    if (ady == NULL) return 0;
    return 1;
}


void dfsRutas(tGrafo g, tCiudad actual, tCiudad destino, tPila *camino) {
    NodoL* nAct = buscarNodo(g, actual);
    if (nAct == NULL) return;
    nAct->visitado = 1;
    Push(camino, actual);

    if (compararCiudad(actual, destino)) {
        imprimirPila(*camino);
        printf("\n");
    } else {
        NodoAdy *a = nAct->ady;
        int usados[NUM_CIUDADES] = {0};
        while (a != NULL) {
            tCiudad sigCiudad = vueloDestino(a->vuelo);
            if (!usados[sigCiudad]) {
                usados[sigCiudad] = 1;

                NodoL *nSig = buscarNodo(g, sigCiudad);
                if (nSig != NULL && !nSig->visitado) {
                    dfsRutas(g, sigCiudad, destino, camino);
                }
            }
            a = a->sig;
        }
    }
    Pop(camino);
    nAct->visitado = 0;
}

void mostrarTodasLasRutas(tGrafo g, tCiudad origen, tCiudad destino) {
    tPila camino;
    CrearPilaVacia(&camino);
    resetearVisitados(g);
    dfsRutas(g, origen, destino, &camino);
    DestruirPila(&camino);
}
