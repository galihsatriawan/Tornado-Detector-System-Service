#include "TimerOne.h"
unsigned int counter=0;


void docount()  // counts from the speed sensor
{
  counter++;  // increase +1 the counter value
} 

void timerIsr()
{
  Timer1.detachInterrupt();  //stop the timer
  Serial.print("Motor Speed: "); 
  int rotation = (counter / 20);  // divide by number of holes in Disc
  Serial.print(rotation,DEC);  
  Serial.println(" Rotation per minutes"); 
  counter=0;  //  reset counter to zero
  Timer1.attachInterrupt( timerIsr );  //enable the timer
}

void setup() 
{
  Serial.begin(9600);
  
// pinMode(2,OUTPUT);
  
  Timer1.initialize(6000000); // set timer for 1sec
  attachInterrupt(0, docount, RISING);  // increase counter when speed sensor pin goes High
  Timer1.attachInterrupt( timerIsr ); // enable the timer
} 

void loop()
{
  
}
