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
#include "ImGuiFileDialog.h"
#define XS_USE_SFML
#define XS_USE_COLORS
#define XS_USE_IMGUI
#define XS_USE_GLM
#include <XsLib.hpp>
#include <filesystem>

v3f XsHexToRGB(int hex) {
    v3f _t;
    _t.x = ((hex >> 16) & 0xff) / 255.f;
    _t.y = ((hex >> 8) & 0xff) / 255.f;
    _t.z = ((hex) & 0xff) / 255.f;
    return _t;
};
void open_with_notepad(const char* const file_name) { system(std::string(std::string("notepad \"") + file_name + "\"").c_str()); };
class XsLib;
class XsLib {
protected:
    struct push_t {
        push_t() {};
        push_t(void (*push_v)(void), const char* code) {
            push_data = push_v;
            push_t::code = code;
        };
        void (*push_data)(void);
        const char* code;
    };
    struct Log_t {
        struct Mem_t {
            Mem_t() {};
            Mem_t(const char* log) {
                XsDate _tdate;
                date = _strdup(std::string(str(_tdate.day()) + " - " + str(_tdate.month()) + " - " + str(_tdate.year())).c_str());
                text = _strdup(log);
            };
            Mem_t(const char* log, v3f _color) {
                XsDate _tdate;
                color = _color;
                date = _strdup(std::string(str(_tdate.day()) + " - " + str(_tdate.month()) + " - " + str(_tdate.year())).c_str());
                text = _strdup(log);
            };
            v3f color = 1;
            char* date;
            char* text;
            std::string date_str() { return std::string(date); };
            std::string text_str() { return std::string(text); };
            const char* date_cstr() { return date; };
            const char* text_cstr() { return text; };
        };
        std::vector<Mem_t> data;
        void clear() { data.clear(); };
        void operator<<(const char* log) { data.push_back(Mem_t(log)); };
        void operator>>(const char* log) { data.push_back(Mem_t(log, XsRed)); };
        void add(const char* log, v3f _color) { data.push_back(Mem_t(log, _color)); };
        void add(std::string log, v3f _color) { data.push_back(Mem_t(log.c_str(), _color)); };
    };
    struct Vertices_t {
        XsVertices* vr;
        std::string name;
    };
    struct Texture_t {
        XsTextureSTB* tx;
        std::string name;
    };
    struct Array_t {
        v3f pos = 0;
        v3f rot = 0;
        v3f scale = 0;
        int limit = 1;
        bool use = false;
    };
    class Shape_t {
    private:
        XsLib* xs_lib;
        v3f origin = 0;
        bool lock_coll_to_shape = false;
        bool show_coll = false;
        float s_point = 1;
        float w_line = 1;
        bool use_shader = false;
        XsEnum f_XsEnum(int v) { return v == 0 ? XS_VERTEX : v == 1 ? XS_VERTEX_AND_TEXTURE : v == 2 ? XS_VERTEX_AND_NORMAL : XS_ALL; };
        GLenum f_GLenum(int v) { return v == 0 ? GL_POINTS : v == 1 ? GL_LINES : v == 2 ? GL_TRIANGLES : v == 3 ? GL_QUADS : GL_POLYGON; };
        XsSolidType f_SolidType(int v) {
            switch (v) {
            case 0: return XS_CUBE; break;
            case 1: return XS_PRISM; break;
            case 2: return XS_SPHERE; break;
            case 3: return XS_CYLINDER; break;
            case 4: return XS_CONE; break;
            case 5: return XS_ICOSPHERE; break;
            case 6: return XS_TORUS; break;
            case 7: return XS_TEAPOT; break;
            case 8: return XS_STAR; break;
            case 9: return XS_MONKE; break;
            };
        };
    public:
        bool advanced = false;
        int _selected_vert = 0;
        int _selected_tex = 0;
        int _selected_solid = 0;
        int _selected_coll = 0;
        int _xs_vert = 0;
        int _gl_vert = 0;
        XsShape* _shape;
        Array_t Array;
        Shape_t() {};
        Shape_t(XsLib& engine) { xs_lib = &engine; };
        XsShape& Shape() { return *_shape; };
        XsVertices& Vertices() { if (_selected_vert > 1) return *xs_lib->vertices[_selected_vert].vr; };
        XsTextureSTB& Texture() { if (_selected_tex != 0) return *xs_lib->textures[_selected_tex].tx; };
        XsColl& Coll() { if (_selected_coll != 0) return xs_lib->colls[_selected_coll].cl; };
        XsEnum XsMode() { return f_XsEnum(_xs_vert); };
        GLenum GLmode() { return f_GLenum(_gl_vert); };
        XsSolidType SolidType() { return f_SolidType(_selected_solid); };
        bool& isLockColl() { return lock_coll_to_shape; };
        bool& isShowColl() { return show_coll; };
        bool& useShader() { return use_shader; };
        float& pointScale() { return s_point; };
        float& lineWidth() { return w_line; };
        std::string name;
    };
    struct Shader_t {
        Shader_t() {};
        XsShader sd;
        std::string file_name_vs;
        std::string file_name_fs;
        std::string name;
    };
    struct Coll_t {
        Coll_t() {};
        XsColl cl;
        bool view = true;
        std::string name;
    };
    struct Effect_t {
        Effect_t() {};
        XsEffect ef;
        int type = 0;
        std::string name;
    };
    struct Shape2d_t {
        Shape2d_t() {};
        XsShape2d sh;
        std::string name;
    };
    struct Select_t {
        Select_t() {};
        std::string type = "none";
        int num = 0;
    };
    struct Dir_t {
        Dir_t() {};
        Dir_t(std::string p, bool d) {
            path = p;
            is_directory = d;
        };
        std::string path;
        bool is_directory;
    };
    v3f m_fdis = 110;
    v3f m_ldis = 2;
    v3f blue = v3f(34.f, 207.f, 230.f) / 255.f;
    v3f red = v3f(238.f, 23.f, 23.f) / 255.f;
    v3f green = v3f(XsDarkGreen);
    v3f bgColorDark = v3f(0.05f, 0.05f, 0.075f), bgColorLight = v3f(0.85f, 0.85f, 0.875f);
    std::string floor_shader_vs = "                                 \n\
        #version 400                                                \n\
        layout(location = 0) in vec3 aPos;                          \n\
                                                                    \n\
        void main() {                                               \n\
            gl_Position = ftransform();                             \n\
        };                                                          \n\
        ";
    std::string floor_shader_fs = "                                 \n\
        #version 400                                                \n\
        out vec4 FragColor;                                         \n\
                                                                    \n\
        float near = 0.20;                                          \n\
        float far = 100.0;                                          \n\
        float p = 100.0;                                            \n\
        uniform vec3 color;                                         \n\
        uniform float cam_y;                                        \n\
                                                                    \n\
        float linearizeDepth(float depth) {                         \n\
            float z = depth * 2.0 - 1.0;                            \n\
            return (2.0 * near * p) / (p + near - z * (p - near));  \n\
        };                                                          \n\
                                                                    \n\
        void main() {                                               \n\
            p = far - (far - abs(cam_y));                           \n\
            float alpha = linearizeDepth(gl_FragCoord.z) / p;       \n\
            FragColor = vec4(color, 1 - alpha);                     \n\
        };                                                          \n\
        ";
    XsShader floor_shader;
    void drawline(float x1, float y1, float z1, float x2 = 0, float y2 = 0, float z2 = 0) { glVertex3f(x1, y1, z1); glVertex3f(x2, y2, z2); };
    void drawfloor(XsShader& v);

    v2f cam_rot = v2f(0, 300);
    v2f cam_vel = 0;
    v2f last_mouse_pos = 0, plast_mouse_pos = 0;
    bool mouse_press = false;
    v2f m_sayac = 0;

    vex3f speed = 0;
    vex2f mouse_pos = 0;
    float speed_x = 100.f;

    XsPopUpSett p_sett;
    sf::Clock imclock;
    int leftshapenum = 1;
    int leftvertnum = 1;
    int lefttexnum = 1;
    int leftcollnum = 1;
    int lefteffectnum = 1;

    std::vector<Coll_t> colls;
    std::vector<Effect_t> effects;
    std::vector<Shape_t> shapes;
    std::vector<Vertices_t> vertices;
    std::vector<Texture_t> textures;
    std::vector<Shader_t> shaders;
    std::vector<char*> coll_name = { _strdup("none") };
    std::vector<char*> effect_name = { _strdup("none") };
    std::vector<char*> vert_name = {_strdup("none"), _strdup("solid")};
    std::vector<char*> shape_name = { _strdup("none") };
    std::vector<char*> tex_name = { _strdup("none") };
    std::vector<char*> shader_name = { _strdup("none") };
    const char* p_format_types[3]{ "RGB", "RGBA", "SRGB" };
    const char* p_filter_types[2]{ "Nearest", "Linear" };
    const char* p_wrap_types[4]{ "Repeat", "Mirrored Repeat", "Clamp to Edge", "Clamp to Border" };
    const char* xs_vert_types[4]{ "vertex", "vertex and texture", "vertex and normal", "all" };
    const char* gl_vert_types[5]{ "points", "lines", "triangles", "quads", "polygon" };
    const char* solid_types[10]{ "cube", "prism", "sphere", "cylinder", "cone", "ico sphere", "torus", "teapot", "star", "monke", };
    const char* file_format[3]{ "default", "obj", "xs.model" };
    int vert_load_format = 0;
    std::string input_text;

    float fps = 1.f;
    XsChrono fps_tm;
    std::chrono::high_resolution_clock::time_point s_fps;

    XsChrono set_cam_speed_tm;
    bool show_cam_speed = false;
    XsChrono show_cam_info_tm;
    bool show_cam_info = false;
    
    Shape_t nw_st;
    Vertices_t nw_vt;
    Texture_t nw_tt;
    Coll_t nw_ct;
    Effect_t nw_et;
    int s_ns = 0;
    int s_nv = 0;
    int s_nt = 0;
    int s_nc = 0;
    int s_ne = 0;
    char** _tsv;
    ImGuiStyle* t_nthm;
    ImGuiStyle _thm;
    v2f left_panel_size = v2f(7, 1);
    v2f right_panel_size = v2f(5, 1);
    bool r_panel = false;
    int l_panel_menu = 0;
    float log_y = 0;
    v2f tool_pos;
    Select_t selected;
    Select_t selected_r;
    std::string selected_a = "log";
    bool is_drop = false;
    std::string drop_path;

    int lt_f = 0, lt_w = 0, lt_t = 0;
    std::string _notepad;
    std::vector<push_t> pushs;
    volatile bool game_mode = true;
    XsEnum f_XsEnum(int v) { return v == 0 ? XS_VERTEX : v == 1 ? XS_VERTEX_AND_TEXTURE : v == 2 ? XS_VERTEX_AND_NORMAL : XS_ALL; };
    GLenum f_GLenum(int v) { return v == 0 ? GL_POINTS : v == 1 ? GL_LINES : v == 2 ? GL_TRIANGLES : v == 3 ? GL_QUADS : GL_POLYGON; };
    XsSolidType f_SolidType(int v) {
        switch (v) {
        case 0: return XS_CUBE; break;
        case 1: return XS_PRISM; break;
        case 2: return XS_SPHERE; break;
        case 3: return XS_CYLINDER; break;
        case 4: return XS_CONE; break;
        case 5: return XS_ICOSPHERE; break;
        case 6: return XS_TORUS; break;
        case 7: return XS_TEAPOT; break;
        case 8: return XS_STAR; break;
        case 9: return XS_MONKE; break;
        };
    };
    ImVec4 ximColor(v3f v) { return ImVec4(v.x, v.y, v.z, 1.f); };
    ImVec4 ximColor(v3f v, float va) { return ImVec4(v.x, v.y, v.z, va); };

    XsChrono tex_preview_timer;
    bool preview_loaded = false;
    std::string first_preview_file = "", last_preview_file = "";

    std::string export_array_name = "Array";
    std::string loaded_file;
    std::string path;

    sf::Texture textfile_icon, folder_icon, imagefile_icon, updir_icon, model_icon;
    std::string preview_path, preview_filename;
    XsChrono preview_tm;
    bool im_preview = false;
    sf::Texture preview_tex;
    std::vector<Dir_t> dir_iterator;

    void camera_sett();
    void ui();
    void logpanel();
    void tools();
    void xsui();
    void setThem(int v);

    bool use_skybox = false;
    vex2f sky_rot = 0;
    int sky_f = 0, sky_w = 0, sky_fl = 0;
    std::string sky_img_path;
    XsSky skybox;

    bool Sett = false;
    short int them = 1; // 0 = dark, 1 = light
    XsSaver* file;
    const char* WindowName = "";
    bool show_floor = true;
public:
    void Save(const char* file_name);
    void Load(const char* file_name);
    XsCamera Camera;
    sf::RenderWindow Window;
    sf::Event Event;
    std::vector<Shape_t>& Shapes() { return shapes; };
    std::vector<Vertices_t>& Vertices() { return vertices; };
    std::vector<Texture_t>& Texture() { return textures; };
    XsSky& Sky() { return skybox; };
    XsShape& getXsShape(const char* const name) {
        for (auto& i : shapes)
            if (i.name == name)
                return i.Shape();
        Log >> "Failed \"getXsShape()\" function.";
        std::cerr << "Cannot find this Shape.\n";
    };
    Shape_t& getShape(const char* const name) {
        for (auto& i : shapes)
            if (i.name == name)
                return i;
        Log >> "Failed \"getShape()\" function.";
        std::cerr << "Cannot find this Shape.\n";
    };
    Log_t Log;
    XsLib() {};
    XsLib(const char* window_name) {
        srand(time(NULL));
        sf::ContextSettings csett;
        csett.depthBits = 24;
        csett.stencilBits = 8;
        csett.antialiasingLevel = 0;
        csett.majorVersion = 3;
        csett.minorVersion = 3;
        csett.sRgbCapable = false;
        WindowName = window_name;
        Window.create(sf::VideoMode(1200, 700), WindowName, sf::Style::Default, csett);
        Log << "Create window.";
        ImGui::SFML::Init(Window);
        ImGui::GetIO().Fonts->Clear();
        ImGui::GetIO().Fonts->AddFontFromFileTTF("media/font.ttf", 18.f);
        ImGui::SFML::UpdateFontTexture();
        glewInit();
        glEnable(GL_SCISSOR_TEST);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glEnable(GL_TEXTURE_2D);
        glBlendFunc(GL_ZERO, GL_SRC_COLOR);
        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
        glBlendEquation(GL_FUNC_ADD);
        glDepthFunc(GL_LESS);

        Camera.fov = 45.0f;
        Camera.far_ = 100;
        Camera.viewport = vex2f(1200, 750);
        Camera.near_ = 0.2;
        Camera.pos = vex3f(-20, 20, 0);

        skybox.color = 1;
        skybox.position = Camera.pos;
        skybox.rotation = 0;

        floor_shader = XsShader(floor_shader_vs, floor_shader_fs);
        setThem(0);
        t_nthm = &ImGui::GetStyle();
        _thm = ImGui::GetStyle();

        path = std::filesystem::current_path().string();
        for (const auto& i : std::filesystem::directory_iterator(path))
            dir_iterator.push_back(Dir_t(i.path().string(), i.is_directory()));

        textfile_icon.loadFromFile("media/textfile.png");
        folder_icon.loadFromFile("media/folder.png");
        imagefile_icon.loadFromFile("media/imagefile.png");
        updir_icon.loadFromFile("media/updir.png");
        model_icon.loadFromFile("media/3dmodel.png");

        nw_st.name = "Shape 0";
        nw_vt.name = "Vertices 0";
        nw_tt.name = "Texture 0";
        nw_ct.name = "Coll 1";
        nw_et.name = "Effect 0";
        ImGuiFileDialog::Instance()->SetExtentionInfos(".xs.model", ImVec4(XsRed.x,XsRed.y,XsRed.z,0.9), "XS");
    };
    std::vector<push_t> Pushs() { return pushs; };
    /*
    push your function in code.
    codes;
    -> "normal"
    -> "in imgui",
    -> "before camera" "after camera"
    -> "before display", "after display"
    -> "before process", "after process"
    -> "before clear", "after clear"
    -> "before draw", "after draw"
    */
    void Push(void (*push_v)(void), const char* code = "normal") {
        pushs.push_back(push_t(push_v, code));
        Log << "Push function";
    };
    float Fps() { return fps; };

    void operator<<(XsShape& v);
    void operator<<(XsVertices& v);
    void operator<<(XsTextureSTB& v);
    void Create(const char* window_name);
    void Start();
};
#include "XsEngineInit.hpp"
#include "XsEngineUI.hpp"
#include "XsEngineTools.hpp"
#include "XsEngineLogPanel.hpp"
#include "XsEngineStart.hpp"
