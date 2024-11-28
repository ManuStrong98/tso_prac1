#ifndef LISTA_CICLICA_H
#define LISTA_CICLICA_H

// Definición del nodo
typedef struct Nodo {
    int *datos;          // Puntero a un arreglo de enteros
    int tamano;          // Tamaño de la lista de enteros en este nodo
    int indice;
    struct Nodo *siguiente;
} Nodo;

// Definición de la lista enlazada cíclica
typedef struct {
    Nodo *cabeza;
    int tamano;
} ListaCiclicaDeListas;

// Declaración de funciones
ListaCiclicaDeListas* crearListaCiclica();
Nodo* crearNodo(int *arreglo, int tamano, int ind);
void agregarNodo(ListaCiclicaDeListas *lista, int *arreglo, int tamano, int ind);
int obtenerTamano(ListaCiclicaDeListas *lista);
Nodo* obtenerNodo(ListaCiclicaDeListas *lista, int indice);
void eliminarNodo(ListaCiclicaDeListas *lista, int indice);
void imprimirLista(ListaCiclicaDeListas *lista);
void liberarLista(ListaCiclicaDeListas *lista);

#endif

