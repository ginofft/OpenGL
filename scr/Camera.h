#pragma once

#include<glew.h>
#include<GLM\glm.hpp>
#include<GLM\gtc\matrix_transform.hpp>
#include<glfw3.h>

class Camera
{
    public:
        Camera();
        Camera(glm::vec3 startPos, glm::vec3 startUp, 
                GLfloat startYaw, GLfloat startPitch,
                GLfloat startMovementSpeed, GLfloat startTurnSpeed);
        void keyControl(bool* keys, GLfloat deltaTime);
        void mouseControl(GLfloat xChange, GLfloat yChange);
        glm::vec3 getPosition();
        glm::mat4 calculateViewMatrix();
        ~Camera();

    private:
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 worldUp;

        GLfloat yaw;
        GLfloat pitch;

        GLfloat movementSpeed;
        GLfloat turnSpeed;
        void update();
};