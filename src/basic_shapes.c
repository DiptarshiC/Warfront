
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#include "../headers/basic_shapes.h"
#include "../headers/vehicles.h"


#define		PI	3.14


/**
*@func:         Vertex
*
*@description:  A program that helps us conmpute the vertices using cosine sine functions that inturn helps us render shapes
*
*@param:        double theta,double alpha
*
*@return:       void
*
*/

void Vertex(double theta,double alpha)
{
   	//glColor3f(cos(PI/180*(theta))*cos(PI/180*(theta)) ,sin(PI/180*(alpha))*sin(PI/180*(alpha)) ,sin(PI/180*(theta))*sin(PI/180*(theta)));
	glNormal3d(sin(PI/180*(theta))*cos(PI/180*(alpha)) ,sin(PI/180*(alpha)) ,cos(PI/180*(theta))*cos(PI/180*(alpha)));
   	glVertex3d(sin(PI/180*(theta))*cos(PI/180*(alpha)) , sin(PI/180*(alpha)) , cos(PI/180*(theta))*cos(PI/180*(alpha)));
}



/************************** draw_cylinder() **************************
 * This function will draw the cylinder
 *
 *   @parameter1: radius = The radius of cylinder
 *   @parameter2: height = Height of the cylinder
 *   @parameter3: R = Red value of the cylinder's color
 *   @parameter4: G = Green value of the cylinder's color
 *   @parameter5: B = Blue value of the cylinder's color
 *
 *   @return: Nothing
 */

void drawCylinder(double radius,double height,double x1, double y1, double z1,double delta_x,double delta_y,double delta_z,double th,GLubyte R,GLubyte G,GLubyte B,double alpha)
{
	glPushMatrix();
	glTranslated(x1,y1,z1);
        glRotated(th,1,0,0);
	glRotated(alpha,0,1,0);
        glScaled(delta_x,delta_y,delta_z);


	GLfloat x              = 0.0;
    	GLfloat y              = 0.0;
    	GLfloat angle          = 0.0;
    	GLfloat angle_stepsize = 0.1;

    	/** Draw the tube */
    	glColor3ub(R-40,G-40,B-40);
    	glBegin(GL_QUAD_STRIP);
    	angle = 0.0;
        while( angle < 2*PI ) 
	{
            	x = radius * cos(angle);
            	y = radius * sin(angle);
            	glVertex3f(x, y , height);
            	glVertex3f(x, y , 0.0);
            	angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
        glVertex3f(radius, 0.0, 0.0);
    	glEnd();

    	/** Draw the circle on top of cylinder */
/*    	glColor3ub(R,G,B);
    	glBegin(GL_POLYGON);
    	angle = 0.0;
        while( angle < 2*PI ) 
	{
        	x = radius * cos(angle);
        	y = radius * sin(angle);
        	glVertex3f(x, y , height);
        	angle = angle + angle_stepsize;
        }
        	glVertex3f(radius, 0.0, height);
    	glEnd();*/
	glPopMatrix();
}


/******************************drawCone()********************************
*@func: drawDome
*
*@description:
*
*@param: 
*
*@return: 
*
*
*/

void drawDome(double x, double y, double z, double delta_x, double delta_y, double delta_z,double th)
{
        const int d = 5;
        int theta, alpha;

        //  Save transformation

        glPushMatrix();
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
        //  Offset and scale
        glTranslated(x, y, z);
        glScaled(delta_x, delta_y, delta_z);
	glRotated(th,1,0,0);


        //  South pole cap
/*        glBegin(GL_TRIANGLE_FAN);

        Vertex(0, -90);
        for (theta = 0; theta <= 360; theta += d)
        {
                Vertex(theta, d - 90);
        }
        glEnd();*/

        //  Latitude bands
        for (alpha = d ; alpha <= 90 - (2*d); alpha += d)
        {
                glBegin(GL_QUAD_STRIP);
		glColor3ub(158, 158, 158);
                for (theta = 0; theta <= 360; theta += d)
                {
                        Vertex(theta, alpha);
                        Vertex(theta, alpha + d);
                }
                glEnd();
        }


        //  North pole cap
        glBegin(GL_TRIANGLE_FAN);

        Vertex(0, 90);
        for (theta = 0; theta <= 360; theta += d)
        {
                Vertex(theta, 90 - d);
        }
        glEnd();
//	glDisable(GL_BLEND);

        //  Undo transformations
        glPopMatrix();
}

/**
*
*
*
*
*
*
*
*
*
*/

void drawSphere(double x, double y, double z, double delta_x, double delta_y, double delta_z)
{
        const int d = 5;
        int theta, alpha;

        //  Save transformation

        glPushMatrix();
        //  Offset and scale
        glTranslated(x, y, z);
        glScaled(delta_x, delta_y, delta_z);

        //  South pole cap
        glBegin(GL_TRIANGLE_FAN);

        Vertex(0, -90);
        for (theta = 0; theta <= 360; theta += d)
        {
                Vertex(theta, d - 90);
        }
        glEnd();

        //  Latitude bands
        for (alpha = d - 90; alpha <= 90 - (2*d); alpha += d)
        {
                glBegin(GL_QUAD_STRIP);
                for (theta = 0; theta <= 360; theta += d)
                {
                        Vertex(theta, alpha);
                        Vertex(theta, alpha + d);
                }
                glEnd();
        }

        //  North pole cap
        glBegin(GL_TRIANGLE_FAN);
        Vertex(0, 90);
        for (theta = 0; theta <= 360; theta += d)
        {
                Vertex(theta, 90 - d);
        }
        glEnd();

        //  Undo transformations
        glPopMatrix();
}

/**
*@func:		drawCube
*
*@description:
*
*@param:        double x,double y,double z,double dx,double dy,double dz, double th
*
*@return:       void
*
*@reference:    http://www.prinmath.com/csci5229/F18/programs/ex9.zip
*/

void drawCube(double x,double y,double z,double delta_x,double delta_y,double delta_z, double th)
{

//      glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, Shine);
//      glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, colorwhite);
//      glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, colorblack);
        //  Save transformation
        glPushMatrix();
        //  Offset
        glTranslated(x,y,z);
        glRotated(th,0,1,0);
        glScaled(delta_x,delta_y,delta_z);
        //  Cube

        glBegin(GL_QUADS);
        //  Front
        glNormal3f(0, 0, +1);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-1,-1, 1);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(+1,-1, 1);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(+1,+1, 1);
        glTexCoord2f(0.0, 1.0);  
        glVertex3f(-1,+1, 1);
        glEnd();
        glBegin(GL_QUADS);
        //  Back
        glNormal3f(0, 0, -1);
        glTexCoord2f(1.0, 0.0); 
        glVertex3f(+1,-1,-1);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-1,-1,-1);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-1,+1,-1);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(+1,+1,-1);
        glEnd();
        glBegin(GL_QUADS);
        //  Right
        glNormal3f(+1, 0, 0);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(+1,-1,+1);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(+1,-1,-1);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(+1,+1,-1);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(+1,+1,+1);
        glEnd();
        //  Left
        glBegin(GL_QUADS);
        glNormal3f(-1, 0, 0);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-1,-1,-1);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-1,-1,+1);
        glTexCoord2f(1.0, 1.0);  
        glVertex3f(-1,+1,+1);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(-1,+1,-1);
        glEnd();
        //  Top
        glBegin(GL_QUADS);
        glNormal3f( 0,+1, 0);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-1,+1,+1);
        glTexCoord2f(1.0, 1.0); 
        glVertex3f(+1,+1,+1);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(+1,+1,-1);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-1,+1,-1);
        glEnd();
        //  Bottom
        glBegin(GL_QUADS);
        glNormal3f(0, -1, 0);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-1,-1,-1);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(+1,-1,-1);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(+1,-1,+1);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-1,-1,+1);
        //  End
        glEnd();
        //  Undo transofrmations
        glPopMatrix();
}


/**
*@func:         drawCube
*
*@description:
*
*@param:        double x,double y,double z,double dx,double dy,double dz, double th
*
*@return:       void
*
*@reference:    http://www.prinmath.com/csci5229/F18/programs/ex9.zip
*/

void drawCubewithoutTexture(double x,double y,double z,double delta_x,double delta_y,double delta_z, double th)
{

//      glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, Shine);
//      glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, colorwhite);
//      glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, colorblack);
        //  Save transformation
        glPushMatrix();
        //  Offset
        glTranslated(x,y,z);
        glRotated(th,0,1,0);
        glScaled(delta_x,delta_y,delta_z);
        //  Cube

        glBegin(GL_QUADS);
        //  Front
        glNormal3f(0, 0, +1);
//        glTexCoord2f(0.0, 0.0);
        glVertex3f(-1,-1, 1);
//        glTexCoord2f(1.0, 0.0);
        glVertex3f(+1,-1, 1);
//        glTexCoord2f(1.0, 1.0);
        glVertex3f(+1,+1, 1);
//        glTexCoord2f(0.0, 1.0);  
        glVertex3f(-1,+1, 1);
        glEnd();
        glBegin(GL_QUADS);
        //  Back
        glNormal3f(0, 0, -1);
//        glTexCoord2f(1.0, 0.0); 
        glVertex3f(+1,-1,-1);
//        glTexCoord2f(0.0, 0.0);
        glVertex3f(-1,-1,-1);
//        glTexCoord2f(0.0, 1.0);
        glVertex3f(-1,+1,-1);
//        glTexCoord2f(1.0, 1.0);
        glVertex3f(+1,+1,-1);
        glEnd();
        glBegin(GL_QUADS);
        //  Right
        glNormal3f(+1, 0, 0);
//        glTexCoord2f(0.0, 1.0);
        glVertex3f(+1,-1,+1);
//        glTexCoord2f(1.0, 0.0);
        glVertex3f(+1,-1,-1);
//        glTexCoord2f(1.0, 0.0);
        glVertex3f(+1,+1,-1);
//        glTexCoord2f(1.0, 1.0);
        glVertex3f(+1,+1,+1);
 
       glEnd();
        //  Left
        glBegin(GL_QUADS);
        glNormal3f(-1, 0, 0);
//        glTexCoord2f(0.0, 0.0);
        glVertex3f(-1,-1,-1);
//        glTexCoord2f(0.0, 1.0);
        glVertex3f(-1,-1,+1);
//        glTexCoord2f(1.0, 1.0);  
        glVertex3f(-1,+1,+1);
//        glTexCoord2f(1.0, 0.0);
        glVertex3f(-1,+1,-1);
        glEnd();
        //  Top
        glBegin(GL_QUADS);
        glNormal3f( 0,+1, 0);
//        glTexCoord2f(0.0, 1.0);
        glVertex3f(-1,+1,+1);
//        glTexCoord2f(1.0, 1.0); 
        glVertex3f(+1,+1,+1);
//        glTexCoord2f(1.0, 0.0);
        glVertex3f(+1,+1,-1);
//        glTexCoord2f(0.0, 0.0);
        glVertex3f(-1,+1,-1);
        glEnd();
        //  Bottom
        glBegin(GL_QUADS);
        glNormal3f(0, -1, 0);
//        glTexCoord2f(0.0, 0.0);
        glVertex3f(-1,-1,-1);
//        glTexCoord2f(1.0, 0.0);
        glVertex3f(+1,-1,-1);
//        glTexCoord2f(1.0, 1.0);
        glVertex3f(+1,-1,+1);
//        glTexCoord2f(0.0, 1.0);
        glVertex3f(-1,-1,+1);
        //  End
        glEnd();
        //  Undo transofrmations
        glPopMatrix();
}


/**
*@func:		drawCone
*
*@description:	helps draw a cone
*
*@param:	double x, double y, double z, double delta_x, double delta_y, double delta_z
*
*@return:	void
*
*/

void drawCone(double radius,double height,double x1, double y1, double z1,double delta_x,double delta_y,double delta_z,double th,GLubyte R,GLubyte G,GLubyte B,double alpha)
{
 	glPushMatrix();
        glTranslated(x1,y1,z1);
        glRotated(th,1,0,0);
        glRotated(alpha,0,1,0);
        glScaled(delta_x,delta_y,delta_z);


        GLfloat x              = 0.0;
        GLfloat y              = 0.0;
        GLfloat angle          = 0.0;
        GLfloat angle_stepsize = 0.005;


        /** Draw the tube */
        glColor3ub(R-40,G-40,B-40);
        glBegin(GL_LINES);
        angle = 0.0;
        while( angle < 2*PI ) 
        {
                x = radius * cos(angle);
                y = radius * sin(angle);
                glVertex3f(0, 0 , height);
                glVertex3f(x, y , 0.0);
                angle = angle + angle_stepsize;
        }
//        glVertex3f(radius, 0.0, height);
//        glVertex3f(radius, 0.0, 0.0);
        glEnd();

        /** Draw the circle on bottom of cylinder */
/*        glColor3ub(R,G,B);
        glBegin(GL_POLYGON);
        angle = 0.0;
        while( angle < 2*PI ) 
        {
                x = radius * cos(angle);
                y = radius * sin(angle);
                glVertex3f(x, y , height);
                angle = angle + angle_stepsize;
        }
                glVertex3f(radius, 0.0, 0.0);
        glEnd();*/
        glPopMatrix();
}

/********************************************************drawCannon()*******************************************
*@func:		drawCannon
*
*@description:	
*
*@params:	double x, double y, double z, double delta_x, double delta_y, double delta_z
*
*@return:	void
*
****************************************************************************************************************/

void drawCannon(double x, double y, double z, double delta_x, double delta_y, double delta_z)
{

	drawSphere(x, y, z, delta_x, delta_y, delta_z);

}

/********************************************drawTurret()********************************************************
*@func:		drawTurret
*
*@description:	
*
*@param:	double radius, double height,double x1, double y1, double z1,double delta_x,double delta_y,double delta_z,double th,GLubyte R, GLubyte G,GLubyte B,double alpha,double FireBallRad
*
*@return:	void
*
*********************************************************************************************************************/

void drawTurret(double radius, double height,double x1, double y1, double z1,double delta_x,double delta_y,double delta_z,double th,GLubyte R, GLubyte G,GLubyte B,double alpha,double FireBallRad)
{

	glPushMatrix();
        glTranslated(x1,y1,z1);
        glRotated(th,1,0,0);
        glRotated(alpha,0,1,0);
        glScaled(delta_x,delta_y,delta_z);
	drawCylinder(radius,height,0, 0, 0,1,1,1,0,R,G,B,0);
	glColor3ub(255 , 255 ,0);
	drawSphere(0, 0, height + FireBallRad, FireBallRad, FireBallRad, FireBallRad);
	glPopMatrix();

}

/***************************************************************drawCycloid()************************************************
*@func:			drawCycloid()
*
*@description:		
*
*@param:		double radius, double height,double x1, double y1, double z1,double delta_x,double delta_y,double delta_z,double th,GLubyte R, GLubyte G,GLubyte B,double alpha
*
*@return:		void
*
***************************************************************************************************************************/

void drawCycloid(double radius, double height,double x1, double y1, double z1,double delta_x,double delta_y,double delta_z,double th,GLubyte R, GLubyte G,GLubyte B,double alpha)
{

	glPushMatrix();
        glTranslated(x1,y1,z1);
        glRotated(th,1,0,0);
        glRotated(alpha,0,1,0);
        glScaled(delta_x,delta_y,delta_z);


        GLfloat x              		= 0.0;
        GLfloat y              		= 0.0;
        GLfloat angle          		= 0.0;
        GLfloat angle_stepsize 		= 0.1;
	GLfloat height_stepsize		= 0.05;
	GLfloat init_height 		= 0.0;
	GLfloat init_height_previous 	= 0.0;

        /** Draw the tube */
        glColor3ub(R-40,G-40,B-40);
        glBegin(GL_LINE_STRIP);
        angle = 0.0;
	init_height = 0.0 + 0.1;

        while( init_height < height ) 
        {
                x = radius * cos(angle);
                y = radius * sin(angle);
                glVertex3f(x, y , init_height);
                glVertex3f(x, y , init_height_previous);
                angle = angle + angle_stepsize;
		init_height_previous = init_height;
		init_height = init_height + height_stepsize;
        }
        glEnd();
        /** Draw the circle on top of cylinder */
        glPopMatrix();
}


/***************************************************************drawCloud()************************************************
*@func:                 drawCloud()
*
*@description:          
*
*@param:                
*
*@return:               void
*
***************************************************************************************************************************/

void drawClouds(double x, double y, double z, double delta_x, double delta_y, double delta_z)
{

	glPushMatrix();
        glTranslated(x,y,z);
	glScaled(delta_x,delta_y,delta_z);
	glColor3ub(200,200,200);
	drawSphere(0, 0, 0, 2, 2, 2);
	drawSphere(0, 0, 0.5, 1, 1, 1);
	drawSphere(0, 0, 1.0, 2, 2, 2);
	drawSphere(0, 0, 1.5, 1, 1, 1);
	drawSphere(0.5, 0, 0, 2, 2, 2);
        drawSphere(0.5, 0, 0, 1, 1, 1);
        drawSphere(0.5, 0, 0, 2, 2, 2);
        drawSphere(0.5, 0, 0, 1, 1, 1);
	drawSphere(0, 0.5, 0, 2, 2, 2);
        drawSphere(0, 0.5, 0, 1, 1, 1);
        drawSphere(0, 0.5, 0, 2, 2, 2);
        drawSphere(0, 0.5, 0, 1, 1, 1);

	drawSphere(0, 0, 0, 2, 2, 2);
        drawSphere(0, 0, -0.5, 1, 1, 1);
        drawSphere(0, 0, -1.0, 2, 2, 2);
        drawSphere(0, 0, -1.5, 1, 1, 1);
        drawSphere(-0.5, 0, 0, 2, 2, 2);
        drawSphere(-0.5, 0, 0, 1, 1, 1);
        drawSphere(-0.5, 0, 0, 2, 2, 2);
        drawSphere(-0.5, 0, 0, 1, 1, 1);
        drawSphere(0, -0.5, 0, 2, 2, 2);
        drawSphere(0, -0.5, 0, 1, 1, 1);
        drawSphere(0, -0.5, 0, 2, 2, 2);
        drawSphere(0, -0.5, 0, 1, 1, 1);

	drawSphere(-1.5, 0, 0, 2, 2, 2);
        drawSphere(-1.5, 0, 0, 1, 1, 1);
        drawSphere(-1.5, 0, 0, 2, 2, 2);
        drawSphere(-1.5, 0, 0, 1, 1, 1);

	drawSphere(1.5, 0, 0, 2, 2, 2);
        drawSphere(1.5, 0, 0, 1, 1, 1);
        drawSphere(1.5, 0, 0, 2, 2, 2);
        drawSphere(1.5, 0, 0, 1, 1, 1);
	glPopMatrix();

}
