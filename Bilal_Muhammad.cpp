/*********
   CTIS164 - Template Source Program
----------
STUDENT : MUHAMMAD BILAL
STUDENT NUMBER: 22101368
SECTION : 04
HOMEWORK: 1
----------
PROBLEMS:
1)at the end of the screen, the spaceship still moves down (if repeatedely pressed the key)
2)i also didnt make use of winHeight/2 an winWidth/2 so, i think that's a problem as well
3)I have made the hw complex myself, so when returning back to the menu, and starting the game again, everything starts from there (as a continuation). 
----------
EXTRA NOTES:
1)i set up the glut in my system as x86, so hocam, if your visual studio is set at Debug with x64, kindly change it to x86. Then only my code will run.
2)also change the gL in the include directory to GL, because my folder name in the system is gL ;-; 
----------
ADDITIONAL FEATURES:
1)creating of Main Menu
2)creating of loading screen
3)added a new eclipse function
4)added an eclipse_wire
5)increase and decrease speed
6)location track
7)blinking colorful stars
8)moving aliens
9)game over screen
*********/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <gL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <string>
#include <conio.h>
#include <time.h>


#define MENU 0
#define LOADINGSCREEN 1
#define RUN 2
#define END 3
#define GAMEOVER 4

#define AUTONOMOUSSTATE 4
#define MANUALSTATE 5
double CRadius = 30;
double distance, distance2, distance3;
typedef enum  //creating an enum class for directions
{
   NOT_SET=0, LEFT, RIGHT, UP, DOWN

}DIRECTIONS;

typedef struct  //structure for mouse clicks
{
    double X1;
    double Y1;

}mouse_t;
mouse_t Mouse;


typedef struct   //structure for directions
{
    bool right;
    bool left;
    bool up;
    bool down;

}Manual_t;

Manual_t man;



double RecX=400, RecY=100;  //variables for aliens
double RecX2 = RecX + 400, RecY2 = RecY - 100;
double RecX3 = RecX + 800, RecY3 = RecY - 200;

bool isAlien = true;
bool isUFO = true;


double TX1 = 100;    //variables for stars movement (again i didnt consider win/Height and winWidth
double TX2 = 370;
double TX3 = 320;
double TX4 = -100;
double TX5 = -370;
double TX6 = -320;
double TX7 = 600;
double TX8 = -600;

bool reset = false; //variable for setting resetting
int num1,num2,num3;

int CurrentMode = MANUALSTATE;  //two states
int currentState = MENU;
const char * MODE1= "AUTONOMOUS";
const char* MODE2 = "MANUAL";
const char* DIR1 = "UP";   //printing directions
const char* DIR2 = "DOWN";
const char* DIR3 = "RIGHT";
const char* DIR4 = "LEFT";

int PlanetHeight = 250;
double gameSpeed = 1; //for the player
bool state = false;
double TriangleVerticeX = 0;
double TriangleVerticeY = 0;
double Cx=0, Cy=0;
int directions=DIRECTIONS::NOT_SET;
bool gameSpeedIncrease = false, gameSpeedDecrease=false;  //bool variables for speed
bool ClickToCreate = false;
double StarX=0, StarY=0;

#define WINDOW_WIDTH  1400
#define WINDOW_HEIGHT 800

#define TIMER_PERIOD  16 // Period for the timer.
#define TIMER_ON         1 // 0:disable timer, 1:enable timer

#define D2R 0.0174532

/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // current Window width and height

//
// to draw circle, center at (x,y)
// radius r

  //time period for loading
int DotCount = 0;
int TimeSpent = 0;
double UFOradius = 75;

void circle(int x, int y, int r)
{
#define PI 3.1415
    float angle;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void circle_wire(int x, int y, int r)
{
#define PI 3.1415
    float angle;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}
void drawellipse(int x, int y, float Rx, float Ry) {  // i copied the circle function and modified it for the horizontal radius. It creates an ellipse
    
    float angle;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        angle = i * D2R;
        glVertex2f(x + Rx * cos(angle), y + Ry * sin(angle));

    }

    glEnd();
}

void ellipseWire(int x, int y, float Rx, float Ry)
{
    float angle;
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        angle = i * D2R;
        glVertex2f(x + Rx * cos(angle), y + Ry * sin(angle));

    }

    glEnd();

}
void drawAlien(double Loc1, double Loc2)   //displays the aliens
{
   
    glColor3f(1, 1, 0);
    glRectf(Loc1, Loc2, Loc1 +25, Loc2 -30);
    glColor3f(0.4, 0.4, 0.4);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glVertex2f(Loc1 + 2, Loc2 - 12.5);
    glVertex2f(Loc1 + 7, Loc2);
    glVertex2f(Loc1 + 12, Loc2 - 12.5);
    glVertex2f(Loc1 + 17, Loc2);
    glVertex2f(Loc1 + 22, Loc2 - 12.5);
    glEnd();
    circle(Loc1 + 12.5, Loc2 - 22, 3);
    glColor3f(1, 1, 1);
    glBegin(GL_LINE_STRIP);
    glVertex2f(Loc1 + 25, Loc2 - 20);
    glVertex2f(Loc1 + 35, Loc2 - 12.5);
    glVertex2f(Loc1 + 45, Loc2 - 20);
    glVertex2f(Loc1 + 55, Loc2 - 12.5);
    glVertex2f(Loc1 + 65, Loc2 - 20);
    glEnd();
    glLineWidth(1);
    
    if (RecX <= -winWidth/2)  //return to the screen
    {
        RecX = winWidth / 2;
       

    }
    if (RecX2 <= -winWidth / 2)  //returns to the screen
    {
        RecX2 = winWidth / 2;


    }

    if (RecX3 <= -winWidth / 2)
    {
        RecX3 = winWidth / 2;


    }



}
void print(int x, int y, const char* string, void* font)
{
    int len, i;

    glRasterPos2f(x, y);
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, string[i]);
    }
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void* font, const char* string, ...)
{
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);

    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, str[i]);
    }
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, const char* string, ...) {
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(size, size, 1);

    int len, i;
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
    }
    glPopMatrix();
}

//
// To display onto window using OpenGL commands
//
void drawBackground()  //creates a singular background for all the states
{
    glColor3f(0, 0, 0);
    glRectf(-700, -400,700,400);
    glColor3f(1,1,1);
    glRectf(-700, -220, 700, -400);
    vprint(570, 380, GLUT_BITMAP_9_BY_15, "Muhammad Bilal");
    vprint(580, 360, GLUT_BITMAP_9_BY_15, "22101368");

   
}
void drawTwoLines()   //ufo's antennas
{
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2f(Cx + 35, Cy - 25);
    glVertex2f(Cx + 40, Cy - 50);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(Cx - 35, Cy - 25);
    glVertex2f(Cx - 40, Cy - 50);
    glEnd();
    glLineWidth(1);
}
void DrawUFO()   //it draws the UFO 
{
    
       
        glColor3f(1, 1, 153 / 255.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(Cx, Cy - 20 - (CRadius - 10));
        glVertex2f(Cx + 20, Cy - 80 - (CRadius - 10));
        glVertex2f(Cx - 20, Cy - 80 - (CRadius - 10));
        glEnd();
        glColor3f(192 / 255.0, 192 / 255.0, 192 / 255.0);
        drawellipse(Cx, Cy, 60, 30);
        drawellipse(Cx, Cy, 80, 15);
        glColor3f(135 / 255.0, 206 / 255.0, 230 / 255.0);
        circle(Cx, Cy + 40, CRadius);
        glColor3f(0, 0, 0);
        circle_wire(Cx, Cy + 40, CRadius);
        glColor3f(192 / 255.0, 192 / 255.0, 192 / 255.0);
        circle(Cx, Cy - 20, CRadius - 5);
        glColor3f(1, 1, 0); //implement blinkin lights for this one as well tomorrow
        circle(Cx - 50, Cy - 5, 3);
        circle(Cx - 20, Cy - 17, 3);
        circle(Cx + 50, Cy - 5, 3);
        circle(Cx + 20, Cy - 17, 3);
        glColor3f(1, 0, 0);
        circle(Cx - 35, Cy - 12, 3);
        circle(Cx, Cy - 22, 3);
        circle(Cx + 35, Cy - 12, 3);
        glColor3f(1, 1, 1);
        drawTwoLines();

   
   

}

void DrawPlanet()  //draws the planet
{
    glColor3f(1, 1, 1);
    circle(StarX, StarY + PlanetHeight, 30);
    glColor3f(0, 0, 0);
    glPointSize(2);
    glBegin(GL_POINTS);
    glVertex2f(StarX + 10, StarY+ PlanetHeight);
    glVertex2f(StarX + 20, StarY+10 + PlanetHeight);
    glVertex2f(StarX -15, StarY + PlanetHeight -15);
    glVertex2f(StarX -18, StarY + 20 + PlanetHeight);
    glVertex2f(StarX, StarY + 25 + PlanetHeight);
    glVertex2f(StarX, StarY + PlanetHeight -25);

    glEnd();

    if (StarX < -700)
    {
        StarX = 700;
    }


}
void DrawStar(double x, double y)  //draws a star
{
    TriangleVerticeX = x; //assigning the loation
    TriangleVerticeY = y;
    glBegin(GL_TRIANGLES);
    glColor3f(num1/255.0, num2/255.0, num3/255.0);
    glVertex2f(TriangleVerticeX, TriangleVerticeY);
    glColor3f(num2/255.0, num1/255.0, num3/255.0);
    glVertex2f(TriangleVerticeX + 10, TriangleVerticeY + 16);
    glColor3f(num3/255.0, num2/255.0, num1/255.0);
    glVertex2f(TriangleVerticeX + 20, TriangleVerticeY);
    glEnd();


    glBegin(GL_TRIANGLES);
    glColor3f(num3 / 255.0, num2 / 255.0, num1 / 255.0);
    glVertex2f(TriangleVerticeX + 10, TriangleVerticeY - 5);
    glColor3f(num2 / 255.0, num1 / 255.0, num3 / 255.0);
    glVertex2f(TriangleVerticeX + 20, TriangleVerticeY + 10);
    glColor3f(num1 / 255.0, num2 / 255.0, num3 / 255.0);
    glVertex2f(TriangleVerticeX, TriangleVerticeY + 10);
    glEnd();


    if (TX1 < -700)  //all the if statements for to set them back to the initial position ( i know its not efficient)
    {
        TX1 = 700;
    }
    if (TX2 < -700)
    {
        TX2 = 700;

    }

    if (TX3 < -700)
    {
        TX3 = 700;

    }
    if (TX4 < -700)
    {
        TX4 = 700;
    }
    if (TX5 < -700)
    {
        TX5 = 700;
    }
    if (TX6 < -700)
    {

        TX6 = 700;
    }
    if (TX7 < -700)
    {

        TX7 = 700;
    }
    if (TX8 < -700)
    {

        TX8 = 700;
    }



      
    
}
void Directions()
{
    switch (directions)   //checks the variable and compare it against enum values 
    {
    case NOT_SET:
        glColor3f(1, 1, 1);
        vprint(-580, 350, GLUT_BITMAP_HELVETICA_18, "NOT SET");
        break;
    case DOWN:
        glColor3f(1, 1, 1);
        vprint(-580, 350, GLUT_BITMAP_HELVETICA_18, "DOWN");
        break;

    case UP:
        glColor3f(1, 1, 1);
        vprint(-580, 350, GLUT_BITMAP_HELVETICA_18, "UP");
        break;
    case RIGHT:
        glColor3f(1, 1, 1);
        vprint(-580, 350, GLUT_BITMAP_HELVETICA_18, "RIGHT");
        break;

    case LEFT:
        glColor3f(1, 1, 1);
        vprint(-580, 350, GLUT_BITMAP_HELVETICA_18, "LEFT");
        break;

    }

}
void RunBackGround()
{
    glColor3f(70 / 255.0, 232 / 255.0, 143 / 255.0); //background for the run 
    vprint2(-680, 380, 0.13, "MODE: ");
    vprint2(-680, 350, 0.13, "DIRECTION: ");
    glColor3f(0, 0, 0);
    vprint2(-100, -350, 0.15, "Press ");
    glColor3f(191 / 255.0, 10 / 255.0, 85 / 255.0);
    vprint2(-40, -350, 0.15, "<F1>");
    glColor3f(0, 0, 0);
    vprint2(20, -350, 0.15, "to switch the mode and ");
    glColor3f(191 / 255.0, 10 / 255.0, 85 / 255.0);
    vprint2(270, -350, 0.15, "ARROW KEYS ");
    glColor3f(0, 0, 0);
    vprint2(410, -350, 0.15, "to change the direction");
    glColor3f(0, 0, 0);
    vprint2(-690, -350, 0.15, "Press");
    glColor3f(191 / 255.0, 10 / 255.0, 85 / 255.0);
    vprint2(-630, -350, 0.15, "<Q>");
    glColor3f(0, 0, 0);
    vprint2(-575, -350, 0.15, "to reset the location");
    glColor3f(0, 0, 0);
    vprint2(-690, -280, 0.15, "Press");
    glColor3f(191 / 255.0, 10 / 255.0, 85 / 255.0);
    vprint2(-630, -280, 0.15, "<M>");
    glColor3f(0, 0, 0);
    vprint2(-575, -280, 0.15, "to return back to the Menu");
    glColor3f(0, 0, 0);
    vprint2(-100, -280, 0.15, "Press");
    glColor3f(191 / 255.0, 10 / 255.0, 85 / 255.0);
    vprint2(-40, -280, 0.15, "<I>");
    glColor3f(0, 0, 0);
    vprint2(-5, -280, 0.15, "to Increase and ");
    glColor3f(191 / 255.0, 10 / 255.0, 85 / 255.0);
    vprint2(155, -280, 0.15, "<D>");
    glColor3f(0, 0, 0);
    vprint2(200, -280, 0.15, "to Decrease the speed ");
    glColor3f(1, 1, 1);
    vprint(580, 340, GLUT_BITMAP_9_BY_15, "(%.0f,%.0f)", Cx, Cy);

    if (ClickToCreate == false)   //checks if its false
    {

        glColor3f(191 / 255.0, 10 / 255.0, 85 / 255.0);
        vprint(-140, 0, GLUT_BITMAP_TIMES_ROMAN_24, "Click ");
        glColor3f(1, 1, 1);
        vprint(-80, 0, GLUT_BITMAP_TIMES_ROMAN_24, "to create/relocate the UFO ");

    }


}void drawstates()  //write two modes
{
    if (state)
    {
        glColor3f(1, 1, 1);
        vprint(-600, 380, GLUT_BITMAP_HELVETICA_18, MODE1);
        CurrentMode = AUTONOMOUSSTATE;
    }
    else
    {
        glColor3f(1, 1, 1);
        vprint(-600, 380, GLUT_BITMAP_HELVETICA_18, MODE2);
        CurrentMode = MANUALSTATE;

    }
 
}
void LoadingScreen()  //loading screen
{
    glColor3f(1, 1, 1);
    vprint(-70, 90, GLUT_BITMAP_TIMES_ROMAN_24, "LOADING");
    for (int i = 0; i < DotCount; i++)
    {
        vprint2(50 + i * 20,90, 0.3, ".");

    }
}
void Gameover() //gameOver screen
{
    glColor3f(191 / 255.0, 10 / 255.0, 85 / 255.0);
    vprint(-80, 100, GLUT_BITMAP_TIMES_ROMAN_24, "GAME OVER!!!");
    vprint(-140, 0, GLUT_BITMAP_TIMES_ROMAN_24, "Click ");
    glColor3f(1, 1, 1);
    vprint(-80, 0, GLUT_BITMAP_TIMES_ROMAN_24, "to create/relocate the UFO ");

}
void Menu()
{
    glColor3f(191 / 255.0, 10 / 255.0, 85 / 255.0);   //Menu creation
    vprint(-190, 300, GLUT_BITMAP_TIMES_ROMAN_24, "WELCOME TO ALIEN-DAMNATION");
   
    glColor3f(61 / 255.0, 116 / 255.0, 212 / 255.0);
    vprint(-50, 200, GLUT_BITMAP_HELVETICA_18, "START");

    glColor3f(210 / 255.0, 224 / 255.0, 117 / 255.0);
    vprint(-50, 150, GLUT_BITMAP_HELVETICA_18, "OPTIONS");

    glColor3f(70 / 255.0, 232 / 255.0, 143 / 255.0);
    vprint(-50, 100, GLUT_BITMAP_HELVETICA_18, "EXIT");  //use exit function to close the window altogether (if possible)

    glColor3f(203 / 255.0, 95 / 255.0, 227 / 255.0);
    vprint(-120, -100, GLUT_BITMAP_HELVETICA_18, "Press <Enter> to start the game");

}
void display() {
    //
    // clear window to black
    //
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    drawBackground();

    switch (currentState)
    {

    case MENU:
        Menu();
        break;

    case LOADINGSCREEN:  //loading segment
        LoadingScreen(); 
        break;

    case RUN:  //displays all the functions for the run segment
        RunBackGround();   
        if (ClickToCreate)
        {
           
            DrawPlanet();
            drawstates();
            Directions();
            DrawStar(TX1,200);
            DrawStar(TX2, 280);
            DrawStar(TX3, 300);
            DrawStar(TX4, 200);
            DrawStar(TX5, 280);
            DrawStar(TX6, 300);
            DrawStar(TX7, 290);
            DrawStar(TX8, 290);
            if (isUFO)
            {
                DrawUFO();
              
            }
            
            if (isAlien)  //if alien is true, it displays
            {
              
                drawAlien(RecX, RecY);
            
                drawAlien(RecX2, RecY2);
                drawAlien(RecX3, RecY3);

            }

        }
       
        break;
    case GAMEOVER:
        RunBackGround();
        Gameover();
      
  
       
        break;
    }

  


    glutSwapBuffers();
}

//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);

    if (key == 13 && currentState!=RUN)
    {
        currentState = LOADINGSCREEN;
    }

    if (key == 113)
    {
        reset = true;  //setting the direction
        directions = DIRECTIONS::NOT_SET;
    }

    if (key == 109) //checks for the M key (to return back to the menu)
    {
        currentState = MENU;
        TimeSpent = 0;  //sets the time spent to zer0 for the load screen
        ClickToCreate = false; //rests the run screen
        gameSpeed = 1;
        directions = DIRECTIONS::NOT_SET;
    }

    if (key == 105 && currentState ==RUN)  //increases the ufo speed in RUN state
    {
        gameSpeedIncrease = true;
        gameSpeed++;
    }

    if (key == 100 && currentState == RUN)
    {
        gameSpeedDecrease = true;
        if (gameSpeed>=2)  //otherwise it decreases to negative numbers, and speed increases automatically
        {  //also speed never decreased below 1 because of default speed
            gameSpeed--;
        }
         //halves the speed on every press
    }


    // to refresh the window it calls display() function
    glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown(int key, int x, int y)
{
    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP: up = true; break;
    case GLUT_KEY_DOWN: down = true; break;
    case GLUT_KEY_LEFT: left = true; break;
    case GLUT_KEY_RIGHT: right = true; break;
    }
  
    if (key==GLUT_KEY_F1 && currentState==RUN)  //had to use GLUT_KEY_F1
    {
      
        state = !state;  //changes state

    }


    if (key == GLUT_KEY_DOWN && currentState == RUN)  //had to use GLUT_KEY_F1
    {
      
        
        directions = DIRECTIONS::DOWN;  //i know this is C++ syntax, but im using it for changing direction string 
        man.down = true;
    }

    if (key == GLUT_KEY_UP && currentState == RUN)        //these are to change the direction (enum based)
    {
       
        directions = DIRECTIONS::UP;
        man.up = true;
    }

    if (key == GLUT_KEY_RIGHT && currentState == RUN)  
    {
      
        directions = DIRECTIONS::RIGHT;
        man.right = true;
    }

    if (key == GLUT_KEY_LEFT && currentState == RUN) 
    {
       
        directions = DIRECTIONS::LEFT;
        man.left = true;
    }

    


    


    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp(int key, int x, int y)
{
    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP: up = false; break;
    case GLUT_KEY_DOWN: down = false; break;
    case GLUT_KEY_LEFT: left = false; break;
    case GLUT_KEY_RIGHT: right = false; break;
    }


  


    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
void onClick(int button, int stat, int x, int y)
{
    // Write your codes here
    if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN && currentState==RUN && ClickToCreate==false)
    {
        ClickToCreate = true;

       
    }

    if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN && currentState == RUN  && ClickToCreate == true)
    {
        Cx = Mouse.X1;                   //for run screeen (placing the object)
        Cy = Mouse.Y1;
      
      
    }
    if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN && currentState == GAMEOVER && ClickToCreate == false)
    {
        ClickToCreate = true;                      //for gameover screen
       
       

    }

    if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN &&  currentState == GAMEOVER && ClickToCreate == true)
    {
        Cx = Mouse.X1;
        Cy = Mouse.Y1;                   //for gameover screen
        isUFO = true;
        currentState = RUN;
        gameSpeed = 1;
        directions = DIRECTIONS::NOT_SET;

    }


    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize(int w, int h)
{
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    display(); // refresh window.
}

void onMoveDown(int x, int y) {
    // Write your codes here.



    // to refresh the window it calls display() function   
    glutPostRedisplay();
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove(int x, int y) {
    // Write your codes here.

    Mouse.X1 = x - winWidth / 2;
    Mouse.Y1 = winHeight / 2 - y;

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {

    // Write your codes here.
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);


    if (currentState == LOADINGSCREEN)   //checks if its the loadingscreen
    {

        DotCount = (DotCount + 1) % 4;  //dots for the loading screen
        TimeSpent++;
        if (TimeSpent == 60)
        {
            currentState = RUN;
        }
    }
    else if (currentState == RUN)
    {
         num1 = rand() % 255;
         num2 = rand() % 200;
         num3 = rand() % 250;
        
         if (isAlien)
         {

              RecX -= 2;
              RecX2 -= 2;
              RecX3 -= 2;
              distance = sqrt(pow(abs((Cx - RecX)),2) + pow(abs((Cy - RecY)),2)); //calculates the distance
             if (distance<=UFOradius)
             {
                 ClickToCreate = false;  //disables everything
                 isUFO = false;
                 currentState = GAMEOVER;
             }

             distance2 = sqrt(pow(abs((Cx - RecX2)), 2) + pow(abs((Cy - RecY2)), 2)); //calculates the distance
             if (distance2 <= UFOradius)
             {
                 ClickToCreate = false;  //disables everything
                 isUFO = false;
                 currentState = GAMEOVER;
             }

             distance3= sqrt(pow(abs((Cx - RecX3)), 2) + pow(abs((Cy - RecY3)), 2)); //calculates the distance
             if (distance3 <= UFOradius)
             {
                 ClickToCreate = false;  //disables everything
                 isUFO = false;
                 currentState = GAMEOVER;
             }
            
         }

      
      
        if (ClickToCreate == true  )
        {

            StarX -= 5;


            TX1 -= 2;
            TX2 -= 2;
            TX3 -= 2;
            TX4 -= 2;
            TX5 -= 2;
            TX6 -= 2;
            TX7 -= 2;
            TX8 -= 2;


        }

        if (CurrentMode == AUTONOMOUSSTATE)
        {
            switch (directions)
            {

            case NOT_SET:  //implement reset the direction
                if (reset)
                {
                    Cx = 0;
                    Cy = 0;
                    reset = false;
                }

                break;
            case DOWN:

                Cy -= 1.5 * gameSpeed;   //increases and decreases the speed with multiplication of gamespeed
                break;

            case UP:
                Cy += 1.5 * gameSpeed;

                break;
            case RIGHT:
                Cx += 1.5 * gameSpeed;
                break;

            case LEFT:
                Cx -= 1.5 * gameSpeed;
                break;

            }

            if (Cx >= (700 - CRadius))  //stopping the player from going out of bounds
            {
                directions = LEFT;
            }
            else if (Cx <= (-700 + CRadius))
            {
                directions = RIGHT;
            }
            else if (Cy >= (380 - CRadius))
            {
                directions = DOWN;
            }
            else if (Cy <= (-160 + CRadius))
            {
                directions = UP;
            }
        }
        else if (CurrentMode == MANUALSTATE)
        {

            switch (directions)
            {

            case NOT_SET:  //implement reset the direction
                if (reset)
                {
                    Cx = 0;
                    Cy = 0;
                    reset = false;
                }


                break;
            case DOWN:   //increases and decreases the speed with multiplication of gamespeed
                if (man.down)
                {
                    Cy -= 3 * gameSpeed;
                    man.down = false;

                }
                break;

            case UP:
                if (man.up)
                {
                    Cy += 3 * gameSpeed; 
                    man.up = false;

                }

                break;
            case RIGHT:
                if (man.right)
                {
                    Cx += 3 * gameSpeed;
                    man.right = false;

                }
                break;

            case LEFT:
                if (man.left)
                {
                    Cx -= 3 * gameSpeed;
                    man.left = false;

                }
                break;

            }

            if (Cx >= (660 - CRadius))  
            {
                Cx -= 3;
            }
            else if (Cx <= (-660 + CRadius)) //stopping the player from going out of bounds
            {
                Cx += 3;
            }
            else if (Cy >= (380 - CRadius))
            {
                Cy -= 3;
            }
            else if (Cy <= (-160 + CRadius))
            {
                Cy += 3;
            }





        }
        
    }



    // to refresh the window it calls display() function
    glutPostRedisplay(); // display()

}
#endif

void Init() {

    // Smoothing shapes
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void main(int argc, char* argv[]) {

    srand(time(NULL));
  
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    //glutInitWindowPosition(100, 100);
    glutCreateWindow("Alien Damnation");

    glutDisplayFunc(display);
    glutReshapeFunc(onResize);

    //
    // keyboard registration
    //
    glutKeyboardFunc(onKeyDown);
    glutSpecialFunc(onSpecialKeyDown);

    glutKeyboardUpFunc(onKeyUp);
    glutSpecialUpFunc(onSpecialKeyUp);

    //
    // mouse registration
    //
    glutMouseFunc(onClick);
    glutMotionFunc(onMoveDown);
    glutPassiveMotionFunc(onMove);

#if  TIMER_ON == 1
        // timer event
        glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

    Init();

    glutMainLoop();
}