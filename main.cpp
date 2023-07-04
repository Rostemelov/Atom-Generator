#include <stdio.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include<cmath>
//______________________________________________________________________________________________________________________
int option=0,atno=0;
int k=75,l=150,m=225;
float pi=3.14159,t=0;
//___________________________________________________________________________________________________________________________________
void acceptui()
{
    printf("Enter an atomic number less than or equal to 18");
    scanf("%d", &atno);
}
//_____________________________________________________________________________________________________________________
void init()
{
    glClearColor(0.0,0.0,0.0,1.0);
    gluOrtho2D(-500,500,-500,500);
}
//_______________________________________________________________________________________________________________________
void orbit(int r)
{
    glBegin(GL_POINTS);
    glColor3f(1.0,0.7,0.1);
    glPointSize(10.0);
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;

    while (x <= y) {
        // Plot points for one octant of the circle
        glVertex2i(x, y);
        glVertex2i(-x, y);
        glVertex2i(x, -y);
        glVertex2i(-x, -y);
        glVertex2i(y, x);
        glVertex2i(-y, x);
        glVertex2i(y, -x);
        glVertex2i(-y, -x);


        // Update coordinates and decision variable
        if (d < 0) {
            d += 4 * x + 6;
        } else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
    glEnd();
}
//__________________________________________________________________________________________________________________________
void nucleus()
{
glBegin(GL_POLYGON);
glColor3f(0.2,0.6,1.0);
    for (int i = 0; i < 360; ++i)
    {
        float angle = 2.0 * pi * static_cast<float>(i) / static_cast<float>(360);
        float x = 25 * cos(angle);
        float y = 25 * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}
//_________________________________________________________________________________________________________________________
void electron(float x1,float y1)
{
glBegin(GL_POLYGON);
glColor3f(0.5,1.0,0.1);
    for (int i = 0; i < 360; ++i)
    {
        float angle = 2.0 * pi * static_cast<float>(i) / static_cast<float>(360);
        float x = x1+7 * cos(angle);
        float y = y1+7 * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}
//_________________________________________________________________________________________________________________________________________________
void write(float x, float y, void* font, const char* string)
{
    const char* c;
    glRasterPos2f(x, y);

    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}
//___________________________________________________________________________________________________________________________________________
void atom()
{
    if(atno>=1)
    {
        orbit(k);
        electron(k,0);
    }
    if(atno>=2)
    {
        electron(-k,0);
    }
    if(atno>=3)
    {
        orbit(l);
        electron(0,l);
    }
    if(atno>=4)
    {
        electron(0,-l);
    }
    if(atno>=5)
    {
        electron(l,0);
    }
    if(atno>=6)
    {
        electron(-l,0);
    }
    if(atno>=7)
    {
        electron(l*cos(45),l*sin(45));
    }
    if(atno>=8)
    {
        electron(-l*cos(45),l*sin(45));
    }
    if(atno>=9)
    {
        electron(-l*cos(45),-l*sin(45));
    }
    if(atno>=10)
    {
        electron(l*cos(45),-l*sin(45));
    }
    if(atno>=11)
    {
        orbit(m);
        electron(0,m);
    }
    if(atno>=12)
    {
        electron(0,-m);
    }
    if(atno>=13)
    {
        electron(m,0);
    }
    if(atno>=14)
    {
        electron(-m,0);
    }
    if(atno>=15)
    {
        electron(m*cos(45),m*sin(45));
    }
    if(atno>=16)
    {
        electron(-m*cos(45),m*sin(45));
    }
    if(atno>=17)
    {
        electron(-m*cos(45),-m*sin(45));
    }
    if(atno>=18)
    {
        electron(m*cos(45),-m*sin(45));
}
}
//_____________________________________________________________________________________________________________________________________
void home()
{
    glColor3f(1.0,1.0,1.0);
    glColor3f(1.0,1.0,1.0);
    write(-50,200,GLUT_BITMAP_HELVETICA_12,"Project By:");
    write(-200,100,GLUT_BITMAP_HELVETICA_12,"Sai Harshit B");
    write(100,100,GLUT_BITMAP_HELVETICA_12,"1BY20CS162");
    write(-200,0,GLUT_BITMAP_HELVETICA_12,"S Guru Prasad");
    write(100,0,GLUT_BITMAP_HELVETICA_12,"1BY20CS154");
    write(-100,-100,GLUT_BITMAP_HELVETICA_12,"Department of CSE, BMSIT&M");
    glEnd();
}
//________________________________________________________________________________________________________________________________________
void elem(int n)
{
    if(n==11)
    {
        acceptui();
    }
    else
    {atno=n;}
}
//_________________________________________________________________________________________________________________________________________
void opt(int n)
{
    option=n;
    if(n==3)
    {
        exit(0);
    }
}
//_________________________________________________________________________________________________________________________________________
void display()
{
       glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    write(-125, 300, GLUT_BITMAP_TIMES_ROMAN_24, "ATOM GENERATOR");

    if (atno == 0) {
        home();
    } else {
        glPushMatrix(); // Save the current transformation matrix

        nucleus();

        if (option == 1) {
            t += 0.1; // Increment the rotation angle
        }

        glTranslatef(0.0, 0.0, 0.0); // Translate the atom position

        // Draw the atom with its transformations
        glPushMatrix();
        glRotatef(t, 0, 0, 1); // Apply rotation only to the atom
        atom();
        glPopMatrix();

        glPopMatrix(); // Restore the previous transformation matrix
    }

    glutPostRedisplay();
    glutSwapBuffers();
}
//_______________________________________________________________________________________________________________________________
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(1000,1000);
    glutInitWindowPosition(10,10);
    glutCreateWindow("Atom Generator");
    init();
    glutDisplayFunc(display);
    glutCreateMenu(elem);
    glutAddMenuEntry("Home",0);
    glutAddMenuEntry("Hydrogen",1);
    glutAddMenuEntry("Helium",2);
    glutAddMenuEntry("Lithium",3);
    glutAddMenuEntry("Beryllium",4);
    glutAddMenuEntry("Boron",5);
    glutAddMenuEntry("Carbon",6);
    glutAddMenuEntry("Nitrogen",7);
    glutAddMenuEntry("Oxygen",8);
    glutAddMenuEntry("Fluorine",9);
    glutAddMenuEntry("Neon",10);
    glutAddMenuEntry("Enter Atomic Number in Terminal", 11);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutCreateMenu(opt);
    glutAddMenuEntry("Start Animation",1);
    glutAddMenuEntry("Stop Animation",2);
    glutAddMenuEntry("Exit",3);
    glutAttachMenu(GLUT_LEFT_BUTTON);
    glutMainLoop();
    return 0;
}
