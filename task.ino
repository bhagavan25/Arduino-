#include <Arduino.h>
int sensorValue = 0;
void delay_ms(unsigned int ms)
{
  TCCR1A = 0; // Clear Timer1 control register A
  TCCR1B = 0; // Clear Timer1 control register B

  // Set Timer1 prescaler to 64
  TCCR1B |= (1 << CS11) | (1 << CS10); // Clock/64

  // Set initial value for Timer1
  TCNT1 = 0;
  //compare value:(ms*16000)/(64*1000)=625
  TCNT1 = 65535 - (ms/4);
  while((TIFR1&(1<<TOV1))==0);
  TIFR1 |= (1<<TOV1);
  TCNT1 = 0; //set timer1 counter to 0
}
void setup()
{
  pinMode(A0, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  // read the value from the sensor
  sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  if(sensorValue<30)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay_ms(250);
    digitalWrite(LED_BUILTIN, LOW);
    delay_ms(250);
  }
  else
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay_ms(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay_ms(500);
  }
}
