#include<GL/gl.h>
#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include <fstream>
#include <iostream>
#include "game.h"

#define COLUMNS 40
#define ROWS 40
#define FPS 10
#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2

using namespace std;

extern int  Direction;
extern int flagL,flagR,flagU,flagD;
extern int pointY1,pointY2;
extern bool point1,point2;
extern int score;
extern char buffer1[10],buffer2[10];
bool gameOver = false;
int q,highscore;
int screen = 0;


void display_callback();
void reshape_callback(int,int);
void timer_callback(int);
void keyboard_callback(int,int,int);
void alphabet_keys(unsigned char,int,int);

void my_utoa(int dataIn, char* bffr, int radix){
	int temp_dataIn;
	temp_dataIn = dataIn;
	int stringLen=1;

	while ((int)temp_dataIn/radix != 0){
	    temp_dataIn = (int)temp_dataIn/radix;
	    stringLen++;
	}
	temp_dataIn = dataIn;
	do{
	    *(bffr+stringLen-1) = (temp_dataIn%radix)+'0';
	    temp_dataIn = (int) temp_dataIn / radix;
	}while(stringLen--);
}

void init(){
	glClearColor(0.0,0.0,0.0,1.0);
	initWindow(ROWS,COLUMNS);
	gluOrtho2D(0, 500, 0, 500);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc,char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	ifstream myFile;
	myFile.open("highScore.txt");
	myFile>>highscore;
	myFile.close();


	glutInitWindowSize(500,700);
	glutCreateWindow("2 Cars");
	init();
	glutDisplayFunc(display_callback);
	glutReshapeFunc(reshape_callback);
	glutTimerFunc(0,timer_callback,0);
	glutSpecialFunc(keyboard_callback);
	glutKeyboardFunc(alphabet_keys);
	glutIdleFunc(display_callback);
	glutMainLoop();
	return 0;
}


void display_callback(){
    if(screen == 0)
    {
	    glClear(GL_COLOR_BUFFER_BIT);
	    glColor3f(1.0,0.6,0.2);
	    drawTitle("2 CARS", 12,30);
	    glColor3f(0.6,0.0,1.0);
	    drawText("WELCOME", 12,20);
	    drawText("PLAYER", 12, 18);
	    drawText("Press 1 to continue", 12, 16);
	    glutSwapBuffers();
    }
    else if(screen == 1){
	    glClear(GL_COLOR_BUFFER_BIT);
	    glColor3f(1.0,0.6,0.2);
	    drawTitle("2 CARS", 12,30);
	    glColor3f(0,0,1);
	    drawText("Use 'A' to move blue car left", 9, 20);
	    drawText("Use 'D' to move blue car right", 9, 18);
	    glColor3f(0,1,0);
	    drawText("Use <-- to move green car left", 8, 15);
	    drawText("Use <-- to move green car right", 8, 13);
	    glColor3f(1,1,1);
	    drawText("Press 2 to continue", 13, 11);
	    glutSwapBuffers();
    }
    else{
	glClear(GL_COLOR_BUFFER_BIT);
	drawLanes();
	drawCars();
	drawPoints();
	glColor3f(1,1,1);
    	drawText("Score:", 3,38);
    	my_utoa(score, buffer1, 10);
    	drawTextNum(buffer1, 6, 8,38);

	drawText("HighScore:", 23,38);
	my_utoa(highscore, buffer2, 10);
	drawTextNum(buffer2, 6, 31,38);	
	glutSwapBuffers();
	for(q = 0; q<= 10000000; q++){;}
	if(gameOver==true){
		fstream File;
		File.open("highScore.txt",ios::in);
		File>>highscore;
		File.close();

		if(highscore<score){
			highscore = score;
			File.open("highScore.txt",ios::out | ios::trunc);
			File<<highscore;
			File.close();
		}
		glColor3f(1,0,0);
		drawText("Game  Over", 15,20);
		drawText("Press ESC to quit", 13,18);
		glutSwapBuffers();
        	getchar();
		//exit(0);
	}
	}
}

void reshape_callback(int w,int h){
        glViewport(0,0,(GLsizei)w,(GLsizei)h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0,COLUMNS,0.0,ROWS,-1.0,1.0);
        glMatrixMode(GL_MODELVIEW);
}

void timer_callback(int){
	glutPostRedisplay();
	glutTimerFunc(1000/FPS,timer_callback,0);

	if(score<=20){
		if(pointY1>0)
			pointY1 -= 0.15;
		if(pointY1==0)
			point1 = true;

		if(pointY2>0)
			pointY2 -= 0.15;
		if(pointY2==0)
			point2 = true;
	}else if(score>20 && score<=50){
		if(pointY1>0)
			pointY1 -= 0.25;
		if(pointY1==0)
			point1 = true;

		if(pointY2>0)
			pointY2 -= 0.25;
		if(pointY2==0)
			point2 = true;
	}else{
		if(pointY1>0)
			pointY1 -= 0.35;
		if(pointY1==0)
			point1 = true;

		if(pointY2>0)
			pointY2 -= 0.35;
		if(pointY2==0)
			point2 = true;
	}
}

void keyboard_callback(int key,int x,int y){
	switch(key){
                case GLUT_KEY_RIGHT:
                        if(Direction!=RIGHT){
                                Direction=RIGHT;
				flagR=0;
			}
			break;

                case GLUT_KEY_LEFT:
                        if(Direction!=LEFT){
                                Direction=LEFT;
				flagL=0;
			}
			break;
	}
}

void alphabet_keys(unsigned char key,int x,int y){
	switch(key){
		 case 'd':
			if(Direction!=UP ){
				Direction=UP;
				flagU=0;
			}
			break;

                case 'a':
                        if(Direction!=DOWN){
                                Direction=DOWN;
				flagD=0;
			}
			break; 

		case '1':if(screen == 0)
             			screen=1;
             		break;
   		case '2':if(screen == 1)
             			screen=2;
             		break;
		
		case 'q': 
			 exit(0);
			 
	}
}
