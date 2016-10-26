#include <SPI.h>
#include "Adafruit_BLE_UART.h"

#define ADAFRUITBLE_REQ 10
#define ADAFRUITBLE_RDY 2
#define ADAFRUITBLE_RST 9
#define RELAY1  7

int lightSensor = 0; //Placeholder for photoresistor measurment, can be used to in the void loop() to display the value in Serial Monitor
int lightSensorOn = 0; //Toggle between 0 and 1 to determine if photoresistor should be active
int currentState = 0; //Toggle between 0 and 1 to determine what state the relay is in, used to execute the opposite with minimal code
int timeBypass = 0; //Used as a placeholder for the time to bypass the photoresistor, created presets that use this as a variable to be set and used. Presets are: 1, 2, 4, 8 * x, where x is the delay in countdown

Adafruit_BLE_UART uart = Adafruit_BLE_UART(ADAFRUITBLE_REQ, ADAFRUITBLE_RDY, ADAFRUITBLE_RST);

void aciCallback(aci_evt_opcode_t event)
{
  switch(event)
  {
    case ACI_EVT_DEVICE_STARTED:
      Serial.println(F("Looking for devices"));
      break;
    case ACI_EVT_CONNECTED:
      Serial.println(F("Connected!"));
      break;
    case ACI_EVT_DISCONNECTED:
      Serial.println(F("Disconnected or timed out"));
      break;
    default:
      break;
  }
}

/**************************************************************************/
/*!
    This function is called whenever data arrives on the RX channel
*/
/**************************************************************************/
void rxCallback(uint8_t *buffer, uint8_t len)
{
  Serial.print(F("Received "));
  Serial.print(len);
  Serial.print(F(" bytes: "));

  Serial.print(F(" ["));

  for(int i=0; i<len; i++)
  {
    Serial.print(" 0x"); Serial.print((char)buffer[i], HEX); 
  }
  Serial.println(F(" ]"));

  if(len==0 || (char)buffer[0] == 0xA) //Current override character, that gives full control to Bluetooth, is an empty space. Photoresistor will be overridden until a reset character is sent, arbitrary choice was 'R'
  {
    currentState = digitalRead(RELAY1);
    if(currentState == HIGH)
    {
      Serial.println("Turn on, light sensor will be overwritten until Bluetooth receives character: R");
      lightSensorOn = 1;
      digitalWrite(RELAY1,LOW);
    }
    else if(currentState == LOW)
    {
      Serial.println("Turn off, light sensor will be overwritten until Bluetooth receives character: R");
      lightSensorOn = 1;
      digitalWrite(RELAY1,HIGH);
    }
  }
  
  if((char)buffer[0] == 0x72 || (char)buffer[0] == 0x52) //Arbitrary letter choice, can be used with native app
  {
    Serial.println("Light sensor will be turned back on");
    lightSensorOn = 0;
  }
  
  
  if((char)buffer[0] == 0x31) //Checks for certain input from Bluetooth, 1
  {

    currentState = digitalRead(RELAY1);
//    Serial.println("Current state is: " + currentState);
    if(currentState == HIGH)
    {
      Serial.println("Turn on");
      digitalWrite(RELAY1,LOW);
    }
    else if(currentState == LOW)
    {
      Serial.println("Turn off");
      digitalWrite(RELAY1,HIGH);
    }
    
    lightSensorOn = 1; 
    timeBypass = 60;
    
    for(int f=60; f>0; f--) //For loop that delays for one minute
    {
        if(timeBypass < 2)
        {
          Serial.println("Light sensor is now functional");
          lightSensorOn = 0;
        }
        else
        {
        timeBypass --;
        delay (1000);
        }
    }
  }
  
  if((char)buffer[0] == 0x32) //Checks for certain input from Bluetooth, 2
  {

    currentState = digitalRead(RELAY1);
//    Serial.println("Current state is: " + currentState);
    if(currentState == HIGH)
    {
      Serial.println("Turn on");
      digitalWrite(RELAY1,LOW);
    }
    else if(currentState == LOW)
    {
      Serial.println("Turn off");
      digitalWrite(RELAY1,HIGH);
    }
    
    lightSensorOn = 1; 
    timeBypass = 120;
    
    for(int f=120; f>0; f--) //For loop that delays for two minutes
    {
        if(timeBypass < 2)
        {
          Serial.println("Light sensor is now functional");
          lightSensorOn = 0;
        }
        else
        {
        timeBypass --;
        delay (1000);
        }
    }
  }
  
  if((char)buffer[0] == 0x34) //Checks for certain input from Bluetooth, 4
  {

    currentState = digitalRead(RELAY1);
//    Serial.println("Current state is: " + currentState);
    if(currentState == HIGH)
    {
      Serial.println("Turn on");
      digitalWrite(RELAY1,LOW);
    }
    else if(currentState == LOW)
    {
      Serial.println("Turn off");
      digitalWrite(RELAY1,HIGH);
    }
    
    lightSensorOn = 1; 
    timeBypass = 240;
    
    for(int f=240; f>0; f--) //For loop that delays for 4 minutes
    {
        if(timeBypass < 2)
        {
          Serial.println("Light sensor is now functional");
          lightSensorOn = 0;
        }
        else
        {
        timeBypass --;
        delay (1000);
        }
    }
  }
  
  if((char)buffer[0] == 0x38) //Checks for certain input from Bluetooth, 8
  {

    currentState = digitalRead(RELAY1);
//    Serial.println("Current state is: " + currentState);
    if(currentState == HIGH)
    {
      Serial.println("Turn on");
      digitalWrite(RELAY1,LOW);
    }
    else if(currentState == LOW)
    {
      Serial.println("Turn off");
      digitalWrite(RELAY1,HIGH);
    }
    
    lightSensorOn = 1; 
    timeBypass = 480;
    
    for(int f=480; f>0; f--) //For loop that delays for 8 minutes
    {
        if(timeBypass < 2)
        {
          Serial.println("Light sensor is now functional");
          lightSensorOn = 0;
        }
        else
        {
        timeBypass --;
        delay (1000);
        }
    }
  }
  
  if((char)buffer[0] == 0x35) //Checks for certain input from Bluetooth, 5
  {

    currentState = digitalRead(RELAY1);
//    Serial.println("Current state is: " + currentState);
    if(currentState == HIGH)
    {
      Serial.println("Turn on");
      digitalWrite(RELAY1,LOW);
    }
    else if(currentState == LOW)
    {
      Serial.println("Turn off");
      digitalWrite(RELAY1,HIGH);
    }
    
    lightSensorOn = 1; 
    timeBypass = 10;
    
    for(int f=10; f>0; f--) //For loop that delays ten seconds, testing purposes only
    {
        if(timeBypass < 2)
        {
          Serial.println("Light sensor is now functional");
          lightSensorOn = 0;
        }
        else
        {
        timeBypass --;
        delay (1000);
        }
    }
  }

  /* Echo the same data back! */
//  uart.write(buffer, len);
}

/**************************************************************************/
/*!
    Configure the Arduino and start advertising with the radio
*/
/**************************************************************************/
void setup(void)
{ 
  Serial.begin(9600);
  pinMode(RELAY1, OUTPUT);
  pinMode(lightSensor, INPUT);
  digitalWrite(RELAY1,HIGH);
  while(!Serial); // Leonardo/Micro should wait for serial init
  Serial.println(F("Bluetooth Photoresistor Relay"));
  

  uart.setRXcallback(rxCallback);
  uart.setACIcallback(aciCallback);
  // uart.setDeviceName("NEWNAME"); /* 7 characters max! */
  uart.begin();
}

/**************************************************************************/
/*!
    Constantly checks for new events on the nRF8001
*/
/**************************************************************************/
void loop()
{
  int lightLevel = analogRead(lightSensor); 
//  Serial.println(lightLevel);
  delay(500);
  if( lightLevel < 400 && lightSensorOn == 0)
  {
     digitalWrite(RELAY1,LOW); 
  }
  
  if(lightLevel >= 400 && lightSensorOn == 0)
  {
       digitalWrite(RELAY1,HIGH);
  }
  uart.pollACI();
}
