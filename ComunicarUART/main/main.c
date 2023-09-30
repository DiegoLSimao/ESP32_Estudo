#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include <string.h>
#include "esp_log.h"


//***
#define UART_NUM UART_NUM_2 	// Porta UART a ser usada
#define TXD_PIN (UART_PIN_NO_CHANGE) 	// Pino de transmissão
#define RXD_PIN (UART_PIN_NO_CHANGE) 	// Pino de recepção


void ConfigurarUART()
{

	 // Configurar a porta serial
	uart_config_t uart_config = {
		.baud_rate = 115200,
		.data_bits = UART_DATA_8_BITS,
		.parity = UART_PARITY_DISABLE,
		.stop_bits = UART_STOP_BITS_1,
		.flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
		.source_clk = UART_SCLK_DEFAULT
	};
	uart_param_config(UART_NUM, &uart_config);
	uart_set_pin(UART_NUM, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
	uart_driver_install(UART_NUM, 256, 0, 0, NULL,  0);

	ESP_LOGI(__func__, "Configurou UART");
}

void Delay_ms(int ms)
{
	vTaskDelay(ms / portTICK_PERIOD_MS);

}


void app_main(void)
{
	ConfigurarUART();
	char* dataSend = "Teste!!!";
    while (1)
    {
    	uart_write_bytes(UART_NUM, dataSend, strlen(dataSend));
    	Delay_ms(2000);
    }
}
