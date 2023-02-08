
#include <first_lib.h>
MPU6050 mpu;
float a_angle;
bool counter = 0;
int rfs = 0, rbs, lfs = 0, lbs = 0;

void setup() {
  Wire.begin();
  mpu.initialize();
  mpu.dmpInitialize();
  mpu.setDMPEnabled(true);
  attachInterrupt(1, dmpReady, RISING);
  Serial.begin(115200);
}
int rf_sensor = 0, rb_sensor = 0, lf_sensor = 0, lb_sensor = 0;
void loop() {
}