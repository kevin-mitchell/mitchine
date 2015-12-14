 
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <ESP8266WebServer.h>
#include <Ticker.h>
#include <EEPROM.h>
#include <WiFiUdp.h>


#include "helpers.h"
#include "global.h"
/*
Include the HTML, STYLE and Script "Pages"
*/
#include "Page_Admin.h"
#include "Page_Information.h"
#include "PAGE_NetworkConfiguration.h"

/*
 * 1 = 16 = Mom = Red = Mitchine Chicago
 * 2 = 14 = Dad = Orange = Mitchine Houghton
 * 3 = 0 = Ant = Green = Mitchine Berkeley
 * 4 = 13 = Tri = Light Blue = Mitchine Oakland
 * 5 = 4 = Bri = Yellow = Mitchine San Francisco
 * 6 = 15 = Izz = Purple = Mitchine Tokyo
 * 7 = 2 = Gra = Brown = Mitchine Seoul
 * 8 = 5 = KL = Black = Mitchine Osaka
 */
#define ACCESS_POINT_NAME  "Mitchine Chicago"
#define ACCESS_POINT_PASSWORD  "mitchinexmas15" 
#define AdminTimeOut 180  // Defines the Time in Seconds, when the Admin-Mode will be diabled
WiFiClient espClient;
PubSubClient client(espClient);
const int maximumDevices = 8;

//The number of samples we'll take each time we check the capacitive button
const int capSamples = 10;
//The pin to be used for capacitive input
const int capInputPin = 12;
//The threshold for the total the capacitive input adds up to with capSamples attempts
const int threshHold = 45;
//time millis of last touch detection event
long lastCapTouch = 0;

long lastReconnect = 0;
long lastMsg = 0;
char msg[50];
int value = 0;

/*
 * 1 = 16 = Mom = Red = Mitchine Chicago
 * 2 = 14 = Dad = Orange = Mitchine Houghton
 * 3 = 0 = Ant = Green = Mitchine Berkeley
 * 4 = 13 = Tri = Light Blue = Mitchine Oakland
 * 5 = 4 = Bri = Yellow = Mitchine San Francisco
 * 6 = 15 = Izz = Purple = Mitchine Tokyo
 * 7 = 2 = Gra = Brown = Mitchine Seoul
 * 8 = 5 = KL = Black = Mitchine Osaka
 */
int outputPins[] = {16,14,0,13,4,15,2,5};
int ledOnState[] = {HIGH, HIGH, LOW, HIGH, HIGH, HIGH, LOW, HIGH};

void setup ( void ) {

  pinMode(16, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(5, OUTPUT);
  
  
  EEPROM.begin(512);
  Serial.begin(115200);
  delay(500);
  Serial.println("Starting ES8266");
  if (!ReadConfig())
  {
    // DEFAULT CONFIG
    config.ssid = "MYSSID";
    config.password = "MYPASSWORD";
    config.dhcp = true;
    config.IP[0] = 192;config.IP[1] = 168;config.IP[2] = 1;config.IP[3] = 100;
    config.Netmask[0] = 255;config.Netmask[1] = 255;config.Netmask[2] = 255;config.Netmask[3] = 0;
    config.Gateway[0] = 192;config.Gateway[1] = 168;config.Gateway[2] = 1;config.Gateway[3] = 1;
    config.mqttServer = "mqtt.develpr.com";
    config.deviceIdentifier = 1;
    
    WriteConfig();
    Serial.println("General config applied");
  }
  
  
  if (AdminEnabled)
  {
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP( ACCESS_POINT_NAME , ACCESS_POINT_PASSWORD);
  }
  else
  {
    WiFi.mode(WIFI_STA);
  }

  ConfigureWifi();
  

  server.on ( "/", send_network_configuration_html  );
  
  server.on ( "/favicon.ico",   []() { Serial.println("favicon.ico"); server.send ( 200, "text/html", "" );   }  );


  server.on ( "/admin.html", []() { Serial.println("admin.html"); server.send ( 200, "text/html", PAGE_AdminMainPage );   }  );
  server.on ( "/config.html", send_network_configuration_html );
  server.on ( "/info.html", []() { Serial.println("info.html"); server.send ( 200, "text/html", PAGE_Information );   }  );
  server.on ( "/admin/values", send_network_configuration_values_html );
  server.on ( "/admin/connectionstate", send_connection_state_values_html );
  server.on ( "/admin/infovalues", send_information_values_html );

  server.onNotFound ( []() { Serial.println("Page Not Found"); server.send ( 400, "text/html", "Page not Found" );   }  );
  server.begin();
  Serial.println( "HTTP server started" );

  char charMqttServer[config.mqttServer.length()];
  config.mqttServer.toCharArray(charMqttServer, config.mqttServer.length()+1); 

  client.setServer(charMqttServer, 1883);
  
  client.setCallback(callback);

  reconnect();
  disableAllButMe();

}


static bool checkTouch() {
   long riseTime = 0;

   //capSamples = int 20 - just the number of samples to take - adjust as desried
   for(int i = 0; i < capSamples; i++){

    //capInputPin = int 12 in my case, just the pin # to use
    pinMode(capInputPin, OUTPUT);
    digitalWrite(capInputPin, LOW);

    //This delay which may or may not need to be here.    
    delayMicroseconds(500);

    pinMode(capInputPin, INPUT_PULLUP);

    while(digitalRead(capInputPin) != HIGH){
      ++riseTime;
    }

   }
   //"threshHold" is some number that you will likely need to
   //experiment with. For 20 samples, somewhere around 1000
   //might be good. 
   return (riseTime > threshHold);   
}

void disableAllButMe(){
  for(int i = 0; i < 8; i++){
    if(outputPins[i] != getPin(config.deviceIdentifier)){
      digitalWrite(outputPins[i], !ledOnState[i]);
    }
  }
}

void publishTouched(){
  snprintf (msg, 75, "%ld", getPin(config.deviceIdentifier));
  client.publish("mitchinexmas15", msg);
}


void callback(char* topic, byte* payload, unsigned int length) {

  int mqttIdentifier = ((char)payload[0] - '0');
  int pin = getPin(mqttIdentifier);

//  if(mqttIdentifier == config.deviceIdentifier){
//    disableAllButMe();  
//  }
  if( pin != -2 ){
      digitalWrite(pin, ledOnState[mqttIdentifier-1]);
      delay(500);
      digitalWrite(pin, !ledOnState[mqttIdentifier-1]);
      delay(500);
      digitalWrite(pin, ledOnState[mqttIdentifier-1]);
  }
}


void reconnect() {
  // Loop until we're reconnected
  int attempts = 0;
  while (!client.connected() && attempts < 4) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("mitchinexmas15", "Welcome to Chicago!");
      // ... and resubscribe
      client.subscribe("mitchinexmas15");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 3 seconds");
      // Wait 5 seconds before retrying
      delay(3000);
      attempts++;
    }
  }
}


int getPin(int mqttIdentifier){ 
  
  int result = -2;
  
  if(mqttIdentifier < 1 || mqttIdentifier > 8){
     result = result;
  }
  else{
    result = outputPins[(mqttIdentifier-1)];
  }
  
  return result;
}


 
void loop ( void ) {
  if (AdminEnabled)
  {
    if (AdminTimeOutCounter > AdminTimeOut)
    {
       AdminEnabled = false;
       Serial.println("Admin Mode disabled!");
       WiFi.mode(WIFI_STA);
    }
  }
  
  server.handleClient();

  if(WiFi.status() == WL_CONNECTED){

    long now = millis();
    if (!client.connected() && (now - lastReconnect > 60000)) {
      Serial.println("Reconnecting...");
      lastReconnect = now;
      reconnect();
    }

      client.loop();
   
      now = millis();
      if (now - lastMsg > 90000) {
        lastMsg = now;
        ++value;
        if(value > 9999){
          value = 1;
        }
        snprintf (msg, 75, "Hello from Chicago #%ld", value);
        Serial.print("Publish message: ");
        Serial.println(msg);
        client.publish("heartBeat", msg);
        
      }
      
      if((now - lastCapTouch) > 6000){
        if(checkTouch()){
          publishTouched();
          disableAllButMe();
          lastCapTouch = now;
          
        }
      }
    
  }

}
