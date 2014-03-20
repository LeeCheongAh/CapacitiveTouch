#include <CapacitiveSensor.h>

/*
 * Uses CapitiveSense Library by Paul Badger 2008
 * Uses a high value resistor between send pin and receive pin
 *
 * All signals are active low
*/
int countLoop = 0;

const int cap_left_in = 4;
const int cap_shared = 3;
const int cap_right_in = 2;

const int cap_left_out = 9;
const int cap_right_out = 10;
const int ir_reach = 6;
const int ir_back = 7;

const int led_mirror = 11;

//share pin 3
CapacitiveSensor cap_left_sensor = CapacitiveSensor(cap_shared, cap_left_in);
CapacitiveSensor cap_right_sensor = CapacitiveSensor(cap_shared,cap_right_in);

long cap_left_value = 0;
long cap_right_value = 0;

long cap_left_threshold = 75;
long cap_right_threshold = 75;

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
  //countLoop = countLoop + 1;
  
  cap_left_value = cap_left_sensor.capacitiveSensor(cap_samples);
  cap_right_value = cap_right_sensor.capacitiveSensor(cap_samples);
  /*Serial.println(cap_left_value);
  Serial.println(cap_right_value);*/

  if(digitalRead(ir_back) == HIGH) {
    digitalWrite(led_mirror, HIGH);
    cap_left_sensor.set_CS_AutocaL_Millis(0xFFFFFFFF); //autocal off
    cap_right_sensor.set_CS_AutocaL_Millis(0xFFFFFFFF); //autocal off
    if(cap_left_value > cap_left_threshold) { //paw on left sensor?
      digitalWrite(cap_left_out, LOW);
    } else {
      digitalWrite(cap_left_out, HIGH);
    }
    if(cap_right_value > cap_right_threshold) { //paw on right sensor?
      digitalWrite(cap_right_out, LOW);
    } else {
      digitalWrite(cap_right_out, HIGH);
    }
  } else {
     //Serial.println("BACK!");
     //first thin, make sure sensors are HIGH
     digitalWrite(cap_right_out, HIGH);
     digitalWrite(cap_left_out, HIGH);
     
     digitalWrite(led_mirror, LOW);
     
     cap_left_sensor.reset_CS_AutoCal();
     cap_right_sensor.reset_CS_AutoCal();
  }
/*
  if(countLoop > 10) {
     Serial.print(cap_left_value); //print sensor output 1
     Serial.print("\t");
     Serial.println(cap_right_value); //print sensor output 2
     countLoop = 0;
  }
*/
}
