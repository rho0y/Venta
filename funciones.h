#define MAX_LIBROS 10
#define MAX_ID 20
#define MAX_TITULOS 100
#define MAX_COMPRADORES 100
#define MAX_VENTAS 100

struct InfoAutor {
    char nombreCompleto[100];
};

struct EstadoLibro {
    int stock;
};

struct DatosLibroAnidado {
    char ID[MAX_ID];
    char titulo[MAX_TITULOS];
    char idioma[20];
    char genero[30];
    struct InfoAutor autor;
    struct EstadoLibro estado;
};

struct Comprador {
    char nombre[50];
    char cedula[20];
};

struct Venta {
    char cedulaComprador[20];
    char idLibro[MAX_ID];
    int cantidad;
};

void menu();
void inicializarLibros(struct DatosLibroAnidado coleccion[], int *totalLibros);
void listaLibros(struct DatosLibroAnidado coleccion[], int totalLibros);
void imprimirCompradores(struct Comprador compradores[], int totalCompradores);
void imprimirVentas(struct Venta ventas[], int totalVentas);
void venderLibro(struct DatosLibroAnidado coleccion[], int totalLibros,
                 struct Comprador compradores[], int *totalCompradores,
                 struct Venta ventas[], int *totalVentas);
int validarCadenaVacia(const char *cadena);
int esNumeroValido(const char *cadena);
int cedulaExiste(struct Comprador compradores[], int total, const char *cedula);
