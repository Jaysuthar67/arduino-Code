#include <ArduinoJson.h>
#include <FS.h>

void setup() {
  SPIFFS.format();
  Serial.begin(115200);
  Serial.println("");
  StaticJsonDocument<200> doc;
  doc["hello"] = "world";
  serializeJson(doc, Serial);
}
void loop() {}
