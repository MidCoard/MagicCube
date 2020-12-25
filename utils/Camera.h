#ifndef MAGICCUBE_CAMERA_H
#define MAGICCUBE_CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Configuration.h"

#include <vector>

using namespace glm;

const float YAW = -90.0f;//偏转角
const float PITCH = 0.0f;//俯仰角
const float SENSITIVITY = 0.05f;//鼠标灵敏度
float ZOOM = 45.0f;//初始缩放值

const vec3 CAMERA_POSITION = vec3(3.0f, 5.0f, 8.0f);//初始相机位置

vec3 YAxis = vec3(0.0f, 1.0f, 0.0f);
vec3 XAxis = -normalize(cross(vec3(CAMERA_POSITION),YAxis));//使用欧拉角旋转时的旋转轴 会随视角改变

class Camera {

private:
    vec3 position;
    vec3 lastPosition;
    vec3 front;
    vec3 up;
    vec3 right;
    vec3 worldUp;

    float yaw;
    float pitch;
    float mouseSensitivity;
    float zoom;
    bool inverseUp = false;
    void updateCameraVectors();
public:
    Camera(vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 up = vec3(0.0f, 1.0f, 0.0f), float yaw = YAW,
           float pitch = PITCH) ;
    mat4 getViewMatrix() const;


    void processMouseMovement(float xOffset, float yOffset);

    void processMouseScroll(float yOffset);

    float getZoom();

    vec3 getWorldUp();

    vec3 getPosition();

    ~Camera();

};

#endif