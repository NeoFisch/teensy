/* Teensyduino Tutorial Pulsed Output : Pulse Width Modulation
   https://www.pjrc.com/teensy/td_pulse.html
   https://www.pjrc.com/teensy/tutorial2.html
*/

const byte NUMBER_OF_INTS = 3;
const int INTERN_LED_PIN = 13;
const int INTERN_ANALOG_PIN_LED_PRINTER = 20; // print output LEDS
const int INTERN_ANALOG_PIN_LED_BUTTON = 22; // button LED

// set default sleepTime range to decimal number for switch case
const unsigned int SUPER_SHORT = 1;
const unsigned int VERY_SHORT = 2;
const unsigned int SHORT = 3;
const unsigned int MEDIUM = 4;
const unsigned int LONG = 5;

// Intensity for analog PIN. Range: 0..255  (0 very bright), (255 alsmost off)
const unsigned int INSENSITY_OFF = 0;
const unsigned int INSENSITY_LOW = 50;
const unsigned int INSENSITY_MID = 140;
const unsigned int INSENSITY_BRIGHT = 200;
const unsigned int INSENSITY_VERY_BRIGHT = 255;

const unsigned int FADE_INSTENSITY_STEPS = 40;  // steps for fading
const unsigned int FADE_INSTENSITY_DELAY = 100;  // delay for fading

const long int FOTO_SHOOT_DELAY_IN_SEC = 30;   // 2 sec ==  2000ms   and     45000ms == 45 sec
const long int PRINT_OUT_DELAY_IN_SEC = 41; //301

const unsigned int BLINK_PRINT_LED_DELAY = 500;


// calculate new const
const long int PRINT_OUT_DELAY_IN_MS = PRINT_OUT_DELAY_IN_SEC*1000;

// PWM creates an output with analog-like properties, where you can control the intensity in fine steps, even though the signal is really a digital pin rapidly pulsing.
unsigned int intensity[NUMBER_OF_INTS] = {
  50, 140, 250
};

// LONG, SHORT and how many times it should blink
void blinkInternLed (int times = 1, const unsigned int range = SHORT) {
  
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
    digitalWrite(INTERN_LED_PIN, HIGH);
    delay(sleepTime);    
    digitalWrite(INTERN_LED_PIN, LOW);
    delay(sleepTime);
    times--;
  }
}


void blinkAnalogOutputLed (unsigned int analogPin = NULL, unsigned int times = 1, const int unsigned range = SHORT, const int intensity = INSENSITY_MID, const int comesFromIntensity = INSENSITY_MID, const int setBackToIntensity = INSENSITY_MID) {
  
   if (analogPin != NULL) {
          ////////////////////////
          // set default
          unsigned int sleepTime = 500;
          // select sleepTime by range
          switch (range) {
             
             case SUPER_SHORT:
                sleepTime = 20;
                break;
                  
             case VERY_SHORT:
                sleepTime = 80;
                break;
                  
             case SHORT:
                sleepTime = 200;
                break;
             
             case MEDIUM:   
               sleepTime = 800;
               break;
                
             case LONG:   
               sleepTime = 1200;
               break;
              
             default:
                sleepTime = 500;
                break;
          }
      
         int fadeIntensity = comesFromIntensity; // 0
         // activate LED on analog pin with random intesity  
         while (times) {
                   Serial.print("INTENSITY BEFORE IN LOOP:");
                   Serial.println (intensity);
                   Serial.print("FADE IN .....");
                   // fade in the led light in 10 decimal steps of intensity
                   
                   while (fadeIntensity < intensity) {
                           if(fadeIntensity > 255) {fadeIntensity=255;}
                           analogWrite(analogPin, fadeIntensity);
                           fadeIntensity+=FADE_INSTENSITY_STEPS;
                           Serial.print("fadeINIntensity: ");
                           Serial.println(fadeIntensity);
                           delay(FADE_INSTENSITY_DELAY);
                   }
                   analogWrite(analogPin, intensity);
                   
                   // set full intensity on analogPin
                   //analogWrite(analogPin, intensity);
                   delay(sleepTime);
                  
                   Serial.print("FADE OUT .....");
                   // fade out the led light in 10 decimal steps of intensity
                   fadeIntensity = intensity;
        
                   Serial.print("INTENSITY BEFORE OUT LOOP:");
                   Serial.println (intensity);
        
                   while (fadeIntensity > setBackToIntensity) {
                           if(fadeIntensity < 0) {fadeIntensity=0;}
                           analogWrite(analogPin, fadeIntensity);
                           fadeIntensity-=FADE_INSTENSITY_STEPS;
                           Serial.print("fadeOUTIntensity: ");
                           Serial.println(fadeIntensity);
                           delay(FADE_INSTENSITY_DELAY);
                   }
                   analogWrite(analogPin, setBackToIntensity);
        
        /*
                  if(leaveLedOn == false) {
                      analogWrite(analogPin, setBackToIntensity);
                      Serial.println(">>>>  LeaveLedOn == false.   SHUT LED OFF");
                  }*/
                  
                  delay(sleepTime);
                  times--;
        }
    }
}

void setup()   {   
  Serial.begin(38400);  //9600 baud  
  pinMode(12, INPUT_PULLUP); // INPUT_PULLUP serves to pull the voltage back up when you are not pressing the button. You can activate the pullup resistor by using INPUT_PULLUP with pinMode in your setup function.
  
  pinMode(INTERN_LED_PIN, OUTPUT);
  
  pinMode(INTERN_ANALOG_PIN_LED_PRINTER, OUTPUT);
  pinMode(INTERN_ANALOG_PIN_LED_BUTTON, OUTPUT);
  
  // set default intesity to zero
  //analogWrite(INTERN_ANALOG_PIN_LED_PRINTER, INSENSITY_OFF);
  //analogWrite(INTERN_ANALOG_PIN_LED_BUTTON, INSENSITY_OFF);
  /*
  blinkInternLed(1, SHORT);
  delay(2500);
  // intialization for MacOS to identify keyboard - if not working close the init dialog on MacOS system
  blinkInternLed(2, SHORT);
  Keyboard.set_modifier(MODIFIERKEY_SHIFT);  
  Keyboard.set_modifier(0);
  delay(2500);
 */
  delay(200);
  
  blinkInternLed(3, SHORT);

  // activate button LED
    analogWrite(INTERN_ANALOG_PIN_LED_BUTTON, INSENSITY_VERY_BRIGHT);

  // deactivate printer LEDS
  analogWrite(INTERN_ANALOG_PIN_LED_PRINTER, INSENSITY_OFF);
}

void loop()                     
{
  if (digitalRead(12) == LOW)
  {
    Serial.println("Button pressed!!!");
    blinkInternLed(1, SHORT);
    // output simulate space bar pressed
    //Keyboard.print(" ");
    // output simulate Enter/Return key press
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    blinkAnalogOutputLed(INTERN_ANALOG_PIN_LED_BUTTON, 1, SUPER_SHORT, INSENSITY_VERY_BRIGHT, INSENSITY_VERY_BRIGHT, INSENSITY_OFF);
    //analogWrite(INTERN_ANALOG_PIN_LED_BUTTON, INSENSITY_OFF);
    //digitalWrite(INTERN_ANALOG_PIN_LED_BUTTON, LOW);  // shut the led completly off

    delay(FOTO_SHOOT_DELAY_IN_SEC * 1000);
    
 //   int randNo = random(0,NUMBER_OF_INTS);


    
    // activate LED on analog pin with random intesity
    // analogWrite(INTERN_ANALOG_PIN_LED_PRINTER, intensity[randNo]);
    //blinkAnalogOutputLed(INTERN_ANALOG_PIN_LED_PRINTER, 5, SHORT, INSENSITY_VERY_BRIGHT);

    long int loopDelay = PRINT_OUT_DELAY_IN_MS;
    while(loopDelay > 0) {
      Serial.println("Print LED ON");
      analogWrite(INTERN_ANALOG_PIN_LED_PRINTER, INSENSITY_VERY_BRIGHT);
      delay(BLINK_PRINT_LED_DELAY/2); // wait half the time when led is off
      
      Serial.println("Print LED OFF");
      analogWrite(INTERN_ANALOG_PIN_LED_PRINTER, INSENSITY_OFF);
      delay(BLINK_PRINT_LED_DELAY/2); // wait other half when led is on
      
      //blinkAnalogOutputLed(INTERN_ANALOG_PIN_LED_BUTTON, 3, SHORT, INSENSITY_VERY_BRIGHT, INSENSITY_VERY_BRIGHT, INSENSITY_MID);
  
      loopDelay-=BLINK_PRINT_LED_DELAY;
      Serial.print("delay remaining: ");
      Serial.println(loopDelay);
    }

/*    
    digitalWrite(INTERN_ANALOG_PIN_LED_PRINTER, LOW);
    
    // set button back on
    analogWrite(INTERN_ANALOG_PIN_LED_BUTTON, INSENSITY_MID);
    
    
    // DEBUG OUT
    Serial.print("Intensity is set to: ");  // here you could debug with serial monitor
  //  Serial.print(intensity[randNo]);
    Serial.print(" on analog PIN: ");
    Serial.println(INTERN_ANALOG_PIN_LED_PRINTER);

    // wait until next button interupt will be recognized
    //delay(250);
    */

    delay(3);

    // set back to default button ld on    
    blinkAnalogOutputLed(INTERN_ANALOG_PIN_LED_BUTTON, 1, SHORT, INSENSITY_VERY_BRIGHT, INSENSITY_OFF, INSENSITY_VERY_BRIGHT);
    analogWrite(INTERN_ANALOG_PIN_LED_PRINTER, INSENSITY_OFF);
  }
}
