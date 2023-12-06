#ifndef H_STATE
#define H_STATE

class State {
    public:
        float rotate;
        float offsetX;
        float offsetZ;
        bool quit;

        State() : rotate(0.0f), offsetX(0.0f), offsetZ(0.0f), quit(false) {}
};

#endif 