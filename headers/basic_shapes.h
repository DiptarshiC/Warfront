#ifndef __BASIC_SHAPES_H__
#define __BASIC_SHAPES_H__



void Vertex(double theta,double alpha);
void drawCube(double x,double y,double z,double delta_x,double delta_y,double delta_z, double th);
void drawCylinder(GLfloat radius, GLfloat height, char R,char G, char B);
void drawDome(double x, double y, double z, double delta_x, double delta_y, double delta_z,double th);
void drawSphere(double x, double y, double z, double delta_x, double delta_y, double delta_z);
void drawCone(double x, double y, double z, double delta_x, double delta_y, double delta_z,double theta);

#endif /*__BASIC_SHAPES_H__*/
