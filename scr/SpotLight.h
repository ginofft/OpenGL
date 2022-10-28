#pragma once

#include "PointLight.h"

class SpotLight:
    public PointLight
{
    public:
        SpotLight();
        SpotLight(GLfloat red, GLfloat green, GLfloat blue,
                    GLfloat aIntensity, GLfloat dIntensity,
                    GLfloat xPos, GLfloat yPos, GLfloat zPos,
                    GLfloat xDir, GLfloat yDir, GLfloat zDir,
                    GLfloat constant, GLfloat linear, GLfloat exponent,
                    GLfloat edg);
        void useLight(GLuint aIntensityLocation, GLuint aColorLocation,
                    GLuint dIntensityLocation, GLuint dPosLocation, GLuint directionLocation, 
                    GLuint constLocation, GLuint linearLocation, GLuint expLocation);
        
        ~SpotLight();
    private:
        glm::vec3 direction;

        GLfloat edge, procEdge;

};