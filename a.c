#include <stdio.h>
#include <stdlib.h>

// Función para contar filas y columnas automáticamente
void contarFilasColumnas(const char* nombreArchivo, int* filas, int* columnas) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo: %s\n", nombreArchivo);
        exit(1);
    }

    *filas = *columnas = 0;
    int columnasTemp = 0;
    char c;

    while ((c = fgetc(archivo)) != EOF) {
        if (c == ' ') {
            columnasTemp++;
        } else if (c == '\n') {
            (*filas)++;
            if (*filas == 1) {
                *columnas = columnasTemp + 1; // Primer fila determina columnas
            }
            columnasTemp = 0;
        }
    }

    if (columnasTemp > 0) { // Para la última fila si no termina en '\n'
        (*filas)++;
        if (*filas == 1) {
            *columnas = columnasTemp + 1;
        }
    }

    fclose(archivo);
}

// Función para leer la matriz desde el archivo
int** leerMatriz(const char* nombreArchivo, int filas, int columnas) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo: %s\n", nombreArchivo);
        exit(1);
    }

    // Asignar memoria para la matriz
    int** matriz = (int**)malloc(filas * sizeof(int*));
    for (int i = 0; i < filas; i++) {
        matriz[i] = (int*)malloc(columnas * sizeof(int));
    }

    // Leer la matriz desde el archivo
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            fscanf(archivo, "%d", &matriz[i][j]);
        }
    }

    fclose(archivo);
    return matriz;
}

// Mostrar la matriz en pantalla
void imprimirMatriz(int** matriz, int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int** matrizFile(const char* nombreArchivo){
    int filas = 0, columnas = 0;

    contarFilasColumnas(nombreArchivo, &filas, &columnas);
    return leerMatriz(nombreArchivo, filas, columnas);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Uso: %s <nombre del archivo>\n", argv[0]);
        return 1;
    }

    int filas = 0, columnas = 0;


    int** matriz = matrizFile(argv[1]);
    contarFilasColumnas(argv[1], &filas, &columnas);
    imprimirMatriz(matriz, filas, columnas);

    // Liberar memoria
    for (int i = 0; i < filas; i++) {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}

