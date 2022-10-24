#pragma once

#include<glew.h>

class Material
{
    public:
        Material();
        Material(GLfloat sIntensity, GLfloat shine);
        void useMaterial(GLuint sIntensityLocation, GLuint shininessLocation);

        ~Material();
    private:
        GLfloat specularIntensity;
        GLfloat shininess;
};