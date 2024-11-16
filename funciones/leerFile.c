#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include "../include/leerFile.h"

void contarFilasColumnas(const char* nombreArchivo, int* filas, int* columnas) {
    int fd = open(nombreArchivo, O_RDONLY);
    if (fd == -1) {
        perror("Error al abrir el archivo");
        exit(1);
    }

    *filas = *columnas = 0;
    int columnasTemp = 0;
    char c;
    ssize_t bytesLeidos;

    while ((bytesLeidos = read(fd, &c, 1)) > 0) {
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

    close(fd);
}

// Función para leer la matriz desde el archivo
int** leerMatriz(const char* nombreArchivo, int filas, int columnas) {
    int fd = open(nombreArchivo, O_RDONLY);
    if (fd == -1) {
        perror("Error al abrir el archivo");
        exit(1);
    }

    // Asignar memoria para la matriz
    int** matriz = (int**)malloc(filas * sizeof(int*));
    for (int i = 0; i < filas; i++) {
        matriz[i] = (int*)malloc(columnas * sizeof(int));
    }

    // Leer la matriz desde el archivo
    char buffer[10];
    ssize_t bytesLeidos;
    int i = 0, j = 0, numBytes;
    
    while ((bytesLeidos = read(fd, buffer, sizeof(buffer)-1)) > 0) {
        for (int k = 0; k < bytesLeidos; k++) {
            if (isdigit(buffer[k])) {
                numBytes = 0;
                while (isdigit(buffer[k])) {
                    numBytes = numBytes * 10 + (buffer[k] - '0');
                    k++;
                }
                matriz[i][j] = numBytes;
                j++;
            } else if (buffer[k] == '\n') {
                i++;
                j = 0;
            }
        }
    }

    close(fd);
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

int** matrizFile(const char* nombreArchivo) {
    int filas = 0, columnas = 0;

    contarFilasColumnas(nombreArchivo, &filas, &columnas);
    return leerMatriz(nombreArchivo, filas, columnas);
}


