// Pin definitions
# define windPin 10 // Receive the data from sensor

// Constants definitions
const float pi = 3.14159265; // pi number
int period = 1000; // Measurement period (miliseconds)
int delaytime = 1000; // Time between samples (miliseconds)
int radio = 80; // Distance from center windmill to outer cup (mm)
int jml_celah = 20; // jumlah celah sensor

// Variable definitions
unsigned int Sample = 0; // Sample number
unsigned int counter = 0; // B/W counter for sensor
unsigned int RPM = 0; // Revolutions per minute
float speedwind = 0; // Wind speed (m/s)

void setup()
{
// Set the pins
pinMode(10, INPUT);
digitalWrite(10, HIGH);

// sets the serial port to 9600
Serial.begin(9600);

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
Sample++;
Serial.print(Sample);
Serial.print(": Start measurement…");
windvelocity();
Serial.println(" finished.");
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
  Serial.println("Keterangan : Awas");
}else if(fixSpeed>40){
  Serial.println("Keterangan : Bahaya");
}
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
