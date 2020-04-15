
#include <GL/glut.h>
#include <chrono>
#include <iostream>
#include <math.h>
#include <cstring>

void drawRectangle(float x, float y, float width, float height, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x+width, y);
    glVertex2f(x+width, y+height);
    glVertex2f(x, y+height);
    glEnd();
}

void drawString(float x, float y, char *str) {
    glColor3f(1, 1, 1);
    glRasterPos2f(x, y);
    for(size_t i = 0; i < strlen(str); ++i)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *(str + i));
    glEnd();
}

void setView() {
    glViewport(0, 0, 500, 500);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, 500, 0, 500, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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

    setView();

    drawRectangle(100, 100, 100, 100 + 50 * sin(timeNow * 10), 0, 1, 0.5f);
    
    char *fpsStr = new char[24];
    sprintf(fpsStr, "Hello OpenGL!  %dfps", currentFPS);
    drawString(5, 5, fpsStr);
    delete[] fpsStr;

    glutSwapBuffers();
}

int main(int argc, char **argv) {
    // initialize glut
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