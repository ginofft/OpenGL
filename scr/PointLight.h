#pragma once

#include "Light.h"

class PointLight:
    public Light
{
    public:
        PointLight();
        PointLight(GLfloat red, GLfloat green, GLfloat blue,
                    GLfloat aIntensity, GLfloat dIntensity,
                    GLfloat xPos, GLfloat yPos, GLfloat zPos,
                    GLfloat constant, GLfloat linear, GLfloat exponent);
        void useLight(GLuint aIntensityLocation, GLuint aColorLocation,
                    GLuint dIntensityLocation, GLuint dDirectionLocation,
                    GLuint constLocation, GLuint linearLocation, GLuint expLocation);
        ~PointLight();
    private:
        glm::vec3 position;
        GLfloat constant, linear, exponent;

};