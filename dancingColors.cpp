
#include <chrono>
#include <fstream>
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>

void setView(GLint x, GLint y, GLint width, GLint height) {
    glViewport(x, y, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, 1, 0, 1, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void setView() {
    glViewport(0, 0, 500, 500);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, 500, 0, 500, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawString(float x, float y, std::string str) {
    glColor3f(1, 1, 1);
    glRasterPos2f(x, y);
    for(size_t i = 0; i < str.length(); ++i)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str[i]);
    glEnd();
}

void drawFigure(GLint x, GLint y, GLint w, GLint h) {
    setView(x, y, w, h);
    glBegin(GL_TRIANGLES);
    glColor3f(0, 0, 1); glVertex2f(0.5, 0.0); 
    glColor3f(0, 1, 1); glVertex2f(1.0, 0.5); 
    glColor3f(0, 1, 0); glVertex2f(1.0, 1.0); 
    glColor3f(0, 1, 0); glVertex2f(1.0, 1.0); 
    glColor3f(0, 1, 1); glVertex2f(0.5, 1.0); 
    glColor3f(0, 0, 1); glVertex2f(0.0, 0.5); 
    glColor3f(1, 0, 0); glVertex2f(0.0, 0.0); 
    glColor3f(0, 0, 1); glVertex2f(0.5, 0.0); 
    glColor3f(0, 1, 0); glVertex2f(1.0, 1.0); 
    glColor3f(0, 1, 0); glVertex2f(1.0, 1.0); 
    glColor3f(1, 0, 0); glVertex2f(0.0, 0.0); 
    glColor3f(0, 0, 1); glVertex2f(0.0, 0.5); 
    glEnd();
}

void drawRectangle(float x, float y, float width, float height) {
    setView(x, y, width, height);
    glBegin(GL_QUADS);
    glColor3f(0, 0, 1);
    glVertex2f(0, 0);
    glColor3f(1, 0, 1);
    glVertex2f(1, 0);
    glColor3f(1, 1, 1);
    glVertex2f(1, 1);
    glColor3f(0, 1, 1);
    glVertex2f(0, 1);
    glEnd();
}

void display() {
    // Calculate and print fps
    static double lastTime = 0;
    static int numFrames = 0;
    static int currentFPS = 0;

    double timeNow = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::system_clock::now().time_since_epoch()).count();
    
    ++numFrames;

    if(timeNow - lastTime > 1) {
        lastTime = timeNow;
        currentFPS = numFrames;
        numFrames = 0;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glLoadIdentity();

    drawFigure(100 + 10 * (sin(timeNow*10)), 100 + 10 * cos(timeNow*10), 100 + 50 * cos(timeNow*10), 100 + 50 * (sin(timeNow*10)));
    drawFigure(400, 300, 50, 50);
    
    setView();

    char *fpsStr = new char[24];
    sprintf(fpsStr, "Hello OpenGL!  %dfps", currentFPS);
    drawString(5, 5, fpsStr);
    delete[] fpsStr;

    glutSwapBuffers();

}

int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hello OpenGL");

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}