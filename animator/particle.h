
#ifndef PARTICLE_H
#define PARTICLE_H

class Particle
{
	vec3f pos, speed;
	unsigned char r,g,b,a; // Color
	//float size, angle, weight;
	float life; // Remaining life of the particle. if < 0 : dead and unused.

};

#endif

