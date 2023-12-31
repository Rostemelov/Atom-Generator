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
    printf("Enter an atomic number less than or equal to 18:\n");
    scanf("%d", &atno);
    if(atno>18)
    {
        atno=0;
    }
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
    write(-125, 400, GLUT_BITMAP_TIMES_ROMAN_24, "ATOM GENERATOR");
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

        switch(atno)
        {
        case 1: glColor3f(0.5,0.7,1.0);
                write(-50,300,GLUT_BITMAP_HELVETICA_18,"HYDROGEN");
                glColor3f(1.0,0.0,0.0);
                write(-20,-5,GLUT_BITMAP_HELVETICA_10,"p=1,n=0");
                break;
        case 2: glColor3f(0.5,0.7,1.0);
            write(-50,300,GLUT_BITMAP_HELVETICA_18,"HELIUM");
                glColor3f(1.0,0.0,0.0);
                write(-20,-5,GLUT_BITMAP_HELVETICA_10,"p=2,n=2");
                break;
        case 3: glColor3f(0.5,0.7,1.0);
            write(-50,300,GLUT_BITMAP_HELVETICA_18,"LITHIUM");
                glColor3f(1.0,0.0,0.0);
                write(-20,-5,GLUT_BITMAP_HELVETICA_10,"p=3,n=4");
                break;
        case 4: glColor3f(0.5,0.7,1.0);
            write(-50,300,GLUT_BITMAP_HELVETICA_18,"BERYLLIUM");
                glColor3f(1.0,0.0,0.0);
                write(-20,-5,GLUT_BITMAP_HELVETICA_10,"p=4,n=5");
                break;
        case 5: glColor3f(0.5,0.7,1.0);
            write(-50,300,GLUT_BITMAP_HELVETICA_18,"BORON");
            glColor3f(1.0,0.0,0.0);
                write(-20,-5,GLUT_BITMAP_HELVETICA_10,"p=5,n=6");
                break;
        case 6: glColor3f(0.5,0.7,1.0);
            write(-50,300,GLUT_BITMAP_HELVETICA_18,"CARBON");
            glColor3f(1.0,0.0,0.0);
                write(-20,-5,GLUT_BITMAP_HELVETICA_10,"p=6,n=6");
                break;
        case 7: glColor3f(0.5,0.7,1.0);
            write(-50,300,GLUT_BITMAP_HELVETICA_18,"NITROGEN");
                write(-20,-5,GLUT_BITMAP_HELVETICA_10,"p=7,n=7");
                break;
        case 8: glColor3f(0.5,0.7,1.0);
            write(-50,300,GLUT_BITMAP_HELVETICA_18,"OXYGEN");
            glColor3f(1.0,0.0,0.0);
                write(-20,-5,GLUT_BITMAP_HELVETICA_10,"p=8,n=8");
                break;
        case 9: glColor3f(0.5,0.7,1.0);
            write(-50,300,GLUT_BITMAP_HELVETICA_18,"FLUORINE");
            glColor3f(1.0,0.0,0.0);
                write(-22,-5,GLUT_BITMAP_HELVETICA_10,"p=9,n=10");
                break;
        case 10: glColor3f(0.5,0.7,1.0);
            write(-50,300,GLUT_BITMAP_HELVETICA_18,"NEON");
            glColor3f(1.0,0.0,0.0);
                 write(-25,-5,GLUT_BITMAP_HELVETICA_10,"p=10,n=10");
                 break;
        case 11: glColor3f(0.5,0.7,1.0);
            write(-50,300,GLUT_BITMAP_HELVETICA_18,"SODIUM");
            glColor3f(1.0,0.0,0.0);
                 write(-20,-5,GLUT_BITMAP_HELVETICA_10,"p=11,n=12");
                 break;
        case 12: glColor3f(0.5,0.7,1.0);
            write(-50,300,GLUT_BITMAP_HELVETICA_18,"MAGNESIUM");
            glColor3f(1.0,0.0,0.0);
                 write(-25,-5,GLUT_BITMAP_HELVETICA_10,"p=12,n=12");
                 break;
        case 13: glColor3f(0.5,0.7,1.0);
            write(-50,300,GLUT_BITMAP_HELVETICA_18,"ALUMINIUM");
            glColor3f(1.0,0.0,0.0);
                 write(-25,-5,GLUT_BITMAP_HELVETICA_10,"p=13,n=14");
                 break;
        case 14: glColor3f(0.5,0.7,1.0);
            write(-50,300,GLUT_BITMAP_HELVETICA_18,"SILICON");
            glColor3f(1.0,0.0,0.0);
                 write(-25,-5,GLUT_BITMAP_HELVETICA_10,"p=14,n=14");
                 break;
        case 15: glColor3f(0.5,0.7,1.0);
            write(-50,300,GLUT_BITMAP_HELVETICA_18,"PHOSPHORUS");
            glColor3f(1.0,0.0,0.0);
                 write(-25,-5,GLUT_BITMAP_HELVETICA_10,"p=15,n=16");
                 break;
        case 16: glColor3f(0.5,0.7,1.0);
            write(-50,300,GLUT_BITMAP_HELVETICA_18,"SULFUR");
            glColor3f(1.0,0.0,0.0);
                 write(-25,-5,GLUT_BITMAP_HELVETICA_10,"p=16,n=16");
                 break;
        case 17: glColor3f(0.5,0.7,1.0);
            write(-50,300,GLUT_BITMAP_HELVETICA_18,"CHLORINE");
            glColor3f(1.0,0.0,0.0);
                 write(-25,-5,GLUT_BITMAP_HELVETICA_10,"p=17,n=18");
                 break;
        case 18: glColor3f(0.5,0.7,1.0);
            write(-50,300,GLUT_BITMAP_HELVETICA_18,"ARGON");
            glColor3f(1.0,0.0,0.0);
                 write(-25,-5,GLUT_BITMAP_HELVETICA_10,"p=18,n=22");
                 break;
        }
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
