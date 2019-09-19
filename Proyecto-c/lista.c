#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
void crear_lista(tLista* l)
{
    *l=(tLista) malloc(sizeof(struct celda));

    if(*l==NULL)
        exit(LST_ERROR_MEMORIA);

    (*l) -> elemento=NULL; ///elemento nulo.
    (*l) -> siguiente=NULL; ///el puntero al sig elemento es nulo.

}

void l_insertar(tLista l, tPosicion p, tElemento e)
{
    tPosicion nuevaCelda=(tPosicion) malloc(sizeof(struct celda));
    if(nuevaCelda==NULL)
        exit(LST_ERROR_MEMORIA);
    nuevaCelda->elemento=e;
    nuevaCelda->siguiente=p->siguiente;
    p->siguiente=nuevaCelda;
}

void l_eliminar(tLista l, tPosicion p, void (*fEliminar)(tElemento))
{
    if(p->siguiente==NULL)//chequea si la posicion p es valida.
            exit(LST_POSICION_INVALIDA); //Lista Posicion Invalida;

    tPosicion aux=p->siguiente;
    p->siguiente=(aux->siguiente);
    fEliminar(aux->elemento);
    aux->elemento=NULL;    //Elimino puntero
    aux->siguiente=NULL;
    free(aux); //libero el espacio de la celda a eliminar
}

void l_destruir(tLista* l, void (*fEliminar)(tElemento))
{
    tPosicion actual=(*l)->siguiente;
    tPosicion aux;
    while(actual != NULL){
        fEliminar(actual->elemento);
        aux=actual;
        actual=(aux->siguiente);

        aux->elemento=NULL;    //Elimino punteros
        aux->siguiente=NULL;
        free(aux);
    }
    free(*l); //elimino puntero a la lista
    l=NULL;   //elimino puntero de puntero a la lista
}

tElemento l_recuperar(tLista l, tPosicion p)
{
    if(p->siguiente==NULL)
        exit(LST_POSICION_INVALIDA);
    return (p->siguiente->elemento);
}

tPosicion l_primera(tLista l)
{
    return l;
}

tPosicion l_siguiente(tLista l, tPosicion p)
{
    if(p->siguiente == NULL)
        exit (LST_NO_EXISTE_SIGUIENTE);
    return p->siguiente;
}

tPosicion l_anterior(tLista l, tPosicion p)
{
    if(p == l_primera(l))
        exit(LST_NO_EXISTE_ANTERIOR);
    tPosicion anterior=l->siguiente;
    while (anterior->siguiente != p){
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
//Lista Corregida 19/9/2019 sin errores
