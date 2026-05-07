#include <stdio.h>
#define NUM_CIUDADES 8
#include "tGrafo.h"

int main(void) {
    char fichero[20] = "Vuelos.txt";
    tGrafo g = NULL;
    cargarVuelos(&g, fichero);

    destinosDesdeCiudad(g, ciudadDesdeNombre("Madrid"));
    destinosDesdeCiudad(g, ciudadDesdeNombre("Roma"));
    destinosDesdeCiudad(g, ciudadDesdeNombre("Amsterdam"));

    if (esConexo(g))
        printf("\nEl grafo SI es conexo\n");
    else
        printf("\nEl grafo NO es conexo\n");

    if (hayVueloDirecto(g, ciudadDesdeNombre("Madrid"), ciudadDesdeNombre("Atenas"))) {
        printf("\nSI ay vuelo directo\n");
    }
    else printf("\nNO hay vuelo directo\n");

    return 0;
}