#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a = 8;
    int *pi;
    double *pd;
    double f = 5.8000000006;

    for(int n = 0; n < 1000000000; n++)
    {
        pi = (int *) malloc(sizeof(int));
        pd = (float *) malloc(sizeof(double));

        free(pi);
        free(pd);
    }


    *pi = a;
    *pd = f;

    printf("\nValor de PI: %d\n",*pi);
    printf("\nValor de PD: %lf\n",*pd);

    free(pi);
    free(pd);
    getchar();
    return 0;
}
