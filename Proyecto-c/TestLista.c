#include <stdlib.h>
#include <stdio.h>
#include "LISTA.h"

int* crearElementoEntero(int v){
    int* pEnt=(int*) malloc (sizeof(int));
    *pEnt=v;
    return pEnt;
}
void fEliminar(tElemento p);

void mostrarLista(tLista lista);

int l_main ()
{
    int *a,*b,*c,*d,*e;

    a=(int*)malloc(sizeof(int));
    b=(int*)malloc(sizeof(int));
    c=(int*)malloc(sizeof(int));
    d=(int*)malloc(sizeof(int));
    e=(int*)malloc(sizeof(int));

    *a=0;
    *b=1;
    *c=2;
    *d=3;
    *e=4;

    //Inicializo lista.
    tLista lista_prueba;
    crear_lista(&lista_prueba);
    printf("Se crea una lista nueva. Longitud: %i\n", l_longitud(lista_prueba));

    //Insertar.
    l_insertar(lista_prueba,l_primera(lista_prueba),a);
    printf("Se inserto el '0'. Longitud: %i\n",l_longitud(lista_prueba));
    mostrarLista(lista_prueba);
    printf("\n");

    l_insertar(lista_prueba,l_siguiente(lista_prueba,l_primera(lista_prueba)),d);
    printf("Se inserto el '3'. Longitud: %i\n",l_longitud(lista_prueba));
    mostrarLista(lista_prueba);
    printf("\n");

    l_insertar(lista_prueba,l_ultima(lista_prueba),c);
    printf("Se inserto el '2'. Longitud: %i\n",l_longitud(lista_prueba));
    mostrarLista(lista_prueba);
    printf("\n");

    l_insertar(lista_prueba,l_anterior(lista_prueba,l_ultima(lista_prueba)),b);
    printf("Se inserto el '1'. Longitud: %i\n",l_longitud(lista_prueba));
    mostrarLista(lista_prueba);
    printf("\n");

    l_insertar(lista_prueba,l_fin(lista_prueba),e);
    printf("Se inserto el '4'. Longitud: %i\n",l_longitud(lista_prueba));
    mostrarLista(lista_prueba);
    printf("\n");

    //Eliminar.
    printf("Se elimina el primer elemento de la lista.\n");
    l_eliminar(lista_prueba, l_primera(lista_prueba), &fEliminar);
    printf("Longitud: %i\n", l_longitud(lista_prueba));
    mostrarLista(lista_prueba);
    printf("\n");



    printf("Se elimina el anteultimo elemento de la lista.\n");
    l_eliminar(lista_prueba, l_anterior(lista_prueba, l_ultima(lista_prueba)), &fEliminar);
    printf("longitud %i\n", l_longitud(lista_prueba));
    mostrarLista(lista_prueba);
    printf("\n");

    //l_siguiente(lista_prueba,l_fin(lista_prueba));
    //l_anterior(lista_prueba,l_primera(lista_prueba));
    //l_recuperar(lista_prueba,l_fin(lista_prueba));

    printf("Se destruye la lista.\n");
    l_destruir(&lista_prueba, fEliminar);





    tLista lp;
    crear_lista(&lp);

    int * elemGen = (int*) malloc(sizeof(int)) ;
    int valor=0;
    *elemGen=valor;
    tElemento ver;

    while(valor<10){     ///inserto 10 elementos y los recupero para ver quese inserten correctamente

        l_insertar(lp,l_fin(lp),crearElementoEntero(valor)); ///Inserto
        ver=l_recuperar(lp,l_ultima(lp));   ///Almaceno
        elemGen=(int*) ver;
        printf("valor: %i\n", *elemGen);
        valor++;
    }

    int longit=l_longitud(lp);
    printf("longitud de la lista: %i\n",longit);

    tPosicion referencia=l_primera(lp);
    tPosicion fin=l_fin(lp);
    while(referencia!=fin){
        ver=l_recuperar(lp,referencia);
        elemGen=(int*) ver;
        printf("elemento: %i\n",*elemGen);
        referencia=l_siguiente(lp,referencia);
    }
    while(referencia!=l_primera(lp)){
        referencia=l_anterior(lp,referencia);
        ver=l_recuperar(lp,referencia);
        elemGen=(int*) ver;
        printf("elemento: %i\n",*elemGen);
    }
       /* ver=l_recuperar(lp,referencia);
        elemGen=(int*) ver;
        printf("elemento: %i\n",*elemGen);
        */
    l_destruir(&lp,fEliminar); //destruye la lista, funciona
    l_anterior(lp,l_primera(lp));
    printf("CHECK");
    ver=l_primera(lp);
    elemGen=(int*) ver;
    printf("Si este valor es cero probablemente no destruya bien: %i",*elemGen);

    while(valor>=0){//Elimino todos los elementos recien insertados mas uno generando el error 4 (si funciona)
        l_eliminar(lp,l_ultima(lp),fEliminar);
        valor--;
    }


    return 0;
}



void fEliminarl(tElemento p){
    free(p);
    printf("elimino bien\n");
};

void mostrarLista(tLista lista) {

    tPosicion cursor = l_primera(lista);

    tPosicion finLista = l_fin(lista);

    int* valor;



    while(cursor != finLista) {

        valor = (int *) l_recuperar(lista, cursor);

        printf("[%i] ", *valor);

        cursor = l_siguiente(lista, cursor);

    }
    printf("\n");
}
