
#include <ModbusRTU.h>
#include <SoftwareSerial.h>
const int analogOutPin = D8;
SoftwareSerial S(D3, D2);// we need one serial port for communicating with RS 485 to TTL adapter


#define POT_VAL_REG 10
#define SLAVE_ID 1

ModbusRTU mb;
uint16_t pot_value=0;
void setup() {
  Serial.begin(9600);
  S.begin(9600, SWSERIAL_8N1);
  mb.begin(&S,D0); // RE/DI connected to D0 of ESP8266
  
  mb.slave(SLAVE_ID);
  mb.addHreg(POT_VAL_REG);
  mb.Hreg(POT_VAL_REG, 0);
  

}

void loop() {
  
     pot_value=mb.Hreg(POT_VAL_REG);
     pot_value=map(pot_value,9,1023,0,255);
     Serial.println(pot_value);
     analogWrite(analogOutPin, pot_value);
     delay(10);
     mb.task();
     
}
