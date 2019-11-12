/**
*@file: 	3D.c
*
*@description:	A scene describing two planes and a warship that are travelling in the ocean
*		The ship is obstructed by Mountains. It toggles between orthogonal, perspective
*		and first person view.
*
*@author:	Diptarshi Chakraborty
*
*@date:		3rd October 2019
*
*/



/*C STL header files for standard I/0 operations that print to the terminal */


/*
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#define GL_GLEXT_PROTOTYPES

#ifdef __APPLE__
#include <GLUT/glut.h>

#else
#include <GL/glut.h>
#endif

*/

#include "CSCIx229.h"
#include "headers/basic_shapes.h"
#include "headers/buildings.h"
#include "headers/vehicles.h"



#define		PI		3.1415926
#define		increment	10


//#define GL_NORMAL(a,b,c,p,q,r,x,y,z)  glNormal3d(((q-b)*(z-c))-((y-b)*(r-c)),-((p-a)*(z-c))-((x-a)*(r-c)),((p-a)*(y-b))-((x-a)*(q-b)))

#define GL_NORMAL(x1,y1,z1,x2,y2,z2,x3,y3,z3)   glNormal3d(((y2-y1)*(z3-z2))-((z2-z1)*(y3-y2)), ((z2-z1)*(x3-x2))-((x2-x1)*(z3-z2)),((x2-x1)*(y3-y2))-((y2-y1)*(x3-x2)))
#define GL_NORMALNX(x1,y1,z1,x2,y2,z2,x3,y3,z3)   glNormal3d( -(((y2-y1)*(z3-z2))-((z2-z1)*(y3-y2))), ((z2-z1)*(x3-x2))-((x2-x1)*(z3-z2)),((x2-x1)*(y3-y2))-((y2-y1)*(x3-x2)))

#define GL_NORMALNY(x1,y1,z1,x2,y2,z2,x3,y3,z3)   glNormal3d(((y2-y1)*(z3-z2))-((z2-z1)*(y3-y2)), -(((z2-z1)*(x3-x2))-((x2-x1)*(z3-z2))),((x2-x1)*(y3-y2))-((y2-y1)*(x3-x2)))

#define GL_NORMALNZ(x1,y1,z1,x2,y2,z2,x3,y3,z3)   glNormal3d(((y2-y1)*(z3-z2))-((z2-z1)*(y3-y2)), -(((z2-z1)*(x3-x2))-((x2-x1)*(z3-z2))),-(((x2-x1)*(y3-y2))-((y2-y1)*(x3-x2))))


#define GL_NORMALNXY(x1,y1,z1,x2,y2,z2,x3,y3,z3)   glNormal3d( -(((y2-y1)*(z3-z2))-((z2-z1)*(y3-y2))), -(((z2-z1)*(x3-x2))-((x2-x1)*(z3-z2))),((x2-x1)*(y3-y2))-((y2-y1)*(x3-x2)))


/* These are for orthogonal mode of projection*/
int alpha=0;
int theta=0;

int displayMode = 2;
double widht2height = 1.0;
int Field_of_View = 55;
double dimension = 20.0;   //  Size of world

int smoothness  =	1;  	/* Smooth/Flat shading*/
int locality	=	0; 	/*Locality*/
int emission	=	0; 	/*Intensity of Emission*/
int ambient_intensity = 10; 	/* Ambient intensity*/
int diffuse_intensity = 100;	/*Diffusion intensity*/
int specular_intensity= 0;	/*Specular intensity*/
int shine = 0;			/* Value of shine in power*/
float Shine = 1;		/* Value of shine*/
int azhimuth = 90;		/* azhimuth of light*/
float light_elevation = 0.0;	/* Elevation of light*/
int light = 1;			/* Light option kept on by default*/
int distance = 18;		/* Distance of the light source*/
int unit_step = 1;		/* One unit of increment or deceremnet*/
int move = 1;       		/*  Move light */



unsigned int texture[14];


/* These are for perspective mode of projection*/
double EYE_x = 0;
double EYE_y = 0;
double EYE_z = 0;


/* These are for first person mode of projection*/
/*double Focus_x = 0;
double Focus_y = -25;
double Focus_z = 10;

double Delta_x = 0;
double Delta_y = 0;
*/

// X-coordinate of camera position
double EX = 5;
// Y-coordinate of camera position
double EY = -20;
// Z-coordinate of camera position
double EZ = 10;
// X-coordinate of where the camera is looking
double AX = 0;
// Y-coordinate of where the camera is looking
double AY = 0;
// Z-coordinate of where the camera is looking
double AZ = 0;


double rot = -180.0;

double Cx;
double Cy;
 /* EX = EX + AX * 0.1;
  EZ = EZ + AZ * 0.1;
*/



#define LEN 8192  //  Maximum length of text string

/**
*@func:		Print
*
*@description:	Prints the function name
*
*@param:	const char * format
*
*@return:	void
*
*/

/*void Print(const char* format , ...)
{
   char    buf[LEN];
   char*   ch = buf;
   va_list args;
   //  Turn the parameters into a character string
   va_start(args, format);
   vsnprintf(buf, LEN, format, args);
   va_end(args);
   //  Display the characters one at a time at the current raster position
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *ch++);
}
*/


/**
*@func:         idle
*
*@description:  GLUT calls this routine when the window is resized
*
*@param:        void
*
*@return:       void
*
*/

void idle()
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   azhimuth = fmod(90*t,360.0);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}


/**
*@func:         arrow_keys_move
*
*@description:  main display function that renders the image called by GLUT
*
*@param:        void
*
*@return:       void
*
*todo:          add variable angle functionality
*/

void arrow_keys_move(int key, int x, int y)
{

	double dt = 0.005;
        switch(key)
        {
                case GLUT_KEY_UP:
                alpha++;

		EX += Cx*dt; //Update the eye vector based on the camera vector
		EY += Cy*dt;
                theta %= 360; /*Helps angles be within the margin of 360*/
                alpha %= 360; /*Helps angles be within the margin of 360*/
                glutPostRedisplay();
                break;

                case GLUT_KEY_DOWN:
                alpha--;
		EX -= Cx*dt; //Update the eye vector based on the camera vector
		EY -= Cy*dt;
                theta %= 360;/*Helps angles be within the margin of 360*/
                alpha %= 360;/*Helps angles be within the margin of 360*/
                glutPostRedisplay();
                break;

		 case GLUT_KEY_LEFT:
                theta++;
		rot = rot + 1;

                theta %= 360;/*Helps angles be within the margin of 360*/
                alpha %= 360;/*Helps angles be within the margin of 360*/
                glutPostRedisplay();
                break;

                case GLUT_KEY_RIGHT:
                theta--;
		rot = rot - 1;

                theta %= 360;/*Helps angles be within the margin of 360*/
                alpha %= 360;/*Helps angles be within the margin of 360*/
                glutPostRedisplay();
                break;

		case GLUT_KEY_PAGE_UP:
                dimension++;
                glutPostRedisplay();
                break;

		case GLUT_KEY_PAGE_DOWN:
                dimension--;
                glutPostRedisplay();
                break;

		case GLUT_KEY_HOME:
                unit_step = -unit_step;
                glutPostRedisplay();
                break;

                case GLUT_KEY_END:
                smoothness = 1 - smoothness;
                glutPostRedisplay();
                break;



        }
}

/**
*@func:         myProject
*
*@description:  A program that helps us conmpute the vertices using cosine sine functions that inturn helps us render shapes
*
*@param:        double theta,double alpha
*
*@return:       void
* 
*/

void Project()
{

        /* Select projection matrix */
        glMatrixMode(GL_PROJECTION);
        /*  Set projection to identity */
        glLoadIdentity();
        if(displayMode)
        {
                gluPerspective(Field_of_View , widht2height , dimension/4, 4*dimension);
        }
        else
        {
                /*  Orthogonal projection:  unit cube adjusted for aspect ratio*/
                glOrtho(-widht2height*dimension,+widht2height*dimension, -dimension,+dimension, -dimension,+dimension);
        }
        /*  Select model view matrix*/
        glMatrixMode(GL_MODELVIEW);



        /*  Set model view to identity*/
        glLoadIdentity();
}


/**
*@func:		char_input
*
*@description:	handles the event of key presses
*
*@param:	char key, int x, int y
*
*@return:	void
*/

void char_input(unsigned char key,int x, int y)
{
	switch(key)
	{

		case 'm':       case 'M':
                if( displayMode == 0)
		{
			displayMode =1;		/* If the mode is 0 , make it 1*/
		}

		else if( displayMode == 1)
		{
		      	displayMode = 2;	/* If the mode is 1, make it 0*/
		}

		else if( displayMode == 2)
                {
                        displayMode = 0;                /* If the mode is 2, make it back to 0*/
                }


		break;

		case 'l':	case 'L':       /* Option to toggle lighting*/
		light = 1-light;
                break;

		case 'f':       case 'F':	/* Option to increase field of view*/
                	Field_of_View += 1;
                break;

                case 'v':       case 'V':	/* Option to decrease field of view */
                	Field_of_View -= 1;
                break;

		case 'a':	case 'A':
			ambient_intensity += 5;/*Option to increase ambient intensity */
		break;

		case 'z':       case 'Z':
                        ambient_intensity -= 5;/*Option to decrease ambient intensity */
                break;

		case 'd':       case 'D':
                        diffuse_intensity += 5;/*Option to increase diffuse intensity */
                break;

		case 'c':       case 'C':
                        diffuse_intensity -= 5;/*Option to decrease diffuse intensity */
                break;

		case 's':       case 'S':
                        specular_intensity += 5;/*Option to increase specular intensity */
                break;

                case 'x':       case 'X':
                        specular_intensity -= 5;/*Option to decrease specular intensity */
                break;

		case 'e':       case 'E':
                        emission += 5;	/*Option to increase emission */
                break;

                case 'r':       case 'R':
                        emission -= 5;	/*Option to decrease emission */
                break;

		case 'y':       case 'Y':
                        azhimuth += 5;	/*Option to increase azhimuth */
                break;

                case 'u':       case 'U':
                        azhimuth -= 5;	/*Option to decrease azhimuth */
                break;

		case 'h':       case 'H':
                        if (shine <7 )
			{
				shine += 1;	/*Option to increase shine */
			}
                break;

                case 'j':       case 'J':
			if (shine > -1 )
                        {
                                shine -= 1;     /*Option to increase shine */
                        }
                break;

		case 'k':       case 'K':
                        light_elevation += 0.1;     /*Option to increase light elevation */
                break;

                case 'n':       case 'N':
                        light_elevation -= 0.1;     /*Option to decrease light elevation */
                break;

		case 'q':	case 'Q':	/* Option to change locality */
			locality = 1 - locality;
		break;

		case 'o':	case 'O':
			move = 1 - move;
		break;

		case 't':       case 'T':       /* Option to change circumference of light source path */
                        if ( distance == 18)
				distance = 5;
			else
				distance = 18;
                break;

		case '+':       	       /* Option to change circumference of light source path */
                        EZ = EZ + 1;

		break;

		 case '-':                      /* Option to change circumference of light source path */
                        EZ = EZ - 1;
                break;

	}


	//  Translate shininess power to value (-1 => 0)
    	Shine = shine<0 ? 0 : pow(2.0,shine);

	/*Reproject*/

	Project(displayMode?Field_of_View:0,widht2height,dimension);
	//	myProject();
   	//  Tell GLUT it is necessary to redisplay the scene

	glutIdleFunc(move?idle:NULL);

	//  Tell GLUT it is necessary to redisplay the scene
   	glutPostRedisplay();
}

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

/**
*@func:		drawSun
*
*@description:	draws a sun
*
*@param:	double x,double y,double z,double r
*
*@return:	void
*
*/

void drawSun(double x,double y,double z,double r)
{
	int theta, alpha;
	float yellow[] = {1.0, 1.0, 0.0, 1.0};
	float Emission[]  = {0.0, 0.0, 0.01*emission, 1.0};
	glPushMatrix();
   	//  Offset, scale and rotate
   	glTranslated(x,y,z);
   	glScaled(r,r,r);
   	//  White ball
   	glColor3f(1,1,1);

	glMaterialf(GL_FRONT,GL_SHININESS,Shine);

	glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);

	glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
   	//  Bands of latitude
   	for (alpha=-90; alpha<90; alpha+=increment)
  	{
      		glBegin(GL_QUAD_STRIP);
      		for (theta=0; theta<=180; theta+=2*increment)
      		{
         		Vertex(theta,alpha);
         		Vertex(theta,alpha+increment);
      		}
      		glEnd();
   	}
   	//  Undo transofrmations
   	glPopMatrix();
}


/************************** drawCylinder() **************************
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

/**
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
*/






/**
*@func:		drawMyShip
*
*@description:	draws a ship
*
*@param:	double x, double y, double z, double delta_x, double delta_y, double delta_z, double theta
*
*@return:	void
*
*@reference:	Derived from example shapes provided in  http://www.prinmath.com/csci5229/F18/programs/ex9.zip
*/

static void drawMyShip(double x, double y, double z, double delta_x, double delta_y, double delta_z, double theta)
{
  	//  Save transformation
  	glPushMatrix();
  	//  Offset
  	glTranslated(x,y,z);
  	glRotated(theta, 0, 1, 0);
  	glScaled(delta_x,delta_y,delta_z);

	 glBindTexture(GL_TEXTURE_2D,texture[9]);
 
  	glBegin(GL_QUADS);

  	glColor3ub(100, 100, 100);

	glNormal3d(0, 0, 1);

	glTexCoord2f(0.0, 0.0);
  	glVertex3f(-1, -1, 1);

	glTexCoord2f(1.0, 0.0);
  	glVertex3f(+1, -1, 1);

	glTexCoord2f(1.0, 1.0);
  	glVertex3f(+1, +1, 1);

	glTexCoord2f(0.0, 1.0);
  	glVertex3f(-1, +1, 1);

	glEnd();


	glBegin(GL_QUADS);

  	glColor3ub(60, 72, 78);

	GL_NORMAL(0, -1, 0, 0, +1, 0, +1,- 1, +1);
	glTexCoord2f(0.0, 1.0);
  	glVertex3f(+1, -1, +1);

	glTexCoord2f(0.0, 0.0);
  	glVertex3f(0, -1, 0);

	glTexCoord2f(1.0, 0.0);
  	glVertex3f(0, +1, 0);

	glTexCoord2f(1.0, 1.0);
  	glVertex3f(+1, +1, +1);
	glEnd();

	glBegin(GL_QUADS);

	GL_NORMAL(0, -1, 0,-1, -1, +1,0, +1, 0);

	glTexCoord2f(0.0, 1.0);
  	glVertex3f(-1, -1, +1);

	glTexCoord2f(0.0, 0.0);
  	glVertex3f(0, -1, 0);

	glTexCoord2f(1.0, 0.0);
  	glVertex3f(0, +1, 0);

	glTexCoord2f(1.0, 1.0);
  	glVertex3f(-1, +1, +1);

	glEnd();

  	glBegin(GL_TRIANGLES);
  	glColor3ub(100, 100, 100);

	glNormal3d(0, 0, +1);

	glTexCoord2f(0.0, 0.0);
  	glVertex3f(-1, +1, 1);

	glTexCoord2f(1.0, 0.0);
  	glVertex3f(+1, +1, 1);

	glTexCoord2f(0.5, 1.0);
  	glVertex3f(0, +2, 1);
	glEnd();



	glBegin(GL_TRIANGLES);
	glNormal3d(0, 0, +1);

	glTexCoord2f(0.0, 1.0);
  	glVertex3f(-1, -1, +1);

	glTexCoord2f(0.5, 0.0);
  	glVertex3f(0, -2, +1);

	glTexCoord2f(1.0, 1.0);
  	glVertex3f(+1, -1, +1);

	glEnd();




//left side
	glBegin(GL_TRIANGLES);


  	glColor3ub(120, 100, 80);
/* texture line*/	glBindTexture(GL_TEXTURE_2D,texture[11]);

	GL_NORMAL(-1, +1, +1, 0, +2, +1, 0, +1, 0);

	glTexCoord2f(0.0, 0.0);
  	glVertex3f(-1, +1, +1);

	glTexCoord2f(0.5, 1.0);
  	glVertex3f(0, +1, 0);

	glTexCoord2f(1.0, 0.0);
  	glVertex3f(0, +2, +1);

	glEnd();


//right side
	glBegin(GL_TRIANGLES);
 /* texture line*/       glBindTexture(GL_TEXTURE_2D,texture[11]);


	GL_NORMAL(0, +2, +1, +1, +1, +1, 0, +1, 0);

	glTexCoord2f(0.0, 0.0);
  	glVertex3f(+1, +1, +1);

	glTexCoord2f(0.5, 1.0);
  	glVertex3f(0, +1, 0);

	glTexCoord2f(1.0, 0.0);
  	glVertex3f(0, +2, +1);

	glEnd();


	glBegin(GL_TRIANGLES);

	 /* texture line*/        glBindTexture(GL_TEXTURE_2D,texture[11]);


	GL_NORMAL(0, -2, +1, -1,-1, +1, 0, -1, 0);

	glTexCoord2f(0.0, 0.0);
  	glVertex3f(-1,-1, +1);

	glTexCoord2f(0.5, 1.0);
  	glVertex3f(0, -1, 0);

	glTexCoord2f(1.0, 0.0);
  	glVertex3f(0, -2, +1);

	glEnd();



	glBegin(GL_TRIANGLES);

	/* texture line*/       glBindTexture(GL_TEXTURE_2D,texture[11]);


	GL_NORMAL(0, -1, 0, +1, -1, +1, 0, -2, +1);

	glTexCoord2f(0.0, 0.0);
  	glVertex3f(+1, -1, +1);

	glTexCoord2f(0.5, 1.0);
  	glVertex3f(0, -1, 0);

	glTexCoord2f(1.0, 0.0);
  	glVertex3f(0, -2, +1);
  	glEnd();




  	glColor3ub(100, 130, 160);
	glBindTexture(GL_TEXTURE_2D,texture[11]);
  	drawCube(0, 0, 1.2, 0.5, 1.0, 0.2, 0);

  	glColor3ub(120, 140, 160);
	glBindTexture(GL_TEXTURE_2D,texture[9]);
  	drawCube(0, 0, 1.6, 0.25, 0.75, 0.2, 0);

  	/*chimney pipes*/
  	glColor3ub(180, 150, 130);
	glBindTexture(GL_TEXTURE_2D,texture[10]);
  	drawCube(0, 0.25, 2.2, 0.1, 0.1, 0.4, 0);

  	glColor3ub(200, 187, 213);
  	drawCube(0, -0.25, 2.0, 0.1, 0.1, 0.2, 0);

  	glPopMatrix();
}

/**
*@func:
*
*@description:
*
*@param:
*
*@return:
*
*/

void drawMyMountain()
{

	glColor3ub(100,54,58);
        drawCone(-20,20,-5,1,1,1,90);
        drawCone(-19,20,-5,1,1,1,90);
        drawCone(-18,20,-5,1,1,1,90);
        drawCone(-17,20,-5,1,1,1,90);
        drawCone(-16,20,-5,1,1,1,90);
        drawCone(-15,20,-5,1,1,1,90);
        drawCone(-14,20,-5,1,1,1,90);
        drawCone(-13,20,-5,1,1,1,90);
        drawCone(-12,20,-5,1,1,1,90);
        drawCone(-11,20,-5,1,1,1,90);
        drawCone(-10,20,-5,1,1,1,90);
        drawCone(-9,20,-5,1,1,1,90);
        drawCone(-8,20,-5,1,1,1,90);
        drawCone(-7,20,-5,1,1,1,90);
        drawCone(-6,20,-5,1,1,1,90);
        drawCone(-5,20,-5,1,1,1,90);
        drawCone(-4,20,-5,1,1,1,90);
        drawCone(-3,20,-5,1,1,1,90);
        drawCone(-2,20,-5,1,1,1,90);
        drawCone(-1,20,-5,1,1,1,90);
        drawCone(0,20,-5,1,1,1,90);
        drawCone(1,20,-5,1,1,1,90);
        drawCone(2,20,-5,1,1,1,90);
        drawCone(3,20,-5,1,1,1,90);
        drawCone(5,20,-5,1,1,1,90);
        drawCone(6,20,-5,1,1,1,90);
        drawCone(7,20,-5,1,1,1,90);
        drawCone(8,20,-5,1,1,1,90);
        drawCone(9,20,-5,1,1,1,90);
        drawCone(10,20,-5,1,1,1,90);
        drawCone(11,20,-5,1,1,1,90);
        drawCone(12,20,-5,1,1,1,90);
        drawCone(-12,20,-5,1,1,1,90);
        drawCone(-11,20,-5,1,1,1,90);
	drawCone(-11,4,-5,1,1,1,90);
        drawCone(-10,2,-5,1,1,1,90);
        drawCone(-10,2,-5,1,1,1,90);
        drawCone(-9,0,-5,1,1,1,90);
        drawCone(-9,0,-5,1,1,1,90);
        drawCone(-8,2,-5,1,1,1,90);
        drawCone(-8,2,-5,1,1,1,90);
        drawCone(-7,4,-5,1,1,1,90);
        drawCone(-7,4,-5,1,1,1,90);
}

/**
*@func:		drawMyAirplane
*
*@description:	draws an airplane 
*
*@param:	double x, double y, double z, double delta_x, double delta_y, double delta_z, double theta
*
*
*/

void drawMyAirplane(double x, double y, double z, double delta_x, double delta_y, double delta_z, double theta)
{
  	/* transformation matrix is saved */
  	glPushMatrix();
  	//  Offset
  	glTranslated(x, y, z);
  	glRotated(theta, 0, 1, 0);
  	glScaled(delta_x, delta_y, delta_z);



	glBindTexture(GL_TEXTURE_2D,texture[9]);
  	/*wings*/
  	glColor3ub(255, 255, 255);
  	drawCube(0, 0.5, 0, 3, 0.2, 0.05, 0);

  	/*Thrusters*/
/*	glDisable(GL_TEXTURE_2D);
	glColor3ub(255, 255, 255);
  	drawSphere(1.5, 0.5, -0.2, 0.2, 0.5, 0.2);
  	drawSphere(-1.5, 0.5, -0.2, 0.2, 0.5 ,0.2);
	glEnable(GL_TEXTURE_2D);
*/
  	/*Highlight the wing endings*/
  	glColor3ub(255, 255, 255);
  	drawCube(3, 0.5, 0, 0.1, 0.3, 0.2, 0);
  	drawCube(-3, 0.5, 0, 0.1, 0.3, 0.2, 0);

  	/*tail*/
  	glColor3ub(200, 200, 200);
  	drawCube(0, -1.7, 0.8, 0.1, 0.3, 0.4, 0);
  	drawCube(0, -1.9, 1.3, 1, 0.1, 0.1, 0);


	/* Main body */
	glBindTexture(GL_TEXTURE_2D,texture[9]);
//	glBindTexture(GL_TEXTURE_2D,texture[13]);
        glColor3ub(225, 0, 0);
        drawCube(0, 0, 0, 0.5, 2, 0.4, 0);



//	glBindTexture(GL_TEXTURE_2D,texture[4]);

  	glBegin(GL_TRIANGLES);



  	/*nose head tip*/
  	glColor3ub(200, 200, 200);

	/*Top surface */
	//GL_NORMAL(+0.5,+2, 0.4, -0.5,+2, 0.4, 0, +3, 0);
	GL_NORMAL(-0.5,+2, 0.4, +0.5,+2, 0.4, 0, +3, 0);
  	glTexCoord2f(0.0, 0.0); glVertex3f(-0.5,+2, 0.4);
  	glTexCoord2f(1.0, 0.0);	glVertex3f(+0.5,+2, 0.4);
  	glTexCoord2f(0.5, 1.0); glVertex3f(0, +3, 0);
	glEnd();


	glBegin(GL_TRIANGLES);

	/*.bottom surface */
	//GL_NORMAL(+0.5, +2, -0.4, -0.5, +2, -0.4, 0, +3, 0);
	GL_NORMALNZ(-0.5, +2, -0.4, +0.5, +2, -0.4, 0, +3, 0);
  	glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, +2, -0.4);
  	glTexCoord2f(1.0, 0.0); glVertex3f(+0.5, +2, -0.4);
  	glTexCoord2f(0.5, 1.0); glVertex3f(0, +3, 0);
	glEnd();


	glBegin(GL_TRIANGLES);
	glColor3ub(200, 200, 200);

	/* Right side */
	//GL_NORMAL(+0.5, +2, -0.4, +0.5, +2, 0.4, 0, +3, 0);
	GL_NORMALNX(+0.5, +2, -0.4, +0.5, +2, +0.4, 0, +3, 0);
  	glTexCoord2f(1.0, 0.0); glVertex3f(+0.5, +2, 0.4);
  	glTexCoord2f(0.0, 0.0); glVertex3f(+0.5, +2, -0.4);
  	glTexCoord2f(0.5, 1.0); glVertex3f(0, +3, 0);
	glEnd();



	glBegin(GL_TRIANGLES);

	/* Left */
	glColor3ub(200, 200, 200);
	//GL_NORMAL(-0.5, +2, +0.4, -0.5, +2, +0.4, 0, +3, 0);
	GL_NORMAL(-0.5, +2, -0.4, -0.5, +2, +0.4, 0, +3, 0);
  	glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, +2, 0.4);
  	glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, +2, -0.4);
  	glTexCoord2f(0.5, 1.0); glVertex3f(0, +3, 0);
	glEnd();

//  	glColor3f(1,1,1);

	//Draw the fan blades at the tip of the head
/*  	glNormal3d(0, +1, 0);
  	glVertex3f(0, +3, 0);
  	glVertex3f(-0.1, +3, +1);
  	glVertex3f(+0.1, +3, +1);

  	glVertex3f(0, +3, 0);
  	glVertex3f(-0.1, +3, -1);
  	glVertex3f(+0.1, +3, -1);

  	glVertex3f(0, +3, 0);
  	glVertex3f(-0.4, +3, 1);
  	glVertex3f(-0.6, +3, 1);

  	glVertex3f(0, +3, 0);
  	glVertex3f(-0.4, +3, -1);
  	glVertex3f(-0.6, +3, -1);

  	glVertex3f(0, +3, 0);
  	glVertex3f(+0.4, +3, +1);
  	glVertex3f(+0.6, +3, +1);

  	glVertex3f(0, +3, 0);
  	glVertex3f(+0.4, +3, -1);
  	glVertex3f(+0.6, +3, -1);

  	glVertex3f(0, +3, 0);
  	glVertex3f(+1, +3, -0.1);
  	glVertex3f(+1, +3, +0.1);

  	glVertex3f(0, +3, 0);
  	glVertex3f(-1, +3, -0.1);
  	glVertex3f(-1, +3, +0.1);

  	glVertex3f(0, +3, 0);
  	glVertex3f(+1, +3, -0.4);
  	glVertex3f(+1, +3, -0.6);

  	glVertex3f(0, +3, 0);
  	glVertex3f(-1, +3, +0.4);
  	glVertex3f(-1, +3, +0.6);

  	glVertex3f(0, +3, 0);
  	glVertex3f(-1, +3, -0.4);
  	glVertex3f(-1, +3, -0.6);

  	glVertex3f(0, +3, 0);
  	glVertex3f(+1, +3, +0.4);
  	glVertex3f(+1, +3, +0.6);
*/
	glEnd();

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
*/



/*
void ErrCheck(const char* where)
{
   int err = glGetError();
   if (err) fprintf(stderr,"ERROR: %s [%s]\n",gluErrorString(err),where);
}*/

/**
*@func:         display
*
*@description:  wrapper around mydisplay
*
*@void:         void
*
*@return:       void
*
*/

void display()
{


	//glEnable(GL_CULL_FACE); 

   	/*Erase the window and the depth buffer*/
   	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	/* Enable Z-buffering in OpenGL*/
   	glEnable(GL_DEPTH_TEST);

   	/*  Undo previous transformations*/
   	glLoadIdentity();


	glEnable(GL_TEXTURE_2D);
   	glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);


	switch (displayMode)
	{
		case 0: /* This is for orthogonal mode */
		Print(" Orthogonal View ");
		glRotatef(alpha, 1, 0, 0);
      		glRotatef(theta, 0, 1, 0);
		break;

		case 1:  /* For perspective mode of projection */
		Print("Perspective View ");
		EYE_x = -2*dimension*sin((PI/180)*(theta))*cos((PI/180)*(alpha));
          	EYE_y = +2*dimension        *sin((PI/180)*(alpha));
          	EYE_z = +2*dimension*cos((PI/180)*(theta))*cos((PI/180)*(alpha));
          	gluLookAt(EYE_x, EYE_y, EYE_z, 0, 0, 0, 0, cos((PI/180)*(alpha)), 0);
        	break;

		case 2: /* This is for the first person mode of projection */
                Print("First person view ");
		Cx = +2 * dimension * sin((PI/180)*rot); //Ajust the camera vector based on rot
      		Cy = -2 * dimension * cos((PI/180)*rot);

                //gluLookAt(Focus_x, Focus_y, Focus_z, Delta_x, Delta_y, Focus_z, 0, 0, 1);
		// Orient the scene so it imitates first person movement
    		gluLookAt(EX, EY, EZ, Cx + EX, Cy + EY, EZ, 0, 0, 1);
                break;

	}


	glShadeModel(smoothness ? GL_SMOOTH : GL_FLAT);

	if (light)
   	{
        	//  Translate intensity to color vectors
        	float Ambience[]   = {0.01*ambient_intensity ,0.01*ambient_intensity ,0.01*ambient_intensity ,1.0};
        	float Diffusion[]   = {0.01*diffuse_intensity ,0.01*diffuse_intensity ,0.01*diffuse_intensity ,1.0};
        	float Specularity[]  = {0.01*specular_intensity,0.01*specular_intensity,0.01*specular_intensity,1.0};
        	//  Light position
        	float coordinates[]  = {distance*cos((PI/180)*azhimuth), distance*sin((PI/180)*azhimuth), light_elevation, 1.0};
        	//  Draw light position as ball (still no lighting here)
        	glColor3f(1,1,1);
//        	drawSun(coordinates[0],coordinates[1],coordinates[2] , 0.2);

		//  OpenGL should normalize normal vectors
        	glEnable(GL_NORMALIZE);

		//  Enable lighting
		glEnable(GL_LIGHTING);


		glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
        	glEnable(GL_COLOR_MATERIAL);

		//  Enable light 0
        	glEnable(GL_LIGHT0);
        	//  Set ambient, diffuse, specular components and position of light 0
        	glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambience );
        	glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffusion );
        	glLightfv(GL_LIGHT0,GL_SPECULAR, Specularity );
        	glLightfv(GL_LIGHT0,GL_POSITION, coordinates );
   	}

   	else
	{
     		glDisable(GL_LIGHTING);
	}


	drawSwastika(0,0,0,1,1,1);
//	ErrCheck("Display");
	glFlush();
   	glutSwapBuffers();

}



/**
*@func:         reshape
*
*@description:  handles the reshaping of the window
*
*@param:        int width, int height
*
*@return:       void
*/

void reshape(int width,int height)
{


        /* Calculate width to height ratio*/
        widht2height = (height>0) ? (double)width/height : 1;

        /*  Set viewport as entire window */
        glViewport(0,0, width,height);

	Project();

}


/**
*@func:         main
*
*@description:  main function that is the entry point of the program
*
*
*@param:        int argc, char argv[][]
*
*@return:       int
*
*@todo:         add interaction API calls
*/

int main(int argc, char *argv[])
{


        /*Initialize using command line arguments*/
        glutInit(&argc, argv);

        /*Initializing display modes*/
        glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH |  GLUT_DOUBLE);

        /*Initializing window position*/
        glutInitWindowPosition(30,30);

        /*Now I am fixing the window size to 720 * 640*/
        glutInitWindowSize(1000,1000);

        /*Naming the window*/
        glutCreateWindow("Naval War by Diptarshi ");

        /*Now Display the figure*/
        glutDisplayFunc(display);

	/*Reshape function*/
        glutReshapeFunc(reshape);

	/* Key press function */
	glutKeyboardFunc(char_input);

        /*Use arrow keys to change the viewing angles*/
        glutSpecialFunc(arrow_keys_move);


	 //  Load textures
   	texture[0] = LoadTexBMP("textures/brick.bmp");
   	texture[1] = LoadTexBMP("textures/pattern.bmp");
   	texture[2] = LoadTexBMP("textures/sky.bmp");
   	texture[3] = LoadTexBMP("textures/smoke.bmp");
   	texture[4] = LoadTexBMP("textures/squares.bmp");
   	texture[5] = LoadTexBMP("textures/stars.bmp");
   	texture[6] = LoadTexBMP("textures/water.bmp");
   	texture[7] = LoadTexBMP("textures/wood.bmp");
	texture[8] = LoadTexBMP("textures/copper.bmp");
	texture[9] = LoadTexBMP("textures/rusted.bmp");
	texture[10]=LoadTexBMP("textures/ship.bmp");
	texture[11]=LoadTexBMP("textures/galvanized.bmp");
	texture[12]=LoadTexBMP("textures/plane.bmp");
	texture[13]=LoadTexBMP("textures/plane_small.bmp");





        /*glutMainLoop enters the GLUT event processing loop*/
        glutMainLoop();

        return 0;


}

