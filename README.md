# Projeto de Microcontrolador RP2040 com Placa BitDogLab

## Descrição da Tarefa
Para consolidar a compreensão dos conceitos relacionados ao uso de interrupções no microcontrolador RP2040 e explorar as funcionalidades da placa de desenvolvimento BitDogLab, propõe-se a seguinte tarefa prática.

## Objetivos
Compreender o funcionamento e a aplicação de interrupções em microcontroladores.

Identificar e corrigir o fenômeno do bouncing em botões por meio de debouncing via software.

Manipular e controlar LEDs comuns e LEDs endereçáveis WS2812.

Fixar o estudo do uso de resistores de pull-up internos em botões de acionamento.

Desenvolver um projeto funcional que combine hardware e software.

## Descrição do Projeto
Neste projeto, utilizamos os seguintes componentes conectados à placa BitDogLab:

Matriz 5x5 de LEDs (endereçáveis) WS2812, conectada à GPIO 7.

LED RGB, com os pinos conectados às GPIOs (11, 12 e 13).

Botão A conectado à GPIO 5.

Botão B conectado à GPIO 6.

## Funcionalidades do Projeto
- O LED vermelho do LED RGB deve piscar continuamente 5 vezes por segundo.

- O botão A deve incrementar o número exibido na matriz de LEDs cada vez que for pressionado.

- O botão B deve decrementar o número exibido na matriz de LEDs cada vez que for pressionado.

- Os LEDs WS2812 devem ser usados para criar efeitos visuais representando números de 0 a 9.

- Formatação fixa: Cada número deve ser exibido na matriz em um formato fixo, como caracteres em estilo digital (ex.: segmentos iluminados que formem o número).
- Alternativamente, é permitido utilizar um estilo criativo, desde que o número seja claramente identificável.

## Requisitos do Projeto
Para o desenvolvimento, devem ser seguidos os seguintes requisitos:

- Uso de interrupções: Todas as funcionalidades relacionadas aos botões devem ser implementadas utilizando rotinas de interrupção (IRQ).

- Debouncing: É obrigatório implementar o tratamento do bouncing dos botões via software.

- Controle de LEDs: O projeto deve incluir o uso de LEDs comuns e LEDs WS2812, demonstrando o domínio de diferentes tipos de controle.

- Organização do código: O código deve estar bem estruturado e comentado para facilitar o entendimento.

## Explicação do Código
Estrutura do Código
O código é dividido nos seguintes arquivos:

- main.c: Contém o código principal do projeto.

- ws2812.h e ws2812.c: Contêm as definições e implementação para o controle dos LEDs WS2812.

- numeros.h: Contém as definições das matrizes que representam os números de 0 a 9.

## Funcionalidades Implementadas
- Piscar LED Vermelho: A função blinkarLedVermelho faz o LED vermelho piscar 5 vezes por segundo.

- Controle de Botões com Debouncing: As funções gpio_irq_handler e debouncing implementam o controle dos botões A e B, com tratamento de bouncing via software.

- Exibição de Números na Matriz de LEDs: A função ligarMatrizLeds exibe números de 0 a 9 na matriz de LEDs WS2812, com cores diferentes para números pares e ímpares.

## Video demonstrativo

https://www.youtube.com/shorts/VomWoGWmlhk

## Autores

- [Davi Moura](https://www.github.com/davims9)

