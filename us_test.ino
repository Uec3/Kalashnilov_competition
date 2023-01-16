#include <first_lib.h>


US us(10,9);
void setup() {
  Serial.begin(9600);
}
void loop() {
  Serial.println(us.distance());
}