#pragma once

#define PI 3.141592

/////////////////////////////////////////////////
// main parameters
/////////////////////////////////////////////////

#define WINDOW_X 200
#define WINDOW_Y 200

#define window_width 1000
#define window_height 1000

#define boundary_x window_width/2
#define boundary_y window_height/2

// update period
#define update_period 3
#define preprocess_timelimit 360



/////////////////////////////////////////////////
// intermediate screen 
/////////////////////////////////////////////////
#define screen_on 1





/////////////////////////////////////////////////
// turret parameters
/////////////////////////////////////////////////
#define Turret_center_x 0
#define Turret_center_y 0



/////////////////////////////////////////////////
// cannon parameters
/////////////////////////////////////////////////
/*
Rotation (angular) velocity of cannon : cannon_rotate_velocity

Velocity of shooted shell : shooted_velocity
*/
#define cannon_rotate_velocity 8
#define shooted_velocity 12


/////////////////////////////////////////////////
// shell parameters
/////////////////////////////////////////////////
/*
Mutual radius of shell : RADIUS
*/

// radius
#define RADIUS 30.0




/////////////////////////////////////////////////
// loop parameters
/////////////////////////////////////////////////

/*
velocity of shells in the loop in
	idle update (no collision) : Idle_Loop_velocity
	event update (collision) : Event_Loop_velocity
*/

// HIGHLY RECOMMENDED : strictly less than RADIUS
#define Idle_Loop_velocity 1
#define Event_Loop_velocity 4


// Round 1
/*
number of shells appeared : total_num1

circular path with
	center : (loop_center_x, looop_center_y, 0)
	radius : loop_radius
*/

#define Total_num1 20

#define Loop_center_x Turret_center_x
#define Loop_center_y Turret_center_y
#define Loop_radius 300




// Round 2
/*
number of shells appeared : total_num2

line path with
slope : WINDOW_Y/(X2_top - X2_bottom)
*/

#define Total_num2 30

#define X2_top -400.0f
#define X2_bottom -200.0f




// Round 3
/*
number of shells appeared : total_num2

rectangular path with
	width : X1 + boundary_x
	height : Y1_high - Y1_low
*/

#define Total_num3 40

#define X3 300
#define Y3_low -250
#define Y3_high 250