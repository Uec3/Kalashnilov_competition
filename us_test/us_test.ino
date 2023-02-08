#include <first_lib.h>
Motor motor_l(13,12,10,255);
Motor motor_r(6,7,5,255);
void setup() {
  // pinMode(8,OUTPUT);
  // pinMode(7,OUTPUT);
  // pinMode(6,OUTPUT);
  Serial.begin(9600);
}
void loop() {
  // Serial.println(" "); 
  // digitalWrite(8,0);
  // digitalWrite(7,1);
  // analogWrite(6,255);
  // Serial.println(Parce_string(Speed));
  // motor_r.start_rotation();
  // motor_l.start_rotation();
  // delay(2000);
  // motor.Stop();
  // delay(250);
  // motor.Forwad_rotation();
  // delay(2000);
  // motor.Stop();
  // delay(2000);
  int* signal = motor_l.Condition();
  Serial.print(signal[0]);
  Serial.print('\t');
  Serial.println(signal[1]);
}