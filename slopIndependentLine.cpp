/*
     ALGO - 2
*/
 
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
 
 
static int slices = 16;
static int stacks = 16;
#define LINE_COUNT 10


int Wi=640, He=480;


int maxy =He/2-1 ;
int miny =-He/2 ;
int maxx =Wi/2-1 ;
int minx =-Wi/2 ;
int top = 8;
int bottom = 4;
int right_ = 2;
int left_ = 1;
 
int lineCoords[LINE_COUNT][4];
 
int generateRandX() {
    return (rand() % 640) - 320;
}
 
int generateRandY() {
    return (rand() % 480) - 240;
}
 
void generateLines() {
    for (int i = 0; i < LINE_COUNT; i++) {
        lineCoords[i][0] = generateRandX();
        lineCoords[i][1] = generateRandY();
        lineCoords[i][2] = generateRandX();
        lineCoords[i][3] = generateRandY();
    }
}
 
static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-320, 319, -240, 239, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}



void draw_grid(void){
    glBegin(GL_LINES);
    glVertex2i(-140,miny);
    glVertex2i(-140,maxy);
    glVertex2i(140,miny);
    glVertex2i(140,maxy);
    glVertex2i(minx,100);
    glVertex2i(maxx,100);
    glVertex2i(minx,-100);
    glVertex2i(maxx,-100);

    glEnd();
}
 
int findZone (int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0, dy = y1 - y0;
    if (dx >= 0 and dy >= 0)
    {
        if (dx >= dy)
        {
            //printf("GREEN\n");
            return 0;
        }
        else
        { //printf("SKYBLUE\n");
            return 1;
        }
    }
    else if (dx < 0 and dy >= 0)
    {
        if (-dx >= dy)
        {
            //printf("YELLOW");
            return 3;
        }
        else
        {
           //printf("PURPLE\n");
            return 2;
        }
    }
    else if (dx < 0 and dy < 0)
    {
        if (-dx >= -dy)
        {
             //printf("RED\n");
             return 4;
        }
        else
        {
             //printf("BLUE\n");
             return 5;
        }
    }
    else
    {
        if (dx >= -dy)
        {
           //printf("PINK\n"); 
           return 7;
        }
        else
        {
            //printf("WHITE\n");
             return 6;
        }
    }
}
 
void drawPixel (int x, int y, int zone)
{
    switch (zone)
    {
    case 0:
        glColor3d(0, 102, 0);
        glVertex2i(x, y);
        break;
    case 1:
        glColor3d(0, 102, 102);
        glVertex2i(y, x);
        break;
    case 2:
        glColor3f(0.5f, 0.0f, 1.0f); // make this vertex purple
 
        glVertex2i(-y, x);
        break;
    case 3:
        glColor3d(255, 255, 0);
 
        glVertex2i(-x, y);
        break;
    case 4:
        glColor3d(204, 0, 0);
 
        glVertex2i(-x, -y);
        break;
    case 5:
        glColor3d(0, 0, 255);
 
        glVertex2i(-y, -x);
        break;
    case 6:
        glColor3d(255, 255, 255);
 
        glVertex2i(y, -x);
        break;
    case 7:
        glColor3d(102, 0, 51);
 
        glVertex2i(x, -y);
        break;
    }
}
 
void drawLine0 (int x0, int y0, int x1, int y1, int zone)
{
    int dx = x1 - x0, dy = y1 - y0;
    int x = x0, y = y0, d = 2 * dy - dx;
    int de = 2 * dy, dne = 2 * (dy - dx);
    while (x <= x1)
    {
        drawPixel (x, y, zone);
        if (d < 0)
        {
            ++x;
            d += de;
        }
        else
        {
            ++x, ++y;
            d += dne;
        }
    }
}
 
void drawLine (int x0, int y0, int x1, int y1)
{
    int zone = findZone(x0, y0, x1, y1);
    // printf("zone = %d\n", zone);
    switch (zone)
    {
    case 0:
 
        drawLine0(x0, y0, x1, y1, zone);
        break;
    case 1:
 
        drawLine0(y0, x0, y1, x1, zone);
        break;
    case 2:
 
        drawLine0(y0, -x0, y1, -x1, zone);
        break;
    case 3:
 
        drawLine0(-x0, y0, -x1, y1, zone);
        break;
    case 4:
 
        drawLine0(-x0, -y0, -x1, -y1, zone);
        break;
    case 5:
 
        drawLine0(-y0, -x0, -y1, -x1, zone);
        break;
    case 6:
 
        drawLine0(-y0, x0, -y1, x1, zone);
        break;
    case 7:
 
        drawLine0(x0, -y0, x1, -y1, zone);
        break;
    }
}
 
 
int x_0, x_1, y_0, y_1;
 
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,1,1);
    glBegin(GL_LINES);
    glVertex2i(-320, 0);
    glVertex2i(319, 0);
    glVertex2i(0, -240);
    glVertex2i(0, 239);
    glEnd();
 
    glPointSize(2);
    glBegin(GL_POINTS);
    draw_grid();


    // drawLine(0,0,-20,-200);
    // drawLine(0,0,-20,200);
    // drawLine(0,0,20,-200);
    // drawLine(0,0,20,200);
    // drawLine(0,0,-200,-20);
    // drawLine(0,0,-200,20);
    // drawLine(0,0,200,-20);
    // drawLine(0,0,200,20);

    // int x0=0,y0=0,x1,y1;
    // for(int i=0;i<360;i=i+1){
    //     x1=200*cos(i);
    //     y1=200*sin(i);
    //     drawLine(x0,y0,x1,y1);
    // }


    
    
    glEnd();
 
    glutSwapBuffers();
}

 
 
static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27 :
    case 'q':
        exit(0);
        break;
 
    case '+':
        slices++;
        stacks++;
        break;
 
    case '-':
        if (slices>3 && stacks>3)
        {
            slices--;
            stacks--;
        }
        break;
    }
 
    glutPostRedisplay();
}
 
static void idle(void)
{
    glutPostRedisplay();
}
 
// Program entry point
 
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    generateLines();
    glutCreateWindow("Experiment 01");
 
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
 
    glutMainLoop();
 
    return EXIT_SUCCESS;
}


///g++ draw8way2.cpp -o draw8way2 -lglut -lGLU -lGL &&./draw8way2