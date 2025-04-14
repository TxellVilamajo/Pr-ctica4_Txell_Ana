#include <Arduino.h>
#include <FreeRTOS.h>


void anotherTask(void*parameter); // Declaració de la funció

void setup()
{
  Serial.begin(115200);
  /* aquí creem una nova tasca */
  xTaskCreate(
    anotherTask, /* Funció de la tasca. */
    "another Task", /* Nom de la tasca. */
    10000, /* Mida de la pila de la tasca */
    NULL, /* Paràmetre de la tasca */
    1, /* Prioritat de la tasca */
    NULL /* Identificador de la tasca per fer-ne el seguiment */
  ); 
}

/* la funció loop() infinita és invocada per l'ESP32 com a loopTask */
void loop()
{
  Serial.println("this is ESP32 Task");
  delay(1000);
}

/* aquesta funció serà invocada quan es creï anotherTask */
void anotherTask( void * parameter )
{
  /* bucle infinit */
  for(;;)
  {
    Serial.println("this is another Task");
    delay(1000);
  }
  /* elimina una tasca quan acaba,
  això mai passarà perquè és un bucle infinit */
  vTaskDelete( NULL );
}
