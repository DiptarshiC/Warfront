
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#include "../CSCIx229.h"
#include "../headers/basic_shapes.h"
#include "../headers/buildings.h"

	unsigned int texture[14];
/*	texture[0] = LoadTexBMP("../textures/brick.bmp");
	texture[1] = LoadTexBMP("../textures/pattern.bmp");
        texture[2] = LoadTexBMP("../textures/sky.bmp");
        texture[3] = LoadTexBMP("../textures/smoke.bmp");
        texture[4] = LoadTexBMP("../textures/squares.bmp");
        texture[5] = LoadTexBMP("../textures/stars.bmp");
        texture[6] = LoadTexBMP("../textures/water.bmp");
        texture[7] = LoadTexBMP("../textures/wood.bmp");
        texture[8] = LoadTexBMP("../textures/copper.bmp");
        texture[9] = LoadTexBMP("../textures/rusted.bmp");
        texture[10]=LoadTexBMP("../textures/ship.bmp");
        texture[11]=LoadTexBMP("../textures/galvanized.bmp");
        texture[12]=LoadTexBMP("../textures/plane.bmp");
        texture[13]=LoadTexBMP("../textures/plane_small.bmp");

*/

/**************************drawSwastika()****************************************************
*@func:		drawSwastika
*
*@description:	
*
*@params:	double x, double y, double z, double delta_x, double delta_y, double delta_z
*
*@return:	void
*
*
*/

void drawSwastika(double x, double y, double z, double delta_x, double delta_y, double delta_z)
{

	glPushMatrix();
        //  Offset
        glTranslated(x,y,z);
        glScaled(delta_x,delta_y,delta_z);
	drawCube(0,0,0,1,1,7,0);
	drawCube(+4,0,+6,3,1,1,0);
        drawCube(-4,0,-6,3,1,1,0);
	drawCube(+4,0,0,3,1,1,0);
        drawCube(-4,0,0,3,1,1,0);
	drawCube(+6,0,-4,1,1,3,0);
	drawCube(-6,0,+4,1,1,3,0);

	glPopMatrix();

}

/*****************************drawBuilding()********************************
*@func: drawBuilding()
*
*@description:
*
*@param:
*
*@return:
*
*
*/

void drawBuilding(double x, double y, double z, double delta_x, double delta_y, double delta_z)
{
	glPushMatrix();
        //  Offset
        glTranslated(x,y,z);
        glScaled(delta_x,delta_y,delta_z);
	glColor3ub(158, 158, 158);
        drawDome(0,0,7,4,4,4,90);
	drawSwastika(0,0,12.4,0.20,0.20,0.20);
	drawCube(0,0,0,9,5,7.3,0);

	//Towers at all four corners
	drawCube(+18,+10,0,9,5,7.3,0);
	drawCube(-18,+10,0,9,5,7.3,0);
	drawCube(+18,-10,0,9,5,7.3,0);
	drawCube(-18,-10,0,9,5,7.3,0);
	glPopMatrix();

}

/**
*
*
*
*
*
*
*/

void drawBarbedwire(double radius, double height, double x1, double y1 ,double z1, double delta_x, double delta_y, double delta_z, double th, GLubyte R, GLubyte G,GLubyte B, double alpha )
{

	glPushMatrix();

	drawCycloid(radius,  height, x1,  y1, z1,delta_x,delta_y,delta_z,th,255,255,255,alpha);

	glPopMatrix();

}

/**
*@func:		drawNewBuilding
*
*@definition:	
*
*@params:	double x, double y, double z, double delta_x, double delta_y, double delta_z
*
*@return:	void
*
*
*/

void drawNewBuilding(double x, double y, double z, double delta_x, double delta_y, double delta_z)
{

	glPushMatrix();
        //  Offset
        glTranslated(x,y,z);
        glScaled(delta_x,delta_y,delta_z);
        glColor3ub(158, 158, 158);
        drawDome(0,0,30,4,4,4,90);
        drawSwastika(0,0,12.4,0.20,0.20,0.20);


	/* Drawing the new building*/

	/* 1. Drawing the front face*/
	glBegin(GL_QUADS);
	glVertex3f(-36,-20, 30);
	glVertex3f(-36,-20, 0);
	glVertex3f(36,-20, 0);
	glVertex3f(36,-20, 30);
	glEnd();

	/* 2. Drawing the back face*/
        glBegin(GL_QUADS);
        glVertex3f(36,20, 30);
        glVertex3f(-36,20,30);
        glVertex3f(-36,20, 0);
        glVertex3f(36,20, 30);
        glEnd();

	/* 3. Drawing the right face*/

        glBegin(GL_QUADS);
        glVertex3f(36,-20, 30);
        glVertex3f(36,-20,0);
        glVertex3f(36,20, 0);
        glVertex3f(36,20, 30);
        glEnd();

	/* 4. Drawing the left face*/
        glBegin(GL_QUADS);
        glVertex3f(-36,20, 30);
	glVertex3f(-36,20, 0);
	glVertex3f(-36,-20,0);
	glVertex3f(-36,-20, 30);
	glEnd();
	/* 5. Drawing the top face*/
        glBegin(GL_QUADS);
        glVertex3f(-36,20, 30);
        glVertex3f(-36,-20, 30);
        glVertex3f(36,-20,30);
        glVertex3f(36,20, 30);
        glEnd();

	/* 6. Drawing the bottom face*/
        glBegin(GL_QUADS);
        glVertex3f(36,20, 0);
	glVertex3f(36,-20,0);
	glVertex3f(-36,-20,0);
 	glVertex3f(-36,20,0);

        glEnd();
        glPopMatrix();
}
