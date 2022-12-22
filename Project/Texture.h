#pragma once

#include <iostream>
#include <string>
#include <Freeimage/FreeImage.h>
#include <GL/glut.h>
using namespace std;

class Texture
{
public:
	Texture();

	FIBITMAP* createBitMap(string filename) const;
	void generateTexture() const;
	void initializeTexture(string filename) const;

	GLuint getTextureID() const;

private:
	mutable GLuint textureID;
	mutable GLubyte* textureData;
	mutable int imageWidth, imageHeight;
};

