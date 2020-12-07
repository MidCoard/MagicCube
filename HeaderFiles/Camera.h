#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

using namespace glm;

vec3 xAXIS = vec3(1.0f, 0.0f, 0.0f);
vec3 yAXIS = vec3(0.0f, 1.0f, 0.0f);
vec3 zAXIS = vec3(0.0f, 0.0f, 1.0f);

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.05f;
const float ZOOM = 45.0f;


class Camera {
public:

    vec3 Position;
    vec3 lastPosition;
    vec3 Front;
    vec3 Up;
    vec3 Right;
    vec3 WorldUp;

    float Yaw;
    float Pitch;

    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    Camera(vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 up = vec3(0.0f, 1.0f, 0.0f), float yaw = YAW,
           float pitch = PITCH) : Front(vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY),
                                  Zoom(ZOOM) {
        Position = position;
        lastPosition = vec3(0, 0, 0);
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(
            vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
        Position = vec3(posX, posY, posZ);
        WorldUp = vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    mat4 getViewMatrix() {
        return lookAt(Position, vec3(0, 0, 0), Up);
    }
    bool ifInverseUp = false;

    void processMouseMovement(float xoffset, float yoffset) {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        vec4 positionv4 = vec4(Position, 1.0f);
        mat4 transx = mat4(1.0f);
        mat4 transy = mat4(1.0f);
        transx = rotate(transx, radians(-xoffset), yAXIS);
        vec4 xAXISv4 = vec4(xAXIS, 1.0f);
        xAXISv4 = transx * xAXISv4;
        xAXIS = vec3(xAXISv4);
        transy = rotate(transy, radians(yoffset), xAXIS);
        positionv4 = transy * transx * positionv4;
        Position = vec3(positionv4);

        if ((Position.x >= -1.0f) && (Position.x <= 1.0f) && (lastPosition.z * Position.z <= 0)) {
            ifInverseUp = !ifInverseUp;
        }

        updateCameraVectors();
    }

    void ProcessMouseScroll(float yoffset) {
        Zoom -= (float) yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 89.0f)
            Zoom = 89.0f;
    }

private:
    void updateCameraVectors() {
        vec3 front;
        front.x = cos(radians(Yaw)) * cos(radians(Pitch));
        front.y = sin(radians(Pitch));
        front.z = sin(radians(Yaw)) * cos(radians(Pitch));
        Front = normalize(front);
        Right = normalize(cross(Front, WorldUp));
        if (!ifInverseUp) Up = normalize(cross(Right, Front));
        else Up = -normalize(cross(Right, Front));
        lastPosition = Position;
    }
};

#endif