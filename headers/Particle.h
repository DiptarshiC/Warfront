#ifndef __PARTICLE_H__
#define __PARTICLE_H__


typedef struct Particle_t{

	double pos[3];
	double speed[3];
	float size, angle, weight;
	float life;
}Particle;






#endif /*__PARTICLE_H__*/
