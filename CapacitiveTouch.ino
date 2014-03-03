#include <CapacitiveSensor.h>

/*
 * Uses CapitiveSense Library by Paul Badger 2008
 * Uses a high value resistor between send pin and receive pin
 *
 * All signals are active low
*/

const int cap_left_in = 2;
const int cap_right_in = 4;
const int cap_left_out = 8;
const int cap_right_out = 9;
const int ir_reach = 6;
const int ir_back = 7;

const int led_mirror = 11;

CapacitiveSensor cap_left_sensor = CapacitiveSensor(3, cap_left_in); //pin 2 sensor
CapacitiveSensor cap_right_sensor = CapacitiveSensor(3,cap_right_in); //pin 6 sensor

long cap_left_value = 0;
long cap_right_value = 0;

long cap_left_threshold = 200;
long cap_right_threshold = 200;

long cap_autocal_value = 5000;
byte cap_samples = 25;

void setup()                    
{
 //Serial.begin(9600);
 
 pinMode(cap_left_out, OUTPUT);
 digitalWrite(cap_left_out, HIGH);

 pinMode(cap_right_out, OUTPUT);
 digitalWrite(cap_right_out, HIGH); 
 
 pinMode(ir_reach, INPUT);
 pinMode(ir_back, INPUT);
 
 pinMode(led_mirror, OUTPUT);
}

void loop()                    
{
  //long start = millis();
  
  cap_left_value = cap_left_sensor.capacitiveSensor(cap_samples);
  cap_right_value = cap_right_sensor.capacitiveSensor(cap_samples);

  if(digitalRead(ir_back) == HIGH) {
    //Serial.println("Not back...");
    digitalWrite(led_mirror, HIGH);
    if(cap_left_value > cap_left_threshold) { //paw on left sensor?
      cap_left_sensor.set_CS_AutocaL_Millis(0xFFFFFFFF); //autocal off
      digitalWrite(cap_left_out, LOW);
    } else {
      cap_left_sensor.set_CS_AutocaL_Millis(cap_autocal_value); //autocal on
      digitalWrite(cap_left_out, HIGH);
    }
    if(cap_right_value > cap_right_threshold) { //paw on right sensor?
      cap_right_sensor.set_CS_AutocaL_Millis(0xFFFFFFFF); //autocal off
      digitalWrite(cap_right_out, LOW);
    } else {
      cap_right_sensor.set_CS_AutocaL_Millis(cap_autocal_value); //autocal on
      digitalWrite(cap_right_out, HIGH);
    }
  } else {
     //Serial.println("BACK!");
     digitalWrite(led_mirror, LOW);
     cap_left_sensor.reset_CS_AutoCal();
     cap_right_sensor.reset_CS_AutoCal();
  }
/*
  Serial.print(millis() - start); //check on performance in milliseconds
  Serial.print("\t");

  Serial.print(cap_left_value); //print sensor output 1
  Serial.print("\t");
  Serial.println(cap_right_value); //print sensor output 2
  delay(50);
*/  
}
