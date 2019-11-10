
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>


#include "../headers/basic_shapes.h"
#include "../headers/buildings.h"



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
        drawDome(0,0,7,4,4,4,90);
	drawCube(0,0,0,9,5,7.3,0);
	glPopMatrix();

}