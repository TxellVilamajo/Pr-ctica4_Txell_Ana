#include <Arduino.h>

void ledON (void * pvParameters);
void ledOFF(void * pvParameters);
int LED = 2;

SemaphoreHandle_t semafor; // Declarem el semàfor

void setup() {
    Serial.begin(112500);
    pinMode(LED, OUTPUT);
    semafor = xSemaphoreCreateMutex();  // Creació del semàfor

    // Creem les dues tasques amb FreeRTOS
    xTaskCreate(ledON, "LED ON", 1000, NULL, 1, NULL);
    xTaskCreate(ledOFF, "LED OFF", 1000, NULL, 1, NULL);
}

void loop() {
    // No cal fer res al loop, ja que FreeRTOS gestiona les tasques
}

void ledON (void * pvParameters) {
    for(;;) {
        if (xSemaphoreTake(semafor, portMAX_DELAY)) {  // Agafem el semàfor
            Serial.println("Ejecutando tarea: LED ON");
            digitalWrite(LED, HIGH); // Encén el LED
            vTaskDelay(100 / portTICK_PERIOD_MS); // Espera sense bloquejar altres tasques
            xSemaphoreGive(semafor);  // Allibera el semàfor
        }
        vTaskDelay(100 / portTICK_PERIOD_MS); // Deixem temps perquè FreeRTOS canviï de tasca
    }
}

void ledOFF (void * pvParameters) {
    for(;;) {
        if (xSemaphoreTake(semafor, portMAX_DELAY)) {  // Agafem el semàfor
            Serial.println("Ejecutando tarea: LED OFF");
            digitalWrite(LED, LOW); // Apaga el LED
            vTaskDelay(100 / portTICK_PERIOD_MS); // Espera sense bloquejar altres tasques
            xSemaphoreGive(semafor);  // Allibera el semàfor
        }
        vTaskDelay(100 / portTICK_PERIOD_MS); // Deixem temps perquè FreeRTOS canviï de tasca
    }
}
