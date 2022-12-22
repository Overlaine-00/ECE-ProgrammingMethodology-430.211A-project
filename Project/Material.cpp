#include <iostream>
#include "Material.h"


Material::Material() {
	setEmission(0.1f, 0.1f, 0.1f, 1.0f);
	setAmbient(0.4f, 0.4f, 0.1f, 1.0f);
	setDiffuse(0.7f, 0.7f, 0.7f, 1.0f);
	setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
	setShininess(10.0f);
}


void Material::setEmission(float r, float g, float b, float a) {
	emission[0] = r, emission[1] = g, emission[2] = b, emission[3] = a;
}

void Material::setAmbient(float r, float g, float b, float a) {
	ambient[0] = r, ambient[1] = g, ambient[2] = b, ambient[3] = a;
}

void Material::setDiffuse(float r, float g, float b, float a) {
	diffuse[0] = r, diffuse[1] = g, diffuse[2] = b, diffuse[3] = a;
}

void Material::setSpecular(float r, float g, float b, float a) {
	specular[0] = r, specular[1] = g, specular[2] = b, specular[3] = a;
}

void Material::setShininess(float sh) {
	shininess[0] = sh;
}

void Material::set_color(int type) {
	/*
	Red : 0, Green : 1, Blue : 2
	*/
	switch (type) {
	case 0 :
		setAmbient(0.05f, 0.0f, 0.0f, 1.0f);
		setDiffuse(0.5f, 0.4f, 0.4f, 1.0f);
		setSpecular(0.7f, 0.04f, 0.04f, 1.0f);
		break;

	case 1:
		setAmbient(0.0f, 0.05f, 0.0f, 1.0f);
		setDiffuse(0.4f, 0.5f, 0.4f, 1.0f);
		setSpecular(0.04f, 0.7f, 0.04f, 1.0f);
		break;

	case 2:
		setAmbient(0.0f, 0.05f, 0.05f, 1.0f);
		setDiffuse(0.4f, 0.5f, 0.5f, 1.0f);
		setSpecular(0.04f, 0.7f, 0.7f, 1.0f);
		break;
	}
}


const float* Material::getEmission() const {
	return emission;
}

const float* Material::getAmbient() const {
	return ambient;
}

const float* Material::getDiffuse() const {
	return diffuse;
}

const float* Material::getSpecular() const {
	return specular;
}

const float* Material::getShininess() const {
	return shininess;
}
