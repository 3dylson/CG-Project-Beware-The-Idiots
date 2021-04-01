#ifndef SPERM_H
#define SPERM_H
#include <DirectXMath.h>
#include <GL/glut.h>
#include "Dijkstra_Path_Algorithm.h"


class Sperm : public Dijkstra_Path_Algorithm
{
	GLfloat x;
	GLfloat y;
	GLfloat flick;
	GLfloat flickTimer;

public:
	Sperm(GLfloat x = 0, GLfloat y = 0, GLfloat flick = 1, GLfloat flickTimer = 0.1f, GLfloat maxSpeed=5, GLfloat rotSpeed=90, GLfloat flickSpeed=0.1f, GLfloat HP =1, GLfloat damage =1);
	GLfloat maxSpeed;
	GLfloat rotSpeed;
	GLfloat flickSpeed;
	GLfloat HP;
	GLfloat damage;

	void draw();
	
	void update();
	void moveForward(GLfloat speed);
	void faceGo(DirectX::XMFLOAT3 target, GLfloat rotSpeed);
	void takeDamage(GLfloat damage);
	void isDead();
	
	 
};


#endif // SPERM_H
