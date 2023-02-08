#include <first_lib.h>

Light_sensor light_sensor(A0, A1, A2, A3);

void setup() {
  Serial.begin(9600);
  // Serial.print(light_sensor.check());
}
int counter =0;
void loop() {
  for(int i = 0; i < 4; i++){
    Serial.print(light_sensor.Get_data()[i]);
    Serial.print('\t');
  }
  Serial.println(counter) ;
  counter++; 
}
