

#include <windows.h> 
#include <stdio.h>
#include <stdlib.h>
#include <gl/glut.h>
#include "cScene.h"

//Delete console
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

cScene Scene;

//User Input Control
bool enable_texture;
bool enable_blend;
bool enable_depth;
bool enable_write;

//OpenGL initializations
bool init(void)
{
	bool res;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// Background

	enable_texture = true;
	glEnable(GL_TEXTURE_2D);

	enable_depth = false;
	glDisable(GL_DEPTH_TEST);

	enable_write = true; 
	glDepthMask(GL_TRUE);

	enable_blend = true;	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	res = Scene.Init();

	return res;
}

//Rendering
void GameRender(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	Scene.Render();

	glutSwapBuffers();					//Swap makes rendering visible
}

//Reshaping handler (required even in fullscreen-only modes)
void GameReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Calculate the aspect ratio and set the clipping volume
	gluPerspective(45, (float)w / (float)h, 0.1, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//Keyboard handler (normal keys)
void GameKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27: exit(0);	break;
	}
}

//Keyboard handler for special keys (like arrow keys and function keys)
void GameSpecialKeys(int a_keys, int x, int y)
{
	switch (a_keys)
	{
		case GLUT_KEY_F1:	enable_texture = !enable_texture;
							if (enable_texture)	glEnable(GL_TEXTURE_2D);
							else				glDisable(GL_TEXTURE_2D);
							break;
		case GLUT_KEY_F2:	enable_blend = !enable_blend;
							if (enable_blend)	glEnable(GL_BLEND);
							else				glDisable(GL_BLEND);
							break;
		case GLUT_KEY_F3:	enable_depth = !enable_depth;
							if (enable_depth)	glEnable(GL_DEPTH_TEST);
							else				glDisable(GL_DEPTH_TEST);
							break;
		case GLUT_KEY_F4:	enable_write = !enable_write;
							if (enable_write)	glDepthMask(GL_TRUE);
							else				glDepthMask(GL_FALSE);
							break;
	}
	char s[128];
	sprintf(s, "(F1) Texture: %s, (F2) Blending: %s, (F3) Z-Test: %s, (F4) Z-buff writeable: %s",
				enable_texture ? " ON" : "OFF",
				enable_blend ? " ON" : "OFF",
				enable_depth ? " ON" : "OFF",
				enable_write ? " ON" : "OFF");
	glutSetWindowTitle(s);
}

//Check the user input and performs the rendering
void GameLoop()
{
	//Update
	Scene.Update();
	//Do The Rendering
	GameRender();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);										// GLUT initialization
	glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE);	// Display mode (rgb and double buffered)
	
	glutInitWindowSize(800,600);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Particle System");

	glutSetCursor(GLUT_CURSOR_NONE);							// Make the default cursor disappear
	if(!init())													// Initialization
	{
		printf("\nError initializing game!\n");
		exit(0);
	}
	glutDisplayFunc(GameRender);								// Register the display function
	glutReshapeFunc(GameReshape);								// Register the Reshape handler
	glutKeyboardFunc(GameKeyboard);								// Register the keyboard handler
	glutSpecialFunc(GameSpecialKeys);							// Register special keys handler
	glutIdleFunc(GameLoop);										// Process user input and does rendering
	glutMainLoop();												// Go to GLUT main loop
}