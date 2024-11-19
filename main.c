#include "funciones/leerFile.c"
#include "funciones/sumarCol.c"
#include "include/leerFile.h"
#include <stdio.h>
int main(int argc, char* argv[]) {
   if (argc != 2) {
      printf("Uso: %s <nombre del archivo>\n", argv[0]);
      return 1;
   }

   int filas = 0, columnas = 0;


   int** matriz = matrizFile(argv[1]);
      contarFilasColumnas(argv[1], &filas, &columnas);
      printf("fila: %d, col: %d\n", filas, columnas);
      imprimirMatriz(matriz, filas, columnas);

      int r[columnas];
       sumarColumnas1(matriz, filas,columnas, r); 
       for (int i = 0; i < columnas; i++) {
	  printf("%d: %d ", i, r[i]);
       }
       printf("\n");

      // Liberar memoria
      for (int i = 0; i < filas; i++) {
	 free(matriz[i]);
      }
      free(matriz);

      return 0;
}


