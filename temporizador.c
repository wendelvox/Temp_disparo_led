#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

const uint LED_R_PIN = 11;
const uint LED_B_PIN = 12;
const uint LED_G_PIN = 13;
const uint BUTTON_PIN = 5;

bool led_on = false;
bool led_active = false;

absolute_time_t turn_off_time;

int64_t turn_of_callback(alarm_id_t id, void *user_data){
    // Desliga o Led
    gpio_put(LED_R_PIN, false);
    led_active = false;
    return 0; 
}

int main(){
    // Inicializar comunicação padrão
    stdio_init_all();

    gpio_init(LED_R_PIN);
    gpio_set_dir(LED_R_PIN, GPIO_OUT);
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    while(1){

        if (gpio_get(BUTTON_PIN) == 0 && !led_active){
            sleep_ms(50);
            if (gpio_get(BUTTON_PIN) == 0){
                gpio_put(LED_R_PIN, true);
                led_active;

                add_alarm_in_ms(3000, turn_of_callback, NULL, false);
            }
        }
        sleep_ms(10);

    }
}



