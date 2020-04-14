from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
from time import time

frameNum = 0
lastTime = int(time())

def draw():
    global frameNum, lastTime

    frameNum += 1

    if time() > lastTime + 1:
        print(f'{frameNum} fps')
        lastTime = time()
        frameNum = 0


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)


if __name__ == '__main__':
    glutInit()
    glutInitDisplayMode(GLUT_RGBA)
    glutInitWindowSize(500, 500)
    glutInitWindowPosition(0, 0)
    wind = glutCreateWindow("Hello OpenGL")
    glutDisplayFunc(draw)
    glutIdleFunc(draw)

    glutMainLoop()