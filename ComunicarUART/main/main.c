#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include <string.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "esp_types.h"
#include "LM32.h"


//***
#define UART_NUM UART_NUM_2 	// Porta UART a ser usada
#define TXD_PIN (UART_PIN_NO_CHANGE) 	// Pino de transmissão
#define RXD_PIN (UART_PIN_NO_CHANGE) 	// Pino de recepção


SemaphoreHandle_t mutexI2C0;

void setup_i2c(){
    mutexI2C0 = xSemaphoreCreateMutex();

    i2c_config_t i2c0Config = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C0_SDA,
        .scl_io_num = I2C0_SCL,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 100000};
    i2c_param_config(I2C_NUM_0, &i2c0Config);
    i2c_driver_install(I2C_NUM_0,I2C_MODE_MASTER,0,0,0);
}

void readTeamperature(void *args){
    while(1){
        if(xSemaphoreTake(mutexI2C0, 250/portTICK_PERIOD_MS))
        {
            float temperature = lm75aGetValues();
            printf("Temperatura: %f\n",temperature);

            xSemaphoreGive(mutexI2C0);
        }
        else
        {
            ESP_LOGE("LM75A","ERRO AO ACESSAR BARRAMENTOO I2C");
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}


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
	setup_i2c();
	xTaskCreate(readTeamperature, "readTeamperature", 2048, NULL, 2, NULL);
	char* dataSend = "Teste!!!";
    while (1)
    {
    	uart_write_bytes(UART_NUM, dataSend, strlen(dataSend));
    	Delay_ms(2000);
    }
}
