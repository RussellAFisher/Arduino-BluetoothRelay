#include <SPI.h>
#include "Adafruit_BLE_UART.h"

#define ADAFRUITBLE_REQ 10
#define ADAFRUITBLE_RDY 2
#define ADAFRUITBLE_RST 9
#define RELAY1  7

int lightSensor = 0;
int timer = 0;
int lightSensorOn = 0;
int currentState = 0;

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
  for(int i=0; i<len; i++)
   Serial.print((char)buffer[i]); 

  Serial.print(F(" ["));

  for(int i=0; i<len; i++)
  {
    Serial.print(" 0x"); Serial.print((char)buffer[i], HEX); 
  }
  Serial.println(F(" ]"));

  if(len==0 || (char)buffer[0] == 0xA)
  {
    currentState = digitalRead(RELAY1);
    if(currentState == HIGH)
    {
      Serial.println("Turn on, light sensor will be overwritten until Bluetooth receives character: L");
      lightSensorOn = 1;
      digitalWrite(RELAY1,LOW);
    }
    else if(currentState == LOW)
    {
      Serial.println("Turn off, light sensor will be overwritten until Bluetooth receives character: L");
      lightSensorOn = 1;
      digitalWrite(RELAY1,HIGH);
    }
  }
  
  if((char)buffer[0] == 0x4c || (char)buffer[0] == 0x6c)
  {
    Serial.println("Light sensor will be turned back on");
    lightSensorOn = 0;
  }
  
  //This entire if statement needs to be reworked to check that Bluetooth input is numbers only, if it is it should delay by that many sec/min/hours, depending on desire. Error handle for mixed input that doesn't match any cases.
  if((char)buffer[0] == 0x31 && (char)buffer[1] == 0x30) //Checks for certain input from Bluetooth, in this case '10'
  {
    currentState = digitalRead(RELAY1);
    Serial.println("Current state is: " + currentState);
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
    
    Serial.println("Delay ten seconds"); //Arbitrary amount of time, kept it at ten seconds for testing. 
    timer = 10; 
    Serial.println(timer);
    lightSensorOn = 1; 
    
    for(int f=10; f>0; f--) //For loop that
    {
        if(timer < 2)
        {
          Serial.println("Light sensor is now functional");
          lightSensorOn = 0;
        }
        else
        {
        Serial.println("Counting down: " + timer);
        timer --;
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
  Serial.println(F("Learning Bluetooth"));
  

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
