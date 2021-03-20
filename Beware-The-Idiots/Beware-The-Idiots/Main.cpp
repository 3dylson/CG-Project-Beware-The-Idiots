#include <GL/glut.h>


void display();


int main(int argc,char**argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);

	glutInitWindowPosition(200, 100);
	glutInitWindowSize(500, 500);	
	
	glutCreateWindow("Beware The Idiots");

	glutDisplayFunc(display);
	
	glutMainLoop();
	
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	
	//draw

	
	glFlush();
	
}
