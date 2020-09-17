#include <LittleFS.h>
#include <ArduinoJson.h>

void setup() {
  LittleFS.format();
  Serial.begin(115200);
  Serial.println("");
  StaticJsonDocument<200> doc;
  doc["hello"] = "world";
  doc["ada"] = "wwfaorld";
  doc["ab3ge"] = "eg";
  doc["adbw34sd"] = "aeg";
  LittleFS.begin();
  if (LittleFS.mkdir("root")) {
    File fptr = LittleFS.open("/root/hello.json", "w+");
    if (!fptr) {
      Serial.println("file open failed");
    } else {
      serializeJson(doc, fptr);
      fptr.close();
    }
  }

  File fptr2 = LittleFS.open("/root/hello.json", "r");
  if (!fptr2) {
    Serial.println("file open failed | fptr2");
  } else {
    DynamicJsonDocument doc1(2048);
    deserializeJson(doc1, fptr2);
    String str = doc1["hello"];
    Serial.println(str);
    fptr2.close();
  }
  LittleFS.end();
}
void loop() {}
