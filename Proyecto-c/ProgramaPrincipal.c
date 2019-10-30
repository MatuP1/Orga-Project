#include <stdio.h>
#include <stdlib.h>
#include "partida.h"
#include "ia.h"
#include "arbol.h"
#include "lista.h"


//Declaracion de funciones.

void printActualGame(tTablero tablero);


int main(){

    ///Declaracion de variables.
    tPartida part = (tPartida)malloc(sizeof(struct partida));
    tTablero tab = (tTablero)malloc(sizeof(struct tablero));
    ///Declaro todas las cosas de una partida
    char nombreJugador1[50];
    char nombreJugador2[50];
    int turno=0;
    int modo=0;
    ///banderas
    int buenModo = 0;
    int estadoPartida=111;
    ///posiciones
    int coordenadaX;
    int coordenadaY;
    ///alojo la memoria necesaria para una busqueda adversaria
    tBusquedaAdversaria maqBusqueda = (tBusquedaAdversaria)malloc(sizeof(struct busqueda_adversaria));

    ///escaneo el modo de juego
    while(!buenModo){
    printf("Indique el modo de partida\n1.Jugador vs Jugador\n2.Jugador vs Maquina\n3.Maquina vs Maquina\n");
    scanf("%i",&modo);

    ///msj de error si el modo de juego no es correcto
    if(modo!=1 && modo!=2 && modo!=3){
        printf("No selecciono un modo correcto de partida\n");
    }

    else
        buenModo = 1;
    }
    ///Escaneo el nombre del jugador 1
    printf("Indique nombre de Jugador 1.\n");
    scanf("%s",nombreJugador1);
    ///Modo usario vs usario
    if(modo==1){
            ///Guardo nombre jugador 2
            printf("Indique nombre de Jugador 2.\n");
            scanf("%s",nombreJugador2);
    }
    ///Modo usuario vs maquina
    if(modo==2){
        ///guardo nombre de la maquina
            nombreJugador2[0] = 'M';
            nombreJugador2[1] = 'a';
            nombreJugador2[2] = 'q';
            nombreJugador2[3] = 'u';
            nombreJugador2[4] = 'i';
            nombreJugador2[5] = 'n';
            nombreJugador2[6] = 'a';
    }
    ///Modo maquina vs maquina.
    if(modo==3){
        //seteo nombre de ambas maquinas
            nombreJugador1[0] = 'M';
            nombreJugador1[1] = 'a';
            nombreJugador1[2] = 'q';
            nombreJugador1[3] = 'u';
            nombreJugador1[4] = 'i';
            nombreJugador1[5] = 'n';
            nombreJugador1[6] = 'a';
            nombreJugador1[7] = ' ';
            nombreJugador1[8] = '1';
            nombreJugador2[0] = 'M';
            nombreJugador2[1] = 'a';
            nombreJugador2[2] = 'q';
            nombreJugador2[3] = 'u';
            nombreJugador2[4] = 'i';
            nombreJugador2[5] = 'n';
            nombreJugador2[6] = 'a';
            nombreJugador2[7] = ' ';
            nombreJugador2[8] = '2';
    }

    ///escaneo el turno del jugador
    printf("Indique '1' si empieza el jugador 1, '2' si empieza el jugador 2 o '3' para seleccion aleatoria.\n");
    scanf("%i",&turno);
    printf("los movimientos validos son entre 1 y 3 tanto para filas y columnas\n");
    ///Dependiendo el turno inicio un tipo de partida
    if(turno==1)
        nueva_partida(&part,PART_MODO_USUARIO_VS_USUARIO,PART_JUGADOR_1,nombreJugador1,nombreJugador2);
    if(turno==2)
        nueva_partida(&part,PART_MODO_USUARIO_VS_USUARIO,PART_JUGADOR_2,nombreJugador1,nombreJugador2);
    if(turno==3)
        nueva_partida(&part,PART_MODO_USUARIO_VS_USUARIO,PART_JUGADOR_RANDOM,nombreJugador1,nombreJugador2);

    ///Muestro el tablero vacio.
    tab = part->tablero;

    printActualGame(tab);
    printf("\n");
    ///Modo usario vs usuario
    if(modo==1){
        ///Empieza la partida y no termina hasta que gana el jugador 1, el 2 o empatan.
        while(estadoPartida != PART_GANA_JUGADOR_1 && estadoPartida != PART_GANA_JUGADOR_2 && estadoPartida !=PART_EMPATE){
                buenModo=0;

                ///Turno Jugador 1.
                if(part->turno_de == PART_JUGADOR_1)
                        printf("Jugador:%s Indique su movimiento\n",nombreJugador1);
                else
                        printf("Jugador:%s Indique su movimiento\n",nombreJugador2);

                while(!buenModo){
                    ///escaneo la fila
                    printf("Fila: ");
                    scanf("%i",&coordenadaX);
                    ///escaneo la columna
                    printf("Columna: ");
                    scanf("%i",&coordenadaY);

                    ///Chequeo si son coordenadas validas.
                    if((coordenadaX!=3 && coordenadaX!=1 && coordenadaX!=2 )|| (coordenadaY!=3 && coordenadaY!=1 &&coordenadaY!=2)){
                        printf("El movimiento no es valido\n");
                    }
                    ///si no salgo del while
                    else{
                        buenModo=1;
                    }
                }
                ///Actualizo el estado de la partida actual con un nuevo movimiento a las coordenadas
                estadoPartida = nuevo_movimiento(part,coordenadaX-1,coordenadaY-1);
                ///msg de error
                if(estadoPartida==PART_MOVIMIENTO_ERROR)
                    printf("Intenta en un lugar que no este ocupado\n");
                printActualGame(tab);
                printf("\n");
        }
    }
    ///Modo usario vs maquina
    if(modo==2){
        ///Empieza la partida y no termina hasta que gana el jugador 1 el 2 o empatan.
        while(estadoPartida != PART_GANA_JUGADOR_1 && estadoPartida != PART_GANA_JUGADOR_2 && estadoPartida !=PART_EMPATE){
                buenModo=0;
                 ///Turno Jugador 1.
                if(part->turno_de == PART_JUGADOR_1){
                    while(!buenModo){
                        ///escaneo fila
                        printf("Indique su movimiento\n");
                        printf("Fila: ");
                        scanf("%i",&coordenadaX);
                        ///escaneo columna
                        printf("Columna: ");
                        scanf("%i",&coordenadaY);

                        ///Chequeo si son coordenadas validas.
                        if((coordenadaX!=3 && coordenadaX!=1 && coordenadaX!=2 )|| (coordenadaY!=3 && coordenadaY!=1 &&coordenadaY!=2)){
                            printf("El movimiento no es valido\n");
                        }
                        ///si no salgo del while
                        else{
                            buenModo=1;
                        }
                    }
                    ///Realizo el movimiento.
                    estadoPartida = nuevo_movimiento(part,coordenadaX-1,coordenadaY-1);
                    ///msg de ERROR
                    if(estadoPartida==PART_MOVIMIENTO_ERROR)
                        printf("Intenta en un lugar que no este ocupado\n");
                    printActualGame(tab);
                    printf("\n");

                }
                ///Turno Maquina.
                ///si el jugador 1 no termino la partida
                if(part->turno_de == PART_JUGADOR_2 && (estadoPartida==PART_MOVIMIENTO_OK || estadoPartida==PART_EN_JUEGO)){
                        printf("Movimiento de la maquina\n");
                        ///Creo el arbol de busqueda adversaria.
                        crear_busqueda_adversaria(&maqBusqueda,part);
                        ///Le pido el proximo movimiento a la maquina y realizo el movimiento.
                        proximo_movimiento(maqBusqueda,&coordenadaX,&coordenadaY);
                        estadoPartida=nuevo_movimiento(part,coordenadaX,coordenadaY);
                        ///Destruyo la busqueda
                        destruir_busqueda_adversaria(&maqBusqueda);
                        printActualGame(tab);
                }
        }
    }

    if(modo==3){

        while(estadoPartida != PART_GANA_JUGADOR_1 && estadoPartida != PART_GANA_JUGADOR_2 && estadoPartida !=PART_EMPATE){
            ///turno maquina 1
            if(part->turno_de == PART_JUGADOR_1){
                ///Creo el arbol de busqueda adversaria.
                crear_busqueda_adversaria(&maqBusqueda,part);
                ///Le pido el proximo movimiento a la maquina y realizo el movimiento.
                proximo_movimiento(maqBusqueda,&coordenadaX,&coordenadaY);
                estadoPartida=nuevo_movimiento(part,coordenadaX,coordenadaY);
                destruir_busqueda_adversaria(&maqBusqueda);
                printActualGame(tab);
            }
            ///turno maquina 2
            if(part->turno_de == PART_JUGADOR_2 && estadoPartida==PART_MOVIMIENTO_OK){
                ///Creo el arbol de busqueda adversaria.
                crear_busqueda_adversaria(&maqBusqueda,part);
                ///Le pido el proximo movimiento a la maquina y realizo el movimiento.
                proximo_movimiento(maqBusqueda,&coordenadaX,&coordenadaY);
                estadoPartida=nuevo_movimiento(part,coordenadaX,coordenadaY);
                destruir_busqueda_adversaria(&maqBusqueda);
                printActualGame(tab);
            }
        }
    }
    ///Muestro el resultado de la partida.
    if(estadoPartida == PART_GANA_JUGADOR_1){
        printf("Gano %s!!",nombreJugador1);
    }
    if(estadoPartida == PART_GANA_JUGADOR_2){
        printf("Gano %s!!",nombreJugador2);
    }
    if(estadoPartida == PART_EMPATE){
        printf("La partida termino en empate");
    }
    ///Finalizo la partida.
    finalizar_partida(&part);

    return 0;
}
///metodo que imprime las columnas de los extremos segun corresponda
void printPositionLateral(tTablero tablero,int fila,int columna){
    if(tablero->grilla[fila][columna]==PART_SIN_MOVIMIENTO)
       printf("|   |");
    if(tablero->grilla[fila][columna]==PART_JUGADOR_1)
        printf("| X |");
    if(tablero->grilla[fila][columna]==PART_JUGADOR_2)
        printf("| O |");
}
///metodo que imprime la columna del medio segun corresponda
void PrintPositionMid(tTablero tablero,int fila,int columna){
    if(tablero->grilla[fila][columna]==PART_SIN_MOVIMIENTO)
       printf("   ");
    if(tablero->grilla[fila][columna]==PART_JUGADOR_1)
        printf(" X ");
    if(tablero->grilla[fila][columna]==PART_JUGADOR_2)
        printf(" O ");
}
///metodo que imprime el tablero actual
void printActualGame(tTablero tablero){
    ///Imprimo separador.
    printf("|---|---|---|\n");
    ///imprimo primera fila.
    printPositionLateral(tablero,0,0);
    PrintPositionMid(tablero,0,1);
    printPositionLateral(tablero,0,2);
    printf("\n");
    ///Imprimo separador.
    printf("|---|---|---|\n");
    ///Imprimo segunda linea.
    printPositionLateral(tablero,1,0);
    PrintPositionMid(tablero,1,1);
    printPositionLateral(tablero,1,2);
    printf("\n");
    ///Imprimo separador.
    printf("|---|---|---|\n");
    ///Imprimo tercera linea.
    printPositionLateral(tablero,2,0);
    PrintPositionMid(tablero,2,1);
    printPositionLateral(tablero,2,2);
    printf("\n");
    ///Imprimo separador.
    printf("|---|---|---|\n");

}
