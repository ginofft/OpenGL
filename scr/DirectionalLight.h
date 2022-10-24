#pragma once
#include "Light.h"

class DirectionalLight:
    public Light
{
    public:
        DirectionalLight();
        DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, 
                        GLfloat aIntensity, GLfloat dIntensity,
                        GLfloat xDir, GLfloat yDir, GLfloat zDir);
        void useLight(GLuint aIntensityLocation, GLuint aColorLocation,
                    GLuint dIntensityLocation, GLuint dDirectionLocation);
        ~DirectionalLight();
    private:
        glm::vec3 direction;
};