#include <first_lib.h>
MPU6050 mpu;
Motor motor_l(13,12,10,255);
Motor motor_r(6,7,5,255);
PID m_pid(10,0.01,100,60);
Light_sensor light_sensor(A0, A1, A2, A3);
US right_us(9);
US center_us(8);
US left_us(10);
Task task(motor_r, motor_l, mpu, m_pid, light_sensor, left_us, center_us,right_us);
void setup() {
  Wire.begin();
  mpu.initialize();
  mpu.dmpInitialize();
  mpu.setDMPEnabled(true);
  attachInterrupt(1, dmpReady, RISING);
  Serial.begin(115200);
}
void loop() {
  Get_angle(mpu);
  task.rta(0);
  Serial.println(Get_angle(mpu));
}