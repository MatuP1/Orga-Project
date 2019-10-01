#include <stdlib.h>
#include <stdio.h>
#include "arbol.h"
#include "lista.h"


/**Muestra el arbol en preorden.

*/
void fEliminar(tElemento p){
    free(p);
    printf("elimino bien\n");
};
/**Recorrido en preOrden.
*/
void preOrdenMostrar(tArbol arbol){
    int* valor=(int *)a_raiz(arbol)->elemento;
    int cantHijos=l_longitud(a_raiz(arbol)->hijos);
    printf("[%i]",*valor);
    tPosicion hijoActual=NULL;
    if(cantHijos>0){
        hijoActual=l_primera(a_raiz(arbol)->hijos);
        }
    int i = 0;
    tArbol arbolRestante;
    while(i<cantHijos){

            a_sub_arbol(arbol, hijoActual->elemento,&arbolRestante);
            preOrdenMostrar(arbolRestante);
            cantHijos--;
            hijoActual=l_siguiente(a_raiz(arbol)->hijos,hijoActual);
    }
}

/*void preOrden(tArbol arbol,tNodo cursor){

    int *valor = (int *)a_recuperar(arbol,cursor);
    printf("[%i] ", *valor);
    if(l_longitud(cursor->hijos)>0){
        tPosicion posEnListaHijo=l_primera(cursor->hijos);
        tNodo nodoEnListaHijo = posEnListaHijo->elemento;
        tNodo finListaHijo = (tNodo)l_fin(cursor->hijos)->elemento;
        while(cursor != finListaHijo){
            preOrden(arbol,nodoEnListaHijo);
            posEnListaHijo=l_siguiente(cursor->hijos,posEnListaHijo);
            nodoEnListaHijo=(tNodo)posEnListaHijo->elemento;
        }
    }
}*/

void mostrarArbol(tArbol arbol){

    tNodo cursor = a_raiz(arbol);

    preOrdenMostrar(arbol);

    printf("\n");

}
int a_main(){

    int *a,*b,*c,*d,*e,*f,*g,*h,*i,*j;

    a=(int*)malloc(sizeof(int));
    b=(int*)malloc(sizeof(int));
    c=(int*)malloc(sizeof(int));
    d=(int*)malloc(sizeof(int));
    e=(int*)malloc(sizeof(int));
    f=(int*)malloc(sizeof(int));
    g=(int*)malloc(sizeof(int));
    h=(int*)malloc(sizeof(int));
    i=(int*)malloc(sizeof(int));
    j=(int*)malloc(sizeof(int));

    *a=0;
    *b=1;
    *c=2;
    *d=3;
    *e=4;
    *f=5;
    *g=6;
    *h=7;
    *i=8;
    *j=9;

    //Inicializo el arbol.
    tArbol* ar;
    crear_arbol(ar);
    printf("Se creo un nuevo arbol\n");

    //Insertar.
    crear_raiz(*ar,a);
    printf("Se inserto el '0'.\n");
    mostrarArbol(*ar);
    tNodo ins;
    ins=a_insertar(*ar,a_raiz(*ar),NULL,b);
    printf("Se inserto el '1'.\n");
    mostrarArbol(*ar);

    ins=a_insertar(*ar,ins,NULL,c);
    printf("Se inserto el '2'.\n");
    mostrarArbol(*ar);

    ins=a_insertar(*ar,ins,NULL,d);
    printf("Se inserto el '3'.\n");
    mostrarArbol(*ar);

    ins=a_insertar(*ar,ins->padre,NULL,e);
    printf("Se inserto el '4'.\n");
    mostrarArbol(*ar);

    ins=a_insertar(*ar,ins->padre,NULL,f);
    printf("Se inserto el '5'.\n");
    mostrarArbol(*ar);

    ins=a_insertar(*ar,ins,NULL,g);
    printf("Se inserto el '6'.\n");
    mostrarArbol(*ar);

    ins=a_insertar(*ar,ins->padre,NULL,h);
    printf("Se inserto el '7'.\n");
    mostrarArbol(*ar);

    ins=a_insertar(*ar,ins,NULL,i);
    printf("Se inserto el '8'.\n");
    mostrarArbol(*ar);

    ins=a_insertar(*ar,ins->padre,NULL,j);
    printf("Se inserto el '9'.\n");
    mostrarArbol(*ar);

    //test subArbol que usa insertar y eliminar.
    tArbol sar;
    crear_arbol(&sar);
    printf("Se creo un nuevo *arbol");
    printf("Primer arbol antes de utilizar la funcion subArbol\n");
    mostrarArbol(*ar);
    //a_sub_arbol(*ar,b,sa);
    printf("Primer arbol despues de utilizar la funcion subArbol\n");
    mostrarArbol(*ar);
    printf("Segundo arbol despues de utilizar la funcion subArbol\n");
    mostrarArbol(sar);

    //test destruir.
    a_destruir(ar,fEliminar);
    printf("Se destruyo el primer arbol\n");
    a_destruir(&sar,fEliminar);
    printf("Se destruyo el segundo arbol\n");

    return 0;
}
