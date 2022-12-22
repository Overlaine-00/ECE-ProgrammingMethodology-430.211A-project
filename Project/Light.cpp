#include <iostream>
#include "Light.h"

#include <GL/glut.h>



Light::Light(float x, float y, float z, int LID) {
	pos[0] = x, pos[1] = y, pos[2] = z;
	lightID = LID; bLightOn = true;
	
	setAmbient(0.5f, 0.5f, 0.5f, 1.0f);
	setDiffuse(0.7f, 0.7f, 0.7f, 1.0f);
	setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
}

void Light::setLightID(int LID) {
	lightID = LID;
}

void Light::setPosition(float x, float y, float z) {
	pos[0] = x, pos[1] = y, pos[2] = z;
}

void Light::setAmbient(float r, float g, float b, float a) {
	ambient[0] = r, ambient[1] = g, ambient[2] = b, ambient[3] = a;
}

void Light::setDiffuse(float r, float g, float b, float a) {
	diffuse[0] = r, diffuse[1] = g, diffuse[2] = b, diffuse[3] = a;
}

void Light::setSpecular(float r, float g, float b, float a) {
	specular[0] = r, specular[1] = g, specular[2] = b, specular[3] = a;
}

void Light::enableLight(bool bOn) {
	bLightOn = bOn;
}

bool Light::isLightOn() const {
	return bLightOn;
}

void Light::draw() const {
	if (bLightOn) {
		glEnable(lightID);
		glLightfv(lightID, GL_AMBIENT, ambient);
		glLightfv(lightID, GL_DIFFUSE, diffuse);
		glLightfv(lightID, GL_SPECULAR, specular);
		glLightfv(lightID, GL_POSITION, pos);
	}
	else {
		glDisable(lightID);
	}
}