
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

