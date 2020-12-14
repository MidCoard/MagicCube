#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include"HeaderFiles/SetVertices.h"

#include <vector>

using namespace glm;

const float YAW = -90.0f;//偏转角
const float PITCH = 0.0f;//俯仰角
const float SENSITIVITY = 0.05f;//鼠标灵敏度
float ZOOM = 45.0f;//初始缩放值

const vec3 CAMERA_POSITION = vec3(3.0f, 5.0f, 8.0f);//初始相机位置

vec3 YAxis = vec3(0.0f, 1.0f, 0.0f);
vec3 XAxis = -normalize(cross(vec3(CAMERA_POSITION),YAxis));//使用欧拉角旋转时的旋转轴 会随视角改变

unsigned int zeroMouseMovementCount=0;

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

    float MouseSensitivity;
    float Zoom;

    Camera(vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 up = vec3(0.0f, 1.0f, 0.0f), float yaw = YAW,
           float pitch = PITCH) : Front(-normalize(CAMERA_POSITION)), MouseSensitivity(SENSITIVITY),
                                  Zoom(ZOOM) {
        Position = position;
        lastPosition = vec3(0, 0, 0);
        WorldUp = up;
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

        mat4 transx = mat4(1.0f);
        mat4 transy = mat4(1.0f);
        if(!ifInverseUp) transx = rotate(transx, radians(-xoffset), YAxis);
        if(ifInverseUp) transx = rotate(transx, -radians(-xoffset), YAxis);
        XAxis = vec3(transx * vec4(XAxis, 1.0f));
        transy = rotate(transy, radians(yoffset), XAxis);
        Position = vec3(transy * transx * vec4(Position, 1.0f));

        if (((Position.x >= -1.7f) && (Position.x <= 1.7f)) && (lastPosition.z * Position.z <= 0)) {
            ifInverseUp = !ifInverseUp;
        }

        updateCameraVectors();
    }

    void ProcessMouseScroll(float yoffset) {
        Zoom -= (float) yoffset;
        if (Zoom < 25.0f)
            Zoom = 25.0f;
        if (Zoom > 70.0f)
            Zoom = 70.0f;
    }

    ~Camera(){
        ZOOM = Zoom;
    }

private:
    void updateCameraVectors() {
        vec3 front;
        front.x = cos(radians(Yaw)) * cos(radians(Pitch));
        front.y = sin(radians(Pitch));
        front.z = sin(radians(Yaw)) * cos(radians(Pitch));
        Front = normalize(front);
        Right = normalize(cross(Front, WorldUp));
        if (!ifInverseUp) {
            Up = normalize(cross(Right, Front));
        }
        else {
            Up = -normalize(cross(Right, Front));
        }
        lastPosition = Position;
    }
};

#endif