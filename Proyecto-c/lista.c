#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

void crear_lista(tLista* l)
{
    *l=(tPosicion) malloc(sizeof(struct celda));
    //*l=&lista;
    (*l) -> elemento=NULL; ///elemento nulo.
    (*l) -> siguiente=NULL; ///el puntero al sig elemento es nulo.

}

void l_insertar(tLista l, tPosicion p, tElemento e) //asumiendo posicion indirecta
{
    tPosicion nuevaCelda=(tPosicion) malloc(sizeof(struct celda));
    nuevaCelda->elemento=e;
    nuevaCelda->siguiente=p->siguiente;
    p->siguiente=nuevaCelda;
}

void l_eliminar(tLista l, tPosicion p, void (*fEliminar)(tElemento))
{
    if(l_fin(l)==p)//chequea si la posicion p es valida.
            exit(LST_POSICION_INVALIDA); //Lista Posicion Invalida;

    tPosicion aux=p->siguiente;
    p->siguiente=(aux->siguiente); //Creo que esta bien
    fEliminar(aux->elemento);
    free(aux); //libero el espacio de la celda a eliminar
}

void l_destruir(tLista* l, void (*fEliminar)(tElemento))
{
    tPosicion actual=(*l)->siguiente;
    tPosicion aux;
    while(l_ultima(*l)!=actual){
        fEliminar(actual->elemento);
        aux=actual;
        actual=(aux->siguiente);
        free(aux);
    }
    free(l);
}

tElemento l_recuperar(tLista l, tPosicion p)
{
    if(p==l_fin(l))
        exit(LST_POSICION_INVALIDA);
    return (p->siguiente->elemento);
}

tPosicion l_primera(tLista l)
{
    return l;
}

tPosicion l_siguiente(tLista l, tPosicion p)
{
    if((p) == l_ultima(l))
        exit (LST_NO_EXISTE_SIGUIENTE);
    return p->siguiente->siguiente;
}

tPosicion l_anterior(tLista l, tPosicion p)
{
    if(p == l_primera(l))
        exit(LST_NO_EXISTE_ANTERIOR);
    tPosicion anterior=l->siguiente;
    while (anterior->siguiente->siguiente != p){
        anterior=anterior->siguiente;
    }
    return anterior;
}

tPosicion l_ultima(tLista l)
{
    if(l->siguiente == NULL){
        return l;
    }
    tPosicion iterador=l;
    while(iterador->siguiente->siguiente !=NULL){
        iterador=iterador->siguiente;
    }
    return iterador;
}

tPosicion l_fin(tLista l)
{
    tPosicion iterador=l;
    while(iterador->siguiente != NULL){
        iterador=iterador->siguiente;
    }
    return iterador;
}

int l_longitud(tLista l)
{
    int cont=0;
    tPosicion iterador=l;
    while(iterador->siguiente !=NULL){
        iterador=iterador->siguiente;
        cont++;
    }
    return cont;
}
