#include <iostream>
#include <cmath>

#include "Loop.h"

using namespace std;

Loop::Loop() {
	reset();
}

void Loop::reset() {
	score = 0;
	shells.clear();
	maked_shells = 0;
	event_update_idx_info.clear();
}


Shell Loop::create_shell() {
	Shell shell = Shell();
	shell.set_center(loop_points[0]);    // equivalent to loop_points[shell.get_index()]
	return shell;
}


// idle functions

void Loop::move() {
	for (auto shell_itr = shells.begin(); shell_itr < shells.end(); ++shell_itr) {
		shell_itr->move_by_index(velocity, loop_points);
	}
}

void Loop::add_shell() {
	// create new shell at initial position (index 0)
	if (maked_shells >= total_shells) return;

	if (shells.size() == 0) {
		shells.push_back(create_shell());
		maked_shells++;
	}
	else {
		if ((shells.end() - 1)->get_index() >= 2 * RADIUS) {
			shells.push_back(create_shell());
			maked_shells++;
		}
	}
}

void Loop::round_finish_check() {
	// win
	if ((maked_shells == total_shells) && (shells.size() == 0)) {
		throw 1;
	}

	// lose : also implied 
	else if ((shells.size() > 0) && (shells[0].get_index() >= loop_points.size() - velocity)) {
		throw -1;
	}
}




// event functions
/* initial collision */

float Loop::distance(vector<float> a, vector<float> b) const {
	float result = 0;
	for (int i = 0; i < 3; i++) {
		result += pow(a[i] - b[i], 2);
	}
	return sqrt(result);
}

bool Loop::collide_with_before(Shell& shell, int i) const {
	/*
	shell : collided shooted shell
	i : index (of loop, not shells)
	*/
	auto center = shell.get_center();
	auto point = loop_points[i];
	auto tangent_vec = tangent_vector(i);

	float inner_product = (tangent_vec[0] * (center[0] - point[0]) +
						   tangent_vec[1] * (center[1] - point[1]) +
						   tangent_vec[2] * (center[2] - point[2]));

	return inner_product >= 0;
}


int Loop::detect_collision(Shell& shell) const {
	for (auto shell_itr = shells.begin(); shell_itr < shells.end(); ++shell_itr) {
		if (shell_itr->get_index() <= 2 * RADIUS) { continue; }
		else if (distance(shell.get_center(), shell_itr->get_center()) <= shell.get_radius() + shell_itr->get_radius())
			return (int)(shell_itr - shells.begin());
	}

	return -1;    // when no collision
}

vector<int> Loop::candidates_tobe_removed(Shell& shell, int collide_at) {
	int collide_at_2 = collide_at + pow(-1, collide_with_before(shell, shells[collide_at].get_index()));
	int min_idx = min(collide_at, collide_at_2);    // >= -1
	int max_idx = max(collide_at, collide_at_2);    // <= shells.size()
	int inserted_idx = max_idx;

	int standard_type = shell.get_type();
	while (min_idx > -1) {
		if (shells[min_idx].get_type() != standard_type) break;
		min_idx--;
	}
	while (max_idx < (int)(shells.size())) {
		if (shells[max_idx].get_type() != standard_type) break;
		max_idx++;
	}

	// if insert : append at inserted_idx
	// if deleted : min_idx ~ (max_idx-1) will be deleted
	vector<int> result = { min_idx+1, max_idx, inserted_idx };
	return result;
}

vector<int> Loop::adjust_shells(vector<int> range, Shell& shell) {
	vector<int> result = { 0,0 };
	if ((range[1] - range[0]) < 2) {    // insert. mode 0 (at result[0])
		if (range[2] == shells.size()) { shell.set_index((shells.end() - 1)->get_index() - 2 * RADIUS); }
		else { shell.set_index(shells[range[2]].get_index() + 2 * RADIUS); }
		shells.insert(shells.begin() + range[2], shell);
		result[0] = 0, result[1] = range[2];   // result[1] = index of newly append shell
		return result;
	}
	else {    // delete. mode 1 (at result[0])
		shells.erase(shells.begin() + range[0], shells.begin() + range[1]);
		result[0] = 1, result[1] = range[0];    // result[1] = index of ball after removed.  00(0)00 -> 2
		score += range[1] - range[0] + 1;
		return result;
	}
}

bool Loop::treat_collision(Shell& shell) {
	int collide_at = detect_collision(shell); if (collide_at == -1) { return false; }    // no collision -> no need to event update
	vector<int> tobe_removed = candidates_tobe_removed(shell, collide_at);
	vector<int> adjust_info = adjust_shells(tobe_removed, shell);

	if (adjust_info[0] == 0) {    // insert
		vector<float> target_pos = loop_points[shells[adjust_info[1]].get_index()];
		auto present_pos = shell.get_center();
		vector<float> v = { (target_pos[0] - present_pos[0]) * Event_Loop_velocity / (float)(2 * RADIUS),
							(target_pos[1] - present_pos[1]) * Event_Loop_velocity / (float)(2 * RADIUS),
							(target_pos[2] - present_pos[2]) * Event_Loop_velocity / (float)(2 * RADIUS) };
		shells[adjust_info[1]].set_velocity(v);
	}
	else if (adjust_info[0] == 1) {    // delete
		if (adjust_info[1] == 0) { return true; }    // first shell removed -> no need to event update
		else if ((maked_shells == total_shells) && (adjust_info[1] == shells.size())) { return true; }    // last shell removed -> no need to event update
	}

	event_update_idx_info.push_back(adjust_info);
	return true;
}


/* chained collision */
vector<int> Loop::candidates_tobe_removed(int next_part_i) {
	/*
	* next_part_i : first index of second part after divided.
	  this input comes from
		index 1 value of return of function adjust_shells() (it must be of the form {1,i}), or
		that of event_update_idx_info[0]
	*/
	// not necessary
	if (next_part_i == 0 || next_part_i == shells.size()) { return { 0,0 }; }

	int standard_type = shells[next_part_i].get_type();
	int min_idx = next_part_i - 1;
	int max_idx = next_part_i;
	while (min_idx > -1) {
		if (shells[min_idx].get_type() != standard_type) break;
		min_idx--;
	}
	while (max_idx < (int)(shells.size())) {
		if (shells[max_idx].get_type() != standard_type) break;
		max_idx++;
	}

	// if insert : append at inserted_idx
	// if deleted : min_idx ~ (max_idx-1) will be deleted
	vector<int> result = { min_idx + 1, max_idx};
	return result;
}

vector<int> Loop::adjust_shells(vector<int> range) {
	vector<int> result = { 0,0 };
	if ((range[1] - range[0]) < 3) {    // no delete. mode 0
		result[0] = 0, result[1] = 0;
		return result;
	}
	else {    // delete. mode 1 (at result[0])
		shells.erase(shells.begin() + range[0], shells.begin() + range[1]);
		result[0] = 1, result[1] = range[0];    // result[1] = index of ball after removed.  00(0)00 -> 2
		score += range[1] - range[0];
		return result;
	}
}

bool Loop::treat_collision(vector<int> prev_info) {
	if (prev_info[0] == 0) { return false; }
	vector<int> tobe_removed = candidates_tobe_removed(prev_info[1]);
	vector<int> adjust_info = adjust_shells(tobe_removed);

	if (adjust_info[0] == 0) {    // insert
		return false;
	}
	else if (adjust_info[0] == 1) {    // delete
		if (adjust_info[1] == 0) { return true; }    // first shell removed -> no need to event update
		else if ((maked_shells == total_shells) && (adjust_info[1] == shells.size())) { return true; }    // last shell removed -> no need to event update
		/*
		event_velocity = (int)((shells[adjust_info[1]].get_index() -
								shells[adjust_info[1] - 1].get_index() +
								2 * RADIUS) / event_timelimit);
		*/
	}

	event_update_idx_info.push_back(adjust_info);
	return true;
}




// public

void Loop::idle_update() {
	round_finish_check();
	add_shell();
	move();
}

void Loop::displaycharacters(void* font, string str, float x, float y) const {
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(x, y);
	for (int i = 0; i < (int)str.size(); i++)
		glutBitmapCharacter(font, str[i]);
}


void Loop::draw() const {
	// score
	stringstream b;
	b << score;
	displaycharacters(GLUT_BITMAP_TIMES_ROMAN_24, "Score is " + b.str(), boundary_x * 0.65f, boundary_y * 0.65f);

	// loop
	glDisable(GL_LIGHTING);
	glLineWidth(line_width);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.5f, 0.5f, 0.5f);
	for (auto itr = loop_points.begin() + 2*RADIUS; itr < loop_points.end(); ++itr)
		glVertex3f((*itr)[0], (*itr)[1], (*itr)[2]);
	glEnd();
	glEnable(GL_LIGHTING);

	// shells
	for (auto shell_itr = shells.begin(); shell_itr < shells.end(); ++shell_itr) {
		shell_itr->draw();
	}

	// custom for each loops
	additional_draw();
}

bool Loop::event_update() {
	/*
	activate when event_update_info has (unique) element
	*/
	round_finish_check();

	bool repeat = false;

	for (auto itr = event_update_idx_info.begin(); itr < event_update_idx_info.end(); ++itr) {
		if ((*itr)[0] == 0) {    // insert
			// move
			shells[(*itr)[1]].move();
			for (auto shell_itr = shells.begin(); shell_itr < shells.begin() + (*itr)[1]; ++shell_itr) {
				shell_itr->move_by_index(event_velocity, loop_points);
			}

			// determine repeation
			vector<float> zero = { 0,0,0 };
			if ((*itr)[1] == 0) {
				if (distance(loop_points[shells[(*itr)[1]].get_index()], shells[(*itr)[1]].get_center()) < distance(shells[(*itr)[1]].get_velocity(), zero)) {
					repeat = false;
				}
				else { repeat = true; }
			}
			else if ((*itr)[1] < shells.size() - 1) {
				if (shells[(*itr)[1] - 1].get_index() - shells[(*itr)[1] + 1].get_index() > 4 * RADIUS - event_velocity) {
					repeat = false;
				}
				else { repeat = true; }
			}
			else {    // (*itr)[1] = shells.size() - 1
				if (distance(loop_points[shells[(*itr)[1]].get_index()], shells[(*itr)[1]].get_center()) < distance(shells[(*itr)[1]].get_velocity(), zero)) {
					repeat = false;
				}
				else { repeat = true; }
			}
		}


		else if ((*itr)[0] == 1) {    // delete
			// move
			for (auto shell_itr = shells.begin(); shell_itr < shells.begin() + (*itr)[1]; ++shell_itr) {
				shell_itr->move_by_index(-event_velocity, loop_points);    // move backward -> - at velocity
			}

			// determine repeation
			if ((*itr)[1] < shells.size()) {    // (*itr)[1] > 0 always
				if (shells[(*itr)[1] - 1].get_index() - shells[(*itr)[1]].get_index() < 2 * RADIUS + Event_Loop_velocity) {
					repeat = false;
				}
				else { repeat = true; }
			}
			else {
				if (shells[(*itr)[1] - 1].get_index() < RADIUS + Event_Loop_velocity) {    // (0 < ~~ < 2*RADIUS) + Event_Loop_velocity
					repeat = false;
				}
				else { repeat = true; }
			}
		}

	}

	return repeat;
}

vector<int> Loop::event_postporcessing() {
	round_finish_check();

	// fine-tunning
	vector<int> prev_info = { 0,0 };
	for (auto itr = event_update_idx_info.begin(); itr < event_update_idx_info.end(); ++itr) {
		if ((*itr)[0] == 0) {    // insert
			if ((*itr)[1] < shells.size() - 1) {    // inserted at index [0, size-1)
				// inserted shell
				int target_index = shells[(*itr)[1] + 1].get_index() + 2 * RADIUS;
				shells[(*itr)[1]].set_index(target_index);
				shells[(*itr)[1]].set_center(loop_points[target_index]);

				// forward shells
				int standard_index = shells[(*itr)[1]].get_index();
				for (auto shell_itr = shells.begin(); shell_itr < shells.begin() + (*itr)[1]; ++shell_itr) {
					int gap = 2 * RADIUS * (shells.begin() + (*itr)[1] - shell_itr);
					int exact_index = gap + (shells.begin() + (*itr)[1])->get_index();
					shell_itr->set_index(exact_index);
					shell_itr->set_center(loop_points[exact_index]);
				}
			}
			else {    // inserted at last index (= size-1)
				// inserted shell (only) <- simplification trick
				int target_index = (shells.end()-2)->get_index() - 2 * RADIUS;
				shells[(*itr)[1]].set_index(target_index);
				shells[(*itr)[1]].set_center(loop_points[target_index]);
			}
		}

		else if ((*itr)[0] = 1) {    // delete
			// forward shells
			for (auto shell_itr = shells.begin(); shell_itr < shells.begin() + (*itr)[1]; ++shell_itr) {
				if ((*itr)[1] == shells.size()) { continue; }    // event-update breaking check implies fine-tunning
				int gap = 2 * RADIUS * (shells.begin() + (*itr)[1] - shell_itr);    // note : (*itr)[1] < shells.size()
				int exact_index = gap + (shells.begin() + (*itr)[1])->get_index();
				shell_itr->set_index(exact_index);
				shell_itr->set_center(loop_points[exact_index]);
			}
		}
		// reset event-related parameters and return used parameters
		prev_info = *event_update_idx_info.begin();
	}
	event_update_idx_info.clear();


	return prev_info;
}



// Round 1

Loop_1::Loop_1() : Loop() {
	// or use set_shell_parameters
	reset();
	total_shells = Total_num1;
	maked_shells = 0;
	loop_radius = Loop_radius;
}

void Loop_1::create_loop() {
	int num = loop_radius * 5 * PI / 3;
	for (int i = -2*RADIUS; i < num; i++) {
		loop_points.push_back({loop_radius * sin((float)PI / 6 + i / loop_radius),
							   loop_radius * cos((float)PI / 6 + i / loop_radius),
							   0});
	}
}

vector<float> Loop_1::tangent_vector(int i) const {
	vector<float> result = { loop_points[i][1], -1*loop_points[i][0], 0 };
	return result;
}

void Loop_1::additional_draw() const {
	glDisable(GL_LIGHTING);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex3f(loop_points[2 * RADIUS][0] - RADIUS, loop_points[2 * RADIUS][1] - sqrt(3) * RADIUS, RADIUS+1);
	glVertex3f(loop_points[2 * RADIUS][0] + RADIUS, loop_points[2 * RADIUS][1] + sqrt(3) * RADIUS, RADIUS + 1);
	glVertex3f(loop_points[2 * RADIUS][0] - 2*sqrt(3)*RADIUS, loop_points[2 * RADIUS][1] + (sqrt(3)+1) * RADIUS, RADIUS + 1);
	glVertex3f(loop_points[2 * RADIUS][0] - 2 * sqrt(3) * RADIUS, loop_points[2 * RADIUS][1] - (sqrt(3)-1) * RADIUS, RADIUS + 1);
	glEnd();
	glEnable(GL_LIGHTING);
}



// Round 2

Loop_2::Loop_2() : Loop() {
	reset();
	total_shells = Total_num2;
	maked_shells = 0;
}

void Loop_2::create_loop() {
	int num = sqrt(window_height * window_height + (X2_top - X2_bottom) * (X2_top - X2_bottom));
	float width = (X2_top - X2_bottom) / sqrt(window_height * window_height + (X2_top - X2_bottom) * (X2_top - X2_bottom));
	float height = (window_height) / sqrt(window_height * window_height + (X2_top - X2_bottom) * (X2_top - X2_bottom));
	for (int i = -2 * RADIUS; i < num + 1; i++) {
		loop_points.push_back({ X2_bottom + width * i, height * i - boundary_y, 0 });
	}
}

vector<float> Loop_2::tangent_vector(int i) const {
	return { X2_top - X2_bottom, window_height, 0 };
}

void Loop_2::additional_draw() const {}



// Round 3

Loop_3::Loop_3() : Loop() {
	reset();
	total_shells = Total_num3;
	maked_shells = 0;
}

void Loop_3::create_loop() {
	for (int i = -2 * RADIUS - boundary_x; i < X3; i++) {
		loop_points.push_back({ (float)i, Y3_high, 0 });
	}
	for (int i = Y3_high; i > Y3_low; i--) {
		loop_points.push_back({ X3, (float)i, 0 });
	}
	for (int i = X3; i > -1 - boundary_x; i--) {
		loop_points.push_back({ (float)i, Y3_low, 0 });
	}
}

vector<float> Loop_3::tangent_vector(int i) const {
	if (i < Y3_high) {
		return { 1,0,0 };
	}
	else if (i < Y3_high + Y3_low) {
		return { 0,-1,0 };
	}
	else { // i <= Y3_high + Y3_low
		return { -1,0,0 };
	}
}

void Loop_3::additional_draw() const {}