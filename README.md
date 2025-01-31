# Projeto: Controle de LEDs com Temporização e Botão

Descrição

Este projeto utiliza um Raspberry Pi Pico para controlar três LEDs (vermelho, azul e verde) de forma sequencial com temporização. O acionamento ocorre ao pressionar um botão (pushbutton), ativando todos os LEDs simultaneamente. A cada 3 segundos, um LED é desligado seguindo a ordem: azul → vermelho → verde. Após o último LED apagar, o botão pode ser pressionado novamente para reiniciar o ciclo.

Componentes Utilizados

Microcontrolador: Raspberry Pi Pico

LEDs: Vermelho, Azul e Verde

Resistores: 330Ω para cada LED

Botão (pushbutton): Utilizado para iniciar a sequência

Funcionalidades

Controle por botão: O ciclo só pode ser ativado após a finalização completa do desligamento dos LEDs.

Temporização: Uso de add_alarm_in_ms() para alternar estados a cada 3 segundos.

Debounce: Implementação de uma rotina para evitar leituras errôneas do botão.

Estrutura do Código

Definição dos pinos dos LEDs e botão.

Função turn_off_callback(): Responsável por desligar os LEDs gradualmente.

Função is_button_pressed(): Implementa um mecanismo de debounce para evitar múltiplas ativações indesejadas.

Loop principal (main()):

Aguarda a pressão do botão.

Liga todos os LEDs e inicia o temporizador para desligá-los em sequência.

Esquemático de Ligação

LEDs:

Vermelho: GPIO 12

Azul: GPIO 11

Verde: GPIO 13

Botão: GPIO 5

Como Executar

Compilar o código para o Raspberry Pi Pico.

Gravar o binário na memória do microcontrolador.

Conectar os componentes conforme o esquemático.

Pressionar o botão para iniciar a sequência.
