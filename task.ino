#include <Arduino.h>
#define LM35_PIN A0
#define LED 13
int temperature = 0;

void setup()
{
  pinMode(LM35_PIN, INPUT);
  pinMode(LED, OUTPUT);
}

void loop()
{
  // read the value from the sensor
  temperature=readTemperature();
  if(temperature<30)
  {
    //blinking LED with 250ms delay
    digitalWrite(LED, HIGH);
    delay_ms(250);
    digitalWrite(LED, LOW);
    delay_ms(250);
  }
  else if(temperature>30)
  {
    //blinking LED with 500ms delay
    digitalWrite(LED, HIGH);
    delay_ms(500);
    digitalWrite(LED, LOW);
    delay_ms(500);
  }
}
int readTemperature() 
{
  // Read analog value from LM35 sensor
  int sensorValue = analogRead(LM35_PIN);
  
  // Convert analog value to temperature in Celsius
  float temperatureC = (sensorValue * 5.0) / 1024.0 * 100.0;

  // Return temperature in Celsius
  return (int)temperatureC;
}
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
