#define utara 3
#define tl 4
#define timur 5
#define tenggara 6
#define selatan 7
#define bd 8
#define barat 9
#define bl 10

void setup() 
{
  Serial.begin(9600);
  pinMode(utara,INPUT_PULLUP);
  pinMode(tl,INPUT_PULLUP);
  pinMode(timur,INPUT_PULLUP);
  pinMode(tenggara,INPUT_PULLUP);
  pinMode(selatan,INPUT_PULLUP);
  pinMode(bd,INPUT_PULLUP);
  pinMode(barat,INPUT_PULLUP);
  pinMode(bl,INPUT_PULLUP);
}

void loop()
{
if(digitalRead(utara)==LOW){Serial.println("ARAH ANGIN : UTARA");}
else if(digitalRead(tl)==LOW){Serial.println("ARAH ANGIN : TIMUR LAUT");}
else if(digitalRead(timur)==LOW){Serial.println("ARAH ANGIN : TIMUR");}
else if(digitalRead(tenggara)==LOW){Serial.println("ARAH ANGIN : TENGGARA");}
else if(digitalRead(selatan)==LOW){Serial.println("ARAH ANGIN : SELATAN");}
else if(digitalRead(bd)==LOW){Serial.println("ARAH ANGIN : BARAT DAYA");}
else if(digitalRead(barat)==LOW){Serial.println("ARAH ANGIN : BARAT");}
else if(digitalRead(bl)==LOW){Serial.println("ARAH ANGIN : BARAT LAUT");}
delay(1000);
}
