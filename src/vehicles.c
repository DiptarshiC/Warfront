 
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#include "../headers/basic_shapes.h"
#include "../headers/vehicles.h"



/**
*@func: drawTank
*
*@description: Helps me a draw a tank. The trank looks like a Soviet Army tank from the 
*		1940s. It has the capacity to fire artillery, Has the Red Army logo on it
*		and can also fire missiles at the designated target. Look forward to work
*		hard on this one.
*
*@params:	double x: Indicates the forward/backward translation units of the vehcile
*		double y: Indicates the left/right translation unit of the vehicle
*		double z: Indicates the up/ down translation unit of the vehicle
*		double th: Indicates the amount by which you want the vehicle to turn
*
*@return:	int for now, later might change it to void
*
*
*@todo:		All the features are yet to be added. Just started working on the project
*/


void drawTank(double x,double y,double z,double delta_x,double delta_y,double delta_z, double th)
{
	float colorblack[] = {0,0,0,1};
        float colorwhite[] = {1,1,1,1};
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, Shine);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, colorwhite);
        glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, colorblack);
	//  Save transformation
        glPushMatrix();
        //  Offset
        glTranslated(x,y,z);
        glRotated(th,0,1,0);
        glScaled(delta_x,delta_y,delta_z);
	//top
	glBegin(GL_QUADS);
	glVertex3f(-1,+2,0);
	glVertex3f(+1,+2,0);
	glVertex3f(+2,+1,0);
        glVertex3f(-2,+1,0);
	glVertex3f(-1,-2,0);
 	glVertex3f(+1,-2,0);
	glVertex3f(+2,+1,0);
        glVertex3f(-2,+1,0);
	glVertex3f(-1,+2,1);
        glVertex3f(+1,+2,1);
        glVertex3f(+2,+1,1);
        glVertex3f(-2,+1,1);
        glVertex3f(-1,-2,1);
        glVertex3f(+1,-2,1);
        glVertex3f(+2,+1,1);
        glVertex3f(-2,+1,1);
	glEnd();
	glPopMatrix();
}

