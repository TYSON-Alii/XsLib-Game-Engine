#define _CRT_SECURE_NO_WARNINGS
#include <XsEngine.hpp>
XsShape v;

using namespace std;

void myfunc() {
    if (XsIsKeyPressed(XS_MOUSE_LEFT)) {
        v.pos.y += 0.1;
    };
}

int main() {
    XsLib engine("oyun motoru");
    engine.load("new_proj.xs.save");
    XsVertices cube_vert = XsOBJLoader("data/magic.obj", XS_VERTEX);
    XsTextureSTB tex("data/pattern32.png");
    engine << v;
    engine << tex;
    engine << cube_vert;
    engine.Push(myfunc, "normal");

    engine.Start();
    return 0;
};
