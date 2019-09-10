#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

void crear_lista(tLista* l)
{
    l=(struct celda**) malloc(sizeof(struct celda));
    l->elemento=NULL;//elemento nulo.
    l->siguiente=NULL;//el puntero al sig elemento es nulo.

}

void l_insertar(tLista l, tPosicion p, tElemento e)
{
    //Averiguar si P esta apuntando a B por que es con posicion indirecta, ent para que sirve l o si apunta a c y tengo q recorrer l.

}

void l_eliminar(tLista l, tPosicion p, void(* fEliminar)(tElemento))
{
    if(l_ultima(l)==p)//chequea si la posicion p es valida.
        exit("LST_POSICION_INVALIDA");


}

void l_destruir(tLista* l, void(* fEliminar)(tElemento))
{

}

tElemento l_recuperar(tLista l, tPosicion p)
{

}

tPosicion l_primera(tLista l)
{

}

tPosicion l_siguiente(tLista l, tPosicion p)
{

}

tPosicion l_anterior(tLista l, tPosicion p)
{

}

tPosicion l_ultima(tLista l)
{

}

tPosicion l_fin(tLista l)
{

}

int l_longitud(tLista l)
{

}

lista::~lista()
{
    //dtor
}
