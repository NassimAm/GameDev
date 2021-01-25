// CSCE A211
// Graphics Framework by Matthew Devins
// This code demonstrates how to load a png image,
// display, and process it using the lodepng library
// and a wrapper pngImage class.

#include "gl/glut.h"
#include "gl/gl.h"
#include "gl/glu.h"

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <vector>
#include "pngImage.h"

using namespace std;

void init();
void display();


void *font = GLUT_BITMAP_TIMES_ROMAN_24;//GLUT_STROKE_ROMAN;
const int WIDTH = 768;
const int HEIGHT = 576;

static int screenx = 0;
static int screeny = 0;


PngImage image;  


int main(int argc, char** argv)
{
	srand(time(NULL)); 
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Image processing demo");

	init();

	glutDisplayFunc(display);

	glutMainLoop();

	return 0;
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(screenx, screenx + WIDTH, screeny + HEIGHT, screeny);
	
	image.loadImage("BoysSanddune.png");
}

/* For this lab you only need to work in this display function */
void display()
{
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	for (int j = 0; j < image.getHeight(); j++)
		for (int i = 0; i < image.getWidth(); i++)		
		{
			int r, g, b;
			image.getRGB(i, j, r, g, b);
			if ((i>136) && (i < 215) && (j > 366) && (j<492))
			{
				if ((g - 30 > r) && (g - 30 > b))
				{
					g = g / 3;
					r = r * 3;
				}
			}
			glColor3f((float)r / 255, (float)g / 255, (float)b / 255);						
			glVertex2f(i, j);
		}
	glEnd();
	
	glutSwapBuffers();
	glFlush();

	return;
}

