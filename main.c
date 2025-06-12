#include <stdio.h>
#include <string.h>
#include "funciones.h"

int main() {
    struct DatosLibroAnidado coleccion[MAX_LIBROS];
    struct Venta ventas[MAX_VENTAS];
    struct Comprador compradores[MAX_COMPRADORES];

    int totalLibros = 0, totalVentas = 0, totalCompradores = 0;
    inicializarLibros(coleccion, &totalLibros);

    int opcion;
    char entrada[10];

    do {
        printf("\n---- Menu Principal ----\n");
        printf("1. Ver libros disponibles\n");
        printf("2. Registrar venta\n");
        printf("3. Ver todas las ventas\n");
        printf("4. Ver compradores\n");
        printf("5. Salir\n");
        printf("Seleccione una opcion: ");

        fgets(entrada, sizeof(entrada), stdin);
        opcion = entrada[0] - '0';

        switch (opcion) {
            case 1:
                mostrarLibros(coleccion, totalLibros);
                break;
            case 2:
                registrarVenta(coleccion, totalLibros, ventas, &totalVentas, compradores, &totalCompradores);
                break;
            case 3:
                mostrarVentas(ventas, totalVentas);
                break;
            case 4:
                mostrarCompradores(compradores, totalCompradores);
                break;
            case 5:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }

    } while (opcion != 5);

    return 0;
}
