#include <stdio.h>
#include <stdlib.h>

int main()
{
    // **1. Declarar Variables**
    int var = 10;      // Variable entera
    int *ptr;          // Puntero a entero

    // **2. Asignar Direcciones**
    ptr = &var;        // Asignar la dirección de var a ptr

    // **3. Acceder y Modificar Valores**
    printf("Valor de var: %d\n", var);                  // Valor original de var
    printf("Dirección de var: %p\n", (void*)&var);      // Dirección de var
    printf("Valor de ptr (dirección de var): %p\n", (void*)ptr); // Dirección almacenada en ptr
    printf("Valor al que apunta ptr: %d\n", *ptr);      // Valor al que apunta ptr

    // Modificar valor usando puntero
    *ptr = 20;
    printf("Nuevo valor de var (modificado a través de ptr): %d\n", var);

    // **4. Punteros y Arreglos**
    int arr[3] = {1, 2, 3}; // Arreglo de enteros
    int *arr_ptr = arr;     // Puntero al primer elemento del arreglo

    printf("Elementos del arreglo usando punteros:\n");
    for (int i = 0; i < 3; i++) {
        printf("arr[%d] = %d\n", i, *(arr_ptr + i)); // Acceder a elementos usando punteros
    }

    // Modificar elementos del arreglo usando punteros
    *(arr_ptr + 1) = 42;
    printf("Nuevo valor de arr[1] (modificado a través de puntero): %d\n", arr[1]);

    return 0;
}

