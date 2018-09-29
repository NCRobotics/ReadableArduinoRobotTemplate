#include "MDD10A.h"

MDD10A::MDD10A(){

}

void MDD10A::init(){
	pinMode(_mc1m1_dir, OUTPUT);
	pinMode(_mc1m2_dir, OUTPUT);
	pinMode(_mc2m1_dir, OUTPUT);
	pinMode(_mc2m2_dir, OUTPUT);
	pinMode(_mc3m1_dir, OUTPUT);
	pinMode(_mc3m2_dir, OUTPUT);
	pinMode(_mc4m1_dir, OUTPUT);
	pinMode(_mc4m2_dir, OUTPUT);
}

void MDD10A::setMotorSpeed(int controller, int speed){
	if(speed < 0){
		dir = 1;
		speed *= -1;
	}else{
		dir = 0;
	}

	switch(controller){
		case 0:
			digitalWrite(_mc1m1_dir, dir);
			analogWrite(_mc1m1_pwm, speed);
		break;

		case 1:
			digitalWrite(_mc1m2_dir, dir);
			analogWrite(_mc1m2_pwm, speed);
		break;

		case 2:
			digitalWrite(_mc2m1_dir, dir);
			analogWrite(_mc2m1_pwm, speed);
		break;

		case 3:
			digitalWrite(_mc2m2_dir, dir);
			analogWrite(_mc2m2_pwm, speed);
		break;

		case 4:
			digitalWrite(_mc3m1_dir, dir);
			analogWrite(_mc3m1_pwm, speed);
		break;

		case 5:
			digitalWrite(_mc3m2_dir, dir);
			analogWrite(_mc3m2_pwm, speed);
		break;

		case 6:
			digitalWrite(_mc4m1_dir, dir);
			analogWrite(_mc4m1_pwm, speed);
		break;

		case 7:
			digitalWrite(_mc4m2_dir, dir);
			analogWrite(_mc4m2_pwm, speed);
		break;

	}
}
