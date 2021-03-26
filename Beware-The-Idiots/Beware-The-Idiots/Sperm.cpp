#include "Sperm.h"
using namespace std;

Sperm::Sperm(GLfloat x, GLfloat y, GLfloat flick, GLfloat flickTimer, GLfloat maxSpeed, GLfloat rotSpeed, GLfloat flickSpeed, GLfloat HP, GLfloat damage):
	x(0),
	y(0),
	flick(1),
	flickTimer(0.1f),
	maxSpeed(5),
	rotSpeed(90),
	flickSpeed(0.1f),
	HP(1),
	damage(1)
{
}

void Sperm::draw()
{
	const double randomR = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
	const double randomG = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
	const double randomB = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);

	glColor3f(randomR, randomG, randomB); //Body color
	glBegin(GL_POLYGON);
	glVertex2f(0.0, 1.0);
	glVertex2f(1.0, 1.0);
	glVertex2f(3.0, 1.0);
	glVertex2f(4.0, 0.0);
	glVertex2f(5.0, 0.0);
	glVertex2f(6.0, 1.0);
	glVertex2f(5.0, 2.0);
	glVertex2f(4.0, 2.0);
	glVertex2f(3.0, 1.0);
	glEnd();
}
