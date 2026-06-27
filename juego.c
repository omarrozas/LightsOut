#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 5
#define F 5
#define C 5
#define TIPO char

void dibujar(TIPO[F][C], int);
void cargar(TIPO[F][C]);
void calcular(TIPO[F][C], int, int);

int main(){
    long start = time(NULL);
    TIPO tablero[F][C];
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
                printf("\nFila: \n");
                scanf("%d", &fil);
                printf("\nColumna: \n");
                scanf("%d", &col);
                calcular(tablero, fil, col);
                //evaluar(tablero)
                printf("Desea jugar de nuevo?(s/n) > ");
                scanf(" %c", &sel);
            }while(sel == 's');
    }//switch
    long end = time(NULL);
    printf("%ld\n", end - start);
    return 0;
}//main

void dibujar(TIPO m[F][C], int ene){
    for(int i=0;i<=F-(F-ene);i++){ //filas
        if(i!=0) printf("\n");
        for(int j=0;j<=C-(C-ene);j++){
            if (i==0){
            printf("%d\t",j);
            }else if(j==0){
                printf("%d\t",i);
            }else{
                printf("[%c]\t", m[i][j]);
            }//if-elseif
        }//for hijo
    }//for padre
}//dibujar

void calcular(TIPO m[F][C], int fila, int columna){
    for(int i=fila-1;i<=fila+1;i++){
        if(m[i][columna]=='X'){
            m[i][columna] = 'O';
        }else if(m[i][columna]=='O'){
            m[i][columna] = 'X';
        }//if-else
    }//for
    for(int j=columna-1;j<=columna+1;j+=2){
        if(m[fila][j]=='X'){
            m[fila][j] = 'O';
        }else if(m[fila][j]=='O'){
            m[fila][j] = 'X';
        }//if-else
    }
}
/*void calcular(TIPO m[F][C], int fila, int columna){
if (m[fila][columna] == 'O') m[fila][columna] = 'X';
if (m[fila+1][columna] == 'O') m[fila+1][columna] = 'X';
if (m[fila-1][columna] == 'O') m[fila-1][columna] = 'X';
if (m[fila][columna+1] == 'O') m[fila][columna+1] = 'X';
if (m[fila][columna-1] == 'O') m[fila][columna-1] = 'X';
if (m[fila][columna] == 'X') m[fila][columna] = 'O';
if (m[fila+1][columna] == 'X') m[fila+1][columna] = 'O';
if (m[fila-1][columna] == 'X') m[fila-1][columna] = 'O';
if (m[fila][columna+1] == 'X') m[fila][columna+1] = 'O';
if (m[fila][columna-1] == 'X') m[fila][columna-1] = 'O';
}*/
void cargar(TIPO m[F][C]){
    printf("Cargando\n");
    for (int i=0;i<=F;i++){
        for (int j=0;j<=C;j++){
            //printf("%d,%d >", i,j);
            //scanf(" %c", &m[i][j]);
            m[i][j] = 'X';
        }//for hijo
    }//for padre
}//cargar
