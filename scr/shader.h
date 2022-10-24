#pragma once

#include<glew.h>
#include<stdio.h>
#include<string>
#include "DirectionalLight.h"

using namespace std;

class Shader
{
    public:
        Shader();

        void createFromString(const char* vertexCode, const char* fragmentCode);
        void createFromFiles(const char* vertexLocation, const char* fragementLocation);

        std::string readFile(const char* fileLocation);
        GLuint getModelLocation();
        GLuint getProjectionLocation();
        GLuint getViewLocation();
        GLuint getAmbientIntensityLocation();
        GLuint getAmbientColorLocation();
        GLuint getDiffuseIntensityLocation();
        GLuint getDiffuseDirectionLocation();
        GLuint getSpecularIntensityLocation();
        GLuint getShininessLocation();
        GLuint getEyePositionLocation();

        void useShader();
        void clearShader();
        void setDirectionalLight(DirectionalLight* dLight);
        ~Shader();

    private:
        int pointLightCount;

        GLint shaderID, uProjection, uModel, uView, 
            uSpecularIntensity, uShininess, uEyePos;

        struct {
            GLuint uColor;
            GLuint uAmbientIntensity;
            GLuint uDiffuseIntensity;
            GLuint uDirection;
        } uDirectionalLight;

        void compileShader(const char* vertexCode, const char* fragmentCode);
        void addShader(GLuint program, const char* shaderCode, GLenum shaderType);
};