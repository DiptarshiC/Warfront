#ifndef __VEHICLES_H__
#define	__VEHICLES_H__




void drawTank(double x,double y,double z,double delta_x,double delta_y,double delta_z, double turret_Front_Elevation, double turret_Side_Elevation, double FireBallRad, int turnAngle);
void Plane(double x, double y, double z, double delta_x, double delta_y, double delta_z, double horizontal_tilt, double vertical_tilt, double lateral, double blast_rad, int textures[]);
void initializAsteroids( int ast_pos[][3]);
void drawASteroid(int ast_pos[][3]);

#endif /*__VEHICLES_H__*/
