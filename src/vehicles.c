 
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#include "../headers/basic_shapes.h"
#include "../headers/vehicles.h"



/***************************************************drawTank()*************************************************************
*@func: drawTank
*
*@description: Helps me a draw a tank. The trank looks like a Soviet Army tank from the 
*               1940s. It has the capacity to fire artillery, Has the Red Army logo on it
*               and can also fire missiles at the designated target. Look forward to work
*               hard on this one.
*
*@params:       double x: Indicates the forward/backward translation units of the vehcile
*               double y: Indicates the left/right translation unit of the vehicle
*               double z: Indicates the up/ down translation unit of the vehicle
*               double th: Indicates the amount by which you want the vehicle to turn
*
*@return:       int for now, later might change it to void
*
*
*@todo:         All the features are yet to be added. Just started working on the project
********************************************************************************************************************************/


#define         	PI              3.1415926
#define                 SIN(X)          sin((PI/180)*(X))
#define                 COS(X)          cos((PI/180)*(X))



void drawTank(double x,double y,double z,double delta_x,double delta_y,double delta_z, double turret_Front_Elevation, double turret_Side_Elevation,double FireBallRad, int turnAngle )
{

        float colorblack[] = {0,0,0,1};
        float colorwhite[] = {1,1,1,1};
//        glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, Shine);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, colorwhite);
        glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, colorblack);
        //  Save transformation
	glPushMatrix();
        //  Offset
        glTranslated(x,y,z);
//        glRotated(th,0,1,0);
        glScaled(delta_x,delta_y,delta_z);
	glRotated(turnAngle,0,0,1);

	glColor3ub(255, 0, 0);


	/* Gun mouth*/
//	drawCylinder(0.5, 12, 0, 2, 10.5,1, 1,1,turret_Front_Elevation,0, 200, 0,turret_Side_Elevation );
	drawTurret(0.5, 12,0, 2, 10.5,1,1,1,turret_Front_Elevation,0, 200,0,turret_Side_Elevation,FireBallRad);

	/*This is for the top surface*/

	//top
        glBegin(GL_POLYGON);
        glVertex3f(+1,+2,10);
        glVertex3f(+2,+1,10);
        glVertex3f(+2,-1,10);
        glVertex3f(+1,-2,10);
        glVertex3f(-1,-2,10);
        glVertex3f(-2,-1,10);
        glVertex3f(-2,+1,10);
	glVertex3f(-1,+2,10);

	glEnd();


	//Bottom
	glBegin(GL_POLYGON);

	glVertex3f(+1,+2,11);
        glVertex3f(+2,+1,11);
        glVertex3f(+2,-1,11);
        glVertex3f(+1,-2,11);
        glVertex3f(-1,-2,11);
        glVertex3f(-2,-1,11);
        glVertex3f(-2,+1,11);
 	glVertex3f(-1,+2,11);

        glEnd();



	//Sealing the surfaces : Front

	glBegin(GL_QUADS);
	glVertex3f(+1,+2,11);
 	glVertex3f(+1,+2,10);
	glVertex3f(-1,+2,10);
	glVertex3f(-1,+2,11);
	glEnd();


	//Sealing the surfaces : Back

        glBegin(GL_QUADS);
        glVertex3f(+1,-2,11);
        glVertex3f(+1,-2,10);
        glVertex3f(-1,-2,10);
        glVertex3f(-1,-2,11);
        glEnd();


	 //Sealing the surfaces : right

        glBegin(GL_QUADS);
        glVertex3f(+2,+1,11);
        glVertex3f(+2,+1,10);
        glVertex3f(+2,-1,10);
        glVertex3f(+2,-1,11);
        glEnd();


	//Sealing the surfaces : left

        glBegin(GL_QUADS);
        glVertex3f(-2,+1,11);
        glVertex3f(-2,-1,11);
        glVertex3f(-2,-1,10);
        glVertex3f(-2,+1,10);
        glEnd();



	 glColor3ub(0, 100, 255);

	 //Sealing the surfaces : right top diagonal

        glBegin(GL_QUADS);
        glVertex3f(+2,+1,10);
        glVertex3f(+2,+1,11);
        glVertex3f(+1,+2,11);
        glVertex3f(+1,+2,10);
        glEnd();


	//sealing the surfaces: right bottom diagonal
	glBegin(GL_QUADS);
        glVertex3f(+2,-1,11);
        glVertex3f(+2,-1,10);
        glVertex3f(+1,-2,10);
        glVertex3f(+1,-2,11);
        glEnd(); 

	//sealing the surfaces: left top diagonal
        glBegin(GL_QUADS);
        glVertex3f(-2,+1,11);
        glVertex3f(-1,+2,11);
        glVertex3f(-1,+2,10);
        glVertex3f(-2,+1,10);
        glEnd(); 

	//sealing the surfaces: left bottom diagonal
        glBegin(GL_QUADS);
        glVertex3f(-2,-1,11);
        glVertex3f(-2,-1,10);
        glVertex3f(-1,-2,10);
        glVertex3f(-1,-2,11);
        glEnd(); 



	/*This is for the second  layer*/

	 glColor3ub(0, 175, 255);
        //top
        glBegin(GL_POLYGON);
        glVertex3f(+1,+5,10);
        glVertex3f(+5,+1,10);
        glVertex3f(+5,-1,10);
        glVertex3f(+1,-5,10);
        glVertex3f(-1,-5,10);
        glVertex3f(-5,-1,10);
        glVertex3f(-5,+1,10);
        glVertex3f(-1,+5,10);

        glEnd();


        //Bottom
        glBegin(GL_POLYGON);

        glVertex3f(+1,+5,7);
        glVertex3f(+5,+1,7);
        glVertex3f(+5,-1,7);
        glVertex3f(+1,-5,7);
        glVertex3f(-1,-5,7);
        glVertex3f(-5,-1,7);
        glVertex3f(-5,+1,7);
        glVertex3f(-1,+5,7);

        glEnd();



	glColor3ub(0, 255, 175);
        //Sealing the surfaces : Front

        glBegin(GL_QUADS);
        glVertex3f(+1,+5,7);
        glVertex3f(+1,+5,10);
        glVertex3f(-1,+5,10);
        glVertex3f(-1,+5,7);
        glEnd();


        //Sealing the surfaces : Back

        glBegin(GL_QUADS);
        glVertex3f(+1,-5,7);
        glVertex3f(+1,-5,10);
        glVertex3f(-1,-5,10);
        glVertex3f(-1,-5,7);
        glEnd();


         //Sealing the surfaces : right

        glBegin(GL_QUADS);
        glVertex3f(+5,+1,7);
        glVertex3f(+5,+1,10);
        glVertex3f(+5,-1,10);
        glVertex3f(+5,-1,7);
        glEnd();


        //Sealing the surfaces : left

        glBegin(GL_QUADS);
        glVertex3f(-5,+1,7);
        glVertex3f(-5,-1,7);
        glVertex3f(-5,-1,10);
        glVertex3f(-5,+1,10);
        glEnd();


	    //Sealing the surfaces : right top diagonal

        glBegin(GL_QUADS);
        glVertex3f(+5,+1,10);
        glVertex3f(+5,+1,7);
        glVertex3f(+1,+5,7);
        glVertex3f(+1,+5,10);
        glEnd();


        //sealing the surfaces: right bottom diagonal
        glBegin(GL_QUADS);
        glVertex3f(+5,-1,7);
        glVertex3f(+5,-1,10);
        glVertex3f(+1,-5,10);
        glVertex3f(+1,-5,7);
        glEnd(); 

        //sealing the surfaces: left top diagonal
        glBegin(GL_QUADS);
        glVertex3f(-5,+1,7);
        glVertex3f(-1,+5,7);
        glVertex3f(-1,+5,10);
        glVertex3f(-5,+1,10);
        glEnd(); 

        //sealing the surfaces: left bottom diagonal
        glBegin(GL_QUADS);
        glVertex3f(-5,-1,7);
        glVertex3f(-5,-1,10);
        glVertex3f(-1,-5,10);
        glVertex3f(-1,-5,7);
        glEnd(); 



	/*Now, I shall draw the middle layer*/


	/* Top */
	glColor3ub(200, 100, 175);

        glBegin(GL_QUADS);
        glVertex3f(+8,+8,7);
        glVertex3f(-8,+8,7);
        glVertex3f(-8,-8,7);
        glVertex3f(+8,-8,7);
        glEnd();

	/* Bottom */
	glColor3ub(40, 40, 40);

	glBegin(GL_QUADS);
        glVertex3f(+10,+15,0);
        glVertex3f(-10,+15,0);
        glVertex3f(-10,-15,0);
        glVertex3f(+10,-15,0);
        glEnd(); 



	/* Front */
	glColor3ub(40, 70, 40);
	glBegin(GL_QUADS);
        glVertex3f(+8,+8,7);
        glVertex3f(+10,+15,0);
        glVertex3f(-10,+15,0);
        glVertex3f(-8,+8,7);
        glEnd();


	/* Back */
        glBegin(GL_QUADS);
        glVertex3f(-8,-8,7);
        glVertex3f(-10,-15,0);
        glVertex3f(+10,-15,0);
        glVertex3f(+8,-8,7);
        glEnd(); 

	/* Right */
	glBegin(GL_QUADS);
        glVertex3f(+8,+8,7);
        glVertex3f(+8,-8,7);
        glVertex3f(+10,-15,0);
        glVertex3f(+10,+15,0);
        glEnd();



	/* Left */
        glBegin(GL_QUADS);
        glVertex3f(-8,+8,7);
        glVertex3f(-10,+15,0);
        glVertex3f(-10,-15,0);
        glVertex3f(-8,-8,7);
        glEnd();

        glPopMatrix();
}



/***************************************************drawTank()*************************************************************
*@func: drawPlane
*
*@description: Helps me a draw a plane.
*
*
*
*
*@params:       double x: Indicates the forward/backward translation units of the vehcile
*               double y: Indicates the left/right translation unit of the vehicle
*               double z: Indicates the up/ down translation unit of the vehicle
*               double th: Indicates the amount by which you want the vehicle to turn
*
*@return:       int for now, later might change it to void
*
*
*@todo:         All the features are yet to be added. Just started working on the project
********************************************************************************************************************************/


void Plane(double x, double y, double z, double delta_x, double delta_y, double delta_z, double yaw, double roll, double pitch, double blast_rad, int textures[])
{
	glShadeModel(GL_SMOOTH);
	glPushMatrix();
	glTranslated(x,y,z);
/*      glRotated(roll,1,0,0);
	glRotated(yaw,0,1,0);
	glRotated(pitch,0,0,1);
*/

	glRotated(roll,COS(pitch) ,SIN(pitch),0);
//        glRotated(yaw,SIN(pitch),COS(pitch),0);
        glRotated(pitch,0,0,1);
        glScaled(delta_x,delta_y,delta_z);

	/* Now draswing the cockpit*/
	glColor3ub(175,175,175);
	drawSphere(0, 4, 0.4, 0.65, 0.65,0.65);

	glColor3ub(255,255,0);
	drawSphere(-2, 3.5 + blast_rad, 0.1, blast_rad , blast_rad , blast_rad ); /* Fireball out of the left turret*/
        drawSphere( 2, 3.5 + blast_rad, 0.1, blast_rad , blast_rad , blast_rad ); /* Fireball out of the right turret*/

	glColor3ub(45,155,40);
	drawCylinder(0.8, 5, 0, 0, 0,1, 1,1,-90,100,100,100,0);
	/* Now drawing missile cannons */
	drawCylinder(0.1, 1,-2, 2.4, 0.1,1, 1,1,-90,100,100,100,0); /* Missile cannon on the left wing*/
	drawCylinder(0.1, 1, 2, 2.4, 0.1,1, 1,1,-90,100,100,100,0); /* Missile cannon on the right wing*/
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,textures[16]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	/* Wing on the right side */
	glBegin(GL_QUADS);
	glNormal3f(0, 0, +1);
	glColor3ub(100,100,100);
	glTexCoord2f(0,1);glVertex3f(0.8,3.5,0);
        glTexCoord2f(0,0);glVertex3f(0.8,2.5,0);
        glTexCoord2f(1,0);glVertex3f(5.4,2.5,0);
        glTexCoord2f(1,1); glVertex3f(3.9,3.5,0);
	glEnd();

	/* Wing on the left side */
	glBegin(GL_QUADS);
	glNormal3f(0, 0, +1);
	glColor3ub(100,100,100);
        glTexCoord2f(1,0);glVertex3f(-0.8,2.5,0);
        glTexCoord2f(1,1);glVertex3f(-0.8,3.5,0);
        glTexCoord2f(0,1);glVertex3f(-3.9,3.5,0);
        glTexCoord2f(0,0); glVertex3f(-5.4,2.5,0);
        glEnd();

	glDisable(GL_TEXTURE_2D);
	/*Drawing the front nose*/
	drawCone(0.8,2,0,5,0,1,1,1,-90,100,100,100,0);

	/*Drawing the front nose*/
	drawCone(0.8,2,0,0,0,1,1,1,90,100,100,100,0);

	/* Drawing the tail plane*/
	glBegin(GL_TRIANGLES);
        glVertex3f(0,0,0.8);
	glVertex3f(0,-2,2);
	glVertex3f(0,-2,0);
        glEnd();

	glPopMatrix();
}

