#include <stdio.h>
#include <stdlib.h>
#include "partida.h"


//Declaracion de funciones.

void printActualGame(tTablero tablero){
    printf("---┬---┬---\n");
    if(tablero->grilla[0][0]==0)
       printf("|   |");

}


int main(){

    //Declaracion de variables.
    //tTablero tablero; poque se crashea cuando hago tablero = partida ->tablero;
    tPartida part;
    char nombreJugador1[50];
    char nombreJugador2[50];
    int turno=0;
    int modo=0;
    int buenModo = 0;


    while(!buenModo){
    printf("Indique el modo de partida\n1.Jugador vs Jugador\n2.Jugador vs Maquina\n3.Maquina vs Maquina\n");
    scanf("%i",&modo);

    if(modo!=1 && modo!=2 && modo!=3){
        printf("No selecciono un modo correcto de partida\n");
    }
    else
        buenModo = 1;
    }
    //Modo usuario vs usuario.
    if(modo==1){
            printf("Indique nombre de Jugador 1.\n");
            scanf("%s",nombreJugador1);
            printf("Indique nombre de Jugador 2.\n");
            scanf("%s",nombreJugador2);
            printf("%s\n",nombreJugador1);
            printf("Indique '1' si empieza el jugador 1, '2' si empieza el jugador 2 o '3' para seleccion aleatoria.\n");
            scanf("%i",&turno);
            printf("antes");
            if(turno==1)
                nueva_partida(&part,PART_MODO_USUARIO_VS_USUARIO,PART_JUGADOR_1,nombreJugador1,nombreJugador2);
            if(turno==2)
                nueva_partida(&part,PART_MODO_USUARIO_VS_USUARIO,PART_JUGADOR_2,nombreJugador1,nombreJugador2);
            if(turno==3)
                nueva_partida(&part,PART_MODO_USUARIO_VS_USUARIO,PART_JUGADOR_RANDOM,nombreJugador1,nombreJugador2);
            printf("despues");
            printActualGame(part->tablero);
    }















return 0;
}
