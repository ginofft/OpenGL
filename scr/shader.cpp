#include "shader.h"
#include<string.h>
#include<fstream>

Shader::Shader()
{
    shaderID = 0;
    uProjection = 0;
    uModel = 0;

    pointLightCount = 0;
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
    uDirectionalLight.uColor = glGetUniformLocation(shaderID, "directionalLight.base.color");
    uDirectionalLight.uAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.base.ambientIntensity");
    uDirectionalLight.uDiffuseIntensity = glGetUniformLocation(shaderID, "directionalLight.base.diffuseIntensity");
    uDirectionalLight.uDirection = glGetUniformLocation(shaderID, "directionalLight.direction");
    uSpecularIntensity = glGetUniformLocation(shaderID, "material.sIntensity");
    uShininess = glGetUniformLocation(shaderID, "material.shininess");
    uEyePos = glGetUniformLocation(shaderID, "eyePos");

    uPointLightCount = glGetUniformLocation(shaderID, "pointLightCount");
    for(size_t i=0; i<MAX_POINT_LIGHTS;i++)
    {
        char locBuff[100] = {'\0'};
        
        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.color", i);
        uPointLight[i].uColor = glGetUniformLocation(shaderID, locBuff);

        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.ambientIntensity", i);
        uPointLight[i].uAmbientIntensity = glGetUniformLocation(shaderID, locBuff);

        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.diffuseIntensity", i);
        uPointLight[i].uDiffuseIntensity = glGetUniformLocation(shaderID, locBuff);
        
        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].position", i);
        uPointLight[i].uPosition = glGetUniformLocation(shaderID, locBuff);

        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].constant", i);
        uPointLight[i].uConstant = glGetUniformLocation(shaderID, locBuff);
        
        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].linear", i);
        uPointLight[i].uLinear = glGetUniformLocation(shaderID, locBuff);

        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].exponent", i);
        uPointLight[i].uExponent = glGetUniformLocation(shaderID, locBuff);
    }
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

void Shader::setPointLights(PointLight* pLight, unsigned int lightCount)
{
    if (lightCount > MAX_POINT_LIGHTS) lightCount = MAX_POINT_LIGHTS;
    
    glUniform1i(uPointLightCount, lightCount);
    for (size_t i=0; i<lightCount; i++)
    {
        pLight[i].useLight(uPointLight[i].uAmbientIntensity, uPointLight[i].uColor,
                        uPointLight[i].uDiffuseIntensity, uPointLight[i].uPosition,
                        uPointLight[i].uConstant, uPointLight[i].uLinear, uPointLight[i].uExponent);
    }
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