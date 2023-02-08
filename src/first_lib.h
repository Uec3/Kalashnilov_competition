#include <Arduino.h>
const bool debug = 0;
class US
{
public:
	US(int echo, int trig);
	int distance();
private:
	long duration;
	int l_duration;
	long f_duration;
	int echo_pin;
	int trig_pin;
};
class Motor
{
public:
	Motor(int pin1, int pin2, int pin3, int spd);
	Motor(int pin1, int pin2, int pin3);
	void Forwad_rotation();
	void Backward_rotation();
	void Set_speed(int spd);
private:
	int speed;
	int r_pin;
	int l_pin;
	int s_pin;
};
