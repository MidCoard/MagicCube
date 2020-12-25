#ifndef MAGICCUBE_CAMERA_H
#define MAGICCUBE_CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Configuration.h"

#include <vector>

using namespace glm;


extern const float YAW;
extern const float PITCH;
extern const float SENSITIVITY;

extern float ZOOM;

extern vec3 YAxis;
extern vec3 XAxis;
extern const vec3 CAMERA_POSITION;

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