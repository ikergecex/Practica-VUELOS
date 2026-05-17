#include "tGrafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tPila.h"

float precioMin, precioMax;
tPila trayectoMin, trayectoMax;

int tiempoMin, tiempoMax;
tPila trayectoRapido, trayectoLento;


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


void crearGrafoVacio(tGrafo *g) {
    *g = NULL;
    for (int i = 0; i < NUM_CIUDADES; i++) {
        NodoL *nuevo = malloc(sizeof(NodoL));
        nuevo->ciudad = i;
        nuevo->visitado = 0;
        nuevo->ady = NULL;
        nuevo->sig = *g;
        *g = nuevo;
    }
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
    NodoL *actual = buscarNodo(*g, origen);
    if (actual == NULL) {
        actual = (NodoL *) malloc(sizeof(NodoL));
        actual->ciudad = origen;
        actual->visitado = 0;
        actual->ady = NULL;
        actual->sig = *g;
        *g = actual;
    }
    NodoAdy* nuevoAdy = (NodoAdy*)malloc(sizeof(NodoAdy));
    nuevoAdy->vuelo = v;
    nuevoAdy->sig = actual->ady;
    actual->ady = nuevoAdy;
}


void destinosDesdeCiudad(tGrafo g, tCiudad origen) {
    NodoL* actual = buscarNodo(g, origen);
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
    tGrafo actual = buscarNodo(g, origen);
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

                NodoL* nSig = buscarNodo(g, sigCiudad);
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

void ciudadesFuenteSumidero(tGrafo g) {
    int entrada[NUM_CIUDADES] = {0};
    int salida[NUM_CIUDADES] = {0};
    NodoL *v = g;
    while (v != NULL) {
        NodoAdy *a = v->ady;
        while (a != NULL) {
            tCiudad origen = v->ciudad;
            tCiudad destino = vueloDestino(a->vuelo);
            salida[origen]++;
            entrada[destino]++;
            a = a->sig;
        }
        v = v->sig;
    }
    for (int i = 0; i < NUM_CIUDADES; i++) {
        if (entrada[i] == 0 && salida[i] > 0) {
            imprimirCiudad(i);
            printf(" es ciudad FUENTE\n");
        }
        if (entrada[i] > 0 && salida[i] == 0) {
            imprimirCiudad(i);
            printf(" es ciudad SUMIDERO\n");
        }
    }
}


int maxCompanias = 0;
tPila mejorTrayecto = NULL;


int contarCompanias(tGrafo g, tPila camino) {
    int usadas[100] = {0};   // marcas
    char companias[100][50];
    int num = 0;

    tPila p = camino;
    while (p != NULL && p->ant != NULL) {
        tCiudad origen = p->ant->ciudad;
        tCiudad destino = p->ciudad;

        NodoL *n = buscarNodo(g, origen);
        NodoAdy *a = n->ady;

        while (a != NULL) {
            if (vueloDestino(a->vuelo) == destino) {
                int encontrada = 0;
                for (int i = 0; i < num; i++) {
                    if (strcmp(companias[i], a->vuelo.compania) == 0) {
                        encontrada = 1;
                        break;
                    }
                }
                if (!encontrada) {
                    strcpy(companias[num], a->vuelo.compania);
                    num++;
                }
                break;
            }
            a = a->sig;
        }
        p = p->ant;
    }
    return num;
}










void dfsPrecio(tGrafo g, tCiudad actual, tCiudad destino, tPila *camino, float precioActual) {
    NodoL *nAct = buscarNodo(g, actual);
    if (nAct == NULL) return;
    nAct->visitado = 1;
    Push(camino, actual);

    if (compararCiudad(actual, destino)) {
        if (precioActual < precioMin) {
            precioMin = precioActual;
            DestruirPila(&trayectoMin);
            trayectoMin = copiarPila(*camino);
        }
        if (precioActual > precioMax) {
            precioMax = precioActual;
            DestruirPila(&trayectoMax);
            trayectoMax = copiarPila(*camino);
        }
    } else {
        NodoAdy *a = nAct->ady;
        int usados[NUM_CIUDADES] = {0};
        while (a != NULL) {
            tCiudad sig = vueloDestino(a->vuelo);
            if (!usados[sig]) {
                usados[sig] = 1;
                NodoL *nSig = buscarNodo(g, sig);
                if (nSig != NULL && !nSig->visitado) {
                    dfsPrecio(g, sig, destino, camino, precioActual + vueloPrecio(a->vuelo));
                }
            }
            a = a->sig;
        }
    }
    Pop(camino);
    nAct->visitado = 0;
}





void trayectoMasCaroYBarato(tGrafo g, tCiudad origen, tCiudad destino) {
    tPila camino;
    CrearPilaVacia(&camino);

    precioMin = 1e9;
    precioMax = 0;
    trayectoMin = NULL;
    trayectoMax = NULL;

    resetearVisitados(g);
    dfsPrecio(g, origen, destino, &camino, 0);

    printf("\nTrayecto MAS BARATO (%.2f):\n", precioMin);
    imprimirPila(trayectoMin);
    printf("\n");

    printf("\nTrayecto MAS CARO (%.2f):\n", precioMax);
    imprimirPila(trayectoMax);
    printf("\n");

    DestruirPila(&camino);
    DestruirPila(&trayectoMin);
    DestruirPila(&trayectoMax);
}


void dfsTiempo(tGrafo g, tCiudad actual, tCiudad destino, tPila *camino, int tiempoActual) {

    NodoL *nAct = buscarNodo(g, actual);
    if (nAct == NULL) return;

    nAct->visitado = 1;
    Push(camino, actual);

    if (compararCiudad(actual, destino)) {

        if (tiempoActual < tiempoMin) {
            tiempoMin = tiempoActual;
            DestruirPila(&trayectoRapido);
            trayectoRapido = copiarPila(*camino);
        }

        if (tiempoActual > tiempoMax) {
            tiempoMax = tiempoActual;
            DestruirPila(&trayectoLento);
            trayectoLento = copiarPila(*camino);
        }

    } else {
        NodoAdy *a = nAct->ady;
        int usados[NUM_CIUDADES] = {0};

        while (a != NULL) {
            tCiudad sig = vueloDestino(a->vuelo);
            if (!usados[sig]) {
                usados[sig] = 1;
                NodoL *nSig = buscarNodo(g, sig);
                if (nSig != NULL && !nSig->visitado) {
                    dfsTiempo(g, sig, destino,
                              camino, tiempoActual + vueloTiempo(a->vuelo));
                }
            }
            a = a->sig;
        }
    }

    Pop(camino);
    nAct->visitado = 0;
}

void trayectoMasRapidoYLento(tGrafo g, tCiudad origen, tCiudad destino) {
    tPila camino;
    CrearPilaVacia(&camino);

    tiempoMin = 1000000;
    tiempoMax = 0;
    trayectoRapido = NULL;
    trayectoLento = NULL;

    resetearVisitados(g);
    dfsTiempo(g, origen, destino, &camino, 0);

    printf("\nTrayecto MAS RAPIDO (%d min):\n", tiempoMin);
    imprimirPila(trayectoRapido);
    printf("\n");

    printf("\nTrayecto MAS LENTO (%d min):\n", tiempoMax);
    imprimirPila(trayectoLento);
    printf("\n");

    DestruirPila(&camino);
    DestruirPila(&trayectoRapido);
    DestruirPila(&trayectoLento);
}
