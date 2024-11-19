#include <stdlib.h>
#include "../include/sumarCol.h"
#include "../include/leerFile.h"

void sumarColumnas1(int** matriz, int filas, int columnas, int* resultado) {
    // Inicializar el arreglo de resultados a 0
    for (int j = 0; j < columnas; j++) {
        resultado[j] = 0;
    }

    // Sumar los valores de cada columna
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            resultado[j] += matriz[i][j];
        }
    }
}

/* int main() { */
/*     int filas = 3, columnas = 3; */
/*     int matriz[3][3] = { */
/*         {1, 2, 3}, */
/*         {4, 5, 6}, */
/*         {7, 8, 9} */
/*     }; */

/*     // Convertir la matriz 2D a una matriz de punteros */
/*     int* matrizPtr[3]; */
/*     for (int i = 0; i < filas; i++) { */
/*         matrizPtr[i] = matriz[i]; */
/*     } */

/*     // Llamar a la función para obtener la suma de las columnas */
/*     int* resultado = sumarColumnas(matrizPtr, filas, columnas); */

/*     // Imprimir el resultado */
/*     printf("Suma de las columnas:\n"); */
/*     for (int j = 0; j < columnas; j++) { */
/*         printf("Columna %d: %d\n", j + 1, resultado[j]); */
/*     } */

/*     // Liberar la memoria asignada */
/*     free(resultado); */

/*     return 0; */
/* } */
