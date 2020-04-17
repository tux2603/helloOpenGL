
#include <chrono>
#include <fstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>

GLuint shaderProgramID = -1;

GLuint loadShaders(std::string vertexFile, std::string fragmentFile) {
    //Create the shaders
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Load the vertex shader data
    std::ifstream vertStream(vertexFile);
    std::stringstream vertBuffer;
    vertBuffer << vertStream.rdbuf();
    const char *vertData = vertBuffer.str().c_str();
    

    // Load the fragment shader data
    std::ifstream fragStream(fragmentFile);
    std::stringstream fragBuffer;
    fragBuffer << fragStream.rdbuf();
    const char *fragData = fragBuffer.str().c_str();

    // Compile the vertex shader
    glShaderSource(vertShader, 1, &vertData, NULL);
    glCompileShader(vertShader);

    // Compile the fragment shader
    glShaderSource(fragShader, 1, &fragData, NULL);
    glCompileShader(fragShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertShader);
    glAttachShader(shaderProgram, fragShader);

    // Delete the extra data from memory
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    return shaderProgram;
}

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

    glUseProgram(shaderProgramID);

    drawFigure(100, 100, 100 + 50 * cos(timeNow*10), 100 + 50 * (sin(timeNow*10)));
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

    glewInit();
    loadShaders("shaders/vertexShader.vert", "shaders/prettyGreen.frag");
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}