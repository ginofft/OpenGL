#include "shader.h"
#include<string.h>
#include<fstream>

Shader::Shader()
{
    shaderID = 0;
    uProjection = 0;
    uModel = 0;
}

void Shader::createFromString(const char* vertexCode, const char* fragmentCode)
{
    compileShader(vertexCode, fragmentCode);
}

void Shader::createFromFiles(const char* vertexLocation, const char* fragmentLocation)
{
    std::string vertexString = readFile(vertexLocation);
    std::string fragmentString = readFile(fragmentLocation);
    const char* vertexCode = vertexString.c_str();
    const char* fragementCode = fragmentString.c_str();
    compileShader(vertexCode, fragementCode);
}

std::string Shader::readFile(const char* fileLocation)
{
    std::string content;
    std::ifstream fileStream(fileLocation, std::ios::in);

    if (!fileStream.is_open())
    {
        printf("Failed to read '%s'! File doesn't exist.", fileLocation);
    }

    std::string line ="";
    while (!fileStream.eof())
    {
        std::getline(fileStream, line);
        content.append(line+'\n');
    }

    fileStream.close();
    return content;
}

GLuint Shader::getModelLocation()
{
    return uModel;
}

GLuint Shader::getProjectionLocation()
{
    return uProjection;
}
GLuint Shader::getViewLocation()
{
    return uView;
}
GLuint Shader::getAmbientColorLocation()
{
    return uDirectionalLight.uColor;
}
GLuint Shader::getAmbientIntensityLocation()
{
    return uDirectionalLight.uAmbientIntensity;
}
GLuint Shader::getDiffuseDirectionLocation()
{
    return uDirectionalLight.uDirection;
}
GLuint Shader::getDiffuseIntensityLocation()
{
    return uDirectionalLight.uDiffuseIntensity;
}
GLuint Shader::getSpecularIntensityLocation()
{
    return uSpecularIntensity;
}
GLuint Shader::getShininessLocation()
{
    return uShininess;
}
GLuint Shader::getEyePositionLocation()
{
    return uEyePos;
}

void Shader::compileShader(const char* vertexCode, const char* fragmentCode)
{
    shaderID = glCreateProgram();
    if (!shaderID){
        printf("Failed to create shader program!");
        return;
    }
    addShader(shaderID, vertexCode, GL_VERTEX_SHADER);
    addShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glLinkProgram(shaderID);
    glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
        printf("Failed to link program: '%s'\n", eLog);
        return;
    }
    glValidateProgram(shaderID);
    glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
        printf("Failed to validate program: '%s'\n", eLog);
        return;
    }
    uModel = glGetUniformLocation(shaderID, "model");
    uProjection = glGetUniformLocation(shaderID, "projection");
    uView = glGetUniformLocation(shaderID, "view");
    uDirectionalLight.uColor = glGetUniformLocation(shaderID, "directionalLight.color");
    uDirectionalLight.uAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.ambientIntensity");
    uDirectionalLight.uDiffuseIntensity = glGetUniformLocation(shaderID, "directionalLight.diffuseIntensity");
    uDirectionalLight.uDirection = glGetUniformLocation(shaderID, "directionalLight.direction");
    uSpecularIntensity = glGetUniformLocation(shaderID, "material.sIntensity");
    uShininess = glGetUniformLocation(shaderID, "material.shininess");
    uEyePos = glGetUniformLocation(shaderID, "eyePos");
}

void Shader::addShader(GLuint program, const char* shaderCode, GLenum shaderType)
{
    GLuint theShader = glCreateShader(shaderType);
    const GLchar* theCode[1];
    theCode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);
    
    GLint result = 0;
    GLchar eLog[1024] = { 0 };
    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
        printf("Failed to compile %d shader: '%s'\n", shaderType,eLog);
        return;
    }
    glAttachShader(program, theShader);
}

void Shader::setDirectionalLight(DirectionalLight* dLight)
{
    dLight->useLight(uDirectionalLight.uAmbientIntensity,
                    uDirectionalLight.uColor,
                    uDirectionalLight.uDiffuseIntensity,
                    uDirectionalLight.uDirection);
}
void Shader::useShader()
{
    glUseProgram(shaderID);
}

void Shader::clearShader()
{
    if (shaderID!=0)
    {
        glDeleteProgram(shaderID);
        shaderID = 0;
    }
    uProjection = 0;
    uModel = 0;
}
Shader::~Shader()
{
    clearShader();
}