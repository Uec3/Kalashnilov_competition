#include <Arduino.h>
#include "first_lib.h"
const bool debug = 0;
US::US(int echo, int trig){
	this->echo_pin = echo;
	this->trig_pin = trig;
	pinMode(trig_pin, OUTPUT);
  	pinMode(echo_pin, INPUT);
  	if(debug){
  		Serial.begin(9600);
  	}
}
int US::distance(){
	f_duration = 0;
	for(int i = 0; i < 10; i++){
	  	digitalWrite(trig_pin, LOW);
	  	delayMicroseconds(2);
	    digitalWrite(trig_pin, HIGH);
	    delayMicroseconds(10);
	    digitalWrite(trig_pin, LOW);
		duration = pulseIn(echo_pin, HIGH);
		if(debug){
			delay(100);
			Serial.print(duration* 0.034 / 2 );
			Serial.print("_________");
			Serial.print(l_duration* 0.034 / 2);
			Serial.println("");
		}
		if(abs((l_duration - duration) * 0.034 / 2) < 50 ){
			f_duration += duration;
		}
		else{
			f_duration+=l_duration;
		}
		l_duration = duration;
	}
	return f_duration * 0.034 / 20;
}
