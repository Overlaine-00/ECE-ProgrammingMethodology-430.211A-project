#include "Cannon.h"


void Cannon::initializie() {
	turret.initialize_texture();
}

Cannon::Cannon() {
	reset();
}

void Cannon::reset() {
	angle = 0;
	armed.push_back(Shell(shell_pos[1]));
	armed.push_back(Shell(shell_pos[0]));
}

void Cannon::angle_setting() {
	if (angle > 180)
		angle -= 360;
	if (angle <= -180)
		angle += 360;
}

void Cannon::set_angle(float a) {
	angle = a;
}


void Cannon::rotate(int key, int x, int y) {
	angle_setting();
	if (angle > 0 && angle < 90) {
		switch (key) {
		case GLUT_KEY_UP:
			angle -= cannon_rotate_velocity;
			break;
		case GLUT_KEY_DOWN:
			angle += cannon_rotate_velocity;
			break;
		case GLUT_KEY_RIGHT:
			angle += cannon_rotate_velocity;
			break;
		case GLUT_KEY_LEFT:
			angle -= cannon_rotate_velocity;
			break;
		}
	}
	else if (angle == 90) {
		switch (key) {
		case GLUT_KEY_UP:
			angle -= cannon_rotate_velocity;
			break;
		case GLUT_KEY_DOWN:
			angle += cannon_rotate_velocity;
			break;
		}
	}
	else if (angle > 90 && angle < 180) {
		switch (key) {
		case GLUT_KEY_UP:
			angle -= cannon_rotate_velocity;
			break;
		case GLUT_KEY_DOWN:
			angle += cannon_rotate_velocity;
			break;
		case GLUT_KEY_RIGHT:
			angle -= cannon_rotate_velocity;
			break;
		case GLUT_KEY_LEFT:
			angle += cannon_rotate_velocity;
			break;
		}
	}
	else if (angle == 180) {
		switch (key) {
		case GLUT_KEY_RIGHT:
			angle -= cannon_rotate_velocity;
			break;
		case GLUT_KEY_LEFT:
			angle += cannon_rotate_velocity;
			break;
		}
	}
	else if (angle > -180 && angle < -90) {
		switch (key) {
		case GLUT_KEY_UP:
			angle += cannon_rotate_velocity;
			break;
		case GLUT_KEY_DOWN:
			angle -= cannon_rotate_velocity;
			break;
		case GLUT_KEY_RIGHT:
			angle -= cannon_rotate_velocity;
			break;
		case GLUT_KEY_LEFT:
			angle += cannon_rotate_velocity;
			break;
		}
	}
	else if (angle == -90) {
		switch (key) {
		case GLUT_KEY_UP:
			angle += cannon_rotate_velocity;
			break;
		case GLUT_KEY_DOWN:
			angle -= cannon_rotate_velocity;
			break;
		}
	}
	else if (angle > -90 && angle < 0) {
		switch (key) {
		case GLUT_KEY_UP:
			angle += cannon_rotate_velocity;
			break;
		case GLUT_KEY_DOWN:
			angle -= cannon_rotate_velocity;
			break;
		case GLUT_KEY_RIGHT:
			angle += cannon_rotate_velocity;
			break;
		case GLUT_KEY_LEFT:
			angle -= cannon_rotate_velocity;
			break;
		}
	}
	else if (angle == 0) {
		switch (key) {
		case GLUT_KEY_RIGHT:
			angle += cannon_rotate_velocity;
			break;
		case GLUT_KEY_LEFT:
			angle -= cannon_rotate_velocity;
			break;
		}
	}
}




void Cannon::move_forward() {
	if (armed[0].get_center()[1] < shell_pos[1][1] - 3) {
		armed[0].move();
	}
	else {
		armed[0].set_center(shell_pos[1]);
	}
}

void Cannon::load() {
	if (armed.size() == 2) { return; }

	armed.push_back(Shell(shell_pos[0]));
}

Shell Cannon::shoot() {
	/*
	Process : shoot -> load new shell & trigger move forward
	*/

	// shoot
	Shell shooted_shell = *(armed.begin());
	shooted_shell.set_center({ 2 * (float)RADIUS * sin(angle * (float)PI / 180), 2 * (float)RADIUS * cos(angle * (float)PI / 180), 0 });
	shooted_shell.set_velocity({ shooted_velocity * sin(angle * (float)PI / 180), shooted_velocity * cos(angle * (float)PI / 180), 0 });
	armed.erase(armed.begin());

	// load
	load();

	return shooted_shell;
}



void Cannon::idle_update() {
	/*
	* update move_forward()
	*/
	move_forward();
}

void Cannon::keyboard_down_update(int key, int x, int y) {
	/*
	This works always. No determination and returns.
	*/
	rotate(key, x, y);
}

Shell Cannon::mouse_update() {
	/*
	* This does not contain determination.
	  This function won't be activated when shooted shell moves,
	  which is checked at main.
	* This does not treat mouse click signal. Such functions are at main
	*/
	return shoot();
}

void Cannon::draw() const {
	glPushMatrix();
	glRotatef(-angle, 0.0, 0.0, 1.0);
	// turret
	turret.draw();

	// shells
	for (auto itr = armed.begin(); itr < armed.end(); ++itr) {
		itr->draw();
	}

	glPopMatrix();
}