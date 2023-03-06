#include <Arduino.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"


void dmpReady();

//------------------------------------------------------------------------------------------------------------------------------------------------------------

class US
{
public:
	US();
	US(int pin);
	US(int echo, int trig);
	int distance();
private:
	long duration;
	int l_duration;
	long f_duration;
	int echo_pin;
	int trig_pin;
};

//------------------------------------------------------------------------------------------------------------------------------------------------------------

class Motor
{
public:
	Motor();
	Motor(int right_pin, int left_pin, int speed_pin, int spd = 0);
	// Motor(int pin1, int pin2, int pin3);
	void start_rotation();
	void Set_speed(int spd);
	void Stop();
	int Condition();
	int Dir;
private:
	int speed;
	int r_pin;
	int l_pin;
	int s_pin;
};
int Get_angle(MPU6050 &mpu);

//------------------------------------------------------------------------------------------------------------------------------------------------------------

class PID{
private:
	double Pk,Ik,Dk, o_error = 0, Mi;
public:
	PID();
	PID(double p, double i, double d, double mi);
	double ID(double error);
};

//------------------------------------------------------------------------------------------------------------------------------------------------------------

class Light_sensor
{
public:
	Light_sensor();
	Light_sensor(uint8_t rf_pin, uint8_t rb_pin, uint8_t lfs_pin, uint8_t lb_pin);
	int* Get_data();
	~Light_sensor();	
	void init();
private:
	uint8_t rfs_pin, rbs_pin, lfs_pin, lbs_pin; 	
	int rf_sensor = 0, rb_sensor = 0, lf_sensor = 0, lb_sensor = 0;
	int* arr;
	bool counter = false;

};

//------------------------------------------------------------------------------------------------------------------------------------------------------------

class Task
{
public:
	Task(Motor &rm, Motor &lm, MPU6050 &m, PID &mr, Light_sensor &ls, US &l_us, US &c_us, US &r_us);
	// ~Task();
	void rta(int i_angle);
	void mta(int t_angle);
	int check(int i_angle);
	void sl();
	void uta(int a);
	int gta();
	void i_uta(int a);
	// int* usd();
private:
	// int* usd_arr;
	int i_angle, t_angle = 0;
	Motor r_motor, l_motor;
	MPU6050 mpu;
	PID motor_rotation;
	Light_sensor light_sensor;
	US l_US,r_US, c_US; 
};

//------------------------------------------------------------------------------------------------------------------------------------------------------------
