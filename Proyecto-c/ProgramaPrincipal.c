#include <stdio.h>
#include <stdlib.h>
#include "partida.h"
#include "ia.h"


//Declaracion de funciones.

void printActualGame(tTablero tablero);


int main(){

    //Declaracion de variables.
    //tTablero tablero; poque se crashea cuando hago tablero = partida ->tablero;
    tPartida part = (tPartida)malloc(sizeof(int));
    tTablero tab = (tTablero)malloc(sizeof(int));
    char nombreJugador1[50];
    char nombreJugador2[50];
    int turno=0;
    int modo=0;
    int buenModo = 0;
    int estadoPartida=111;
    int coordenadaX;
    int coordenadaY;
    tBusquedaAdversaria maqBusqueda = (tBusquedaAdversaria)malloc(sizeof(struct busqueda_adversaria));



    while(!buenModo){
    printf("Indique el modo de partida\n1.Jugador vs Jugador\n2.Jugador vs Maquina\n3.Maquina vs Maquina\n");
    scanf("%i",&modo);

    if(modo!=1 && modo!=2 && modo!=3){
        printf("No selecciono un modo correcto de partida\n");
    }
    else
        buenModo = 1;
    }
    ///Modo usuario vs usuario.
    if(modo==1){
            printf("Indique nombre de Jugador 1.\n");
            scanf("%s",nombreJugador1);
            printf("Indique nombre de Jugador 2.\n");
            scanf("%s",nombreJugador2);
            printf("%s\n",nombreJugador1);
            printf("Indique '1' si empieza el jugador 1, '2' si empieza el jugador 2 o '3' para seleccion aleatoria.\n");
            scanf("%i",&turno);

            if(turno==1)
                nueva_partida(&part,PART_MODO_USUARIO_VS_USUARIO,PART_JUGADOR_1,nombreJugador1,nombreJugador2);
            if(turno==2)
                nueva_partida(&part,PART_MODO_USUARIO_VS_USUARIO,PART_JUGADOR_2,nombreJugador1,nombreJugador2);
            if(turno==3)
                nueva_partida(&part,PART_MODO_USUARIO_VS_USUARIO,PART_JUGADOR_RANDOM,nombreJugador1,nombreJugador2);

            ///Muestro el tablero vacio.
            tab = part->tablero;
            printActualGame(tab);

            ///Empieza la partida y no termina hasta que gana el jugador 1 el 2 o empatan.
            while(estadoPartida != PART_GANA_JUGADOR_1 && estadoPartida != PART_GANA_JUGADOR_2 && estadoPartida !=PART_EMPATE){
                    buenModo=0;

                    ///Turno Jugador 1.
                    if(part->turno_de == PART_JUGADOR_1){
                        while(!buenModo){
                            printf("%s Indique su movimiento\n",nombreJugador1);
                            printf("Fila: ");
                            scanf("%i\n",&coordenadaX);
                            printf("Columna: ");
                            scanf("%i\n",&coordenadaY);

                            ///Chequeo si son coordenadas validas.
                            if((coordenadaX!=0 && coordenadaX!=1 && coordenadaX!=2 )|| (coordenadaY!=0 && coordenadaY!=1 &&coordenadaY!=2)){
                                printf("El movimiento no es valido\n");
                            }
                            else{
                                buenModo=1;
                            }
                        }
                        nuevo_movimiento(part,coordenadaX,coordenadaY);


                    }
                    ///Turno Jugador 2.
                    if(part->turno_de == PART_JUGADOR_2){
                        while(!buenModo){
                            printf("%s Indique su movimiento\n",nombreJugador2);
                            printf("Fila: ");
                            scanf("%i\n",&coordenadaX);
                            printf("Columna: ");
                            scanf("%i\n",&coordenadaY);

                            ///Chequeo si son coordenadas validas.
                            if((coordenadaX!=0 && coordenadaX!=1 && coordenadaX!=2 )|| (coordenadaY!=0 && coordenadaY!=1 &&coordenadaY!=2)){
                                printf("El movimiento no es valido\n");
                            }
                            else{
                                buenModo=1;
                            }
                        }
                        ///Realizo el movimiento y actualizo el estado de la partida.
                        estadoPartida = nuevo_movimiento(part,coordenadaX,coordenadaY);
                    }


            }
            ///Muestro el resultado de la partida.
            if(estadoPartida == PART_GANA_JUGADOR_1){
                printf("Gano %s!!",nombreJugador1);
            }
            if(estadoPartida ==PART_GANA_JUGADOR_2){
                printf("Gano %s!!",nombreJugador2);
            }
            if(estadoPartida == PART_EMPATE){
                printf("La partida termino en empate");
            }
            ///Finalizo la partida.
            finalizar_partida(&part);
    }
    ///Modo usuario vs maquina
    if(modo==2){
            printf("Indique nombre de Jugador\n");
            scanf("%s",nombreJugador1);
            nombreJugador2[0] = 'M';
            nombreJugador2[1] = 'a';
            nombreJugador2[2] = 'q';
            nombreJugador2[3] = 'u';
            nombreJugador2[4] = 'i';
            nombreJugador2[5] = 'n';
            nombreJugador2[6] = 'a';

            printf("Indique '1' si empieza el jugador 1, '2' si empieza la maquina 2 o '3' para seleccion aleatoria.\n");
            scanf("%i",&turno);

            if(turno==1)
                nueva_partida(&part,PART_MODO_USUARIO_VS_USUARIO,PART_JUGADOR_1,nombreJugador1,nombreJugador2);
            if(turno==2)
                nueva_partida(&part,PART_MODO_USUARIO_VS_USUARIO,PART_JUGADOR_2,nombreJugador1,nombreJugador2);
            if(turno==3)
                nueva_partida(&part,PART_MODO_USUARIO_VS_USUARIO,PART_JUGADOR_RANDOM,nombreJugador1,nombreJugador2);

            ///Muestro el tablero vacio.
            tab = part->tablero;
            printActualGame(tab);

            ///Empieza la partida y no termina hasta que gana el jugador 1 el 2 o empatan.
            while(estadoPartida != PART_GANA_JUGADOR_1 && estadoPartida != PART_GANA_JUGADOR_2 && estadoPartida !=PART_EMPATE){
                    buenModo=0;

                    ///Turno Jugador 1.
                    if(part->turno_de == PART_JUGADOR_1){
                        while(!buenModo){
                            printf("%s Indique su movimiento\n",nombreJugador1);
                            printf("Fila: ");
                            scanf("%i\n",&coordenadaX);
                            printf("Columna: ");
                            scanf("%i\n",&coordenadaY);

                            ///Chequeo si son coordenadas validas.
                            if((coordenadaX!=0 && coordenadaX!=1 && coordenadaX!=2 )|| (coordenadaY!=0 && coordenadaY!=1 &&coordenadaY!=2)){
                                printf("El movimiento no es valido\n");
                            }
                            else{
                                buenModo=1;
                            }
                        }
                        nuevo_movimiento(part,coordenadaX,coordenadaY);


                    }
                    ///Turno Maquina.
                    if(part->turno_de == PART_JUGADOR_2){
                            ///Creo el arbol de busqueda adversaria.
                            crear_busqueda_adversaria(&maqBusqueda,part);
                            ///Le pido el proximo movimiento a la maquina.
                            proximo_movimiento(maqBusqueda,&coordenadaX,&coordenadaY);

                            }
            }
            ///Realizo el movimiento y actualizo el estado de la partida.
            estadoPartida = nuevo_movimiento(part,coordenadaX,coordenadaY);

            ///Muestro el resultado de la partida(No es posible que gane el jugador).
            if(estadoPartida ==PART_GANA_JUGADOR_2){
                printf("Gano %s!!",nombreJugador2);
            }
            if(estadoPartida == PART_EMPATE){
                printf("La partida termino en empate");
            }
            ///Finalizo la partida.
            finalizar_partida(&part);


    }
















return 0;
}

void printActualGame(tTablero tablero){
    printf("---┬---┬---\n");
    if(tablero->grilla[1][2]==2)
       printf("|   |");

}