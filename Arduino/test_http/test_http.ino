#include <SoftwareSerial.h>

String Arsp, Grsp;
SoftwareSerial gsm(5,6); // RX, TX

void setup() {
  // put your setup code here, to run once:

  Serial.begin(19200);
  Serial.println("Testing GSM SIM800L");
  gsm.begin(19200);

}

void loop() {
  // put your main code here, to run repeatedly:

  if(gsm.available())
  {
    //Grsp = gsm.readString();
    while(gsm.available()){
    Serial.write(gsm.read());
    }
  }

  if(Serial.available())
  {
    Arsp = Serial.readString();
    gsm.println(Arsp);
  }

}
