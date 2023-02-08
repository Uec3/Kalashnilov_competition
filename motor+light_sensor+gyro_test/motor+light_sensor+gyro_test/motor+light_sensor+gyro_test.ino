#include <first_lib.h>
MPU6050 mpu;
Motor motor_r(13,12,11,255);
Motor motor_l(6,7,5,255);
PID m_pid(10,0.01,100,60);
Light_sensor light_sensor(A0, A1, A2, A3);
US right_us(10);
US center_us(10);
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
int counter = 0;
int t_angle = 0;
void loop() {
  if(!light_sensor.Get_data()[0] && !light_sensor.Get_data()[1] && !light_sensor.Get_data()[2] && !light_sensor.Get_data()[3]){
    Serial.print("NO_LINE-------------");
  }
  int a = 1000 * light_sensor.Get_data()[0] + 100 * light_sensor.Get_data()[1] + 10 * light_sensor.Get_data()[2] + light_sensor.Get_data()[3];  
  Serial.print(a);
  Serial.print('\t');
  Serial.print(task.gta());
  Serial.print('\t');
  Serial.print(motor_l.Condition());
  Serial.print('\t');
  Serial.println(motor_r.Condition());
  Get_angle(mpu);
  task.mta(task.gta());
}
