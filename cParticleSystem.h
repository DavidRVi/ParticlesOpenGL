#pragma once

#include "cParticle.h"
#include "cTexture.h"
#define NUM_PARTICLES	500
#define PARTICLE_SIZE	0.2f

class cParticleSystem
{
public:
	cParticleSystem();
	virtual ~cParticleSystem();

	bool Load();
	void Update();
	void Render();

private:
	bool MakeTexture();
	void InitParticle(int i);

	cTexture text;

	cParticle particle[NUM_PARTICLES];
	unsigned int tex_id;
	float time_alive;
};
