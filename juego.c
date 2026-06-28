#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "libfun.h"
#define N 6 //Acá había un error, porque la matriz es de 6x6 pero va de 0 a 5.
#define TIPO char

void dibujar(char[N][N], int);
void cargar(char[N][N]);
void calcular(char[N][N], int, int, int, int);
int solicitarf(int);
int solicitarc(int);
int ganar(char[N][N], int);

int main(){
    long start = time(NULL);
    char tablero[N][N];
    int seleccion, fil, col;
    char sel = 's';
    nuevo:
    system("cls");
    printf("1 - Jugar\n2 - Estadisticas\n3 - Salir\n");
    scanf(" %d", &seleccion);
    switch(seleccion){
        case 1:
            cargar(tablero);
            do{
                system("cls");
                dibujar(tablero, 3);
                fil = solicitarf(N);
                col = solicitarc(N);
                if (fil==8 || col==8){
                    cargar(tablero);
                    dibujar(tablero, 3);
                } else if (fil==9 || col==9) {
                    goto nuevo;
                } else {
                   calcular(tablero, fil, col, N, N);
                   }
                if ((ganar(tablero, 3))==1){
                   printf("¡Ganaste!");}
                //evaluar(tablero)
                //printf("Desea jugar de nuevo?(s/n) > ");
               // scanf(" %c", &sel);
            }while(sel == 's');
    }//switch
    long end = time(NULL);
    printf("%ld\n", end - start);
    return 0;
}//main

void dibujar(char m[N][N], int ene){
    for(int i=0;i<=ene;i++){ //filas
        if(i!=0) printf("\n");
        for(int j=0;j<=ene;j++){
            if (i==0){
            printf("%d\t",j);
            }else if(j==0){
                printf("%d\t",i);
            }else{
                printf("[%c]\t", m[i][j]);
            }//if-elseif
        }//for hijo
    }//for padre
    printf("\nPresiona: 1-%d para jugar | 8 para resetear | 9 para abandonar\n", ene);
}//dibujar

void calcular(char m[N][N], int fila, int columna, int filaTope, int colTope){
    if (fila == 8 || columna == 8) {
            cargar(m);

    } else {
    for(int i=fila-1;i<=fila+1;i++){
        if(i>0 && i < filaTope){//con esta línea valido que el if no evalúe nada en la fila 0
          if(m[i][columna]=='X'){
              m[i][columna] = ' ';
          }else if(m[i][columna]==' '){
              m[i][columna] = 'X';
          }//if-else
        }//if validador
    }//for
    for(int j=columna-1;j<=columna+1;j+=2){
        if(j>0 && j < colTope){ //con esta línea valido que el if no evalúe nada en la columna 0
          if(m[fila][j]=='X'){
              m[fila][j] = ' ';
          }else if(m[fila][j]==' '){
              m[fila][j] = 'X';
          }//if-else
        }//if validador
    }
}
}

void cargar(char m[N][N]){
    printf("Cargando\n");
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            //printf("%d,%d >", i,j);
            //scanf(" %c", &m[i][j]);
            m[i][j] = 'X';
        }//for hijo
    }//for padre
}//cargar

int solicitarf(int filas){
    int filasUsuario;
    do{
        printf("\nFila: \n");
        scanf("%d", &filasUsuario);
        if (filasUsuario==8 || filasUsuario==9){
            return filasUsuario;
        }
        if (filasUsuario<1 || filasUsuario >= filas) printf("\n*******Fila fuera de rango******* \n");
    }while(filasUsuario<1 || filasUsuario >= filas);
    return filasUsuario;
}//solicitarf

int solicitarc(int columnas){
    int columnasUsuario;
    do{
        printf("\nColumna: \n");
        scanf("%d", &columnasUsuario);
        if (columnasUsuario==8 || columnasUsuario==9){
            return columnasUsuario;
        }
        if (columnasUsuario<1 || columnasUsuario >= columnas) printf("\n*******Columna fuera de rango******* \n");
    }while(columnasUsuario<1 || columnasUsuario >= columnas);
    return columnasUsuario;
}//solicitarf

/*int ganar (char m[N][N], int ene){
    for (int i=1;i<=ene;i++){
        for (int j=1;j<=ene;j++){
            if (m[i][j]!=' ')
            return 0;
            }
    }
    return 1;
}*/
 int ganar (char m[N][N], int ene){
    for (int i=1;i<=ene;i++){
        for (int j=1;j<=ene;j++){
            if (m[i][j]=='X'){
                return 0;
            }
    return 1;
}
}}


