#include "Turret.h"

// constructor
Turret::Turret() {
	pos[0] = 0, pos[1] = 0, pos[2] = 0;
	radius = 3 * RADIUS, cannon_width = 2 * RADIUS;
}

Turret::Turret(float shell_radius) {
	pos[0] = 0, pos[1] = 0, pos[2] = 0;
	radius = 3 * shell_radius, cannon_width = 2 * shell_radius;
}

Turret::Turret(float x, float y) {
	pos[0] = x, pos[1] = y, pos[2] = 0;
	radius = 3 * RADIUS, cannon_width = 2 * RADIUS;
}

Turret::Turret(float x, float y, float shell_radius) {
	pos[0] = x, pos[1] = y, pos[2] = 0;
	radius = 3 * shell_radius, cannon_width = 2 * shell_radius;
}

void Turret::initialize_texture() {
	texture.initializeTexture("Image/turret.png");
}


vector<float> Turret::get_center() const {
	return pos;
}


void Turret::draw() const {
	/*
		base direction of cannon : positive y direction
		This contains push-pop matrix
	*/
	glDisable(GL_LIGHTING);

	// Turret.  using texture
	// In case using 3d : using quads to build surface as in homework (ref. lab1 week 07)
	glColor3f(0, 0.0, 0.0);
	glBegin(GL_QUADS);    // inner : remains black
	glVertex2f(-cannon_width / 2, 0);
	glVertex2f(cannon_width / 2, 0);
	glVertex2f(cannon_width / 2, radius + cannon_width * 1 / 3);
	glVertex2f(-cannon_width / 2, radius + cannon_width * 1 / 3);
	glEnd();
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, texture.getTextureID());
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.5f);		glVertex2f(-cannon_width, -cannon_width / 2);
	glTexCoord2f(0.2f, 0.2f);	    glVertex2f(-cannon_width / 2, -cannon_width / 2);
	glTexCoord2f(0.5f, 0.f);	    glVertex2f(-cannon_width / 2, -cannon_width);
	glTexCoord2f(0.7f, 0.2f);		glVertex2f(cannon_width / 2, -cannon_width);
	glTexCoord2f(0.7f, 0.7f);		glVertex2f(cannon_width, -cannon_width / 2);
	glTexCoord2f(0.5f, 1.0f);		glVertex2f(cannon_width, radius + cannon_width * 1 / 3);
	glTexCoord2f(0.2f, 0.7f);		glVertex2f(-cannon_width, radius + cannon_width * 1 / 3);
	glTexCoord2f(0.0f, 0.5f);		glVertex2f(-cannon_width, -cannon_width / 2);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
}