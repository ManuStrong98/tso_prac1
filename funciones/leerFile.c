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
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

int** leerMatriz(const char* nombreArchivo, int filas, int columnas) {
    // Abrir el archivo
    int fd = open(nombreArchivo, O_RDONLY);
    if (fd == -1) {
        perror("Error al abrir el archivo");
        exit(1);
    }

    // Asignar memoria para la matriz
    int** matriz = (int**)malloc(filas * sizeof(int*));
    if (matriz == NULL) {
        perror("Error al asignar memoria para la matriz");
        close(fd);
        exit(1);
    }

    int i;
    for (i = 0; i < filas; i++) {
        matriz[i] = (int*)malloc(columnas * sizeof(int));
        if (matriz[i] == NULL) {
            perror("Error al asignar memoria para una fila de la matriz");
            // Liberar la memoria asignada previamente
            while (i > 0) {
                free(matriz[i-1]);
                i--;
            }
            free(matriz);
            close(fd);
            exit(1);
        }
    }

    // Leer la matriz desde el archivo
    char buffer[10];
    ssize_t bytesLeidos;
    int iFila = 0, iCol = 0, numBytes = 0;
    
    while ((bytesLeidos = read(fd, buffer, sizeof(buffer)-1)) > 0) {
        int k;
        for (k = 0; k < bytesLeidos; k++) {
            if (isdigit(buffer[k])) {
                numBytes = 0;
                while (k < bytesLeidos && isdigit(buffer[k])) {
                    numBytes = numBytes * 10 + (buffer[k] - '0');
                    k++;
                }
                matriz[iFila][iCol] = numBytes;
                iCol++;
                if (iCol == columnas) {
                    iCol = 0;
                    iFila++;
                }
            } else if (buffer[k] == '\n') {
                // Si se encuentra un salto de línea, resetear la columna
                iCol = 0;
                iFila++;
            }
        }
    }

    // Verificar que se hayan leído todas las filas y columnas
    if (iFila != filas) {
        fprintf(stderr, "Error: El archivo no contiene el número esperado de filas.\n");
        for (i = 0; i < filas; i++) {
            free(matriz[i]);
        }
        free(matriz);
        close(fd);
        exit(1);
    }

    // Cerrar el archivo
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


