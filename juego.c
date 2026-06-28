#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "libfun.h"
#define N 6 //Acá había un error, porque la matriz es de 6x6 pero va de 0 a 5.
#define TIPO char

int main(){
    long start = time(NULL);
    char tablero[N][N];
    int seleccion, fil, col;
    char sel = 's';
    printf("1 - Jugar\n2 - Estadisticas\n3 - Salir\n");
    scanf(" %d", &seleccion);
    switch(seleccion){
        case 1:
            cargar(tablero);
            do{
                system("clear");
                dibujar(tablero, 5);
                fil = solicitarf(N);
                col = solicitarc(N);
                calcular(tablero, fil, col, N, N);
                //evaluar(tablero)
                //printf("Desea jugar de nuevo?(s/n) > ");
               // scanf(" %c", &sel);
            }while(sel == 's');
    }//switch
    long end = time(NULL);
    printf("%ld\n", end - start);
    return 0;
}//main


