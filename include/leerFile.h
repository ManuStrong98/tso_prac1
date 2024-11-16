#ifndef LEERFILE_H
#define LEERFILE_H

#include <stdio.h>
#include <stdlib.h>

// Declaración de funciones
void contarFilasColumnas(const char* nombreArchivo, int* filas, int* columnas);
int** leerMatriz(const char* nombreArchivo, int filas, int columnas);
void imprimirMatriz(int** matriz, int filas, int columnas);
int** matrizFile(const char* nombreArchivo);

#endif // LEERFILE_H
