#include <Arduino.h>
#include "first_lib.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "MPU6050_6Axis_MotionApps20.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------

uint8_t fifoBuffer[45];
volatile bool mpuFlag = false;
const int min_spd = 10;
void dmpReady(){
	mpuFlag = true;
}
int Get_angle(MPU6050 &mpu){
  if(mpu.dmpGetCurrentFIFOPacket(fifoBuffer) && mpuFlag or 1){
      Quaternion q;
      VectorFloat gravity;
      float ypr[3];
      mpu.dmpGetQuaternion(&q, fifoBuffer);
      mpu.dmpGetGravity(&gravity, &q);
      mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
   	  return degrees(ypr[0]);
  }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------

US::US(){
	this->echo_pin = NULL;	
}
US::US(int pin){
	this->echo_pin = pin;
	this->trig_pin = pin;
}

US::US(int echo, int trig){
	this->echo_pin = echo;
	this->trig_pin = trig;
	pinMode(trig_pin, OUTPUT);
  	pinMode(echo_pin, INPUT);
}
int US::distance(){
	f_duration = 0;
	for(int i = 0; i < 10; i++){
	  	if(echo_pin != trig_pin){
		  	digitalWrite(trig_pin, LOW);
		  	delayMicroseconds(2);
		    digitalWrite(trig_pin, HIGH);
		    delayMicroseconds(10);
		    digitalWrite(trig_pin, LOW);
			duration = pulseIn(echo_pin, HIGH);
		}
		else{
			pinMode(echo_pin, OUTPUT);
			digitalWrite(echo_pin, LOW);
			delayMicroseconds(2);
			digitalWrite(echo_pin, HIGH);
			delayMicroseconds(10);
			digitalWrite(echo_pin, LOW);
			pinMode(echo_pin, INPUT);
			duration = pulseIn(echo_pin, HIGH);
		}
		if(abs((l_duration - duration) * 0.034 / 2) < 50){
			f_duration += duration;
		}
		else{
			f_duration += l_duration;
		}
		l_duration = duration;
	}
	return f_duration * 0.034/20 ;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------

Motor::Motor(){
	r_pin = 14;
	l_pin = 14;
	s_pin = 14;
	speed = 0;	
}
Motor::Motor(int right_pin, int left_pin, int speed_pin, int spd = 0){
	r_pin = right_pin;
	l_pin = left_pin;
	s_pin = speed_pin;
	speed = spd;
	Dir = -1000;
	pinMode(r_pin,OUTPUT);
	pinMode(l_pin,OUTPUT);
	pinMode(s_pin,OUTPUT);
}
void Motor::start_rotation(){
	if(abs(speed) < min_spd){
		Stop();
	}
	else if(speed > min_spd){
		digitalWrite(r_pin,1);
		digitalWrite(l_pin,0);
		analogWrite(s_pin,speed);
	}
	else if (speed < min_spd){
		digitalWrite(r_pin,0);
		digitalWrite(l_pin,1);
		analogWrite(s_pin, -speed);
		
	}
}
void Motor::Stop(){
	// if(speed > 0){
	// 	digitalWrite(r_pin,1);
	// 	digitalWrite(l_pin,0);
	// 	analogWrite(s_pin,255);
	// 	delay(map(abs(speed), 0,255,0,70));
	// 	speed = 0;
	// }
	// else if(speed <){
	// 	speed = 0;
	// 	digitalWrite(r_pin,0);
	// 	digitalWrite(l_pin,1);
	// 	analogWrite(s_pin,255);
	// 	delay(map(abs(speed), 0,255,0,70));
	// }
	Dir = 0;
	digitalWrite(l_pin,0);
	digitalWrite(r_pin,0);
}
int Motor::Condition(){
	return Dir;
	// return 15;
}
void Motor::Set_speed(int spd){
	if(spd >= 255){
		speed = 255;
	}
	else if (spd <= -255){
		speed = -255;
	}
	else{
		speed = spd;
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------

PID::PID(){
	Pk = 0;
	Ik = 0;
	Dk = 0;
	Mi = 0;

}
PID::PID(double p, double i, double d, double mi){
	Pk = p;
	Ik = i;
	Dk = d;
	Mi = mi;
}
double PID::ID(double error){
	int i_error = error + o_error;
	if(i_error > Mi ){
		i_error = Mi;
	}
	else if(i_error < -Mi){
		i_error = Mi;
	}
	int d_error = error - o_error;
	o_error = error;
	return error*Pk;
	return error*Pk + i_error*Ik + d_error*Dk;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------
Light_sensor::Light_sensor(){
	rfs_pin = 10;
	rbs_pin = 10;
	lfs_pin = 10;
	lbs_pin = 10;
}
Light_sensor::Light_sensor(uint8_t lf_pin, uint8_t rf_pin, uint8_t rb_pin, uint8_t lb_pin){
	rfs_pin = rf_pin;
	rbs_pin = rb_pin;
	lfs_pin = lf_pin;
	lbs_pin = lb_pin;
	pinMode(lfs_pin, INPUT);
	pinMode(rfs_pin, INPUT);
	pinMode(lbs_pin, INPUT);
	pinMode(rbs_pin, INPUT);
}
void Light_sensor::init(){
	lf_sensor = analogRead(lfs_pin);
	rf_sensor = analogRead(rfs_pin); 
	rb_sensor = analogRead(rbs_pin);
	lb_sensor = analogRead(lbs_pin);
}
int* Light_sensor::Get_data(){
	arr = new int[4];
	if(!counter){
		init();
		counter = true;
	}
	for(int i = 0; i < 4; i++) arr[i] = 0;
	if(analogRead(lfs_pin) - lf_sensor > 20){
		for(int i = 0; i <= 10; i++){
			if(abs(analogRead(lfs_pin) - lf_sensor) < 20){
				arr[0] = 0;
				break;
			}
			else{
				arr[0] = 1;
			}
		}
	}
	if(analogRead(rfs_pin) - rf_sensor > 40){
		for(int i = 0; i <= 10; i++){
			if(abs(analogRead(rfs_pin) - rf_sensor) < 20){
				arr[1] = 0;
				break;
			}
			else{
				arr[1] = 1;
			}
		}
	}
	if(analogRead(rbs_pin) - rb_sensor > 20){
		for(int i = 0; i <= 10; i++){
			if(abs(analogRead(rbs_pin) - rb_sensor) < 20){
				arr[2] = 0;
				break;
			}
			else{
				arr[2] = 1;
			}
		}
	}
	if(analogRead(lbs_pin) - lb_sensor > 20){
		for(int i = 0; i <= 10; i++){
			if(abs(analogRead((lbs_pin) - lb_sensor < 20))){
				arr[3] = 0;
				break;
			}
			else{
				arr[3] = 1;
			}
		}
	}
	return arr;
}
Light_sensor::~Light_sensor(){
	delete[] arr;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------

Task::Task(Motor &rm, Motor &lm, MPU6050 &m, PID &mr, Light_sensor &ls, US &l_us, US &c_us, US &r_us){
	r_motor = rm;
	l_motor = lm;
	mpu = m;
	motor_rotation = mr;
	light_sensor = ls;
	l_US = l_us;
	c_US = c_us;
	r_US = r_us;
}
int Task::check(int t_angle){
	return (Get_angle(mpu));	
}
void Task::rta(int t_angle){
	if(!light_sensor.Get_data()[0] && !light_sensor.Get_data()[1] && !light_sensor.Get_data()[2] && !light_sensor.Get_data()[3]){
		i_angle = Get_angle(mpu);
		r_motor.Set_speed(-motor_rotation.ID((i_angle + 540 - t_angle) % 360 - 180));
		l_motor.Set_speed(motor_rotation.ID((i_angle + 540 - t_angle) % 360 - 180));
		r_motor.start_rotation();
		l_motor.start_rotation();
	}
	else{
		sl();
	}
}
void Task::i_uta(int a){
	t_angle = (gta() + 540 - a) % 360 - 180;
}
void Task::uta(int a){
	if(abs(Get_angle(mpu) - t_angle) < 10){
		t_angle = (gta() + 540 - a) % 360 - 180;
	}
}
int Task::gta(){
	return t_angle;
}
void Task::sl(){
	int* data = light_sensor.Get_data();
	if(data[0] || data[1]){
		r_motor.Set_speed(255);
		l_motor.Set_speed(255);
		r_motor.start_rotation();
		l_motor.start_rotation();		
		delay(100);
		// uta(-90);.
		// return 1;
	}
	else if(data[2] || data[3]){
		r_motor.Set_speed(-255);
		l_motor.Set_speed(-255);
		r_motor.start_rotation();
		l_motor.start_rotation();		
		delay(100);
		// uta(90);
		// return 2;
	}
	// else if(data[1]){
	// 	l_motor.Stop();
	// 	r_motor.Set_speed(-255);
	// 	r_motor.start_rotation();
	// 	delay(20);
	// }
	// else if(data[0]){
	// 	r_motor.Stop();
	// 	l_motor.Set_speed(-255);
	// 	l_motor.start_rotation();
	// 	delay(20);
	// }

	// else if(data[2]){
	// 	l_motor.Stop();
	// 	r_motor.Set_speed(255);
	// 	r_motor.start_rotation();
	// 	delay(20);
	// }
	// else if(data[3]){
	// 	r_motor.Stop();
	// 	l_motor.Set_speed(255);
	// 	l_motor.start_rotation();
	// 	delay(20);
	// }
	delete data;
}
void Task::mta(int t_angle){
	if(!light_sensor.Get_data()[0] && !light_sensor.Get_data()[1] && !light_sensor.Get_data()[2] && !light_sensor.Get_data()[3]){
		i_angle = Get_angle(mpu);
		l_motor.Set_speed(200 + motor_rotation.ID((i_angle + 540 - t_angle) % 360 - 180));
		r_motor.Set_speed(200 - motor_rotation.ID((i_angle + 540 - t_angle) % 360 - 180));
		r_motor.start_rotation();
		l_motor.start_rotation();		
	}
	else{
		sl();
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------
