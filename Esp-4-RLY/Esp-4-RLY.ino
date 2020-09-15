#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "Jay_Suthar"
#define STAPSK  "7359209090"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;
int d0 = 16, d1 = 5, d2 = 4, d3 = 0;

ESP8266WebServer server(80);

const int led = 2;

void handleRoot() {
  digitalWrite(led, LOW);
  server.send(200, "text/plain", "root");
  digitalWrite(led, HIGH);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  //Pin Setup
  pinMode(d0, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  digitalWrite(d0, HIGH);
  digitalWrite(d1, HIGH);
  digitalWrite(d2, HIGH);
  digitalWrite(d3, HIGH);
  //End

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(led, LOW);
    delay(500);
    Serial.print(".");
    digitalWrite(led, HIGH);
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  //  String LocalIP = WiFi.localIP();
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);


  //Get Status API
  server.on("/status", []() {
    digitalWrite(led, LOW);
    String str = "{\"deviceid\":\"espJay\",\"status\":{\"rly1\":\"" ;
    str += !digitalRead(d0);
    str += "\",\"rly2\":\"";
    str += !digitalRead(d1);
    str += "\",\"rly3\":\"";
    str += !digitalRead(d2);
    str += "\",\"rly4\":\"";
    str += !digitalRead(d3);
    str += "\"},\"myIP\":\"";
    str += MyIP();
    str += "\"}";
    server.send(200, "text/json", str);
    digitalWrite(led, HIGH);
  });

  //get IP API
  server.on("/ip", []() {
    digitalWrite(led, LOW);
    String str = "{\"ip\":\"";
    str += MyIP();
    str += "\"}";
    server.send(200, "text/json", str);
    digitalWrite(led, HIGH);
  });

  server.on("/set", []() {
    digitalWrite(led, LOW);
    if (server.args() < 1) {
      server.send(400, "text/plain", "No Arguments");
    } else {
      for (int i = 0; i < server.args(); i++) {
        String argNames = server.argName(i);
        if (argNames.equalsIgnoreCase("rly1")) {
          if (server.arg(argNames).equalsIgnoreCase("on")) {
            digitalWrite(d0, LOW);
          } else if (server.arg(argNames).equalsIgnoreCase("off")) {
            digitalWrite(d0, HIGH);
          } else if (server.arg(argNames).equalsIgnoreCase("toggle")) {
            digitalWrite(d0, (!digitalRead(d0)));
          } else {
            server.send(422, "text/plain", "Wrong argument for rly1");
          }

        } else if (argNames.equalsIgnoreCase("rly2")) {
         
          if (server.arg(argNames).equalsIgnoreCase("on")) {
            digitalWrite(d1, LOW);
          } else if (server.arg(argNames).equalsIgnoreCase("off")) {
            digitalWrite(d1, HIGH);
          } else if (server.arg(argNames).equalsIgnoreCase("toggle")) {
            digitalWrite(d1, (!digitalRead(d1)));
          } else {
            server.send(422, "text/plain", "Wrong argument for rly2");
          }

        } else if (argNames.equalsIgnoreCase("rly3")) {
         
          if (server.arg(argNames).equalsIgnoreCase("on")) {
            digitalWrite(d2, LOW);
          } else if (server.arg(argNames).equalsIgnoreCase("off")) {
            digitalWrite(d2, HIGH);
          } else if (server.arg(argNames).equalsIgnoreCase("toggle")) {
            digitalWrite(d2, (!digitalRead(d2)));
          } else {
            server.send(422, "text/plain", "Wrong argument for rly3");
          }

        } else if (argNames.equalsIgnoreCase("rly4")) {
        
          if (server.arg(argNames).equalsIgnoreCase("on")) {
            digitalWrite(d3, LOW);
          } else if (server.arg(argNames).equalsIgnoreCase("off")) {
            digitalWrite(d3, HIGH);
          } else if (server.arg(argNames).equalsIgnoreCase("toggle")) {
            digitalWrite(d3, (!digitalRead(d3)));
          }  else {
            server.send(422, "text/plain", "Wrong argument for rly4");
          }

        } else {
          server.send(422, "text/plain", "Unknown Argument");
          break;
        }

      }
    }
    server.send(200, "text/plain", "updated");
    digitalWrite(led, HIGH);
  });


  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

String MyIP() {
  String MyIPStr = String(WiFi.localIP()[0]) + String(".") + \
                   String(WiFi.localIP()[1]) + String(".") + \
                   String(WiFi.localIP()[2]) + String(".") + \
                   String(WiFi.localIP()[3])  ;
  return MyIPStr;
}

void loop(void) {
  server.handleClient();
  MDNS.update();
}
