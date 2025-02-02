#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/irq.h"
#include "ws2812.pio.h"
#include "numeros.h"

#define IS_RGBW false
#define NUM_PIXELS 25
#define WS2812_PIN 7
#define LED_PIN_RED 13
#define BUTTON_A 5
#define BUTTON_B 6
#define DEBOUNCE_TIME_MS 200 // Tempo de debounce

int contador_numero_a_exibir = 0;
absolute_time_t last_interrupt_time_a = {0};
absolute_time_t last_interrupt_time_b = {0};

// Buffer para armazenar quais LEDs estão ligados matriz 5x5
bool led_buffer[NUM_PIXELS];
bool* numeros[10] = {numeroZero, numeroUm, numeroDois, numeroTres, numeroQuatro, numeroCinco, numeroSeis, numeroSete, numeroOito, numeroNove};

static inline void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t)(r) << 8) | ((uint32_t)(g) << 16) | (uint32_t)(b);
}

bool debouncing(absolute_time_t* last_interrupt_time) {
    absolute_time_t current_time = get_absolute_time();
    if (absolute_time_diff_us(*last_interrupt_time, current_time) < DEBOUNCE_TIME_MS * 1000) {
        return false;
    } else {
        *last_interrupt_time = current_time;
        return true;
    }
}

//Função para quando pressionar botões A ou B
void gpio_irq_handler(uint gpio, uint32_t events) {
    if (gpio == BUTTON_A && debouncing(&last_interrupt_time_a)) {
        contador_numero_a_exibir++;
        if (contador_numero_a_exibir > 9) {
            contador_numero_a_exibir = 0;
        }
        printf("Botão A pressionado: %d\n", contador_numero_a_exibir);
    } else if (gpio == BUTTON_B && debouncing(&last_interrupt_time_b)) {
        contador_numero_a_exibir--;
        if (contador_numero_a_exibir < 0) {
            contador_numero_a_exibir = 9;
        }
        printf("Botão B pressionado: %d\n", contador_numero_a_exibir);
    }
}

//Função para ligar os leds de acordo com o numero chamado
void ligarMatrizLeds(int numExibir) {
    uint8_t r = 0;
    uint8_t g = (numExibir % 2 != 0) ? 255 : 0;
    uint8_t b = (numExibir % 2 == 0) ? 255 : 0;

    uint32_t color = urgb_u32(r, g, b);

    for (int j = 0; j < 25; j++) {
        led_buffer[j] = numeros[numExibir][j];
    }

    for (int i = 0; i < NUM_PIXELS; i++) {   
        if (led_buffer[i]) {
            put_pixel(color);
        } else {
            put_pixel(0);
        }
    }
}

void blinkarLedVermelho() {
    static absolute_time_t last_blink_time = {0};
    static bool led_on = false;

    absolute_time_t current_time = get_absolute_time();
    if (absolute_time_diff_us(last_blink_time, current_time) >= 1000000 / 5) {
        last_blink_time = current_time;
        led_on = !led_on;
        gpio_put(LED_PIN_RED, led_on);
    }
    sleep_ms(100);
}

int main() {   
    stdio_init_all();

    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);

    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);

    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    printf("Sistema inicializado. Pressione os botões para testar.\n");

    while (1) {   
        ligarMatrizLeds(contador_numero_a_exibir);
        blinkarLedVermelho();
    }

    return 0;
}
