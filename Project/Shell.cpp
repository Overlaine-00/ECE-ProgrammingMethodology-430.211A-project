#include <iostream>
#include "Shell.h"


int Shell::get_random_color() const {
	return std::rand() % 3;
}

// constructor

Shell::Shell() {
	/*
	used at shells in loop
	* radius : default RADIUS
	* color : default random
	* pos : nan
	* velocity : nan
	* index : default 0
	* mtl : default
	*/
	radius = RADIUS;
	type = get_random_color();
	mtl.set_color(type);

	index_on_loop = 0;
}

Shell::Shell(vector<float> p) {
	/*
	used at shells in cannon
	* radius : default RADIUS
	* color : default random
	* pos : input
	* velocity : defalut {0,2,0} (move to forward position)
	* index : default 0
	* mtl : default
	*/
	radius = RADIUS;
	type = get_random_color();
	mtl.set_color(type);
	for (int i = 0; i < 3; ++i) {
		pos[i] = p[i];
	}
	set_velocity({ 0,3,0 });
	index_on_loop = 0;
}


void Shell::set_center(vector<float> p) {
	pos = p;
}




void Shell::set_velocity(int axis, float v) {
	velocity[axis] = v;
}

void Shell::set_velocity(vector<float> v) {
	velocity[0] = v[0], velocity[1] = v[1], velocity[2] = v[2];
}



vector<float> Shell::get_center() const {
	return pos;
}

vector<float> Shell::get_velocity() const {
	return velocity;
}


void Shell::set_index(int i) {
	index_on_loop = i;
}

int Shell::get_index() const {
	return index_on_loop;
}


void Shell::set_type(int i) {
	type = i;
	mtl.set_color(type);
}

int Shell::get_type() const{
	return type;
}


void Shell::move() {
	/* used at armed/shooted shells */
	pos[0] += velocity[0], pos[1] += velocity[1], pos[2] += velocity[2];
}

void Shell::move_by_index(int v, const vector<vector<float>>& loop_point) {
	/* used at shells in loop */
	index_on_loop += v;
	if (index_on_loop >= loop_point.size()) {
		throw -1;
	}
	set_center(loop_point[index_on_loop]);
}



void Shell::draw() const {
	/*
	This contains push-pop matrix
	*/
	//glPushMatrix();
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_EMISSION, mtl.getEmission());
	glMaterialfv(GL_FRONT, GL_AMBIENT, mtl.getAmbient());
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mtl.getDiffuse());
	glMaterialfv(GL_FRONT, GL_SPECULAR, mtl.getSpecular());
	glMaterialfv(GL_FRONT, GL_SHININESS, mtl.getShininess());

	glTranslatef(pos[0], pos[1], pos[2]);
	glutSolidSphere(radius, slice, stack);
	glTranslatef(-pos[0], -pos[1], -pos[2]);
	//glPopMatrix();
}