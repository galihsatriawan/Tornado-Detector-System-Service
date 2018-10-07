#define utara 0
#define tl 13
#define timur 2
#define tenggara 3
#define selatan 4
#define bd 7
#define barat 8
#define bl 9

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
