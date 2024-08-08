#include <stdio.h>
#include <stdlib.h>

void intercambiar(int *a, int *b)
{
    printf("\nIntercambiando:\n");
    printf("Direccion de a: %p, valor de a: %d\n", (void*)a, *a);
    printf("Direccion de b: %p, valor de b: %d\n", (void*)b, *b);

    int temp = *a;  // Se guardar el valor de "a" en "temp"
    *a = *b;        // Se asigna el valor de "b" a "a"
    *b = temp;      // Se asigna el valor de "temp" a "b" (que es el valor original de "a")

    printf("Resultado del intercambio:\n");
    printf("Valor de a: %d, valor de b: %d\n", *a, *b);
}

int main()
{
    int x = 5;
    int y = 10;
    int z = 2;

    printf("\nAntes del intercambio:\n");
    printf("x = %d \ny = %d \nz = %d\n", x, y, z);
    printf("Direccion de x: %p\n", (void*)&x);
    printf("Direccion de y: %p\n", (void*)&y);
    printf("Direccion de z: %p\n", (void*)&z);

    intercambiar(&x, &y); // Llamar a la función de intercambio

    printf("\nDespues del intercambio:\n");
    printf("x = %d, y = %d, z = %d\n", x, y, z);
    printf("Direccion de x: %p\n", (void*)&x);
    printf("Direccion de y: %p\n", (void*)&y);
    printf("Direccion de z: %p\n", (void*)&z);

    int suma_x = x + z;
    int suma_y = y + z;

    printf("\nDespues de sumar z a los valores intercambiados:\n");
    printf("x + z = %d \ny + z = %d\n", suma_x, suma_y);
    printf("Direccion de x + z: %p\n", (void*)&suma_x);
    printf("Direccion de y + z: %p\n", (void*)&suma_y);

    return 0;
}

