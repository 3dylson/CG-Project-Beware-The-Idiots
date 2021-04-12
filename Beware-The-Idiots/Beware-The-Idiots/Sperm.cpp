#include "Sperm.h"

#include <vector>
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
	this->x = x;
	this->y = y;
	this->flick = flick;
	this->flickTimer = flickTimer;
	this->maxSpeed = maxSpeed;
	this->rotSpeed = rotSpeed;
	this->flickSpeed = flickSpeed;
	this->HP = HP;
	this->damage = damage;
	
}

void Sperm::draw(GLfloat x, GLfloat y, Ovule target)
{
	this->x = x;
	this->y = y;
	this->target = target;

	GLsizei rsize = 2.0;
		
	const GLfloat randomR = (double)rand() / (double)RAND_MAX;
	const GLfloat randomG = (double)rand() / (double)RAND_MAX;
	const GLfloat randomB = (double)rand() / (double)RAND_MAX;
	
	glColor3f(randomR, randomG, randomB); //Body color
	glPointSize(10.0);
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x+1.0, y);
	glVertex2f(x+2.0, y);
	glVertex2f(x+3.0, y);
	glVertex2f(x+4.0, y-1.0);
	glVertex2f(x+5.0, y-1.0);
	glVertex2f(x+6.0, y);
	glVertex2f(x+5.0, y+1.0);
	glVertex2f(x+4.0, y+1.0);
	glEnd();
	

	
}

void Sperm::update()
{
	//isDead();
	/*this->target = bait;*/
	
	
	
}
