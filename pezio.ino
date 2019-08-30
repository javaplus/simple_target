/******************************************************************************
Piezo_Vibration_Sensor.ino
Example sketch for SparkFun's Piezo Vibration Sensor
  (https://www.sparkfun.com/products/9197)
Jim Lindblom @ SparkFun Electronics
April 29, 2016

- Connect a 1Mohm resistor across the Piezo sensor's pins.
- Connect one leg of the Piezo to GND
- Connect the other leg of the piezo to A0

Vibrations on the Piezo sensor create voltags, which are sensed by the Arduino's
A0 pin. Check the serial monitor to view the voltage generated.

Development environment specifics:
Arduino 1.6.7
******************************************************************************/
const int PIEZO_PIN = A0; // Piezo output
int LED = 2; //the pin we connect the LED
int LED_LIGHT_HIT = 11; //the pin we connect the LED
int flickerInterval = 100;
unsigned long startFlickerTime = 0;

unsigned long lastLightHit = 0;
unsigned long lastHardHit = 0;
unsigned long timeToReactToHit = 1500;

boolean areFlickering = false;
boolean reactingToHit = false;
int tonePlayTime = 500;
int vibrationLevel = 0;
void setup() 
{
  Serial.begin(9600);
   pinMode(LED, OUTPUT); //set the LED pin as OUTPUT
   pinMode(LED_LIGHT_HIT, OUTPUT); //set the LED pin as OUTPUT
}

void loop() 
{
  
  // Read Piezo ADC value in, and convert it to a voltage
  if(!reactingToHit){
    vibrationLevel = analogRead(PIEZO_PIN);
    // float piezoV = vibrationLevel / 1023.0 * 5.0;
    //Serial.println(piezoV); // Print the voltage.
     // Serial.println(vibrationLevel);
  }
  
  if(vibrationLevel > 9){
    // if not currently reacting to a hit read the time (i.e. it's a new hit)
    if(!reactingToHit){
      lastLightHit = millis();
    }
    reactingToHit = true;
    //Serial.println("MORE THAN TWO");
    if(!areFlickering){
      digitalWrite(LED_LIGHT_HIT, HIGH); //write 1 or HIGH to led pin
      tone(13, 2000, 50);
    }
    
    
    if(vibrationLevel > 14 && !areFlickering){
      //Serial.println("MORE THAN TWO");
      digitalWrite(LED, HIGH); //write 1 or HIGH to led pin
      
    }
  }

  // see if time has run out for us to respond to hit
  if(millis() - lastLightHit > timeToReactToHit){
    // we've responded to the hit long enough
    reactingToHit = false;
    lastLightHit = 0;
    
  }
  int mod = (millis()-lastLightHit)%100;

  if(reactingToHit && mod ==0){
    if(!areFlickering){
     startFlickerTime = millis(); 
    }
    areFlickering=true;
  }
  if(areFlickering){
    digitalWrite(LED, LOW); //write 0 or LOW to led pin
    digitalWrite(LED_LIGHT_HIT, LOW); //write 0 or LOW to led pin
  }
  if(millis()-startFlickerTime > flickerInterval){
    areFlickering = false;
    startFlickerTime = 0;
  }
  if (!reactingToHit){
    vibrationLevel = 0;
    digitalWrite(LED, LOW); //write 0 or LOW to led pin
    digitalWrite(LED_LIGHT_HIT, LOW); //write 0 or LOW to led pin
  }
    
}
