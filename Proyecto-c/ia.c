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
    int  resultadoEstado = gano(estado,esJugadorMax);
    tLista sucesores;
    tPosicion posActualSucesores;
    tPosicion finSucesores;
    tEstado elemento;
    int encontro = 0;


    if(resultadoEstado==IA_GANA_MAX||resultadoEstado==IA_EMPATA_MAX||resultadoEstado==IA_PIERDE_MAX)
        return valor_utilidad(estado,esJugadorMax);

    if(esJugadorMax){
        mejorValorSucesores = IA_INFINITO_NEG;
        sucesores = estados_sucesores(estado,esJugadorMax);
        posActualSucesores = l_primera(sucesores);
        finSucesores = l_fin(sucesores);

        while(posActualSucesores!=finSucesores&&!encontro){
                elemento = (tEstado) l_recuperar(sucesores,posActualSucesores);
                valorSucesor = minimax(elemento,0,alpha,beta);//Este esta bien.Creo, le paso 0 para que vaya al else.

                if(valorSucesor>mejorValorSucesores)
                    mejorValorSucesores= valorSucesor;

                if(alpha<mejorValorSucesores)
                    alpha = mejorValorSucesores;

                if(beta<=alpha){
                    encontro = 1;
                    return mejorValorSucesores;
                }

                posActualSucesores = l_siguiente(sucesores,posActualSucesores);

        }
    }
    else{
        mejorValorSucesores = IA_INFINITO_POS;
        sucesores = estados_sucesores(estado,esJugadorMax);
        posActualSucesores = l_primera(sucesores);
        finSucesores = l_fin(sucesores);

        while(posActualSucesores!=finSucesores&&!encontro){
                elemento = (tEstado) l_recuperar(sucesores,posActualSucesores);
                valorSucesor = minimax(elemento,1,alpha,beta);//Este le paso para que en el sig vaya al if y no al else

                if(valorSucesor<mejorValorSucesores)
                    mejorValorSucesores = valorSucesor;

                if(mejorValorSucesores<beta)
                    beta = mejorValorSucesores;

                if(beta<=alpha){
                    encontro = 1;
                    return mejorValorSucesores;
                }

                posActualSucesores = l_siguiente(sucesores,posActualSucesores);

        }
    }

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

/**
>>>>>  A IMPLEMENTAR   <<<<<
*/
void proximo_movimiento(tBusquedaAdversaria b, int * x, int * y){
    ejecutar_min_max(b);
    tEstado mayorUtilidad;
    tLista movimientos=a_hijos(b->arbol_busqueda,a_raiz(b->arbol_busqueda));
    tPosicion inicio=l_primera(movimientos);
    tNodo movimientoActual=(tNodo)inicio->elemento;
    tEstado estadoActual=(tEstado)movimientoActual->elemento;
    mayorUtilidad=estadoActual;
    for(int i=0;i<l_longitud(movimientos-1);i++){ //me caigo de la lista??
        if(mayorUtilidad->utilidad<estadoActual->utilidad)
            mayorUtilidad=estadoActual;
        inicio=l_siguiente(movimientos,inicio);
        movimientoActual=(tNodo)inicio->elemento;
        estadoActual=(tEstado)movimientoActual->elemento;
    }
    tEstado raiz=(tEstado)a_recuperar(b->arbol_busqueda,a_raiz(b->arbol_busqueda));
    diferencia_estados(raiz,mayorUtilidad,x,y);
}

/**
>>>>>  A IMPLEMENTAR   <<<<<
**/
void destruir_busqueda_adversaria(tBusquedaAdversaria * b){
    a_destruir(&(*b)->arbol_busqueda,fElimBusq);
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
    tArbol a = b->arbol_busqueda;
    tNodo r = a_raiz(a);
    int jugador_max = b->jugador_max;
    int jugador_min = b->jugador_min;

    crear_sucesores_min_max(a, r, 1, IA_INFINITO_NEG, IA_INFINITO_POS, jugador_max, jugador_min);
}

/**
>>>>>  A IMPLEMENTAR   <<<<<
Implementa la estrategia del algoritmo Min-Max con podas Alpha-Beta, a partir del estado almacenado en N.
- A referencia al �rbol de b�squeda adversaria.
- N referencia al nodo a partir del cual se construye el sub�rbol de b�squeda adversaria.
- ES_MAX indica si N representa un nodo MAX en el �rbol de b�squeda adversaria.
- ALPHA y BETA indican sendos valores correspondientes a los nodos ancestros a N en el �rbol de b�squeda A.
- JUGADOR_MAX y JUGADOR_MIN indican las fichas con las que juegan los respectivos jugadores.
**/
static void crear_sucesores_min_max(tArbol a, tNodo n, int es_max, int alpha, int beta, int jugador_max, int jugador_min){
    if(es_max){
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
        //similar al if preguntar si el algoritmo va encaminado
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
        while(gano1!=3 || gano2!=3 || i<3){
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
        while(gano1!=3 || gano2!=3 || j<3){
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
        while(j<3 && i<3){
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

        while(j>0 && i<3){
            j--;
            i--;
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
- IA_GANA_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX gan� la partida.
- IA_EMPATA_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX empat� la partida.
- IA_PIERDE_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX perdi� la partida.
- IA_NO_TERMINO en caso contrario.
**/
static int valor_utilidad(tEstado e, int jugador_max){
    return gano(e,jugador_max);
}

/**
>>>>>  A IMPLEMENTAR   <<<<<
Computa y retorna una lista con aquellos estados que representan estados sucesores al estado E.
Un estado sucesor corresponde a la clonaci�n del estado E, junto con la incorporaci�n de un nuevo movimiento
realizado por el jugador cuya ficha es FICHA_JUGADOR por sobre una posici�n que se encuentra libre en el estado E.
La lista de estados sucesores se debe ordenar de forma aleatoria, de forma tal que una doble invocaci�n de la funci�n
estados_sucesores(estado, ficha) retornar�a dos listas L1 y L2 tal que:
- L1 y L2 tienen exactamente los mismos estados sucesores de ESTADO a partir de jugar FICHA.
- El orden de los estado en L1 posiblemente sea diferente al orden de los estados en L2.
**/
static tLista estados_sucesores(tEstado e, int ficha_jugador){
    struct par{
        int x;
        int y;
    };
    typedef struct par * tPar;
    tLista sucesores;
    crear_lista(&sucesores);
    tPar coorVacias[9];
    int lugaresVacios=0;
    int i,j;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if(e->grilla[i][j]==0){
                coorVacias[lugaresVacios]=(tPar) malloc (sizeof(struct par));
                coorVacias[lugaresVacios]->x=i;
                coorVacias[lugaresVacios]->y=j;
                lugaresVacios++;
            }
        }
    }
    i=0;
    tEstado aux;
    while(i<lugaresVacios){
            int xAux,yAux;
            xAux=coorVacias[i]->x;
            yAux=coorVacias[i]->y;
            aux=(tEstado) malloc (sizeof(struct estado));
            aux=clonar_estado(e);
            aux->grilla[xAux][yAux]=ficha_jugador;
            aux->utilidad=valor_utilidad(aux,ficha_jugador);
            int r=rand();
            //insercion random
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
                    l_insertar(sucesores,NULL,aux);
            }
            i++;
    }
    return sucesores;
}

/**
>>>>>  A IMPLEMENTAR   <<<<<
Inicializa y retorna un nuevo estado que resulta de la clonaci�n del estado E.
Para esto copia en el estado a retornar los valores actuales de la grilla del estado E, como su valor
de utilidad.
**/
static tEstado clonar_estado(tEstado e){
    tEstado ret=(tEstado) malloc (sizeof(struct estado));
    if(ret==NULL)
        exit(IA_ERROR_MEMORIA);
    //copio la grilla
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            ret->grilla[i][j]=e->grilla[i][j];
        }
    }
    ret->utilidad=e->utilidad;
    return ret;
}

/**
Computa la diferencia existente entre dos estados.
Se asume que entre ambos existe s�lo una posici�n en el que la ficha del estado anterior y nuevo difiere.
La posici�n en la que los estados difiere, es retornada en los par�metros *X e *Y.
**/
static void diferencia_estados(tEstado anterior, tEstado nuevo, int * x, int * y){
    int i,j, hallado = 0;
    for(i=0; i<3 && !hallado; i++){
        for(j=0; j<3 && !hallado; j++){
            if (anterior->grilla[i][j] != nuevo->grilla[i][j]){
                *x = i;
                *y = j;
                hallado = 1;
            }
        }
    }
}
