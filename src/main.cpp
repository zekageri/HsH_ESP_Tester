#include <Arduino.h>
#include <hshTest.h>
#include <displayTest.h>
spiDisplay display;
hshTest test;

void setup() {
  Serial.begin(115200);
  vTaskDelay(1000);

  display.init();

  test.ramFill();
  test.json("{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}");
  test.setArraySize(500000);
  test.ramFill();

  // External ram speed test
  test.ramSpeed();
  // Internal ram speed test
  test.ramSpeed(false);
  // Flash speed test
  test.flashSpeed();
}

void loop() {
  // put your main code here, to run repeatedly:
}