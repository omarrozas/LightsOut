#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "libfun.h"
#define N 6
#define TIPO char

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
}//dibujar

void calcular(char m[N][N], int fila, int columna, int filaTope, int colTope){
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
        if (filasUsuario<1 || filasUsuario >= filas) printf("Fila fuera de rango: \n");
    }while(filasUsuario<1 || filasUsuario >= filas);
    return filasUsuario;
}//solicitarf

int solicitarc(int columnas){
    int columnasUsuario;
    do{
        printf("\nColumna: \n");
        scanf("%d", &columnasUsuario);
        if (columnasUsuario<1 || columnasUsuario >= columnas) printf("Columna fuera de rango: \n");
    }while(columnasUsuario<1 || columnasUsuario >= columnas);
    return columnasUsuario;
}//solicitarf
