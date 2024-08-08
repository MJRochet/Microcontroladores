#include <stdio.h>
#include <stdlib.h>

int main()
{
    //se apunta con un numero de 64 bits
    // * Operador de indireccion
    // & Operador de direccion

    int i = 1492;
    int *ptr1;
    ptr1 = &i;

    printf("\ni vale: %p", ptr1); //imprime el valor 1492
    printf("\ni vale: %p", &i); // imprime la direccion de memoria que apunta el puntero
    printf("\ni vale: %d", *ptr1); //


    //printf("Dimension de ptr: %d", sizeof(ptr1));

    return 0;
}
