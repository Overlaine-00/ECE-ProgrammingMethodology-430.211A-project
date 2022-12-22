#pragma once
#include <vector>
#include <random>

#include "Constraints.h"
#include "Material.h"

#include <GL/glut.h>

using namespace std;

class Shell{
private:
	Material mtl;

	float radius;    // every shell must have radius = RADIUS
	float slice = 20;
	float stack = 20;

	vector<float> pos = { 0,0,0 };
	float type;    // 0:R, 1:G, 2:B
	vector<float> velocity = { 0,0,0 };
	
	int index_on_loop;

	int get_random_color() const;

public:
	Shell();
	Shell(vector<float> p);
	
	void set_center(vector<float> p);
	vector<float> get_center() const;

	void set_velocity(int axis, float v);
	void set_velocity(vector<float> v);
	vector<float> get_velocity() const;

	float get_radius() const { return radius; }

	void set_index(int i);
	int get_index() const;

	void set_type(int t);
	int get_type() const;


	void move();
	void move_by_index(int v, const vector<vector<float>>& loop_point);

	void draw() const;
};

