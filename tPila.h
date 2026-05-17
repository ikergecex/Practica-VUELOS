#ifndef UNTITLED7_TPILA_H
#define UNTITLED7_TPILA_H
#include "tCiudad.h"

typedef struct NodoP {
    tCiudad ciudad;
    struct NodoP* ant;
} NodoP;

typedef NodoP* tPila;

void CrearPilaVacia(tPila *pila);
void Push(tPila *pila, tCiudad c);
tCiudad PopYRetorno(tPila *pila);
void Pop(tPila *pila);
void Cima(tPila pila, tCiudad* c);
void DestruirPila(tPila *pila);
int esVacia(tPila pila);
void imprimirPila(tPila pila);
tPila copiarPila(tPila p);

#endif //UNTITLED7_TPILA_H
