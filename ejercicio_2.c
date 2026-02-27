#include <stdio.h>
#include <string.h>

// 1. Definición de la estructura pizza
typedef struct {
    float radio;
    int num_toppings;
    char ingredientes[100];
    float precio_base;
    float precio_final;
    int emparejada; 
} Pizza;

int main() {
    int num_pizzas;
    float total_pagar = 0.0;

    printf("--- Bienvenido a la Pizzería de Copilco ---\n");
    do{
    printf("¿Cuántas pizzas vas a ordenar? ");
    scanf("%d", &num_pizzas);
    if (num_pizzas<0)
        printf("Error: Ingrese una cantidad real de pizzas ---\n");
    }
    while (num_pizzas<0);
    
    // 2. Arreglo para almacenar la orden
    Pizza orden[num_pizzas];

    // 3. Captura de datos de cada pizza
    for (int i = 0; i < num_pizzas; i++) {
        printf("\n--- Ingresando datos de la Pizza %d ---\n", i + 1);
        
        do{
        printf("Ingresa el tamaño (radio en cm): ");
        scanf("%f", &orden[i].radio);  //Lee el radio de la pizza 
        if (orden[i].radio<=0)
        printf("Error: Ingrese una cantidad real de radio ---\n");
    }
    while (orden[i].radio<=0);
       
        do{
        printf("¿Cuántos toppings extra llevará?: ");
        scanf("%d", &orden[i].num_toppings); //Lee el número de toppings extra
        if (orden[i].num_toppings<0)
        printf("Error: No puedes agregar toppings negativos ---\n");
    }
    while (orden[i].num_toppings<0);
        
        // Limpiar el buffer del teclado antes de leer la cadena de texto para evitar problemas con fgets
        while (getchar() != '\n');
        
        printf("Escribe los ingredientes (Ej. Queso, Pepperoni): ");
        fgets(orden[i].ingredientes, 100, stdin); //Lee los ingredientes de la pizza, incluyendo espacios, y los almacena en el arreglo de caracteres 'ingredientes' de la estructura Pizza.
        // Eliminar el salto de línea que guarda fgets
        orden[i].ingredientes[strcspn(orden[i].ingredientes, "\n")] = 0;

        // Cálculo del precio (Ejemplo: $3 por cm de radio + $15 por topping)
        orden[i].precio_base = (orden[i].radio * 3.0) + (orden[i].num_toppings * 15.0);
        orden[i].precio_final = orden[i].precio_base;
        orden[i].emparejada = 0; // Inicializamos indicando que no tiene promo de 2x1 aún
    }

    // 4. Lógica de la Promoción 2x1 (Mismo tamaño)
    for (int i = 0; i < num_pizzas; i++) {
        if (orden[i].emparejada == 0) { // Si esta pizza aún no tiene pareja
            for (int j = i + 1; j < num_pizzas; j++) {
                // Buscamos otra pizza que no tenga pareja y que tenga el mismo radio
                if (orden[j].emparejada == 0 && orden[i].radio == orden[j].radio) {
                    
                    orden[i].emparejada = 1;
                    orden[j].emparejada = 1;
                    
                    // En un 2x1, se cobra la más cara y la más barata es gratis
                    if (orden[i].precio_base >= orden[j].precio_base) {
                        orden[j].precio_final = 0.0; 
                    } else {
                        orden[i].precio_final = 0.0;
                    }
                    break; // Terminamos de buscarle pareja a la pizza 'i'
                }
            }
        }
    }

    // 5. Impresión del Ticket
    printf("\n========================================\n");
    printf("           TICKET DE COMPRA             \n");
    printf("          PIZZERÍA DE COPILCO           \n");
    printf("========================================\n");
    
    for (int i = 0; i < num_pizzas; i++) {
        printf("Pizza %d (Radio: %.2f cm)\n", i + 1, orden[i].radio);
        printf("  Ingredientes: %s\n", orden[i].ingredientes);
        printf("  Toppings: %d\n", orden[i].num_toppings);
        
        if (orden[i].precio_final == 0.0) {
            printf("  Precio: $%.2f (¡PROMO 2x1! GRATIS)\n", orden[i].precio_base);
        } else if (orden[i].emparejada == 1) {
            printf("  Precio: $%.2f (Aplica Promo 2x1)\n", orden[i].precio_final);
            total_pagar += orden[i].precio_final;
        } else {
            printf("  Precio: $%.2f\n", orden[i].precio_final);
            total_pagar += orden[i].precio_final;
        }
        printf("----------------------------------------\n");
    }
    
    printf("TOTAL A PAGAR: $%.2f\n", total_pagar);
    printf("========================================\n");

    return 0;
