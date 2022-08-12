#include <ModbusRTU.h>
#include <SoftwareSerial.h>
 
SoftwareSerial S(D3, D2); // we need one serial port for communicating with RS 485 to TTL adapter


ModbusRTU mb;

bool cb(Modbus::ResultCode event, uint16_t transactionId, void* data) { // Callback to monitor errors
  if (event != Modbus::EX_SUCCESS) {
    Serial.print("Request result: 0x");
    Serial.print(event, HEX);
  }
  return true;
}

void setup() {
  Serial.begin(9600); // This serial for debug prints
  S.begin(9600, SWSERIAL_8N1);
  mb.begin(&S,D0); // RE/DI connected to D0 of ESP8266
  mb.master();
  
}

uint16_t adc_val;
void loop() {
  
  if (!mb.slave()) {
    adc_val=analogRead(A0);
    Serial.println(adc_val);
    mb.writeHreg(1,10,adc_val,cb);    
    while(mb.slave()) { // Check if transaction is active
      mb.task();
      }
    delay(10); 
  }
}
