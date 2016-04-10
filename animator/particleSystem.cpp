#pragma warning(disable : 4786)

#include "particleSystem.h"

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cmath>

#include "modelerdraw.h"
#include <FL/gl.h>
#include "modelerui.h"

using namespace std;

static float prevT;

/***************
 * Constructors
 ***************/

ParticleSystem::ParticleSystem() 
{
	// TODO
	simulate = false;
}




/*************
 * Destructor
 *************/

ParticleSystem::~ParticleSystem() 
{
	// TODO
}


/******************
 * Simulation fxns
 ******************/

/** Start the simulation */
void ParticleSystem::startSimulation(float t)
{
	// TODO

	// These values are used by the UI ...
	// negative bake_end_time indicates that simulation
	// is still progressing, and allows the
	// indicator window above the time slider
	// to correctly show the "baked" region
	// in grey.
	//ptcs.clear();
	if(firstTime){
		for(int i=0; i<MaxParticles; i++){
			Particle *p1 = new Particle();
			float h1 =ModelerApplication::Instance()->GetControlValue(4);
			p1->pos = Vec3f(0.5, 0.6+2*h1, 0.6);
			p1->speed = Vec3f(0.0, 1.0, 0.0)*(1.0+3*(rand()%100)/100.0);
			p1->life = 30.0*(rand()%100)/100.0;
			p1->mass = 1 + 3.0*(rand()%100)/100;
			ptcs.push_back(*p1);
			delete(p1);
		}
		// for(int i=0; i<MaxParticles; i++){
		// 	Particle *p1 = new Particle();
		// 	float h1 =ModelerApplication::Instance()->GetControlValue(4);
		// 	p1->pos = Vec3f(0.5, 0.6+2*h1, 0.6);
		// 	p1->speed = Vec3f(0.0, 1.0, 0.0)*(1.0+3*(rand()%100)/100.0);
		// 	p1->life = 30.0*(rand()%100)/100.0;
		// 	p1->mass = 1 + 3.0*(rand()%100)/100;
		// 	ptcsG.push_back(*p1);
		// 	delete(p1);
		// }
		firstTime = false;
	}else{
		for(int i=0; i<MaxParticles; i++){
			float h1 =ModelerApplication::Instance()->GetControlValue(4);
			ptcs[i].pos = Vec3f(0.5, 0.6+2*h1, 0.6);
			//p1->prePos = Vec3f(0.5, 0.6+2*h1, 0.6);
			ptcs[i].speed = Vec3f(0.0, 1.0, 0.0)*(1.0+3*(rand()%100)/100.0);
			//p1->preSpeed = Vec3f(0.0, 1.0, 0.0);
			ptcs[i].life = 30.0*(rand()%100)/100.0;
			ptcs[i].mass = 1 + 3.0*(rand()%100)/100;;
		}
	}
	bake_start_time = t;
	bake_end_time = -1;
	simulate = true;
	dirty = true;

}

/** Stop the simulation */
void ParticleSystem::stopSimulation(float t)
{
	// TODO

	// These values are used by the UI
	//bake_start_time = -1;

	for(int i=0; i<MaxParticles; i++){
		ptcs[i].prePos = ptcs[i].pos;
		ptcs[i].preSpeed = ptcs[i].speed;
	}

	bake_end_time = t;
	simulate = false;
	dirty = true;

}

/** Reset the simulation */
void ParticleSystem::resetSimulation(float t)
{
	// TODO

	// These values are used by the UI
	simulate = false;
	dirty = true;

}

/** Compute forces and update particles **/
void ParticleSystem::computeForcesAndUpdateParticles(float t)
{
	// TODO

	//need to call bakeParticles fxn

	// if(simulate){//max


	// 	bakeParticles(t);


	// }

	// Debugging info
	if( t - prevT > .04 )
		//printf("(!!) Dropped Frame %lf (!!)\n", t-prevT);
	prevT = t;
}


/** Render particles */
void ParticleSystem::drawParticles(float t)
{
	// TODO
	//float gravity = -9.8;
	//float velocity = gravity * t;

	for(int i=0; i<MaxParticles; i++){

		if(ptcs[i].life>30){
			float h1 =ModelerApplication::Instance()->GetControlValue(4);
			ptcs[i].pos = Vec3f(0.5, 0.6+2*h1, 0.6);
			//p1->prePos = Vec3f(0.5, 0.6+2*h1, 0.6);
			ptcs[i].speed = Vec3f(0.0, 1.0, 0.0)*(1.0+3*(rand()%100)/100.0);
			//p1->preSpeed = Vec3f(0.0, 1.0, 0.0);
			ptcs[i].life = 30.0*(rand()%100)/100.0;
			ptcs[i].mass = 1 + 3.0*(rand()%100)/100;;
		}

		setDiffuseColor(0.5, 0.5, 0.5);
	    setAmbientColor(0.6, 0.6, 0.6);
	    //for(int i=0;i<2;i++){
		bool animate = ModelerApplication::Instance()->GetUI()->getAnimating();

	    if(animate){//simulate

		//max:change everything into p1's attribute
			float deltaT = t - prevT;
			ptcs[i].speed = ptcs[i].speed + windForce/ptcs[i].mass*deltaT;
			ptcs[i].pos = ptcs[i].pos + ptcs[i].speed*deltaT;
			float h1 =ModelerApplication::Instance()->GetControlValue(4);

		    glPushMatrix();
		        //glTranslatef(0.5, 0.6+2*h1 - 1.0/2*velocity*t, 0.6);
		        //glTranslatef(0.5 + position[0], 0.6+2*h1 +position[1], 0.6 +position[2]);
		        glTranslatef(ptcs[i].pos[0], ptcs[i].pos[1], ptcs[i].pos[2]);
		        drawSphere(0.15);
		    glPopMatrix();
		ptcs[i].life += 1;
		}else{
			glPushMatrix();
		        glTranslatef(ptcs[i].prePos[0], ptcs[i].prePos[1], ptcs[i].prePos[2]);
		        drawSphere(0.15);
		    glPopMatrix();
		}
		
	}

	setDiffuseColor(0.5, 0.5, 0.5);
    setAmbientColor(0.6, 0.6, 0.6);
	glPushMatrix();
	    //glTranslatef(ptcs[i].pos[0], ptcs[i].pos[1], ptcs[i].pos[2]);
	    glTranslatef(3, 3, 3);

	    drawSphere(1);
	glPopMatrix();

}




/** Adds the current configuration of particles to
  * your data structure for storing baked particles **/
void ParticleSystem::bakeParticles(float t) 
{
	// TODO
}

/** Clears out your data structure of baked particles */
void ParticleSystem::clearBaked()
{
	// TODO
}




