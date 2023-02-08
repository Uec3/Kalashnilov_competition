#include <Servo.h>

Servo servo;

void setup() {
  pinMode(13,OUTPUT);
  servo.attach(9);
  Serial.begin(9600);
  // put your setup code here, to run once:

}
int pos = 0;
void loop() {
for (pos = 50; pos <= 130; pos += 1) { // от 0 до 180 градусов
    // шаг в один градус
    servo.write(pos);              // просим повернуться на позицию значения переменной 'pos'
    delay(15);                       // ждём 15ms для достижения позиции
  }
  for (pos = 130; pos >= 50; pos -= 1) { // от 180 до 0 градусов
    servo.write(pos);              // просим повернуться на позицию значения переменной 'pos'
    delay(15);                       // ждём 15ms для достижения позиции
  }
}
  // for(int i = 600; i < 1200; i++){
  //   servo.write(i/10);
  // }
