#include <stdio.h>   
#include <stdlib.h>  
#include <time.h>    

typedef struct {                                                                //Con typedef no necesito escribir todo el tiempo struct Carta
    int valor;                                                                  //Guarda el número de la carta que son: 1=As, 2-10=números, 11=J, 12=Q, 13=K
    int palo;                                                                   //Guarda el palo de la carta como: 0=trébol, 1=espada, 2=corazón, 3=diamante
} Carta; 

typedef struct {                                                                //Con typedef no necesito escribir todo el tiempo struct Jugador
    Carta mano[2];                                                              //Arreglo con las 2 cartas que tiene que tener el jugador
    int sigue;                                                                  //Para ver si el jugador se queda o se retira
} Jugador;

Carta NumeroCartas[52];                                                         //Este arreglo guarda las 52 cartas de la baraja
int CartasUso[52];                                                              //Para ver qué cartas se usaron
Carta River[5];                                                                 //El máximo de cartas que el River puede sacar

void crearBaraja() {                                                            //Esta función crea la baraja con las 52 cartas
    int indice=0;                                                               //La variable va desde 0 a 51, porque son las cartas
                  
    for(int palo=0; palo<4; palo=palo+1) {                                      //Es el bucle for para los palos       
        for(int valor=1; valor<=13; valor=valor+1) {                            //Es el bucle for para los valores de las Cartas
            NumeroCartas[indice].valor=valor;                                   //Le asigna valor a la carta
            NumeroCartas[indice].palo=palo;                                     //Le asigna valor de los palos 
            indice=indice+1;                                                    //Pasa a la siguiente carta 
        }
    }
}

Carta CartaAzar() {                                                             //Es la función para sacar una carta que no se haya usado
    int posicion=rand()%52; 
    while(CartasUso[posicion]==1) {                                             //Si la carta ya está usada, se busca otra 
        posicion=rand()%52;                                                     //Busca otra posición nueva 
    }

    CartasUso[posicion]=1;                                                      //Después marca para ir a otra posición 
    return NumeroCartas[posicion];                                              //Devuelve la carta
}

void VerValor(int valor) {                                                      //Muestra el valor de la carta 
    if(valor==1) {
        printf("A");
    }
    else if(valor==11) {
        printf("J");
    }
    else if(valor==12) { 
        printf("Q");
    }
    else if(valor==13) { 
        printf("K");
    }
    else { 
        printf("%d", valor);
    }
}

void VerPalo(int palo) {                                                        //Muestra el palo y su símbolo
    if(palo==0) { 
        printf("♣");
    }
    else if(palo==1) { 
        printf("♠");
    }
    else if(palo==2) {
        printf("♥");
    }
    else { // Diamante
        printf("♦");
    }
}
 
void VerCarta(Carta carta) {                                                    //Muestra la carta
    VerValor(carta.valor); 
    VerPalo(carta.palo);   
}

void orden(Carta cartas[], int cantidad) {                                      //Ordena las cartas por método burbuja 
    Carta temporal; 
    for(int i=0; i<cantidad-1; i=i+1) {
        for(int j=i+1; j<cantidad; j=j+1) {                                     //Si la carta que está en i es mayor que la de j, las intercambia
            if(cartas[i].valor>cartas[j].valor) {
                temporal=cartas[i];
                cartas[i]=cartas[j];
                cartas[j]=temporal;
            }
        }
    }
}

// Función para verificar si hay 5 cartas consecutivas (corrida)
int esCorrida(Carta cartas[], int cantidad) {
    orden(cartas, cantidad); // Ordena las cartas para facilitar la búsqueda
    
    // Busca corrida normal como 5,6,7,8,9
    for(int i=0; i<=cantidad-5; i=i+1) {
        if(cartas[i].valor+1==cartas[i+1].valor &&
           cartas[i].valor+2==cartas[i+2].valor &&
           cartas[i].valor+3==cartas[i+3].valor &&
           cartas[i].valor+4==cartas[i+4].valor) {
            return 1; // Sí hay corrida
        }
    }
    
    // Busca el caso especial: 10, J, Q, K, A
    for(int i=0; i<cantidad; i=i+1) {
        if(cartas[i].valor==1 && i<=cantidad-4) { // Encontró un As
            if(cartas[i+1].valor==10 && 
               cartas[i+2].valor==11 && 
               cartas[i+3].valor==12 && 
               cartas[i+4].valor==13) {
                return 1; // Sí hay corrida (10,J,Q,K,A)
            }
        }
    }
    
    return 0; // No hay corrida
}
       
int evaluarMano(Jugador jugador, Carta river[]) {                               //Ve qué mano tiene el jugador 
    Carta todas[7];                                                             //Junta las cartas del river y del jugador
    int valores[14]={0};                                                        //Cuenta cuántas cartas hay de cada valor
    int palos[4]={0};                                                           //Cuenta cuántas cartas hay de cada palo
    for(int i=0; i<2; i=i+1) {                                                  //Junta las cartas del jugador
        todas[i]=jugador.mano[i];
    }
    
    for(int i=0; i<5; i=i+1) {                                                  //Junta las cartas del river para poder analizarlas juntas 
        todas[i+2]=river[i];
    }
    
    for(int i=0; i<7; i=i+1) {                                                   //Cuenta frecuencias de valores y palos para que me diga cuántos de cada uno hay 
        valores[todas[i].valor]=valores[todas[i].valor]+1;
        palos[todas[i].palo]=palos[todas[i].palo]+1;
    }
    
    //1. Corrida real
    for(int paloActual=0; paloActual<4; paloActual=paloActual+1) {
        if(palos[paloActual]>=5) { 
            Carta mismoPalo[7];
            int contador=0;
            
            for(int i=0; i<7; i=i+1) {                                          //Guarda las cartas de ese palo
                if(todas[i].palo==paloActual) {
                    mismoPalo[contador]=todas[i];
                    contador=contador+1;
                }
            }
            orden(mismoPalo, contador); 
            for(int i=0; i<contador-4; i=i+1) {                                 //Ve si está: 10, J, Q, K 
                if(mismoPalo[i].valor==1 && 
                   mismoPalo[i+1].valor==10 &&
                   mismoPalo[i+2].valor==11 && 
                   mismoPalo[i+3].valor==12 &&
                   mismoPalo[i+4].valor==13) {
                    return 9;                                                   //Dice que es corrida real
                }
            }
        }
    }
    
    //2.Corrida de color 
    for(int paloActual=0; paloActual<4; paloActual=paloActual+1) {
        if(palos[paloActual]>=5) {
            Carta mismoPalo[7];
            int contador=0;
            
            for(int i=0; i<7; i=i+1) {
                if(todas[i].palo==paloActual) {
                    mismoPalo[contador]=todas[i];
                    contador=contador+1;
                }
            }
            
            if(esCorrida(mismoPalo, contador)==1) {
                return 8; 
            }
        }
    }
    
    //3.Poker
    for(int valorActual=1; valorActual<=13; valorActual=valorActual+1) {
        if(valores[valorActual]>=4) {
            return 7; 
        }
    }
    
    //4.Casa llena
    int cantidadTercias=0;                                                   //Cuenta cuántos valores tienen 3 o más
    int cantidadPares=0;                                                     //Cuenta cuántos valores tienen 2 o más
    
    for(int valorActual=1; valorActual<=13; valorActual=valorActual+1) {
        if(valores[valorActual]>=3) {
            cantidadTercias=cantidadTercias+1;
        }
        if(valores[valorActual]>=2) {
            cantidadPares=cantidadPares+1;
        }
    }
    
    if(cantidadTercias>=1 && cantidadPares>=2) {
        return 6; 
    }
    
    //5.Color
    for(int paloActual=0; paloActual<4; paloActual=paloActual+1) {
        if(palos[paloActual]>=5) {
            return 5; 
        }
    }
    
    //6.Corrida
    if(esCorrida(todas, 7)==1) {
        return 4;
    }
    
    //7.Tercia
    if(cantidadTercias>=1) {
        return 3; 
    }
    
    //8. Dos pares
    if(cantidadPares>=2) {
        return 2; 
    }
    
    //9.Un par
    if(cantidadPares>=1) {
        return 1; 
    }
    
    //10. Carta alta 
    return 0;
}

int cartaAlta(Jugador jugador) {                                                //Para obtener la carta más alta del jugador
    if(jugador.mano[0].valor>jugador.mano[1].valor) {
        return jugador.mano[0].valor;                                           //La primera es más grande
    }
    else {
        return jugador.mano[1].valor;                                           //La segunda es más grande
    }
}

int preguntar(int numeroJugador) {                                              //Pregunta si quiere seguir 
    int respuesta;                                                            
    do { 
        printf("Jugador %d, ¿quieres seguir jugando? (1=si, 2=no): ", numeroJugador);
        scanf(" %d", &respuesta);                                              
        
        if(respuesta!=1 && respuesta!=2) {                                 
            printf("Error, intenta de nuevo\n");
        }
    } while(respuesta!=1 && respuesta!=2);
    if(respuesta==1) {
        return 1; 
    }
    else {
        return 0; 
    }
}

int main() {                                                                    //Función principal
    srand(time(NULL));                       
    crearBaraja();                                                              //Se crea la baraja
    
    Jugador Jugador1, Jugador2; // Declara los dos jugadores
    printf("       .°˖⋆ ℧ 𓃗 .°˖⋆   Poker Texas Hold'em .°˖⋆ ℧ 𓃗 .°˖⋆     \n\n");
    
    for(int i=0; i<52; i=i+1) {                                                 //Reinicia el control de cartas usadas cuando se inicie el programa otra vez
        CartasUso[i]=0;
    }
    Jugador1.mano[0]=CartaAzar();                                               //Reparte las 2 cartas a cada jugador
    Jugador1.mano[1]=CartaAzar();
    Jugador2.mano[0]=CartaAzar();
    Jugador2.mano[1]=CartaAzar();
    
    printf("Cartas del jugador 1: ");
    VerCarta(Jugador1.mano[0]);
    printf(" ");
    VerCarta(Jugador1.mano[1]);
    printf("\n");
    printf("Cartas del jugador 2: ");
    VerCarta(Jugador2.mano[0]);
    printf(" ");
    VerCarta(Jugador2.mano[1]);
    printf("\n\n");
    
    printf(".°˖⋆🂾.°˖⋆ RONDA 1 .°˖⋆🂾.°˖⋆\n");
    Jugador1.sigue=preguntar(1);
    Jugador2.sigue=preguntar(2);
    
    if(Jugador1.sigue==0) {
        printf("\nEl jugador 2 gana :)\n");
        return 0;
    }
    if(Jugador2.sigue==0) {
        printf("\nEl jugador 1 gana :)\n");
        return 0;
    }
  
    printf("\n.°˖⋆🂾.°˖⋆ RONDA 2 .°˖⋆🂾.°˖⋆ \n");
    printf("Cartas del river: ");
    for(int i=0; i<3; i=i+1) {
        River[i]=CartaAzar();
        VerCarta(River[i]);
        printf(" ");
    }
    printf("\n");
    
    Jugador1.sigue=preguntar(1);
    Jugador2.sigue=preguntar(2);
    
    if(Jugador1.sigue==0) {
        printf("\nEl jugador 2 gana :)\n");
        return 0;
    }
    if(Jugador2.sigue==0) {
        printf("\nEl jugador 1 gana :)\n");
        return 0;
    }
   
    printf("\n.°˖⋆🂾.°˖⋆ RONDA 3 .°˖⋆🂾.°˖⋆\n");
    printf("Cartas del river: ");
    River[3]=CartaAzar();
    for(int i=0; i<4; i=i+1) {
        VerCarta(River[i]);
        printf(" ");
    }
    printf("\n");
    
    Jugador1.sigue=preguntar(1);
    Jugador2.sigue=preguntar(2);
    
    if(Jugador1.sigue==0) {
        printf("\nEl jugador 2 gana :)\n");
        return 0;
    }
    if(Jugador2.sigue==0) {
        printf("\nEl jugador 1 gana :)\n");
        return 0;
    }

    printf("\n.°˖⋆🂾.°˖⋆ RONDA 4 .°˖⋆🂾.°˖⋆\n");
    printf("Cartas completas del river: ");
    River[4]=CartaAzar();
    for(int i=0; i<5; i=i+1) {
        VerCarta(River[i]);
        printf(" ");
    }
    printf("\n\n");
    
    int puntosJugador1=evaluarMano(Jugador1, River);
    int puntosJugador2=evaluarMano(Jugador2, River);
    printf("Tabla de puntajes:\nCorrida real=9\n Corrida color=8\n Poker=7\n Casa llena=6\n Color=5\n Corrida=4\n Tercia=3\n Dos pares=2\n Un par=1\n Carta alta=0\n", puntosJugador1, puntosJugador2);
    printf("Puntos: Jugador 1=%d, Jugador 2=%d\n", puntosJugador1, puntosJugador2);

    if(puntosJugador1>puntosJugador2) {
        printf("Gana el jugador 1\n");
    }
    else if(puntosJugador2>puntosJugador1) {
        printf("Gana el jugador 2\n");
    }
    else {                                                                      //Empate
        int altaJugador1=cartaAlta(Jugador1);
        int altaJugador2=cartaAlta(Jugador2);
        printf("Empate en puntos\n");
        if(altaJugador1>altaJugador2) {
            printf("Gana el jugador 1 con carta %d\n", altaJugador1);
        }
        else if(altaJugador2>altaJugador1) {
            printf("Gana el jugador 2 con carta %d\n", altaJugador2);
        }
        else {
            printf("Empate total\n");
        }
    }
    
    return 0;
}
