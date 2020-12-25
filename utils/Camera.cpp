#include "Camera.h"

void Camera::updateCameraVectors() {
    vec3 front;
    front.x = cos(radians(this->yaw)) * cos(radians(this->pitch));
    front.y = sin(radians(this->pitch));
    front.z = sin(radians(this->yaw)) * cos(radians(this->pitch));
    this->front = normalize(front);
    this->right = normalize(cross(this->front, this->worldUp));
    if (!inverseUp) 
        this->up = normalize(cross(this->right, this->front));
    else
        this->up = -normalize(cross(this->right, this->front));
    lastPosition = this->position;
}

Camera::Camera(vec3 position, vec3 up, float yaw, float pitch) : front(-normalize(CAMERA_POSITION)), mouseSensitivity(SENSITIVITY),
                                                                 zoom(ZOOM) {
    this->position = position;
    lastPosition = vec3(0, 0, 0);
    this->worldUp = up;
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
}

mat4 Camera::getViewMatrix() const  {
    return lookAt(this->position, vec3(0, 0, 0), this->up);
}

Camera::~Camera(){
    ZOOM = this->zoom;
}
void Camera::processMouseMovement(float xOffset, float yOffset) {

    xOffset *= this->mouseSensitivity;
    yOffset *= this->mouseSensitivity;

    this->front = normalize(this->position);
    this->up = cross(this->front,this->right);

    mat4 translationX = mat4(1.0f);
    mat4 translationY = mat4(1.0f);

    if (!inverseUp)
    	translationX = rotate(translationX, radians(-xOffset), YAxis);
    if (inverseUp)
    	translationX = rotate(translationX, -radians(-xOffset), YAxis);
    XAxis = vec3(translationX * vec4(XAxis, 1.0f));
    translationY = rotate(translationY, radians(yOffset), XAxis);
    this->position = vec3(translationY * translationX * vec4(this->position, 1.0f));
    if (((this->position.x >= -1.5f) && (this->position.x <= 1.5f)) && (lastPosition.z * this->position.z <= 0))
        inverseUp = !inverseUp;

    updateCameraVectors();
}

float Camera::getZoom() {
    return zoom;
}

vec3 Camera::getPosition() {
    return position;
}

vec3 Camera::getWorldUp() {
    return worldUp;
}

void Camera::processMouseScroll(float yOffset) {
    this->zoom -= (float) yOffset;
    if (this->zoom < 25.0f)
        this->zoom = 25.0f;
    if (this->zoom > 70.0f)
        this->zoom = 70.0f;
}
