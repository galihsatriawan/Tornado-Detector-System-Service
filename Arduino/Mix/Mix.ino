// Pin definitions
# define windPin 2 // Receive the data from sensor
#define utara 3
#define tl 4
#define timur 5
#define tenggara 6
#define selatan 7
#define bd 8
#define barat 9
#define bl 10
// Servo Position
int time_pulled = 0;
bool pulled = false;
int maxTime = 1000*60*10;

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
int jml_celah = 22, pos; // jumlah celah sensor

// Variable definitions
unsigned int Sample = 0; // Sample number
unsigned int counter = 0; // B/W counter for sensor
unsigned int RPM = 0; // Revolutions per minute
float speedwind = 0; // Wind speed (m/s)

void setup()
{
myservo.detach();
  myservo.attach(11);
  myservo.write(180);

// sets the serial port to 9600
Serial.begin(115200);
// Set the pins


pinMode(2, INPUT);
digitalWrite(2, HIGH);
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

// Splash screen
Serial.println("ANEMOMETER");
Serial.println("**********");
Serial.println("Based on depoinovasi anemometer sensor");
Serial.print("Sampling period: ");
Serial.print(period/1000);
Serial.print(" seconds every ");
Serial.print(delaytime/1000);
Serial.println(" seconds.");
Serial.println("** You could modify those values on code **");
Serial.println();
}

void loop()
{
  //if pulled , count the time
  if(pulled){
    time_pulled ++;
  }else time_pulled = 0;

  if(time_pulled == maxTime){
    // start dari 180 derajat ke 0 derajat , ulurkan
       for(pos = 180; pos>=1; pos-=2)  
       {
        // memberitahu servo untuk pergi ke posisi  'pos'                                
        myservo.write(pos);                 
        // tunggu 15ms untuk pencapaian  posisi servo    
        delay(15);                        
       }
       pulled = false;
  }
   
 
  Sample++;
  Serial.print(Sample);
  Serial.print(": Start measurement…");
  windvelocity();
  Serial.println("t finished.");
  Serial.print("Counter: ");
  Serial.print(counter);
  Serial.print("; RPM: ");
  RPMcalc();
  Serial.print(RPM);
  Serial.print("; Wind speed: ");
  WindSpeed();
  float fixSpeed = speedwind*3600/1000;
  Serial.print(fixSpeed);
  //Serial.print(" [m/s]");
  Serial.print(" [km/h]");
  Serial.println();
  if(fixSpeed<=20){
    
    Serial.println("Keterangan : Aman");
   
  }else if(fixSpeed<=40){
    pulled = true;
    // start dari 0 derajar sampai 180 derajat 
     for(pos = 0; pos < 180; pos += 4)  
       {
        // pada posisi 1 derajat
        // memberitahu servo untuk pergi ke posisi  'pos'
       
        myservo.write(pos);                 
       
        // tunggu 15ms untuk pencapaian  posisi servo    
        delay(15);                  
       } 
       
    Serial.println("Keterangan : Awas");
  }else if(fixSpeed>40){
    Serial.println("Keterangan : Bahaya");
        
  }
  

  // Arah Angin
  if(digitalRead(utara)==LOW){Serial.println("ARAH ANGIN : UTARA");}
  else if(digitalRead(tl)==LOW){Serial.println("ARAH ANGIN : TIMUR LAUT");}
  else if(digitalRead(timur)==LOW){Serial.println("ARAH ANGIN : TIMUR");}
  else if(digitalRead(tenggara)==LOW){Serial.println("ARAH ANGIN : TENGGARA");}
  else if(digitalRead(selatan)==LOW){Serial.println("ARAH ANGIN : SELATAN");}
  else if(digitalRead(bd)==LOW){Serial.println("ARAH ANGIN : BARAT DAYA");}
  else if(digitalRead(barat)==LOW){Serial.println("ARAH ANGIN : BARAT");}
  else if(digitalRead(bl)==LOW){Serial.println("ARAH ANGIN : BARAT LAUT");}

  // Rain Sensor
   nRainVal = analogRead(nRainIn);
  bIsRaining = !(digitalRead(nRainDigitalIn));
  
  if(bIsRaining){
    strRaining = "YES";
  }
  else{
    strRaining = "NO";
  }
  
  Serial.print("Raining?: ");
  Serial.print(strRaining);  
  Serial.print("\t Moisture Level: ");
  Serial.print(nRainVal);
  Serial.print(",");
  Serial.println(fixSpeed);
  delay(1000);
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
  RPM=((counter/jml_celah)*60)/(period/1000); // Calculate revolutions per minute (RPM)
}

void WindSpeed()
{
  speedwind = ((2 * pi * radio * RPM)/60) / 1000; // Calculate wind speed on m/s
}

void addcount()
{
  counter++;
}
