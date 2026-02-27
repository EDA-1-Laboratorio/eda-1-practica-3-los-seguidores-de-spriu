#include <stdio.h>
#include <math.h>

typedef struct { // Ayuda a no escribir todo el tiempo: struct circulo.
    float x;
    float y;
    float radio;
} Circulo;

float calcular_distancia(Circulo c1, Circulo c2) {    // Esta funcion calcula la distancia entre los centros de los dos circulos:
    return sqrt(pow(c2.x-c1.x, 2)+pow(c2.y-c1.y, 2)); // Distancia entre el circulo 1 y el circulo 2.
}

int intersectan(Circulo c1, Circulo c2) {
    float d=calcular_distancia(c1, c2);
    float mayor; // Obtendrá el radio del circulo mas grande para poder tener dos casos.
    
    if(c1.radio>c2.radio) {
        mayor=c1.radio;
    }
    else if (c2.radio>c1.radio) {
        mayor=c2.radio;
    } else {
        mayor=c1.radio;
    }
    
    if (d<=mayor) { /* En este caso se analiza que un centro de un circulo se encuentre dentro del otro, inclusive si ese centro toca el
                       perimetro del otro circulo, analizando que estos dos se intersecten, ya que puede haber el caso de que un circulo 
                       pequeño dentro del otro, no se intersecte. */
    
        if (d>=fabs(c1.radio-c2.radio)) {
            return 1; // Caso donde si se intersectan.
        }
        else {
            return 0; //Caso donde no se intersectan.
        }
    }
    else { /* En este caso se analiza que un centro de un circulo se encuentre fuera del otro, analizando que estos dos se intersecten 
              ya que pueden estar muy alejados uno del otro. */
      
        if (d<=c1.radio+c2.radio) {
            return 1; // Caso donde si se intersectan.
        }
        else {
            return 0; // Caso donde no se intersectan.
        }
    }

}

int main() {

    Circulo c1, c2;

    printf("Ingrese los datos del circulo 1:\n\nCirculo 1, x: ");
    scanf("%f", &c1.x);
    printf("\nCirculo 1, y: ");
    scanf("%f", &c1.y);
    printf("\nCirculo 1, radio: ");
    do {
        scanf("%f", &c1.radio);
        if (c1.radio<=0) { // Es incorrecto mencionar radios con radio menor o igual a cero.
            printf("\nMatematicamente y geometricamente no existen circulos con radio menor o igual a cero. Vuelve a intentarlo. Circulo 1, radio: ");
        }
    }while (c1.radio<=0); // Lo incorpore para que solo acepte radios mayores a 0 y no te saque del ejecutable si te equivocas.
    
    printf("\n\nIngrese los datos del circulo 2:\n\nCirculo 2, x: ");
    scanf("%f", &c2.x);
    printf("\nCirculo 2, y: ");
    scanf("%f", &c2.y);
    printf("\nCirculo 2, radio: ");
    do {
        scanf("%f", &c2.radio);
        if (c2.radio<=0) { // Es incorrecto mencionar radios con radio menor o igual a cero.
            printf("\nMatematicamente y geometricamente no existen circulos con radio menor o igual a 0. Vuelve a intentarlo. Circulo 2, radio: ");
        }
    }while (c2.radio<=0); // Lo incorpore para que solo acepte radios mayores a 0 y no te saque del ejecutable si te equivocas.

    if(intersectan(c1, c2)) // Resultados :D
        printf("\nLos circulos SI se intersectan :D");
    else
        printf("\nLos circulos NO se intersectan :(");

    return 0;
}
