#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

// Definición de estados
#define ESTADO_INIT         0
#define ESTADO_ABRIENDO     1
#define ESTADO_CERRANDO     2
#define ESTADO_CERRADO      3
#define ESTADO_ABIERTO      4
#define ESTADO_EMERGENCIA   5
#define ESTADO_ERROR        6
#define ESTADO_ESPERA       7

// Pines GPIO para entradas y salidas (ajustar según sea necesario)
#define GPIO_LSA 18  // Sensor de límite superior
#define GPIO_LSC 19  // Sensor de límite inferior
#define GPIO_CA  21  // Comando de apertura
#define GPIO_CC  22  // Comando de cierre
#define GPIO_FC  23  // Falla de cierre
#define GPIO_MC  5   // Motor cierre
#define GPIO_MA  17  // Motor apertura
#define GPIO_LED_EMER 16 // LED de emergencia
#define GPIO_LED_MOV 4   // LED de movimiento

// Variables de estado
volatile int ESTADO_ACTUAL = ESTADO_INIT;
volatile int ESTADO_SIGUIENTE = ESTADO_INIT;
volatile int ESTADO_ANTERIOR = ESTADO_INIT;

// Funciones de estado
int Func_ESTADO_INIT();
int Func_ESTADO_ABRIENDO();
int Func_ESTADO_CERRANDO();
int Func_ESTADO_CERRADO();
int Func_ESTADO_ABIERTO();
int Func_ESTADO_EMERGENCIA();
int Func_ESTADO_ERROR();
int Func_ESTADO_ESPERA();

void app_main(void)
{
    // Configuración de pines GPIO
    gpio_config_t io_conf;

    // Configuración de pines de entrada
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1ULL << GPIO_LSA) | (1ULL << GPIO_LSC) | (1ULL << GPIO_CA) | (1ULL << GPIO_CC) | (1ULL << GPIO_FC);
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);

    // Configuración de pines de salida
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << GPIO_MC) | (1ULL << GPIO_MA) | (1ULL << GPIO_LED_EMER) | (1ULL << GPIO_LED_MOV);
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    // Bucle principal
    while (true)
    {
        switch (ESTADO_SIGUIENTE)
        {
            case ESTADO_INIT:
                ESTADO_SIGUIENTE = Func_ESTADO_INIT();
                break;
            case ESTADO_ESPERA:
                ESTADO_SIGUIENTE = Func_ESTADO_ESPERA();
                break;
            case ESTADO_ABIERTO:
                ESTADO_SIGUIENTE = Func_ESTADO_ABIERTO();
                break;
            case ESTADO_CERRADO:
                ESTADO_SIGUIENTE = Func_ESTADO_CERRADO();
                break;
            case ESTADO_ABRIENDO:
                ESTADO_SIGUIENTE = Func_ESTADO_ABRIENDO();
                break;
            case ESTADO_CERRANDO:
                ESTADO_SIGUIENTE = Func_ESTADO_CERRANDO();
                break;
            case ESTADO_ERROR:
                ESTADO_SIGUIENTE = Func_ESTADO_ERROR();
                break;
            case ESTADO_EMERGENCIA:
                ESTADO_SIGUIENTE = Func_ESTADO_EMERGENCIA();
                break;
            default:
                ESTADO_SIGUIENTE = Func_ESTADO_ERROR();
                break;
        }
        vTaskDelay(pdMS_TO_TICKS(10)); // Pequeño retraso para evitar el uso intensivo de la CPU
    }
}

int Func_ESTADO_INIT()
{
    // Estado de inicialización: preparar el sistema
    ESTADO_ANTERIOR = ESTADO_ACTUAL;
    ESTADO_ACTUAL = ESTADO_INIT;

    // Configuración inicial de salidas
    gpio_set_level(GPIO_LED_EMER, 0);
    gpio_set_level(GPIO_LED_MOV, 0);
    gpio_set_level(GPIO_MA, 0);
    gpio_set_level(GPIO_MC, 0);

    return ESTADO_ESPERA;
}

int Func_ESTADO_ABRIENDO()
{
    // Estado de apertura
    ESTADO_ANTERIOR = ESTADO_ACTUAL;
    ESTADO_ACTUAL = ESTADO_ABRIENDO;

    gpio_set_level(GPIO_LED_MOV, 1);
    gpio_set_level(GPIO_MA, 1);
    gpio_set_level(GPIO_MC, 0);

    while (true)
    {
        if (gpio_get_level(GPIO_LSA) == 1)
        {
            return ESTADO_ABIERTO;
        }
        if (gpio_get_level(GPIO_FC) == 1)
        {
            return ESTADO_EMERGENCIA;
        }
        if (gpio_get_level(GPIO_CC) == 1)
        {
            return ESTADO_CERRANDO;
        }
        // Añadir otras condiciones de salida si es necesario
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

int Func_ESTADO_CERRANDO()
{
    // Estado de cierre
    ESTADO_ANTERIOR = ESTADO_ACTUAL;
    ESTADO_ACTUAL = ESTADO_CERRANDO;

    gpio_set_level(GPIO_LED_MOV, 1);
    gpio_set_level(GPIO_MA, 0);
    gpio_set_level(GPIO_MC, 1);

    while (true)
    {
        if (gpio_get_level(GPIO_LSC) == 1)
        {
            return ESTADO_CERRADO;
        }
        if (gpio_get_level(GPIO_FC) == 1)
        {
            return ESTADO_EMERGENCIA;
        }
        if (gpio_get_level(GPIO_CA) == 1)
        {
            return ESTADO_ABRIENDO;
        }
        // Añadir otras condiciones de salida si es necesario
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

int Func_ESTADO_CERRADO()
{
    // Estado cerrado
    ESTADO_ANTERIOR = ESTADO_ACTUAL;
    ESTADO_ACTUAL = ESTADO_CERRADO;

    gpio_set_level(GPIO_LED_MOV, 0);
    gpio_set_level(GPIO_MA, 0);
    gpio_set_level(GPIO_MC, 0);

    return ESTADO_ESPERA;
}

int Func_ESTADO_ABIERTO()
{
    // Estado abierto
    ESTADO_ANTERIOR = ESTADO_ACTUAL;
    ESTADO_ACTUAL = ESTADO_ABIERTO;

    gpio_set_level(GPIO_LED_MOV, 0);
    gpio_set_level(GPIO_MA, 0);
    gpio_set_level(GPIO_MC, 0);

    return ESTADO_ESPERA;
}

int Func_ESTADO_EMERGENCIA()
{
    // Estado de emergencia
    ESTADO_ANTERIOR = ESTADO_ACTUAL;
    ESTADO_ACTUAL = ESTADO_EMERGENCIA;

    gpio_set_level(GPIO_LED_EMER, 1);
    gpio_set_level(GPIO_LED_MOV, 0);
    gpio_set_level(GPIO_MA, 0);
    gpio_set_level(GPIO_MC, 0);

    while (true)
    {
        // Implementar lógica de emergencia, como resetear sistema o esperar intervención
        // if (/* condición para salir de emergencia */) {
        //     return ESTADO_ESPERA;
        // }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

int Func_ESTADO_ERROR()
{
    // Estado de error
    ESTADO_ANTERIOR = ESTADO_ACTUAL;
    ESTADO_ACTUAL = ESTADO_ERROR;

    gpio_set_level(GPIO_LED_EMER, 1);
    gpio_set_level(GPIO_LED_MOV, 0);
    gpio_set_level(GPIO_MA, 0);
    gpio_set_level(GPIO_MC, 0);

    // Implementar lógica de manejo de errores
    return ESTADO_ESPERA;
}

int Func_ESTADO_ESPERA()
{
    // Estado de espera
    ESTADO_ANTERIOR = ESTADO_ACTUAL;
    ESTADO_ACTUAL = ESTADO_ESPERA;

    gpio_set_level(GPIO_LED_EMER, 0);
    gpio_set_level(GPIO_LED_MOV, 0);
    gpio_set_level(GPIO_MA, 0);
    gpio_set_level(GPIO_MC, 0);

    while (true)
    {
        if (gpio_get_level(GPIO_LSC) == 0 && gpio_get_level(GPIO_LSA) == 0 && gpio_get_level(GPIO_FC) == 0)
        {
            return ESTADO_CERRANDO;
        }

        if (gpio_get_level(GPIO_CA) == 1 && gpio_get_level(GPIO_FC) == 0 && gpio_get_level(GPIO_LSA) == 0)
        {
            return ESTADO_ABRIENDO;
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}






