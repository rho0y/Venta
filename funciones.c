#include <stdio.h>
#include <string.h>
#include "funciones.h"

int validarCadenaVacia(const char *cadena) {
    return cadena == NULL || strlen(cadena) == 0;
}

int esNumeroValido(const char *entrada) {
    if (entrada[0] == '\0') return 0;
    for (int i = 0; entrada[i] != '\0'; i++) {
        if (entrada[i] < '0' || entrada[i] > '9') {
            return 0;
        }
    }
    return 1;
}

int leerEnteroSeguro() {
    char buffer[20];
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (!esNumeroValido(buffer)) {
        return -1;
    }
    int numero = 0;
    for (int i = 0; buffer[i] != '\0'; i++) {
        numero = numero * 10 + (buffer[i] - '0');
    }
    return numero;
}

int cedulaExiste(struct Comprador compradores[], int totalCompradores, const char *cedula) {
    for (int i = 0; i < totalCompradores; i++) {
        if (strcmp(compradores[i].cedula, cedula) == 0) {
            return 1;
        }
    }
    return 0;
}

void inicializarLibros(struct DatosLibroAnidado coleccion[], int *totalLibros) {
    // Predefinir 5 libros con stock 10
    strcpy(coleccion[0].ID, "B001");
    strcpy(coleccion[0].titulo, "Mobby Dick");
    coleccion[0].estado.stock = 10;

    strcpy(coleccion[1].ID, "B002");
    strcpy(coleccion[1].titulo, "La Biblia");
    coleccion[1].estado.stock = 10;

    strcpy(coleccion[2].ID, "B003");
    strcpy(coleccion[2].titulo, "Don Quijote de la Mancha");
    coleccion[2].estado.stock = 10;

    strcpy(coleccion[3].ID, "B004");
    strcpy(coleccion[3].titulo, "Traces in the Dark");
    coleccion[3].estado.stock = 10;

    strcpy(coleccion[4].ID, "B005");
    strcpy(coleccion[4].titulo, "Ciencias de la Logica");
    coleccion[4].estado.stock = 10;

    *totalLibros = 5;
}

void listaLibros(struct DatosLibroAnidado coleccion[], int totalLibros) {
    printf("\n--- LIBROS DISPONIBLES ---\n");
    for (int i = 0; i < totalLibros; i++) {
        printf("%d) ID:%s  Titulo:%s  Stock:%d\n",
            i+1, coleccion[i].ID, coleccion[i].titulo, coleccion[i].estado.stock);
    }
}

void imprimirCompradores(struct Comprador compradores[], int totalCompradores) {
    printf("\n--- COMPRADORES ---\n");
    for (int i = 0; i < totalCompradores; i++) {
        printf("%d) Nombre:%s  Cedula:%s\n",
            i+1, compradores[i].nombre, compradores[i].cedula);
    }
}

void imprimirVentas(struct Venta ventas[], int totalVentas) {
    printf("\n--- VENTAS ---\n");
    for (int i = 0; i < totalVentas; i++) {
        printf("%d) Cedula:%s  IDlibro:%s  Cantidad:%d\n",
            i+1, ventas[i].cedulaComprador, ventas[i].idLibro, ventas[i].cantidad);
    }
}

void venderLibro(struct DatosLibroAnidado coleccion[], int totalLibros,
                 struct Comprador compradores[], int *totalCompradores,
                 struct Venta ventas[], int *totalVentas) {

    char nombre[50], cedula[20];
    int valido;

    // nombre
    do {
        printf("Ingrese nombre del comprador: ");
        fgets(nombre, sizeof(nombre), stdin);
        nombre[strcspn(nombre, "\n")] = '\0';
        valido = !validarCadenaVacia(nombre);
        if (!valido) printf("Nombre invalido.\n");
    } while (!valido);

    // cedula
    do {
        printf("Ingrese cedula (solo numeros): ");
        fgets(cedula, sizeof(cedula), stdin);
        cedula[strcspn(cedula, "\n")] = '\0';
        valido = esNumeroValido(cedula) && !cedulaExiste(compradores, *totalCompradores, cedula);
        if (!valido) printf("Cedula invalida o repetida.\n");
    } while (!valido);

    strcpy(compradores[*totalCompradores].nombre, nombre);
    strcpy(compradores[*totalCompradores].cedula, cedula);
    (*totalCompradores)++;

    int seguir = 1, totalVenta = 0;
    do {
        listaLibros(coleccion, totalLibros);
        printf("Que libro desea comprar? (indice): ");
        int idx = leerEnteroSeguro();
        if (idx < 1 || idx > totalLibros) {
            printf("Indice invalido.\n");
            continue;
        }

        printf("Cuantos desea comprar?: ");
        int cant = leerEnteroSeguro();
        if (cant < 1 || cant > coleccion[idx-1].estado.stock) {
            printf("Cantidad invalida o sin stock.\n");
            continue;
        }

        coleccion[idx-1].estado.stock -= cant;

        strcpy(ventas[*totalVentas].cedulaComprador, cedula);
        strcpy(ventas[*totalVentas].idLibro, coleccion[idx-1].ID);
        ventas[*totalVentas].cantidad = cant;
        (*totalVentas)++;
        totalVenta += cant;

        printf("Desea seguir comprando? si(1) no(0): ");
        int resp = leerEnteroSeguro();
        seguir = (resp == 1) ? 1 : 0;

    } while (seguir == 1);

    printf("Total de la venta:%d\n", totalVenta);
    printf("Realizar compra? si(1) no(0): ");
    int confirma = leerEnteroSeguro();
    if (confirma == 1) {
        printf("Compra realizada exitosamente.\n");
    } else {
        printf("Compra cancelada.\n");
    }
}#include <stdio.h>
#include <string.h>
#include "funciones.h"

int validarCadenaVacia(const char *cadena) {
    return cadena == NULL || strlen(cadena) == 0;
}

int esNumeroValido(const char *entrada) {
    if (entrada[0] == '\0') return 0;
    for (int i = 0; entrada[i] != '\0'; i++) {
        if (entrada[i] < '0' || entrada[i] > '9') {
            return 0;
        }
    }
    return 1;
}

int leerEnteroSeguro() {
    char buffer[20];
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (!esNumeroValido(buffer)) {
        return -1;
    }
    int numero = 0;
    for (int i = 0; buffer[i] != '\0'; i++) {
        numero = numero * 10 + (buffer[i] - '0');
    }
    return numero;
}

int cedulaExiste(struct Comprador compradores[], int totalCompradores, const char *cedula) {
    for (int i = 0; i < totalCompradores; i++) {
        if (strcmp(compradores[i].cedula, cedula) == 0) {
            return 1;
        }
    }
    return 0;
}

void inicializarLibros(struct DatosLibroAnidado coleccion[], int *totalLibros) {
    // Predefinir 5 libros con stock 10
    strcpy(coleccion[0].ID, "B001");
    strcpy(coleccion[0].titulo, "Mobby Dick");
    coleccion[0].estado.stock = 10;

    strcpy(coleccion[1].ID, "B002");
    strcpy(coleccion[1].titulo, "La Biblia");
    coleccion[1].estado.stock = 10;

    strcpy(coleccion[2].ID, "B003");
    strcpy(coleccion[2].titulo, "Don Quijote de la Mancha");
    coleccion[2].estado.stock = 10;

    strcpy(coleccion[3].ID, "B004");
    strcpy(coleccion[3].titulo, "Traces in the Dark");
    coleccion[3].estado.stock = 10;

    strcpy(coleccion[4].ID, "B005");
    strcpy(coleccion[4].titulo, "Ciencias de la Logica");
    coleccion[4].estado.stock = 10;

    *totalLibros = 5;
}

void listaLibros(struct DatosLibroAnidado coleccion[], int totalLibros) {
    printf("\n--- LIBROS DISPONIBLES ---\n");
    for (int i = 0; i < totalLibros; i++) {
        printf("%d) ID:%s  Titulo:%s  Stock:%d\n",
            i+1, coleccion[i].ID, coleccion[i].titulo, coleccion[i].estado.stock);
    }
}

void imprimirCompradores(struct Comprador compradores[], int totalCompradores) {
    printf("\n--- COMPRADORES ---\n");
    for (int i = 0; i < totalCompradores; i++) {
        printf("%d) Nombre:%s  Cedula:%s\n",
            i+1, compradores[i].nombre, compradores[i].cedula);
    }
}

void imprimirVentas(struct Venta ventas[], int totalVentas) {
    printf("\n--- VENTAS ---\n");
    for (int i = 0; i < totalVentas; i++) {
        printf("%d) Cedula:%s  IDlibro:%s  Cantidad:%d\n",
            i+1, ventas[i].cedulaComprador, ventas[i].idLibro, ventas[i].cantidad);
    }
}

void venderLibro(struct DatosLibroAnidado coleccion[], int totalLibros,
                 struct Comprador compradores[], int *totalCompradores,
                 struct Venta ventas[], int *totalVentas) {

    char nombre[50], cedula[20];
    int valido;

    // nombre
    do {
        printf("Ingrese nombre del comprador: ");
        fgets(nombre, sizeof(nombre), stdin);
        nombre[strcspn(nombre, "\n")] = '\0';
        valido = !validarCadenaVacia(nombre);
        if (!valido) printf("Nombre invalido.\n");
    } while (!valido);

    // cedula
    do {
        printf("Ingrese cedula (solo numeros): ");
        fgets(cedula, sizeof(cedula), stdin);
        cedula[strcspn(cedula, "\n")] = '\0';
        valido = esNumeroValido(cedula) && !cedulaExiste(compradores, *totalCompradores, cedula);
        if (!valido) printf("Cedula invalida o repetida.\n");
    } while (!valido);

    strcpy(compradores[*totalCompradores].nombre, nombre);
    strcpy(compradores[*totalCompradores].cedula, cedula);
    (*totalCompradores)++;

    int seguir = 1, totalVenta = 0;
    do {
        listaLibros(coleccion, totalLibros);
        printf("Que libro desea comprar? (indice): ");
        int idx = leerEnteroSeguro();
        if (idx < 1 || idx > totalLibros) {
            printf("Indice invalido.\n");
            continue;
        }

        printf("Cuantos desea comprar?: ");
        int cant = leerEnteroSeguro();
        if (cant < 1 || cant > coleccion[idx-1].estado.stock) {
            printf("Cantidad invalida o sin stock.\n");
            continue;
        }

        coleccion[idx-1].estado.stock -= cant;

        strcpy(ventas[*totalVentas].cedulaComprador, cedula);
        strcpy(ventas[*totalVentas].idLibro, coleccion[idx-1].ID);
        ventas[*totalVentas].cantidad = cant;
        (*totalVentas)++;
        totalVenta += cant;

        printf("Desea seguir comprando? si(1) no(0): ");
        int resp = leerEnteroSeguro();
        seguir = (resp == 1) ? 1 : 0;

    } while (seguir == 1);

    printf("Total de la venta:%d\n", totalVenta);
    printf("Realizar compra? si(1) no(0): ");
    int confirma = leerEnteroSeguro();
    if (confirma == 1) {
        printf("Compra realizada exitosamente.\n");
    } else {
        printf("Compra cancelada.\n");
    }
}
