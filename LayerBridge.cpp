#include "Layers/LogicLayer.cpp"
#include "Layers/RenderLayer.cpp"

#define DEBUG

void render() {
    Render::render();
}

void updateGameState() {
    Logic::updateGameState();
}
int count=0;
void handleInput() {
    if (glfwGetKey(Render::getWindow()->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(Render::getWindow()->getWindow(), true);//退出游戏

    if (glfwGetKey(Render::getWindow()->getWindow(), GLFW_KEY_LEFT_ALT) == GLFW_PRESS) {
        glfwSetInputMode(Render::getWindow()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        Render::setFirstMouse(true);
    }
    if (glfwGetKey(Render::getWindow()->getWindow(), GLFW_KEY_LEFT_ALT) == GLFW_RELEASE) {
        glfwSetInputMode(Render::getWindow()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }//捕捉鼠标

    if (glfwGetKey(Render::getWindow()->getWindow(), GLFW_KEY_R) == GLFW_PRESS){
        delete(Render::camera);
        Render::camera = new Camera(Render::CAMERA_POSITION);
        xAXIS = glm::vec3(1.0f,0.0f,0.0f);
    }//复位
#ifdef DEBUG
    if (glfwGetKey(Render::getWindow()->getWindow(), GLFW_KEY_P) == GLFW_PRESS){
        count++;
        if(count==1) printf("%10f,%10f,%10f\n",Render::camera->Position.x,Render::camera->Position.y,Render::camera->Position.z);
    }
    if (glfwGetKey(Render::getWindow()->getWindow(), GLFW_KEY_P) == GLFW_RELEASE){
        count=0;
    }
#endif
}