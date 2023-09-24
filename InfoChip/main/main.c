/* Projeto Informação dos chips
 *
 * Autor: Diego de Lima Simão
 * email: simaold@gmail.com
 * Data: 23/09/2023
 *
 * Este projeto faz a impressão via terminal das informações do chip
 * IDE espressif Versão: 2.9.1
 */

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "esp_chip_info.h"
#include "esp_log.h"



void CaracteristicasDoChip(uint32_t features)
{
	//*** Essas características estão nos defines da esp_chip_info.h

	if(features & 0x01) //bit 0
		ESP_LOGI(__func__, "Chip possui memoria flash embarcada");
	if(features & 0x02) //bit 1
		ESP_LOGI(__func__, "Chip possui WiFi 2.4GHz ");
	if(features & 0x10) // bit 4
		ESP_LOGI(__func__, "Chip possui Bluetooth LE (Low Energy)");
	if(features & 0x20) //bit 5
		ESP_LOGI(__func__, "Chip possui Bluetooth Classico");
	if(features & 0x40) // bit 6
		ESP_LOGI(__func__, "Chip possui IEEE 802.15.4");
	if(features & 0x80) //bit 7
		ESP_LOGI(__func__, "Chip possui psram embarcado");
}


void ModeloDoChip(uint8_t model)
{
    //Enumerador esp_chip_model_t

	switch (model)
	{
		case 1:
			ESP_LOGI(__func__, "ESP32");
			break;

		case 2:
			ESP_LOGI(__func__, "ESP32-S2");
			break;

		case 9:
			ESP_LOGI(__func__, "ESP32-S3");
			break;

		case 5:
			ESP_LOGI(__func__, "ESP32-C3");
			break;

		case 6:
			ESP_LOGI(__func__, "ESP32-H2");
			break;
		case 12:
			ESP_LOGI(__func__, "ESP32-C2");
			break;

		default:
			ESP_LOGE(__func__, "CHIP Nao Identificado");
			break;
	}
}


void InformacoesDoChip()
{
	esp_chip_info_t infoChip;					// Cria uma variável do tipo struct esp_chip_info_t
	esp_chip_info(&infoChip);					// Preenche campos com informações do chip
	ModeloDoChip(infoChip.model);				// Imprime Modelo do chip
	CaracteristicasDoChip(infoChip.features);	// Imprime características do Chip

	ESP_LOGI(__func__, "Revisao: %d",infoChip.revision);	// Imprime a revisão do chip
	ESP_LOGI(__func__, "Nucleos (Cores): %d",infoChip.cores);// Imprime a quantidade de núcleos de processamento
}


void app_main(void)
{
	ESP_LOGI(__func__, "\r\n==== INFO CHIP ====");
	InformacoesDoChip();
}
