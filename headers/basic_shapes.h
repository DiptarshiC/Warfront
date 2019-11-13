#ifndef __BASIC_SHAPES_H__
#define __BASIC_SHAPES_H__



void Vertex(double theta,double alpha);
void drawCube(double x,double y,double z,double delta_x,double delta_y,double delta_z, double th);
void drawCylinder(double radius, double height,double x1, double y1, double z1,double delta_x,double delta_y,double delta_z,double th,GLubyte R, GLubyte G,GLubyte B,double alpha );
void drawDome(double x, double y, double z, double delta_x, double delta_y, double delta_z,double th);
void drawSphere(double x, double y, double z, double delta_x, double delta_y, double delta_z);
void drawCone(double x, double y, double z, double delta_x, double delta_y, double delta_z,double theta);

#endif /*__BASIC_SHAPES_H__*/
