#include <lista.h>
#include "arbol.h"
#include <stdio.h>
#include <stdlib.h>

void crear_arbol(tArbol* a)
{
    a=(arbol *) malloc(sizeof(arbol));
    a->raiz=NULL;
}

void crear_raiz(tArbol a, tElemento e)
{

    if((a->raiz)!=NULL)
        exit(ARB_OPERACION_INVALIDA);
    a->raiz=(nodo *) malloc(sizeof(nodo));           //reservo espacio raiz
    tLista hijosRaiz;                                //reservo lista hijos
    a->raiz->elemento=e;                             //asigno el elemento de la raiz
    crear_lista(*hijosRaiz);                         //creo la lista de hijos
    a->raiz->hijos=hijosRaiz;
    a->raiz->padre=NULL;                             //elimino al padre
}

tNodo a_insertar(tArbol a, tNodo np, tNodo nh, tElemento e)
{
    tNodo ret=(nodo*) malloc(sizeof(nodo));
    tLista hijosI;
    crear_lista(*hijosI);
    ret->hijos=hijosI;
    ret->padre=np;
    ret->elemento=e;
    tLista hijosPadre=np->hijos;
    if(nh==NULL){
        l_insertar(np->hijos,l_fin(np->hijos),ret);
    }
    else{
        if(nh->padre!=np)
            exit(ARB_POSICION_INVALIDA)
        else{
            tNodo hijoAux=l_primera(hijosPadre);
            while(hijoAux!=l_fin(hijosPadre)){
                if(hijoAux==nh){
                    l_insertar(hijosPadre,nh,ret);
                    hijoAux=l_ultima(hijosPadre);
                }
                hijoAux=l_siguiente(hijoAux);
            }
        }
    }
    return ret;
}

void a_eliminar(tArbol a, tNodo n, void(* fEliminar)(tElemento))
{
    if(n==a->raiz){
        if(l_longitud(n->hijos)>1)
            exit(ARB_OPERACION_INVALIDA);

        if(l_longitud(n->hijos)==1){
            a->raiz=l_primera(n->hijos);
        }
    }
    else{
        tNodo padreNuevo=n->padre;
        tLista hermanos=padreNuevo->hijos;
        tLista hijosNuevos=n->hijos;
        tPosicion posInicial=l_primera(hermanos);
        while(posInicial->elemento!=n){
            posInicial=l_siguiente(hermanos,posInicial);
        }
        tPosicion pHijoActual=l_primera(hijosNuevos);
        tPosicion final=l_fin(hijosNuevos);
        while(pHijoActual!=final){
            tNodo hijoActual;
            l_insertar(hermanos,posInicial,l_recuperar(pHijoActual))
            hijoActual=(tNodo)l_recuperar(pHijoActual);
            hijoActual->padre=padreNuevo;
            pHijoActual=l_siguiente(hijosNuevos,pHijoActual);
        }
    }
    fEliminar(n->elemento);
    n->padre=NULL;
    free(n->hijos); //PREGUNTARRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
    free(n);

}

void a_destruir(tArbol* a, void(* fEliminar)(tElemento))
{
    ElimPreOrden(*a,*a->raiz,fEliminar());
    *a=NULL;
    free(a);
}

/**
    Recorrido en preOrden que elimina.
*/
void ElimPreOrden(tArbol arbol,tNodo cursor,void(* fEliminar)(tElemento)){
    tNodo nodoEnListaHijo = l_primera((cursor->hijos));
    tNodo finListaHijo = l_fin(cursor->hijos);
    while(cursor != finListaHijo){
        preOrden(arbol,nodoEnListaHijo);
    }
   a_eliminar(arbol,cursor,fEliminar());

}

tNodo BuscarPreOrden(tArbol arbol,tNodo cursor, tNodo buscado, tNodo encontrado){
    tNodo nodoEnListaHijo = l_primera((cursor->hijos));
    tNodo finListaHijo = l_fin(cursor->hijos);
    while(cursor != finListaHijo && cursor!=buscado){
        preOrden(arbol,nodoEnListaHijo);
    }
    if(cursor==buscado)
        encontrado=buscado;
    return encontrado;
}

tElemento a_recuperar(tArbol a, tNodo n)
{
    tNodo retorno=BuscarPreOrden(a,a->raiz,n,retorno);
    return retorno->elemento;
}

tNodo a_raiz(tArbol a)
{
    return a->raiz;
}

tLista a_hijos(tArbol a, tNodo n)
{
    return n->hijos;
}

void a_sub_arbol(tArbol a, tNodo n, tArbol* sa)
{
    crear_arbol(sa);
    subArbolEnPreOrden(a,*sa,n->padre,n->padre->hijos,n);
}

/**Recorrido en preOrden.
*/
void subArbolEnPreOrden(tArbol arbol,tArbol subArbol,tNodo padre,tLista hijosPadre,tNodo cursor){

    if(a_raiz(subArbol)==null)
        crear_raiz(cursor);
    else
        a_insertar(subArbol,padre,NULL,cursor->elemento);
    tNodo nodoEnListaHijo = l_primera((cursor->hijos));
    tNodo finListaHijo = l_fin(cursor->hijos);
    while(cursor != finListaHijo){
        preOrden(arbol,subArbol,cursor,cursor->hijos,nodoEnListaHijo);
        nodoEnListaHijo=l_siguiente(arbol,nodoEnListaHijo);
        a_eliminar(arbol,cursor,fEliminar());
    }



}
