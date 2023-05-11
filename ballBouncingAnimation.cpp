#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <bits/stdc++.h>

#define WIDTH 1000
#define HEIGHT 1000
#define XC  0
#define YC  400
#define G 0.06
#define NUM 30

void drawPixel(int x, int y, int zone);
void drawEllipse(int a, int b);
void draw4way(int x, int y);

double xc, yc, diffA, diffB;
double a = 97, b = 97;
double dy;
int flatCount;
int state = -1;
int flag = 1;

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

    glPointSize(1);
    glBegin(GL_POINTS);
    getchar();

    

    if( yc - b < -HEIGHT / 2 && state == -1){
        diffB = dy / 5;
        diffA = (a * diffB)/(b - diffB);
        state = 0;
    }
    
    if( yc >= YC){
        if(state == 1)
            dy = 0;
        state = -1;
    }


    if(state == 0){
        if(flag == 1){
            a += diffA; b -= diffB;
            flatCount++;
            if(flatCount >= NUM){
                flatCount = 0;
                flag = 0;
            }
            yc -= diffB;
        }
        else {
            a -= diffA; b += diffB;
            flatCount++;
            if(flatCount >= NUM){
                flatCount = 0;
                flag = 1;
                state = 1;
            }
            yc += diffB;
        }

        
    }
    

    yc += state * dy;

    if(yc - b <= -HEIGHT / 2 && state == -1){
        yc = -HEIGHT / 2 + b;
        state = 0;
        diffB = dy / 5;
        diffA = (a * diffB)/(b - diffB);
    }
         

    dy += -1 * state * G;

    drawEllipse(a, b);
    
    glEnd();

    glutSwapBuffers();
}

static void idle(void)
{
    glutPostRedisplay();
}

void drawEllipse(int a, int b)
{
    int x = 0, y = b;
    int d = 4 * (b*b - a*a*b) + a*a;
    int delE = 4*b*b * (2*x + 3);
    int delSE = 4*b*b * (2*x + 3) + 4*a*a * (2 - 2*y);

    draw4way(x, y);

    while(2*b*b*(x + 1) < a*a*(2*y - 1)){
        if(d < 0){
            d += 4*b*b*(2*x + 3);
            x++;
        }
        else{
            d += 4*b*b * (2*x + 3) + 4*a*a * (2 - 2*y);
            x++;
            y--;
        }
        draw4way(x, y);
    }

    while(y > 0){
        if(d < 0){
            d += 4*b*b * (2*x + 3) + 4*a*a * (2 - 2*y);
            x++;
            y--;
        }
        else{
            d += 4*a*a * (2 - 2*y);
            y--;
        }
        draw4way(x, y);
    }
}


void draw4way(int x, int y)
{
    drawPixel(x, y, 0);
    drawPixel(x, y, 3);
    drawPixel(x, y, 4);
    drawPixel(x, y, 7);
}


void drawPixel (int x, int y, int zone)
{
    glColor3d(0, 255, 0);
    switch (zone)
    {
    case 0:
        glVertex2i(x + xc, y + yc);
        break;
    case 3:
        glVertex2i(-x + xc, y + yc);
        break;
    case 4:
        glVertex2i(-x + xc, -y + yc);
        break;
    case 7:
        glVertex2i(x + xc, -y + yc);
        break;
    }
}

int main(int argc, char *argv[])
{
    xc = XC;
    yc = YC;
    dy = 0;
    flatCount = 0;

    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Experiment 01");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}