#include <SoftwareSerial.h>

String Arsp, Grsp;
SoftwareSerial gprsSerial(10, 11); // RX, TX

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  Serial.println("Testing GSM SIM800L");
  gprsSerial.begin(4800);
  //Set Awal 
  Serial.println("Config SIM900...");
  delay(2000);
  Serial.println("Done!...");
  gprsSerial.flush();
  Serial.flush();
gprsSerial.println("AT+SAPBR=0,1");
  delay(2000);
  toSerial();
  
  gprsSerial.println("AT+CREG?");
  delay(100);
  toSerial();
  gprsSerial.println("AT+CFUN=1");
  delay(100);
  toSerial();
//  // attach or detach from GPRS service 
  gprsSerial.println("AT+COPS?");
  delay(100);
  toSerial();


  // bearer settings
  gprsSerial.println("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
  delay(2000);
  toSerial();

  // bearer settings
  gprsSerial.println("AT+SAPBR=3,1,\"APN\",\"internet\"");
  delay(2000);
  toSerial();
  
  // bearer settings
  gprsSerial.println("AT+SAPBR=1,1");
  delay(2000);
  toSerial();
  // bearer settings
  gprsSerial.println("AT+SAPBR=2,1");
  delay(2000);
  toSerial();
}
void toSerial()
{
  while(gprsSerial.available()!=0)
  {
    Serial.write(gprsSerial.read());
  }
}
int wind=102;
int id = 2;
char* noteku="War";
char fulls[255];


void loop() {
  // put your main code here, to run repeatedly:
   // initialize http service
  
   gprsSerial.println("AT+HTTPINIT");
   delay(2000); 
   toSerial();
   
    wind++;
   
   // set http param value
   //sprintf(fulls,"test%d%d%s",id,wind,noteku);
   noteku="oke";
   snprintf(fulls,sizeof fulls,"at+httppara=\"URL\",\"http://antontds.com/Service/insert_from_form.php?id_arduino=%d&wind_speed=%d&note=%s\"",id,wind,noteku);
//   gprsSerial.println("AT+HTTPPARA=\"URL\",\"http://antontds.com/Service/insert_from_form.php?id_arduino="" + id +""&wind_speed=""+wind+""&note=""+note+ ""\"");
   gprsSerial.println(fulls);
   delay(2000);
   toSerial();

   // set http action type 0 = GET, 1 = POST, 2 = HEAD
   gprsSerial.println("AT+HTTPACTION=0");
   delay(2000);
   toSerial();

   // read server response
   gprsSerial.println("AT+HTTPREAD"); 
   delay(1000);
   toSerial();

   gprsSerial.println("");
   gprsSerial.println("AT+HTTPTERM");
   toSerial();
   delay(300);

   gprsSerial.println("");
   delay(2000);
}
