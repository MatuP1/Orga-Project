#include <stdlib.h>

#include "lista.h"
#include "arbol.h"
#include "ia.h"
#include "partida.h"

// Prototipos de funciones auxiliares.
void fElimBusq(void * est){
    free(est);
    est=NULL;
}
static void ejecutar_min_max(tBusquedaAdversaria b);
static void crear_sucesores_min_max(tArbol a, tNodo n, int es_max, int alpha, int beta, int jugador_max, int jugador_min);
static int valor_utilidad(tEstado e, int jugador_max);
static tLista estados_sucesores(tEstado e, int ficha_jugador);
static void diferencia_estados(tEstado anterior, tEstado nuevo, int * x, int * y);
static tEstado clonar_estado(tEstado e);
int gano(tEstado e, int ficha);




int minimax(tEstado estado,int esJugadorMax,int alpha,int beta){
    //Declaracion de variables.
    int mejorValorSucesores;
    int valorSucesor;
    tLista sucesores;
    tPosicion posActualSucesores;
    tPosicion finSucesores;
    tEstado elemento;
    int encontro = 0;

    ///Si es un estado final devuelve la utilidad.
    int val=valor_utilidad(estado,esJugadorMax);
    if(val==IA_GANA_MAX||val==IA_EMPATA_MAX||val==IA_PIERDE_MAX)
        return val;
    ///Si esJugadorMax !=0 significa que es un estado max.
    if(esJugadorMax){
        ///Inicializo las variables.
        //mejorValorSucesores = IA_INFINITO_NEG;
        mejorValorSucesores = alpha;
        sucesores = estados_sucesores(estado,esJugadorMax);
        posActualSucesores = l_primera(sucesores);
        finSucesores = l_fin(sucesores);
        ///Exploro la lista de estados hijos del estado actual.
        while(posActualSucesores!=finSucesores&&!encontro){
                ///Recupero el estado de la posicion de la lista de hijos.
                elemento = (tEstado) l_recuperar(sucesores,posActualSucesores);
                ///Accedo a una instancia recusiva con el estado hijo correspondiente a  la pos actual de la lista de hijos cambiando que ahora es un estado min.
                valorSucesor = minimax(elemento,0,alpha,beta);//Este esta bien.Creo, le paso 0 para que vaya al else.
                ///Si la utilidad del hijo es mayor a la anteriormente calculada la reemplazo por el nuevo valor.
                if(valorSucesor>mejorValorSucesores)
                    mejorValorSucesores= valorSucesor;
                ///Si alpha es menor al nuevo valor de utilidad actualizo el valor de alpha con el nuevo valor de utilidad.
                if(alpha<mejorValorSucesores)
                    alpha = mejorValorSucesores;
                ///Si beta es menor  o igual a alpha, podo.
                if(beta<=alpha){
                    encontro = 1;
                    return mejorValorSucesores;
                }
                ///Actualizo la posicion en la lista de hijos.
                posActualSucesores = l_siguiente(sucesores,posActualSucesores);

        }
    }
    ///Si esJugadorMax =0 significa que es un estado min.
    //esto lo tenes que hacer en crear sucesores
    else{
        ///Inicializo las variables.
        //mejorValorSucesores = IA_INFINITO_POS;
        mejorValorSucesores = beta;
        sucesores = estados_sucesores(estado,esJugadorMax);
        posActualSucesores = l_primera(sucesores);
        finSucesores = l_fin(sucesores);
        ///Exploro la lista de estados hijos del estado actual.
        while(posActualSucesores!=finSucesores&&!encontro){
                ///Recupero el estado de la posicion de la lista de hijos.
                elemento = (tEstado) l_recuperar(sucesores,posActualSucesores);
                ///Accedo a una instancia recusiva con el estado hijo correspondiente a  la pos actual de la lista de hijos cambiando que ahora es un estado max.
                valorSucesor = minimax(elemento,1,alpha,beta);//Este le paso para que en el sig vaya al if y no al else
                //tenes que usar crear sucesores
                ///Si la utilidad del hijo es menor a la anteriormente calculada la reemplazo por el nuevo valor.
                if(valorSucesor<mejorValorSucesores)
                    mejorValorSucesores = valorSucesor;
                ///Si beta es mayor al nuevo valor de utilidad actualizo el valor de alpha con el nuevo valor de utilidad.
                if(mejorValorSucesores<beta)
                    beta = mejorValorSucesores;
                ///Si beta es menor  o igual a alpha, podo.
                if(beta<=alpha){
                    encontro = 1;
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

    // Se clona el estado del tablero de la partida, al estado inicial de la búsqueda adversaria.
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            estado->grilla[i][j] = p->tablero->grilla[i][j];
        }
    }

	// Se asume que el estado de la partida es PART_EN_JUEGO por lo que, la utilidad del estado
	// inicialmente es IA_NO_TERMINO
    estado->utilidad = IA_NO_TERMINO;

    // Inicializa los valores que representarán a los jugadores MAX y MIN respectivamente.
    (*b)->jugador_max = p->turno_de;
    (*b)->jugador_min = (p->turno_de == PART_JUGADOR_1) ? PART_JUGADOR_2 : PART_JUGADOR_1;

    // Inicializa un árbol para la búsqueda adversaria inicialmente vacío.
    crear_arbol(&((*b)->arbol_busqueda));

    // Inicializa la raíz del árbol de búsqueda con el estado del tablero T.
    crear_raiz((*b)->arbol_busqueda, estado);

    // Ejecuta algoritmo Min-Max con podas Alpha-Beta.
    ejecutar_min_max((*b));
}

/**
>>>>>  A IMPLEMENTAR   <<<<<
*/
void proximo_movimiento(tBusquedaAdversaria b, int * x, int * y){
    ///Ejecuto la funcion ejecutar_min_max con el puntero a la estructura busqueda adversaria.
    ejecutar_min_max(b);
    ///Creo una variable auxiliar a un puntero a la estructura estado.
    tEstado mayorUtilidad;
    ///Guardo en una variable auxiliar la lista de hijos de la raiz del arbol encontrado en la estructura busqueda adversaria.
    tLista movimientos=a_hijos(b->arbol_busqueda,a_raiz(b->arbol_busqueda));
    ///Guardo en una variable auxiliar la primera posicion de la lista anteriormente guardada.
    tPosicion inicio=l_primera(movimientos);
    // tNodo movimientoActual=(tNodo)inicio->elemento;
    ///Guardo en una variable auxiliar el elemento del elemento anteriormente mencionado.
    tNodo nodoActual=(tNodo)inicio->elemento;
    tEstado estadoActual=nodoActual->elemento;
    ///Modifico el valor de la variable auxiliar a un puntero a la estructura estado con el elemento del elemento anteriormente mencionado.
    mayorUtilidad=(tEstado)estadoActual;
    ///Recorro la lista hasta que no tenga mas posiciones.
    for(int i=0;i<l_longitud(movimientos)-1;i++){ //me caigo de la lista??
        ///Si la utilidad de la estructura estado de mayorUtilidad es menor a la utilidad de la estructura estado del estado actual modifico mayorUtilidad con el puntero de estado actual.
        if(mayorUtilidad->utilidad<estadoActual->utilidad)
            mayorUtilidad=estadoActual;
        ///Avanzo en la lista a la siguiente posicion y actualizo los valores de las variables que guardaban datos de la anterior posicion.
        inicio=l_siguiente(movimientos,inicio);
        //movimientoActual=(tNodo)inicio->elemento;
        estadoActual=(tEstado)inicio->elemento;
    }
    ///Guardo en una variable auxiliar el elemento de la raiz de la estructura arbol de busqueda pasada por parametro.
    tEstado raiz=(tEstado)a_recuperar(b->arbol_busqueda,a_raiz(b->arbol_busqueda));
    ///Utilizo la funcion diferencia de estados con la variable auxiliar anteriormente guardada, la ultima mayorUtilidad conseguida en la lista y los punteros a enteros pasados por parametro.
    diferencia_estados(raiz,mayorUtilidad,x,y);
}

/**
>>>>>  A IMPLEMENTAR   <<<<<
**/
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
Ordena la ejecución del algoritmo Min-Max para la generación del árbol de búsqueda adversaria, considerando como
estado inicial el estado de la partida almacenado en el árbol almacenado en B.
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
>>>>>  A IMPLEMENTAR   <<<<<
Implementa la estrategia del algoritmo Min-Max con podas Alpha-Beta, a partir del estado almacenado en N.
- A referencia al árbol de búsqueda adversaria.
- N referencia al nodo a partir del cual se construye el subárbol de búsqueda adversaria.
- ES_MAX indica si N representa un nodo MAX en el árbol de búsqueda adversaria.
- ALPHA y BETA indican sendos valores correspondientes a los nodos ancestros a N en el árbol de búsqueda A.
- JUGADOR_MAX y JUGADOR_MIN indican las fichas con las que juegan los respectivos jugadores.
**/
static void crear_sucesores_min_max(tArbol a, tNodo n, int es_max, int alpha, int beta, int jugador_max, int jugador_min){
    ///Guardo en una variable auxiliar el elemento del nodo encontrado en el arbol y el nodo pasados por paramentro.
    tEstado prim= (tEstado)a_recuperar(a,n);
    ///Ejecuto la funcion minimax pasando por parametro el elemento del nodo anteriormente guardado,el entero que identifica al jugador y dos variables que identifican el valor de utilidad.
    minimax(prim,es_max,alpha,beta);

   /** if(es_max){
        es_max--;
        tEstado tab=(tEstado)n->elemento;
        tLista sucesores=a_hijos(a,n);
        sucesores=estados_sucesores(tab,jugador_max); //son estados min
        int inicio=0,fin=l_longitud(sucesores);
        tPosicion pActual=l_primera(sucesores);
        tNodo nActual;
        int sigo=1; //bandera
        int utilidad;
        while(inicio!=fin && sigo){
            nActual=l_recuperar(sucesores,pActual);
            utilidad=valor_utilidad(tab,jugador_max);
            if(utilidad==IA_NO_TERMINO) //la linea de abajo me hace ruido
                crear_sucesores_min_max(a,nActual,!es_max,alpha,beta,jugador_max,jugador_min);
            else
                if(utilidad>alpha)
                    alpha=utilidad;
            if(utilidad==IA_GANA_MAX)
                sigo=0;
            pActual=l_siguiente(sucesores,pActual);
            inicio++;
        }
    }
    else{}
        //similar al if preguntar si el algoritmo va encaminado*/
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
                if(e->grilla[i][j]==ficha1)
                    gano1++;
                if(e->grilla[i][j]==ficha2)
                    gano2++;
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
>>>>>  A IMPLEMENTAR   <<<<<
Computa el valor de utilidad correspondiente al estado E, y la ficha correspondiente al JUGADOR_MAX, retornado:
- IA_GANA_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX ganó la partida.
- IA_EMPATA_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX empató la partida.
- IA_PIERDE_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX perdió la partida.
- IA_NO_TERMINO en caso contrario.
**/
static int valor_utilidad(tEstado e, int jugador_max){
    ///Retorno el entero conseguido al ejecutar la funcion gano con el estado pasado por parametro y la variable que representa al jugador tambien pasada por parametro.
    return gano(e,jugador_max);
}

/**
>>>>>  A IMPLEMENTAR   <<<<<
Computa y retorna una lista con aquellos estados que representan estados sucesores al estado E.
Un estado sucesor corresponde a la clonación del estado E, junto con la incorporación de un nuevo movimiento
realizado por el jugador cuya ficha es FICHA_JUGADOR por sobre una posición que se encuentra libre en el estado E.
La lista de estados sucesores se debe ordenar de forma aleatoria, de forma tal que una doble invocación de la función
estados_sucesores(estado, ficha) retornaría dos listas L1 y L2 tal que:
- L1 y L2 tienen exactamente los mismos estados sucesores de ESTADO a partir de jugar FICHA.
- El orden de los estado en L1 posiblemente sea diferente al orden de los estados en L2.
**/
static tLista estados_sucesores(tEstado e, int ficha_jugador){
    ///Defino una estructura que guarda dos enteros.
    struct par{
        int x;
        int y;
    };
    ///Defino un puntero que apunta a la estructura anteriormente definida.
    typedef struct par * tPar;
    ///Creo una lista como variable auxiliar llamada sucesores,
    tLista sucesores;
    crear_lista(&sucesores);
    ///Guardo como variable auxiliar un arreglo de estructura anteriormente definida.
    tPar coorVacias[9];
    ///Guardo como una variable auxiliar un contador que cuenta las posiciones vacias de un tablero.
    int lugaresVacios=0;
    int i,j;
    ///Recorro la matriz encontrada en la estuctura estado pasada por parametro.
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            ///Si la posicion que se esta recorriendo esta vacia.
            if(e->grilla[i][j]==0){
                ///Guardo espacio en memoria y modifico las variables de la estructura par con las posiciones actuales que estoy recorriendo.
                coorVacias[lugaresVacios]=(tPar) malloc (sizeof(struct par));
                coorVacias[lugaresVacios]->x=i;
                coorVacias[lugaresVacios]->y=j;
                lugaresVacios++;
            }
        }
    }
    i=0;
    ///Guardo una variable auxiliar que hace referencia a un puntero de una estructura estado.
    tEstado aux;
    ///Mientras el contador sea menor a la cantidad de espacios vacios.
    while(i<lugaresVacios){
            ///Declaro dos variables auxiliares.
            int xAux,yAux;
            ///A las variables auxilares les asigno los valores encontrados en el arreglo previamente mencionado.
            xAux=coorVacias[i]->x;
            yAux=coorVacias[i]->y;
            ///Guardo espacio en memoria para una variable auxiliar.
           // aux=(tEstado) malloc (sizeof(struct estado));
            ///Clono el estado pasado por parametro en la variable auxiliar que hace referencia a un puntero de una estructura estado.
            aux=clonar_estado(e);
            ///A la posicion de la grilla del estado auxiliar le asigno la variable ficha_jugador que es pasada por parametro.
            aux->grilla[xAux][yAux]=ficha_jugador;
            ///A la utilidad de la variable auxiliar que hace referencia a un puntero de una estructura estado le asigno el resultado de la funcion valor_utilidad con parametros variable auxiliar que hace referencia a un puntero de una estructura estado y ficha_jugador que es pasada por parametro.
            aux->utilidad=valor_utilidad(aux,ficha_jugador);
            ///Declaro una variable y le asigno un numero aleatorio.
            int r=rand();
            ///Inserto en una posicion aleatoria a los hijos de la lista sucesores.
            if((r%lugaresVacios)%3==0)
                l_insertar(sucesores,l_primera(sucesores),aux);
            else{
                if((r%lugaresVacios)%3==1){
                    tPosicion p=l_primera(sucesores);
                    for(j=0;j<i;j++){
                        p=l_siguiente(sucesores,p);
                    }
                    l_insertar(sucesores,p,aux);
                }
                else
                    l_insertar(sucesores,l_ultima(sucesores),aux);
            }
            i++;
    }
    ///Retorono la lista de sucesores.
    return sucesores;
}

/**
>>>>>  A IMPLEMENTAR   <<<<<
Inicializa y retorna un nuevo estado que resulta de la clonación del estado E.
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
Se asume que entre ambos existe sólo una posición en el que la ficha del estado anterior y nuevo difiere.
La posición en la que los estados difiere, es retornada en los parámetros *X e *Y.
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
