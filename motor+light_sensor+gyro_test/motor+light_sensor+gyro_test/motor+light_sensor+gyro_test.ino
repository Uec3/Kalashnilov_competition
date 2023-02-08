#include <first_lib.h>
MPU6050 mpu;
Motor motor_r(13,12,10,255);
Motor motor_l(6,7,5,255);
PID m_pid(5,0.01,100,60);
Light_sensor light_sensor(A0, A1, A2, A3);
Task task(motor_r, motor_l, mpu, m_pid, light_sensor);
void setup() {
  Wire.begin();
  mpu.initialize();
  mpu.dmpInitialize();
  mpu.setDMPEnabled(true);
  attachInterrupt(1, dmpReady, RISING);
  Serial.begin(9600);
}
int counter = 0;
void loop() {
  Get_angle(mpu);
  // for(int i = 0; i < 4; i++){
  //   Serial.print(light_sensor.Get_data()[i]);
  //   Serial.print('\t');
  // }
  // Serial.println(counter) ;
  // counter++; 
  // counter = counter /100;
  // Serial.print(motor_l.Condition());
  // Serial.print('\t');
  // Serial.print(motor_r.Condition());
  // Serial.print('\n');
  task.mta(0);
  if(!light_sensor.Get_data()[0] && !light_sensor.Get_data()[1] && !light_sensor.Get_data()[2] && !light_sensor.Get_data()[3]){
    Serial.println("Work");
  }
  // task.sl();
  // put your main code here, to run repeatedly:

}
