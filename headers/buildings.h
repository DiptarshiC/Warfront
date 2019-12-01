#ifndef __BUILDINGS_H__
#define __BUILDINGS_H__




void drawBarbedwire(double radius, double height, double x1, double y1 ,double z1, double delta_x, double delta_y, double delta_z, double th, GLubyte R, GLubyte G,GLubyte B, double alpha );

void drawBuilding(double x, double y, double z, double delta_x, double delta_y, double delta_z, int texture[]);
void drawNewBuilding(double x, double y, double z, double delta_x, double delta_y, double delta_z, int texture[]);

void drawSwastika(double x, double y, double z, double delta_x, double delta_y, double delta_z);

void drawNewWall(int texture[]);

void drawCrack(double x, double y, double z,double delta_x, double delta_y, double delta_z,int th, int texture[]);

void drawFlag( double x, double y, double z,  double delta_x, double delta_y, double delta_z,int th, int textures[]);

#endif /*__BUILDINGS__H*/
