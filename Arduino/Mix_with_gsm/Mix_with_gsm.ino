// Pin definitions
# define windPin 2 // Receive the data from sensor
#define utara 0
#define tl 13
#define timur 10
#define tenggara 3
#define selatan 4
#define bd 7
#define barat 8
#define bl 9

// Sim 800L
#include <SoftwareSerial.h>

String Arsp, Grsp;
SoftwareSerial gprsSerial(5,6); // RX, TX
bool kirim = false;
int time_kirim = 60; //1 minutes
int sec =1;

//Rain Sensor
int nRainIn = A1;
int nRainDigitalIn = 12;
int nRainVal;
boolean bIsRaining = false;
String strRaining;
#include <Servo.h>          //include the servo library
Servo myservo;              //create a servo object

// Constants definitions
const float pi = 3.14159265; // pi number
int period = 1000; // Measurement period (miliseconds)
int delaytime = 1000; // Time between samples (miliseconds)
int radio = 80; // Distance from center windmill to outer cup (mm)
int jml_celah = 18, pos; // jumlah celah sensor

// Variable definitions
unsigned int Sample = 0; // Sample number
unsigned int counter = 0; // B/W counter for sensor
unsigned int RPM = 0; // Revolutions per minute
float speedwind = 0; // Wind speed (m/s)
// Servo Position
int time_pulled = 0;
bool pulled = false;
const int maxTime = 1*10;
const int jeda_putar = 1000*3;
void tarik(){
  myservo.write(0);
  delay(jeda_putar);
  myservo.write(90);
}
void ulur(){
  myservo.write(180);
  delay(jeda_putar);
  myservo.write(90);
}

void toSerial()
{
  while(gprsSerial.available()!=0)
  {
    Serial.write(gprsSerial.read());
  }
}

void setup()
{
Serial.begin(38400);
gprsSerial.begin(19200);
//gprsSerial.println("AT+IPR=9600");
// Sim 800L
Serial.println("Testing GSM SIM900A");
  
  //Set Awal 
  Serial.println("Config SIM900A...");
  delay(2000);
  Serial.println("Done!...");
  gprsSerial.flush();
  Serial.flush();
  gprsSerial.println("AT+IPR=19200");
  delay(2000);
  toSerial();
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
// initialize http service
  
   gprsSerial.println("AT+HTTPINIT");
   delay(2000); 
   toSerial();
   // initialize http service
  
   gprsSerial.println("at+httppara=\"cid\",1");
   delay(2000); 
   toSerial();

  myservo.attach(11);
  pulled = false;
  

// Set the pins

//anemometer
pinMode(10, INPUT);
digitalWrite(10, HIGH);

 pinMode(utara,INPUT_PULLUP);
  pinMode(tl,INPUT_PULLUP);
  pinMode(timur,INPUT_PULLUP);
  pinMode(tenggara,INPUT_PULLUP);
  pinMode(selatan,INPUT_PULLUP);
  pinMode(bd,INPUT_PULLUP);
  pinMode(barat,INPUT_PULLUP);
  pinMode(bl,INPUT_PULLUP);
  //Rain
  pinMode(12,INPUT);
// sets the serial port to 9600

//// Splash screen
//Serial.println("ANEMOMETER");
//Serial.println("**********");
//Serial.println("Based on depoinovasi anemometer sensor");
//Serial.print("Sampling period: ");
//Serial.print(period/1000);
//Serial.print(" seconds every ");
//Serial.print(delaytime/1000);
//Serial.println(" seconds.");
//Serial.println("** You could modify those values on code **");
//Serial.println();
//gprsSerial.flush();
//  Serial.flush();
}
char* noteku ="War";
char fulls[255];
int arduino_id = 1;
void loop()
{
  sec++;
  //gprsSerial.println("AT");
  //delay(2000);
  //toSerial();
  //if pulled , count the time
  //Serial.println(time_pulled);
  if(pulled){
    time_pulled ++;
  }else time_pulled = 0;

  if(time_pulled == maxTime){
    // start dari 180 derajat ke 0 derajat , ulurkan
//       Serial.println("Balik");
       //ulur 
       ulur();
       pulled = false;
  }
   
 
  Sample++;
  /*
  Serial.print(Sample);
  Serial.print(": Start measurement…");
  
  Serial.println("t finished.");
  Serial.print("Counter: ");
  Serial.print(counter);
  Serial.print("; RPM: ");
  
  Serial.print(RPM);
  Serial.print("; Wind speed: ");
  
  
  Serial.print(fixSpeed);
  //Serial.print(" [m/s]");
  Serial.print(" [km/h]");
  Serial.println();
  */
  windvelocity();
  RPMcalc();
  WindSpeed();
  
  float fixSpeed = speedwind*1.0*3600/1000;

  
  // tester ketika >= 2 km per jam
   if(fixSpeed>=2){
    Serial.println("Tarik");
    pulled = true;
    // start dari 0 derajar sampai 180 derajat 
     tarik();
  }
  
  if(fixSpeed<=20){
    noteku = "Aman\"";
//    Serial.println("Keterangan : Aman");
   
  }else if(fixSpeed<=40){
//    Serial.println("Tarik");
    kirim = true;
    pulled = true;
    // start dari 0 derajar sampai 180 derajat 
     tarik();
    noteku = "Awas\"";   
//    Serial.println("Keterangan : Awas");
  }else if(fixSpeed>40){
    kirim = true;
    if(!pulled){
//      Serial.println("Tarik 2");
      pulled = true;
      tarik();
      
       
    }
    noteku = "Bahaya\"";   
//    Serial.println("Keterangan : Bahaya");      
  }
//  Serial.println(noteku);
  if((sec%time_kirim ==0)||(kirim)){
    sec = 1 ;
    kirim = false;
    sendData(fixSpeed);
  }
  
  // Arah Angin
  if(digitalRead(utara)==LOW){
//    Serial.println("ARAH ANGIN : UTARA");
    }
  else if(digitalRead(tl)==LOW){
//    Serial.println("ARAH ANGIN : TIMUR LAUT");
    }
  else if(digitalRead(timur)==LOW){
//    Serial.println("ARAH ANGIN : TIMUR");
    }
  else if(digitalRead(tenggara)==LOW){
//    Serial.println("ARAH ANGIN : TENGGARA");
  }
  else if(digitalRead(selatan)==LOW){
//    Serial.println("ARAH ANGIN : SELATAN");
  }
  else if(digitalRead(bd)==LOW){
//    Serial.println("ARAH ANGIN : BARAT DAYA");
    }
  else if(digitalRead(barat)==LOW){
//    Serial.println("ARAH ANGIN : BARAT");
  }
  else if(digitalRead(bl)==LOW){
//    Serial.println("ARAH ANGIN : BARAT LAUT");
    }

  // Rain Sensor
   nRainVal = analogRead(nRainIn);
  bIsRaining = !(digitalRead(nRainDigitalIn));
  
  if(bIsRaining){
    kirim = false;
    noteku= "Hujuan";
    sendData(fixSpeed);
    strRaining = "YES";
  }
  else{
    strRaining = "NO";
  }
  /*
  Serial.print("Raining?: ");
  Serial.print(strRaining);  
  Serial.print("\t Moisture Level: ");
  Serial.print(nRainVal);
  Serial.print(",");
  Serial.println(fixSpeed);
  */
  
  
  
}
void sendData(int fixSpeed)
{
    kirim = false;
  // Sim 900A 
  
   // Sim 900A Send data
   
   sprintf(fulls,"at+httppara=\"URL\",\"http://antontds.com/Service/insert_from_form.php?id_arduino=%d&wind_speed=%d&note=",arduino_id,fixSpeed);
   strcat(fulls,noteku);
   //snprintf(fulls,sizeof fulls,"at+httppara=\"URL\",\"http://antontds.com/Service/insert_from_form.php?id_arduino=%d&wind_speed=%d&note=%s\"",arduino_id,fixSpeed,noteku);
//   gprsSerial.println("AT+HTTPPARA=\"URL\",\"http://antontds.com/Service/insert_from_form.php?id_arduino="" + id +""&wind_speed=""+wind+""&note=""+note+ ""\"");
  Serial.println(fulls);
   gprsSerial.println(fulls);
   delay(3000);
   toSerial();

   // set http action type 0 = GET, 1 = POST, 2 = HEAD
   gprsSerial.println("AT+HTTPACTION=0");
   delay(3000);
   toSerial();


   // read server response
   gprsSerial.println("AT+HTTPREAD");
   delay(3000);
   toSerial();  
}
// Measure wind speed
void windvelocity()
{
  speedwind = 0;
  counter = 0;
  attachInterrupt(0, addcount, CHANGE);
  unsigned long millis();
  long startTime = millis();
  while(millis() < startTime + period) {}
  
  detachInterrupt(1);
}

void RPMcalc()
{
  RPM=((counter*1.0/jml_celah)*60)/(period*1.0/1000); // Calculate revolutions per minute (RPM)
}

void WindSpeed()
{
  speedwind = ((2 * pi * radio * RPM * 1.0)/60) / 1000; // Calculate wind speed on m/s
}

void addcount()
{
  counter++;
}
