#include <stdlib.h>
#include <stdio.h>
#include "LISTA.h"
#include "felim.h"

void *p;
void fEliminar(void (*p));

int main ()
{
    tLista* lista_prueba=NULL;///inisializado para prevenir el warning
    crear_lista(lista_prueba);///asocia lista_prueba a una celda centinela.
    ///Prueba de la funciones con lista vacia.

    l_eliminar((struct celda*)lista_prueba,(struct celda*)lista_prueba, fEliminar);///intenta eliminar el centinela, deberia devolver error.

    return 0;
}
