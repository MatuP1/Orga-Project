#include "lista.h"
#include "arbol.h"
#include <stdio.h>
#include <stdlib.h>
void fnoElminar(void * nada){}
void (*fEliminarUsuario)(tElemento);
void auxDestruir(tElemento elemento);

void crear_arbol(tArbol* a)

{
    ///Asigno memoria,
    *a=(tArbol) malloc(sizeof(struct arbol));
    ///Si la memoria no se asigno produce un error.
    if((*a)==NULL)
        exit(ARB_ERROR_MEMORIA);
    ///Inicializo la variable de la estructura en nulo.
    (*a)->raiz=NULL;
}

void crear_raiz(tArbol a, tElemento e)
{
    ///Si la raiz ya existe la operacion es invalida.
    if((a->raiz)!=NULL)
        exit(ARB_OPERACION_INVALIDA);
    a->raiz=(tNodo) malloc(sizeof(struct nodo));//reservo espacio raiz
    ///Si la memoria no se asigno produce un error.
    if(a->raiz==NULL)
        exit(ARB_ERROR_MEMORIA);

    tLista hijosRaiz;                                //reservo lista hijos
    a->raiz->elemento=e;                             //asigno el elemento de la raiz
    crear_lista(&hijosRaiz);                         //creo la lista de hijos
    a->raiz->hijos=hijosRaiz;                        //Asugbi a la variable de la lista de hijos de la estructura de la raiz una lista vacia;
    a->raiz->padre=NULL;                             //elimino al padre.
}

tNodo a_insertar(tArbol a, tNodo np, tNodo nh, tElemento e)
{
    ///Asigno memoria.
    tNodo ret=(tNodo) malloc(sizeof(struct nodo));
    ///Si la memoria no se asigno produce un error.
    if(ret==NULL)
        exit(ARB_ERROR_MEMORIA);

    tLista hijosI;
    crear_lista(&hijosI); // creo la lista de hijos que va a tener el nodo insertado
    ret->hijos=hijosI;
    ret->padre=np;        //le asigno su nuevo padre
    ret->elemento=e;      //le asigno su nuevo elemento

    tLista hijosPadre=np->hijos;   //guardo la lista de hijos del padre
    tPosicion hermanoFin = l_fin(hijosPadre); // guardo el ultimo hijo del padre

    if(nh==NULL){  //si el nodo hermano es nulo inserto al final
        l_insertar(hijosPadre,hermanoFin,ret);
        printf("inserte con NULL\n");
    }

    else{
        if((nh->padre)!=np)           //si nh no es un hijo del padre error
            exit(ARB_POSICION_INVALIDA);

        else{
            tPosicion hijoAux=l_primera(hijosPadre); //tomo al primer hijo del padre
            int i=0;
            int parar=l_longitud(hijosPadre);
            ///Mientras no encuentre al nodo nh,recorro la lista.
            while(i<=parar){
                ///Si encuentro al nodo nh inserto el nodo creado ret.
                if(((tNodo)l_recuperar(hijosPadre,hijoAux)==nh)){
                    l_insertar(hijosPadre,hijoAux,ret);
                    i=parar;
                }
                hijoAux=l_siguiente(hijosPadre,hijoAux);
                i++;
            }
        }
    }
    ///Retorno el nuevo nodo creado.dw
    return ret;
}

void a_eliminar(tArbol a, tNodo n, void(* fEliminar)(tElemento))
{
    ///Si el nodo dado es la raiz.
    if(n==(a->raiz)){
        ///Si la raiz tiene mas de un hijo la operacion es invalida.
        if(l_longitud(n->hijos)>1)
            exit(ARB_OPERACION_INVALIDA);
        ///Si la raiz no tiene hijos.
        if(l_longitud(n->hijos)==0){
            ///Elimino el elemento del nodo, destruyo su lista y libero la memoria.
            fEliminar(n->elemento);
            l_destruir(&n->hijos,fnoElminar);
            free(n);
            a->raiz=NULL;
        }
        ///Si la raiz tiene un hijo.
        if(l_longitud(n->hijos)==1){
            ///Asigno a su unico hijo como raiz.
            (a->raiz)=(tNodo)l_recuperar(n->hijos,l_primera(n->hijos));
            ///Asigno al padre de la nueva raiz nulo.
            (a->raiz->padre)=NULL;
            ///Elimino el elemento del nodo dado, elimino de su lista de hijo a la nueva raiz sin liberar la memoria de este y luego destruyo la lista.
             fEliminar(n->elemento);
             l_eliminar(n->hijos,l_primera(n->hijos),fnoElminar);
             l_destruir(&(n->hijos),fnoElminar);
             ///Libero la memoria del nodo dado.
             free(n);
        }
    }
    ///Si el nodo no es la raiz.
    else{
        ///Guardo en una variable auxiliar al padre del nodo dado.
        tNodo padreNuevo=n->padre;
        ///Guardo en una variable auxiliar la lista de hijos del padre del nodo dado.
        tLista hermanos=padreNuevo->hijos;
        ///Guardo en una variable auxiliar a la lista de hijos del nodo dado.
        tLista hijosNuevos=n->hijos;
        ///Guardo la primera posicion de la lista de hijos del padre del nodo dado.
        tPosicion posInicial=l_primera(hermanos);
        ///Recorro la lista de hijos del padre del nodo dado hasta encontrar a este.
        while((tNodo)l_recuperar(hermanos,posInicial)!=n){
            posInicial=l_siguiente(hermanos,posInicial);
        }
        ///Guardo en una variable auxiliar la primera posicion y la posicion fin de la lista de hijos del nodo dado.
        tPosicion pHijoActual=l_primera(hijosNuevos);
        tPosicion pfinal=l_fin(hijosNuevos);
        ///Recorro la lista hasta que la variable que guarda la posicion actual sea igual a la posicion final de la lista de hijos del nodo dado.
        while(pHijoActual!=pfinal){
            tNodo hijoActual;
            ///Recupero el elemento de la posicion actual, siendo este un tNodo.
            hijoActual=(tNodo)l_recuperar(hijosNuevos,pHijoActual);
            ///Inserto en la lista de hijos del padre del nodo dado al elemento de la lista de hijos del nodo en la posicion que pertenecia al nodo dado.
            l_insertar(hermanos,posInicial,hijoActual);
            ///elimino de la lista del nodo dado la posicion actual sin eliminar su elemento.
            l_eliminar(hijosNuevos,pHijoActual,fnoElminar);
            ///Actualizo el padre del nodo actual.
            hijoActual->padre=padreNuevo;
            pHijoActual=l_siguiente(hijosNuevos,pHijoActual);
        }
        ///Elimino el nodo dado de la lista del padre del nodo dado.
        l_eliminar(hermanos,posInicial,fnoElminar);
        ///Elimino el elemento del nodo dado.
        fEliminar(n->elemento);
        ///Asigno al padre del nodo dado como null.
        n->padre=NULL;
        ///destruyo la lista de nodo dado sin eliminar los elementos de las posiciones.
        l_destruir(&(n->hijos),fnoElminar);
        n->elemento=NULL;
        ///Libero el espacio en memoria.
        free(n);
    }

}


void a_destruir(tArbol * a, void (*fEliminar)(tElemento)) {
    ///Guardo en una variable auxiliar la funcion para eliminar elementos.
    fEliminarUsuario = fEliminar;
    ///Guardo en una variable auxiliar la lista de hijos de la raiz del arbol dado.
    tLista hijos = (*a)->raiz->hijos;
    ///Destruyo la lista pasando como parametro las direcciones de memoria de la lista de hijos de la raiz del arbol dado y la funcion auxDestruir.
    l_destruir(&hijos, &auxDestruir);
    ///Elimino el elemento de la raiz del arbol dado.
    fEliminar((*a)->raiz->elemento);
    (*a)->raiz->elemento = NULL;
    ///Libero el espacio en memoria.
    free((*a)->raiz);
    (*a)->raiz = NULL;
    free((*a));
    a = NULL;
    fEliminarUsuario = NULL;

}
void auxDestruir(tElemento elemento){
    ///Guardo en una variable auxiliar el elemento dado y lo casteo.
    tNodo nodo_borrar = (tNodo) elemento;
    ///Destruyo la lista pasando como parametro la lista de hijos de la variable auxiliar previamente guardada y la funcion auxDestruir.
    l_destruir(&nodo_borrar->hijos, &auxDestruir);
    ///Elimino el elemento del nodo previamente guardado.
    fEliminarUsuario(nodo_borrar->elemento);
    ///Libero la memoria.
    nodo_borrar->elemento = NULL;
    nodo_borrar->padre = NULL;
    free(nodo_borrar);
}

tElemento a_recuperar(tArbol a, tNodo n)
{   ///Retorno el elemento del nodo dado.
    return n->elemento;
}

tNodo a_raiz(tArbol a)
{   ///Retorno la raiz del arbol dado.
    return a->raiz;
}

tLista a_hijos(tArbol a, tNodo n)
{   ///Retorno la lista de hijos del nodo dado.
    return n->hijos;
}
tPosicion buscarPosicion(tNodo n) {
    ///Guardo en una variable auxiliar a la lista de hijos del padre del nodo dado.
    tLista hijosPadre = n->padre->hijos;
    ///Guardo en una variable la primera posicion de la lista de hijos del padre del nodo dado.
    tPosicion cursor = l_primera(hijosPadre);
    ///Guardo en una variable la posicion fin de la lista de hijos del padre del nodo dado.
    tPosicion fin = l_fin(hijosPadre);
    ///Recorro la lista de hijos del padre del nodo dado hasta que la variable que guardaba la primera posicion sea la posicion fin.
    while (cursor != fin) {
        ///Guardo en una variable auxiliar el elemento de la posicion actual de la lista de hijos del padre del nodo dado.
        tNodo hijo = (tNodo) l_recuperar(hijosPadre, cursor);
        ///Si el elemento de la posicion actual es igual al nodo dado Retorno la posicion de la lista de hijos del padre del nodo dado.
        if (hijo == n) {
            return cursor;
        }
        ///Actualizo la posicion actual de la lista de hijos del padre del nodo dado.
        cursor = l_siguiente(hijosPadre, cursor);
    }
    ///Retorno null si el nodo no pertenece a la lista de hijos de su padre.
    return NULL;
}

void a_sub_arbol(tArbol a, tNodo n, tArbol* sa)
{
    ///Creo un arbol asignandolo al puntero a arbol dado.
    crear_arbol(sa);
    ///Creo la raiz con el nodo dado en el arbol creado.
    (*sa)->raiz=n;
    ///Si el padre del nodo dado es diferente a null.
    if(n->padre!=NULL){
        ///Guardo en una variable auxiliar a la lista del padre del nodo dado.
        tLista hermanosDeN=n->padre->hijos;
        ///Guardo en una variable auxiliar la posicion del nodo dado en la lista de su padre.
        tPosicion posDeN=buscarPosicion(n);
        ///Elimino una lista pasando por parametro a la lista de hijos del padre del nodo dado, la posicion del nodo dado en la lista de hijos de su padre y una funcion que no elimina elementos.
        l_eliminar(hermanosDeN,posDeN,fnoElminar);
        ///Asigno al padre del nodo dado NULL.
        n->padre=NULL;
    }
    else
        ///Si el padre del nodo dado es null-
        ///Asigno a la raiz del arbol a null.
        a->raiz=NULL;
}
