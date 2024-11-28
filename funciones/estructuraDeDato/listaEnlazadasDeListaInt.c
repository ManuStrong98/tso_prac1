#include <stdio.h>
#include <stdlib.h>
#include "../../include/listaEnlazadasDeListaInt.h"

// Crear una lista vacía
ListaCiclicaDeListas* crearListaCiclica() {
    ListaCiclicaDeListas *lista = (ListaCiclicaDeListas *)malloc(sizeof(ListaCiclicaDeListas));
    lista->cabeza = NULL;
    lista->tamano = 0;
    return lista;
}

// Crear un nodo con un arreglo de enteros
Nodo* crearNodo(int *arreglo, int tamano, int ind) {
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    nuevoNodo->datos = arreglo;
    nuevoNodo->tamano = tamano;
    nuevoNodo->siguiente = NULL;
    nuevoNodo->indice = ind;
    return nuevoNodo;
}

// Agregar un nuevo nodo a la lista
void agregarNodo(ListaCiclicaDeListas *lista, int *arreglo, int tamano, int ind) {
    Nodo *nuevoNodo = crearNodo(arreglo, tamano, ind);
    if (lista->cabeza == NULL) {
        lista->cabeza = nuevoNodo;
        nuevoNodo->siguiente = nuevoNodo; // Apunta a sí mismo (cíclico)
    } else {
        Nodo *temp = lista->cabeza;
        while (temp->siguiente != lista->cabeza) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevoNodo;
        nuevoNodo->siguiente = lista->cabeza;
    }
    lista->tamano++;
}

// Obtener el tamaño de la lista
int obtenerTamano(ListaCiclicaDeListas *lista) {
    return lista->tamano;
}

// Obtener un nodo por índice
Nodo* obtenerNodo(ListaCiclicaDeListas *lista, int indice) {
    if (indice < 0 || indice >= lista->tamano) {
        return NULL; // Índice fuera de rango
    }
    Nodo *actual = lista->cabeza;
    for (int i = 0; i < indice; i++) {
        actual = actual->siguiente;
    }
    return actual;
}

// Eliminar un nodo por índice
void eliminarNodo(ListaCiclicaDeListas *lista, int indice) {
    if (indice < 0 || indice >= lista->tamano) {
        printf("Índice fuera de rango.\n");
        return;
    }
    Nodo *actual = lista->cabeza;
    Nodo *anterior = NULL;

    // Caso especial: eliminar el nodo en la cabeza
    if (indice == 0) {
        while (actual->siguiente != lista->cabeza) {
            actual = actual->siguiente;
        }
        Nodo *aEliminar = lista->cabeza;
        if (lista->tamano == 1) {
            lista->cabeza = NULL; // Lista vacía
        } else {
            actual->siguiente = lista->cabeza->siguiente;
            lista->cabeza = lista->cabeza->siguiente;
        }
        free(aEliminar->datos); // Liberar el arreglo de enteros
        free(aEliminar);
    } else {
        for (int i = 0; i < indice; i++) {
            anterior = actual;
            actual = actual->siguiente;
        }
        anterior->siguiente = actual->siguiente;
        free(actual->datos); // Liberar el arreglo de enteros
        free(actual);
    }
    lista->tamano--;
}

// Imprimir los elementos de la lista
void imprimirLista(ListaCiclicaDeListas *lista) {
    if (lista->cabeza == NULL) {
        printf("La lista está vacía.\n");
        return;
    }
    Nodo *temp = lista->cabeza;
    do {
        printf("[");
        for (int i = 0; i < temp->tamano; i++) {
            printf("%d", temp->datos[i]);
            if (i < temp->tamano - 1) {
                printf(", ");
            }
        }
        printf("] -> ");
        temp = temp->siguiente;
    } while (temp != lista->cabeza);
    printf("(Lista Enlazada Ciclica)\n");
}

// Liberar la memoria de la lista
void liberarLista(ListaCiclicaDeListas *lista) {
    while (lista->tamano > 0) {
        eliminarNodo(lista, 0);
    }
    free(lista);
}

