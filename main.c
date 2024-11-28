#include "funciones/leerFile.c"
#include "funciones/sumarCol.c"
#include "include/leerFile.h"
#include "funciones/estructuraDeDato/listaEnlazadasDeListaInt.c"
#include "include/listaEnlazadasDeListaInt.h"
#include <stdio.h>
#include<stdbool.h>// Booleanos
#include <stdlib.h>

void volverTodaLaFilaEn0(int* c, int col){
    for(int i = 0; i < col; i++){
	c[i] = 0;
    }
}
bool hayAlgunNegativoEnlaLista(int* a, int* r, int col){
    bool respuesta = false;
    int n;
    for(int i = 0; i < col; i++){
	n = a[i] - r[i];
	if(n < 0){
	    respuesta = true;
	    break;
	}
    }
    return respuesta;
}

bool verificarInterbloqueo(int** r, int* a, int filas, int columnas) {
    int neg[filas];
    for (int i = 0; i < filas; i++) {
	neg[i] = 0;
    }
    for (int i = 0; i < filas; i++) {  // Recorremos cada columna
        for (int j = 0; j < columnas; j++) {  // Recorremos cada fila de la matriz
            int diferencia = a[j] - r[i][j];  // Operación a[i] - r[j][i]
            if (diferencia < 0) {  // Si la diferencia es negativa
		neg[i] = -1;
		break;
            }
        }
    }
    bool x = true;
    for(int i = 0; i < filas; i++){
	if( neg[i] == -1){
	    x = x && true;
	}else{
	    x = x && false;
	}

    }
    return x;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
	printf("Uso: %s <nombre del archivo>\n", argv[0]);
	return 1;
    }

    int filas = 0, columnas = 0;


    int** matriz = matrizFile(argv[1]);
    contarFilasColumnas(argv[1], &filas, &columnas);
    printf("fila: %d, col: %d\n", filas, columnas);
    imprimirMatriz(matriz, filas, columnas);

    int c[columnas];
    sumarColumnas1(matriz, filas,columnas, c); 
    for (int i = 0; i < columnas; i++) {
	printf("%d: %d ", i, c[i]);
    }
    printf("\n");

    int** e = matrizFile(argv[2]);
    int a[columnas];
    for (int i = 0; i < columnas; i++) {
	a[i] = e[0][i] - c[i];
    }
    for (int i = 0; i < columnas; i++) {
	printf("%d ", a[i]);
    }
    printf("\n");

    int** r = matrizFile(argv[3]);
    int filR= 0;
    int colR = 0;
    contarFilasColumnas(argv[3], &filR, &colR);
    for(int i = 0; i < filR; i++){
	for(int j = 0; j < colR; j++){
	    printf("%d ", r[i][j]);
	}
	printf("\n");
    }

    ListaCiclicaDeListas *lista = crearListaCiclica();
    for(int i = 0; i < filR; i++){
	agregarNodo(lista, r[i], colR, i);
    }

    printf("\n");
    printf("Tamaño de la lista: %d\n", obtenerTamano(lista));
    imprimirLista(lista);

    Nodo *temp = lista->cabeza;
    int indice = 0;

    while(obtenerTamano(lista) > 0){
	if(!hayAlgunNegativoEnlaLista(a, temp->datos, colR)){
	    eliminarNodo(lista,indice);

	}
	temp = temp->siguiente;
	/* if(indice == obtenerTamano(lista) - 1){ */
	/*     printf("interbloqueo\n"); */
	/*     exit(0); */
	/* } */
	indice = indice % obtenerTamano(lista);
	printf("el indice es: %d\n", indice);
    }




    if(verificarInterbloqueo(r, a, filR, colR)){
	printf("interbloqueo");
    }else{
	printf("no hay interbloqueo");
    }

    int i = 0;
    while (filR > i ) {
	i += 1;
    }

    // Liberar memoria
    for (int i = 0; i < filas; i++) {
	free(matriz[i]);
    }
    free(matriz);

    return 0;
}
