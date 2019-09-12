#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

void crear_lista(tLista* l)
{
    struct celda Centinela;
    tLista lista=(struct celda*) malloc(sizeof(struct celda));
    lista=&Centinela;
    l=&lista;
    (*l) -> elemento=NULL; ///elemento nulo.
    (*l) -> siguiente=NULL; ///el puntero al sig elemento es nulo.

}

void l_insertar(tLista l, tPosicion p, tElemento e) //asumiendo posicion indirecta
{
    struct celda * nuevaCelda=(struct celda*) malloc(sizeof(struct celda));
    nuevaCelda->elemento=e;
    nuevaCelda->siguiente=(p->siguiente);
    p->siguiente=nuevaCelda;
    ///Averiguar si P esta apuntando a B por que es con posicion indirecta, ent para que sirve l o si apunta a c y tengo q recorrer l.

}

void l_eliminar(tLista l, tPosicion p, void (*fEliminar)(tElemento)) //quien hace fEliminar
{
    if(l_ultima(l)==p)//chequea si la posicion p es valida.
        exit(3); //Lista Posicion Invalida;


}

void l_destruir(tLista* l, void (*fEliminar)(tElemento))
{

}

tElemento l_recuperar(tLista l, tPosicion p)
{

}

tPosicion l_primera(tLista l)
{
    if(l->siguiente == NULL){
        return l;
    }
    return l->siguiente;
}

tPosicion l_siguiente(tLista l, tPosicion p)
{

}

tPosicion l_anterior(tLista l, tPosicion p)
{

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
     if(l->siguiente == NULL){
        return l;
    }
    tPosicion iterador=l;
    while(iterador->siguiente !=NULL){
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
