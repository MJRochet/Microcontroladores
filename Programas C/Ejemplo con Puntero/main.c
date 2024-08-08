#include <stdio.h>
#include <stdlib.h>

int main()
{
    int v1 = 34;
    int v2 = 100;

    int *ptrint;
    int *ptrint2;

    //ptrint = &v1;
    ptrint = &v2;

    ptrint2 = ptrint++;

    printf("Valor en Ptrint2: %d\n", *ptrint2);

    //printf("Dimencion de v1: %d\n", sizeof(v1));
    //printf("Dimencion de ptr: %d\n", sizeof(ptrint));

    printf("Direccion de memoria de v1 = %p\n", &v1);
    printf("Direccion de memoria de v2 = %p\n", &v2);

    ptrint = &v2;

    return 0;
}
