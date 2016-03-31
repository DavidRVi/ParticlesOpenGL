
#pragma once

#include "cVector3D.h"

class cParticle
{
public:

	cVector3D pos;	// Position
	cVector3D dir;	// Direction
	float life;		// Life
	float fade;		// Fade speed
	float particle_size;	//particle size
};