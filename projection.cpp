/*
     ALGO - 2
*/
 
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
 
#include <bits/stdc++.h>
 
using namespace std;
 
 
static int slices = 16;
static int stacks = 16;
#define LINE_COUNT 10
int d = 600, L = 400, A = 200;
float Qx=0,Qy=0,Qz=0;




struct Point2D {
    int x, y;
    Point2D(int _x, int _y) {
            x = _x;
            y = _y;
        }
    Point2D(){}
};
 
struct Point3D {
    int x, y, z;
    Point3D(int _x, int _y, int _z) {
            x = _x;
            y = _y;
            z = _z;
        }
    Point3D(){}
};
 
vector<Point3D> P3D;
vector<Point3D> P3D2;
vector<Point2D> P2D;

















 
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


void generatePoints() {
    P3D.push_back(Point3D(-A, -A, A));
    P3D.push_back(Point3D(A, -A, A));
    P3D.push_back(Point3D(A, A, A));
    P3D.push_back(Point3D(-A, A, A));
    P3D.push_back(Point3D(-A, -A, -A));
    P3D.push_back(Point3D(A, -A, -A));
    P3D.push_back(Point3D(A, A, -A));
    P3D.push_back(Point3D(-A, A, -A));
}


void generateRotation() {
    float matrix[4][4] = {
        {cos(Qy)*cos(Qz), sin(Qx)*sin(Qy)*cos(Qz)-cos(Qx)*sin(Qz), cos(Qx)*sin(Qy)*cos(Qz)+sin(Qx)*sin(Qz) },
        { cos(Qy)*sin(Qz), sin(Qx)*sin(Qy)*sin(Qz)+cos(Qx)*cos(Qz), cos(Qx)*sin(Qy)*sin(Qz)-sin(Qx)*cos(Qz) },
        { -sin(Qy), sin(Qx)*cos(Qy), cos(Qx)*cos(Qy) },
    };

    for(int i = 0; i<8; i++) {
        float x = matrix[0][0]*P3D[i].x + matrix[0][1]*P3D[i].y + matrix[0][2]*(P3D[i].z);
        float y = matrix[1][0]*P3D[i].x + matrix[1][1]*P3D[i].y + matrix[1][2]*(P3D[i].z); 
        float z = matrix[2][0]*P3D[i].x + matrix[2][1]*P3D[i].y + matrix[2][2]*(P3D[i].z); 
        float w = matrix[3][0]*P3D[i].x + matrix[3][1]*P3D[i].y + matrix[3][2]*(P3D[i].z); 

        P3D2.push_back(Point3D(x, y, z));
    }
}

void generateProjection(float matrix[][4]){
    for(int i = 0; i<8; i++) {
        float x = matrix[0][0]*P3D[i].x + matrix[0][1]*P3D[i].y + matrix[0][2]*(P3D[i].z - d - L) + matrix[0][3];
        float y = matrix[1][0]*P3D[i].x + matrix[1][1]*P3D[i].y + matrix[1][2]*(P3D[i].z - d - L) + matrix[1][3];
        float z = matrix[2][0]*P3D[i].x + matrix[2][1]*P3D[i].y + matrix[2][2]*(P3D[i].z - d - L) + matrix[2][3];
        float w = matrix[3][0]*P3D[i].x + matrix[3][1]*P3D[i].y + matrix[3][2]*(P3D[i].z - d - L) + matrix[3][3];
 
        P2D.push_back(Point2D(x/w, y/w));
        cout<<P2D[i].x<< P2D[i].y<<endl;
    }
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


void makeCube(){
    drawLine(P2D[0].x, P2D[0].y, P2D[1].x, P2D[1].y);
    drawLine(P2D[2].x, P2D[2].y, P2D[1].x, P2D[1].y);
    drawLine(P2D[3].x, P2D[3].y, P2D[2].x, P2D[2].y);
    drawLine(P2D[0].x, P2D[0].y, P2D[3].x, P2D[3].y);
 
    drawLine(P2D[4].x, P2D[4].y, P2D[5].x, P2D[5].y);
    drawLine(P2D[6].x, P2D[6].y, P2D[5].x, P2D[5].y);
    drawLine(P2D[6].x, P2D[6].y, P2D[7].x, P2D[7].y);
    drawLine(P2D[4].x, P2D[4].y, P2D[7].x, P2D[7].y);
 
    drawLine(P2D[0].x, P2D[0].y, P2D[4].x, P2D[4].y);
    drawLine(P2D[5].x, P2D[5].y, P2D[1].x, P2D[1].y);
    drawLine(P2D[2].x, P2D[2].y, P2D[6].x, P2D[6].y);
    drawLine(P2D[3].x, P2D[3].y, P2D[7].x, P2D[7].y);


    P3D.clear();
    P3D2.clear();
    P2D.clear();





}




 
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

    float matrix[4][4] = {
        {1.0, 0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0, 0.0},
        {0.0, 0.0,float(-1.0/d), 0.0},
    };


    generatePoints();
    generateRotation();
    generateProjection(matrix);
    makeCube();  
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

void specialKey(int key, int x, int y) {
    switch (key){
        case GLUT_KEY_UP:
            Qy += 0.1;
            break;
        case GLUT_KEY_DOWN:
            Qy -= 0.1;
            break;
        case GLUT_KEY_LEFT:
            Qx += 0.1;
            break;
        case GLUT_KEY_RIGHT:
            Qx -= 0.1;
            break;
        case GLUT_KEY_F1:
            Qz -= 0.1;
            break;
        case GLUT_KEY_F2:
            Qz += 0.1;
            break;
    }     
}
​
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
    glutSpecialFunc(specialKey);
    glutIdleFunc(idle);
 
    glutMainLoop();
 
    return EXIT_SUCCESS;
}


///g++ draw8way2.cpp -o draw8way2 -lglut -lGLU -lGL &&./draw8way2