#include <GL/glut.h>
#include <Windows.h>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <fstream>

using namespace std;

#define PI 3.14159265f
#define GAME_SCREEN 0			          //Constant to identify background color
#define MENU_SCREEN 3			
#define MAX_SPERM  1000      
#define MAX_SPERM_TYPES 2
#define spermRotationSpeed 90

char title[] = "Beware The Idiots";
char start[] = "    Start";
char instructions[] = "Instructions";
char quit[] = "    Quit";
char game_over[] = "G A M E    O V E R ! ! !";
char restart[] = "Restart";
char back[] = "Back";
char intro[] = "4 People are born every second. Your mission is to prevent more assholes from being born";
char instruction1[] = "Left-Click on Sperm to kill Them";


GLint m_viewport[4];
GLint x, y;
GLint i;
GLint index;
int Score = 0;
int GameLvl = 1;

GLfloat mouseX, mouseY;				       //Cursor coordinates;

//----------------- Sperm variables
GLint randomSpermIndices[100];
GLfloat spermAngle = 0, lineWidth = 1;
GLfloat xSperm[MAX_SPERM], ySperm[MAX_SPERM]; //coordinates of sperms
GLint spermAlive[MAX_SPERM];		       //check to see if sperm is killed
int spermTranslationSpeed = 5;       
//----------------------------------------------

//------------------Ovule variables
GLfloat xOne = 0, yOne = 0;				   //Ovule coordinates
int ovuleLife = 124;
GLfloat ovuleRadius = 300.5f;   // Radius of the Ovule
GLfloat ovuleX = 0.0f;        // Ovule's center (x, y) position
GLfloat ovuleY = 0.0f;
GLfloat xStart = 1200;				//Ovule health bar starting coodinate
//------------------------------------------------------
GLfloat a[][2] = { 0,-50, 70,-50, 70,70, -70,70 };

bool mButtonPressed = false, startGame = false, gameOver = false;		//boolean values to check state of the game
bool startScreen = true, nextScreen = false, previousScreen = false;
bool gameQuit = false, instructionsGame = false, optionsGame = false;



char highScore[100], ch;
void display();
void timer(int);
void backButton();
void DrawLine();
void displayRasterText(float x, float y, float z, char* stringToDisplay);
void DrawSperm(int);
void GameOverScreen();



// Menu items
enum MENU_TYPE
{
	MENU_CONTINUE,
	MENU_QUIT,
};

// Assign a default value
MENU_TYPE show = MENU_CONTINUE;

// Menu handling function definition
void menu(int item)
{
	switch (item)
	{
	case MENU_CONTINUE:
	{
		glColor3f(1, 0, 0);
	}break;
	case MENU_QUIT:
	{
		exit(0);
	}break;
	
	}

	glutPostRedisplay();

	return;
}


void HandleKeyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 81: //	Q
	case 113: //	q
	case 27: // esc
		exit(0);
		break; 
	case	80:	//	P
	case	112: //	p
	
	// Associate a mouse button with menu
		glutCreateMenu(menu);
		glutAttachMenu(112);
		//GameOverScreen();
		//instructionsGame = false;
		//startScreen = false;
		//gameQuit=true;
		break;
	}
	glutPostRedisplay();
}

void SpermGenerate()
{
	for (int i = 0; i < MAX_SPERM;i++) {
		index = i;

		if (mouseX <= (xSperm[i] / 2 + 20) && mouseX >= (xSperm[i] / 2 - 20) && mouseY >= (ySperm[i] / 2 - 20) && mouseY <= (ySperm[i] / 2 + 20) && mButtonPressed) {
			if (spermAlive[i]) {   // IF ALIVE KILL SPERM
				spermAlive[i] = 0;
				Score++;
				if (Score % 5 == 0) {
					GameLvl++;
					spermTranslationSpeed += 1;			//<--------------Rate of increase of game speed
				}
			}
		}
		xSperm[i] += spermTranslationSpeed;
		if (spermAlive[i])             //sperm alive
			DrawSperm(randomSpermIndices[i]);
	}
	spermAngle += spermRotationSpeed;
	if (spermAngle > 360) spermAngle = 0;
}


void DisplayHealthBar() {

	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2f(-xStart, 700);
	glVertex2f(1200, 700);
	glVertex2f(1200, 670);
	glVertex2f(-xStart, 670);
	glEnd();
	char temp[40];
	glColor3f(0, 0, 1);
	sprintf_s(temp, "SCORE = %d", Score);
	displayRasterText(-1100, 600, 0.4, temp);//<---display variable score ?
	sprintf_s(temp, "  LIFE = %d", ovuleLife);
	displayRasterText(800, 600, 0.4, temp);
	sprintf_s(temp, "  LEVEL : %d", GameLvl);
	displayRasterText(-100, 600, 0.4, temp);
	glColor3f(1, 0, 0);
}


void DrawSperm(int SpermIndex)
{
	glPushMatrix();
	glLoadIdentity();
	switch (SpermIndex)                           //CHANGE INDEX VALUE FOR DIFFERENT SPERM VARIETY;
	{
	case 0:

		glTranslated(xSperm[index], ySperm[index], 0);
		glRotatef(spermAngle, 0, 0, 1);
		glTranslated(0, 0, 0);
		glColor3f(1.0f, 1.0f, 1.0f);
		glScalef(35, 35, 1);
		glutSolidSphere(300, 100, 100);
		/*glScalef(30000, 30000, 1);
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
		glEnd();*/
		

		break;
	case 1:
		glColor3f(1.4f, 0.3f, 0.4f);
		glTranslated(xSperm[index], ySperm[index], 0);
		glRotatef(spermAngle, 0, 0, 1);
		glTranslated(0, 0, 0);
		glScalef(15, 20, 1);
		glutSolidSphere(3010, 100, 100);
		/*glTranslated(0, 0, 0);
		glScalef(30000, 30000, 1);
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
		glEnd();*/

		
		break;
	}
	glPopMatrix();
	//glutSwapBuffers();
}


void initializeSpermArray() {
	//random sperms index

	for (int i = 0;i < MAX_SPERM;i++) {
		randomSpermIndices[i] = rand() % MAX_SPERM_TYPES;
		spermAlive[i] = true;
	}

	xSperm[0] = -(200 * MAX_SPERM) - 600;           //START LINE for sperm appearance

	for (int i = 0;i < MAX_SPERM;i++) {				//ramdom appearance yIndex for each sperm
		ySperm[i] = rand() % 600;
		if (int(ySperm[i]) % 2)
			ySperm[i] *= -1;
		xSperm[i + 1] = xSperm[i] + 200;			//xIndex of sperm aligned with 200 units gap
	}
}

bool colision() {
	if (spermAlive[i] && ((xOne >= (xSperm[i] / 2 - 70) && xOne <= (xSperm[i] / 2 + 70) && yOne >= (ySperm[i] / 2 - 18) && yOne <= (ySperm[i] / 2 + 53)) || (yOne <= (ySperm[i] / 2 - 20) && yOne >= (ySperm[i] / 2 - 90) && xOne >= (xSperm[i] / 2 - 40) && xOne <= (xSperm[i] / 2 + 40))))
	{
		spermAlive[i] = 0;
		ovuleLife--;
		return false;
	}

	return true;

}

void DrawOvule()
{
	/*glPushMatrix();	*/
	glLoadIdentity();              // Reset model-view matrix

	glTranslatef(ovuleX, ovuleY, 0.0f);  // Translate to (xPos, yPos)
   // Use triangular segments to form a circle
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 0.0f, 1.0f);  // Blue
	glVertex2f(0.0f, 0.0f);       // Center of circle
	int numSegments = 50;
	GLfloat angle;
	for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
		angle = i * 2.0f * PI / numSegments;  // 360 deg for all segments
		glVertex2f(cos(angle) * ovuleRadius, sin(angle) * ovuleRadius);
	}
	glEnd();

	/*glPopMatrix();*/
}



#pragma region Menu
void displayRasterText(float x, float y, float z, char* stringToDisplay) {
	glRasterPos3f(x, y, z);
	const int length = strlen(stringToDisplay);

	for (int i = 0;i < length;i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, stringToDisplay[i]);
	}
}

void SetDisplayMode(int modeToDisplay) {
	switch (modeToDisplay) {
	case GAME_SCREEN: glClearColor(0, 0, 0, 1);break;
	case MENU_SCREEN: glClearColor(0, 0, 1, 1);break;
	}
}

void startScreenDisplay()
{
	glLineWidth(50);
	SetDisplayMode(MENU_SCREEN);

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);               //Border
	glVertex3f(-750, -500, 0.5);
	glVertex3f(-750, 550, 0.5);
	glVertex3f(750, 550, 0.5);
	glVertex3f(750, -500, 0.5);
	glEnd();

	glLineWidth(1);

	glColor3f(1, 1,0);
	glBegin(GL_POLYGON);				//START GAME PLOYGON
	glVertex3f(-200, 300, 0.5);
	glVertex3f(-200, 400, 0.5);
	glVertex3f(200, 400, 0.5);
	glVertex3f(200, 300, 0.5);
	glEnd();

	glBegin(GL_POLYGON);				//INSTRUCTIONS POLYGON
	glVertex3f(-200, 50, 0.5);
	glVertex3f(-200, 150, 0.5);
	glVertex3f(200, 150, 0.5);
	glVertex3f(200, 50, 0.5);
	glEnd();

	glBegin(GL_POLYGON);				//QUIT POLYGON
	glVertex3f(-200, -200, 0.5);
	glVertex3f(-200, -100, 0.5);
	glVertex3f(200, -100, 0.5);
	glVertex3f(200, -200, 0.5);
	glEnd();

	if (mouseX >= -100 && mouseX <= 100 && mouseY >= 150 && mouseY <= 200) {
		glColor3f(0, 0, 1);
		if (mButtonPressed) {
			startGame = true;
			gameOver = false;
			mButtonPressed = false;
		}
	}
	else
		glColor3f(0, 0, 0);

	displayRasterText(-100, 340, 0.4, start);

	if (mouseX >= -100 && mouseX <= 100 && mouseY >= 30 && mouseY <= 80) {
		glColor3f(0, 0, 1);
		if (mButtonPressed) {
			instructionsGame = true;
			mButtonPressed = false;
		}
	}
	else
		glColor3f(0, 0, 0);
	displayRasterText(-120, 80, 0.4, instructions);

	if (mouseX >= -100 && mouseX <= 100 && mouseY >= -90 && mouseY <= -40) {
		glColor3f(0, 0, 1);
		if (mButtonPressed) {
			gameQuit = true;
			mButtonPressed = false;
		}
	}
	else
		glColor3f(0, 0, 0);
	displayRasterText(-100, -170, 0.4, quit);

}
#pragma endregion


#pragma region Screens

void GameScreenDisplay()
{
	
	SetDisplayMode(GAME_SCREEN);
	glScalef(2, 2, 0);
	if (ovuleLife) {
		DrawOvule();
		DisplayHealthBar();
		SpermGenerate();
		//if (mButtonPressed) { DrawLine(); }
		if (colision) {
			ovuleLife--;
		}
	}
	else {
		gameOver = true;
		instructionsGame = false;
		startScreen = false;
	}								//<----------------------gameover screen


}

void GameOverScreen()
{
	SetDisplayMode(MENU_SCREEN);
	glColor3f(0, 0, 0);
	glLineWidth(50);
	glBegin(GL_LINE_LOOP);               //Border
	glVertex3f(-650, -500, 0.5);
	glVertex3f(-650, 520, 0.5);
	glVertex3f(650, 520, 0.5);
	glVertex3f(650, -500, 0.5);
	glEnd();

	glLineWidth(1);
	//spermTranslationSpeed = 5;
	glColor3f(0, 1, 0);
	glBegin(GL_POLYGON);				//GAME OVER
	glVertex3f(-550, 810, 0.5);
	glVertex3f(-550, 610, 0.5);
	glVertex3f(550, 610, 0.5);
	glVertex3f(550, 810, 0.5);
	glEnd();

	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);				//RESTART POLYGON
	glVertex3f(-200, 50, 0.5);
	glVertex3f(-200, 150, 0.5);
	glVertex3f(200, 150, 0.5);
	glVertex3f(200, 50, 0.5);
	glEnd();

	glBegin(GL_POLYGON);				//QUIT POLYGON
	glVertex3f(-200, -200, 0.5);
	glVertex3f(-200, -100, 0.5);
	glVertex3f(200, -100, 0.5);
	glVertex3f(200, -200, 0.5);
	glEnd();


	displayRasterText(-300, 640, 0.4, game_over);
	glColor3f(0, 0, 0);
	char temp[40];

	sprintf_s(temp, "Score : %d", Score);
	displayRasterText(-100, 340, 0.4, temp);
	/*readFromFile();*/
	char temp2[40];
	if (atoi(highScore) < Score) {
		/*writeIntoFile()*/;
		sprintf_s(temp2, "Highest Score :%d", Score);
	}
	else
		sprintf_s(temp2, "Highest Score :%s", highScore);

	displayRasterText(-250, 400, 0.4, temp2);

	if (mouseX >= -100 && mouseX <= 100 && mouseY >= 25 && mouseY <= 75) {
		glColor3f(0, 0, 1);
		if (mButtonPressed) {                                                       //Reset game default values
			startGame = true;
			gameOver = false;
			mButtonPressed = false;
			//initializeSpermArray();
			ovuleLife = 124;
			Score = 0;
			GameLvl = 1;
			GameScreenDisplay();
		}
	}
	else
		glColor3f(0, 0, 0);
	displayRasterText(-70, 80, 0.4, restart);

	if (mouseX >= -100 && mouseX <= 100 && mouseY >= -100 && mouseY <= -50) {
		glColor3f(0, 1, 0);
		if (mButtonPressed) {
			exit(0);
			mButtonPressed = false;
		}
	}
	else
		glColor3f(0, 0, 0);
	displayRasterText(-100, -170, 0.4, quit);

}

void InstructionsScreenDisplay()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SetDisplayMode(MENU_SCREEN);
	//colorBackground();
	glColor3f(0, 0, 0);
	displayRasterText(-900, 400, 0.4, intro);
	displayRasterText(-900, 300, 0.4, instruction1);
	/*displayRasterText(-900, 200, 0.4, );
	displayRasterText(-900, 100, 0.4, );
	displayRasterText(-900, 0.0, 0.4, );
	displayRasterText(-900, -200, 0.4, );*/

	backButton();
	if (previousScreen)
		nextScreen = false, previousScreen = false; //as set by backButton()


}
#pragma endregion


#pragma region FileScore
void readFromFile() {
	FILE* fp;
	errno_t err = fopen_s(&fp, "HighScoreFile.txt", "r");
	auto i = 0;
	if (err == 0) {
		while (fread(&ch, sizeof(char), 1, fp)) {
			highScore[i++] = ch;
		}
		highScore[i] = '\0';
	}
	fclose(fp);
}

void writeIntoFile() {						//To write high score on to file
	FILE* fp;
	errno_t err = fopen_s(&fp, "HighScoreFile.txt", "r");
	auto i = 0;
	char temp[40];
	if (err == 0) {
		auto n = Score;
		while (n) {
			ch = (n % 10) + '0';
			n /= 10;
			temp[i++] = ch;
		}
		temp[i] = '\0';
		_strrev(temp);
		puts(temp);
		if (temp[0] == '\0')
			temp[i++] = '0', temp[i++] = '\0';
		fwrite(temp, sizeof(char) * i, i, fp);
	}
	fclose(fp);
}
#pragma endregion


void DrawLine() {

	float xMid = -(55 + 50) / 2.0;
	float yMid = (25 + 35) / 2.0;

	float mouseXEnd = mouseX;
	float mouseYEnd = mouseY;
	glLineWidth(5);   //----Line width

	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(xMid, yMid);
	glVertex2f(mouseXEnd, mouseYEnd);
	glEnd();
	glLineWidth(1);
}

void backButton() {
	if (mouseX <= -450 && mouseX >= -500 && mouseY >= -275 && mouseY <= -250) {
		glColor3f(1, 1, 0);
		if (mButtonPressed) {
			mButtonPressed = false;
			instructionsGame = false;
			startScreenDisplay();
		}
	}
	else glColor3f(0, 0, 0);
	displayRasterText(-1000, -550, 0, back);
}

void mouseClick(int buttonPressed, int state, int x, int y) {

	if (buttonPressed == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		mButtonPressed = true;
	else
		mButtonPressed = false;
	glutPostRedisplay();
}

void passiveMotionFunc(int x, int y) {

	//when mouse not clicked
	mouseX = static_cast<float>(x) / (m_viewport[2] / 1200.0) - 600.0;  //converting screen resolution to ortho 2d spec
	mouseY = -(static_cast<float>(y) / (m_viewport[3] / 700.0) - 350.0);


	glutPostRedisplay();
}

void idleCallBack() {			//when no mouse or keybord pressed
	glutPostRedisplay();
}


void init()
{
	//gama de cores: [0,1]
	glClearColor(0.5, 0.5, 0.5, 0);
	glColor3f(0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(-1200, 1200, -700, 700);                   //<-----CHANGE THIS TO GET EXTRA SPACE
//  gluOrtho2D(-200,200,-200,200);
	glMatrixMode(GL_MODELVIEW);
}

void timer(int)
{
	//chamar a função display
	/*glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 1);

	switch (state)
	{
	case 1:
		if (x < 8)
			x += 0.15;
		else
			state = -1;
		break;
	case -1:
		if (x > -10)
			x -= 0.15;
		else state = 1;
		break;

	}*/
}

/**
 * \brief Função para exibir tudo
 */
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 1200, 700);

	if (startGame && !gameOver)
		GameScreenDisplay();

	else if (instructionsGame)
		InstructionsScreenDisplay();

	else if (gameOver)
		GameOverScreen();

	else if (startScreen) {

		startScreenDisplay();
		if (gameQuit || startGame || optionsGame || instructionsGame) {
			//startScreen = false;

			/*if (startGame) {
				SetDisplayMode(GAME_SCREEN);
				DrawOvule();
				startScreen = false;

			}
			else if (gameQuit)
				exit(0);*/
			if (gameQuit)
				exit(0);

		}
		else if (instructionsGame) {
			SetDisplayMode(GAME_SCREEN);
			InstructionsScreenDisplay();
		}
	}

	//Reset Scaling values

	if (startGame) {
		SetDisplayMode(GAME_SCREEN);
		
		startScreen = false;
	}
	glScalef(1 / 2, 1 / 2, 0);
	glFlush();
	glLoadIdentity();
	glutSwapBuffers();
	
}


int main(int argc,char**argv)
{
	fstream fp;
	// err = fp.open("HighScoreFile.txt", ios::in);

	//errno_t err = open_s(&fp, "HighScoreFile.txt", "r");      //check if HighScoreFile.txt exist if not create             
	//if (err == 0)
	//	fclose(fp);
	//else
	//	writeIntoFile();
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	glutInitWindowPosition(90, 0);
	glutInitWindowSize(1200, 700);	
	
	glutCreateWindow(title);

	glutDisplayFunc(display);
	glutPassiveMotionFunc(passiveMotionFunc);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutIdleFunc(idleCallBack);
	//glutReshapeFunc(reshape);
	glutTimerFunc(0,timer,0);
	glutMouseFunc(mouseClick);
	glGetIntegerv(GL_VIEWPORT, m_viewport);
	init();
	SetDisplayMode(GAME_SCREEN);

	 
	initializeSpermArray();
	colision();
	glutKeyboardFunc(HandleKeyboard);
	glutMainLoop();

	

	// Create a menu
	glutCreateMenu(menu);

	// Add menu items
	glutAddMenuEntry("Continue", MENU_CONTINUE);
	glutAddMenuEntry("Quit", MENU_QUIT);
	

	// Associate a mouse button with menu
	
	


	return 0;
}








