#include <stdlib.h>
#include <stdio.h>
#include "lista.h"
#include "arbol.h"
#include "ia.h"
#include "partida.h"
#include <time.h>

// Prototipos de funciones auxiliares.
void fElimBusq(void * est){
    free(est);
    est=NULL;
}

void f_no_eliminar(void * nada){}

static void ejecutar_min_max(tBusquedaAdversaria b);
static void crear_sucesores_min_max(tArbol a, tNodo n, int es_max, int alpha, int beta, int jugador_max, int jugador_min);
static int valor_utilidad(tEstado e, int jugador_max);
static tLista estados_sucesores(tEstado e, int ficha_jugador);
static void diferencia_estados(tEstado anterior, tEstado nuevo, int * x, int * y);
static tEstado clonar_estado(tEstado e);
int gano(tEstado e, int ficha);


int minimax(tEstado estado,int esJugadorMax,int alpha,int beta,int jugador_max,int jug_min){
    //Declaracion de variables.
    int mejorValorSucesores;
    int valorSucesor;
    tLista sucesores;
    tPosicion posActualSucesores;
    tPosicion finSucesores;
    tEstado elemento;
    int encontro = 0;

    ///Si es un estado final devuelve la utilidad.
    int val=valor_utilidad(estado,jugador_max);
    if(val==IA_GANA_MAX||val==IA_EMPATA_MAX||val==IA_PIERDE_MAX){
        estado->utilidad = val;
        return val;
    }
    ///Si esJugadorMax !=0 significa que es un estado max.
    if(esJugadorMax){
        ///Inicializo las variables.
        mejorValorSucesores = IA_INFINITO_NEG;
        sucesores = estados_sucesores(estado,esJugadorMax);
        posActualSucesores = l_primera(sucesores);
        finSucesores = l_fin(sucesores);
        ///Exploro la lista de estados hijos del estado actual.
        while(posActualSucesores!=finSucesores&&!encontro){
                ///Recupero el estado de la posicion de la lista de hijos.
                elemento = (tEstado) l_recuperar(sucesores,posActualSucesores);
                ///Accedo a una instancia recusiva con el estado hijo correspondiente a  la pos actual de la lista de hijos cambiando que ahora es un estado min.
                valorSucesor = minimax(elemento,0,alpha,beta,jugador_max,jug_min);//Este esta bien.Creo, le paso 0 para que vaya al else.
                ///Si la utilidad del hijo es mayor a la anteriormente calculada la reemplazo por el nuevo valor.
                if(valorSucesor>mejorValorSucesores)
                    mejorValorSucesores= valorSucesor;
                ///Si alpha es menor al nuevo valor de utilidad actualizo el valor de alpha con el nuevo valor de utilidad.
                if(alpha<mejorValorSucesores)
                    alpha = mejorValorSucesores;
                ///Si beta es menor  o igual a alpha, podo.
                if(beta<=alpha){
                    encontro = 1;
                    estado->utilidad = mejorValorSucesores;
                    return mejorValorSucesores;
                }
                ///Actualizo la posicion en la lista de hijos.
                posActualSucesores = l_siguiente(sucesores,posActualSucesores);

        }
    }
    ///Si esJugadorMax =0 significa que es un estado min.
    else{
        ///Inicializo las variables.
        mejorValorSucesores = IA_INFINITO_POS;
        sucesores = estados_sucesores(estado,esJugadorMax);
        posActualSucesores = l_primera(sucesores);
        finSucesores = l_fin(sucesores);
        ///Exploro la lista de estados hijos del estado actual.
        while(posActualSucesores!=finSucesores&&!encontro){
                ///Recupero el estado de la posicion de la lista de hijos.
                elemento = (tEstado) l_recuperar(sucesores,posActualSucesores);
                ///Accedo a una instancia recusiva con el estado hijo correspondiente a  la pos actual de la lista de hijos cambiando que ahora es un estado max.
                valorSucesor = minimax(elemento,1,alpha,beta,jugador_max,jug_min);//Este le paso para que en el sig vaya al if y no al else
                ///Si la utilidad del hijo es menor a la anteriormente calculada la reemplazo por el nuevo valor.
                if(valorSucesor<mejorValorSucesores)
                    mejorValorSucesores = valorSucesor;
                ///Si beta es mayor al nuevo valor de utilidad actualizo el valor de alpha con el nuevo valor de utilidad.
                if(mejorValorSucesores<beta)
                    beta = mejorValorSucesores;
                ///Si beta es menor  o igual a alpha, podo.
                if(beta<=alpha){
                    encontro = 1;
                    estado->utilidad = mejorValorSucesores;
                    return mejorValorSucesores;
                }
                ///Actualizo la posicion en la lista de hijos.
                posActualSucesores = l_siguiente(sucesores,posActualSucesores);
        }
    }

    return 0;
}

void crear_busqueda_adversaria(tBusquedaAdversaria * b, tPartida p){
    int i, j;
    tEstado estado;
    (*b) = (tBusquedaAdversaria) malloc(sizeof(struct busqueda_adversaria));
    if ((*b) == NULL) exit(IA_ERROR_MEMORIA);

    estado = (tEstado) malloc(sizeof(struct estado));
    if (estado == NULL) exit(IA_ERROR_MEMORIA);

    // Se clona el estado del tablero de la partida, al estado inicial de la b�squeda adversaria.
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            estado->grilla[i][j] = p->tablero->grilla[i][j];
        }
    }

	// Se asume que el estado de la partida es PART_EN_JUEGO por lo que, la utilidad del estado
	// inicialmente es IA_NO_TERMINO
    estado->utilidad = IA_NO_TERMINO;

    // Inicializa los valores que representar�n a los jugadores MAX y MIN respectivamente.
    (*b)->jugador_max = p->turno_de;
    (*b)->jugador_min = (p->turno_de == PART_JUGADOR_1) ? PART_JUGADOR_2 : PART_JUGADOR_1;

    // Inicializa un �rbol para la b�squeda adversaria inicialmente vac�o.
    crear_arbol(&((*b)->arbol_busqueda));

    // Inicializa la ra�z del �rbol de b�squeda con el estado del tablero T.
    crear_raiz((*b)->arbol_busqueda, estado);

    // Ejecuta algoritmo Min-Max con podas Alpha-Beta.
    ejecutar_min_max((*b));
}

void proximo_movimiento(tBusquedaAdversaria b, int * x, int * y){
        tNodo raiz = a_raiz(b->arbol_busqueda);
        tEstado estado_actual = (tEstado) a_recuperar(b->arbol_busqueda, raiz);
        tLista sucesores = a_hijos(b->arbol_busqueda, raiz);
        int mejor_valor = IA_INFINITO_NEG;
        int nuevo_valor;
        tNodo mejor_sucesor = NULL;
        tPosicion fin = l_fin(sucesores);
        tPosicion cursor = l_primera(sucesores);
        tNodo hijoActual =l_recuperar(sucesores,l_primera(sucesores));
        tEstado estadoHijo= (tEstado) a_recuperar(b->arbol_busqueda,hijoActual);
        nuevo_valor=estadoHijo->utilidad;
        while(cursor != fin){
            hijoActual=l_recuperar(sucesores,cursor);
            estadoHijo=a_recuperar(b->arbol_busqueda,hijoActual);
            nuevo_valor = estadoHijo->utilidad;
            if(mejor_valor < nuevo_valor){
                mejor_sucesor = l_recuperar(sucesores, cursor);
                mejor_valor = nuevo_valor;
            }
            cursor = l_siguiente(sucesores, cursor);
        }
        diferencia_estados(estado_actual, (tEstado) a_recuperar(b->arbol_busqueda, mejor_sucesor), x, y);

}

void destruir_busqueda_adversaria(tBusquedaAdversaria * b){
    ///Destruyo el arbol encontrado dentro de la estructura busqueda adversaria pasada por paramtero.
    a_destruir(&(*b)->arbol_busqueda,fElimBusq);
    ///Libero el espacio en memoria ocupado por la estructura busqueda adversaria pasada por parametro.
    free(*b);
    *b=NULL;
    free(b);
    b=NULL;
}

// ===============================================================================================================
// FUNCIONES Y PROCEDEMIENTOS AUXILIARES
// ===============================================================================================================

/**
Ordena la ejecuci�n del algoritmo Min-Max para la generaci�n del �rbol de b�squeda adversaria, considerando como
estado inicial el estado de la partida almacenado en el �rbol almacenado en B.
**/
static void ejecutar_min_max(tBusquedaAdversaria b){
    ///Guardo en una variable auxiliar el arbol encontrado en la estructura busqueda adversaria pasada por paramtero.
    tArbol a = b->arbol_busqueda;
    ///Guardo en una variable auxiliar la raiz de la variable arbol anteriormente guardada.
    tNodo r = a_raiz(a);
    ///Guardo en variables auxilares los enteros que identifican a jugadores encontrados en la estructura busqueda adversaria pasada por parametro.
    int jugador_max = b->jugador_max;
    int jugador_min = b->jugador_min;
    ///Utilizo la funcion crear_sucesores_min_max con los parametro del arbol anteriormente guardado, su raiz, un entero numeros infinitos y las variables que identifican jugadores anteriormente guardadas.
    crear_sucesores_min_max(a, r, 1, IA_INFINITO_NEG, IA_INFINITO_POS, jugador_max, jugador_min);
}

/**
Implementa la estrategia del algoritmo Min-Max con podas Alpha-Beta, a partir del estado almacenado en N.
- A referencia al �rbol de b�squeda adversaria.
- N referencia al nodo a partir del cual se construye el sub�rbol de b�squeda adversaria.
- ES_MAX indica si N representa un nodo MAX en el �rbol de b�squeda adversaria.
- ALPHA y BETA indican sendos valores correspondientes a los nodos ancestros a N en el �rbol de b�squeda A.
- JUGADOR_MAX y JUGADOR_MIN indican las fichas con las que juegan los respectivos jugadores.
**/
static void crear_sucesores_min_max(tArbol a, tNodo n, int es_max, int alpha, int beta, int jugador_max, int jugador_min){
    ///Guardo en una variable auxiliar el elemento del nodo encontrado en el arbol y el nodo pasados por paramentro.
    ///Ejecuto la funcion minimax pasando por parametro el elemento del nodo anteriormente guardado,el entero que identifica al jugador y dos variables que identifican el valor de utilidad.
   //Declaracion de variables.
    tEstado estado=n->elemento;
    tLista sucesores;
    tPosicion posActualSucesores;
    tPosicion finSucesores;
    tEstado sucesorAct;
    int encontro = 0;

    ///Si es un estado final devuelve la utilidad.
    estado->utilidad=valor_utilidad(estado,jugador_max);
    if(estado->utilidad==IA_NO_TERMINO){
        ///Si esJugadorMax !=0 significa que es un estado max.
        if(es_max){
            ///Inicializo las variables.
            sucesores = estados_sucesores(estado,jugador_max);
            posActualSucesores = l_primera(sucesores);
            finSucesores = l_fin(sucesores);
            ///Exploro la lista de estados hijos del estado actual.
            while(posActualSucesores!=finSucesores&&!encontro){
                    ///Recupero el estado de la posicion de la lista de hijos.
                    sucesorAct = (tEstado) l_recuperar(sucesores,posActualSucesores);
                    ///Accedo a una instancia recusiva con el estado hijo correspondiente a  la pos actual de la lista de hijos cambiando que ahora es un estado min.
                    sucesorAct->utilidad=valor_utilidad(sucesorAct,jugador_max);
                    tNodo hijoActual = a_insertar(a,n,NULL,sucesorAct);
                    crear_sucesores_min_max(a,hijoActual,0,alpha,beta,jugador_max,jugador_min);//Este esta bien.Creo, le paso 0 para que vaya al else.
                    ///Si la utilidad del hijo es mayor a la anteriormente calculada la reemplazo por el nuevo valor.
                    tEstado estadoSucesor = hijoActual->elemento;
                    //if(estadoSucesor->utilidad<mejorValorSucesores)
                    //    mejorValorSucesores= caca->utilidad;
                    ///Si alpha es menor al nuevo valor de utilidad actualizo el valor de alpha con el nuevo valor de utilidad.
                    if(alpha<estadoSucesor->utilidad)
                        alpha = estadoSucesor->utilidad;
                    ///Si beta es menor  o igual a alpha, podo.
                    if(beta<=alpha){
                        encontro = 1;
                    }
                    ///Actualizo la posicion en la lista de hijos.
                    posActualSucesores = l_siguiente(sucesores,posActualSucesores);
            }
            estado->utilidad = alpha;
        }
        ///Si esJugadorMax =0 significa que es un estado min.
        else{
            ///Inicializo las variables.
            sucesores = estados_sucesores(estado,jugador_min);
            posActualSucesores = l_primera(sucesores);
            finSucesores = l_fin(sucesores);
            ///Exploro la lista de estados hijos del estado actual.
            while(posActualSucesores!=finSucesores&&!encontro){
                    ///Recupero el estado de la posicion de la lista de hijos.
                    sucesorAct = (tEstado) l_recuperar(sucesores,posActualSucesores);
                    ///Accedo a una instancia recusiva con el estado hijo correspondiente a  la pos actual de la lista de hijos cambiando que ahora es un estado max.
                    tNodo hijoActual =a_insertar(a,n,NULL,sucesorAct);
                    sucesorAct->utilidad=valor_utilidad(sucesorAct,jugador_max);
                    crear_sucesores_min_max(a,hijoActual,1,alpha,beta,jugador_max,jugador_min);//Este le paso para que en el sig vaya al if y no al else
                    ///Si la utilidad del hijo es menor a la anteriormente calculada la reemplazo por el nuevo valor.
                    tEstado estadoSucesor=hijoActual->elemento;
                    ///Si beta es mayor al nuevo valor de utilidad actualizo el valor de alpha con el nuevo valor de utilidad.
                    if(estadoSucesor->utilidad<beta)
                        beta = estadoSucesor->utilidad;
                    ///Si beta es menor  o igual a alpha, podo.
                    if(beta<=alpha){
                        encontro = 1;
                    }
                    ///Actualizo la posicion en la lista de hijos.
                    posActualSucesores = l_siguiente(sucesores,posActualSucesores);
            }
            estado->utilidad = beta;
        }
    l_destruir(&sucesores,f_no_eliminar);
    }
}

int gano(tEstado e, int ficha){
    int gano1=0;
    int gano2=0;

    int ficha1=ficha;
    int ficha2=0;

    int espaciosVacios=0;
    int i=0;

    if(ficha==PART_JUGADOR_1)
        ficha2=PART_JUGADOR_2;
    else{
        ficha2=PART_JUGADOR_1;
    }
        ///Chequeo las filas.
        while(gano1!=3 && gano2!=3 && i<3){
            for(int j=0; j<3; j++){
                if(e->grilla[i][j]==ficha1){
                    gano1++;
                }
                if(e->grilla[i][j]==ficha2){
                    gano2++;
                }
                if(e->grilla[i][j]==0){
                    espaciosVacios++;
                }
            }
            if(gano1>=3)
                return IA_GANA_MAX;
            if(gano2>=3)
                return IA_PIERDE_MAX;
            gano2=0;
            gano1=0;
            i++;
        }
        printf("el  valor de juagodr 1= %i\n",ficha1);
        printf("el  valor de juagodr 2= %i\n",ficha2);
        printf("el  valor de lugares vacios= %i\n",espaciosVacios);

        int j=0;
        ///Chequeo las columnas.
        while(gano1!=3 && gano2!=3 && j<3){
            for(i=0; i<3; i++){
                if(e->grilla[i][j]==ficha1)
                    gano1++;
                if(e->grilla[i][j]==ficha2)
                    gano2++;
                if(e->grilla[i][j]==0)
                    espaciosVacios++;
                }
            if(gano1>=3)
                return IA_GANA_MAX;
            if(gano2>=3)
                return IA_PIERDE_MAX;
            gano1=0;
            gano2=0;
            j++;
        }
        //diagonal hardcodeada x2
        i=0; j=0;
        while(j<2 && i<2){
            if(e->grilla[i][j]==ficha1)
                gano1++;
            if(e->grilla[i][j]==ficha2)
                gano2++;
            if(e->grilla[i][j]==0)
                espaciosVacios++;
            i++;
            j++;
        }
        if(gano1>=3)
            return IA_GANA_MAX; //gano1
        if(gano2>=3)
            return IA_PIERDE_MAX;

        gano1=0;
        gano2=0;
        i=-1;
        j=3;
        while(j>0 && i<3){
            j--;
            i++;
            if(e->grilla[i][j]==ficha1)
                gano1++;
            if(e->grilla[i][j]==ficha2)
                gano2++;
            if(e->grilla[i][j]==0)
                espaciosVacios++;
        }
        if(gano1>=3)
            return IA_GANA_MAX; //gano1
        if(gano2>=3)
            return IA_PIERDE_MAX;
        if(espaciosVacios==0)
            return IA_EMPATA_MAX;
    return IA_NO_TERMINO;
}
/**
Computa el valor de utilidad correspondiente al estado E, y la ficha correspondiente al JUGADOR_MAX, retornado:
- IA_GANA_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX gan� la partida.
- IA_EMPATA_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX empat� la partida.
- IA_PIERDE_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX perdi� la partida.
- IA_NO_TERMINO en caso contrario.
**/
static int valor_utilidad(tEstado e, int jugador_max){
    ///Retorno el entero conseguido al ejecutar la funcion gano con el estado pasado por parametro y la variable que representa al jugador tambien pasada por parametro.
    int gano1=0;
    int gano2=0;

    int ficha1=jugador_max;
    int ficha2=0;

    int espaciosVacios=0;
    int i=0;

    if(jugador_max==PART_JUGADOR_1)
        ficha2=PART_JUGADOR_2;
    else{
        ficha2=PART_JUGADOR_1;
    }
        ///Chequeo las filas.
        while(gano1!=3 && gano2!=3 && i<3){
            for(int j=0; j<3; j++){
                if(e->grilla[i][j]==ficha1){
                    gano1++;
                }
                if(e->grilla[i][j]==ficha2){
                    gano2++;
                }
                if(e->grilla[i][j]==PART_SIN_MOVIMIENTO){
                    espaciosVacios++;
                }
            }
            if(gano1>=3)
                return IA_GANA_MAX;
            if(gano2>=3)
                return IA_PIERDE_MAX;
            gano2=0;
            gano1=0;
            i++;
        }

        int j=0;
        ///Chequeo las columnas.
        while(gano1!=3 && gano2!=3 && j<3){
            for(i=0; i<3; i++){
                if(e->grilla[i][j]==ficha1)
                    gano1++;
                if(e->grilla[i][j]==ficha2)
                    gano2++;
                if(e->grilla[i][j]==PART_SIN_MOVIMIENTO)
                    espaciosVacios++;
                }
            if(gano1>=3)
                return IA_GANA_MAX;
            if(gano2>=3)
                return IA_PIERDE_MAX;
            gano1=0;
            gano2=0;
            j++;
        }
        //diagonal hardcodeada x2
        i=0; j=0;
        while(j<3 && i<3){
            if(e->grilla[i][j]==ficha1)
                gano1++;
            if(e->grilla[i][j]==ficha2)
                gano2++;
            if(e->grilla[i][j]==PART_SIN_MOVIMIENTO)
                espaciosVacios++;
            i++;
            j++;
        }
        if(gano1>=3)
            return IA_GANA_MAX; //gano1
        if(gano2>=3)
            return IA_PIERDE_MAX;

        gano1=0;
        gano2=0;
        i=-1;
        j=3;
        while(j>0 && i<3){
            j--;
            i++;
            if(e->grilla[i][j]==ficha1)
                gano1++;
            if(e->grilla[i][j]==ficha2)
                gano2++;
            if(e->grilla[i][j]==PART_SIN_MOVIMIENTO)
                espaciosVacios++;
        }
        if(gano1>=3)
            return IA_GANA_MAX; //gano1
        if(gano2>=3)
            return IA_PIERDE_MAX;
        if(espaciosVacios==0)
            return IA_EMPATA_MAX;
    return IA_NO_TERMINO;
}

/**
Computa y retorna una lista con aquellos estados que representan estados sucesores al estado E.
Un estado sucesor corresponde a la clonaci�n del estado E, junto con la incorporaci�n de un nuevo movimiento
realizado por el jugador cuya ficha es FICHA_JUGADOR por sobre una posici�n que se encuentra libre en el estado E.
La lista de estados sucesores se debe ordenar de forma aleatoria, de forma tal que una doble invocaci�n de la funci�n
estados_sucesores(estado, ficha) retornar�a dos listas L1 y L2 tal que:
- L1 y L2 tienen exactamente los mismos estados sucesores de ESTADO a partir de jugar FICHA.
- El orden de los estado en L1 posiblemente sea diferente al orden de los estados en L2.
**/
static tLista estados_sucesores(tEstado e, int ficha_jugador){

    ///Creo una lista como variable auxiliar llamada sucesores,
    tLista sucesores;
    crear_lista(&sucesores);

    ///Guardo una variable auxiliar que hace referencia a un puntero de una estructura estado.
    tEstado aux;

    int i,j;
    ///Recorro la matriz encontrada en la estuctura estado pasada por parametro.
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            ///Si la posicion que se esta recorriendo esta vacia.
            if(e->grilla[i][j]==PART_SIN_MOVIMIENTO){
                ///Clono el estado pasado por parametro en la variable auxiliar que hace referencia a un puntero de una estructura estado.
                aux=clonar_estado(e);
                ///A la posicion de la grilla del estado auxiliar le asigno la variable ficha_jugador que es pasada por parametro.
                aux->grilla[i][j]=ficha_jugador;
                ///Declaro una variable y le asigno un numero aleatorio.
                int r=rand();
                ///Inserto en una posicion aleatoria a los hijos de la lista sucesores.
                if((r%2)==0){
                    l_insertar(sucesores,l_primera(sucesores),aux);
                   }
                else{
                    l_insertar(sucesores,l_ultima(sucesores),aux);
                }
            }
        }
    }
    ///Retorono la lista de sucesores.
    return sucesores;
}

/**
Inicializa y retorna un nuevo estado que resulta de la clonaci�n del estado E.
Para esto copia en el estado a retornar los valores actuales de la grilla del estado E, como su valor
de utilidad.
**/
static tEstado clonar_estado(tEstado e){
    ///Guardo espacio en memoria a una variable auxiliar definida en la misma linea.
    tEstado ret=(tEstado) malloc (sizeof(struct estado));
    ///Si la variable anteriormente definida es nula es un error.
    if(ret==NULL)
        exit(IA_ERROR_MEMORIA);
    ///Copio la grilla.
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            ret->grilla[i][j]=e->grilla[i][j];
        }
    }
    ///A la utilidad de la variable anteriormente definida le asigno la utilidad de la estructura estado pasada por parametro.
    ret->utilidad=e->utilidad;
    ///Retorno la variable anteriormente definida.
    return ret;
}

/**
Computa la diferencia existente entre dos estados.
Se asume que entre ambos existe s�lo una posici�n en el que la ficha del estado anterior y nuevo difiere.
La posici�n en la que los estados difiere, es retornada en los par�metros *X e *Y.
**/
static void diferencia_estados(tEstado anterior, tEstado nuevo, int * x, int * y){
    ///Declaro 3 variables enteras auxiliares.
    int i,j, hallado = 0;
    ///Recorro la grillas de las matrices encontradas en las estructuras estado pasadas por parametro hasta que se terminen o hasta que halle la posicion diferente entre dos estructuras estado.
    for(i=0; i<3 && !hallado; i++){
        for(j=0; j<3 && !hallado; j++){
            ///Si encuentro la posicion que difiere actualizo los puntero a enteros pasados por parametro e indico que halle la diferencia.
            if (anterior->grilla[i][j] != nuevo->grilla[i][j]){
                *x = i;
                *y = j;
                hallado = 1;
            }
        }
    }
}
