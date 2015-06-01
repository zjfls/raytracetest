#include "stdafx.h"
#include "SimpleGLApplication.h"
//#include "gl/glew.h"
//#include <gl/glut.h>
//#include "gl/freeglut.h"
//#include "glfw/glfw3.h"
#include "gl/glew.h"
#include "gl/freeglut.h"
#include "gl/GL.h"


SmartPointer<SimpleGLApplication> Singleton<SimpleGLApplication>::_instance = nullptr;

SimpleGLApplication::SimpleGLApplication()
{
	
}


SimpleGLApplication::~SimpleGLApplication()
{
}

void SimpleGLApplication::OnInit()
{
	GlWindow(200, 300);
}

void SimpleGLApplication::SetupScene()
{

}

void SimpleGLApplication::OnEndInit()
{

}

void SimpleGLApplication::Run()
{
	glutMainLoop();
}

void SimpleGLApplication::GlWindow(int width, int height)
{
	glutInit(&m_argc, m_argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow("3D Tech- GLUT Tutorial");
	glutDisplayFunc(RenderScene);
}

void SimpleGLApplication::RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(0.0, 0.5, 0.0);
	glEnd();
	glFlush();
}
