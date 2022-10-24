#pragma once
#include<GLM\glm.hpp>
#include<glew.h>

class Light
{
    public:
        Light();
        Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity);
        void useLight(GLuint aIntensityLocation, GLuint aColorLocation,
                    GLuint dIntensityLocation, GLuint dDirectionLocation);
        ~Light();
    protected:
        glm::vec3 color;
        GLfloat ambientIntensity;  
        GLfloat diffuseIntensity;
};