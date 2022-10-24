#include "PointLight.h"

PointLight::PointLight() : Light()
{
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    constant = 1.0f;
    linear = 0.0f;
    exponent = 0.0f;  
}

PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue,
                    GLfloat aIntensity, GLfloat dIntensity,
                    GLfloat xPos, GLfloat yPos, GLfloat zPos,
                    GLfloat con, GLfloat lin, GLfloat exp):
            Light(red, green, blue, aIntensity, dIntensity)
{
    position = glm::vec3(xPos, yPos, zPos);
    constant = con;
    linear = lin;
    exponent = exp;
}

void PointLight::useLight(GLuint aIntensityLocation, GLuint aColorLocation,
                    GLuint dIntensityLocation, GLuint posLocation,
                    GLuint constLocation, GLuint linearLocation, GLuint expLocation)
{
    glUniform3f(aColorLocation, color.x, color.y, color.z);
    glUniform1f(aIntensityLocation, ambientIntensity);
    glUniform1f(dIntensityLocation, diffuseIntensity);
    glUniform3f(posLocation, position.x, position.y, position.z);
    glUniform1f(constLocation, constant);
    glUniform1f(linearLocation, linear);
    glUniform1f(expLocation, exponent);
}

PointLight::~PointLight()
{
}