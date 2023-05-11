#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <bits/stdc++.h>

using namespace std;
#define WIDTH 512
#define HEIGHT 512

int maxHeight =HEIGHT/2-1 ;
int minHeight =-HEIGHT/2 ;
int maxWidth =WIDTH/2-1 ;
int minWidth =-WIDTH/2 ;
int top = 8;
int bottom = 4;
int right_ = 2;
int left_ = 1;


int maxy = 100;
int miny = -100;
int maxx = 100;
int minx = -100;



void findZone(int x0, int y0, int x1, int y1);
void drawLine0(int x0, int y0, int x1, int y1, int zone);
void drawPixel(int x, int y, int zone);
void drawGrid(void);
void clipLine(int x0,int y0,int x1,int y1);
int findTx(int x0, int x1, float t);
int findTy(int y0, int y1, float t);


static void resize(int width, int height)
{
    const float ar = (float)width / (float)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WIDTH / 2, WIDTH / 2, -HEIGHT / 2, HEIGHT / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glColor3d(1, 1, 1);
    // glBegin(GL_LINES);
    // glVertex2i(-WIDTH / 2, 0);
    // glVertex2i(WIDTH / 2, 0);
    // glVertex2i(0, -HEIGHT / 2);
    // glVertex2i(0, HEIGHT / 2);
    // glEnd();

    glColor3f(0.2, 0.2, 0.2);
    drawGrid();

    glPointSize(2);
    glBegin(GL_POINTS);

    int x0 = -200;
    int x1 = 150;
    int y0 = 120;
    int y1 = -120;

    cin >> x0 >> y0 >> x1 >> y1;
    
    clipLine(x0,y0,x1,y1);

    cout << "Line Drawn" << endl;
    cout << endl;

    glEnd();

    

    glutSwapBuffers();
}

static void idle(void)
{
    glutPostRedisplay();
}


int findTx(int x0, int x1, float t) {
    return (x0 + t*(x1 - x0));
}

int findTy(int y0, int y1, float t) {
    return (y0 + t*(y1 - y0));
}

void drawGrid(void){
    glBegin(GL_LINES);
    glVertex2i(minx,minHeight);
    glVertex2i(minx,maxHeight);
    glVertex2i(maxx,minHeight);
    glVertex2i(maxx,maxHeight);
    glVertex2i(minWidth,maxy);
    glVertex2i(maxWidth,maxy);
    glVertex2i(minWidth,miny);
    glVertex2i(maxWidth,miny);

    glEnd();
}

void clipLine(int x0,int y0,int x1,int y1){
    float t,temax = 0.0,tlmin = 1.0;

    t = -(float)(y0-maxy)/(y1-y0);
    if(y1-y0>=0){
        tlmin = min(tlmin,t);
    } else{
        temax = max(temax,t);
    }

    t = -(float)(y0-(miny))/(y1-y0);
    if(-(y1-y0)>=0){
        tlmin = min(tlmin,t);
    } else{
        temax = max(temax,t);
    }

    t = -(float)(x0-maxx)/(x1-x0);
    if((x1-x0)>=0){
        tlmin = min(tlmin,t);

    } else{
        temax = max(temax,t);
    }

    t = -(float)(x0-minx)/(x1-x0);
    if(-(x1-x0)>=0){
        tlmin = min(tlmin,t);
    } else{
        temax = max(temax,t);
    }

    if(tlmin<=1.0 && temax>=0.0 && tlmin>=temax){
        int px0 = findTx(x0, x1, tlmin);
        int py0 = findTy(y0, y1, tlmin);
        int px1 = findTx(x0, x1, temax);
        int py1 = findTy(y0, y1, temax);
        glEnd();
        glPointSize(5);
        glColor3f(1.0,1.0,1.0);

        glBegin(GL_POINTS);
        glVertex2i(px0,py0);
        glVertex2i(px1,py1);
        glVertex2i(x0,y0);
        glVertex2i(x1,y1);
        glEnd();
        glPointSize(1);
        glBegin(GL_POINTS);
        findZone(px0,py0,px1,py1);
        findZone(x0,y0,px1,py1);
        findZone(px0,py0,x1,y1);
    }
    else{
        cout<<"Rejected"<<endl;
        glEnd();
        glPointSize(5);
        glColor3f(1.0,1.0,1.0);

        glBegin(GL_POINTS);
        glVertex2i(x0,y0);
        glVertex2i(x1,y1);
        glEnd();
        glPointSize(1);
        glBegin(GL_POINTS);
        findZone(x0,y0,x1,y1);
    }

}

void findZone(int x0, int y0, int x1, int y1) {
    int dx = x1 - x0, dy = y1 - y0;

    if (abs(dx) >= abs(dy))
    { // 0, 3, 4, 7
        if (dx >= 0 && dy >= 0){ // zone 0
            glColor3ub(255, 255, 255); // white
            drawLine0(x0, y0, x1, y1, 0);
        }
        else if (dx < 0 && dy >= 0){ // zone 3
            glColor3ub(255, 0, 0); // red
            drawLine0(-x0, y0, -x1, y1, 3);
        }
        else if (dx < 0 && dy < 0){ // zone 4
            glColor3ub(0, 255, 0); // green
            drawLine0(-x0, -y0, -x1, -y1, 4);
        }
        else{ // zone 7
            glColor3ub(0, 0, 255); // blue
            drawLine0(x0, -y0, x1, -y1, 7);
        }
    }
    else
    { // 1, 2, 5, 6
        if (dx >= 0 && dy >= 0){ // zone 1
            glColor3ub(255, 255, 0); // yellow 
            drawLine0(y0, x0, y1, x1, 1);
        }
        else if (dx < 0 && dy >= 0){
            glColor3ub(0, 100, 100); // cyan
            drawLine0(y0, -x0, y1, -x1, 2);
        }
        else if (dx < 0 && dy < 0){
            glColor3ub(255, 191, 0); // orange
            drawLine0(-y0, -x0, -y1, -x1, 5);
        }
        else{
            glColor3ub(128, 128, 128); // gray
            drawLine0(-y0, x0, -y1, x1, 6);
        }
    }
}

void drawLine0(int x0, int y0, int x1, int y1, int zone)
{

    int dx = x1 - x0, dy = y1 - y0;
    int delE = 2 * dy, delNE = 2 * (dy - dx);
    int d = 2 * dy - dx;
    int x = x0, y = y0;

    drawPixel(x0, y0, zone);

    while (x < x1)
    {
        if (d < 0)
        { // delE
            d += delE;
            x++;
        }
        else
        { // delNE
            d += delNE;
            x++;
            y++;
        }

        drawPixel(x, y, zone);
    }
}


void drawPixel(int x, int y, int zone)
{
    switch (zone){
        case 0:
            glVertex2i(x, y);
            break;
        case 1:
            glVertex2i(y, x);
            break;
        case 2:
            glVertex2i(-y, x);
            break;
        case 3:
            glVertex2i(-x, y);
            break;
        case 4:
            glVertex2i(-x, -y);
            break;
        case 5:
            glVertex2i(-y, -x);
            break;
        case 6:
            glVertex2i(y, -x);
            break;
        case 7:
            glVertex2i(x, -y);
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

    return EXIT_SUCCESS;
}