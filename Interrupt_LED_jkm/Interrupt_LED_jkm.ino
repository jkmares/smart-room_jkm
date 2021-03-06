#include <TimerOne.h>
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixel(16, 17, NEO_GRB + NEO_KHZ800);

// This example uses the timer interrupt to blink an LED
// and also demonstrates how to share a variable between
// the interrupt and the main program.


const int led = 17;  // the pin with a LED

void setup(void)
{
  //pixel.begin();
    //pixel.show();
   //pixel.clear();
  pinMode(led, OUTPUT);
  Timer1.initialize(300000);
  Timer1.attachInterrupt(blinkLED); // blinkLED to run every 0.15 seconds
  Serial.begin(9600);
}


// The interrupt will blink the LED, and keep
// track of how many times it has blinked.
int ledState = LOW;
volatile unsigned long blinkCount = 0; // use volatile for shared variables

void blinkLED(void)
{
  if (ledState == LOW) {
    ledState = HIGH;
      pixel.fill(0xffffff,0,16);
      pixel.setBrightness(10); 
      pixel.show();
    blinkCount = blinkCount + 1;  // increase when LED turns on
  } else {
    ledState = LOW;
    pixel.clear();
  }
  digitalWrite(led, ledState);
}


// The main program will print the blink count
// to the Arduino Serial Monitor
void loop(void)
{
  unsigned long blinkCopy;  // holds a copy of the blinkCount

  // to read a variable which the interrupt code writes, we
  // must temporarily disable interrupts, to be sure it will
  // not change while we are reading.  To minimize the time
  // with interrupts off, just quickly make a copy, and then
  // use the copy while allowing the interrupt to keep working.
  noInterrupts();
  blinkCopy = blinkCount;
  interrupts();

  Serial.print("blinkCount = ");
  Serial.println(blinkCopy);
  delay(100);
}
