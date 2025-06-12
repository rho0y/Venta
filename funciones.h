

#define MAX_LIBROS 5
#define MAX_VENTAS 100
#define MAX_COMPRADORES 100

// Estructura para estado de libro
struct EstadoLibro {
    int stock;
    int precio;
};

// Estructura principal del libro
struct DatosLibroAnidado {
    char ID[10];
    char titulo[50];
    struct EstadoLibro estado;
};

// Estructura para registrar una venta
struct Venta {
    char cedula[20];
    char nombre[50];
    char libroComprado[50];
    int precio;
};

// Estructura para compradores (evita duplicados)
struct Comprador {
    char cedula[20];
    char nombre[50];
};

// Declaraciones
void inicializarLibros(struct DatosLibroAnidado coleccion[], int *totalLibros);
void mostrarLibros(struct DatosLibroAnidado coleccion[], int totalLibros);
int esCedulaValida(const char *cedula);
int esNombreValido(const char *nombre);
int buscarComprador(struct Comprador compradores[], int totalCompradores, const char *cedula);
void registrarVenta(struct DatosLibroAnidado coleccion[], int totalLibros,
                    struct Venta ventas[], int *totalVentas,
                    struct Comprador compradores[], int *totalCompradores);
void mostrarVentas(struct Venta ventas[], int totalVentas);
void mostrarCompradores(struct Comprador compradores[], int totalCompradores);

