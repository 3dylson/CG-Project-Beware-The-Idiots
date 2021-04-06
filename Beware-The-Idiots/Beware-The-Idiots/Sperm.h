#ifndef SPERM_H
#define SPERM_H
#include <DirectXMath.h>
#include <GL/glut.h>
#include "Ovule.h"


class Sperm 
{
	GLfloat x;
	GLfloat y;
	GLfloat flick;
	GLfloat flickTimer;
	Ovule target;
	

public:
	
	GLfloat maxSpeed;
	GLfloat rotSpeed;
	GLfloat flickSpeed;
	GLfloat HP;
	GLfloat damage;

	Sperm(GLfloat x = 0, GLfloat y = 0, GLfloat flick = 1, GLfloat flickTimer = 0.1f, GLfloat maxSpeed = 5, GLfloat rotSpeed = 90, GLfloat flickSpeed = 0.1f, GLfloat HP = 1, GLfloat damage = 1);
	
	void draw(GLfloat x, GLfloat y, Ovule target);
	
	void update();
	void moveForward(GLfloat speed);
	void faceGo(DirectX::XMFLOAT3 target, GLfloat rotSpeed);
	void takeDamage(GLfloat damage);
	void isDead();
	
	 
};


#endif // SPERM_H
