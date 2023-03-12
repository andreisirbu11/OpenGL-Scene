#include "Camera.hpp"

namespace gps {

    //Camera constructor
    Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp) {
        this -> cameraPosition = cameraPosition;
        this -> cameraTarget = cameraTarget;
        this -> cameraUpDirection = cameraUp;

        //TODO - Update the rest of camera parameters
        this -> cameraFrontDirection = glm::normalize(cameraTarget - cameraPosition);
        this -> cameraRightDirection = glm::normalize(glm::cross(cameraFrontDirection, cameraUp));
        this -> cameraUpDirection = glm::normalize(glm::cross(cameraRightDirection, cameraFrontDirection));

    }

    //return the view matrix, using the glm::lookAt() function
    glm::mat4 Camera::getViewMatrix() {
        return glm::lookAt(cameraPosition, cameraTarget, cameraUpDirection);
    }

    //update the camera internal parameters following a camera move event
    void Camera::move(MOVE_DIRECTION direction, float speed) {
        //TODO
        if (direction == MOVE_FORWARD) {
            cameraPosition = cameraPosition + speed * cameraFrontDirection;
            cameraTarget = cameraTarget + speed * cameraFrontDirection;
        }
        if (direction == MOVE_BACKWARD) {
            cameraPosition = cameraPosition - speed * cameraFrontDirection;
            cameraTarget = cameraTarget - speed * cameraFrontDirection;
        }
        if (direction == MOVE_LEFT) {
            cameraPosition = cameraPosition - speed * cameraRightDirection;
            cameraTarget = cameraTarget - speed * cameraRightDirection;
        }
        if (direction == MOVE_RIGHT) {
            cameraPosition = cameraPosition + speed * cameraRightDirection;
            cameraTarget = cameraTarget + speed * cameraRightDirection;
        }
    }

    //update the camera internal parameters following a camera rotate event
    //yaw - camera rotation around the y axis
    //pitch - camera rotation around the x axis
    void Camera::rotate(float pitch, float yaw) {
        //TODO
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        //glm::vec3 direction;
        //direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        //direction.y = sin(glm::radians(pitch));
        //direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        //this -> cameraFrontDirection = glm::normalize(direction);
        //version 2
        this -> yawAngle = yaw + this -> yawAngle;
        this -> pitchAngle = pitch + this -> pitchAngle;

        this -> cameraTarget.y = this -> cameraPosition.y + sin(pitchAngle);
        this -> cameraTarget.x = this -> cameraPosition.x + sin(yawAngle) * cos(pitchAngle);
        this -> cameraTarget.z = this -> cameraPosition.z - cos(yawAngle) * cos(pitchAngle);

        this -> cameraFrontDirection = glm::normalize(cameraTarget - cameraPosition);
        this -> cameraRightDirection = glm::normalize(glm::cross(cameraFrontDirection, glm::vec3(0.0f, 1.0f, 0.0f)));
        this -> cameraUpDirection = glm::normalize(glm::cross(cameraRightDirection, cameraFrontDirection));
    }
    glm::vec3 Camera::getCameraPosition() {
        return this -> cameraPosition;
    };

    glm::vec3 Camera::getCameraTarget() {
        return this -> cameraTarget;
    };
    void Camera::lookAround(glm::vec3 position, glm::vec3 target)
    {
        this -> cameraPosition = position;
        this -> cameraTarget = target;
    }
}