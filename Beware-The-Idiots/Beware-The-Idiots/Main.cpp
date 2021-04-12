#include <GL/glut.h>
#include <Windows.h>
#include <cmath>
#include <cstring>
#include <cstdio>

#include "Sperm.h"

#define PI 3.14159
#define GAME_SCREEN 0			          //Constant to identify background color
#define MENU_SCREEN 3			
#define MAX_SPERM  1000      
#define MAX_SPERM_TYPES 2

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
int x, y;
int i;
int randomSpermIndices[100];
int index;
int Score = 0;
int ovuleLife = 124;
int GameLvl = 1;
float mouseX, mouseY;				       //Cursor coordinates;
float spermAngle = 0, lineWidth = 1;
float xOne = 0, yOne = 0;				   //Ovule coordinates
float xSperm[MAX_SPERM], ySperm[MAX_SPERM];//coordinates of sperms
GLint spermAlive[MAX_SPERM];		       //check to see if sperm is killed


bool mButtonPressed = false, startGame = false, gameOver = false;		//boolean values to check state of the game
bool startScreen = true, nextScreen = false, previousScreen = false;
bool gameQuit = false, instructionsGame = false, optionsGame = false;
bool fullScreen = true;


char highScore[100], ch;
void display();
void reshape(GLsizei, GLsizei);
void timer(int);
void backButton();
void DrawLine();


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

	glColor3f(1, 1, 0);
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
		//SpermGenerate();
		if (mButtonPressed) { DrawLine(); }
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

	float mouseXEnd = -((-mouseX) + xOne);
	float mouseYEnd = -((-mouseY) + yOne);
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
		glColor3f(0, 0, 1);
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


int main(int argc,char**argv)
{
	//FILE* fp;
	//errno_t err = fopen_s(&fp, "HighScoreFile.txt", "r");      //check if HighScoreFile.txt exist if not create             
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
	glutReshapeFunc(reshape);
	glutTimerFunc(0,timer,0);
	glutMouseFunc(mouseClick);
	glGetIntegerv(GL_VIEWPORT, m_viewport);
	init();
	
	glutMainLoop();

	return 0;
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

			if (startGame) {
				SetDisplayMode(GAME_SCREEN);
				startScreen = false;

			}
			else if (gameQuit)
				exit(0);

		}
		else if (instructionsGame) {
			SetDisplayMode(GAME_SCREEN);
			InstructionsScreenDisplay();
		}
	}

	//Reset Scaling values
	glScalef(1 / 2, 1 / 2, 0);
	glFlush();
	glLoadIdentity();
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
		gluOrtho2D(-1200, 1200, -700 * h / w, 700);
	else
		gluOrtho2D(-1200, 1200 * w / h, -700, 700);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
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


