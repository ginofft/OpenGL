#pragma once
#include<glew.h>
#include<glfw3.h>
#include<stdio.h>

class GLWindow
{
    public:
        GLWindow();
        GLWindow(GLint width, GLint height);
        int Initilized();
        GLint getBufferWidth(){ return bufferWidth;}
        GLint getbufferHeight(){ return bufferHeight;}

        bool getShouldClose(){
            return glfwWindowShouldClose(mainWindow);
        }
        bool* getKeys(){ return keys;}

        GLfloat getXChange();
        GLfloat getYChange();

        void swapBuffer(){
            glfwSwapBuffers(mainWindow);
        }
        ~GLWindow();

    private:
        GLFWwindow *mainWindow;
        GLint width, height;
        GLint bufferWidth, bufferHeight;

        GLfloat lastX, lastY, changeX, changeY;
        bool mouseFirstMoved;
        bool keys[1024];

        void createCallbacks();
        static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
        static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};
