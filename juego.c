#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "libfun.h"
#define N 5
#define F 5
#define C 5
#define TIPO char

int main(){
    long start = time(NULL);
    char tablero[F][C];
    int seleccion, fil, col;
    char sel = 's';
    printf("1 - Jugar\n2 - Estadisticas\n3 - Salir\n");
    scanf(" %d", &seleccion);
    switch(seleccion){
        case 1:
            cargar(tablero);
            do{
                system("clear");
                dibujar(tablero, N);
                fil = solicitarf(F);
                col = solicitarc(C);
                calcular(tablero, fil, col, F, C);
                //evaluar(tablero)
                //printf("Desea jugar de nuevo?(s/n) > ");
               // scanf(" %c", &sel);
            }while(sel == 's');
    }//switch
    long end = time(NULL);
    printf("%ld\n", end - start);
    return 0;
}//main


