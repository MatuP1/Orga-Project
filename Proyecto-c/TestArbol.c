#include <stdlib.h>
#include <stdio.h>
#include "arbol.h"
#include "lista.h"


/**Muestra el arbol en preorden.

*/
void mostarArbol(tArbol arbol){

    tNodo cursor = a_raiz(arbol);

    preOrden(arbol,cursor);

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
