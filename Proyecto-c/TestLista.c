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
    int * elemGen;
    int valor=0;
    elemGen=&valor;
    tElemento ver;
    tLista lista_prueba;///inisializado para prevenir el warning
    crear_lista(&lista_prueba);///asocia lista_prueba a una celda centinela
    while(valor<100){           //inserto 100 elementos y los recupero para ver quese inserten correctamente

        l_insertar(lista_prueba,l_ultima(lista_prueba),&valor); ///Inserto
        ver=l_recuperar(lista_prueba,l_ultima(lista_prueba));   ///Almaceno
        elemGen=(int*) ver;
        printf("valor: %i\n", *elemGen);                            ///Imprimo
        valor++;
    }
    l_destruir(&lista_prueba,fEliminar);
    printf("CHECK");
   /* ver=l_primera(lista_prueba);
    elemGen=(int*) ver;
    printf("Si este valor es cero probablemente no destruya bien: %i",*elemGen);
    */
    /**while(valor>=0){//Elimino todos los elementos recien insertados mas uno generando el error 4 (si funciona)
        l_eliminar(lista_prueba,l_ultima(lista_prueba),fEliminar);
        valor--;
    }*/

    return 0;
}
