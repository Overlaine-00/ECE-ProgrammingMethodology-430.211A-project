#pragma once
#include <iostream>
#include <string>
#include "Texture.h"
#include "Constraints.h"
using namespace std;
class Screen {
private:
	Texture texture1;
	Texture texture2;
	Texture texture3;
	Texture texture1b;

public:
	void displayCharacters(void* font, string str, float x, float y);
	void initialize();
	void start_display();
	void gameover_display();
	void gameclear_display(int present_stage);
};

