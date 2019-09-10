#include "lista.h"


void crear_lista(tLista* l)
{
    l= tPosicion;//typedef struct celda * tPosicion.
    l.elemento=null;//elemento nulo.
    l.siguiente=null;//el puntero al sig elemento es nulo.

}

void l_insertar(tLista l, tPosicion p, tElemento e)
{

}

void l_eliminar(tLista l, tPosicion p, void(* fEliminar)(tElemento))
{

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
