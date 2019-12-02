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



#include <stdio.h>
/*
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

//#define GL_GLEXT_PROTOTYPES

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


#define			SIN(X)		sin((PI/180)*(X))
#define			COS(X)		cos((PI/180)*(X))

/* These are for orthogonal mode of projection*/



double turret_elevation_vertical = -90;
double turret_elevation_lateral = 0;
double FireBallRad = 0;
double blast_rad = 0;

int alpha=0;
int theta=0;

double XatTopOfTurret = 0;
double YatTopOfTurret = 0;
double ZatTopOfTurret = 0;

double tankCoordinateX = 0;
double tankCoordinateY = -450;
int tankRotationAngle  =0;

double planeCoordinateX = 0;
double planeCoordinateY = -450;
double planeCoordinateZ = 120;

double yaw = 0;
double roll = 0;
double pitch = 0;

int displayMode = 3;
double widht2height = 1.0;
int Field_of_View = 50;
double dimension = 20.0;   //  Size of world

int angleSun = 0;



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
int light = 0;			/* Light option kept on by default*/
int distance = 18;		/* Distance of the light source*/
int unit_step = 1;		/* One unit of increment or deceremnet*/
int move = 1;       		/*  Move light */

int event_flag = 0;

unsigned int texture[18];
int obj;			/* Variable to point to an object file*/

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

// X-coordinate of camera position when on tank
double EX = 0;
// Y-coordinate of camera position when on tank
double EY = -500;
// Z-coordinate of camera position when on tank 
double EZ = 30;
// X-coordinate of where the camera is looking when on tank
double AX = 0;
// Y-coordinate of where the camera is looking when on tank
double AY = 0;
// Z-coordinate of where the camera is looking when on tank
double AZ = 0;


// X-coordinate of camera position when on tank
double EtankX = 0;
// Y-coordinate of camera position when on tank
double EtankY = -500;
// Z-coordinate of camera position when on tank 
double EtankZ = 20;
double CtankX;
double CtankY;







// X-coordinate of camera position when on plane
double EplaneX = 0;
// Y-coordinate of camera position when on plane
double EplaneY = -500;
// Z-coordinate of camera position when on plane 
double EplaneZ = 90;
// X-coordinate of where the camera is looking when on plane
double AplaneX = 0;
// Y-coordinate of where the camera is looking when on plane
double AplaneY = 0;
// Z-coordinate of where the camera is looking when on plane
double AplaneZ = 0;
//UP vectors when on the plane
double Ux = 1;
double Uy = 0;
double Uz = 0;
//Look at vectors for the plane
double Ox = 0;
double Oy = 0;
double Oz = 0;
//Eye postion for the plane
double Ex = 1;
double Ey = 1; 
double Ez = 1; 


int flight_mode = 0;
int tank_mode = 1;

double rot = -180.0;

double Cx;
double Cy;
 /* EX = EX + AX * 0.1;
  EZ = EZ + AZ * 0.1;
*/



#define LEN 8192  //  Maximum length of text string

/**
*@func:		displayCrack()
*
*@description:
*
*@param:	void
*
*@return:	void
*
*
*/

void displayCrack()
{
	drawCrack( -100, -200,40,20,20,20,0,texture);
}

void display();

/**
*@func:         cannonFire
*
*@description: 
*
*@params:       void
*
*@return:       void
*
*
*/

void cannonFire()
{

        FireBallRad = 2;
	glutPostRedisplay();


}

/**
*@func:		missileFire
*
*@description:	
*
*@params:	void
*
*@return:	void
*
*/

void missileFire()
{
	blast_rad = 0.5;
        glutPostRedisplay();

}

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
	if(tank_mode)
	{
		FireBallRad = 0;
	}
	if(flight_mode)
	{
		blast_rad = 0;
	}
	planeCoordinateZ  += 0.8*sin((PI/180)*(roll));
	planeCoordinateY  += 0.8*cos((PI/180)*(pitch));
	planeCoordinateX  -= 0.8*sin((PI/180)*(pitch));

	angleSun += 1;
	angleSun = angleSun % 360;


   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/**
*@func:		changeTurretElevation
*
*@description:
*
*@params:	double mouseXCoordinate, double mouseYCoordinate
*
*@return: void
*
*@todo:
*
*/

void changeTurretElevation( double mouseXCoordinate, double mouseYCoordinate)
{

	float relative_x = (mouseXCoordinate) / (glutGet(GLUT_WINDOW_WIDTH));
	float relative_y = (mouseYCoordinate) /(glutGet(GLUT_WINDOW_HEIGHT));

	turret_elevation_vertical =  (relative_y*(-90));
	turret_elevation_lateral = -90 + relative_x*180;

	 /*Now Display the figure*/
	glutPostRedisplay();


}
/**
*@func:		mouse_button_detect
*
*
*@description:	the function helps change the elevation of the tank
*		turret
*@params:
*
*@return: void
*
*@todo:
*
*/

void mouse_button_detect(int button, int state, int x, int y)
{
	switch(button)
	{
		case GLUT_LEFT_BUTTON:
		switch(state)
		{
			case GLUT_DOWN:
			if(tank_mode)
			{
			//	printf("Left mouse button clicked \n");
				cannonFire();
			//glutDisplayFunc(displayCrack);
			}
			if(flight_mode)
			{
				missileFire();
			}
			break;
		}
		break;
		case GLUT_RIGHT_BUTTON:
                switch(state)
                {
                        case GLUT_DOWN:
			if(tank_mode)
			{
				changeTurretElevation(x,y);
			}

                        break;
                }
                break;
	}
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
		if(tank_mode)
		{
			if( (tankCoordinateX <= - 158 || tankCoordinateX  >=  158 ) )
			{
			 if( ( 157 <= tankCoordinateX <= 158) && ((-180  < tankRotationAngle < 0)||( 180 < tankRotationAngle < 360)) )
			 {
				tankCoordinateY  += 0.8*cos((PI/180)*(tankRotationAngle));
				tankCoordinateX  -= 0.8*sin((PI/180)*(tankRotationAngle));
			 }

			 if( -158 <= tankCoordinateX <= -157)
                         {
                               tankCoordinateY  += 0.8*cos((PI/180)*(tankRotationAngle));
                               tankCoordinateX  -= 0.8*sin((PI/180)*(tankRotationAngle));
                         }

			 if(tankCoordinateX <  -158 || tankCoordinateX > 158)
                         {
                                        tankCoordinateY  += 0.8*cos((PI/180)*(tankRotationAngle));
                                        tankCoordinateX  -= 0.8*sin((PI/180)*(tankRotationAngle));
                         }

			 }
			else if( -158 <  tankCoordinateX && tankCoordinateX  < 158)
			{
				if( (tankCoordinateY <= -218 ) || ( tankCoordinateY >= 217 ) )
				{
					tankCoordinateY  += 0.8*cos((PI/180)*(tankRotationAngle));
                                	tankCoordinateX  -= 0.8*sin((PI/180)*(tankRotationAngle));
				}
				else if(( -218 <= tankCoordinateY &&  tankCoordinateY <= -217) && ( 90 < tankRotationAngle && tankRotationAngle < 270))
                                {
                                        tankCoordinateY  += 0.8*cos((PI/180)*(tankRotationAngle));
                                        tankCoordinateX  -= 0.8*sin((PI/180)*(tankRotationAngle));
                                }
			}
		}
		printf("X:%f \t Y:%f\n ", tankCoordinateX, tankCoordinateY );
                glutPostRedisplay();
                break;

                case GLUT_KEY_DOWN:
                alpha--;
		EX -= Cx*dt; //Update the eye vector based on the camera vector
		EY -= Cy*dt;
                theta %= 360;/*Helps angles be within the margin of 360*/
                alpha %= 360;/*Helps angles be within the margin of 360*/

		if(tank_mode)
		{
			if( (tankCoordinateX <= - 154 || tankCoordinateX >=  154))
			{

                              		tankCoordinateY  -= 0.8*cos((PI/180)*(tankRotationAngle));
                                	tankCoordinateX  += 0.8*sin((PI/180)*(tankRotationAngle));
			}
			else if(tankCoordinateX >= - 158 && tankCoordinateX <= 158)
                        {
                                if(tankCoordinateY <= -218 || tankCoordinateY >= 218)
                                {
                                        tankCoordinateY  -= 0.8*cos((PI/180)*(tankRotationAngle));
                                        tankCoordinateX  += 0.8*sin((PI/180)*(tankRotationAngle));
                                }
				else if(( -218 <= tankCoordinateY &&  tankCoordinateY <= -216) && (-90 < tankRotationAngle && tankRotationAngle < 90))
                                {
                                        tankCoordinateY  -= 0.8*cos((PI/180)*(tankRotationAngle));
                                        tankCoordinateX  += 0.8*sin((PI/180)*(tankRotationAngle));
                                }

			else if(( 218 >= tankCoordinateY&&tankCoordinateY >= 216)&&((90<tankRotationAngle&&tankRotationAngle<270)||(-90 > tankRotationAngle && tankRotationAngle > -270)))
                                {
                                        tankCoordinateY  -= 0.8*cos((PI/180)*(tankRotationAngle));
                                        tankCoordinateX  += 0.8*sin((PI/180)*(tankRotationAngle));
                                }

                        }

			printf("X:%f \t Y:%f\n ",tankCoordinateX,tankCoordinateY );
		}
                glutPostRedisplay();
                break;

		case GLUT_KEY_LEFT:
                theta++;
		rot = rot + 1;
		if(tank_mode)
		{
			tankRotationAngle += 1;
			printf(" Tank Rotation Angle :%d\n",tankRotationAngle);
		}
                theta %= 360;/*Helps angles be within the margin of 360*/
                alpha %= 360;/*Helps angles be within the margin of 360*/
		tankRotationAngle %= 360;
                glutPostRedisplay();
                break;

                case GLUT_KEY_RIGHT:
                theta--;
		rot = rot - 1;
		if(tank_mode)
		{
           		tankRotationAngle -= 1;
			printf(" Tank Rotation Angle :%d\n",tankRotationAngle);
		}

                theta %= 360;/*Helps angles be within the margin of 360*/
                alpha %= 360;/*Helps angles be within the margin of 360*/
		tankRotationAngle %= 360;
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
                gluPerspective(Field_of_View , widht2height , dimension/4, 5000*dimension);
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
			light = 1;
		}

		else if( displayMode == 1)
		{
		      	displayMode = 2;	/* If the mode is 1, make it 0*/
			light = 1;
		}

		else if( displayMode == 2)
                {

                        displayMode = 3;                /* If the mode is 2, make it back to 0*/
			light = 1;
                }

		else if( displayMode == 3)
                {

                        displayMode = 4;                /* If the mode is 2, make it back to 0*/
			light = 1;
                }

		else if( displayMode == 4)
                {

                        displayMode = 0;                /* If the mode is 2, make it back to 0*/
			light = 1;
                }



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

		case '+':
			       	       /* Option to change circumference of light source path */
                       	EZ = EZ + 1;
			if(flight_mode)
				EplaneZ += 1;

		break;

		 case '-':
		                      /* Option to change circumference of light source path */
                        EZ = EZ - 1;
			if(flight_mode)
				EplaneZ -= 1;

                break;

		case '2':
			if(flight_mode)
				roll -= 1;
		break;

		case '8':
			if(flight_mode)
                        	roll += 1;
                break;

		case '6':
			if(flight_mode)
                        	pitch -= 1;
                break;

                case '4':
			if(flight_mode)
                        	pitch += 1;
                break;

		case '1':
			if(flight_mode)
                        	yaw -= 1;
                break;

                case '3':
			if(flight_mode)
                        	yaw += 1;
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
*@func:         drawWall
*
*@description:  
*
*@param:        void
*
*@return:       void
*/

void drawWall(double x, double y, double z,double delta_x, double delta_y, double delta_z, double th)
{

        glPushMatrix();
        glTranslated(x, y, z);
        glScaled(delta_x, delta_y, delta_z);
        glRotated(th,0,0,1);


	/* Adding the barbed wire*/
	drawBarbedwire(4, 1700,-850,-850,65,1,1,1,-90,255, 255,255,0);
	drawBarbedwire(4, 1700,850,-850,65,1,1,1,-90,255, 255,255,0);

	glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,texture[0]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glColor3ub(200,100,0);

        drawCubewithoutTexture(-850,0,20,1,850,40,0);

	/* Adding the barbed wire */

        drawCubewithoutTexture(850,0,20,1,850,40,0);

	/* Adding the barbed wire */

        drawCubewithoutTexture(0,-850,20,850,1,40,0);

	/* Adding the barbed wire */

        drawCubewithoutTexture(0,850,20,850,1,40,0);
        glPopMatrix();
}

/**
*@func:         DrawSkyBox
*
*@description:  A program that helps us conmpute the vertices using cosine sine functions that inturn helps us render shapes
*
*@param:        double theta,double alpha
*
*@return:       void
*
*/

void drawSkybox(double x,double y,double z,double delta_x,double delta_y,double delta_z, double th)
{

        glPushMatrix();
        //  Offset
        glTranslated(x,y,z);
        glRotated(th,0,1,0);
        glScaled(delta_x,delta_y,delta_z);
	glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D,texture[2]);
        //  Cube
        glBegin(GL_QUADS);
	glColor3ub(150,150,255);
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
        glTexCoord2f(0.0, 0.0);
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
	glDisable(GL_TEXTURE_2D);
	ErrCheck("Skybox");
}

/**
*@func:		drawSurface
*
*@description:	
*
*@params:	double x. double y, double Z, double delta_x, double delta_y, double delta_z)
*
*@return:	void
*
*/

void drawSurface(double x, double y, double z, double delta_x, double delta_y, double delta_z)
{
	glPushMatrix();
	glTranslated(x, y, z);
        glScaled(delta_x, delta_y, delta_z);
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glColor3ub(0,0,0);
	glNormal3f(0, 0, 1);
	glVertex3f(1,1, 0);
	glVertex3f(-1,1, 0);
	glVertex3f(-1,-1, 0);
        glVertex3f(1,-1, 0);
	glEnd();
	glPopMatrix();
}

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


//	double turret_elevation_lateral_abs = (turret_elevation_lateral > 90 )?(180 - turret_elevation_lateral):(turret_elevation_lateral_abs);

//	glEnable(GL_CULL_FACE); 

   	/*Erase the window and the depth buffer*/
   	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	/* Enable Z-buffering in OpenGL*/
   	glEnable(GL_DEPTH_TEST);

	/* Smoother polygons */
	glEnable(GL_POLYGON_SMOOTH);

	

   	/*  Undo previous transformations*/
   	glLoadIdentity();



	ErrCheck("Before Skybox");
	glPushMatrix();

//	gluLookAt(0, 0, 0, Cx, Cy , EZ, 0, 0, 1);
	gluLookAt(0, 0, 0, 1, 1 , 1, 1, 0, 0);

	drawSkybox(0,0,0,50000,50000,50000,0);
	glPopMatrix();
	ErrCheck("After Skybox");



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
		flight_mode = 0;
		tank_mode = 1;
                Print("tank view ");
		EtankY = tankCoordinateY /* - 50 * cos((PI/180)*tankRotationAngle)*/ ;
		EtankX = tankCoordinateX /* - 50 * sin((PI/180)*tankRotationAngle) */ ;
		CtankX = -8 * dimension * sin((PI/180)*tankRotationAngle); //Ajust the camera vector based on rot
      		CtankY = +8 * dimension * cos((PI/180)*tankRotationAngle);
		// Orient the scene so it imitates first person movement
    		gluLookAt(EtankX + 50 * sin((PI/180)*tankRotationAngle)  ,EtankY - 50 * cos((PI/180)*tankRotationAngle), EtankZ,/* CtankX +*/ EtankX ,/*CtankY +*/ EtankY , EtankZ, 0, 0, 1);
                break;

		case 3: /* This is for the plane projection */
		flight_mode = 1;
		tank_mode = 0;
		Print(" Airplane view ");
		EplaneX = planeCoordinateX;
		EplaneY = planeCoordinateY;
		EplaneZ = planeCoordinateZ + 30 ;
                // Orient the scene so it imitates first person movement
                gluLookAt(EplaneX + 50 * sin((PI/180)*pitch), EplaneY  - 50 * cos((PI/180)*pitch) , EplaneZ, EplaneX, EplaneY, EplaneZ, 0, 0, 1);
                break;


		case 4: /* This is for the first person mode of projection */
                flight_mode = 0;
                tank_mode = 0;
                Print("First person view ");
                Cx = +8 * dimension * sin((PI/180)*rot); //Ajust the camera vector based on rot
                Cy = -8 * dimension * cos((PI/180)*rot);
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
//        	float coordinates[]  = {distance*cos((PI/180)*azhimuth), distance*sin((PI/180)*azhimuth), light_elevation, 1.0};
		float coordinates[]  = { 5000 * cos((PI/180)*angleSun)  , 0  ,5000 * sin((PI/180)*angleSun)  , 1.0};
        	//  Draw light position as ball (still no lighting here)
        	glColor3f(1,1,1);
        	drawSun(coordinates[0],coordinates[1],coordinates[2] , 0.2);
//		drawSun(2000 * cos((PI/180)*angleSun),0,2000 * sin((PI/180)*angleSun), 0.2);


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


//	drawWall(0, 0,0,1, 1, 1, 0);
	drawNewWall(texture);

	drawSurface(0,0, 0, 50000, 50000, 50000);
//	drawBuilding(0,0,0,8,8,8);
	drawNewBuilding(0, 0, 0, 1, 1, 1,texture);
	drawTank(tankCoordinateX,tankCoordinateY ,0,1,1,1,turret_elevation_vertical,turret_elevation_lateral,FireBallRad,tankRotationAngle);
	Plane(planeCoordinateX,planeCoordinateY,planeCoordinateZ , 10, 10, 10,yaw, roll,pitch, blast_rad,texture );
//	drawCycloid(4, 100,0,-450, 60,1,1,1,-90,150, 150,150,0);
//	drawBarbedwire(4, 100,0,-450, 60,1,1,1,-90,150, 150,150,0);
//	drawCrack( -100, -200,40,20,20,20,0,texture);
	drawFlag(0, -200, 170, 10, 10, 10,0, texture);
	ErrCheck("Display");
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
        glutInitWindowPosition(0,0);

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


	/* Mouse button work */
	glutMouseFunc(mouse_button_detect);

        /*Use arrow keys to change the viewing angles*/
        glutSpecialFunc(arrow_keys_move);

//	obj = LoadOBJ("objects/Soldier.obj");


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
	texture[14]=LoadTexBMP("textures/building_bitmap_image.bmp");
	texture[15]=LoadTexBMP("textures/BrokenGlass.bmp");
	texture[16]=LoadTexBMP("textures/ussr_flag.bmp");
	texture[17]=LoadTexBMP("textures/nazi_flag.bmp");

        /*glutMainLoop enters the GLUT event processing loop*/
        glutMainLoop();

        return 0;


}

