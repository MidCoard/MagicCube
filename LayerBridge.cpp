#include "Layers/LogicLayer.cpp"
#include "Layers/RenderLayer.cpp"


int renderCount = 0;

int updateCount = 0;

void render() {
    Render::render();
    renderCount++;
}

void updateGameState() {
    Logic::updateGameState();
    updateCount++;
}

void handleInput() {
        if (glfwGetKey(Render::getWindow()->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(Render::getWindow()->getWindow(), true);
        if (glfwGetKey(Render::getWindow()->getWindow(), GLFW_KEY_LEFT_ALT) == GLFW_PRESS) {
            glfwSetInputMode(Render::getWindow()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            Render::setFirstMouse(true);
        }
        if (glfwGetKey(Render::getWindow()->getWindow(), GLFW_KEY_LEFT_ALT) == GLFW_RELEASE)
            glfwSetInputMode(Render::getWindow()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }