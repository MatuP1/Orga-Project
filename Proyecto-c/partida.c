#include "partida.h"
#include "stdlib.h"
#include "stdio.h"

void nueva_partida(tPartida * p, int modo_partida, int comienza, char * j1_nombre, char * j2_nombre){

    p=(tPartida *) malloc (sizeof(tPartida));
    if(p==NULL)
        exit(PART_ERROR_MEMORIA);

    *p=(tPartida) malloc (sizeof(struct partida));
    if((*p)==NULL)
        exit(PART_ERROR_MEMORIA);

    //seteo modo y turno
    (*p)->modo_partida=modo_partida;
    (*p)->turno_de=comienza;       //si es jugador random que?
    (*p)->estado=PART_EN_JUEGO;

    //seteo nombres sin chequeo
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

    //inicializo el tablero
    (*p)->tablero=(tTablero) malloc (sizeof(struct tablero));
    if((*p)->tablero == NULL)
        exit(PART_ERROR_MEMORIA);
    for(int i=0; i<=2; i++){
        for(int j=0; j<=2; j++){
            (*p)->tablero->grilla[i][j]=0;
        }
    }
}

int nuevo_movimiento(tPartida p, int mov_x, int mov_y){
    tTablero t=p->tablero;
    if(t->grilla[mov_x][mov_y]==1)
        return (PART_MOVIMIENTO_ERROR);
    else
        t->grilla[mov_x][mov_y]=1;
    return PART_MOVIMIENTO_OK;      //necesita mas comtroles? cuando es necesario cambiar el estado de la partida?
                                    //debo recorrer todoel tablero cada vez?
}

void finalizar_partida(tPartida * p){
    free((*p)->nombre_jugador_1);
    free((*p)->nombre_jugador_2);
    free((*p)->tablero);
    free(*p);
    free(p);
    p=NULL;
}
