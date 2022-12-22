#pragma once
#include <cmath>

#include "Turret.h"
#include "Shell.h"

using namespace std;

class Cannon {
private:
	float angle;

	Turret turret;

	// at most 2 elements, at least 1 element
	// 0th shell : shooted at next time
	vector<Shell> armed;

	// relative position : when pos = [0,0,0]
	// 0th : load, 1st : fired at next click
	vector<vector<float>> shell_pos = { {0,0,0}, {0,2 * RADIUS,0} };

	// remains angle in range (-180,180]
	void angle_setting();
	void set_angle(float a);

	void rotate(int key, int x, int y);

	// update center position when armed shell moves forward (after shoot)
	void move_forward();

	// load new shell
	void load();

	// shoot
	Shell shoot();
public:
	Cannon();
	void reset();
	void initializie();

	void idle_update();
	void keyboard_down_update(int key, int x, int y);    // special key
	Shell mouse_update();
	void draw() const;
};