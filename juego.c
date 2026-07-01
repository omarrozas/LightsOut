#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define N 6 //Acá había un error, porque la matriz es de 6x6 pero va de 0 a 5.
#define JUEGOS 15
#define TIPO char

// Sección de declaración de funciones
void dibujar(char[N][N], int);
void cargar(char[N][N]);
void calcular(char[N][N], int, int, int);
int ganar(char[N][N], int);
char solicitarJugada(int[], int);
void cargaral(char [N][N],int, int);

//Sección de variables globales
const char* JUEGO3[JUEGOS] = {  //Lleva * porque en realidad son strings
"XXXXXXXXX","X   X   X","X  XX XXX","X XX XXX ","X   XX X ","XX X     ","XXX X X  ","  X XX  X",
"  XXXXXXX"," XXXX X  ","  X  XXX ","XX  XXXX ","X X     X","X  XXXXX ","XXX XX X "};
const char* JUEGO4[JUEGOS] = {"        X   XX  ","  X  XXXX X XX  ","X X X XX  X XX",  
"X   XX      XX  ","        X   XX  ","        X  XXXXX","   X  XXX   XXXX"," X XXX XXX  XXXX",
" XXXX X XXX XXXX","X XX  X XXX XXXX","X     XXXXX XXXX","XXXX   XXXX XXXX","XXXX   XXXXXXX  ",
"XX      XXXXXX  ","XX      XXX XXXX"};
const char* JUEGO5[JUEGOS] = {
"    X   XX    X          ","    X   XXX   XXX   X    ","    X   XX    X          ","    X   XXX   XXX   X    ",
"  XX     XX   XXX   X    ","  XX X   X X  X X   X    "," XXX  XX X    X X   X    "," XXX  XX X    X      XX  ",
" XXX   X XXXX X X    XX  "," XXX   XXXXX X  X X  XX  "," XXX   XXXX  X X XX   X  "," XXX   XX X   XX XXX  X  ",
" XXX   XXXX  X X XX   X  "," X X  X  XX XX X XX   X  ","   X X X XXXXX X XX   X  "};

//Main
int main(){
  srand(getpid());
  long start = time(NULL);
  char tablero[N][N], jugada, seleccion;
  int tamanio, indice;
  int coordenadas[2]; //va a servir para meter la jugada
  menu:
  system("clear");
  printf("Bienvenido\n");    
  printf("1 - Jugar\n2 - Estadisticas\nPresione cualquier tecla para salir\n");
  scanf(" %c", &seleccion);
  switch(seleccion){
    case '1':
      system("clear");
      //cargar(tablero);
      do{
        printf("Que tamaño querés jugar? (3, 4 o 5)\n");
        scanf("%d", &tamanio);
        if(tamanio < 3 || tamanio > 5) printf("Valor incorrecto!\n");
        }while(tamanio < 3 || tamanio > 5);     
      indice = rand()%JUEGOS;//Genera indices entre 0 y 15
      cargaral(tablero, tamanio, indice);
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
            calcular(tablero, coordenadas[0], coordenadas[1], N);
            break;
          case 'r':
            cargaral(tablero, tamanio, indice);
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
      break;
    case '2':
      system("clear");
      printf("Por ahora aqui no hay nada!\n");
      sleep(2);
      goto menu;
    default:
      system("clear");
      printf("NOS VEMOS!\n");
      sleep(2);
      break;    
  }//switch
  long end = time(NULL);
  printf("Tiempo jugado %ld segundos\n", end - start);
  return 0;
}//main

void dibujar(char m[N][N], int ene){
    printf("==========================================================="
      "\nINSTRUCCIONES\n"
      "Para jugar ingresá un numero, Ej: '1%d' para fila 1 y columna %d\n"
      "'r' para resetear\n"
      "'q' para abandonar\n"
      "===========================================================\n\n", ene, ene);
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
  printf("\n");
}//dibujar

void calcular(char m[N][N], int fila, int columna, int tope){
  for(int i=fila-1;i<=fila+1;i++){
    if(i>0 && i < tope){//con esta línea valido que el if no evalúe nada en la fila 0
      if(m[i][columna]=='X'){
        m[i][columna] = ' ';
      }else if(m[i][columna]==' '){
        m[i][columna] = 'X';
      }//if-else
    }//if validador
  }//for
  for(int j=columna-1;j<=columna+1;j+=2){
    if(j>0 && j < tope){ //con esta línea valido que el if no evalúe nada en la columna 0
      if(m[fila][j]=='X'){
        m[fila][j] = ' ';
      }else if(m[fila][j]==' '){
        m[fila][j] = 'X';
      }//if-else
    }//if validador
  }//for
}//calcular

void cargar(char m[N][N]){
  printf("Cargando\n");
  for (int i=1;i<N;i++){
    for (int j=1;j<N;j++){
      m[i][j] = 'X';
    }//for hijo
  }//for padre
}//cargar

void cargaral(char m[N][N],int ene, int ind){
  int k=0;
  const char* aux = NULL;
  switch(ene){
    case 3:
      aux = JUEGO3[ind];
      break;
    case 4:
      aux = JUEGO4[ind];
      break;
    case 5:
      aux = JUEGO5[ind];
      break;
  }//switch
  printf("Cargando\n");
  for (int i=1;i<=ene;i++){
    for (int j=1;j<=ene;j++){
      m[i][j] = aux[k];
      k++;
    }//for hijo
  }//for padre
}//cargaral

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


