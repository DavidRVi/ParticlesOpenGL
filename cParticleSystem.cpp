#include <stdlib.h>
#include "cParticleSystem.h"
#include <GL/glut.h>
#include <math.h>

cParticleSystem::cParticleSystem() {}
cParticleSystem::~cParticleSystem(){}

bool cParticleSystem::Load()
{
	int i;

	if(!text.Load("p01.png")) return false;

	// Initializes all the particles
	for(i=0;i<NUM_PARTICLES;i++)
	{
		InitParticle(i);
	}
	
	return true;
}

bool cParticleSystem::MakeTexture()
{
	int width  = 256,
		height = 256;

    GLubyte *texels, *p;	// GLubyte => 0..255

    int size;
    int i,j;
	int dist, color;

	//Size = R * G * B * A * width * height * byte
    size   = 4 * width * height * sizeof(GLubyte);

    texels = (GLubyte *) malloc(size);
    if(texels==NULL) return false;

    p = texels;

    for(i=0;i<height;++i) 
    {
		for(j=0;j<width;++j) 
		{
			dist = (int)hypot(float(i - (height / 2)),float(j - (width / 2)));

			color = 255-(dist*2);
			if (color < 0) color = 0;
			p[0] = color;
			p[1] = color;
			p[2] = color;
			p[3] = color;   
			p+=4;
		}
    }

	glGenTextures(1, &tex_id);
	glBindTexture(GL_TEXTURE_2D,tex_id);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texels);

    free(texels);
    
    return true;
}

void cParticleSystem::InitParticle(int i)
{
	float v,angle;

	particle[i].particle_size = ((float)(rand() % 10) + 0.001f) / 50.0f;
	// Give all the particles full life
	particle[i].life = 1.0f;

	// Random fade speed = 0.005..0.095
	particle[i].fade = ((float)(rand()%100) / 10000.0f) + 0.005f;
	//particle[i].fade = 0.005f;
	
	// Speed of the particle  = 1..9
	v = (float((rand()%9))+1);  

	// Angle of the particle = 0..359
	angle = float(rand()%360);

	// Set (x,y,z) position = (0,0,0)
	particle[i].pos = cVector3D(0.0f,0.0f,0.0f);
	time_alive = glutGet(GLUT_ELAPSED_TIME);

	// Set (x,y,z) velocity = (-9..9, -9..9, -1..1 )
	//particle[i].dir = cVector3D( sin(angle) * v, cos(angle) * v, 0 );
	particle[i].dir = cVector3D(5.0f*cos(time_alive), 10 , 10.0f*sin(time_alive));
}

void cParticleSystem::Update()
{
	int loop;

	for (loop = 0; loop < NUM_PARTICLES; loop++) // Loop Through All The Particles
	{
		particle[loop].pos.x += particle[loop].dir.x / 250;  // Move on the X axis by X speed
		particle[loop].pos.y += particle[loop].dir.y / 250;  // Move on the Y axis by Y speed
		particle[loop].pos.z += particle[loop].dir.z / 250;  // Move on the Z axis by Z speed

		// Slow down the particles
		particle[loop].dir.x *= 0.99f;
		particle[loop].dir.y *= 0.99f;
		particle[loop].dir.z *= 0.99f;

		particle[loop].life -= particle[loop].fade;	// Reduce particles life by 'fade'

		if (particle[loop].life < 0.05f)				// If particle is burned out
		{
			InitParticle(loop);
		}
	}
	time_alive = glutGet(GLUT_ELAPSED_TIME) - time_alive;
}
void cParticleSystem::Render()
{
	int loop;
	float x,y,z;

	//glBindTexture(GL_TEXTURE_2D,tex_id);
	glBindTexture(GL_TEXTURE_2D, text.GetID());

	for(loop=0; loop<NUM_PARTICLES; loop++) // Loop Through All The Particles
	{
		x = particle[loop].pos.x;
		y = particle[loop].pos.y;
		z = particle[loop].pos.z;

		// Draw the particle using our RGB values, fade the particle based on it's life
		glColor4f(particle[loop].dir.x, particle[loop].life, particle[loop].dir.z, particle[loop].life);

		float particle_size = particle[loop].particle_size;
		glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2f(1,1);	glVertex3f(x+particle_size,y+particle_size,z);
			glTexCoord2f(0, 1);	glVertex3f(x - particle_size, y + particle_size, z);
			glTexCoord2f(1, 0);	glVertex3f(x + particle_size, y - particle_size, z);
			glTexCoord2f(0, 0);	glVertex3f(x - particle_size, y - particle_size, z);
		glEnd();
	}
}
