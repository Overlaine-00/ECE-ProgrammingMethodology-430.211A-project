#pragma once
#include <iostream>
#include <sstream>

#include "Shell.h"

using namespace std;

class Loop {
	/*
	Regard center as (0,0,0). Otherwise, ues translate when draw
	*/
protected:
	vector<vector<float>> loop_points;
	vector<Shell> shells;    // forward element : closer to the end of loop

	int score;
	int total_shells;    // total shells for each round
	int maked_shells;    // created for each round

	float line_width = RADIUS/5;
	int velocity = Idle_Loop_velocity;    // # of loop_point moved for each update

	vector<vector<int>> event_update_idx_info;    // contains at most one element
	int event_velocity = Event_Loop_velocity;    // # of loop_point moved for each update in event


	// initial functions
	virtual void create_loop() = 0;

	// idle functions
	Shell create_shell();

	void move();
	void add_shell();
	void round_finish_check();


	// event functions
	/* initial collision */
	virtual vector<float> tangent_vector(int i) const = 0;
	float distance(vector<float> a, vector<float> b) const;
	bool collide_with_before(Shell& shell, int i) const;    // true : collide between index i and i-1

	int detect_collision(Shell& shell) const;
	vector<int> candidates_tobe_removed(Shell& shell, int collide_at);
	vector<int> adjust_shells(vector<int> range, Shell& shell);

	/* chained collision */
	vector<int> candidates_tobe_removed(int next_part_i);
	vector<int> adjust_shells(vector<int> range);

public:
	Loop();
	void reset();
	void displaycharacters(void* font, string str, float x, float y) const;

	// idle update
	void idle_update();

	// event update.
	/*
	order : repetion of treat_collision -> event_update -> event_postprocessing
	*/
	/* initial collision */
	bool treat_collision(Shell& shell);    // activated at idle, role : preprocessing (init condition)
	/* chained collision */
	bool treat_collision(vector<int> next_part_i);

	bool event_update();    // activated when event_update_info has element
	vector<int> event_postporcessing();

	void draw() const;    // may becomes virtual
	virtual void additional_draw() const = 0;
};


class Loop_1 : public Loop {
private:
	float loop_radius;

	virtual vector<float> tangent_vector(int i) const override;

public:
	Loop_1();
	virtual void create_loop() override;
	virtual void additional_draw() const override;
};

class Loop_2 : public Loop {
private:
	virtual vector<float> tangent_vector(int i) const override;

public:
	Loop_2();
	virtual void create_loop() override;
	virtual void additional_draw() const override;
};

class Loop_3 : public Loop {
private:
	virtual vector<float> tangent_vector(int i) const override;

public:
	Loop_3();
	virtual void create_loop() override;
	virtual void additional_draw() const override;
};