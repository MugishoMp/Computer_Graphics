#ifndef H_STATE
#define H_STATE

#include <glm/vec3.hpp>

class State {
    public:
        int width;
        int height;
        float rotate;
        float offsetX;
        float offsetZ;
        float offsetY;
        bool quit;
        glm::vec3 cameraPosition;

        State() :  width(620), height(480), rotate(0.0f), offsetX(0.0f), offsetY(0.0f), offsetZ(-2.0f), quit(false), cameraPosition(glm::vec3(1)) {}
};

#endif 