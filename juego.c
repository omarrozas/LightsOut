#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <conio.h>
#define N 6 //Acá había un error, porque la matriz es de 6x6 pero va de 0 a 5.
#define JUEGOS 15
#define TIPO char

void dibujar(char[N][N], int, int);
void cargar(char[N][N]);
void calcular(char[N][N], int, int, int);
int ganar(char[N][N], int);
int perder(int);
char solicitarJugada(int[], int);
void cargaral(char [N][N],int, int);
void estadisticas(int, int, int, int, int, int, int);

//Sección de variables globales
const char* JUEGO3[JUEGOS] = {  //Lleva * porque son strings
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


int main(){
  srand(getpid());
  long start = time(NULL);
  char tablero[N][N], jugada, rta, seleccion, continuar;
  int tamanio, indice, cont, tiempo;
  int victorias3=0, victorias4=0, victorias5=0;
  int perdidos3=0, perdidos4=0, perdidos5=0;
  int coordenadas[2];

  do {
    cont=0;
    system("cls");
    printf("Bienvenido\n");

    printf("1 - Jugar\n2 - Estadisticas\n3 - Salir\n");
    scanf(" %c", &seleccion);

    switch(seleccion){
        case '1':
            system("cls");
            do{
                    printf("¿Que tamaño queres jugar? (3, 4 o 5)\n");
                    scanf("%d", &tamanio);
                    if(tamanio < 3 || tamanio > 5) printf("Valor incorrecto!\n");
            }while(tamanio < 3 || tamanio > 5);

        indice = rand()%JUEGOS;//Genera indices entre 0 y 15
        cargaral(tablero, tamanio, indice);
        long start = time(NULL);

        while (cont<=10){
                system("cls");
                dibujar(tablero, tamanio, cont);
                cont++;
                if (ganar(tablero, tamanio) == 1){
                        printf("¡Ganaste!\n");
                        long end = time(NULL);
                        tiempo = end - start;
                        printf("\nTiempo jugado %ld segundos\n", tiempo);
                        cont = 0;
                        if (tamanio==3) victorias3++;
                        if (tamanio==4) victorias4++;
                        if (tamanio==5) victorias5++;
                        fflush(stdout);
                        sleep(2);
                        break;
                }

                if ((perder (cont))==1){
                        printf("\nPerdiste :(\n");
                        long end = time(NULL);
                        tiempo = end - start;
                        printf("\nTiempo jugado %ld segundos\n", tiempo);
                        if (tamanio==3) perdidos3++;
                        if (tamanio==4) perdidos4++;
                        if (tamanio==5) perdidos5++;
                        printf("¿Intentar de nuevo?: s/n \n");
                        scanf(" %c", &rta);
                        switch (rta){
                            case 's':
                                cargaral(tablero, tamanio, indice);
                                dibujar(tablero, tamanio, cont);
                                cont=0;
                                continue;
                            case 'n':
                                break;
                        }
                } else {
                    jugada = solicitarJugada(coordenadas, tamanio);
                }

                switch (jugada){
                    case 'j':
                        calcular(tablero, coordenadas[0], coordenadas[1], N);
                        break;
                    case 'r':
                        cargaral(tablero, tamanio, indice);
                        dibujar(tablero, tamanio, cont);
                        cont=0;
                        break;
                    case 'q':
                        break;
                    case 'e':
                        printf("Valores incorrectos. Por favor, ingresa de nuevo tu jugada.\n");
                        sleep(1);
                        break;
                        }//switch del case 1
        } break;

        case '2':
            system("cls");
            estadisticas(tamanio, victorias3, victorias4, victorias5, perdidos3, perdidos4, perdidos5);
            //sleep(2);
            printf("\nPresiona cualquier tecla para continuar");
            _getch();
            break;

        case '3':
            system("cls");
            printf("\n NOS VEMOS!\n");
            break;

        default:
            system("cls");
            sleep(2);
            break;
    }//switch seleccion
  } while (seleccion != '3');

    return 0;
}

void dibujar(char m[N][N], int ene, int contador){
    printf("==========================================================="
      "\nINSTRUCCIONES\n"
      "Para jugar ingresa un numero, Ej: '1%d' para fila 1 y columna %d\n"
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
  printf("\nIntentos: %d \n", contador);

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

int perder(int intentos){
 if (intentos>10){
    return 1;
 } else {
     return 0;
 }
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

void estadisticas(int tamanio, int v3, int v4, int v5, int p3, int p4, int p5){
printf("\nEstadísticas: \n");
printf("\nPartidas en 3x3\nGanadas: %d   vs   Perdidas: %d", v3, p3);
printf("\nPartidas en 4x4\nGanadas: %d   vs   Perdidas: %d", v4, p4);
printf("\nPartidas en 5x5\nGanadas: %d   vs   Perdidas: %d", v5, p5);
}

