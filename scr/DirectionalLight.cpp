#include "DirectionalLight.h"

DirectionalLight::DirectionalLight():Light()
{
    direction = glm::vec3(0.0f,  -1.0f, 0.0f);
}

DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, 
            GLfloat aIntensity, GLfloat dIntensity,
            GLfloat xDir, GLfloat yDir, GLfloat zDir): 
            Light(red, green, blue, aIntensity, dIntensity)
{
    direction = glm::vec3(xDir, yDir, zDir);
}

void DirectionalLight::useLight(GLuint aIntensityLocation, GLuint aColorLocation,
                    GLuint dIntensityLocation, GLuint dDirectionLocation)
{
    glUniform3f(aColorLocation, color.x, color.y, color.z);
    glUniform1f(aIntensityLocation, ambientIntensity);

    glUniform3f(dDirectionLocation, direction.x, direction.y, direction.z);
    glUniform1f(dIntensityLocation, diffuseIntensity);
}
DirectionalLight::~DirectionalLight()
{
}