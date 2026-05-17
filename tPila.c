#include "tPila.h"
#include <stdio.h>
#include <stdlib.h>

void CrearPilaVacia(tPila *pila) {
    *pila = NULL;
}

void Push(tPila *pila, tCiudad c) {
    NodoP* nuevo = (NodoP*) malloc(sizeof(NodoP));
    nuevo->ciudad = c;
    nuevo->ant = *pila;
    *pila = nuevo;
}

tCiudad PopYRetorno(tPila *pila) {
    if (!esVacia(*pila)) {
        NodoP* aux = *pila;
        tCiudad ciud = aux->ciudad;
        *pila = aux->ant;
        free(aux);
        return ciud;
    }
    return 0;
}

void Pop(tPila *pila) {
    if (!esVacia(*pila)) {
        NodoP* aux = *pila;
        *pila = aux->ant;
        free(aux);
    }
}

void Cima(tPila pila, tCiudad* c) {
    if (!esVacia(pila)) {
        *c = pila->ciudad;
    }
}

void DestruirPila(tPila *pila) {
    while (!esVacia(*pila)) {
        Pop(pila);
    }
}

int esVacia(tPila pila) {
    return pila == NULL;
}

void imprimirPila(tPila pila) {
    if (!esVacia(pila)) {
        imprimirPila(pila->ant);
        if (pila->ant != NULL) printf(" -> ");
        imprimirCiudad(pila->ciudad);
    }
}

tPila copiarPila(tPila p) {
    if (p == NULL) return NULL;
    tPila copiaAnt = copiarPila(p->ant);
    tPila nuevo = (NodoP*) malloc(sizeof(NodoP));
    nuevo->ciudad = p->ciudad;
    nuevo->ant = copiaAnt;
    return nuevo;
}
