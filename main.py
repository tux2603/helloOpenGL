from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
from time import time
from math import sin

frameNum = 0
lastTime = int(time())

def drawRectangle(location, size, color=(0, 1.0, 0.5)):

    c0 = (location[0], location[1])
    c1 = (location[0] + size[0], location[1])
    c2 = (location[0] + size[0], location[1] + size[1])
    c3 = (location[0], location[1] + size[1])

    glBegin(GL_QUADS)
    glColor3fv(color)
    glVertex2fv(c0)
    glVertex2fv(c1)
    glVertex2fv(c2)
    glVertex2fv(c3)
    glEnd()

def setView():

    # Create and load the view matrix
    glViewport(0, 0, 500, 500)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()

    # Create and load the projection matrix
    glOrtho(0, 500, 0, 500, 0, 1)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()

def draw():
    global frameNum, lastTime

    # Compute and print FPS
    frameNum += 1
    if time() > lastTime + 1:
        print(f'{frameNum} fps')
        lastTime = time()
        frameNum = 0

    # Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()

    # Draw a little rectangle
    drawRectangle((100, 100), (100, 100 + 50 * sin(time()*4)))

    glutSwapBuffers()


if __name__ == '__main__':
    glutInit()
    glutInitDisplayMode(GLUT_RGBA)
    glutInitWindowSize(500, 500)
    glutInitWindowPosition(0, 0)
    wind = glutCreateWindow("Hello OpenGL")
    glutDisplayFunc(draw)
    glutIdleFunc(draw)

    setView()
    glutMainLoop()