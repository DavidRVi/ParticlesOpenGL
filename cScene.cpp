
#include "cScene.h"
#include <GL/glut.h>

cScene::cScene() {}
cScene::~cScene(){}

bool cScene::Init()
{
	if(!ParticleSystem.Load()) return false;
	if (!ParticleSystem2.Load()) return false;

	return true;
}
void cScene::Update()
{
	ParticleSystem.Update();
	ParticleSystem2.Update();
}

void cScene::Render()
{
	glTranslatef(0.0f,0.0f,-10.0f);

	ParticleSystem.Render();
	ParticleSystem2.Render();
}
