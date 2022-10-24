#include "Material.h"

Material::Material()
{
    specularIntensity = 0;
    shininess = 0;
}

Material::Material(GLfloat sIntensity, GLfloat shine)
{
    specularIntensity = sIntensity;
    shininess = shine;
}

void Material::useMaterial(GLuint sIntensityLocation, GLuint shininessLocation)
{
    glUniform1f(sIntensityLocation, specularIntensity);
    glUniform1f(shininessLocation, shininess);
}
Material::~Material()
{
    specularIntensity = 0;
    shininess = 0;
}