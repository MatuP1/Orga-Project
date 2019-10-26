#include "partida.h"
#include "stdlib.h"
#include "stdio.h"

void nueva_partida(tPartida * p, int modo_partida, int comienza, char * j1_nombre, char * j2_nombre){

    *p=(tPartida) malloc (sizeof(struct partida));
    if((*p)==NULL)
        exit(PART_ERROR_MEMORIA);

    //seteo modo y turno
    (*p)->modo_partida=modo_partida;
    (*p)->turno_de=comienza;       //si es jugador random que?
    (*p)->estado=PART_EN_JUEGO;
    if(comienza==PART_JUGADOR_RANDOM){
        if(rand() % 2 == 0)
            (*p)->turno_de=PART_JUGADOR_1;
        else
            (*p)->turno_de=PART_JUGADOR_2;
    }

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

int ganoP(tTablero t, int ficha){
    int gano=0;
    int i=0;
<<<<<<< HEAD
    while(gano!=3 && i<3){
=======
    ///Chequeo las lineas horizontales.
    while(gano!=3 || i<3){
>>>>>>> 1f9062c90ca29d9a5114d2bf88517b4045d224c9
        for(int j=0; j<3; j++){
            if(t->grilla[i][j]==ficha)
                gano++;
            }
        if(gano<3){
            gano=0;
        }
        i++;
    }
    if(gano>=3)
        return 1; //gano
    else
        gano=0;

    int j=0;
<<<<<<< HEAD
    while(gano!=3 && j<3){
=======
    ///Chequeo las lineas verticales.
    while(gano!=3 || j<3){
>>>>>>> 1f9062c90ca29d9a5114d2bf88517b4045d224c9
        for(int i=0; i<3; i++){
            if(t->grilla[i][j]==ficha)
                gano++;
            }
        if(gano<3)
            gano=0;
        j++;
    }
    if(gano>=3)
        return 1; //gano
    else
        gano=0;

    //diagonal hardcodeada x2
    i=0; j=0;
    while(j<3 && i<3){
        if(t->grilla[i][j]==ficha)
            gano++;
        else{
            j=2;
            i=2;
        }
    i++;
    j++;
    }
    if(gano>=3)
        return 1; //gano
    else
        gano=0;
    while(j>0 && i<3){
        j--;
        i--;
        if(t->grilla[i][j]==ficha)
            gano++;
        else{
            j=0;
            i=0;
        }
    }
    if(gano>=3)
        return 1; //gano
    else
        return gano=0;

}

int nuevo_movimiento(tPartida p, int mov_x, int mov_y){
    tTablero t=p->tablero;

    int lleno=0;
    ///Chequeo cuantas posiciones no estan vacias.
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(t->grilla[i][j]!=0)
                lleno++;
        }
    }
    ///Chequeo si las coordenadas pasadas por parametros son validas, si no lo son es un error.
    if(mov_x > 2 || mov_y > 2 || mov_x < 0 || mov_y < 0)
        exit(PART_MOVIMIENTO_ERROR);
    ///Chequeo si el tablero esta lleno, si lo esta es un error.
    if(lleno>=9){
        p->estado=PART_SIN_MOVIMIENTO;
        return PART_MOVIMIENTO_ERROR;
    }
    ///Chequeo si la posicion ya esta ocupada, si lo esta es un error.
    if(t->grilla[mov_x][mov_y]!=0)
        return (PART_MOVIMIENTO_ERROR);
    else{///Si la posicion no esta ocupada.
        ///Si es el turno del jugador 1 coloco la pieza del jugador 1 en la posicion pasada por parametro.
        if(p->turno_de==PART_JUGADOR_1){
            t->grilla[mov_x][mov_y]=1;
<<<<<<< HEAD
            if(ganoP(t,1)){
=======
            ///Si con el movimiento gana el jugador 1 retorono que gano el jugador 1.
            if(ganoP(p,1)){
>>>>>>> 1f9062c90ca29d9a5114d2bf88517b4045d224c9
                return PART_GANA_JUGADOR_1;
            }
            ///Indico que es el turno del jugador 2.
            p->turno_de=PART_JUGADOR_2;
        }
        ///Si es el turno del jugador 2 coloco la pieza del jugador 2 en la posicion pasada por parametro.
        else{
            t->grilla[mov_x][mov_y]=2;
            if(ganoP(t,2)){
                return PART_GANA_JUGADOR_2;
            }
            ///Indico que es el turno del jugador 1.
            p->turno_de=PART_JUGADOR_1;
        }
    }
    ///Retorno que el movimiento se ha efectuado correctamente.
    return PART_MOVIMIENTO_OK;
}

void finalizar_partida(tPartida * p){
    ///Libero el espacio en memoria correspondiente al nombre del jugador 1, al nombre del jugador 2, al tablero entotrados en el struct partida y a los punteros de partida.
    free((*p)->nombre_jugador_1);
    free((*p)->nombre_jugador_2);
    free((*p)->tablero);
    free(*p);
    free(p);
    p=NULL;
}

