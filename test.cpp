#define _CRT_SECURE_NO_WARNINGS
#define GLEW_ENABLE_EXPERIMENTAL
#include <GL/glew.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_stdlib.h"
#include "ImGuizmo.h"
#include "imfilebrowser.h"
#include "ImGuiFileDialog.h"
#define XS_USE_SFML
#define XS_USE_COLORS
#define XS_USE_IMGUI
#define XS_USE_GLM
#include <XsLib.hpp>
#define WIDTH 1200
#define HEIGHT 700
#include "XsEngine.hpp"
XsShape v;

int main(int argc, char* argv[]) {
    XsLib engine("oyun motoru");
    XsVertices cube_vert = XsOBJLoader("data/magic.obj", XS_VERTEX);
    XsTextureSTB tex("data/pattern32.png");
    engine << v;
    engine << v;
    engine << tex;
    engine << cube_vert;

    engine.Draw();
    return 0;
};
