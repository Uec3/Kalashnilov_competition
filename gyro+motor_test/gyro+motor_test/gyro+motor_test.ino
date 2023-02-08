#include <first_lib.h>
MPU6050 mpu;
Motor motor_l(13,12,10,255);
Motor motor_r(6,7,5,255);
PID m_pid(10,0.01,100,60);
Light_sensor light_sensor(A0, A1, A2, A3);
Task task(motor_r, motor_l, mpu, m_pid, light_sensor);void setup() {
  Wire.begin();
  mpu.initialize();
  mpu.dmpInitialize();
  mpu.setDMPEnabled(true);
  attachInterrupt(1, dmpReady, RISING);
  Serial.begin(115200);
}
void loop() {
  Get_angle(mpu);
  task.mta(90);
  Serial.println(Get_angle(mpu));
}