#include <iostream>

#include "Light.h"
#include "Loop.h"
#include "cannon.h"
#include "screen.h"

using namespace std;


// objects and parameters
Light light(boundary_x, boundary_y, boundary_x / 2, GL_LIGHT0);
Cannon cannon;
Screen screen;

Loop_1 loop_1;
Loop_2 loop_2;
Loop_3 loop_3;
Loop& loop = loop_1;

int stage = -1;
int clk = 0;
int preprocess_time = 0;

// shooted shell
Shell unused_shell;
Shell shooted_shell = unused_shell;

// condition indicators
bool shoot_available = true;
bool event_updating = false;


// initial conditions
void initialize() {
	unused_shell.set_center({ 0,0,-2 * RADIUS });
	unused_shell.set_velocity({ 0,0,0 });

	cannon.initializie();
	screen.initialize();

	loop_1.create_loop();
	loop_2.create_loop();
	loop_3.create_loop();
}



// set stage
void set_circumstance(int stage_idx) {
	switch (stage_idx) {
	case 1:
		loop = loop_1;
		loop.reset();
		break;

	case 2:
		loop = loop_2;
		loop.reset();
		break;

	case 3:
		loop = loop_3;
		loop.reset();
		break;
	}
}

void set_stage(int i) {
	switch (stage) {
	case -1:    // start
		if (i == 1) {
			stage = 1;
			set_circumstance(1);
		}
		else if (i == -1) {
			// exit game
			exit(0);
		}
		break;

	case 0:    // game over
		if (i == 1) {
			stage = 1;
			set_circumstance(1);
		}
		else if (i == -1) {
			stage = -1;
		}
		break;

	/* 
	* n: stage n
		i == 1  : clear     -> stage = n0
		i == -1 : game over -> stage = 0
	* n0: stage n clear
		i == 1  : continue (go to next stage)    -> stage = n+1, set_circumstance
		i == -1 : return to start				 -> stage = -1
	*/
	case 1:
		shooted_shell = unused_shell;
		shoot_available = false;
		event_updating = false;
		preprocess_time = 0;
		if (i == 1) {
			stage = 10;
		}
		else if (i == -1) {
			stage = 0;
		}
		break;

	case 10:
		if (i == 1) {
			stage = 2;
			set_circumstance(2);
		}
		else if (i == -1) {
			stage = -1;
		}
		break;

	case 2:
		shooted_shell = unused_shell;
		shoot_available = false;
		event_updating = false;
		preprocess_time = 0;
		if (i == 1) {
			stage = 20;
		}
		else if (i == -1) {
			stage = 0;
		}
		break;

	case 20:
		if (i == 1) {
			stage = 3;
			set_circumstance(3);
		}
		else if (i == -1) {
			stage = -1;
		}
		break;

	case 3:
		shooted_shell = unused_shell;
		shoot_available = true;
		event_updating = false;
		preprocess_time = 0;
		if (i == 1) {
			stage = 30;
		}
		else if (i == -1) {
			stage = 0;
		}
		break;

	case 30:
		stage = -1;
		break;

	default:
		stage = -1;
		break;
	}
}



// game progress
bool preprocess() {
	if (preprocess_time < 0) {
		return false;
	}
	else if (preprocess_time < 360) { 
		preprocess_time++;
		return true;
	}
	else {
		preprocess_time = -1;
		shoot_available = true;
		return false;
	}
}


void update() {
	// cannon
	if (abs(shooted_shell.get_center()[0]) > boundary_x + RADIUS || abs(shooted_shell.get_center()[1]) > boundary_y + RADIUS) {
		shooted_shell = unused_shell;
		shoot_available = true;
	}
	cannon.idle_update();
	
	// loop
	if (preprocess()) {
		loop.idle_update();
	}
	else if (clk < update_period) {
		clk++;
	}
	else {
		if (event_updating) {
			event_updating = loop.event_update();
			// return to idle
			if (!event_updating) {    //// !event_updating
				vector<int>prev_info = loop.event_postporcessing();

				event_updating = loop.treat_collision(prev_info);    // chained deletion
				shoot_available = !event_updating;
			}
		}
		else {
			shooted_shell.move();
			loop.idle_update();
			event_updating = loop.treat_collision(shooted_shell);
			if (event_updating) {
				shooted_shell = unused_shell;    // chasing shooted shell finished
			}
		}
		clk = 0;
	}
}



// treat input from outer implement
/* menu */
void keyboard_up_menu(unsigned char key, int x, int y) {
	if (key == 'q') {
		set_stage(-1);
	}
}

void mouse_menu(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		set_stage(1);
	}
}

/* in-game */
void special_key_down_ingame(int key, int x, int y) {
	cannon.keyboard_down_update(key, x, y);
}

void mouse_ingame(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (shoot_available && (preprocess_time==-1)) {
			shooted_shell = cannon.mouse_update();
			shoot_available = false;
		}
	}
}

/* integrated */
void keyboard_up(unsigned char key, int x, int y) {
	if ((0 < stage) && (stage < 10)) { return; }
	else { keyboard_up_menu(key, x, y); }
}

void special_key_down(int key, int x, int y) {
	if ((0 < stage) && (stage < 10)) { special_key_down_ingame(key, x, y); }
	else { return; }
}

void mouse(int button, int state, int x, int y) {
	if ((0 < stage) && (stage < 10)) { mouse_ingame(button, state, x, y); }
	else { mouse_menu(button, state, x, y); }
}



// idle
void idle() {
	// start screen
	if (stage == -1) {
	}
	// game over
	else if (stage == 0) {
	}
	// in-game
	else if ((0 < stage) && (stage < 10)) {
		try {
			update();
		}
		catch (int i) {
			if ((i == -1) || (i == 1)) {
				set_stage(i);
			}
		}
	}
	// clear
	else {
	}

	glutPostRedisplay();
}



// display
void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-boundary_x, boundary_x, -boundary_y, boundary_y, -100.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// start screen
	if (stage == -1) {
		screen.start_display();
	}
	// game over
	else if (stage == 0) {
		screen.gameover_display();
	}
	// in-game
	else if ((0 < stage) && (stage < 10)) {
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);


		light.draw();
		loop.draw();
		cannon.draw();

		shooted_shell.draw();    // may needed only when event_updating = false

		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
	}
	// clear
	else {
		screen.gameclear_display(stage);
	}

	glutSwapBuffers();
}


int main(int argc, char** argv) {
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(WINDOW_X, WINDOW_Y);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("test");
	initialize();

	// register callback
	glutDisplayFunc(display);
	glutKeyboardUpFunc(keyboard_up);
	glutSpecialFunc(special_key_down);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);

	// enter GLUT event processing cycle
	glutMainLoop();


	return 0;
}