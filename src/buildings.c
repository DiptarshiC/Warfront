
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#include "../CSCIx229.h"
#include "../headers/basic_shapes.h"
#include "../headers/buildings.h"

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

void drawBuilding(double x, double y, double z, double delta_x, double delta_y, double delta_z, int textures[])
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

void drawNewBuilding(double x, double y, double z, double delta_x, double delta_y, double delta_z, int texture[])
{

	glPushMatrix();
        //  Offset
        glTranslated(x,y,z);
        glScaled(delta_x,delta_y,delta_z);
        glColor3ub(158, 158, 158);
        drawDome(0,0,140,120,120,120,90);
        drawSwastika(0,0,290,5,5,5);



	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE ,GL_MODULATE);
        glBindTexture(GL_TEXTURE_2D,texture[14]);
	glColor3ub(255,165,0);
	/* Drawing the new building*/

	/* 1. Drawing the front face*/
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	glTexCoord2f(-150.0,150.0); glVertex3f(-150,-200, 150);
	glTexCoord2f(-150.0,148.0); glVertex3f(-150,-200, 0);
	glTexCoord2f(-148.0,148.0); glVertex3f(150,-200, 0);
	glTexCoord2f(-148.0,150.0); glVertex3f(150,-200, 150);
	glEnd();

	/* 2. Drawing the back face*/
        glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
        glTexCoord2f(150.0,150.0); glVertex3f(150,200, 150);
        glTexCoord2f(150.0,148.0);  glVertex3f(150,200,0);
        glTexCoord2f(148.0,148.0);  glVertex3f(-150,200, 0);
        glTexCoord2f(148.0,150.0);  glVertex3f(-150,200, 150);
        glEnd();

	/* 3. Drawing the right face*/

        glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);
        glTexCoord2f(150.0,150.0); glVertex3f(150,-200, 150);
        glTexCoord2f(150.0,148.0); glVertex3f(150,-200,0);
        glTexCoord2f(148.0,148.0); glVertex3f(150,200, 0);
        glTexCoord2f(148.0,150.0); glVertex3f(150,200, 150);
        glEnd();

	/* 4. Drawing the left face*/
        glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
        glTexCoord2f(-150.0,150.0); glVertex3f(-150,200, 150);
	glTexCoord2f(-150.0,148.0); glVertex3f(-150,200, 0);
	glTexCoord2f(-148.0,148.0); glVertex3f(-150,-200,0);
	glTexCoord2f(-148.0,150.0); glVertex3f(-150,-200, 150);
	glEnd();

	/* 5. Drawing the top face*/
        glBegin(GL_QUADS);
	glNormal3f(0,0, 1);
        /*glTexCoord2f(0.0,0.0);*/ glVertex3f(-150,200, 150);
        /*glTexCoord2f(0.0,0.0);*/ glVertex3f(-150,-200, 150);
        /*glTexCoord2f(0.0,0.0);*/ glVertex3f(150,-200,150);
        /*glTexCoord2f(0.0,0.0);*/ glVertex3f(150,200, 150);
        glEnd();

	/* 6. Drawing the bottom face*/
        glBegin(GL_QUADS);
	glNormal3f(0,0, -1);
        /*glTexCoord2f(0.0,0.0)*/; glVertex3f(150,200, 0);
	/*glTexCoord2f(0.0,0.0);*/ glVertex3f(150,-200,0);
	/*glTexCoord2f(0.0,0.0);*/ glVertex3f(-150,-200,0);
 	/*glTexCoord2f(0.0,0.0);*/ glVertex3f(-150,200,0);

        glEnd();
        glPopMatrix();
}
