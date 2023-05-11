/*
    ALGO - 1
*/
 /*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */
 
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
 
#include <cstdlib>
#include <stdio.h>
#include<math.h>
 
#define LINE_COUNT 10
 
int lineCoords[LINE_COUNT][4];
 
/* GLUT callback Handlers */
 
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
 
// int findZone(int x0, int y0, int x1, int y1)
// {
//     int dx = x1 - x0;
//     int dy = y1 - y0;
//     if (abs(dx) >= abs(dy)) {
//         if (dx >= 0 && dy >= 0) return 0;
//         if (dx >= 0 && dy < 0) return 7;
//         if (dx < 0 && dy >= 0) return 3;
//         if (dx < 0 && dy < 0) return 4;
//     } else {
//         if (dx >= 0 && dy >= 0) return 1;
//         if (dx >= 0 && dy < 0) return 6;
//         if (dx < 0 && dy >= 0) return 2;
//         if (dx < 0 && dy < 0) return 5;
//     }
//     return 0;
// }
 
void drawPixel(int x, int y)
{
    glVertex2i(x, y);
}
 
void drawLine0(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int x = x0;
    int y = y0;
    int d = 2 * dy - dx;
    int del_e = 2 * dy;
    int del_ne = 2 * (dy - dx);
    while (x < x1)
    {
        if (d < 0)
        {
            d += del_e;
            x++;
        }
        else
        {
            d += del_ne;
            x++;
            y++;
        }
        drawPixel(x, y);
    }
}
 
void drawLine1(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int x = x0;
    int y = y0;
    int d = dy - 2 * dx;
    int del_n = -2 * dx;
    int del_ne = 2 * (dy - dx);
    while (y < y1)
    {
        if (d > 0)
        {
            d += del_n;
            y++;
        }
        else
        {
            d += del_ne;
            x++;
            y++;
        }
        drawPixel(x, y);
    }
}
 
void drawLine2(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int x = x0;
    int y = y0;
    int d = -2 * dx - dy;
    int del_n = -2 * dx;
    int del_nw = -2 * (dx + dy);
    while (y < y1)
    {
        if (d < 0)
        {
            d += del_n;
            y++;
        }
        else
        {
            d += del_nw;
            x--;
            y++;
        }
        drawPixel(x, y);
    }
}
 
void drawLine3(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int x = x0;
    int y = y0;
    int d = -2 * dx + dy;
    int del_w = -2 * dy;
    int del_nw = -2 * (dx + dy);
    while (x > x1)
    {
        if (d > 0)
        {
            d += del_w;
            x--;
        }
        else
        {
            d += del_nw;
            x--;
            y++;
        }
        drawPixel(x, y);
    }
}
 
void drawLine4(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int x = x0;
    int y = y0;
    int d = dx - 2 * dy;
    int del_w = -2 * dy;
    int del_sw = -2 * (dy - dx);
    while (x > x1)
    {
        if (d < 0)
        {
            d += del_w;
            x--;
        }
        else
        {
            d += del_sw;
            x--;
            y--;
        }
        drawPixel(x, y);
    }
}
 
void drawLine5(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int x = x0;
    int y = y0;
    int d = 2 * dx - dy;
    int del_s = 2 * dx;
    int del_sw = -2 * (dy - dx);
    while (y > y1)
    {
        if (d > 0)
        {
            d += del_s;
            y--;
        }
        else
        {
            d += del_sw;
            x--;
            y--;
        }
        drawPixel(x, y);
    }
}
 
void drawLine6(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int x = x0;
    int y = y0;
    int d = 2 * dx + dy;
    int del_s = 2 * dx;
    int del_se = 2 * (dx + dy);
    while (y > y1)
    {
        if (d < 0)
        {
            d += del_s;
            y--;
        }
        else
        {
            d += del_se;
            x++;
            y--;
        }
        drawPixel(x, y);
    }
}
 
void drawLine7(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int x = x0;
    int y = y0;
    int d = 2 * dx - dy;
    int del_e = 2 * dy;
    int del_se = 2 * (dx + dy);
    while (x < x1)
    {
        if (d > 0)
        {
            d += del_e;
            x++;
        }
        else
        {
            d += del_se;
            x++;
            y--;
        }
        drawPixel(x, y);
    }
}

void findZone(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    if (abs(dx) >= abs(dy)) {
        if (dx >= 0 && dy >= 0)
        {

        glColor3ub(255, 0, 0);
        drawLine0(x0, y0, x1, y1);
        }

        if (dx >= 0 && dy < 0) 
        {
        glColor3ub(128, 128, 0);
        drawLine7(x0, y0, x1, y1);  
        }
        if (dx < 0 && dy >= 0)
        {
        glColor3ub(255, 0, 255);
        drawLine3(x0, y0, x1, y1);  
        }
        if (dx < 0 && dy < 0) 
        {
        glColor3ub(255, 255, 0);
        drawLine4(x0, y0, x1, y1);   
        }
    } else {
        if (dx >= 0 && dy >= 0) 
        {
        glColor3ub(0, 255, 0);
        drawLine1(x0, y0, x1, y1);  
        }
        if (dx >= 0 && dy < 0) 
        {
        glColor3ub(255, 255, 255);
        drawLine6(x0, y0, x1, y1); 
        }
        if (dx < 0 && dy >= 0)
         {
         glColor3ub(0, 0, 255);
        drawLine2(x0, y0, x1, y1);   
        }
        if (dx < 0 && dy < 0)
        {
         glColor3ub(0, 255, 255);
        drawLine5(x0, y0, x1, y1);   
        }
    }
    
}


 
void drawLine()
{
    findZone(0,0,-20,-200);
    findZone(0,0,-20,200);
    findZone(0,0,20,-200);
    findZone(0,0,20,200);
    findZone(0,0,-200,-20);
    findZone(0,0,-200,20);
    findZone(0,0,200,-20);
    findZone(0,0,200,20);


    int x0=0,y0=0,x1,y1;
    for(int i=0;i<360;i=i+1){
        x1=200*cos(i);
        y1=200*sin(i);
        findZone(x0,y0,x1,y1);
    }

}



 
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


 
int call;
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
    drawLine();
    glEnd();
    glutSwapBuffers();
}
 
static void idle(void)
{
    glutPostRedisplay();
}
 
/* Program entry point */
 
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
 
    glutCreateWindow("Lab 01 - Algo 1");
 
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    generateLines();
 
    glutMainLoop();
 
    return EXIT_SUCCESS;
}