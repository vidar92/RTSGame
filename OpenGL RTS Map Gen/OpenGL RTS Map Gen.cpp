// OpenGL RTS Map Gen.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ShaderLoader.h"
#include <Windows.h>
#include <glew.h>
#include <wglew.h>
#include <gl\GL.h>
#include <GL\GLAux.h>
#include <GL\glut.h>
#include "Terrain.h"



void glInit();
void render();
void reshape(int,int);
void timer(int);
Terrain* t;

int _tmain(int argc, char* argv[])
{
	int windows =0;
	  glewExperimental = GL_TRUE;
	
	  


	glutInit(&argc,argv);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB);
	glutInitContextVersion(1,1);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(800,600);


	glutCreateWindow("RTS generator");
	t= new Terrain(2,2);


	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glInit();
	printf("%s",glGetString(GL_VERSION));
	timer(1);




	
	//GLuint program = LoadShader("shader.vert", "shader.frag");
	//glUseProgram(program);

	glutMainLoop();

	return 0;
}

void PutLight()
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
  

}

void glInit()
{

	glClearColor(1,0,0,1);
//	glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	  glEnable( GL_POINT_SMOOTH );
    glEnable( GL_BLEND );
	 glPointSize( 6.0 );
	  
	 glEnable(GL_TEXTURE_2D);
}

double rot =0;

int frames = 0;

int frame,currenttime,timebase;
void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glRotated(0.5,0,1,0);
	t->Draw(3,3);


	//////////USUN/////////////////




				   


	frame++;
	//t
	//glutSolidTeapot(100);
	//get the current time
	currenttime = glutGet(GLUT_ELAPSED_TIME);
 
	//check if a second has passed
	if (currenttime - timebase > 1000) 
	{
		char title[100];
		sprintf(title, "FPS: %4.2f",	frame*1000.0/(currenttime-timebase));
		glutSetWindowTitle(title);
	 	timebase = currenttime;		
		frame = 0;
	}

	glFlush();
	glutSwapBuffers();
	
}

void timer(int) 
{
    glutPostRedisplay();
    glutTimerFunc(1000/50, timer, 0);
}

void reshape(int w,int h)
{
	if(h==0)
	{
		h=1;
	}

	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 1500.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 300.0, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}