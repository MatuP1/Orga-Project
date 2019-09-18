#include <stdlib.h>
#include <stdio.h>
#include "LISTA.h"

tElemento p;
void fEliminar(tElemento p){
    free(p);
    printf("elimino bien\n");
};

int main ()
{
    tLista lista_prueba;///inisializado para prevenir el warning
    crear_lista(&lista_prueba);///asocia lista_prueba a una celda centinela

    int * elemGen;
    int valor=6;
    elemGen=&valor;
    l_primera(lista_prueba); //actualizacion test
    l_insertar(lista_prueba,l_primera(lista_prueba),elemGen);
    int* el=(int*)l_recuperar(lista_prueba,l_primera(lista_prueba));
    printf("%i otra cosa\n %i\n",*el,l_longitud(lista_prueba));
    l_eliminar(lista_prueba,l_primera(lista_prueba), fEliminar);
    printf("llego");
    return 0;
}
