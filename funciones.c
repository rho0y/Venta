#include "funciones.h"
#include <stdio.h>
#include <string.h>

void inicializarLibros(struct DatosLibroAnidado coleccion[], int *totalLibros) {
    strcpy(coleccion[0].ID, "B001");
    strcpy(coleccion[0].titulo, "Mobby Dick");
    coleccion[0].estado.stock = 10;
    coleccion[0].estado.precio = 15;

    strcpy(coleccion[1].ID, "B002");
    strcpy(coleccion[1].titulo, "La Biblia");
    coleccion[1].estado.stock = 10;
    coleccion[1].estado.precio = 35;

    strcpy(coleccion[2].ID, "B003");
    strcpy(coleccion[2].titulo, "Don Quijote de la Mancha");
    coleccion[2].estado.stock = 10;
    coleccion[2].estado.precio = 25;

    strcpy(coleccion[3].ID, "B004");
    strcpy(coleccion[3].titulo, "Traces in the Dark");
    coleccion[3].estado.stock = 10;
    coleccion[3].estado.precio = 20;

    strcpy(coleccion[4].ID, "B005");
    strcpy(coleccion[4].titulo, "Ciencias de la Logica");
    coleccion[4].estado.stock = 10;
    coleccion[4].estado.precio = 40;

    *totalLibros = 5;
}

void mostrarLibros(struct DatosLibroAnidado coleccion[], int totalLibros) {
    printf("\n%-10s %-30s %-10s %-10s\n", "ID", "Titulo", "Stock", "Precio");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < totalLibros; i++) {
        printf("%-10s %-30s %-10d $%-9d\n",
               coleccion[i].ID,
               coleccion[i].titulo,
               coleccion[i].estado.stock,
               coleccion[i].estado.precio);
    }
}

int esCedulaValida(const char *cedula) {
    int len = strlen(cedula);
    if (len < 5 || len > 15) return 0;
    for (int i = 0; i < len; i++) {
        if (cedula[i] < '0' || cedula[i] > '9') return 0;
    }
    return 1;
}

int esNombreValido(const char *nombre) {
    int len = strlen(nombre);
    if (len < 2 || len > 50) return 0;
    for (int i = 0; i < len; i++) {
        if (!((nombre[i] >= 'A' && nombre[i] <= 'Z') || 
              (nombre[i] >= 'a' && nombre[i] <= 'z') || 
              nombre[i] == ' ')) return 0;
    }
    return 1;
}

int buscarComprador(struct Comprador compradores[], int totalCompradores, const char *cedula) {
    for (int i = 0; i < totalCompradores; i++) {
        if (strcmp(compradores[i].cedula, cedula) == 0)
            return i;
    }
    return -1;
}

void registrarVenta(struct DatosLibroAnidado coleccion[], int totalLibros,
                    struct Venta ventas[], int *totalVentas,
                    struct Comprador compradores[], int *totalCompradores) {

    if (*totalVentas >= MAX_VENTAS) {
        printf("Limite de ventas alcanzado.\n");
        return;
    }

    char cedula[20], nombre[50];
    printf("Ingrese la cedula del comprador: ");
    fgets(cedula, sizeof(cedula), stdin);
    cedula[strcspn(cedula, "\n")] = 0;

    if (!esCedulaValida(cedula)) {
        printf("Cedula invalida.\n");
        return;
    }

    printf("Ingrese el nombre del comprador: ");
    fgets(nombre, sizeof(nombre), stdin);
    nombre[strcspn(nombre, "\n")] = 0;

    if (!esNombreValido(nombre)) {
        printf("Nombre invalido.\n");
        return;
    }

    mostrarLibros(coleccion, totalLibros);
    printf("Seleccione el numero del libro (1-%d): ", totalLibros);
    char opcion[10];
    fgets(opcion, sizeof(opcion), stdin);
    int indice = opcion[0] - '1';

    if (indice < 0 || indice >= totalLibros) {
        printf("Opcion invalida.\n");
        return;
    }

    if (coleccion[indice].estado.stock <= 0) {
        printf("No hay stock disponible para ese libro.\n");
        return;
    }

    coleccion[indice].estado.stock--;

    struct Venta nuevaVenta;
    strcpy(nuevaVenta.cedula, cedula);
    strcpy(nuevaVenta.nombre, nombre);
    strcpy(nuevaVenta.libroComprado, coleccion[indice].titulo);
    nuevaVenta.precio = coleccion[indice].estado.precio;
    ventas[*totalVentas] = nuevaVenta;
    (*totalVentas)++;

    if (buscarComprador(compradores, *totalCompradores, cedula) == -1) {
        strcpy(compradores[*totalCompradores].cedula, cedula);
        strcpy(compradores[*totalCompradores].nombre, nombre);
        (*totalCompradores)++;
    }

    printf("Venta registrada con exito.\n");
}

void mostrarVentas(struct Venta ventas[], int totalVentas) {
    printf("\n%-15s %-25s %-30s %-10s\n", "Cedula", "Nombre", "Libro", "Precio");
    printf("--------------------------------------------------------------------------\n");
    for (int i = 0; i < totalVentas; i++) {
        printf("%-15s %-25s %-30s $%-9d\n",
               ventas[i].cedula,
               ventas[i].nombre,
               ventas[i].libroComprado,
               ventas[i].precio);
    }
}

void mostrarCompradores(struct Comprador compradores[], int totalCompradores) {
    printf("\n%-15s %-30s\n", "Cedula", "Nombre");
    printf("-------------------------------------------\n");
    for (int i = 0; i < totalCompradores; i++) {
        printf("%-15s %-30s\n",
               compradores[i].cedula,
               compradores[i].nombre);
    }
}
