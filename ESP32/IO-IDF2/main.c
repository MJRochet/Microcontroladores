#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

//#define LED 2
#define BT 17

int display[] = {14, 27, 18, 25, 26, 12, 13};

char number[10][7] ={
    {0, 0, 0, 0, 0, 0, 1}, // 0
    {1, 0, 0, 1, 1, 1, 1}, // 1
    {0, 0, 1, 0, 0, 1, 0}, // 2
    {0, 0, 0, 0, 1, 1, 0}, // 3
    {1, 0, 0, 1, 1, 0, 0}, // 4
    {0, 1, 0, 0, 1, 0, 0}, // 5
    {0, 1, 0, 0, 0, 0, 0}, // 6
    {0, 0, 0, 1, 1, 1, 1}, // 7
    {0, 0, 0, 0, 0, 0, 0}, // 8
    {0, 0, 0, 0, 1, 0, 0}  // 9
};

void init_hw(void);

void app_main()
{
    init_hw();
    int cnt = 0;
    for(int i=0; i<7; i++){
        gpio_set_level(display[i], number[0][i]);
    }

    while(1)
    {
        int state_bt = gpio_get_level(BT);
        for(int i=0; i<7; i++)
        {
            gpio_set_level(display[i], number[0][i]);
        }

        cnt=(state_bt && cnt < 10) ? (cnt + 1) : cnt;
        cnt = cnt > 9 ? 0 : cnt; 
       /*
        printf("%d\n", state_bt);
        
        //if (state_bt) //Use este en combinacion con el pulldown
        if (!state_bt)  //Use este en combinacion con el pullup
        {
            gpio_set_level(LED, 1);
        }
        else
        {
            gpio_set_level(LED, 0);
        }
        /*gpio_set_level(LED, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(LED, 0);
        */
        
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}

void init_hw(void)
{
    /*
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);
    gpio_set_direction(BT, GPIO_MODE_INPUT);

    //gpio_set_pull_mode(BT, GPIO_PULLDOWN_ONLY);
    gpio_set_pull_mode(BT, GPIO_PULLUP_ONLY);
    */

   gpio_config_t io_config;

   io_config.mode = GPIO_MODE_INPUT;
   io_config.pin_bit_mask = (1 << display[0]) |
                            (1 << display[1]) |
                            (1 << display[2]) |
                            (1 << display[3]) |
                            (1 << display[4]) |
                            (1 << display[5]) |
                            (1 << display[6]);
   io_config.pull_down_en = GPIO_PULLDOWN_ONLY;
   io_config.pull_up_en = GPIO_PULLUP_DISABLE;
   io_config.intr_type = GPIO_INTR_DISABLE;
   gpio_config(&io_config);

   io_config.mode = GPIO_MODE_INPUT;
   io_config.pin_bit_mask = (1 << LED);
   io_config.pull_down_en = GPIO_PULLDOWN_DISABLE;
   io_config.pull_up_en = GPIO_PULLUP_DISABLE;
   io_config.intr_type = GPIO_INTR_DISABLE;
   gpio_config(&io_config);



}


