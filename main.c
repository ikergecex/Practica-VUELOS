#include <stdio.h>
#define NUM_CIUDADES 8
#include "tGrafo.h"

int main(void) {
    char fichero[20] = "Vuelos.txt";
    tGrafo g = NULL;
    crearGrafoVacio(&g);
    cargarVuelos(&g, fichero);

    destinosDesdeCiudad(g, ciudadDesdeNombre("Madrid"));
    destinosDesdeCiudad(g, ciudadDesdeNombre("Roma"));
    destinosDesdeCiudad(g, ciudadDesdeNombre("Amsterdam"));

    if (esConexo(g))
        printf("\nEl grafo SI es conexo\n");
    else
        printf("\nEl grafo NO es conexo\n");

    if (hayVueloDirecto(g, ciudadDesdeNombre("Madrid"), ciudadDesdeNombre("Atenas"))) {
        printf("\nSI hay vuelo directo\n");
    }
    else printf("\nNO hay vuelo directo\n");

    printf("\nRutas desde Madrid hasta Amsterdam:\n"); //Esto lo escribo yo segun q ciudades quiera buscar
    mostrarTodasLasRutas(g, ciudadDesdeNombre("Madrid"), ciudadDesdeNombre("Amsterdam"));

    trayectoMasCaroYBarato(g, ciudadDesdeNombre("Madrid"), ciudadDesdeNombre("Amsterdam"));
    trayectoMasRapidoYLento(g, ciudadDesdeNombre("Madrid"), ciudadDesdeNombre("Amsterdam"));


    return 0;
}
