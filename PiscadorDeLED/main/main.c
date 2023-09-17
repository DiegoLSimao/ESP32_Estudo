/* Projeto de estudo da nova IDE Espressif
 *
 * Autor: Diego de Lima Simão
 * Data: 17/09/2023
 *
 * Este projeto visa somente piscar o led on board da placa devkit V1,
 * utilizando a nova IDE espressif Versão: 2.9.1
 */


//*** Includes
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"



//*** Definições
#define LED_ONBOARD 2 // Define GPIO 2 como pino do LED

//*** Constantes
const char* TAG = "Piscador de LED"; // Apenas uma tag com nome do projeto caso queira usar no log

//*** Variáveis globais
char led_Status = 0;

//***Protótipos de funções
void ConfigurarLed(void);
void PiscarLed(void);
void Delay_ms(int);


//*** Função principal
void app_main(void)
{
	ConfigurarLed();
	int delay = 1000;

	//*** loop infinito
    while (1)
    {
        PiscarLed();
        Delay_ms(delay);

        //*** Controle para acelerar a piscada do led em 10 ms a cada ciclo
        if(delay > 10) delay = delay -10;
        else		delay = 1000;

    }
}


//***Desenvolvimento das funções
void ConfigurarLed()
{
    ESP_LOGI(__func__, "Configura pino 2 como saida!");// Imprime log que passou pela configuração do led

    gpio_reset_pin(LED_ONBOARD);	// faz o reset do pino 2 usdo no led onboard
    gpio_set_direction(LED_ONBOARD, GPIO_MODE_OUTPUT); // define pino 2 como saída para poder controlar o led
}

void PiscarLed()
{
	led_Status = !led_Status;	// inverte status do led 1= ligado ,0=desligado
	gpio_set_level(LED_ONBOARD, led_Status);
	ESP_LOGI(__func__, "Status do LED: %s!", led_Status == 1 ? "Ligado" : "Desligado");
}

void Delay_ms(int ms)
{
	vTaskDelay(ms / portTICK_PERIOD_MS); // Função com nome amigavel para controlar o delay de alternancia do led, parametro recebido em ms.
}
