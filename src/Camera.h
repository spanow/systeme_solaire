#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Camera {
public:
    Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);
    glm::mat4 getViewMatrix();

    void processKeyboard(GLFWwindow* window, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset);
    void centerOnPoint(glm::vec3 point);

private:
    void updateCameraVectors();

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;

    float movementSpeed;
    float mouseSensitivity;
};

#endif // CAMERA_H
