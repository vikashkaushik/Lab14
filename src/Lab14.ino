/*
 * Project Lab14
 * Description:
 * Author:
 * Date:
 */
SYSTEM_THREAD(ENABLED);
#include "MQTT.h"
#include <blynk.h>
MQTT client("lab.thewcl.com", 1883, callback);
#include "oled-wing-adafruit.h"
OledWingAdafruit display;
void callback(char *topic, byte *payload, unsigned int length);
void callback(char* topic, byte* payload, unsigned int length)
{
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  Serial.printf("%s",p);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(p);
  display.display();
  delay(1000);
  Serial.println();
  // if press 1 it turns led on, 0 turns it off
  if(p[0] == '1'){
    digitalWrite(D7,HIGH);
    Serial.println("ON");
  }
  if(p[0] == '0'){
    digitalWrite(D7,LOW);
    Serial.println("OFF");
  }

}  

// setup() runs once, when the device is first turned on.
void setup()
{
// Put initialization like pinMode and begin functions here.
  pinMode(D7, OUTPUT); // le
  display.setup();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("test");
  display.display();
  Blynk.begin("m9AsqCePuYNJjf9JL4f7_DkSjTG668_P", IPAddress(167, 172, 234, 162), 9090); 
  Serial.begin(9600);
}

// loop() runs over and over again, as quickly as it can execute.
void loop()
{
  Blynk.run();
  display.loop();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  // The core of your code will likely live here.
  if (client.isConnected()) {
    client.loop();
    client.subscribe("vkak");
    
    Serial.print("test");
    // press a b or c displays 1 2 and 3 accordingly in oled and mqtt
    if (display.pressedA()) {
      display.clearDisplay();
      
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);

      display.print("1: ");
      client.publish("vkak", "1");
      display.display(); 
      delay(4000);
    }
    if (display.pressedB()) {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);

      display.print("2: ");
      client.publish("vkak", "2");
      display.display(); 
      delay(4000);
    }
    if (display.pressedC()) {

      display.print("3: ");
      client.publish("vkak", "3");
      display.display(); 
      delay(4000);
    }
  } 
  else {
    client.connect(System.deviceID());
    client.subscribe("vkak");
    
  }
  
  
}
// uses blynk to write messages
BLYNK_WRITE(V0){
  String inputText = param.asString();
  client.publish("vkak", inputText);
}