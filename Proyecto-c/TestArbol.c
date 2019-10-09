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

    //tNodo cursor = a_raiz(arbol);

   // preOrdenMostrar(arbol);

    printf("entro \n");

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

    //test subArbol que usa insertar y eliminar.
    tArbol sar;
    crear_arbol(&sar);
    printf("Se creo un nuevo *arbol\n");
    printf("Primer arbol antes de utilizar la funcion subArbol\n");
    mostrarArbol(*ar);
    if(insB!=((*ar)->raiz)){
    a_sub_arbol(*ar,insB,&sar);
    printf("la concha de tu madre all boys");
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
