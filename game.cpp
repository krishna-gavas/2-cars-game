#include<GL/gl.h>
#include<GL/glut.h>
#include<string.h>
#include<ctime>
#include <fstream>
#include <iostream>
#include "game.h"

#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2

using namespace std;

int width,height;
int posX1=3,posY1=2,posX2=23,posY2=2;
int Direction;
int flagL=0,flagR=0,flagU=0,flagD=0;
int pointX1,pointY1,pointX2,pointY2;
bool point1 = true,point2 = true;
int score = 0,i;
char buffer1[10],buffer2[10];
extern bool gameOver;

void initWindow(int x,int y){
	width = x;
	height = y-3;
}

void drawLanes(){
        glLineWidth(2.0);
        glColor3f(0.4,0.0,0.8);
        glBegin(GL_LINES);
                glVertex2f(width/4.0,0.0);
                glVertex2f(width/4.0,height);
        glEnd();


	glLineWidth(6.0);
	glColor3f(0.5,0.0,1.0);
	glBegin(GL_LINES);
		glVertex2f(width/2.0,0.0);
		glVertex2f(width/2.0,height);
	glEnd();

	glLineWidth(2.0);
        glColor3f(0.4,0.0,0.8);
        glBegin(GL_LINES);
                glVertex2f(3*(width/4.0),0.0);
                glVertex2f(3*(width/4.0),height);
        glEnd();

}

void drawCars(){

	if(Direction==UP && flagU==0 && posX1>0 && posX1<10){
		posX1+=10;
		flagU = 1;
	}
	else if(Direction==DOWN && flagD==0 && posX1>10 && posX1<20){
		posX1-=10;
		flagD = 1;
	}
	else if(Direction==RIGHT && flagR==0 && posX2>20 && posX2<30){
		posX2+=10;
		flagR = 1;
	}
	else if(Direction==LEFT && flagL==0 && posX2>30 && posX2<40){
		posX2-=10;
		flagL = 1;
	}
	
	
	glColor3f(0.0,0.0,1.0);
	glRectd(posX1,posY1,posX1+4,posY1+5);
	glColor3f(1.0,1.0,1.0);
	glRectd(posX1+1,posY1+1,posX1+3,posY1+3);  
	
	//glColor3f(0.0,0.0,1.0);
	//glRectd(posX1+10,posY1,posX1+14,posY1+5);
	//glColor3f(1.0,1.0,1.0);
	//glRectd(posX1+11,posY1+1,posX1+13,posY1+3);

	
	glColor3f(0.0,1.0,0.0);
	glRectd(posX2,posY2,posX2+4,posY2+5);
	glColor3f(0.0,0.0,0.0);
	glRectd(posX2+1,posY2+1,posX2+3,posY2+3);

	if((posX1+4==pointX1+4 && posY1+5>=pointY1 && posY1<pointY1) || (posX2+4==pointX2+4 && posY2+5>=pointY2 && posY2<pointY2))
		gameOver = true;
	
}

void random1(int &x,int &y){
	int _maxY = height,_min = 25;
	srand(time(NULL));
	//x = _min + rand() % (_maxX - _min);
	x = posX1;
	y = _min + rand() % (_maxY - _min);
}


void drawPoints(){
	if(point1){
		random1(pointX1,pointY1);
		score++;
	}
	point1 = false;
	glColor3f(1.0,0.0,0.0);
	glRectf(pointX1,pointY1,pointX1+4,pointY1+1.5);


	if(point2){
		pointX2=posX2;pointY2=25+(pointY1+10)%10;
		score++;
		//random1(pointX2,pointY2);
	}
	point2 = false;
	glColor3f(1.0,0.0,0.0);
	glRectf(pointX2,pointY2,pointX2+4,pointY2+1.5);
}

void drawText(const char* ch,int xpos, int ypos)//draw the text for score and game over
{
    int numofchar = strlen(ch);
    glLoadIdentity ();
    glRasterPos2f( xpos , ypos);
    for (i = 0; i <= numofchar - 1; i++)
    {
     
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch[i]);//font used here, may use other font also
    }
}

void drawTitle(const char* ch,int xpos, int ypos)//draw the text for score and game over
{
    int numofchar = strlen(ch);
    glLoadIdentity ();
    glRasterPos2f( xpos , ypos);
    for (i = 0; i <= numofchar - 1; i++)
    {
     
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ch[i]);//font used here, may use other font also
    }
}

void drawTextNum(const char* ch,int numtext,int xpos, int ypos)//counting the score
{
    int len;
    int k;
    k = 0;
    len = numtext - strlen (ch);
    glLoadIdentity ();
    glRasterPos2f( xpos , ypos);
    for (i = 0; i <=numtext - 1; i++)
    {
    if ( i < len )
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'0');
    else
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch[k]);
        k++;
    }
    }
}




