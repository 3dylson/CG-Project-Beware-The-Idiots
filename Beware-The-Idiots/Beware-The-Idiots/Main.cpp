#include <GL/glut.h>
#include <Windows.h>


void display();
void reshape(GLsizei, GLsizei);
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

GLfloat x_position = -10.0;
GLfloat y_position = 1.0;
GLsizei rsize = 2.0;
GLint state = 1;

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

	glVertex2f(x_position, y_position);
	glVertex2f(x_position,-y_position);
	glVertex2f(x_position+rsize,-y_position+rsize);
	glVertex2f(x_position+rsize, y_position+rsize);

	//
	glEnd();
	
	
	glutSwapBuffers();
	
}

/**
 * \brief função para remodelar
 * \param w largura
 * \param h altura
 */
void reshape( GLsizei w, GLsizei h)
{
	// Previnir divisão por zero
	if (h == 0)
		h = 1;
	// Definir janela de exibição para as dimensões da janela
	glViewport(0, 0, w, h);
	// Reiniciar sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
		gluOrtho2D(-10, 10, -10 * h / w, 10);
	else
		gluOrtho2D(-10, 10 * w / h, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void timer(int)
{
	//chamar a função display
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 1);

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


