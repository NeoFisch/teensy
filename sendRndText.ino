/* Used Serial Monitor Example, Teensyduino Tutorial #3
   http://www.pjrc.com/teensy/tutorial3.html

	 and inspirations came from:
	 http://makezine.com/projects/make-32/the-awesome-button/
	 http://makezine.com/2011/04/08/the-awesome-button/
	 
	 Uses 38400 baud connection via USB
	 simulates Keyboard and sends three different words randomly to the client PC
*/

const byte NUMBER_OF_WORDS = 3;
const int internLedPin = 13;
const int SHORT = 1;
const int LONG = 2;

char* names[NUMBER_OF_WORDS] = {
  "super", "toll", "wunderbar"
};

void blinkInternLed (int times = 1, const int range = SHORT) {
  
    int sleepTime = 500;
    
    switch (range) {
      case SHORT:
          sleepTime = 500;
          break;
          
       case LONG:   
         sleepTime = 1000;
         break;
        
       default:
          sleepTime = 500;
          break;
    }
  
  while (times) {
    digitalWrite(internLedPin, HIGH);
    delay(sleepTime);    
    digitalWrite(internLedPin, LOW);
    delay(sleepTime);
    times--;
  }
}

void setup()   {
  pinMode(internLedPin, OUTPUT);
  blinkInternLed(1, SHORT);
  delay(2500);
  // intialization for MacOS to identify keyboard - if not working close the init dialog on MacOS system
  blinkInternLed(2, SHORT);
  Keyboard.set_modifier(MODIFIERKEY_SHIFT);  
  Keyboard.set_modifier(0);
  Serial.begin(38400);  //9600 baud
  pinMode(12, INPUT_PULLUP); // INPUT_PULLUP serves to pull the voltage back up when you are not pressing the button. You can activate the pullup resistor by using INPUT_PULLUP with pinMode in your setup function.
  delay(2500);
  blinkInternLed(3, SHORT);
}

void loop()                     
{
  if (digitalRead(12) == LOW)
  {
    Serial.println("Button pressed!!!");
    blinkInternLed(1, SHORT);
    int randNo = random(0,NUMBER_OF_WORDS);
    Keyboard.print(names[randNo]);
    Keyboard.print(" ");
    Serial.print("Random number was: ");  // here you could debug with serial monitor
    Serial.println(randNo);
    //delay(250);
    delay(1);
  }
}
