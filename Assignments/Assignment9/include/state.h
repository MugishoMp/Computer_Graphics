#ifndef H_STATE
#define H_STATE

class State {
    public:
        int width;
        int height;
        float rotate;
        float offsetX;
        float offsetZ;
        bool quit;

        State() :  width(620), height(480), rotate(0.0f), offsetX(0.0f), offsetZ(-2.0f), quit(false) {}
};

#endif 