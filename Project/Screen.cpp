#include "Screen.h"

void Screen::displayCharacters(void* font, string str, float x, float y) {
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(x, y);
	for (int i = 0; i < (int)str.size(); i++)
		glutBitmapCharacter(font, str[i]);
}

void Screen::initialize() {
	texture1.initializeTexture("Image/start.jpg");
	texture1b.initializeTexture("Image/sky.jpg");
	texture3.initializeTexture("Image/gameclear.png");
	texture2.initializeTexture("Image/gameover.png");
}

void Screen::start_display() {
	/*
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-boundary_x, boundary_x, -boundary_y, boundary_y, -100.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	*/
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, texture1b.getTextureID());
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);		glVertex2f(-450, -450);
	glTexCoord2f(0.0f, 1.0f);		glVertex2f(-450, 450);
	glTexCoord2f(1.0f, 1.0f);		glVertex2f(450, 450);
	glTexCoord2f(1.0f, 0.0f);		glVertex2f(450, -450);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, texture1.getTextureID());
	glBegin(GL_LINE_STRIP); //p
	glTexCoord2f(0.0f, 0.0f);		glVertex2f(-450, 50);
	glTexCoord2f(0.1f, 0.1f);	    glVertex2f(-450, 200);
	glTexCoord2f(0.2f, 0.2f);	    glVertex2f(-300, 200);
	glTexCoord2f(0.3f, 0.3f);		glVertex2f(-300, 140);
	glTexCoord2f(0.4f, 0.4f);		glVertex2f(-430, 140);
	glTexCoord2f(0.5f, 0.5f);		glVertex2f(-430, 160);
	glTexCoord2f(0.6f, 0.6f);		glVertex2f(-320, 160);
	glTexCoord2f(0.7f, 0.7f);		glVertex2f(-320, 180);
	glTexCoord2f(0.8f, 0.8f);		glVertex2f(-430, 180);
	glTexCoord2f(0.9f, 0.9f);		glVertex2f(-430, 50);
	glTexCoord2f(0.9f, 0.9f);		glVertex2f(-450, 50);
	glEnd();
	glBegin(GL_LINE_STRIP);//u
	glTexCoord2f(0.0f, 0.0f);		glVertex2f(-200, 50);
	glTexCoord2f(0.1f, 0.1f);	    glVertex2f(-200, 200);
	glTexCoord2f(0.2f, 0.2f);	    glVertex2f(-170, 200);
	glTexCoord2f(0.3f, 0.3f);		glVertex2f(-170, 80);
	glTexCoord2f(0.4f, 0.4f);		glVertex2f(-80, 80);
	glTexCoord2f(0.5f, 0.5f);		glVertex2f(-80, 200);
	glTexCoord2f(0.6f, 0.6f);		glVertex2f(-50, 200);
	glTexCoord2f(0.7f, 0.7f);		glVertex2f(-50, 50);
	glTexCoord2f(0.8f, 0.8f);		glVertex2f(-200, 50);
	glEnd();
	glBegin(GL_LINE_STRIP);//z
	glTexCoord2f(0.0f, 0.0f);		glVertex2f(200, 50);
	glTexCoord2f(0.1f, 0.1f);	    glVertex2f(200, 80);
	glTexCoord2f(0.2f, 0.2f);	    glVertex2f(80, 80);
	glTexCoord2f(0.3f, 0.3f);		glVertex2f(170, 170);
	glTexCoord2f(0.4f, 0.4f);		glVertex2f(200, 170);
	glTexCoord2f(0.5f, 0.5f);		glVertex2f(200, 200);
	glTexCoord2f(0.6f, 0.6f);		glVertex2f(50, 200);
	glTexCoord2f(0.7f, 0.7f);		glVertex2f(50, 170);
	glTexCoord2f(0.8f, 0.8f);		glVertex2f(140, 170);
	glTexCoord2f(0.85f, 0.85f);		glVertex2f(50, 80);
	glTexCoord2f(0.9f, 0.9f);		glVertex2f(50, 50);
	glTexCoord2f(0.95f, 0.95f);		glVertex2f(200, 50);
	glEnd();
	glBegin(GL_LINE_STRIP);//z
	glTexCoord2f(0.0f, 0.0f);		glVertex2f(450, 50);
	glTexCoord2f(0.1f, 0.1f);	    glVertex2f(450, 80);
	glTexCoord2f(0.2f, 0.2f);	    glVertex2f(330, 80);
	glTexCoord2f(0.3f, 0.3f);		glVertex2f(420, 170);
	glTexCoord2f(0.4f, 0.4f);		glVertex2f(450, 170);
	glTexCoord2f(0.5f, 0.5f);		glVertex2f(450, 200);
	glTexCoord2f(0.6f, 0.6f);		glVertex2f(300, 200);
	glTexCoord2f(0.7f, 0.7f);		glVertex2f(300, 170);
	glTexCoord2f(0.8f, 0.8f);		glVertex2f(390, 170);
	glTexCoord2f(0.85f, 0.85f);		glVertex2f(300, 80);
	glTexCoord2f(0.9f, 0.9f);		glVertex2f(300, 50);
	glTexCoord2f(0.95f, 0.95f);		glVertex2f(450, 50);
	glEnd();
	glBegin(GL_LINE_STRIP);//l
	glTexCoord2f(0.0f, 0.0f);		glVertex2f(-450, -200);
	glTexCoord2f(0.1f, 0.1f);	    glVertex2f(-450, -50);
	glTexCoord2f(0.2f, 0.2f);	    glVertex2f(-420, -50);
	glTexCoord2f(0.3f, 0.3f);		glVertex2f(-420, -170);
	glTexCoord2f(0.4f, 0.4f);		glVertex2f(-300, -170);
	glTexCoord2f(0.5f, 0.5f);		glVertex2f(-300, -200);
	glTexCoord2f(0.6f, 0.6f);		glVertex2f(-450, -200);
	glEnd();
	glBegin(GL_LINE_STRIP);//o
	glTexCoord2f(0.0f, 0.0f);		glVertex2f(-126, -220);
	glTexCoord2f(0.05f, 0.05f);	    glVertex2f(-126, -190);
	glTexCoord2f(0.1f, 0.1f);	    glVertex2f(-170, -144);
	glTexCoord2f(0.15f, 0.15f);		glVertex2f(-170, -90);
	glTexCoord2f(0.2f, 0.2f);		glVertex2f(-125, -50);
	glTexCoord2f(0.25f, 0.25f);		glVertex2f(-80, -90);
	glTexCoord2f(0.3f, 0.3f);		glVertex2f(-80, -144);
	glTexCoord2f(0.4f, 0.4f);		glVertex2f(-124, -190);
	glTexCoord2f(0.45f, 0.45f);	    glVertex2f(-124, -220);
	glTexCoord2f(0.5f, 0.5f);	    glVertex2f(-30, -159);
	glTexCoord2f(0.6f, 0.6f);		glVertex2f(-30, -80);
	glTexCoord2f(0.67f, 0.67f);		glVertex2f(-90, -30);
	glTexCoord2f(0.7f, 0.7f);		glVertex2f(-160, -30);
	glTexCoord2f(0.75f, 0.75f);		glVertex2f(-220, -80);
	glTexCoord2f(0.8f, 0.8f);		glVertex2f(-220, -159);
	glTexCoord2f(0.9f, 0.9f);		glVertex2f(-126, -220);
	glEnd();
	glBegin(GL_LINE_STRIP);//o
	glTexCoord2f(0.0f, 0.0f);		glVertex2f(124, -220);
	glTexCoord2f(0.05f, 0.05f);	    glVertex2f(124, -190);
	glTexCoord2f(0.1f, 0.1f);	    glVertex2f(80, -144);
	glTexCoord2f(0.15f, 0.15f);		glVertex2f(80, -90);
	glTexCoord2f(0.2f, 0.2f);		glVertex2f(125, -50);
	glTexCoord2f(0.25f, 0.25f);		glVertex2f(170, -90);
	glTexCoord2f(0.3f, 0.3f);		glVertex2f(170, -144);
	glTexCoord2f(0.4f, 0.4f);		glVertex2f(126, -190);
	glTexCoord2f(0.45f, 0.45f);	    glVertex2f(126, -220);
	glTexCoord2f(0.5f, 0.5f);	    glVertex2f(220, -159);
	glTexCoord2f(0.6f, 0.6f);		glVertex2f(220, -80);
	glTexCoord2f(0.67f, 0.67f);		glVertex2f(160, -30);
	glTexCoord2f(0.7f, 0.7f);		glVertex2f(90, -30);
	glTexCoord2f(0.75f, 0.75f);		glVertex2f(30, -80);
	glTexCoord2f(0.8f, 0.8f);		glVertex2f(30, -159);
	glTexCoord2f(0.9f, 0.9f);		glVertex2f(124, -220);
	glEnd();
	glBegin(GL_LINE_STRIP);//p
	glTexCoord2f(0.0f, 0.0f);		glVertex2f(300, -200);
	glTexCoord2f(0.1f, 0.1f);	    glVertex2f(300, -50);
	glTexCoord2f(0.2f, 0.2f);	    glVertex2f(450, -50);
	glTexCoord2f(0.3f, 0.3f);		glVertex2f(450, -110);
	glTexCoord2f(0.4f, 0.4f);		glVertex2f(320, -110);
	glTexCoord2f(0.5f, 0.5f);		glVertex2f(320, -90);
	glTexCoord2f(0.6f, 0.6f);		glVertex2f(430, -90);
	glTexCoord2f(0.7f, 0.7f);		glVertex2f(430, -70);
	glTexCoord2f(0.8f, 0.8f);		glVertex2f(320, -70);
	glTexCoord2f(0.9f, 0.9f);		glVertex2f(320, -200);
	glTexCoord2f(0.9f, 0.9f);		glVertex2f(300, -200);
	glEnd();


	glDisable(GL_TEXTURE_2D);
	displayCharacters(GLUT_BITMAP_TIMES_ROMAN_24, "Press Left Mouth Button To Start", -boundary_x * 0.55f, boundary_y * 0.55f);
	displayCharacters(GLUT_BITMAP_TIMES_ROMAN_24, "Press 'q' Button To End The GAME", -boundary_x * 0.55f, -boundary_y * 0.55f);

	// glutSwapBuffers();

}

void Screen::gameover_display() {
	/*
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-boundary_x, boundary_x, -boundary_y, boundary_y, -100.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	*/
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, texture2.getTextureID());
	glBegin(GL_LINE_STRIP); //g
	glTexCoord2f(0.0f, 0.0f);		glVertex2f(-280, 50);
	glTexCoord2f(0.05f, 0.05f);	    glVertex2f(-470, 50);
	glTexCoord2f(0.1f, 0.1f);	    glVertex2f(-470, 170);
	glTexCoord2f(0.15f, 0.15f);		glVertex2f(-370, 220);
	glTexCoord2f(0.2f, 0.2f);		glVertex2f(-280, 220);
	glTexCoord2f(0.25f, 0.25f);		glVertex2f(-280, 170);
	glTexCoord2f(0.3f, 0.3f);		glVertex2f(-340, 170);
	glTexCoord2f(0.4f, 0.4f);		glVertex2f(-440, 140);
	glTexCoord2f(0.45f, 0.45f);	    glVertex2f(-440, 80);
	glTexCoord2f(0.5f, 0.5f);	    glVertex2f(-310, 80);
	glTexCoord2f(0.6f, 0.6f);		glVertex2f(-310, 110);
	glTexCoord2f(0.67f, 0.67f);		glVertex2f(-350, 110);
	glTexCoord2f(0.7f, 0.7f);		glVertex2f(-350, 140);
	glTexCoord2f(0.75f, 0.75f);		glVertex2f(-280, 140);
	glTexCoord2f(0.8f, 0.8f);		glVertex2f(-280, 50);
	glEnd();
	glBegin(GL_LINE_STRIP);//a
	glTexCoord2f(0.0f, 0.0f);		glVertex2f(-220, 50);
	glTexCoord2f(0.05f, 0.05f);	    glVertex2f(-125, 220);
	glTexCoord2f(0.1f, 0.1f);	    glVertex2f(-30, 50);
	glTexCoord2f(0.15f, 0.15f);		glVertex2f(-70, 50);
	glTexCoord2f(0.2f, 0.2f);		glVertex2f(-110, 125);
	glTexCoord2f(0.25f, 0.25f);		glVertex2f(-140, 125);
	glTexCoord2f(0.3f, 0.3f);		glVertex2f(-180, 50);
	glTexCoord2f(0.4f, 0.4f);		glVertex2f(-220, 50);
	glEnd();
	glBegin(GL_LINE_STRIP);//m
	glTexCoord2f(0.0f, 0.0f);		glVertex2f(30, 50);
	glTexCoord2f(0.05f, 0.05f);	    glVertex2f(30, 220);
	glTexCoord2f(0.1f, 0.1f);	    glVertex2f(60, 220);
	glTexCoord2f(0.15f, 0.15f);		glVertex2f(125, 175);
	glTexCoord2f(0.2f, 0.2f);		glVertex2f(190, 220);
	glTexCoord2f(0.25f, 0.25f);		glVertex2f(220, 220);
	glTexCoord2f(0.3f, 0.3f);		glVertex2f(220, 50);
	glTexCoord2f(0.4f, 0.4f);		glVertex2f(190, 50);
	glTexCoord2f(0.45f, 0.45f);	    glVertex2f(190, 185);
	glTexCoord2f(0.5f, 0.5f);	    glVertex2f(125, 125);
	glTexCoord2f(0.6f, 0.6f);		glVertex2f(60, 185);
	glTexCoord2f(0.67f, 0.67f);		glVertex2f(60, 50);
	glTexCoord2f(0.7f, 0.7f);		glVertex2f(30, 50);
	glEnd();
	glBegin(GL_LINE_STRIP);//e
	glTexCoord2f(0.0f, 0.0f);		glVertex2f(280, 50);
	glTexCoord2f(0.05f, 0.05f);	    glVertex2f(280, 220);
	glTexCoord2f(0.1f, 0.1f);	    glVertex2f(470, 220);
	glTexCoord2f(0.15f, 0.15f);		glVertex2f(470, 185);
	glTexCoord2f(0.2f, 0.2f);		glVertex2f(310, 185);
	glTexCoord2f(0.25f, 0.25f);		glVertex2f(310, 140);
	glTexCoord2f(0.3f, 0.3f);		glVertex2f(470, 140);
	glTexCoord2f(0.4f, 0.4f);		glVertex2f(470, 110);
	glTexCoord2f(0.45f, 0.45f);	    glVertex2f(310, 110);
	glTexCoord2f(0.5f, 0.5f);	    glVertex2f(310, 85);
	glTexCoord2f(0.6f, 0.6f);		glVertex2f(470, 85);
	glTexCoord2f(0.67f, 0.67f);		glVertex2f(470, 50);
	glTexCoord2f(0.7f, 0.7f);		glVertex2f(280, 50);
	glEnd();
	glBegin(GL_LINE_STRIP);//o
	glTexCoord2f(0.0f, 0.0f);		glVertex2f(-376, -220);
	glTexCoord2f(0.05f, 0.05f);	    glVertex2f(-376, -190);
	glTexCoord2f(0.1f, 0.1f);	    glVertex2f(-420, -144);
	glTexCoord2f(0.15f, 0.15f);		glVertex2f(-420, -90);
	glTexCoord2f(0.2f, 0.2f);		glVertex2f(-375, -50);
	glTexCoord2f(0.25f, 0.25f);		glVertex2f(-330, -90);
	glTexCoord2f(0.3f, 0.3f);		glVertex2f(-330, -144);
	glTexCoord2f(0.4f, 0.4f);		glVertex2f(-374, -190);
	glTexCoord2f(0.45f, 0.45f);	    glVertex2f(-374, -220);
	glTexCoord2f(0.5f, 0.5f);	    glVertex2f(-280, -159);
	glTexCoord2f(0.6f, 0.6f);		glVertex2f(-280, -80);
	glTexCoord2f(0.67f, 0.67f);		glVertex2f(-340, -30);
	glTexCoord2f(0.7f, 0.7f);		glVertex2f(-410, -30);
	glTexCoord2f(0.75f, 0.75f);		glVertex2f(-470, -80);
	glTexCoord2f(0.8f, 0.8f);		glVertex2f(-470, -159);
	glTexCoord2f(0.9f, 0.9f);		glVertex2f(-376, -220);
	glEnd();
	glBegin(GL_LINE_STRIP);//v
	glTexCoord2f(0.0f, 0.0f);		glVertex2f(-220, -50);
	glTexCoord2f(0.05f, 0.05f);	    glVertex2f(-125, -220);
	glTexCoord2f(0.1f, 0.1f);	    glVertex2f(-30, -50);
	glTexCoord2f(0.15f, 0.15f);		glVertex2f(-70, -50);
	glTexCoord2f(0.2f, 0.2f);		glVertex2f(-110, -125);
	glTexCoord2f(0.25f, 0.25f);		glVertex2f(-140, -125);
	glTexCoord2f(0.3f, 0.3f);		glVertex2f(-180, -50);
	glTexCoord2f(0.4f, 0.4f);		glVertex2f(-220, -50);
	glEnd();
	glBegin(GL_LINE_STRIP);//e
	glTexCoord2f(0.0f, 0.0f);		glVertex2f(30, -200);
	glTexCoord2f(0.05f, 0.05f);	    glVertex2f(30, -30);
	glTexCoord2f(0.1f, 0.1f);	    glVertex2f(220, -30);
	glTexCoord2f(0.15f, 0.15f);		glVertex2f(220, -65);
	glTexCoord2f(0.2f, 0.2f);		glVertex2f(60, -65);
	glTexCoord2f(0.25f, 0.25f);		glVertex2f(60, -110);
	glTexCoord2f(0.3f, 0.3f);		glVertex2f(220, -110);
	glTexCoord2f(0.4f, 0.4f);		glVertex2f(220, -140);
	glTexCoord2f(0.45f, 0.45f);	    glVertex2f(60, -140);
	glTexCoord2f(0.5f, 0.5f);	    glVertex2f(60, -165);
	glTexCoord2f(0.6f, 0.6f);		glVertex2f(220, -165);
	glTexCoord2f(0.67f, 0.67f);		glVertex2f(220, -200);
	glTexCoord2f(0.7f, 0.7f);		glVertex2f(30, -200);
	glEnd();
	glBegin(GL_LINE_STRIP);//r
	glTexCoord2f(0.0f, 0.0f);		glVertex2f(280, -220);
	glTexCoord2f(0.05f, 0.05f);	    glVertex2f(280, -90);
	glTexCoord2f(0.1f, 0.1f);	    glVertex2f(330, -30);
	glTexCoord2f(0.15f, 0.15f);		glVertex2f(420, -30);
	glTexCoord2f(0.2f, 0.2f);		glVertex2f(470, -90);
	glTexCoord2f(0.25f, 0.25f);		glVertex2f(470, -125);
	glTexCoord2f(0.3f, 0.3f);		glVertex2f(370, -125);
	glTexCoord2f(0.4f, 0.4f);		glVertex2f(470, -220);
	glTexCoord2f(0.45f, 0.45f);	    glVertex2f(440, -220);
	glTexCoord2f(0.5f, 0.5f);	    glVertex2f(340, -140);
	glTexCoord2f(0.6f, 0.6f);		glVertex2f(340, -110);
	glTexCoord2f(0.67f, 0.67f);		glVertex2f(440, -110);
	glTexCoord2f(0.7f, 0.7f);		glVertex2f(440, -95);
	glTexCoord2f(0.8f, 0.8f);		glVertex2f(405, -75);
	glTexCoord2f(0.85f, 0.85f);	    glVertex2f(345, -75);
	glTexCoord2f(0.9f, 0.9f);	    glVertex2f(310, -105);
	glTexCoord2f(0.92f, 0.92f);	    glVertex2f(310, -220);
	glTexCoord2f(0.94f, 0.94f);	    glVertex2f(280, -220);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	displayCharacters(GLUT_BITMAP_TIMES_ROMAN_24, "Press 'q' Button To Go To Start Page", -boundary_x * 0.55f, -boundary_y * 0.55f);

	//glutSwapBuffers();
}

void Screen::gameclear_display(int present_stage) {
	/*
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-boundary_x, boundary_x, -boundary_y, boundary_y, -100.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	*/
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, texture3.getTextureID());
	glBegin(GL_LINE_STRIP); //g
	glTexCoord2f(0.0f, 0.0f);		glVertex2f(-280, 50);
	glTexCoord2f(0.05f, 0.05f);	    glVertex2f(-470, 50);
	glTexCoord2f(0.1f, 0.1f);	    glVertex2f(-470, 170);
	glTexCoord2f(0.15f, 0.15f);		glVertex2f(-370, 220);
	glTexCoord2f(0.2f, 0.2f);		glVertex2f(-280, 220);
	glTexCoord2f(0.25f, 0.25f);		glVertex2f(-280, 170);
	glTexCoord2f(0.3f, 0.3f);		glVertex2f(-340, 170);
	glTexCoord2f(0.4f, 0.4f);		glVertex2f(-440, 140);
	glTexCoord2f(0.45f, 0.45f);	    glVertex2f(-440, 80);
	glTexCoord2f(0.5f, 0.5f);	    glVertex2f(-310, 80);
	glTexCoord2f(0.6f, 0.6f);		glVertex2f(-310, 110);
	glTexCoord2f(0.67f, 0.67f);		glVertex2f(-350, 110);
	glTexCoord2f(0.7f, 0.7f);		glVertex2f(-350, 140);
	glTexCoord2f(0.75f, 0.75f);		glVertex2f(-280, 140);
	glTexCoord2f(0.8f, 0.8f);		glVertex2f(-280, 50);
	glEnd();
	glBegin(GL_LINE_STRIP);//a
	glTexCoord2f(0.0f, 0.0f);		glVertex2f(-220, 50);
	glTexCoord2f(0.05f, 0.05f);	    glVertex2f(-125, 220);
	glTexCoord2f(0.1f, 0.1f);	    glVertex2f(-30, 50);
	glTexCoord2f(0.15f, 0.15f);		glVertex2f(-70, 50);
	glTexCoord2f(0.2f, 0.2f);		glVertex2f(-110, 125);
	glTexCoord2f(0.25f, 0.25f);		glVertex2f(-140, 125);
	glTexCoord2f(0.3f, 0.3f);		glVertex2f(-180, 50);
	glTexCoord2f(0.4f, 0.4f);		glVertex2f(-220, 50);
	glEnd();
	glBegin(GL_LINE_STRIP);//m
	glTexCoord2f(0.0f, 0.0f);		glVertex2f(30, 50);
	glTexCoord2f(0.05f, 0.05f);	    glVertex2f(30, 220);
	glTexCoord2f(0.1f, 0.1f);	    glVertex2f(60, 220);
	glTexCoord2f(0.15f, 0.15f);		glVertex2f(125, 175);
	glTexCoord2f(0.2f, 0.2f);		glVertex2f(190, 220);
	glTexCoord2f(0.25f, 0.25f);		glVertex2f(220, 220);
	glTexCoord2f(0.3f, 0.3f);		glVertex2f(220, 50);
	glTexCoord2f(0.4f, 0.4f);		glVertex2f(190, 50);
	glTexCoord2f(0.45f, 0.45f);	    glVertex2f(190, 185);
	glTexCoord2f(0.5f, 0.5f);	    glVertex2f(125, 125);
	glTexCoord2f(0.6f, 0.6f);		glVertex2f(60, 185);
	glTexCoord2f(0.67f, 0.67f);		glVertex2f(60, 50);
	glTexCoord2f(0.7f, 0.7f);		glVertex2f(30, 50);
	glEnd();
	glBegin(GL_LINE_STRIP);//e
	glTexCoord2f(0.0f, 0.0f);		glVertex2f(280, 50);
	glTexCoord2f(0.05f, 0.05f);	    glVertex2f(280, 220);
	glTexCoord2f(0.1f, 0.1f);	    glVertex2f(470, 220);
	glTexCoord2f(0.15f, 0.15f);		glVertex2f(470, 185);
	glTexCoord2f(0.2f, 0.2f);		glVertex2f(310, 185);
	glTexCoord2f(0.25f, 0.25f);		glVertex2f(310, 140);
	glTexCoord2f(0.3f, 0.3f);		glVertex2f(470, 140);
	glTexCoord2f(0.4f, 0.4f);		glVertex2f(470, 110);
	glTexCoord2f(0.45f, 0.45f);	    glVertex2f(310, 110);
	glTexCoord2f(0.5f, 0.5f);	    glVertex2f(310, 85);
	glTexCoord2f(0.6f, 0.6f);		glVertex2f(470, 85);
	glTexCoord2f(0.67f, 0.67f);		glVertex2f(470, 50);
	glTexCoord2f(0.7f, 0.7f);		glVertex2f(280, 50);
	glEnd();
	glBegin(GL_LINE_STRIP);//c
	glTexCoord2f(0.0f, 0.0f);		glVertex2f(-405, -50);
	glTexCoord2f(0.05f, 0.05f);	    glVertex2f(-405, -80);
	glTexCoord2f(0.1f, 0.1f);	    glVertex2f(-430, -80);
	glTexCoord2f(0.15f, 0.15f);		glVertex2f(-445, -110);
	glTexCoord2f(0.2f, 0.2f);		glVertex2f(-445, -140);
	glTexCoord2f(0.25f, 0.25f);		glVertex2f(-430, -170);
	glTexCoord2f(0.3f, 0.3f);		glVertex2f(-405, -170);
	glTexCoord2f(0.4f, 0.4f);		glVertex2f(-405, -200);
	glTexCoord2f(0.45f, 0.45f);	    glVertex2f(-440, -200);
	glTexCoord2f(0.5f, 0.5f);	    glVertex2f(-475, -175);
	glTexCoord2f(0.6f, 0.6f);		glVertex2f(-475, -95);
	glTexCoord2f(0.67f, 0.67f);		glVertex2f(-440, -50);
	glTexCoord2f(0.7f, 0.7f);		glVertex2f(-405, -50);
	glEnd();
	glBegin(GL_LINE_STRIP);//l
	glTexCoord2f(0.0f, 0.0f);		glVertex2f(-350, -50);
	glTexCoord2f(0.05f, 0.05f);	    glVertex2f(-315, -50);
	glTexCoord2f(0.1f, 0.1f);	    glVertex2f(-315, -160);
	glTexCoord2f(0.15f, 0.15f);		glVertex2f(-275, -160);
	glTexCoord2f(0.2f, 0.2f);		glVertex2f(-275, -200);
	glTexCoord2f(0.25f, 0.25f);		glVertex2f(-350, -200);
	glTexCoord2f(0.3f, 0.3f);		glVertex2f(-350, -50);
	glEnd();
	glBegin(GL_LINE_STRIP);//e
	glTexCoord2f(0.0f, 0.0f);		glVertex2f(-220, -200);
	glTexCoord2f(0.05f, 0.05f);	    glVertex2f(-220, -30);
	glTexCoord2f(0.1f, 0.1f);	    glVertex2f(-30, -30);
	glTexCoord2f(0.15f, 0.15f);		glVertex2f(-30, -65);
	glTexCoord2f(0.2f, 0.2f);		glVertex2f(-190, -65);
	glTexCoord2f(0.25f, 0.25f);		glVertex2f(-190, -110);
	glTexCoord2f(0.3f, 0.3f);		glVertex2f(-30, -110);
	glTexCoord2f(0.4f, 0.4f);		glVertex2f(-30, -140);
	glTexCoord2f(0.45f, 0.45f);	    glVertex2f(-190, -140);
	glTexCoord2f(0.5f, 0.5f);	    glVertex2f(-190, -165);
	glTexCoord2f(0.6f, 0.6f);		glVertex2f(-30, -165);
	glTexCoord2f(0.67f, 0.67f);		glVertex2f(-30, -200);
	glTexCoord2f(0.7f, 0.7f);		glVertex2f(-220, -200);
	glEnd();
	glBegin(GL_LINE_STRIP);//a
	glTexCoord2f(0.0f, 0.0f);		glVertex2f(30, -200);
	glTexCoord2f(0.05f, 0.05f);	    glVertex2f(125, -30);
	glTexCoord2f(0.1f, 0.1f);	    glVertex2f(220, -200);
	glTexCoord2f(0.15f, 0.15f);		glVertex2f(180, -200);
	glTexCoord2f(0.2f, 0.2f);		glVertex2f(140, -125);
	glTexCoord2f(0.25f, 0.25f);		glVertex2f(110, -125);
	glTexCoord2f(0.3f, 0.3f);		glVertex2f(70, -200);
	glTexCoord2f(0.4f, 0.4f);		glVertex2f(30, -200);
	glEnd();
	glBegin(GL_LINE_STRIP);//r
	glTexCoord2f(0.0f, 0.0f);		glVertex2f(280, -220);
	glTexCoord2f(0.05f, 0.05f);	    glVertex2f(280, -90);
	glTexCoord2f(0.1f, 0.1f);	    glVertex2f(330, -30);
	glTexCoord2f(0.15f, 0.15f);		glVertex2f(420, -30);
	glTexCoord2f(0.2f, 0.2f);		glVertex2f(470, -90);
	glTexCoord2f(0.25f, 0.25f);		glVertex2f(470, -125);
	glTexCoord2f(0.3f, 0.3f);		glVertex2f(370, -125);
	glTexCoord2f(0.4f, 0.4f);		glVertex2f(470, -220);
	glTexCoord2f(0.45f, 0.45f);	    glVertex2f(440, -220);
	glTexCoord2f(0.5f, 0.5f);	    glVertex2f(340, -140);
	glTexCoord2f(0.6f, 0.6f);		glVertex2f(340, -110);
	glTexCoord2f(0.67f, 0.67f);		glVertex2f(440, -110);
	glTexCoord2f(0.7f, 0.7f);		glVertex2f(440, -95);
	glTexCoord2f(0.8f, 0.8f);		glVertex2f(405, -75);
	glTexCoord2f(0.85f, 0.85f);	    glVertex2f(345, -75);
	glTexCoord2f(0.9f, 0.9f);	    glVertex2f(310, -105);
	glTexCoord2f(0.92f, 0.92f);	    glVertex2f(310, -220);
	glTexCoord2f(0.94f, 0.94f);	    glVertex2f(280, -220);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	if (present_stage != 30) {    // 30 : stage 3 (final) clear
		displayCharacters(GLUT_BITMAP_TIMES_ROMAN_24, "Press Left Mouth Button To Enter The Next Stage", -boundary_x * 0.55f, boundary_y * 0.55f);
	}
	displayCharacters(GLUT_BITMAP_TIMES_ROMAN_24, "Press 'q' Button To Go To Start Screen", -boundary_x * 0.55f, -boundary_y * 0.55f);

	// glutSwapBuffers();
}