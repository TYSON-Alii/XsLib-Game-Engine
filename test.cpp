#define _CRT_SECURE_NO_WARNINGS
#include <XsEngine.hpp>
XsLib engine;
XsShape v;

using namespace std;

void myfunc() {
    if (XsIsKeyPressed(XS_MOUSE_LEFT)) {
        v.pos.y += 0.1;
    };
}

int main() {
    engine.Create("oyun motoru");
    // after creating engine
    XsVertices cube_vert = XsOBJLoader("data/magic.obj", XS_VERTEX);
    XsTextureSTB tex("data/pattern32.png");
    engine.load("new_proj.xs.save");
    engine << v;
    engine << tex;
    engine << cube_vert;
    engine.Push(myfunc, "normal");

    engine.Start();
    return 0;
};
