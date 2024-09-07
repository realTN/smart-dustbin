#include <Servo.h> 
#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
#define trigpin1 3 
#define echopin1 2 
Servo servoMain; 
LiquidCrystal lcd(11, 12, 4, 5, 6, 7); // Creates an LCD object. 

const int trigPin = 9; 
const int echoPin = 10; 
long duration, duration1; 
int distanceCm, distanceCm1; 
int percent; 
void setup() { 
lcd.begin(16, 2); 
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT); 
servoMain.attach(8); 
pinMode(trigpin1, OUTPUT); 
pinMode(echopin1, INPUT); 
Serial.begin(9600); 
} 
 
void loop() { 
digitalWrite(trigPin, LOW); 
delayMicroseconds(2); 
digitalWrite(trigPin, HIGH); 
delayMicroseconds(10); 
digitalWrite(trigPin, LOW); 
duration = pulseIn(echoPin, HIGH); 
distanceCm = duration * 0.034 / 2; 
if (distanceCm < 60) { //height of dustbin is assumed as 60cm
lcd.setCursor(0, 0); 
percent = (01 - (distanceCm / 60.0)) * 100; // Corrected 

 lcd.setCursor(0, 0); // Move to the beginning of the first row

  // Clear the line by printing spaces
  lcd.print("                "); // Print 16 spaces for a 16x2 LCD
  lcd.setCursor(0, 0); // Reset cursor position to the beginning of the line

  // Print the updated garbage level
  lcd.print("Level: ");
  lcd.print(percent);
  lcd.print(" %");

   
} 
delay(10); 
digitalWrite(trigpin1, LOW); // Start with LOW 
delayMicroseconds(2); // Delay for stabilization 
digitalWrite(trigpin1, HIGH); // Send pulse 
delayMicroseconds(10); // Pulse width 

digitalWrite(trigpin1, LOW); // Stop pulse 
duration1 = pulseIn(echopin1, HIGH); 
distanceCm1 = (duration1 / 2) / 29.1; 
if (distanceCm1 < 30) { //lid opens when the person is lesser than 30 cm near the dustbin
delay(1000); 
servoMain.write(180); 
delay(2000); 
} else { 
servoMain.write(0); 
delay(1000); 
} 
}