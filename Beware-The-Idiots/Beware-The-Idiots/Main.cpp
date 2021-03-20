#include <GL/glut.h>


void display();
void reshape(int, int);

void init()
{
	//range of colors: [0,1]
	glClearColor(0.0, 0.0, 0.0, 1.0);
}


int main(int argc,char**argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);

	glutInitWindowPosition(200, 100);
	glutInitWindowSize(500, 500);	
	
	glutCreateWindow("Beware The Idiots");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	init();
	
	glutMainLoop();
	
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	
	//draw

	
	glFlush();
	
}

void reshape(const int w, const int h)
{
	//viewport
	glViewport(0, 0, static_cast<GLsizei>(w), static_cast<GLsizei>(h));
	//projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(-10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);
}

