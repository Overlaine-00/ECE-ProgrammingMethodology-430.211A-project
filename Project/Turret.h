#pragma once
#include <vector>

#include "Constraints.h"
#include "Texture.h"

#include <GL/glut.h>

using namespace std;

class Turret {
	/*
	radius : radius of body
	cannon_width : width of cannon.
		shell may have radius = cannon_width/2 or larger, but
		it may not exceeds cannon_width
	center : may fixed to (0,0)
	*/
private:
	vector<float> pos = { 0,0,0 };
	float radius;    // 3*(radius of shell)
	float cannon_width;    // 2*(radius of shell)

	Texture texture;
	
	// relative position : when pos = [0,0,0]
	// 0th : load, 1st : fired at next click
	//vector<vector<float>> shell_pos;

public:
	// constructor
	Turret();
	Turret(float shell_radius);
	Turret(float x, float y);
	Turret(float x, float y, float shell_radius);

	void initialize_texture();

	vector<float> get_center() const;


	// display
	void draw() const;
};