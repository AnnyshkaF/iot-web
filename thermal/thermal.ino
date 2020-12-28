// This example uses an ESP32 Development Board
// to connect to shiftr.io.
//
// You can check on your device after a successful
// connection here: https://shiftr.io/try.
//
// by Joël Gähwiler
// https://github.com/256dpi/arduino-mqtt

#include <WiFiClient.h>
//#include <ESP32WebServer.h>
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include <WiFi.h>
#include <MQTT.h>
#include <cstdlib>

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


#include <Wire.h>
#include <Adafruit_AMG88xx.h>
Adafruit_AMG88xx amg;
float pixels[AMG88xx_PIXEL_ARRAY_SIZE];
String buf = "";

const char ssid[] = "Net";
const char pass[] = "password";

//const char broker[] = "192.168.0.5";
const char broker[] = "broker.emqx.io";


//ESP32WebServer server(80);
AsyncWebServer server(80);
WiFiClient net;
MQTTClient client(1024);

unsigned long lastMillis = 0;
const char* PARAM_MESSAGE = "message";

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("\nconnecting...");
  while (!client.connect("bsidebotham", "try", "try")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");
}

String getMain(){
  String responseHTML = "<!DOCTYPE html>"
"<html>"
"<script src=\"main.js\"></script> "
   "<body>"
      "<!--000000000000000000000><-->"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a00\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a01\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a02\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a03\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a04\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a05\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a06\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a07\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<br>"
      "<!--11111111111111111111111><-->"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a10\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a11\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a12\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a13\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a14\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a15\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a16\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a17\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<br>"
      "<!--222222222222222222222222><-->"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a20\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a21\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a22\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a23\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a24\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a25\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a26\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a27\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<br>"
      "<!--33333333333333333333333><-->"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a30\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a31\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a32\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a33\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a34\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a35\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a36\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a37\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<br>"
      "<!--444444444444444444444444><-->"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a40\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a41\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a42\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a43\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a44\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a45\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a46\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a47\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<br>"
      "<!--5555555555555555555555555><-->"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a50\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a51\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a52\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a53\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a54\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a55\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a56\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a57\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<br>"
      "<!--666666666666666666666666666><-->"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a60\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a61\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a62\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a63\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a64\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a65\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a66\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a67\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<br>"
      "<!--7777777777777777777777777><-->"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a70\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a71\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a72\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a73\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a74\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a75\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a76\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
      "<svg width=\"50\" height=\"50\">"
         "<rect id=\"a77\" width=\"50\" height=\"50\" style=\"fill:rgb(0,0,255)\" />"
      "</svg>"
   "</body>"
"</html>";
  return responseHTML;
}

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}


void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

   client.begin(broker, 1883, net);
  /********************************
  / SET STANDART PATHS
  ********************************/
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "hello from ESP32!");
   });

   server.on("/inline", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "this works as well");
   });

  server.on("/main", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", getMain());
  });
  
   // Send a GET request to <IP>/get?message=<message>
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
        String message;
        if (request->hasParam(PARAM_MESSAGE)) {
            message = request->getParam(PARAM_MESSAGE)->value();
        } else {
            message = "No message sent";
        }
        request->send(200, "text/plain", "Hello, GET: " + message);
  });

    // Send a POST request to <IP>/post with a form field message set to <message>
    server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request){
        String message;
        if (request->hasParam(PARAM_MESSAGE, true)) {
            message = request->getParam(PARAM_MESSAGE, true)->value();
        } else {
            message = "No message sent";
        }
        request->send(200, "text/plain", "Hello, POST: " + message);
    });

  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.print("FILE:CSS was called");
    request->send(SPIFFS, "/style.css", "text/css");
  });

  //Route to load main.js file
  server.on("/main.js", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.print("FILE:JS was called");
    request->send(SPIFFS, "/main.js", "text/javascript");
  });
  
  server.onNotFound(notFound);
  
/********************************
/ SET MANGING PATHS
********************************/
server.on("/api/getData", HTTP_GET, [](AsyncWebServerRequest *request){
    String response = buf;
    request->send(200, "text/plain", response);
});

  connect();
  server.begin();

  //amg sensor
  bool status;  
  status = amg.begin();
  if (!status) {
      Serial.println("Could not find a valid AMG88xx sensor, check wiring!");
      while (1);
  }

 if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  
  Serial.println("HTTP server started");
}

void loop() {
   client.loop();
 
  delay(10);  // <- fixes some issues with WiFi stability

  // publish a message roughly every second.
  if (millis() - lastMillis > 1000) {
    if (!client.connected()) {
      Serial.print("lastError: ");
      Serial.println(client.lastError());
      connect();
    }
    lastMillis = millis();
    //client.publish("/a153", "world");
  }
  delay(10);  // <- fixes some issues with WiFi stability

  amg.readPixels(pixels);
  
  Serial.print("[");
  for(int i=1; i<=AMG88xx_PIXEL_ARRAY_SIZE; i++){
      Serial.print(pixels[i-1]);
      //pixels[i-1] = map(pixels[i-1],0,80,0,255);
      Serial.print(", ");
      if( i%8 == 0 ) {
        Serial.println();
      }
    }
    Serial.println("]");
    Serial.println();
    /*for(int i=1; i<=AMG88xx_PIXEL_ARRAY_SIZE; i++){
      Serial.print(pixels[i-1]);
      Serial.print(", ");
      if( i%8 == 0 ) {
        Serial.println();
      }
    }
    Serial.println("]");
    Serial.println();*/
  int val = 0;
  buf = "";
  buf = "{"
                "\"a00\":" + String(pixels[val++]) + ","
                "\"a01\":" + String(pixels[val++]) + ","
                "\"a02\":" + String(pixels[val++]) + ","
                "\"a03\":" + String(pixels[val++]) + ","
                "\"a04\":" + String(pixels[val++]) + ","
                "\"a05\":" + String(pixels[val++]) + ","
                "\"a06\":" + String(pixels[val++]) + ","
                "\"a07\":" + String(pixels[val++]) + ","

                "\"a10\":" + String(pixels[val++]) + ","
                "\"a11\":" + String(pixels[val++]) + ","
                "\"a12\":" + String(pixels[val++]) + ","
                "\"a13\":" + String(pixels[val++]) + ","
                "\"a14\":" + String(pixels[val++]) + ","
                "\"a15\":" + String(pixels[val++]) + ","
                "\"a16\":" + String(pixels[val++]) + ","
                "\"a17\":" + String(pixels[val++]) + ","

                "\"a20\":" + String(pixels[val++]) + ","
                "\"a21\":" + String(pixels[val++]) + ","
                "\"a22\":" + String(pixels[val++]) + ","
                "\"a23\":" + String(pixels[val++]) + ","
                "\"a24\":" + String(pixels[val++]) + ","
                "\"a25\":" + String(pixels[val++]) + ","
                "\"a26\":" + String(pixels[val++]) + ","
                "\"a27\":" + String(pixels[val++]) + ","

                "\"a30\":" + String(pixels[val++]) + ","
                "\"a31\":" + String(pixels[val++]) + ","
                "\"a32\":" + String(pixels[val++]) + ","
                "\"a33\":" + String(pixels[val++]) + ","
                "\"a34\":" + String(pixels[val++]) + ","
                "\"a35\":" + String(pixels[val++]) + ","
                "\"a36\":" + String(pixels[val++]) + ","
                "\"a37\":" + String(pixels[val++]) + ","

                "\"a40\":" + String(pixels[val++]) + ","
                "\"a41\":" + String(pixels[val++]) + ","
                "\"a42\":" + String(pixels[val++]) + ","
                "\"a43\":" + String(pixels[val++]) + ","
                "\"a44\":" + String(pixels[val++]) + ","
                "\"a45\":" + String(pixels[val++]) + ","
                "\"a46\":" + String(pixels[val++]) + ","
                "\"a47\":" + String(pixels[val++]) + ","

                "\"a50\":" + String(pixels[val++]) + ","
                "\"a51\":" + String(pixels[val++]) + ","
                "\"a52\":" + String(pixels[val++]) + ","
                "\"a53\":" + String(pixels[val++]) + ","
                "\"a54\":" + String(pixels[val++]) + ","
                "\"a55\":" + String(pixels[val++]) + ","
                "\"a56\":" + String(pixels[val++]) + ","
                "\"a57\":" + String(pixels[val++]) + ","

                "\"a60\":" + String(pixels[val++]) + ","
                "\"a61\":" + String(pixels[val++]) + ","
                "\"a62\":" + String(pixels[val++]) + ","
                "\"a63\":" + String(pixels[val++]) + ","
                "\"a64\":" + String(pixels[val++]) + ","
                "\"a65\":" + String(pixels[val++]) + ","
                "\"a66\":" + String(pixels[val++]) + ","
                "\"a67\":" + String(pixels[val++]) + "," 

                "\"a70\":" + String(pixels[val++]) + ","
                "\"a71\":" + String(pixels[val++]) + ","
                "\"a72\":" + String(pixels[val++]) + ","
                "\"a73\":" + String(pixels[val++]) + ","
                "\"a74\":" + String(pixels[val++]) + ","
                "\"a75\":" + String(pixels[val++]) + ","
                "\"a76\":" + String(pixels[val++]) + ","
                "\"a77\":" + String(pixels[val++])+"}";
                //Serial.println(buf);
                //delay(10000);
    

    //delay a second
    delay(200);
}

//.\mosquitto_pub.exe -h broker.emqx.io -m "on" -t /a153/b1
//.\mosquitto_pub.exe -h broker.emqx.io -m "off" -t /a153/b2
