#include <stdlib.h>
#include <stdio.h>
#include "LISTA.h"

int main ()
{
    tLista* lista_prueba;///=(struct celda**) malloc(sizeof(struct celda));

    struct celda Centinela;
    tLista lista=(struct celda*) malloc(sizeof(struct celda));
    lista_prueba=&lista;
    lista=&Centinela;
    crear_lista(lista_prueba);
    printf("imprimi algo");
    return 0;
}
