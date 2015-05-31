 /* From: http://learn.adafruit.com/adafruit-motor-shield/using-dc-motors  
    8-wheel robot development, using DC Motors with Adafruit motorshield 
    demonstration of possibilities
    en http://arduinobasics.blogspot.nl/2012/11/arduinobasics-hc-sr04-ultrasonic-sensor.html  
    voor HC-SR04 Ultrasonic Sensor
    December 12 2013
    
    Code werkt hier ok. 
    Motorshield (motor 1,2) uses Timer2 and delay() uses Timer0 
    see Robot_info.txt
    
    Used motors probably need more voltage than 6 x 1.5V = 9V since reaction/ power is low, slow speeds not possible.
 */ 
 
#include <AFMotor.h>

#define TRIGGER_PIN  14  // Arduino pin tied to trigger pin on the ultrasonic sensor. Tx
#define ECHO_PIN     15  // Arduino pin tied to echo pin on the ultrasonic sensor. Rx
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define echoPin 15 // Echo Pin
#define trigPin 14 // Trigger Pin
#define LEDPin 13 // Onboard LED

int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration = 0;
long distance = 0; // Duration is used to calculate distance

  AF_DCMotor motor1(1, MOTOR12_64KHZ); // create motor #3, 64KHz pwm
  AF_DCMotor motor2(2, MOTOR12_64KHZ); // create motor #4


void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LEDPin, OUTPUT); // Use LED indicator (if required)

  motor1.setSpeed(150); // set the speed to x/255 : bij 1Khz draait de vrije motor niet onder 80.
  motor2.setSpeed(140); // set the speed to x/255 : bij 64KHz draait  de vrije motor niet onder 50. 

  Serial.println("Motor test!"); 
}
     
void loop() {
  
  Serial.print("GOGO");
  motor1.setSpeed(150); 
  motor2.setSpeed(140); 
  motor1.run(FORWARD); // turn it on going forward
  motor2.run(FORWARD); // turn it on going forward 
//  uS = sonar1.ping()/ US_ROUNDTRIP_CM; // Send ping, get ping time in microseconds (uS) and convert to distance.  
  while (distance > 35 || distance == -1) {
    digitalWrite(LEDPin, LOW); 
//    Serial.print(" - move : ");    
//    Serial.print(uS); // Convert ping time to distance in cm and print result (0 = outside set distance range)
//    delay(100);
    sonar(); 
  }
  
  Serial.print("TURN"); 
  motor1.setSpeed(100); 
  motor2.setSpeed(80); 
  motor1.run(BACKWARD); // turn
  motor2.run(BACKWARD); //  
  while (distance <= 40 && distance != -1) {
    digitalWrite(LEDPin, HIGH); 

//    Serial.print(" - turn : ");    
//    Serial.print(uS); // print result 
//    delay(100);
    sonar(); 
  }
}
    
void sonar() {
/* The following trigPin/echoPin cycle is used to determine the
 distance of the nearest object by bouncing soundwaves off of it. */ 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
 
 //Calculate the distance (in cm) based on the speed of sound.
  distance = duration/58.2;
 
  if (distance >= maximumRange || distance <= minimumRange){
    distance = -1;
    Serial.println("-1");
 }
  else {
   Serial.println(distance);
   delay(50);        // Delay 50ms before next reading.
  }
}
    
  

