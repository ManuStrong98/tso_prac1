#include "funciones/leerFile.c"
#include "funciones/sumarCol.c"
#include "include/leerFile.h"
#include "funciones/estructuraDeDato/listaEnlazadasDeListaInt.c"
#include "include/listaEnlazadasDeListaInt.h"
#include "include/sumarCol.h"
#include <stdio.h>
#include<stdbool.h>// Booleanos
#include <stdlib.h>

void volverTodaLaFilaEn0(int** c, int index, int col){
    for(int i = 0; i < col; i++){
	c[index][i] = 0;
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
    /* printf("fila: %d, col: %d\n", filas, columnas); */
    printf("archivo C: \n");
    imprimirMatriz(matriz, filas, columnas);
    printf("\n");

    int c[columnas];
    sumarColumnas1(matriz, filas,columnas, c); 
    /* for (int i = 0; i < columnas; i++) { */
	/* printf("%d: %d ", i, c[i]); */
    /* } */
    /* printf("\n"); */

    int** e = matrizFile(argv[2]);
    printf("archivo E: \n");
    imprimirMatriz(e, 1, columnas);
    printf("\n");
    int a[columnas];
    for (int i = 0; i < columnas; i++) {
	a[i] = e[0][i] - c[i];
    }
    /* for (int i = 0; i < columnas; i++) { */
	/* printf("%d ", a[i]); */
    /* } */
    /* printf("\n"); */

    int** r = matrizFile(argv[3]);
    int filR= 0;
    int colR = 0;
    contarFilasColumnas(argv[3], &filR, &colR);
    printf("archivo R: \n");
    imprimirMatriz(r, filR, colR);
   /* for(int i = 0; i < filR; i++){ */
	/* for(int j = 0; j < colR; j++){ */
	    /* printf("%d ", r[i][j]); */
	/* } */
	/* printf("\n"); */
    /* } */

    ListaCiclicaDeListas *lista = crearListaCiclica();
    for(int i = 0; i < filR; i++){
	agregarNodo(lista, r[i], colR, i);
    }

    /* printf("\n"); */
    /* printf("Tamaño de la lista: %d\n", obtenerTamano(lista)); */
    /* imprimirLista(lista); */

    Nodo *temp = lista->cabeza;
    int indice = 0;
    char* mensajeInterB = "hay interbloqueo";
    int k = 0;

    while(obtenerTamano(lista) > 0){
	if(!hayAlgunNegativoEnlaLista(a, temp->datos, colR)){
	    volverTodaLaFilaEn0(matriz, temp->indice, colR);
	    sumarColumnas1(matriz, filas,  columnas, c);

	    eliminarNodo(lista,indice);

	}
	temp = temp->siguiente;
	indice = (k) % obtenerTamano(lista);
	if(obtenerTamano(lista) == 1){
	    temp = lista->cabeza;
	    indice = 0;
	}
	k++;
	if(obtenerTamano(lista) <= 1){
	    mensajeInterB = "no hay interbloqueo";
	    break;
	}
    }
    printf("%s", mensajeInterB);


    for (int i = 0; i < filas; i++) {
	free(matriz[i]);
    }
    free(matriz);

    return 0;
}
