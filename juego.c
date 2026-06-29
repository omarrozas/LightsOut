#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define N 6 //Acá había un error, porque la matriz es de 6x6 pero va de 0 a 5.
#define TIPO char

void dibujar(char[N][N], int);
void cargar(char[N][N]);
void calcular(char[N][N], int, int, int, int);
int ganar(char[N][N], int);
char solicitarJugada(int[], int);

int main(){
    long start = time(NULL);
    char tablero[N][N], jugada;
    int seleccion, tamanio;
    int coordenadas[2]; //va a servir para meter la jugada
    menu:
    system("clear");
    printf("1 - Jugar\n2 - Estadisticas\nPresione cualquier tecla para salir\n");
    scanf(" %d", &seleccion);
    switch(seleccion){
        case 1:
            cargar(tablero);
            printf("Que tablero desea jugar? (3x3 4x4 5x5)\n");
            scanf("%d", &tamanio);
            do{
                system("clear");
                dibujar(tablero, tamanio);
                if (ganar(tablero, tamanio) == 1){
                  printf("¡Ganaste!\n");
                  fflush(stdout);
                  sleep(2);
                  goto menu;
                }//if-ganar
                jugada = solicitarJugada(coordenadas, tamanio);
                switch (jugada){
                  case 'j':
                    calcular(tablero, coordenadas[0], coordenadas[1], N, N);
                    break;
                  case 'r':
                    cargar(tablero);
                    dibujar(tablero, tamanio);
                    break;
                  case 'q':
                    goto menu;
                  case 'e':
                    printf("Valores incorrectos! Por favor, ingresá de nuevo tu jugada.\n");
                    sleep(2);
                    break;
                }//switch del case 1
            }while(1);
      case 2:
        system("clear");
        printf("Por ahora aqui no hay nada!\n");
        fflush(stdout);
        sleep(2);
        goto menu;
      default:
        system("clear");
        printf("NOS VEMOS!\n");
        fflush(stdout);
        sleep(2);
        break;    
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
    printf("\nPresiona \nej: '1%d' para fila 1 y columna %d\n'r' para resetear\n'q' para abandonar\n", ene, ene);
}//dibujar

void calcular(char m[N][N], int fila, int columna, int filaTope, int colTope){
    if (fila == 8 || columna == 8) {
            cargar(m);
    }else{
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
    }//for
  }//if
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



int ganar (char m[N][N], int ene){
    for (int i=1;i<=ene;i++){
        for (int j=1;j<=ene;j++){
            if (m[i][j]!=' ')
            return 0;
            }
    }
    return 1;
}
  
char solicitarJugada(int co[], int tope){
  char entrada[10]; //Con 10 espacios por si el jugador mete cualquier cosa
  printf("Tu jugada: ");
  scanf(" %s", entrada); //Va sin el &. Ni idea. Para estudiar
  // Primero evalúo si el jugador quiere abandonar o reiniciar  
  if (entrada[0]=='r' || entrada[0]=='R') return 'r';
  if (entrada[0]=='q' || entrada[0]=='Q') return 'q';
  //Ahora descompongo la jugada
  int f = entrada[0]-'0'; //se resta '0' porque son chars que tienen un valor int. Ej '3'-'0' = 51-48 = 3 numérico
  int c = entrada[1]-'0';
  //Si   
  if(f > 0 && f <= tope && c > 0 && c<=tope){
      co[0] = f;
      co[1] = c;
      return 'j';      
  }else{
      return 'e';
  }
}


