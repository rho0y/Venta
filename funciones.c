#include "funciones.h"
#include <string.h>
#include <stdio.h>

void menu() {
    printf("\n--- MENU ---\n");
    printf("1. Listar libros\n");
    printf("2. Realizar venta\n");
    printf("3. Mostrar compradores\n");
    printf("4. Mostrar ventas\n");
    printf("5. Salir\n");
}

int validarCadenaVacia(const char *cadena) {
    return cadena == NULL || strlen(cadena) == 0;
}

int esNumeroValido(const char *cadena) {
    int i = 0;
    while (cadena[i]) {
        if (cadena[i] < '0' || cadena[i] > '9') {
            return 0;
        }
        i++;
    }
    return 1;
}

int cedulaExiste(struct Comprador compradores[], int total, const char *cedula) {
    for (int i = 0; i < total; i++) {
        if (strcmp(compradores[i].cedula, cedula) == 0) {
            return 1;
        }
    }
    return 0;
}

void inicializarLibros(struct DatosLibroAnidado coleccion[], int *totalLibros) {
    strcpy(coleccion[0].ID, "L001");
    strcpy(coleccion[0].titulo, "C Programming");
    strcpy(coleccion[0].idioma, "Ingles");
    strcpy(coleccion[0].genero, "Educativo");
    strcpy(coleccion[0].autor.nombreCompleto, "Dennis Ritchie");
    coleccion[0].estado.stock = 10;

    strcpy(coleccion[1].ID, "L002");
    strcpy(coleccion[1].titulo, "El Principito");
    strcpy(coleccion[1].idioma, "Español");
    strcpy(coleccion[1].genero, "Ficcion");
    strcpy(coleccion[1].autor.nombreCompleto, "Antoine de Saint-Exupery");
    coleccion[1].estado.stock = 10;

    *totalLibros = 2;
}

void listaLibros(struct DatosLibroAnidado coleccion[], int totalLibros) {
    printf("\n--- Lista de Libros ---\n");
    for (int i = 0; i < totalLibros; i++) {
        printf("%d. ID: %s | Titulo: %s | Autor: %s | Stock: %d\n", 
            i + 1,
            coleccion[i].ID,
            coleccion[i].titulo,
            coleccion[i].autor.nombreCompleto,
            coleccion[i].estado.stock);
    }
}

void imprimirCompradores(struct Comprador compradores[], int totalCompradores) {
    printf("\n--- Lista de Compradores ---\n");
    for (int i = 0; i < totalCompradores; i++) {
        printf("%d. Nombre: %s | Cedula: %s\n", i + 1, compradores[i].nombre, compradores[i].cedula);
    }
}

void imprimirVentas(struct Venta ventas[], int totalVentas) {
    printf("\n--- Lista de Ventas ---\n");
    for (int i = 0; i < totalVentas; i++) {
        printf("%d. Cedula: %s | ID Libro: %s | Cantidad: %d\n", i + 1, ventas[i].cedulaComprador, ventas[i].idLibro, ventas[i].cantidad);
    }
}

void venderLibro(struct DatosLibroAnidado coleccion[], int totalLibros,
                 struct Comprador compradores[], int *totalCompradores,
                 struct Venta ventas[], int *totalVentas) {
    char nombre[50], cedula[20], buffer[10];
    int seguir = 1, totalVenta = 0;

    printf("Ingrese nombre del comprador: ");
    fgets(nombre, sizeof(nombre), stdin);
    nombre[strcspn(nombre, "\n")] = '\0';

    while (validarCadenaVacia(nombre)) {
        printf("Nombre invalido, intente de nuevo: ");
        fgets(nombre, sizeof(nombre), stdin);
        nombre[strcspn(nombre, "\n")] = '\0';
    }

    printf("Ingrese cedula del comprador: ");
    fgets(cedula, sizeof(cedula), stdin);
    cedula[strcspn(cedula, "\n")] = '\0';

    while (!esNumeroValido(cedula) || cedulaExiste(compradores, *totalCompradores, cedula)) {
        printf("Cedula invalida o ya existe, intente de nuevo: ");
        fgets(cedula, sizeof(cedula), stdin);
        cedula[strcspn(cedula, "\n")] = '\0';
    }

    strcpy(compradores[*totalCompradores].nombre, nombre);
    strcpy(compradores[*totalCompradores].cedula, cedula);
    (*totalCompradores)++;

    while (seguir == 1) {
        listaLibros(coleccion, totalLibros);
        int indice, cantidad;

        printf("¿Que libro desea comprar (indice)?: ");
        fgets(buffer, sizeof(buffer), stdin);
        while (!esNumeroValido(buffer)) {
            printf("Entrada invalida. Ingrese un numero: ");
            fgets(buffer, sizeof(buffer), stdin);
        }
        indice = atoi(buffer);

        if (indice < 1 || indice > totalLibros) {
            printf("Indice fuera de rango\n");
            continue;
        }

        printf("¿Cuantos desea comprar?: ");
        fgets(buffer, sizeof(buffer), stdin);
        while (!esNumeroValido(buffer)) {
            printf("Entrada invalida. Ingrese un numero: ");
            fgets(buffer, sizeof(buffer), stdin);
        }
        cantidad = atoi(buffer);

        if (cantidad <= 0 || cantidad > coleccion[indice - 1].estado.stock) {
            printf("Cantidad invalida o no hay suficiente stock\n");
            continue;
        }

        coleccion[indice - 1].estado.stock -= cantidad;

        strcpy(ventas[*totalVentas].cedulaComprador, cedula);
        strcpy(ventas[*totalVentas].idLibro, coleccion[indice - 1].ID);
        ventas[*totalVentas].cantidad = cantidad;
        (*totalVentas)++;

        totalVenta += cantidad;

        printf("¿Desea seguir comprando? si (1), no (0): ");
        fgets(buffer, sizeof(buffer), stdin);
        while (!esNumeroValido(buffer)) {
            printf("Entrada invalida. Ingrese 1 o 0: ");
            fgets(buffer, sizeof(buffer), stdin);
        }
        seguir = atoi(buffer);
    }

    printf("Total de la venta: %d\n", totalVenta);
    printf("¿Desea realizar la compra? si (1), no (0): ");
    fgets(buffer, sizeof(buffer), stdin);
    while (!esNumeroValido(buffer)) {
        printf("Entrada invalida. Ingrese 1 o 0: ");
        fgets(buffer, sizeof(buffer), stdin);
    }

    if (atoi(buffer) == 1) {
        printf("Compra realizada exitosamente\n");
    } else {
        printf("Compra cancelada\n");
    }
}
