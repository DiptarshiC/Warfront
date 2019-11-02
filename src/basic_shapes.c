
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#include "../headers/basic_shapes.h"
#include "../headers/vehicles.h"

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
void drawCylinder(GLfloat radius, GLfloat height, GLubyte R, GLubyte G, GLubyte B)
{

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
    	glColor3ub(R,G,B);
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
    	glEnd();
}

