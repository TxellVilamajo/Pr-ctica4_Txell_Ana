#include <Arduino.h>

// Definim els pins on connectarem els LEDs
const int ledPin1 = 1; // Pin del primer LED
const int ledPin2 = 2; // Pin del segon LED

// Establim els intervals de parpelleig per a cada LED (en mil·lisegons)
const int interval1 = 500; // El primer LED parpellejarà cada 500 ms
const int interval2 = 700; // El segon LED parpellejarà cada 700 ms

// Declarem les funcions que implementaran les dues tasques
void blinkLed1(void *parameter);
void blinkLed2(void *parameter);

void setup() {
    // Inicialitzem la comunicació pel monitor sèrie
    Serial.begin(115200);
    delay(1000); // Donem un petit marge perquè el monitor sèrie s'estabilitzi

    // Configurem els pins dels LEDs com a sortida
    pinMode(ledPin1, OUTPUT);
    pinMode(ledPin2, OUTPUT);

    // Creem la primera tasca que farà parpellejar el primer LED
    xTaskCreate(
        blinkLed1,       // Funció que defineix el comportament de la tasca
        "Blink LED 1",   // Nom de la tasca (informatiu)
        1000,            // Mida de la pila en bytes
        NULL,            // No passem cap paràmetre
        1,               // Prioritat de la tasca
        NULL             // No guardem el "handle"
    );

    // Creem la segona tasca per al segon LED
    xTaskCreate(
        blinkLed2,
        "Blink LED 2",
        1000,
        NULL,
        1,
        NULL
    );
}

void loop() {
    // No posem res al bucle principal perquè les dues tasques funcionen de manera independent
}

// Aquesta tasca controla el parpelleig del primer LED
void blinkLed1(void *parameter) {
    while (true) {
        digitalWrite(ledPin1, HIGH); // Encén el LED
        Serial.println("LED 1 ON");  // Mostrem el missatge pel monitor sèrie
        vTaskDelay(interval1 / portTICK_PERIOD_MS); // Esperem 500 ms

        digitalWrite(ledPin1, LOW);  // Apaguem el LED
        Serial.println("LED 1 OFF"); // Missatge al monitor sèrie
        vTaskDelay(interval1 / portTICK_PERIOD_MS); // Esperem 500 ms més
    }
}

// Aquesta tasca controla el parpelleig del segon LED
void blinkLed2(void *parameter) {
    while (true) {
        digitalWrite(ledPin2, HIGH); // Encén el LED
        Serial.println("LED 2 ON");  // Missatge al monitor sèrie
        vTaskDelay(interval2 / portTICK_PERIOD_MS); // Esperem 700 ms

        digitalWrite(ledPin2, LOW);  // Apaguem el LED
        Serial.println("LED 2 OFF"); // Missatge al monitor sèrie
        vTaskDelay(interval2 / portTICK_PERIOD_MS); // Esperem 700 ms més
    }
}
