#include "partida.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"
void nueva_partida(tPartida * p, int modo_partida, int comienza, char * j1_nombre, char * j2_nombre){
    ///guardo memoria para la partida
    *p=(tPartida) malloc (sizeof(struct partida));
    if((*p)==NULL)
        exit(PART_ERROR_MEMORIA);

    ///seteo modo y turno
    (*p)->modo_partida=modo_partida;
    (*p)->turno_de=comienza;
    (*p)->estado=PART_EN_JUEGO;
    ///asigno turno al azar
    if(comienza==PART_JUGADOR_RANDOM){
        srand(time(NULL));
        if(rand() % 2 == 0)
            (*p)->turno_de=PART_JUGADOR_1;
        else
            (*p)->turno_de=PART_JUGADOR_2;
    }

    ///seteo nombres sin chequeo
    char guarda='\0';
    int i = 0;
    while(j1_nombre[i]!=guarda){
        (*p)->nombre_jugador_1[i]=j1_nombre[i];
        i++;
    }
    i = 0;
    while(j2_nombre[i]!=guarda){
        (*p)->nombre_jugador_2[i]=j2_nombre[i];
        i++;
    }

    ///inicializo el tablero con PART_SIN_MOVIMIENTO
    (*p)->tablero=(tTablero) malloc (sizeof(struct tablero));
    if((*p)->tablero == NULL)
        exit(PART_ERROR_MEMORIA);
    for(int i=0; i<=2; i++){
        for(int j=0; j<=2; j++){
            (*p)->tablero->grilla[i][j]=PART_SIN_MOVIMIENTO;
        }
    }
}

/**
    funcion que devuelve 1 si la ficha enviada gano y 0 si no
*/
int ganoP(tTablero t, int ficha){
    int gano=0;
    int i=0;
    ///chequeo filas y veo si gane
    while(gano!=3 && i<3){
        for(int j=0; j<3; j++){
            if(t->grilla[i][j]==ficha)
                gano++;
            }
        ///si no encontre 3 seguidos reinicio
        if(gano<3){
            gano=0;
        }
        i++;
    }
    ///si encontre la misma ficha 3 veces en una fila gane
    if(gano>=3)
        return 1;
    else
        gano=0;

    ///chequeo columnas y veo si gane
    int j=0;
    while(gano!=3 && j<3){
        for(int i=0; i<3; i++){
            if(t->grilla[i][j]==ficha)
                gano++;
            }
        ///si no encontre 3 seguidos reinicio
        if(gano<3)
            gano=0;
        j++;
    }
    ///si encontre la misma ficha 3 veces en una fila gane
    if(gano>=3)
        return 1; //gano
    else
        gano=0;
    ///chequeo las diagonales
    i=0; j=0;
    while(j<3 && i<3){
        ///si encuentro la ficha aumento gano
        if(t->grilla[i][j]==ficha)
            gano++;
        else{
            j=2;
            i=2;
        }
        i++;
        j++;
    }
    ///si encontre la misma ficha 3 veces en una fila gane
    if(gano>=3)
        return 1; //gano
    else
        gano=0;
    i=-1;
    j=3;

    while(j>0 && i<3){
        j--;
        i++;
        /// si encuentro la ficha aumento gano
        if(t->grilla[i][j]==ficha)
            gano++;
        else{
            j=0;
            i=0;
        }
    }
    ///si encontre la misma ficha 3 veces en una fila gane
    if(gano>=3)
        return 1; //gano
    else
        return gano=0;

}

int nuevo_movimiento(tPartida p, int mov_x, int mov_y){
    tTablero t=p->tablero;
    int lleno=0;
    ///incializo el tablero vacio
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(t->grilla[i][j]!=PART_SIN_MOVIMIENTO)
                lleno++;
        }
    }
    ///si la posicion es fuera de la grilla ERROR
    if(mov_x > 2 || mov_y > 2 || mov_x < 0 || mov_y < 0)
        exit(PART_MOVIMIENTO_ERROR);

    ///si la partida esta llena ERROR
    if(lleno>=9){
        return PART_MOVIMIENTO_ERROR;
    }
    ///si ya hay una ficha en la posicion ERROR
    if(t->grilla[mov_x][mov_y]!=PART_SIN_MOVIMIENTO)
        return (PART_MOVIMIENTO_ERROR);

    else{
        ///si es el turno de Jugador 1 y gana devuelvo gana jug 1, ademas actualizo turno
        if(p->turno_de==PART_JUGADOR_1){
            t->grilla[mov_x][mov_y]=PART_JUGADOR_1;
            if(ganoP(t,PART_JUGADOR_1)){
                return PART_GANA_JUGADOR_1;
            }
                p->turno_de=PART_JUGADOR_2;
        }
        ///si no ,chequeo si gana jugador 2 si gana devuelvo gano jug 2, ademas actualizo turno
        else{
            t->grilla[mov_x][mov_y]=PART_JUGADOR_2;
            if(ganoP(t,PART_JUGADOR_2)){
                return PART_GANA_JUGADOR_2;
            }
                p->turno_de=PART_JUGADOR_1;
        }
        ///aumento lo lleno ya que agregue un movimiento
        lleno++;
        ///si esta lleno se empato la partida
        if(lleno>=9){
            p->estado=PART_SIN_MOVIMIENTO;
            return PART_EMPATE;
        }

    }
    ///si no paso nada de lo anterior el movimiento fue valido
    return PART_MOVIMIENTO_OK;
}
/**
    libero toda la memoria almacenada para la partida y la destruyo
*/
void finalizar_partida(tPartida * p){
    free((*p)->nombre_jugador_1);
    free((*p)->nombre_jugador_2);
    free((*p)->tablero);
    free(*p);
    free(p);
    p=NULL;
}

