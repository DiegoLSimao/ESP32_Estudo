#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void Task1(void * params){
    while(1){
        printf("Realizando leitura de temperatura interna%s \n", (char *) params);
        vTaskDelay (1000 / portTICK_PERIOD_MS);
    }
}

void Task2(void * params){
    while(1){
        printf("Realizando leitura de umidade %s\n",(char *) params);
        vTaskDelay (1000 / portTICK_PERIOD_MS);
    }
}

void Task3(void * params){
    while(1){
        printf("Realizando leitura de Pressao atmosferica %s\n",(char *) params);
        vTaskDelay (2000 / portTICK_PERIOD_MS);
    }
}

void Task4(void * params){
    while(1){
        printf("Realizando leitura do sensor de chuva %s\n",(char *) params);
        vTaskDelay (2000 / portTICK_PERIOD_MS);
    }
}

void Task5(void * params){
    while(1){
        printf("Realizando leitura de temperatura externa %s\n",(char *) params);
        vTaskDelay (2000 / portTICK_PERIOD_MS);
    }
}

void Task6(void * params){
    while(1){
        printf("Realizando leitura sensor da porta %s\n",(char *) params);
        vTaskDelay (2000 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    xTaskCreate(&Task1,"Leitura de temperatura interna",2048,"Task 1",5,NULL);
    xTaskCreate(&Task2,"Leitura de umidade"    ,2048,"Task 2",4,NULL);

    xTaskCreate(&Task3,"Leitura de Pressao atmosferica",2048,"Task 3",2,NULL);
    xTaskCreate(&Task4,"Leitura de sensor de chuva"    ,2048,"Task 4",1,NULL);

    xTaskCreate(&Task5,"Leitura de temperatura externa",2048,"Task 5",3,NULL);
    xTaskCreate(&Task6,"Leitura de sensor da porta"    ,2048,"Task 6",1,NULL);
}
