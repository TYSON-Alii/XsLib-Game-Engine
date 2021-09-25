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
    XsVertices kayadam_vert = XsOBJLoader("data/kayadam.obj", XS_VERTEX_AND_TEXTURE);
    XsTextureSTB kayadam_tex("data/kayadam.png", GL_RGBA);
    XsVertices mortax_vert = XsOBJLoader("data/mortaks_1.obj", XS_VERTEX_AND_TEXTURE);
    XsTextureSTB mortax_tex("data/mortaks_1.png", GL_RGBA);
    XsVertices radxf_mortax_vert = XsOBJLoader("data/radiaktif_mortaks.obj", XS_VERTEX_AND_TEXTURE);
    XsTextureSTB radxf_mortax_tex("data/radiaktif_mortaks.png", GL_RGBA);
    XsTextureSTB tex("data/pattern32.png");
    engine << v;
    engine << v;
    engine << tex;
    engine << cube_vert;
    engine << kayadam_vert;
    engine << mortax_vert;
    engine << radxf_mortax_vert;
    engine << kayadam_tex;
    engine << mortax_tex;
    engine << radxf_mortax_tex;

    engine.Draw();
    return 0;
};
