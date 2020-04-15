from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.arrays import vbo
from time import time
from math import sin
from PIL import Image
import numpy as np

frameNum = 0
lastTime = int(time())

def drawRectangle(location, size, color=(0, 1.0, 0.5)):
    # Compute the locations of the vertices of the rectangle
    c0 = (location[0], location[1])
    c1 = (location[0] + size[0], location[1])
    c2 = (location[0] + size[0], location[1] + size[1])
    c3 = (location[0], location[1] + size[1])

    # Load the color buffer to openGL
    glColor3fv(color)

    # Set the draw mode. Since this is a simple rectangle, quads will do just dandy
    glBegin(GL_QUADS)

    # Draw the vertices
    glVertex2fv(c0)
    glVertex2fv(c1)
    glVertex2fv(c2)
    glVertex2fv(c3)

    # Done drawing now
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


    glEnable(GL_BLEND)
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)

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
    # glutDisplayFunc(draw)
    glutIdleFunc(draw)

    setView()
    glutMainLoop()