
#pragma once

#include "cParticleSystem.h"
#include "cParticleSystemTwo.h"
#include <stdlib.h>
#include "cParticleSystem.h"
#include <GL/glut.h>
#include <math.h>

class cScene  
{
public:
	cScene();
	virtual ~cScene();

	bool Init();
	void Update();
	void Render();

private:
	cParticleSystem ParticleSystem;
	cParticleSystemTwo ParticleSystem2;
	float timer;
};

