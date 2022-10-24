#define STB_IMAGE_IMPLEMENTATION

#include<stdio.h>
#include<string.h>
#include<cmath>
#include<vector>

#include<glew.h>
#include<glfw3.h>

#include<GLM/glm.hpp>
#include<GLM/gtc/matrix_transform.hpp>
#include<GLM/gtc/type_ptr.hpp>

#include"Mesh.h"
#include"shader.h"
#include"Window.h"
#include"Camera.h"
#include"Texture.h"
#include"DirectionalLight.h"
#include"Material.h"

//Vertex Shader
static const char* vShader = "shaders/triangleShader.vert";
static const char* fShader = "shaders/triangleShader.frag";
const float toRadians = (3.14159265f / 180.0f);

std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
GLuint shader, uModel, uProjection;
Camera camera;
DirectionalLight mainLight;
Material shinyMaterial, dullMaterial;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
Texture brickTexture;
Texture dirtTexture;

bool direction = true;
float triOffSet = 0.0f;
float triMaxOffSet = 0.7f;
float triIncrement = 0.005f;

void calculateAverageNormal(unsigned int* indices, unsigned int indiceCount, 
                            GLfloat* vertices, unsigned int verticesCount,
                            unsigned int vLength, unsigned int normalOffset)
{
    for(size_t i=0; i< indiceCount; i+=3)
    {
        unsigned int in0 = indices[i]*vLength;
        unsigned int in1 = indices[i+1]*vLength;
        unsigned int in2 = indices[i+2]*vLength;

        glm::vec3 v1(vertices[in1]- vertices[in0], 
                    vertices[in1+1] - vertices[in0+1],
                    vertices[in1+2] - vertices[in0+2]);
        glm::vec3 v2(vertices[in2]- vertices[in0], 
                    vertices[in2+1] - vertices[in0+1],
                    vertices[in2+2] - vertices[in0+2]); 
        glm::vec3 normal = glm::cross(v1, v2);
        normal = glm::normalize(normal);
        in0 += normalOffset;
        in1 += normalOffset;
        in2 += normalOffset;
        vertices[in0] = normal.x;vertices[in0+1] = normal.y;vertices[in0+2]=normal.z; 
        vertices[in1] = normal.x;vertices[in1+1] = normal.y;vertices[in1+2]=normal.z; 
        vertices[in2] = normal.x;vertices[in2+1] = normal.y;vertices[in2+2]=normal.z;
    }
    
    for (size_t i=0; i<verticesCount/vLength; i++)
    {
        unsigned int nOffSet = i * vLength + normalOffset;
        glm::vec3 vec(vertices[nOffSet], vertices[nOffSet+1], vertices[nOffSet+2]);
        vec = glm::normalize(vec);
        vertices[nOffSet]=vec.x;vertices[nOffSet+1]=vec.y;vertices[nOffSet+2]=vec.z;
    }
}

void  createTriangles()
{
    unsigned int indices[] = {
        0,3,1,
        1,3,2,
        2,3,0,
        0,1,2
    };

    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f,
    };

    calculateAverageNormal(indices, 12, vertices, 32, 8, 5);

    Mesh *obj1 = new Mesh();
    obj1 -> createMesh(vertices, indices, 32, 12);
    meshList.push_back(obj1);

    Mesh *obj2 = new Mesh();
    obj2 -> createMesh(vertices, indices, 32, 12);
    meshList.push_back(obj2);
}

void createShaders()
{
    Shader *shader1 = new Shader();
    shader1->createFromFiles(vShader, fShader);
    shaderList.push_back(*shader1);
}

int main()
{
    GLWindow mainWindow(1600, 900);
    mainWindow.Initilized();
    createTriangles();
    createShaders();  

    camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0, 0, 5.0f, 1.0f);
    brickTexture = Texture("textures/brick.png");
    brickTexture.loadTexture();
    dirtTexture = Texture("textures/dirt.png");
    dirtTexture.loadTexture();
    mainLight = DirectionalLight(1.0f, 1.0f, 1.0f, 
                                0.2f, 0.3f,
                                1.0f, 1.0f, 1.0f);

    shinyMaterial = Material(1.0f, 32);
    dullMaterial = Material(0.2f, 4);
    
    GLuint uProjection = 0, uModel = 0, uView =0;
    GLuint uAmbientIntensity = 0, uAmbientColor =0;
    GLuint uDirection = 0, uDiffuseIntensity = 0;
    GLuint uSpecularIntensity = 0, uShininess = 0;
    GLuint uEyePos;
    // loop until windows closed
    float curAngle = 0.0f;
    float angleIncrement = 0.5f;
    glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth()/mainWindow.getbufferHeight(), 0.1f, 100.0f);
    while(!mainWindow.getShouldClose())
    {
        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        glfwPollEvents();
        camera.keyControl(mainWindow.getKeys(), deltaTime);
        camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
        if (direction){
            triOffSet += triIncrement;
        }else{
            triOffSet -= triIncrement;
        }

        if (abs(triOffSet)>triMaxOffSet){
            direction = !direction;
        }
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (curAngle>358){
            angleIncrement = -angleIncrement;
        }
        curAngle += angleIncrement;
        shaderList[0].useShader();
            uModel = shaderList[0].getModelLocation();
            uProjection = shaderList[0].getProjectionLocation();
            uView = shaderList[0].getViewLocation();
            uAmbientColor = shaderList[0].getAmbientColorLocation();
            uAmbientIntensity = shaderList[0].getAmbientIntensityLocation();
            uDirection = shaderList[0].getDiffuseDirectionLocation();
            uDiffuseIntensity = shaderList[0].getDiffuseIntensityLocation();
            uSpecularIntensity = shaderList[0].getSpecularIntensityLocation();
            uShininess = shaderList[0].getShininessLocation();
            uEyePos = shaderList[0].getDiffuseIntensityLocation();
            
            shaderList[0].setDirectionalLight(&mainLight);
        
            glm::mat4 model(1.0f);

            model = glm::translate(model, glm:: vec3(0.0f, 0.0f,-2.5f));
            //model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
            model = glm::rotate(model, curAngle*toRadians, glm::vec3(0.0f,1.0f,0.0f));

            glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uProjection, 1, GL_FALSE, glm::value_ptr(projection));
            glUniformMatrix4fv(uView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
            glm::vec3 cameraPos = camera.getPosition();
            glUniform3f(uEyePos, cameraPos.x, cameraPos.y, cameraPos.z);
            brickTexture.useTexture();
            shinyMaterial.useMaterial(uSpecularIntensity, uShininess);
            meshList[0]->renderMesh();

            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(1.0f, 1.0f, -2.5f));
            //model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
            model = glm::rotate(model, curAngle*toRadians, glm::vec3(1.0f,0.0f,0.0f));

            glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(model));
            dirtTexture.useTexture();
            dullMaterial.useMaterial(uSpecularIntensity, uShininess);
            meshList[0]->renderMesh(); 
        glUseProgram(0);
        mainWindow.swapBuffer();
    }
    return 0;
}