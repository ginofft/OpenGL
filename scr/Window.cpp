#include "Window.h"
#include<glew.h>
#include<glfw3.h>

GLWindow::GLWindow(){
    width = 800;
    height = 600;  
    changeX = 0.0f;
    changeY = 0.0f;
    for(size_t i=0; i<1024;i++)
    {
        keys[i]=0;
    }
}

GLWindow::GLWindow(GLint windowWidth, GLint windowHeight){
    width = windowWidth;
    height = windowHeight;
    changeX = 0.0f;
    changeY = 0.0f;
    for(size_t i=0; i<1024;i++)
    {
        keys[i]=0;
    }
}

int GLWindow::Initilized(){

    if (!glfwInit())
    {
        printf("Failed to initialized GLFW");
        glfwTerminate();
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    mainWindow = glfwCreateWindow(width, height, "test window 1", NULL, NULL);
    if (mainWindow == NULL)
    {
        printf("Failed to open GLFW window");
        return -1;
    }
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
    glfwMakeContextCurrent(mainWindow);
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        printf("Failed to initialized GLEW");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return -1;
    }

    createCallbacks();
    glViewport(0, 0, bufferWidth, bufferHeight);
    glfwSetWindowUserPointer(mainWindow, this);
    return 0;
}

void GLWindow::createCallbacks()
{
    glfwSetKeyCallback(mainWindow, handleKeys);
    glfwSetCursorPosCallback(mainWindow, handleMouse);
}

GLfloat GLWindow::getXChange()
{
    GLfloat theChange = changeX;
    changeX = 0.0f;
    return theChange;
}

GLfloat GLWindow::getYChange()
{
    GLfloat theChange = changeY;
    changeY = 0.0f;
    return theChange;
}

void GLWindow::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
    GLWindow* theWindow = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key>=0 && key<=1024)
    {
        if (action == GLFW_PRESS)
        {
            theWindow -> keys[key]=true;
            printf("Pressed %d\n", key);
        }
        else if(action == GLFW_RELEASE)
        {
            theWindow -> keys[key]=false;
            printf("Released: %d\n", key);
        }

    }
}

void GLWindow::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
    GLWindow* theWindow = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));
    if (theWindow->mouseFirstMoved)
    {
        theWindow->lastX=xPos;
        theWindow->lastY=yPos;
        theWindow->mouseFirstMoved=false;
    }

    theWindow -> changeX = xPos - theWindow->lastX;
    theWindow -> changeY = theWindow->lastY - yPos;

    theWindow ->lastX = xPos;
    theWindow ->lastY = yPos;

    printf("x: %.6f, y:%.6f\n", theWindow->changeX, theWindow->changeY);
}

GLWindow::~GLWindow()
{
    width = 0;
    height = 0;
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}