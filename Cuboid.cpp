/*NAME: Rahul Roy
  ENROLLMENT: IIT2019194 */

#if defined(_APPLE) && defined(MACH_)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // GLUT, include glu.h and gl.h

using namespace std;
GLfloat xRotated, yRotated, zRotated;
GLdouble radius = 0.5;
GLfloat qaBlack[] = {0.5, 0.5, 0.5, 1.0}; //Black Color
GLfloat qaGreen[] = {0.1, 0.9, 0.4, 1.0}; //Green Color
GLfloat qaWhite[] = {1.0, 1.0, 1.0, 1.0}; //White Color
GLfloat qaRed[] = {1.0, 0.0, 0.0, 1.0};   //Red Color
// Set lighting intensity and color
GLfloat qaAmbientLight[] = {0.2, 0.2, 0.2, 1.0};
GLfloat qaDiffuseLight[] = {0.8, 0.8, 0.8, 1.0};
GLfloat qaSpecularLight[] = {1.0, 1.0, 1.0, 1.0};
// Light source position
GLfloat qaLightPosition[] = {1.0, 2.5, -3.5, 0.5};
void display(void);
void reshape(int x, int y);
void idleFunc(void)
{
    zRotated += 0.02;
    display();
}
void initLighting()
{
    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    // Set lighting intensity and color
    glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);
    // Set the light position
    glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
}
void drawLongCube(GLfloat size, int length, char vector)
{
    for (int i = 0; i < length; i++)
    {
        glutSolidCube(size);

        if (vector == 'x')
        {
            glTranslatef(size, 0, 0);
        }
        else if (vector == 'y')
        {
            glTranslatef(0, size, 0);
        }
        else if (vector == 'z')
        {
            glTranslatef(0, 0, size);
        }
    }
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(350, 350);
    glutCreateWindow("Solid Sphere");
    initLighting();
    xRotated = yRotated = zRotated = 0.0;
    glutIdleFunc(idleFunc);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
void display(void)
{
    glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
    // clear the identity matrix.
    glLoadIdentity();
    // traslate the draw by z = -4.0
    // Note this when you decrease z like -8.0 the drawing will looks far , or smaller.
    glTranslatef(0.0, 0.0, -5.0);
    // scaling transfomation
    glScalef(1.0, 1.0, 1.0);
    glRotatef(zRotated, 0.0, 0.0, 1.0);
    // Set material properties
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaGreen);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, qaGreen);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, qaWhite);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);
    // built-in (glut library) function , draw you a sphere.
    //glutSolidSphere(radius,25,25);
    //glutSolidCube(1.0f);
    drawLongCube(1.0f, 2.0f, 'x');
    // Flush buffers to screen
    glFlush();
    glutSwapBuffers();
    // sawp buffers called because we are using double buffering
    // glutSwapBuffers();
}
void reshape(int x, int y)
{
    if (y == 0 || x == 0)
        return;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(39.0, (GLdouble)x / (GLdouble)y, 0.6, 21.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, x, y); //Use the whole window for rendering
}