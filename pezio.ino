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

int LED2 = 11; //the pin we connect the LED

void setup() 
{
  Serial.begin(9600);
   pinMode(LED, OUTPUT); //set the LED pin as OUTPUT
   pinMode(LED2, OUTPUT); //set the LED pin as OUTPUT
}

void loop() 
{
  // Read Piezo ADC value in, and convert it to a voltage
  int piezoADC = analogRead(PIEZO_PIN);
  float piezoV = piezoADC / 1023.0 * 5.0;
  //Serial.println(piezoV); // Print the voltage.
  Serial.println(piezoADC);
  if(piezoADC > 9){
    //Serial.println("MORE THAN TWO");
    digitalWrite(LED2, HIGH); //write 1 or HIGH to led pin
    tone(10, 2000, 500);
    delay(500);
    tone(10, 5000, 500);
    
    if(piezoADC > 14){
      //Serial.println("MORE THAN TWO");
      digitalWrite(LED, HIGH); //write 1 or HIGH to led pin
      
    }
      delay(1500);
  }
  digitalWrite(LED, LOW); //write 0 or LOW to led pin
  digitalWrite(LED2, LOW); //write 0 or LOW to led pin
    
}
