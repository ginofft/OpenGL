#include "SpotLight.h"

SpotLight::SpotLight() : PointLight()
{
    direction = glm::vec3(0.0f, -1.0f, 0.0f);
    edge = 0.0f;
}

SpotLight::SpotLight(GLfloat red, GLfloat green, GLfloat blue,
                    GLfloat aIntensity, GLfloat dIntensity,
                    GLfloat xPos, GLfloat yPos, GLfloat zPos,
                    GLfloat xDir, GLfloat yDir, GLfloat zDir,
                    GLfloat constant, GLfloat linear, GLfloat exponent,
                    GLfloat edg) : PointLight(red, green, blue, aIntensity, dIntensity,
                    xPos, yPos, zPos, constant, linear, exponent)
{
    direction = glm::vec3(xDir, yDir, zDir);
    edge = edg;
}
SpotLight::~SpotLight()
{
}