#include <GL/glut.h>
#include <Windows.h>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <iostream>

#define PI 3.14159265f
#define GAME_SCREEN 0			          //Constant to identify background color
#define MENU_SCREEN 3			
#define MAX_SPERM  100      
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
int ovuleLife = 30;
GLfloat ovuleRadius = 300.5f;   // Radius of the Ovule
GLfloat ovuleX = 0.0f;        // Ovule's center (x, y) position
GLfloat ovuleY = 0.0f;
GLfloat xStart = 1200;				//Ovule health bar starting coodinate
//------------------------------------------------------
GLfloat a[][2] = { 0,-50, 70,-50, 70,70, -70,70 };
GLint CI = 0;
GLfloat LightColor[][3] = { 1,1,0,   0,1,1,   0,1,0 };

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
void initializeSpermArray();
void GameScreenDisplay();



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
	}
	glutPostRedisplay();
}

void SpermGenerate()
{
	//If the last sperm hits the end of screen then regenerate 
	if (xSperm[0]>=1200)
	{
		GameLvl++;
		initializeSpermArray();
		GameScreenDisplay();
	}
	
		for (int i = 0; i < MAX_SPERM;i++) {
		index = i;

		if (mouseX <= (xSperm[i] / 2 + 20) && mouseX >= (xSperm[i] / 2 - 20) && mouseY >= (ySperm[i] / 2 - 20) && mouseY <= (ySperm[i] / 2 + 20) && mButtonPressed) {
			if (spermAlive[i]) {   // IF ALIVE KILL SPERM
				spermAlive[i] = 0;
				Score++;
				if (Score % 5 == 0) {
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
	glVertex2f(-2100, 700);
	glVertex2f(1200, 700);
	glVertex2f(1200, 670);
	glVertex2f(-2100, 670);
	glEnd();
	char temp[40];
	glColor3f(0, 0, 1);
	sprintf_s(temp, "SCORE = %d", Score);
	displayRasterText(-2000, 600, 0.4, temp);//<---display variable score ?
	sprintf_s(temp, "  LIFE = %d", ovuleLife);
	displayRasterText(-100, 600, 0.4, temp);
	sprintf_s(temp, "  LEVEL : %d", GameLvl);
	displayRasterText(-1000, 600, 0.4, temp);
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
		glutSolidSphere(1, 9, 50);

		//glLoadIdentity();
		//glTranslated(xSperm[index], ySperm[index], 0);
		//glRotatef(spermAngle, 0, 0, 1);
		//glTranslated(spermAngle, 0, 0);
		//glScalef(60, 10, 1);
		////glBegin(GL_LINES);
		////lineWidth(3);
		////glVertex2f(0, 0);
		////glVertex2f(-1, -1);
		////glEnd();
		//glutSolidSphere(1, 5, 50);//*/

		
		/*glLoadIdentity();
		glTranslated(xSperm[index], ySperm[index], 0);
		glRotatef(spermAngle, 0, 0, 1);
		glTranslated(0, 0, 0);
		glScalef(10, 60, 1);
		glutSolidSphere(1, 5, 50);*/
		

		break;
	case 1:
		glColor3f(1.0f, 0.8f, 0.8f);
		glTranslated(xSperm[index], ySperm[index], 0);
		glRotatef(spermAngle, 0, 0, 1);
		glTranslated(0, 0, 0);
		glScalef(15, 20, 1);
		glutSolidSphere(1, 9, 50);

		glLoadIdentity();
		glTranslated(xSperm[index], ySperm[index], 0);
		glRotatef(spermAngle, 0, 0, 1);
		glTranslated(0, 0, 0);
		glScalef(40, 5, 1);
		glutSolidSphere(1, 5, 50);
		

		
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

	for (int i = 0;MAX_SPERM;i++) {

		if (spermAlive[i] && xSperm[i] >= 850 && ySperm[i] == 0)
			
		{
			spermAlive[i] = 0;
			//ovuleLife--;
			return true;
		}
	return false;
	}


}

void DrawOvule()
{
	glPushMatrix();	
	glLoadIdentity();              // Reset model-view matrix

	//glTranslatef(ovuleX, ovuleY, 0.0f);  // Translate to (xPos, yPos)
	glTranslatef(900, ovuleY, 0.0f);  // Translate to (xPos, yPos)

	if (colision()) { ovuleLife--; }
   
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
		/*
		if (!GLUT_RIGHT_BUTTON) {
			Sleep(10000);
		}*/

		//if (mButtonPressed) { DrawLine(); }
		/*if (colision) {
			ovuleLife--;
		}*/
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
			ovuleLife = 30;
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

	std::fstream score_file;
	score_file.open("HighScoreFile.txt", std::ios::in);
	int i = 0;
	if(!score_file)
	{
		std::cout << "No such file";
	}
	else
	{
		while(true)
		{
			highScore[i++] >> ch;
			if (score_file.eof())
				break;
		}
		score_file.close();		
	}
	

	
	/*FILE* fp;
	errno_t err = fopen_s(&fp, "HighScoreFile.txt", "r");
	auto i = 0;
	if (err == 0) {
		while (fread(&ch, sizeof(char), 1, fp)) {
			highScore[i++] = ch;
		}
		highScore[i] = '\0';
	}
	fclose(fp);*/
}

void writeIntoFile() {						//To write high score on to file

	std::fstream score_file;
	score_file.open("HighScoreFile.txt", std::ios::out);
	auto i = 0;
	char temp[40];
	if(!score_file)
	{
		std::cout << "File not created!";
	}
	else
	{
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
		score_file << temp;
		score_file.close();
		
	}


	/*FILE* fp;
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
	fclose(fp);*/
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


	display();
}

void idleCallBack() {			//when no mouse or keybord pressed
	display();
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
	//chamar a fun��o display
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

void UpdateColorIndex(int value)
{
	CI = (CI + 1) % 3;			//Color Index swapping to have rotation effect
	display();
	glutTimerFunc(250, UpdateColorIndex, 0);
	
}

/**
 * \brief Fun��o para exibir tudo
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
	std::fstream score_file;
	score_file.open("HighScoreFile.txt", std::ios::out);
	if(!score_file)
	{
		score_file.close();
	}
	else
	{
		writeIntoFile();
	}
	
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
	glutPassiveMotionFunc(passiveMotionFunc);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutIdleFunc(idleCallBack);
	//glutReshapeFunc(reshape);
	//glutTimerFunc(0,timer,0);
	glutMouseFunc(mouseClick);
	glGetIntegerv(GL_VIEWPORT, m_viewport);
	init();
	SetDisplayMode(GAME_SCREEN);

	 
	initializeSpermArray();
	glutKeyboardFunc(HandleKeyboard);
	

	

	// Create a menu
	glutCreateMenu(menu);

	// Add menu items
	glutAddMenuEntry("Continue", MENU_CONTINUE);
	glutAddMenuEntry("Quit", MENU_QUIT);
	
	
	// Associate a mouse button with menu
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	//
	//if (GLUT_RIGHT_BUTTON) {
	//	startGame = false;
	//	gameOver = false;
	//	
	//	//Sleep(10000);
	//}
	
	glutMainLoop();

	return 0;
}








