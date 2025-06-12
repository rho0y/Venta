#include "funciones.h"

int main() {
    struct DatosLibroAnidado coleccion[MAX_LIBROS];
    struct Comprador compradores[MAX_COMPRADORES];
    struct Venta ventas[MAX_VENTAS];
    int totalLibros = 0, totalCompradores = 0, totalVentas = 0;
    int opcion;
    char buffer[10];

    inicializarLibros(coleccion, &totalLibros);

    do {
        menu();
        printf("Selecciona una opcion: ");
        fgets(buffer, sizeof(buffer), stdin);

        while (!esNumeroValido(buffer)) {
            printf("Entrada invalida. Por favor ingresa un numero: ");
            fgets(buffer, sizeof(buffer), stdin);
        }

        opcion = atoi(buffer);

        if (opcion == 1) {
            listaLibros(coleccion, totalLibros);
        } else if (opcion == 2) {
            venderLibro(coleccion, totalLibros, compradores, &totalCompradores, ventas, &totalVentas);
        } else if (opcion == 3) {
            imprimirCompradores(compradores, totalCompradores);
        } else if (opcion == 4) {
            imprimirVentas(ventas, totalVentas);
        } else if (opcion == 5) {
            printf("Gracias por usar el sistema\n");
        } else {
            printf("Opcion invalida\n");
        }

    } while (opcion != 5);

    return 0;
}
