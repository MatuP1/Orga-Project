#include <stdlib.h>
#include <stdio.h>
#include "arbol.h"
#include "lista.h"


///#define noHijoDePadre
///#define elimRaizConMasHijos
///#define raizNula

/**Muestra el arbol en preorden.

*/
void fEliminar(tElemento p){
    int* valor=(int *)p;
    printf("se elimino el elemento[%i]\n",*valor);
    free(p);
};
/**Recorrido en preOrden.
*/
void preOrdenMostrar(tArbol arbol,tNodo cursor,tLista hijos){
    int* valor=(int *)cursor->elemento;
    int* vPadre;
    if(cursor==a_raiz(arbol)){
        printf("[%i] es raiz; ",*valor);
    }
    else{
        vPadre=(int*)cursor->padre->elemento;
        printf("[%i] es hijo de [%i]; ",*valor,*vPadre);
    }
    tPosicion posActual=l_primera(hijos);
    tPosicion posFinal=l_fin(hijos);
    while(posActual!=posFinal){
        tNodo elemPosActual=l_recuperar(hijos,posActual);
        tLista hijosPosActual=a_hijos(arbol,l_recuperar(hijos,posActual));
        preOrdenMostrar(arbol,elemPosActual,hijosPosActual);
        posActual=l_siguiente(hijos,posActual);
    }
}

void mostrarArbol(tArbol arbol){
    if(a_raiz(arbol)!=NULL){
        preOrdenMostrar(arbol,a_raiz(arbol),a_hijos(arbol,a_raiz(arbol)));
    }
    else{
        printf("El arbol esta vacio\n");
    }
    printf("\n");

}
int a_main(){

    int *a,*b,*c,*d,*e,*f,*g,*h,*i,*j,*k;

    tNodo insA,insB,insC,insD,insE,insF,insG,insH,insI,insJ,insK;

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
    k=(int*)malloc(sizeof(int));

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
    *k=10;

    //Inicializo el arbol.
    tArbol* ar=(tArbol*) malloc(sizeof(tArbol));
    crear_arbol(ar);
    printf("Se creo un nuevo arbol\n");

    //Insertar.
    #ifdef raizNula

    crear_raiz(*ar,NULL);
    #endif // raizNula
    crear_raiz(*ar,a);
    tArbol este=*ar; //para simplificar(?
    int* noson30mil=(int*)(a_recuperar(este,a_raiz(este)));
    printf("Se inserto el %i.\n",*noson30mil);
    mostrarArbol(*ar);
    insA=a_raiz(*ar);
    insB=a_insertar(*ar,insA,NULL,b);
    noson30mil=(int*)insB->elemento;
    printf("Se inserto el '%i'.\n",*noson30mil);
    mostrarArbol(*ar);

    insC=a_insertar(*ar,insB,NULL,c);
    noson30mil=(int*)insC->elemento;
    printf("Se inserto el '%i' = '2'.\n",*noson30mil);
    mostrarArbol(*ar);

    insD=a_insertar(*ar,insC,NULL,d);
    noson30mil=(int*)insD->elemento;

    printf("Se inserto el '%i' = '3'.\n",*noson30mil);
    mostrarArbol(*ar);

    insE=a_insertar(*ar,insD,NULL,e);
    noson30mil=(int*)insE->elemento;
    printf("Se inserto el '%i' = '4'.\n",*noson30mil);
    mostrarArbol(*ar);

    insF=a_insertar(*ar,insC,insD,f);
    noson30mil=(int*)insF->elemento;
    printf("Se inserto el '%i' = '5'.\n",*noson30mil);
    mostrarArbol(*ar);

    insG=a_insertar(*ar,insB,insC,g);
    noson30mil=(int*)insG->elemento;
    printf("Se inserto el '%i' = '6'.\n",*noson30mil);
    mostrarArbol(*ar);

    insH=a_insertar(*ar,insA,NULL,h);
    noson30mil=(int*)insH->elemento;
    printf("Se inserto el '%i' = '7'.\n",*noson30mil);
    mostrarArbol(*ar);

    insI=a_insertar(*ar,insH,NULL,i);
    noson30mil=(int*)insI->elemento;
    printf("Se inserto el '%i' = '8'.\n",*noson30mil);
    mostrarArbol(*ar);

    insJ=a_insertar(*ar,insH,insI,j);
    noson30mil=(int*)insJ->elemento;
    printf("Se inserto el '%i' = '9'.\n",*noson30mil);
    mostrarArbol(*ar);

    insK=a_insertar(*ar,insA,insB,k);
    noson30mil=(int*)insK->elemento;
    printf("Se inserto el '%i' = '10'.\n",*noson30mil);

    #ifdef noHijoDePadre
    a_insertar(*ar,insK,insA,k);///Inserto el elemento k=10 como hijo de insK y hermando de insA, pero como insA es la raiz devuelve error.

    #endif // noHijoDePadre

    #ifdef elimRaizConMasHijos
    a_eliminar(*ar,a_raiz(*ar),fEliminar);
    #endif // elimRaizConMasHijos


    //test subArbol que usa insertar y eliminar.
    tArbol sar;
    crear_arbol(&sar);
    printf("Se creo un nuevo *arbol\n");
    printf("Primer arbol antes de utilizar la funcion subArbol\n");
    mostrarArbol(*ar);
    if(insB!=((*ar)->raiz)){
        a_sub_arbol(*ar,insC,&sar);
    }
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


