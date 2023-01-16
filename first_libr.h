#include <Arduino.h>
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
