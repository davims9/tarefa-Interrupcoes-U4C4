#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"
#include "numeros.h"

#define IS_RGBW false
#define NUM_PIXELS 25
#define WS2812_PIN 7
#define tempo 400

int contador_numero_a_exibir = 0;

const uint led_pin_red   = 13; //Led rgb vermelho
const uint button_A = 5; // Botão A = 5
const uint button_B = 6; // Botão B = 6

// Variável global para armazenar a cor (Entre 0 e 255 para intensidade)
uint8_t led_r = 0; // Intensidade do vermelho
uint8_t led_g = 0; // Intensidade do verde
uint8_t led_b = 5; // Intensidade do azul

// Buffer para armazenar quais LEDs estão ligados matriz 5x5
bool led_buffer[NUM_PIXELS] = {
    1, 0, 0, 0, 1, 
    0, 0, 0, 0, 0, 
    0, 0, 1, 0, 0, 
    0, 0, 0, 0, 0, 
    1, 0, 0, 0, 1
};

bool* numeros[10] = {numeroZero, numeroUm, numeroDois, numeroTres, numeroQuatro, numeroCinco, numeroSeis, numeroSete, numeroOito, numeroNove};

static inline void put_pixel(uint32_t pixel_grb)
{
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b)
{
    return ((uint32_t)(r) << 8) | ((uint32_t)(g) << 16) | (uint32_t)(b);
}



void set_one_led(uint8_t r, uint8_t g, uint8_t b, int numExibir)
{
    // Define a cor com base nos parâmetros fornecidos
    uint32_t color = urgb_u32(r, g, b);
    
    for (int j = 0; j < 25; j++) {
    led_buffer[j] = numeros[numExibir][j];
    }

    // Define todos os LEDs com a cor especificada
    for (int i = 0; i < NUM_PIXELS; i++)
    {   
             
        if (led_buffer[i])
        {
            put_pixel(color); // Liga o LED com um no buffer
        }
        else
        {
            put_pixel(0);  // Desliga os LEDs com zero no buffer
        }
    }
}


void ligarMatrizLeds(){
    //implementar a logica de exibição do numero na matriz, utilize o contador "contador_numero_a_exibir"
}

void blinkarLedVermelho(){
    //implementar a logica do LED Vermelho

}

bool debouncing(){
//implementar o debouncing

}

void gpio_irq_handler_buttonA(uint gpio, uint32_t events)
{
    //implementar a funçao do botao A
    if (debouncing()){

    }
    
}

void gpio_irq_handler_buttonB(uint gpio, uint32_t events)
{
    //implementar a funçao do botao B
    if (debouncing()){

    }
}

int main()
{   
    stdio_init_all();

    int contador = 0;
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);

    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

    gpio_init(led_pin_red);              // Inicializa o pino do LED
    gpio_set_dir(led_pin_red, GPIO_OUT); // Configura o pino como saída
    
    gpio_init(button_A);
    gpio_set_dir(button_A, GPIO_IN); // Configura o pino como entrada
    gpio_pull_up(button_A);

    gpio_init(button_B);
    gpio_set_dir(button_B, GPIO_IN); // Configura o pino como entrada
    gpio_pull_up(button_B);

    gpio_set_irq_enabled_with_callback(button_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler_buttonA);
    gpio_set_irq_enabled_with_callback(button_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler_buttonB);

    while (1)
    {   
        ligarMatrizLeds();
        blinkarLedVermelho();        
    }

    return 0;
}
