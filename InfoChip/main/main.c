/* Projeto Informação do chip
 *
 * Autor: Diego Simão
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
#include "esp_system.h"
#include "esp_heap_caps.h"


void VerificarMemoria()
{
	// https://blog.espressif.com/esp32-programmers-memory-model-259444d89387

	size_t memoriaLivre = esp_get_free_heap_size();
	ESP_LOGI(__func__, "Memoria RAM disponivel: %d bytes", memoriaLivre);

	//*** Heap: Quantidade disponível no bloco de alocação de memória heap(usada para alocação dinâmica de memória durante a execução de um programa)
	// Este bloco é onde fica o carregamento de funções ou variáveis locais durante a execução do software.
	size_t heap_size = heap_caps_get_free_size(MALLOC_CAP_8BIT);
	ESP_LOGI(__func__,"Heap: %u bytes", heap_size);


	//*** DRAM:  Data RAM. Região onde ficam as variáveis, carregamento de funções
	size_t DRAM = heap_caps_get_free_size(MALLOC_CAP_8BIT);
	ESP_LOGI(__func__,"DRAM: %u bytes", DRAM);

	//*** IRAM:  Instruction RAM. Região onde o processador vai  organizar toda a fila de processamento
	size_t IRAN = heap_caps_get_free_size(MALLOC_CAP_32BIT) - DRAM;
	ESP_LOGI(__func__,"IRAM: %u bytes", IRAN);

	//*** Máximo bloco livre
	size_t blocoLivre = heap_caps_get_largest_free_block(MALLOC_CAP_8BIT);
	ESP_LOGI(__func__,"Maximo bloco livre: %u bytes", blocoLivre);

}

void CaracteristicasDoChip(uint32_t features)
{
	//*** Essas características estão nos defines da esp_chip_info.h

	if(features & 0x01) //bit 0
		ESP_LOGI(__func__, "Chip Possui memoria flash embarcada");
	if(features & 0x02) //bit 1
		ESP_LOGI(__func__, "Chip Possui WiFi 2.4GHz ");
	if(features & 0x10) // bit 4
		ESP_LOGI(__func__, "Chip Possui Bluetooth LE (Low Energy)");
	if(features & 0x20) //bit 5
		ESP_LOGI(__func__, "Chip Possui Bluetooth Classico");
	if(features & 0x40) // bit 6
		ESP_LOGI(__func__, "Chip Possui IEEE 802.15.4");
	if(features & 0x80) //bit 7
		ESP_LOGI(__func__, "Chip Possui psram embarcado");
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

	ESP_LOGI(__func__, "Revisao: %d - (no Formato MXX; onde M - Versao principal, XX - versao secundaria)",infoChip.revision);	// Imprime a revisão do chip
	ESP_LOGI(__func__, "Nucleos (Cores): %d ",infoChip.cores);// Imprime a quantidade de núcleos de processamento
}


void app_main(void)
{
	ESP_LOGI(__func__, "\r\n==== INFO CHIP ====");
	InformacoesDoChip();
	VerificarMemoria();
}
