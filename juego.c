#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define N 6 //Acá había un error, porque la matriz es de 6x6 pero va de 0 a 5.
#define JUEGOS 15
#define CONTADOR 5 //esta linea es para reemplazar la cantidad de jugadas. Va a ser de CONTADOR x tamanio
#define MSG "clear"
#define VACIARBUFFER() {int c = 0; while((c=getchar()) != '\n' && c != EOF);}

//Sección de declaración de funciones
void dibujar(char[N][N], int, int);
void instrucciones();
void calcular(char[N][N], int, int, int);
int ganar(char[N][N], int);
int perder(int, int);
char solicitarJugada(int[], int);
void cargaral(char [N][N],int, int);
void estadisticas(int, int [], int [], int []);

//Sección de variables globales
const char *JUEGO3[JUEGOS] = {  //Lleva * porque son strings
"XXXXXXXXX","X   X   X","X  XX XXX","X XX XXX ","X   XX X ","XX X     ","XXX X X  ","  X XX  X",
"  XXXXXXX"," XXXX X  ","  X  XXX ","XX  XXXX ","X X     X","X  XXXXX ","XXX XX X "};
const char *JUEGO4[JUEGOS] = {"        X   XX  ","  X  XXXX X XX  ","X X X XX  X XX  ",
"X   XX      XX  ","        X   XX  ","        X  XXXXX","   X  XXX   XXXX"," X XXX XXX  XXXX",
" XXXX X XXX XXXX","X XX  X XXX XXXX","X     XXXXX XXXX","XXXX   XXXX XXXX","XXXX   XXXXXXX  ",
"XX      XXXXXX  ","XX      XXX XXXX"};
const char *JUEGO5[JUEGOS] = {
"    X   XX    X          ","    X   XXX   XXX   X    ","    X   XX    X          ","    X   XXX   XXX   X    ",
"  XX     XX   XXX   X    ","  XX X   X X  X X   X    "," XXX  XX X    X X   X    "," XXX  XX X    X      XX  ",
" XXX   X XXXX X X    XX  "," XXX   XXXXX X  X X  XX  "," XXX   XXXX  X X XX   X  "," XXX   XX X   XX XXX  X  ",
" XXX   XXXX  X X XX   X  "," X X  X  XX XX X XX   X  ","   X X X XXXXX X XX   X  "};


int main(){
  //declaracion de variables internas
  srand(getpid());
  long start = time(NULL), tiempo;
  char tablero[N][N], jugada, rta, seleccion, continuar;
  int tamanio, indice, cont;
  int victorias[] = {0,0,0};
  int perdidos[] = {0,0,0};
  int abandonados[] = {0,0,0};
  int coordenadas[2];
  system(MSG);
  printf("=================================LIGHTS OUT!=================================\n\n\n"
  "\t\t    [X]...[ ]...[X]...[ ]...[X]...[ ]...[X]\n\n\n"
  "\n\n\nPor Cami y Omar\n"
  "=============================================================================\n");
    
  sleep(2);
  //Bucle principal del juego. Carga el menu. 
  do {
    menu:    
    cont = 0;
    system(MSG);
    printf("Bienvenido\n");
    printf("1 - Jugar\n2 - Estadisticas\nPresiona cualquier tecla para salir\n");
    scanf(" %c", &seleccion);
    
    // switch de selección de menu. case 1: juego. case 2: estadisticas. default: salir
    switch(seleccion){
        case '1':
            system(MSG);            
            instrucciones();
            
            // Solicitud y validación del tamaño de tablero
            do{
              system(MSG);
              VACIARBUFFER(); //Vacio el buffer por si el usuario ingresa un char o string
              printf("¿Que tamaño queres jugar? (3, 4 o 5)\n");
              scanf("%d", &tamanio);
              if(tamanio < 3 || tamanio > 5){ 
                printf("Valor incorrecto!\n");
                sleep(1);                    
              }  
            }while(tamanio < 3 || tamanio > 5);

            // Generacion de un indice aleatorio fijo. Carga de un tablero aleatorio FIJO e inicio de tiempo.
            indice = rand()%JUEGOS;//Genera indices entre 0 y 15
            cargaral(tablero, tamanio, indice); 
            long start = time(NULL);
            
            // Comienzo del juego
            while (cont<=CONTADOR*tamanio){
              system(MSG);
              dibujar(tablero, tamanio, cont);
              
              //Primero se evalua si el tablero está ganado
              if (ganar(tablero, tamanio) == 1){
                printf("¡Ganaste!\n");
                long end = time(NULL);
                tiempo = end - start;
                printf("\nTiempo jugado %ld segundos\n", tiempo);
                cont = 0;
                if (tamanio==3) victorias[0]++;
                if (tamanio==4) victorias[1]++;
                if (tamanio==5) victorias[2]++;
                VACIARBUFFER();
                sleep(2);
                break;
              }
              //Despues se evalúa si el tablero está perdido
              if ((perder(cont, tamanio))==1){
                printf("\nPerdiste :(\n");
                long end = time(NULL);
                tiempo = end - start;
                printf("\nTiempo jugado %ld segundos\n", tiempo);
                printf("¿Intentar de nuevo?: s/n \n");
                scanf(" %c", &rta);
                // Si pierdo elijo si quiero volver a jugar                
                switch (rta){
                  case 's':
                    cargaral(tablero, tamanio, indice);
                    dibujar(tablero, tamanio, cont);
                    cont=0;
                    continue; //Este continue te saca afuera del switch, pero te deja al inicio del MISMO juego.
                  case 'n':
                    if (tamanio==3) perdidos[0]++;
                    if (tamanio==4) perdidos[1]++;
                    if (tamanio==5) perdidos[2]++;
                    estadisticas(tamanio, victorias, perdidos, abandonados);
                    goto menu;
                }//switch de rta
              //Por último, si no gané ni perdí, solicito la jugada.
              } else { 
                jugada = solicitarJugada(coordenadas, tamanio);
                cont++;
              }//if-else

              // Se evalua la salida de SolicitarJugada
              switch (jugada){
                case 'j':
                  calcular(tablero, coordenadas[0], coordenadas[1], tamanio);
                  break;
                case 'r':
                  cargaral(tablero, tamanio, indice);
                  dibujar(tablero, tamanio, cont);
                  cont=0;
                  break;
                case 'q':
                  long end = time(NULL);
                  tiempo = end - start;
                  printf("\nTiempo jugado %ld segundos\n", tiempo);
                  if (tamanio==3) abandonados[0]++;
                  if (tamanio==4) abandonados[1]++;
                  if (tamanio==5) abandonados[2]++;
                  estadisticas(tamanio, victorias, perdidos, abandonados);
                  goto menu;
                  break;
                case 'e':
                  printf("Valores incorrectos. Por favor, ingresa de nuevo tu jugada.\n");
                  sleep(1);
                  break;
              }//switch de jugada
            }//while
            break;

        case '2':
            system(MSG);
            estadisticas(tamanio, victorias, perdidos, abandonados);
            break;

        default:
            system(MSG);
            printf("\n NOS VEMOS!\n");
            sleep(2);
            return 0;
    }//switch seleccion
  } while (1); //while principal. Es el bucle del juego
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
  printf("\nIntentos: %d\tTe quedan: %d\n", contador, (ene*CONTADOR-contador));

}//dibujar

void calcular(char m[N][N], int fila, int columna, int tope){
  for(int i=fila-1;i<=fila+1;i++){
    if(i>0 && i <= tope){//con esta línea valido que el if no evalúe nada en la fila 0
      if(m[i][columna]=='X'){
        m[i][columna] = ' ';
      }else if(m[i][columna]==' '){
        m[i][columna] = 'X';
      }//if-else
    }//if validador
  }//for
  for(int j=columna-1;j<=columna+1;j+=2){
    if(j>0 && j <= tope){ //con esta línea valido que el if no evalúe nada en la columna 0
      if(m[fila][j]=='X'){
        m[fila][j] = ' ';
      }else if(m[fila][j]==' '){
        m[fila][j] = 'X';
      }//if-else
    }//if validador
  }//for
}//calcular

void instrucciones(){
  printf("=======================================================================================\n"
  "Para jugar se tienen que eliminar las 'X' de todos las casillas.\n\n"
  "Al seleccionar una casilla, esta cambiará su estado (por ejemplo de [X] a [ ]).\n\n"
  "También cambiarán de estado las casillas que estén arriba, abajo y a los lados," 
  "pero no en diagonal.\n\n"
  "Para seleccionar una casilla escriba el número de fila junto al número de columna\n"
  "y luego ENTER.\n\n"
  "Por ejemplo: fila 1 y columna 3: 13\n\n"
  "=======================================================================================\n\n"
  "Presione cualquier tecla para continuar: " );
  VACIARBUFFER();
  getchar();
}//intrucciones

void cargaral(char m[N][N],int ene, int ind){
  int k=0;
  const char *aux = NULL;
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

int perder(int intentos, int tam){
 if (intentos>=CONTADOR*tam){
    return 1;
 } else {
    return 0;
 }
}

char solicitarJugada(int co[], int tope){
  char entrada[10]; //Con 10 espacios por si el jugador mete cualquier cosa
  printf("Tu jugada: ");
  scanf(" %s", entrada); //Va sin el & porque es un string (array de chars que se pasa con direccion)
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

void estadisticas(int tamanio, int v[], int p[], int a[]){
  int bandera = 0; //Bandera que indica si el jugador abandonó al menos una partida.
  printf("\nEstadísticas:\n");
  for(int i = 0 ; i<=2 ; i++){
    if (a[i] != 0) bandera = 1; 
  }
  if (bandera == 0){
    printf("\nPartidas en 3x3\t\tGanadas: %d\tPerdidas: %d", v[0], p[0]);
    printf("\nPartidas en 4x4\t\tGanadas: %d\tPerdidas: %d", v[1], p[1]);
    printf("\nPartidas en 5x5\t\tGanadas: %d\tPerdidas: %d", v[2], p[2]);
  } else {
    printf("\nPartidas en 3x3\t\tGanadas: %d\tPerdidas: %d\tAbandonadas: %d", v[0], p[0], a[0]);
    printf("\nPartidas en 4x4\t\tGanadas: %d\tPerdidas: %d\tAbandonadas: %d", v[1], p[1], a[1]);
    printf("\nPartidas en 5x5\t\tGanadas: %d\tPerdidas: %d\tAbandonadas: %d", v[2], p[2], a[2]);
  }
  printf("\nPresiona cualquier tecla para continuar\n");           
  VACIARBUFFER(); 
  getchar();//cambie _getch() por getchar metido en una macro
}//estadisticas
