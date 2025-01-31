#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

// Definição dos pinos
const uint LED_R_PIN = 12;
const uint LED_B_PIN = 11;
const uint LED_G_PIN = 13;
const uint BUTTON_PIN = 5;

bool led_active = false; // Indica se o ciclo está ativo
uint8_t led_state = 0;   // Controla o estado do LED

// Função de callback para desligar LEDs gradualmente
int64_t turn_off_callback(alarm_id_t id, void *user_data) {    

    if (led_state == 2) {
        gpio_put(LED_B_PIN, 0); // Desliga o LED azul
        led_state = 1;
        add_alarm_in_ms(3000, turn_off_callback, NULL, false);
    } else if (led_state == 1) {
        gpio_put(LED_R_PIN, 0); // Desliga o LED verde
        led_state = 0;
        add_alarm_in_ms(3000, turn_off_callback, NULL, false);
    } else {
        gpio_put(LED_G_PIN, 0); // Desliga o LED vermelho
        led_active = false;      // Libera o botão para novo ciclo
    }
    return 0;
}

// Função de debounce e verificação do botão
bool is_button_pressed() {
    if (gpio_get(BUTTON_PIN) == 0) {
        sleep_ms(50); // Pequeno atraso para debounce
        if (gpio_get(BUTTON_PIN) == 0) { // Confirma o estado do botão
            while (gpio_get(BUTTON_PIN) == 0); // Aguarda soltar o botão
            return true;
        }
    }
    return false;
}

int main() {
    stdio_init_all();

    // Inicialização dos LEDs
    gpio_init(LED_R_PIN);
    gpio_set_dir(LED_R_PIN, GPIO_OUT);
    gpio_init(LED_B_PIN);
    gpio_set_dir(LED_B_PIN, GPIO_OUT);
    gpio_init(LED_G_PIN);
    gpio_set_dir(LED_G_PIN, GPIO_OUT);

    // Inicialização do botão
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    while (1) {
        if (!led_active && is_button_pressed()) {
            // Inicia a sequência de LEDs
            gpio_put(LED_R_PIN, 1);
            gpio_put(LED_B_PIN, 1);
            gpio_put(LED_G_PIN, 1);
           
            led_active = true;
            led_state = 2;

            // Inicia o temporizador para desligar os LEDs
            add_alarm_in_ms(3000, turn_off_callback, NULL, false);
        }
        sleep_ms(10);
    }
}
