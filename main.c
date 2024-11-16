#include "funciones/leerFile.c"
/* #include "funciones/sumarCol.c" */
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


