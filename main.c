#include <stdio.h> #include <string.h> #include "funciones.h"

int main() { 
    struct DatosLibroAnidado coleccion[MAX_LIBROS]; 
    struct Venta ventas[MAX_VENTAS];
    struct Comprador compradores[MAX_COMPRADORES];
    int totalLibros = 0, totalVentas = 0, totalCompradores = 0; 
    int opcion;

inicializarLibros(coleccion, &totalLibros);

do {
    menu();
    printf("Selecciona una opcion: ");
    char entrada[10];
    fgets(entrada, sizeof(entrada), stdin);

    opcion = -1;
    int valido = 1;
    for (int i = 0; entrada[i] != '\0' && entrada[i] != '\n'; i++) {
        if (entrada[i] < '0' || entrada[i] > '9') {
            valido = 0;
            break;
        }
    }
    if (valido) {
        opcion = 0;
        for (int i = 0; entrada[i] >= '0' && entrada[i] <= '9'; i++) {
            opcion = opcion * 10 + (entrada[i] - '0');
        }
    }

    switch (opcion) {
        case 1:
            listaLibros(coleccion, totalLibros);
            break;
        case 2:
            venderLibro(coleccion, &totalLibros, ventas, &totalVentas, compradores, &totalCompradores);
            break;
        case 3:
            imprimirCompradores(compradores, totalCompradores);
            break;
        case 4:
            imprimirVentas(ventas, totalVentas);
            break;
        case 5:
            printf("Gracias por usar el sistema de biblioteca. Hasta luego!\n");
            break;
        default:
            printf("Opcion invalida. Por favor selecciona una opcion del menu.\n");
            break;
    }

} while (opcion != 5);

return 0;

}

