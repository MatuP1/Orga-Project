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
    while(valor<10){           //inserto 100 elementos y los recupero para ver quese inserten correctamente
        l_insertar(lista_prueba,l_fin(lista_prueba),&valor); ///Inserto
        ver=l_recuperar(lista_prueba,l_ultima(lista_prueba));   ///Almaceno
        elemGen=(int*) ver;
        printf("valor: %i\n", *elemGen);                            ///Imprimo
        valor++;
    }

    int longit=l_longitud(lista_prueba);
    printf("longitud de la lista: %i\n",longit);

    tPosicion referencia=l_primera(lista_prueba);
    ver=l_recuperar(lista_prueba,l_primera(lista_prueba));
    elemGen=(int*)ver;
    printf("primer elemento: %i",*elemGen);
    while(valor>1){
        ver=l_recuperar(lista_prueba,referencia);
        elemGen=(int*) ver;
        referencia=l_siguiente(lista_prueba,referencia);
        printf("elemento: %i\n",*elemGen);
        valor--;
    }
    printf("prueba anterior\n");
    while(valor<10){
        ver=l_recuperar(lista_prueba,referencia);
        elemGen=(int*) ver;
        referencia=l_anterior(lista_prueba,referencia);
        printf("elemento: %i\n",*elemGen);
        valor++;
    }
    /**
    l_destruir(&lista_prueba,fEliminar); //destruye la lista, funciona
    printf("CHECK");
   *//** ver=l_primera(lista_prueba);
    elemGen=(int*) ver;
    printf("Si este valor es cero probablemente no destruya bien: %i",*elemGen);
    */
    /**while(valor>=0){//Elimino todos los elementos recien insertados mas uno generando el error 4 (si funciona)
        l_eliminar(lista_prueba,l_ultima(lista_prueba),fEliminar);
        valor--;
    }*/

    return 0;
}
