#include <stdlib.h>
#include <stdio.h>
#include "arbol.h"
#include "lista.h"


/**Muestra el arbol en preorden.

*/
void mostarArbol(tArbol arbol){

    tNodo cursor = a_raiz(arbol);

    preOrden(arbol,cursor);

    printf(\n);

}

/**Recorrido en preOrden.
*/
void preOrden(tArbol arbol,tNodo cursor){

    int *valor = (int *)a_recuperar(arbol,cursor);
    printf("[%i] ", *valor);
    tNodo nodoEnListaHijo = l_primera((cursor->hijos));
    tNodo finListaHijo = l_fin(cursor->hijos);
    while(cursor != finListaHijo){
        preOrden(arbol,nodoEnListaHijo);
        nodoEnListaHijo=l_siguiente(arbol,nodoEnListaHijo);
    }
}

int main(){

    int *a,*b,*c,*d,*e;

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
    tArbol ar;
    crear_arbol(ar);
    printf("Se creo un nuevo arbol");

    //Insertar.
    crear_raiz(ar,a);
    printf("Se inserto el '0'.\n);
    mostarArbol(ar);

    a_insertar(ar,a,NULL,b);
    printf("Se inserto el '1'.\n);
    mostarArbol(ar);

    a_insertar(ar,b,NULL,c);
    printf("Se inserto el '2'.\n);
    mostarArbol(ar);

    a_insertar(ar,c,NULL,d);
    printf("Se inserto el '3'.\n);
    mostarArbol(ar);

    a_insertar(ar,d,NULL,e);
    printf("Se inserto el '4'.\n);
    mostarArbol(ar);

    a_insertar(ar,c,NULL,f);
    printf("Se inserto el '5'.\n);
    mostarArbol(ar);

    a_insertar(ar,b,NULL,g);
    printf("Se inserto el '6'.\n);
    mostarArbol(ar);

    a_insertar(ar,a,NULL,h);
    printf("Se inserto el '7'.\n);
    mostarArbol(ar);

    a_insertar(ar,h,NULL,i);
    printf("Se inserto el '8'.\n);
    mostarArbol(ar);

    a_insertar(ar,h,NULL,j);
    printf("Se inserto el '9'.\n);
    mostarArbol(ar);

    //test subArbol que usa insertar y eliminar.
    tArbol sar;
    crear_arbol(sar);
    printf("Se creo un nuevo arbol");
    printf("Primer arbol antes de utilizar la funcion subArbol\n")
    mostarArbol(ar)
    a_sub_arbol(ar,b,sa);
    printf("Primer arbol despues de utilizar la funcion subArbol\n");
    mostarArbol(ar);
    printf("Segundo arbol despues de utilizar la funcion subArbol\n");
    mostarArbol(sar);

    //test destruir.
    a_destruir(ar,fEliminar());
    printf("Se destruyo el primer arbol\n");
    a_destruir(sar,fEliminar());
    printf("Se destruyo el segundo arbol\n");

    return 0;
}
