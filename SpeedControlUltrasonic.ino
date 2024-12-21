#include <VARSTEP_ultrasonic.h> 

#define trigger_pin 8
#define echo_pin 9               
#define motor_pin 10             

double distance_cm, distance_m;  
int pwm_value;                  

VARSTEP_ultrasonic my_HCSR04(trigger_pin, echo_pin); 

void setup() {
  Serial.begin(9600);           
  pinMode(motor_pin, OUTPUT);   

void loop() {
  distance_cm = my_HCSR04.distance_cm(); 
  distance_m = my_HCSR04.distance_m();   

  if (distance_cm == -1.0 || distance_cm > 10) { // Check if no distance is detected or if the distance is greater than 10 cm
    Serial.println("No distance detected");      
    analogWrite(motor_pin, 0);                   
  } else {
    Serial.print("Distance: ");                 
    Serial.print(distance_cm);                  
    Serial.print("cm | ");
    Serial.print(distance_m);                  
    Serial.println("m");

    
    pwm_value = map(distance_cm, 10, 2, 0, 255); // Map the distance range (10 cm to 2 cm) to a PWM range (0 to 255)
    pwm_value = constrain(pwm_value, 0, 255);

    analogWrite(motor_pin, pwm_value);          
  }

  delay(100);
}
