from OpenGL.GL import *
from OpenGL.GL import shaders
from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.arrays import vbo
from time import time
from math import sin, cos
from PIL import Image
import numpy as np

frameNum = 0
happyTextureID = -1
lastTime = int(time())

def loadShaders(vertexFile, fragmentFile):
    with open(vertexFile) as file:
        vertexShader = shaders.compileShader(file.read(), GL_VERTEX_SHADER)

    with open(fragmentFile) as file:
        fragmentShader = shaders.compileShader(file.read(), GL_FRAGMENT_SHADER)

    return shaders.compileProgram(vertexShader, fragmentShader)


def loadTexture(fileName):
    # Try to open the file
    try:
        image = Image.open(fileName)
    except:
        print('Failed to load the image :(')
        return -1

    # Load the raw image info
    imageData = np.array(list(image.getdata()), np.uint8)

    # Get an ID that openGL will use for this image
    textureID = glGenTextures(1)

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1)
    glBindTexture(GL_TEXTURE_2D, textureID)

    # Set texture wrapping configuration to tile textures that need to be extended
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT)
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT)

    # Set texture scaling configuration to just be ugly un-antaliased pixels
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST)
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST)

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE)

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0)

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.size[0], image.size[1],
        0, GL_RGB, GL_UNSIGNED_BYTE, imageData)

    image.close()
    return textureID

def setView(x, y, w, h):

    # Create and load the view matrix
    glViewport(int(x), int(y), int(w), int(h))
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()

    # Create and load the Model matrix
    glOrtho(0, 1, 0, 1, -1.0, 1.0)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()

def drawFigure(x, y, w, h):
    setView(x, y, w, h)
    shaders.glUseProgram(shaderProgram)
    square.bind()
    glEnableClientState(GL_VERTEX_ARRAY)
    glEnableClientState(GL_COLOR_ARRAY)
    glVertexPointer(3, GL_FLOAT, 24, square) 
    glColorPointer(3, GL_FLOAT, 24, square+12)
    glDrawArrays(GL_TRIANGLES, 0, 12)
    square.unbind()
    glDisableClientState(GL_VERTEX_ARRAY)
    glDisableClientState(GL_COLOR_ARRAY)

def draw():
    global frameNum, lastTime, square, shaderProgram

    # Compute and print FPS
    frameNum += 1
    if time() > lastTime + 1:
        print(f'{frameNum} fps')
        lastTime = time()
        frameNum = 0

    # Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()


    drawFigure(100, 100, 100 + 50 * cos(time()*10), 100 + 50 * (sin(time()*10)))
    drawFigure(400, 300, 50, 50)

    # glBegin(GL_POLYGON)
    # glVertex3f (0, 0, 0.0)
    # glVertex3f (100, 0, 0.0)
    # glVertex3f (100, 100, 0.0)
    # glVertex3f (0, 100, 0.0)
    # glEnd()
    

    glutSwapBuffers()

if __name__ == '__main__':
    glutInit()
    glutInitDisplayMode(GLUT_RGBA)
    glutInitWindowSize(500, 500)
    glutInitWindowPosition(0, 0)
    wind = glutCreateWindow("Hello OpenGL")

    # select clearing color 
    glClearColor (0.0, 0.0, 0.0, 0.0)

    # initialize viewing values  
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()

    
    shaderProgram = loadShaders("shaders/vertexShader.vert", "shaders/vertexColors.frag")

    # happyTextureID = loadTexture("happy.png")

    # Create a bunch of triangles to draw a sqaure
    square = vbo.VBO(np.array([
        [0.5, 0.0, 0, 0, 0, 1],
        [1.0, 0.5, 0, 0, 1, 1],
        [1.0, 1.0, 0, 0, 1, 0],
        [1.0, 1.0, 0, 0, 1, 0],
        [0.5, 1.0, 0, 0, 1, 1],
        [0.0, 0.5, 0, 0, 0, 1],
        [0.0, 0.0, 0, 1, 0, 0],
        [0.5, 0.0, 0, 0, 0, 1],
        [1.0, 1.0, 0, 0, 1, 0],
        [1.0, 1.0, 0, 0, 1, 0],
        [0.0, 0.0, 0, 1, 0, 0],
        [0.0, 0.5, 0, 0, 0, 1],

    ], dtype=np.float32))

    glutDisplayFunc(draw)
    glutIdleFunc(draw)

    glutMainLoop()