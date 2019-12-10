
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#include "../CSCIx229.h"
#include "../headers/basic_shapes.h"
#include "../headers/buildings.h"

/**************************drawSwastika()*******************************************************
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
/*********************************************************************************************/
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

/*****************************drawBuilding()************************************************************************
*@func: 		drawBuilding()
*
*@description:		A function that draws the building
*
*@param:		double x, double y, double z, double delta_x, double delta_y, double delta_z, int textures[]
*
*@return:		void
/******************************************************************************************************************/
void drawBuilding(double x, double y, double z, double delta_x, double delta_y, double delta_z, int textures[])
{
	glPushMatrix();
        //  Offset
        glTranslated(x,y,z);
        glScaled(delta_x,delta_y,delta_z);
	glColor3ub(158, 158, 158);
        drawDome(0,0,7,4,4,4,90, textures);
	drawSwastika(0,0,12.4,0.20,0.20,0.20);
	drawCube(0,0,0,9,5,7.3,0);

	//Towers at all four corners
	drawCube(+18,+10,0,9,5,7.3,0);
	drawCube(-18,+10,0,9,5,7.3,0);
	drawCube(+18,-10,0,9,5,7.3,0);
	drawCube(-18,-10,0,9,5,7.3,0);
	glPopMatrix();

}

/***********************************drawBarbedwire()**************************************************************************************************************************************
*@func:		drawBarbedwire
*
*@description:	Draws a barbded wire on the wall
*
*@params:	double radius, double height, double x1, double y1 ,double z1, double delta_x, double delta_y, double delta_z, double th, GLubyte R, GLubyte G,GLubyte B, double alpha
*
*return:	void
*
*******************************************************************************************************************************************************************************************/

void drawBarbedwire(double radius, double height, double x1, double y1 ,double z1, double delta_x, double delta_y, double delta_z, double th, GLubyte R, GLubyte G,GLubyte B, double alpha )
{

	glPushMatrix();

	drawCycloid(radius,  height, x1,  y1, z1,delta_x,delta_y,delta_z,th,255,255,255,alpha);

	glPopMatrix();

}

/**************************************************drawNewBuilding**********************************************
*@func:		drawNewBuilding
*
*@definition:	draws a building in the centre of the scene. The building has a Swastika on top
*
*@params:	double x, double y, double z, double delta_x, double delta_y, double delta_z
*
*@return:	void
****************************************************************************************************************/

void drawNewBuilding(double x, double y, double z, double delta_x, double delta_y, double delta_z, int texture[])
{

	glPushMatrix();
        //  Offset
        glTranslated(x,y,z);
        glScaled(delta_x,delta_y,delta_z);
        glColor3ub(158, 158, 158);
        drawDome(0,0,140,120,120,120,90, texture);
        drawSwastika(0,0,290,5,5,5);



	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//        glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE ,GL_MODULATE);
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

/**************************************drawNewWall()**************************************************
*@func:		drawNewWall
*
*@description:	Draws a wall around the periphery of the building
*
*@params:	int texture[]
*
*@return:	void
*****************************************************************************************************/

void drawNewWall(int texture[])
{
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D,texture[0]);
//        glColor3ub(255,165,0);
	glColor4f(1,0.6470588235294118 ,0,1.0);//silver
	/* Drawing the left inner wall */
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);
	glTexCoord2f(0,1000);glVertex3f(-1000,-1000,40);
        glTexCoord2f(0,0);glVertex3f(-1000,-1000,0);
        glTexCoord2f(2000,0);glVertex3f(-1000,1000,0);
	glTexCoord2f(2000,1000); glVertex3f(-1000,1000,40);
	glEnd();
	/*
	Now drawing the barbed wire on the left inner Wall
	*/

//        drawBarbedwire(5, 2000, -1015, -1000 ,45, 1, 1, 1, -90, 200, 200 ,200, 1 );

	/* Drawing the right inner wall */
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
        glTexCoord2f(0,1000);glVertex3f(1000,1000,40);
        glTexCoord2f(0,0);glVertex3f(1000,1000,0);
        glTexCoord2f(2000,0);glVertex3f(1000,-1000,0);
        glTexCoord2f(2000,1000);glVertex3f(1000,-1000,40);
	glEnd();


	/* Drawing the front inner wall */
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
        glTexCoord2f(0,1000);glVertex3f(-1000,1000,40);
        glTexCoord2f(0,0);glVertex3f(-1000,1000,0);
        glTexCoord2f(2000,0);glVertex3f(1000,1000,0);
        glTexCoord2f(2000,1000);glVertex3f(1000,1000,40);
	glEnd();


	/* Drawing the inner wall at the back */
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
        glTexCoord2f(0,1000);glVertex3f(1000,-1000,40);
        glTexCoord2f(0,0);glVertex3f(1000,-1000,0);
        glTexCoord2f(2000,0);glVertex3f(-1000,-1000,0);
        glTexCoord2f(2000,1000);glVertex3f(-1000,-1000,40);
	glEnd();


	 glColor3ub(0,255,0);
	/* Drawing the left outer wall */
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0,1000);glVertex3f(-1010,1010,40);
	glTexCoord2f(0,0);glVertex3f(-1010,1010,0);
	glTexCoord2f(2000,0);glVertex3f(-1010,-1010,0);
	glTexCoord2f(2000,1000);glVertex3f(-1010,-1010,40);
	glEnd();



        /* Drawing the right outer wall */
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);
	glTexCoord2f(0,1000);glVertex3f(1010,-1010,40);
        glTexCoord2f(0,0);glVertex3f(1010,-1010,0);
        glTexCoord2f(2000,0);glVertex3f(1010,1010,0);
	glTexCoord2f(2000,1000);glVertex3f(1010,1010,40);
	glEnd();

        /* Drawing the front outer wall */
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
        glVertex3f(1010,1010,0);
        glVertex3f(1010,1010,40);
	glVertex3f(-1010,1010,0);
	glVertex3f(-1010,1010,40);

	glEnd();

        /* Drawing the outer wall at the back */
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
        glVertex3f(1010,-1010,40);
        glVertex3f(1010,-1010,0);
        glVertex3f(-1010,-1010,0);
        glVertex3f(-1010,-1010,40);
	glEnd();

	glColor3ub(0,0,255);


	 /* Drawing the top surface of the wall left */
        glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
        glVertex3f(-1000,1000,40);
        glVertex3f(-1010,1010,40);
        glVertex3f(-1010,-1010,40);
        glVertex3f(-1000,-1000,40);
        glEnd();

	/* Drawing the top surface of the wall right */
        glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glVertex3f(1000,1000,40);
        glVertex3f(1010,1010,40);
        glVertex3f(1010,-1010,40);
        glVertex3f(1000,-1000,40);

        glEnd();

	/* Drawing the top surface of the wall front */
        glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
        glVertex3f(-1010,1010,40);
        glVertex3f(-1000,1000,40);
        glVertex3f(1000,1000,40);
        glVertex3f(1010,1010,40);
        glEnd();

	/* Drawing the top surface of the wall back */
        glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
        glVertex3f(-1000,-1000,40);
        glVertex3f(-1010,-1010,40);
        glVertex3f(1010,-1010,40);
        glVertex3f(1000,-1000,40);
        glEnd();


	drawBarbedwire(5, 2000, -1005, -1000 ,45, 1, 1, 1, -90, 200, 200 ,200, 0 );
	drawBarbedwire(5, 2000, 1005, -1000 ,45, 1, 1, 1, -90, 200, 200 ,200, 0 );
	drawBarbedwire(5, 2000, -1005, -1000 ,45, 1, 1, 1, 0, 200, 200 ,200, 90 );
	drawBarbedwire(5, 2000, -1005, 1000 ,45, 1, 1, 1, 0, 200, 200 ,200, 90 );
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

}

/******************************************drawCrack()**********************************************************
*@func: 	drawCrack
*
*@description:	The function draws the crack in the building
*
*@params: 	double x, double y, double z, int texture[]
*
*@return:	void
*
****************************************************************************************************************/

void drawCrack(double x, double y, double z,double delta_x, double delta_y, double delta_z,int th, int texture[])
{

	int alpha = 40;// Transaprency

	glPushMatrix();
	glTranslated(x,y,z);
	glScaled(delta_x, delta_y,delta_z);
	glRotated(th,0,0,1);

	glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,modf?GL_REPLACE:GL_MODULATE);
	glColor4f(1,1,1,0.01*alpha);
	glBindTexture(GL_TEXTURE_2D,texture[15]);
	glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE);

	glBegin(GL_QUADS);
	glNormal3f(0,-1,0);
	glTexCoord2f(0,1);glVertex3f(-1,0,1);
	glTexCoord2f(0,0);glVertex3f(-1,0,0);
	glTexCoord2f(0,1);glVertex3f(1,0,0);
	glTexCoord2f(1,1);glVertex3f(1,0,1);
	glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);

}


/**********************************************drawFlag()*******************************************************
*@func:		drawFlag
*
*@description:	A function that draws the flag. Can be used for the Nazi flag as well as the USSR one
*
*@prams:	double delta_x, double delta_y, double delta_z, int textures[]
*
*@return:	void
****************************************************************************************************************/


void drawFlag(double x, double y, double z, double delta_x, double delta_y, double delta_z,int th, int textures[])
{

	int mode = 1;
	glPushMatrix();
	glTranslated(x, y,z);
	glScaled(delta_x, delta_y,delta_z);
	glRotated(th,0,0,1);
	glEnable(GL_TEXTURE_2D);
	float borderColor[] = { 1.0f, 0.0f, 0.0f, 0.0f };
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);  
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D,textures[17]);
	glBegin(GL_QUADS);
	glColor3ub(255,0,0);
	glTexCoord2f(0,0);glVertex3f(+1.0,0,-1.0);
	glTexCoord2f(1,0);glVertex3f(-1.0,0,-1.0);
	glTexCoord2f(1,1);glVertex3f(-1.0,0,+1.0);
	glTexCoord2f(0,1);glVertex3f(+1.0,0,+1.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}


/**********************************************drawSnowfall***************************************************
*@func:         drawSnowfall
*
*@description:  A function that draws the flag. Can be used for the Nazi flag as well as the USSR one
*
*@prams:        double delta_x, double delta_y, double delta_z, int textures[]
*
*@return:       void
*
*@reference:	https://github.com/akarthik10/opengl-samples/blob/master/examples/asteroids/asteroids.cpp
*************************************************************************************************************/

void drawSnowfall(double x, double y, double z)
{
	glPushMatrix();
	int i;
	glDisable(GL_LIGHTING);

//	glTranslatef(0,0,500);
	glTranslated(x,y,z);
		glColor3f(1,1,1);
		glBegin(GL_POINTS);
		for(i=0;i<1000;i++)
		{

			glVertex3f(rand()%600,rand()%600,rand()%600);
			glVertex3f(-rand()%600,rand()%600,rand()%600);
			glVertex3f(-rand()%600,-rand()%600,rand()%600);
			glVertex3f(rand()%600,-rand()%600,rand()%600);
			glVertex3f(rand()%600,rand()%600,-rand()%600);
			glVertex3f(-rand()%600,rand()%600,-rand()%600);
			glVertex3f(-rand()%600,-rand()%600,-rand()%600);
			glVertex3f(rand()%600,-rand()%600,-rand()%600);



		}
		glEnd();


	glPopMatrix();
	glEnable(GL_LIGHTING);



}






