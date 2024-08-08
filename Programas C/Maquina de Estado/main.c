#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define
#define

#define ESTADO_INIT         0
#define ESTADO_ABRIENDO     1
#define ESTADO_CERRANDO     2
#define ESTADO_CERRADO      3
#define ESTADO_ABIERTO      4
#define ESTADO_EMERGENCIA   5
#define ESTADO_ERROR        6
#define ESTADO_ESPERA       7

int Func_ESTADO_INIT();
int Func_ESTADO_ABRIENDO();
int Func_ESTADO_CERRANDO();
int Func_ESTADO_CERRADO();
int Func_ESTADO_ABIERTO();
int Func_ESTADO_EMERGENCIA();
int Func_ESTADO_ERROR();
int Func_ESTADO_ESPERA();

volatile int ESTADO_ACTUAL = ESTADO_INIT;
volatile int ESTADO_SIGUIENTE = ESTADO_INIT;
volatile int ESTADO_ANTERIOR = ESTADO_INIT;
volatile unsigned int TimeCa = 0;

volatile struct INPUTS
{
    unsigned int LSA:1;
    unsigned int LSC:1;
    unsigned int CA:1;
    unsigned int CC:1;
    unsigned int FC:1;
}inputs;

volatile struct OUTPUTS
{
    unsigned int LSA:1;
    unsigned int LSC:1;
    unsigned int CA:1;
    unsigned int CC:1;
    unsigned int FC:1;
}outputs;

int main()
{
    for(;;)
    {
        if(ESTADO_SIGUIENTE == ESTADO_INIT)
        {
            ESTADO_SIGUIENTE == Func_ESTADO_INIT();
        }
        if(ESTADO_SIGUIENTE == ESTADO_ESPERA)
        {
            ESTADO_SIGUIENTE == Func_ESTADO_ESPERA();
        }
        if(ESTADO_SIGUIENTE == ESTADO_ABIERTO)
        {
            ESTADO_SIGUIENTE == Func_ESTADO_ABIERTO();
        }
        if(ESTADO_SIGUIENTE == ESTADO_ABRIENDO)
        {
            ESTADO_SIGUIENTE == Func_ESTADO_ABRIENDO();
        }
        if(ESTADO_SIGUIENTE == ESTADO_CERRADO)
        {
            ESTADO_SIGUIENTE == Func_ESTADO_CERRADO();
        }
        if(ESTADO_SIGUIENTE == ESTADO_CERRANDO)
        {
            ESTADO_SIGUIENTE == Func_ESTADO_CERRANDO();
        }
        if(ESTADO_SIGUIENTE == ESTADO_ERROR)
        {
            ESTADO_SIGUIENTE == Func_ESTADO_ERROR();
        }
        if(ESTADO_SIGUIENTE == ESTADO_EMERGENCIA)
        {
            ESTADO_SIGUIENTE == Func_ESTADO_EMERGENCIA();
        }
    }
}

int Func_ESTADO_INIT()
{
    for(;;)
    {
        return ESTADO_ESPERA
    }
}
int Func_ESTADO_ABRIENDO()
{
    for(;;)
    {

    }
}
int Func_ESTADO_CERRANDO()
{
    //ACTUALIZAR VALORES DE ESTADO
    ESTADO_ANTERIOR = ESTADO_ACTUAL;
    ESTADO_ACTUAL = ESTADO_ESPERA;

    outputs.LED_EMER = OFF;
    outputs.LED_MOV = ON;
    outputs.MA = FALSE;
    //PONER TIEMPO DE ESPERA 10ms A 25ms si es relay
    outputs.MC = TRUE;

    for(;;)
    {
        if(inputs.LSC == TRUE)
        {
            return ESTADO_CERRADO;
        }

        //todo verificar la FC y salir a emergencia

        // verificar el tiempo contador TimeCa

        // verificar cambio de giro
        // detener el motor y esperar 3 seg para cambiar giro
    }
}
int Func_ESTADO_CERRADO()
{
     //ACTUALIZAR VALORES DE ESTADO
    ESTADO_ANTERIOR = ESTADO_ACTUAL;
    ESTADO_ACTUAL = ESTADO_CERRADO;

    outputs.LED_EMER = OFF;
    outputs.LED_MOV = OFF;
    outputs.MA = FALSE;
    //PONER TIEMPO DE ESPERA 10ms A 25ms si es relay
    outputs.MC = FALSE;
    // ESPERAR PARE DE MOTOR

    for(;;)
    {
        return ESTADO_ESPERA;
    }
}
int Func_ESTADO_ABIERTO()
{
    for(;;)
    {

    }
}
int Func_ESTADO_EMERGENCIA()
{
    for(;;)
    {

    }
}
int Func_ESTADO_ERROR()
{
    for(;;)
    {

    }
}
int Func_ESTADO_ESPERA()
{
    //ACTUALIZAR VALORES DE ESTADO
    ESTADO_ANTERIOR = ESTADO_ACTUAL;
    ESTADO_ACTUAL = ESTADO_ESPERA;

    //VALORES DE SALIDA
    outputs.LED_EMER = OFF;
    outputs.LED_MOV = OFF;
    outputs.MA = OFF;
    outputs.MC = OFF;


    for(;;)
    {
        if(inputs.LSC == FALSE && inputs.LSA == FALSE && inputs.FC == FALSE)
        {
            return ESTADO_CERRANDO
        }
        if(inputs.CA == TRUE && inputs.FC == FALSE && inputs.LSA == FALSE)
        {
            return ESTADO_ABRIENDO
        }
    }
}
