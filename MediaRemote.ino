//Based on debounce example at: https://www.arduino.cc/en/Tutorial/Debounce

#include <SoftwareSerial.h>
// constants won't change. They're used here to
// set pin numbers:
const int buttonPins[3] = {2,3,4};    // the numbers of the pushbutton pins

// Variables will change:
int buttonState[3];             // the current reading for each input pin
int lastButtonState[3] = {LOW, LOW, LOW};   // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime[3] = {0,0,0};  // the last time each output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

// instantiate a SoftwareSerial port on pins 10 & 11
SoftwareSerial bluetooth(10, 11);

void setup() {
  // loop over the input pins and initialize them
  for(int i=0;i<=2;i++){
    int buttonPin = buttonPins[i];
    pinMode(buttonPin, INPUT);
  }

  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop() {
  // loop over the array of pins and check for state changes
  for(int i=0;i<=2;i++){
    int buttonPin = buttonPins[i];
    // read the state of the switch into a local variable:
    int reading = digitalRead(buttonPin);
  
    // check to see if you just pressed the button
    // (i.e. the input went from LOW to HIGH),  and you've waited
    // long enough since the last press to ignore any noise:
  
    // If the switch changed, due to noise or pressing:
    if (reading != lastButtonState[i]) {
      // reset the debouncing timer
      lastDebounceTime[i] = millis();
    }
  
    if ((millis() - lastDebounceTime[i]) > debounceDelay) {
      // whatever the reading is at, it's been there for longer
      // than the debounce delay, so take it as the actual current state:
  
      // if the button state has changed:
      if (reading != buttonState[i]) {
        buttonState[i] = reading;
  
        // only toggle the LED if the new button state is HIGH
        if (buttonState[i] == HIGH) {
            switch(i){
              case 0:
                bluetooth.println("prev");
                break;
              case 1:
                bluetooth.println("play");
                break;
              case 2:
                bluetooth.println("next");
                break;
            }
        }   
      }
    }
  
    // save the reading.  Next time through the loop,
    // it'll be the lastButtonState:
    lastButtonState[i] = reading;
  }
  delay(5);
}
