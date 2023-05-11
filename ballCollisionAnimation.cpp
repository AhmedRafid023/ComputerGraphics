
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <bits/stdc++.h>
using namespace std;

#define WIDTH 512
#define HEIGHT 512

 
float r=50;
float dx=0.3, dy=0.7;
float xc=0;
float yc=0;


void drawPixel(int x, int y, int zone , int xc, int yc);
void drawCircle(int xc, int yc, int r);
void draw8way(int x, int y , int xc ,int yc);


bool collisionX(float xc,float r,float dx){
    if (dx<0)
        return xc-r < -WIDTH/2;
    
    else
        return xc+r > WIDTH/2;
}


bool collisionY(float yc,float r,float dy){
    if(dy<0)
        return yc -r < -HEIGHT/2;
    
    else
        return yc+r > HEIGHT/2;

}

static void resize(int width, int height)
{
    const float ar = (float)width / (float)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WIDTH / 2, WIDTH / 2 - 1, -HEIGHT / 2, HEIGHT / 2 - 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2i(-WIDTH / 2, 0);
    glVertex2i(WIDTH / 2, 0);
    glVertex2i(0, -HEIGHT / 2);
    glVertex2i(0, HEIGHT / 2);
    glEnd();

    xc+=dx;
    yc+=dy;



    int colx = collisionX(xc,r,dx);
    int coly = collisionY(yc,r, dy);
    if(colx!=0)dx=-dx;
    if(coly!=0)dy=-dy;


    glPointSize(1);
    glBegin(GL_POINTS);
    drawCircle(xc,yc,r);

    
    glEnd();

    glutSwapBuffers();
}

static void idle(void)
{
    glutPostRedisplay();
}

void drawCircle(int xc, int yc , int r)
{
    int x = 0, y = r;
    int d = 5 - 4*r;
    draw8way(x, y , xc ,yc);

    while(x < y){
        if(d < 0){
            d += 4 * (2*x + 3);
            x++;
        }
        else{
            d += 4 * (2*x - 2*y + 5);
            x++;
            y--;
        }
        draw8way(x, y, xc,yc);
    }
}


void draw8way(int x, int y, int xc, int yc)
{
    for(int i = 0; i < 8; i++){
        drawPixel(x, y, i, xc,yc);
    }
}


void drawPixel (int x, int y, int zone, int xc , int yc)
{
    switch (zone)
    {
    case 0:
        glColor3d(255, 255, 255);
        glVertex2i(x+xc, y+yc);
        break;
    case 1:
        glColor3d(255, 255, 255);
        glVertex2i(y+xc, x+yc);
        break;
    case 2:
    
        glVertex2i(-y+xc, x+yc);
        break;
    case 3:
        glColor3d(255, 255, 255);
        glVertex2i(-x+xc, y+yc);
        break;
    case 4:
        glColor3d(255, 255, 255); 
        glVertex2i(-x+xc, -y+yc);
        break;
    case 5:
        glColor3d(255, 255, 255);
        glVertex2i(-y+xc, -x+yc);
        break;
    case 6:
        glColor3d(255, 255, 255);
        glVertex2i(y+xc, -x+yc);
        break;
    case 7:
        glColor3d(255, 255, 255);
        glVertex2i(x+xc, -y+yc);
        break;
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Experiment 01");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutMainLoop();
}
