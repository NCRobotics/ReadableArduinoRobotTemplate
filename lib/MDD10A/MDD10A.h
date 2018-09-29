#ifndef MDD10A_h
#define MDD10A_h

#include <Arduino.h>

class MDD10A{

public:

	MDD10A();

	void setMotorSpeed(int controller, int speed);
	void init();

	int dir = 0;


	//PinOuts.  Use only one template. Change to match your robot.
	//ARC Reactor V2
	const int _mc1m1_dir = 42;
	const int _mc1m1_pwm = 10;
	const int _mc1m2_dir = 43;
	const int _mc1m2_pwm = 11;
	const int _mc2m1_dir = 28;
	const int _mc2m1_pwm = 2;
	const int _mc2m2_dir = 26;
	const int _mc2m2_pwm = 3;
	const int _mc3m1_dir = 32;
	const int _mc3m1_pwm = 8;
	const int _mc3m2_dir = 30;
	const int _mc3m2_pwm = 9;
	const int _mc4m1_dir = 27;
	const int _mc4m1_pwm = 5;
	const int _mc4m2_dir = 29;
	const int _mc4m2_pwm = 6;

	//ARC Reactor V1
/*	const int _mc1m1_dir = 38;
	const int _mc1m1_pwm = 10;
	const int _mc1m2_dir = 40;
	const int _mc1m2_pwm = 11;
	const int _mc2m1_dir = 22;
	const int _mc2m1_pwm = 2;
	const int _mc2m2_dir = 24;
	const int _mc2m2_pwm = 3;
	const int _mc3m1_dir = 47;
	const int _mc3m1_pwm = 8;
	const int _mc3m2_dir = 49;
	const int _mc3m2_pwm = 9;
	const int _mc4m1_dir = 33;
	const int _mc4m1_pwm = 4;
	const int _mc4m2_dir = 31;
	const int _mc4m2_pwm = 6;
*/

	// C4TJ
/*	const int _mc1m1_dir = 22;
	const int _mc1m1_pwm = 2;
	const int _mc1m2_dir = 24;
	const int _mc1m2_pwm = 3;
	const int _mc2m1_dir = 23;
	const int _mc2m1_pwm = 4;
	const int _mc2m2_dir = 25;
	const int _mc2m2_pwm = 5;
	const int _mc3m1_dir = 26;
	const int _mc3m1_pwm = 6;
	const int _mc3m2_dir = 28;
	const int _mc3m2_pwm = 44;
	const int _mc4m1_dir = 27;
	const int _mc4m1_pwm = 8;
	const int _mc4m2_dir = 29;
	const int _mc4m2_pwm = 9;
	*/




};

#endif
