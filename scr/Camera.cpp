#include "Camera.h"

Camera::Camera(){}
Camera::Camera(glm::vec3 startPos, glm::vec3 startUp, 
                GLfloat startYaw, GLfloat startPitch, 
                GLfloat startMovementSpeed, GLfloat startTurnSpeed)
{
    position = startPos;
    worldUp = startUp;
    yaw = startYaw;
    pitch = startPitch;
    front = glm::vec3(0.0f, 0.0f, -1.0f);

    movementSpeed = startMovementSpeed;
    turnSpeed = startTurnSpeed;

    update();
}

void Camera::keyControl(bool* keys, GLfloat deltaTime)
{   

    GLfloat displacement = movementSpeed*deltaTime;
    if (keys[GLFW_KEY_W]) 
    {
        position += front * displacement;
    }   
    if (keys[GLFW_KEY_A]) 
    {
        position += right * displacement;
    }
    if (keys[GLFW_KEY_S]) 
    {
        position -= front * displacement;
    }
    if (keys[GLFW_KEY_D]) 
    {
        position -= right * displacement;
    }
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange)
{
    xChange *= turnSpeed;
    yChange *= turnSpeed;

    yaw -= xChange;
    pitch -= yChange;

    if (pitch > 89.0f)
    {
        pitch = 89.0f;
    }
    if (pitch <-89.0f)
    {
        pitch = -89.0f;
    }
    update();
}
glm::vec3 Camera::getPosition()
{
    return position;
}
void Camera::update()
{
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(front, right));
}

glm::mat4 Camera::calculateViewMatrix()
{
    return glm::lookAt(position, position+front, up);
}

Camera::~Camera()
{

}

