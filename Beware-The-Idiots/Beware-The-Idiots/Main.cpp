#include <GL/glut.h>


void display();
void reshape(int, int);
void timer(int);

void init()
{
	//gama de cores: [0,1]
	glClearColor(0.0, 0.0, 0.0, 1.0);
}


int main(int argc,char**argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	glutInitWindowPosition(200, 100);
	glutInitWindowSize(500, 500);	
	
	glutCreateWindow("Beware The Idiots");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(0,timer,0);
	init();
	
	glutMainLoop();

	return 0;
}

float x_position = -10.0;
int state = 1;

/**
 * \brief Função para exibir tudo
 */
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	//em pixels
	glPointSize(10.0);
	//desenhar
	glBegin(GL_POLYGON);

	glVertex2f(x_position,1.0);
	glVertex2f(x_position,-1.0);
	glVertex2f(x_position+2.0,-1.0);
	glVertex2f(x_position+2.0,1.0);

	//
	glEnd();
	
	
	glutSwapBuffers();
	
}

/**
 * \brief função para remodelar
 * \param w largura
 * \param h altura
 */
void reshape(const int w, const int h)
{
	//janela de exibição
	glViewport(0, 0, static_cast<GLsizei>(w), static_cast<GLsizei>(h));
	//projeção
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(-10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);
}

void timer(int)
{
	//chamar a função display
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0);

	switch (state)
	{
	case 1:
		if (x_position < 8)
			x_position += 0.15;
		else
			state = -1;
		break;
	case -1:
		if (x_position > -10)
			x_position -= 0.15;
		else state = 1;
		break;

	}
}


