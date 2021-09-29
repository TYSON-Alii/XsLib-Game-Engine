#define s static
#define glCol glColor3f
#define glCol4 glColor4f
#define glBeg glBegin
#define glL glLoadIdentity
#define im ImGui
using namespace std;

v3f XsHexToRGB(int hex) {
    v3f _t;
    _t.x = ((hex >> 16) & 0xff) / 255.f;
    _t.y = ((hex >> 8) & 0xff) / 255.f;
    _t.z = ((hex) & 0xff) / 255.f;
    return _t;
};
class XsLib;
class XsLib {
public:
    struct push_t {
        push_t() {};
        push_t(void (*push_v)(void), const char* code) {
            push_data = push_v;
            push_t::code = code;
        };
        void (*push_data)(void);
        const char* code;
    };
private:
    struct Log_t {
        struct Mem_t {
            Mem_t() {};
            Mem_t(const char* log) {
                XsDate _tdate;
                date = _strdup(string(str(_tdate.day()) + " - " + str(_tdate.month()) + " - " + str(_tdate.year())).c_str());
                text = _strdup(log);
            };
            Mem_t(const char* log, v3f _color) {
                XsDate _tdate;
                color = _color;
                date = _strdup(string(str(_tdate.day()) + " - " + str(_tdate.month()) + " - " + str(_tdate.year())).c_str());
                text = _strdup(log);
            };
            v3f color = 1;
            char* date;
            char* text;
            string date_str() { return string(date); };
            string text_str() { return string(text); };
            const char* date_cstr() { return date; };
            const char* text_cstr() { return text; };
        };
        std::vector<Mem_t> data;
        void clear() { data.clear(); };
        void operator<<(const char* log) { data.push_back(Mem_t(log)); };
        void operator<<(string log) { data.push_back(Mem_t(log.c_str())); };
        void operator>>(const char* log) { data.push_back(Mem_t(log, XsRed)); };
        void operator>>(string log) { data.push_back(Mem_t(log.c_str(), XsRed)); };
        void add(const char* log, v3f _color) { data.push_back(Mem_t(log, _color)); };
        void add(string log, v3f _color) { data.push_back(Mem_t(log.c_str(), _color)); };
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
    void drawfloor(XsShader& v) {
        glDepthFunc(GL_ALWAYS);
        glDepthMask(GL_FALSE);
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_POINT_SMOOTH);
        glL();
        v.use();
        v("projection", camera.projectionMatrix());
        v("view", camera.viewMatrix);
        if (them == 1)
            v("color", bgColorDark);
        else if (them == 0)
            v("color", bgColorLight);
        v("cam_y", camera.pos.y);
        if (3 > fabs(camera.pos.y))
            glLineWidth(4.1 - fabs(camera.pos.y));
        else
            glLineWidth(1);
        glTranslatef(ceil(camera.pos.x / 2) * 2, 0, ceil(camera.pos.z / 2) * 2);
        glBeg(GL_LINES);
        rep(m_ldis.x * m_fdis.z, 2.f)
            if ((ceil(camera.pos.z / 2) * 2) + m_fdis.z - i != 0)
                drawline(m_fdis.x, 0, m_fdis.z - i, -m_fdis.x, 0, m_fdis.z - i);
        glEnd();

        glBeg(GL_LINES);
        rep(m_ldis.z * m_fdis.x, 2.f)
            if ((ceil(camera.pos.x / 2) * 2) + m_fdis.x - i != 0)
                drawline(m_fdis.x - i, 0, m_fdis.z, m_fdis.x - i, 0, -m_fdis.z);
        glEnd();

        glL();
        if (4 > fabs(camera.pos.y))
            glLineWidth(5.1 - fabs(camera.pos.y));
        else
            glLineWidth(2);
        v("color", blue);
        glBeg(GL_LINES);
        drawline(0, 0, m_fdis.z + camera.pos.z, 0, 0, -m_fdis.z + camera.pos.z);
        glEnd();
        v("color", red);
        glBeg(GL_LINES);
        drawline(m_fdis.x + camera.pos.x, 0, 0, -m_fdis.x + camera.pos.x, 0, 0);
        glEnd();
        v("color", green);
        glBeg(GL_LINES);
        drawline(0, m_fdis.y + camera.pos.y, 0, 0, -m_fdis.y + camera.pos.y, 0);
        glEnd();

        v.disuse();
        glDepthFunc(GL_LESS);
        glDepthMask(GL_TRUE);
    };

    v2f cam_rot = v2f(0, 300);
    v2f cam_vel = 0;
    v2f last_mouse_pos = 0, plast_mouse_pos = 0;
    bool mouse_press = false;
    v2f m_sayac = 0;

    vex3f speed = 0;
    vex2f mouse_pos = 0;

    float speed_x = 100.f;

    void camera_sett() {
        camera.viewport = vex2f(window.getSize().x, window.getSize().y);
        if (game_mode) {
            if (XsIsKeyPressed(XS_MOUSE_RIGHT)) {
                if (event.type == sf::Event::MouseWheelMoved) {
                    speed_x += (float)event.mouseWheel.delta * 10;
                    if (speed_x < 20)
                        speed_x = 20;
                    show_cam_speed = true;
                    set_cam_speed_tm.restart();
                }
                else {
                    if (set_cam_speed_tm.getMilliSeconds() > 2.f)
                        show_cam_speed = false;
                };
                if (XsIsKeyPressed(XS_KEY_W) && !XsIsKeyPressed(XS_KEY_SPACE))
                    speed += camera.rot * (1.f / speed_x);
                else if (XsIsKeyPressed(XS_KEY_S) && !XsIsKeyPressed(XS_KEY_SPACE))
                    speed -= camera.rot * (1.f / speed_x);
                if (mouse_press == false) {
                    last_mouse_pos = mouse_pos;
                    mouse_press = true;
                }
                v2f f_pos = mouse_pos - last_mouse_pos;
                v2f sm_pos = cam_rot + f_pos;
                cam_vel = (sm_pos - cam_rot) / 17.5;
                last_mouse_pos += cam_vel;

                show_cam_info = true;
                show_cam_info_tm.restart();
            }
            else {
                if (show_cam_info_tm.getMilliSeconds() > 2.f)
                    show_cam_info = false;
                mouse_press = false;
            };
            if (!XsIsKeyPressed(XS_KEY_S) && !XsIsKeyPressed(XS_KEY_W))
                speed *= 0.95;
            if (XsIsKeyPressed(XS_KEY_SPACE))
                speed *= 0.75f;
            camera.pos += speed;
            cam_vel *= 0.88;
            cam_rot += cam_vel;
        }
        XsFPSCamera(camera, cam_rot - vex2f(0, 300), 0.3);
    };

    XsPopUpSett p_sett;
    sf::Clock imclock;
    int leftshapenum = 1;
    int leftvertnum = 1;
    int lefttexnum = 1;
    int leftcollnum = 1;
    int lefteffectnum = 1;

    struct Vertices_t {
        XsVertices vr;
        string name;
    };
    struct Texture_t {
        XsTextureSTB tx;
        string name;
    };
    struct Shape_t {
        XsShape* sh = nullptr;
        v3f origin = 0;
        //string set_value[5];
        int s_vert = 0;
        int xs_vert = 0;
        int gl_vert = 0;
        int s_texture = 0;
        int s_solid = 0;
        int s_coll = 0;
        bool lock_coll_to_shape = false;
        bool show_coll = false;
        float s_point = 1;
        float w_line = 1;
        bool advanced = false;
        bool use_shader = false;
        string name;
    };
    struct Shader_t {
        XsShader sd;
        string file_name_vs;
        string file_name_fs;
        string name;
    };
    struct Coll_t {
        XsColl cl;
        bool view = true;
        string name;
    };
    struct Effect_t {
        XsEffect ef;
        int type = 0;
        string name;
    };
    struct Shape2d_t {
        XsShape2d sh;
        string name;
    };
    vector<Coll_t> colls;
    vector<Effect_t> effects;
    vector<Shape_t> shapes;
    vector<Vertices_t> vertices;
    vector<Texture_t> textures;
    vector<Shader_t> shaders;
    vector<char*> coll_name = { _strdup("none") };
    vector<char*> effect_name = { _strdup("none") };
    vector<char*> vert_name = {_strdup("none"), _strdup("solid")};
    vector<char*> shape_name = { _strdup("none") };
    vector<char*> tex_name = { _strdup("none") };
    vector<char*> shader_name = { _strdup("none") };
    const const char* p_format_types[3]{ "RGB", "RGBA", "SRGB" };
    const const char* p_filter_types[2]{ "Nearest", "Linear" };
    const const char* p_wrap_types[4]{ "Repeat", "Mirrored Repeat", "Clamp to Edge", "Clamp to Border" };
    const const char* xs_vert_types[4]{ "vertex", "vertex and texture", "vertex and normal", "all" };
    const const char* gl_vert_types[5]{ "points", "lines", "triangles", "quads", "polygon" };
    const const char* solid_types[10]{ "cube", "prism", "sphere", "cylinder", "cone", "ico sphere", "torus", "teapot", "star", "monke", };
    
    string input_text;
    const const char* file_format[3]{ "default", "obj", "xs.model" };
    int vert_load_format = 0;

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
    v2f left_panel_size = v2f(7.5, 1);
    v2f right_panel_size = v2f(5, 1);

    struct Select_t {
        string type = "none";
        int num = -1;
    };
    Select_t selected;
    Select_t selected_r;

    int lt_f = 0, lt_w = 0, lt_t = 0;
    void ui();

    string _notepad;
    void otherui();

    void xsui() {
    //    p_sett.screenSize = camera.viewport;
    //    p_sett.begin();
    //    glLoadIdentity();
    //    glCol(XsRed);
    //    v3f m_rot;
    //    m_rot.x = cos(glm::radians(d_yaw)) * cos(glm::radians(d_pitch));
    //    m_rot.y = -sin(glm::radians(d_pitch));
    //    m_rot.z = sin(glm::radians(d_yaw)) * cos(glm::radians(d_pitch));
    //    glTranslatef(camera.viewport.x - (camera.viewport.x / 5) + 100, 50 / m_rot.z, 0);
    //    glBegin(GL_POLYGON);
    //    XsSolidPolygone(100, 5);
    //    glEnd();
    //    p_sett.end();
    }
    vector<push_t> pushs;
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

    const char* WindowName = "";

    ImVec4 ximColor(v3f v) { return ImVec4(v.x, v.y, v.z, 1.f); };
    ImVec4 ximColor(v3f v, float va) { return ImVec4(v.x, v.y, v.z, va); };

    XsChrono tex_preview_timer;
    sf::Texture preview_tex;
    bool preview_loaded = false;
    string first_preview_file = "", last_preview_file = "";

    short int them = 1; // 0 = dark, 1 = light
    void setThem(int v) {
        if (v == 0 and them != v) {
            ImVec4* colors = ImGui::GetStyle().Colors;
            colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 0.98f);
            colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 0.91f);
            colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.56f);
            colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
            colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
            colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            colors[ImGuiCol_FrameBg] = ImVec4(0.12f, 0.10f, 0.21f, 1.00f);
            colors[ImGuiCol_FrameBgHovered] = ImVec4(0.37f, 0.17f, 0.69f, 1.00f);
            colors[ImGuiCol_FrameBgActive] = ImVec4(0.45f, 0.31f, 0.85f, 1.00f);
            colors[ImGuiCol_TitleBg] = ImVec4(0.16f, 0.16f, 0.19f, 0.94f);
            colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.16f, 0.19f, 0.96f);
            colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.16f, 0.16f, 0.19f, 0.98f);
            colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
            colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
            colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
            colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
            colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
            colors[ImGuiCol_CheckMark] = ImVec4(0.82f, 0.42f, 0.48f, 1.00f);
            colors[ImGuiCol_SliderGrab] = ImVec4(0.45f, 0.31f, 0.85f, 1.00f);
            colors[ImGuiCol_SliderGrabActive] = ImVec4(0.37f, 0.17f, 0.69f, 1.00f);
            colors[ImGuiCol_Button] = ImVec4(0.29f, 0.07f, 0.11f, 1.00f);
            colors[ImGuiCol_ButtonHovered] = ImVec4(0.42f, 0.11f, 0.18f, 1.00f);
            colors[ImGuiCol_ButtonActive] = ImVec4(0.42f, 0.11f, 0.18f, 1.00f);
            colors[ImGuiCol_Header] = ImVec4(0.12f, 0.10f, 0.21f, 1.00f);
            colors[ImGuiCol_HeaderHovered] = ImVec4(0.37f, 0.17f, 0.69f, 1.00f);
            colors[ImGuiCol_HeaderActive] = ImVec4(0.45f, 0.31f, 0.85f, 1.00f);
            colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
            colors[ImGuiCol_SeparatorHovered] = ImVec4(0.91f, 0.52f, 0.64f, 0.78f);
            colors[ImGuiCol_SeparatorActive] = ImVec4(0.67f, 0.64f, 0.81f, 1.00f);
            colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.02f, 0.04f, 0.20f);
            colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.41f, 0.41f, 0.41f, 0.67f);
            colors[ImGuiCol_ResizeGripActive] = ImVec4(0.35f, 0.35f, 0.35f, 0.95f);
            colors[ImGuiCol_Tab] = ImVec4(0.28f, 0.17f, 0.44f, 0.86f);
            colors[ImGuiCol_TabHovered] = ImVec4(0.28f, 0.16f, 0.71f, 0.80f);
            colors[ImGuiCol_TabActive] = ImVec4(0.10f, 0.06f, 0.24f, 1.00f);
            colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
            colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.30f, 0.26f, 0.39f, 1.00f);
            colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
            colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
            colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
            colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
            colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
            colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
            colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
            colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
            colors[ImGuiCol_TextSelectedBg] = ImVec4(0.64f, 0.78f, 0.94f, 0.35f);
            colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
            colors[ImGuiCol_NavHighlight] = ImVec4(0.69f, 0.79f, 0.90f, 1.00f);
            colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
            colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
            colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
            them = 0;
        }
        else if (v == 1 and them != v) {
            ImVec4* colors = ImGui::GetStyle().Colors;
            colors[ImGuiCol_Text] = ImVec4(0.03f, 0.03f, 0.03f, 0.98f);
            colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 0.91f);
            colors[ImGuiCol_WindowBg] = ImVec4(0.95f, 0.95f, 0.95f, 0.56f);
            colors[ImGuiCol_ChildBg] = ImVec4(0.93f, 0.93f, 0.93f, 0.00f);
            colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
            colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
            colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            colors[ImGuiCol_FrameBg] = ImVec4(0.41f, 0.42f, 0.48f, 1.00f);
            colors[ImGuiCol_FrameBgHovered] = ImVec4(0.33f, 0.34f, 0.43f, 1.00f);
            colors[ImGuiCol_FrameBgActive] = ImVec4(0.33f, 0.32f, 0.40f, 1.00f);
            colors[ImGuiCol_TitleBg] = ImVec4(0.16f, 0.16f, 0.19f, 0.94f);
            colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.16f, 0.19f, 0.96f);
            colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.16f, 0.16f, 0.19f, 0.98f);
            colors[ImGuiCol_MenuBarBg] = ImVec4(0.73f, 0.73f, 0.73f, 1.00f);
            colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
            colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
            colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
            colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
            colors[ImGuiCol_CheckMark] = ImVec4(0.42f, 0.48f, 0.82f, 1.00f);
            colors[ImGuiCol_SliderGrab] = ImVec4(0.31f, 0.36f, 0.85f, 1.00f);
            colors[ImGuiCol_SliderGrabActive] = ImVec4(0.17f, 0.21f, 0.69f, 1.00f);
            colors[ImGuiCol_Button] = ImVec4(0.17f, 0.18f, 0.26f, 1.00f);
            colors[ImGuiCol_ButtonHovered] = ImVec4(0.13f, 0.14f, 0.16f, 1.00f);
            colors[ImGuiCol_ButtonActive] = ImVec4(0.10f, 0.10f, 0.12f, 1.00f);
            colors[ImGuiCol_Header] = ImVec4(0.21f, 0.21f, 0.25f, 1.00f);
            colors[ImGuiCol_HeaderHovered] = ImVec4(0.22f, 0.23f, 0.29f, 1.00f);
            colors[ImGuiCol_HeaderActive] = ImVec4(0.45f, 0.31f, 0.85f, 1.00f);
            colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
            colors[ImGuiCol_SeparatorHovered] = ImVec4(0.52f, 0.59f, 0.91f, 0.78f);
            colors[ImGuiCol_SeparatorActive] = ImVec4(0.67f, 0.64f, 0.81f, 1.00f);
            colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.02f, 0.04f, 0.20f);
            colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.41f, 0.41f, 0.41f, 0.67f);
            colors[ImGuiCol_ResizeGripActive] = ImVec4(0.35f, 0.35f, 0.35f, 0.95f);
            colors[ImGuiCol_Tab] = ImVec4(0.20f, 0.21f, 0.25f, 0.86f);
            colors[ImGuiCol_TabHovered] = ImVec4(0.21f, 0.20f, 0.24f, 0.80f);
            colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.26f, 1.00f);
            colors[ImGuiCol_TabUnfocused] = ImVec4(0.09f, 0.07f, 0.15f, 0.97f);
            colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.18f, 0.18f, 0.25f, 1.00f);
            colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
            colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
            colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
            colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
            colors[ImGuiCol_TableHeaderBg] = ImVec4(0.13f, 0.13f, 0.15f, 1.00f);
            colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
            colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
            colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
            colors[ImGuiCol_TextSelectedBg] = ImVec4(0.64f, 0.78f, 0.94f, 0.35f);
            colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
            colors[ImGuiCol_NavHighlight] = ImVec4(0.69f, 0.79f, 0.90f, 1.00f);
            colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
            colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
            colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
            them = 1;
        };
    };
    XsSaver* file;
public:
    void save(const char* file_name) {
        file = new XsSaver(file_name);
        file->clear();
        file->add(WindowName, "window_name");
        file->add(cam_rot, "cam_rot");
        file->add(speed_x, "speed_x");
        file->add(them, "them");
        file->add(input_text, "input_text");
        file->add(vert_load_format, "vert_load_format");
        file->add(selected_r.type, "selected_r_type");
        file->add(selected_r.num, "selected_r_num");
        file->add(selected.type, "selected_type");
        file->add(selected.num, "selected_num");
        file->add(camera.pos, "cam_pos");
        file->add(camera.rot, "cam_rot");
        file->add(camera.viewport, "cam_viewp");
        file->add(camera.near_, "cam_near");
        file->add(camera.far_, "cam_far");
        file->add(camera.fov, "cam_fov");
    };
    void load(const char* file_name) {
        file = new XsSaver(file_name);
        WindowName = file->getcstr("window_name");
        cam_rot = file->getv2f("cam_rot");
        speed_x = file->getf("speed_x");
        them = file->geti("them");
        input_text = file->getstr("input_text");
        vert_load_format = file->geti("vert_load_format");
        selected_r.type = file->getstr("selected_r_type");
        selected_r.num = file->geti("selected_r_num");
        selected.type = file->getstr("selected_type");
        selected.num = file->geti("selected_num");
        camera.pos = file->getv3f("cam_pos");
        camera.rot = file->getv3f("cam_rot");
        camera.viewport = file->getv2f("cam_viewp");
        camera.near_ = file->getf("cam_near");
        camera.far_ = file->getf("cam_far");
        camera.fov = file->getf("cam_fov");
    }
    XsCamera camera;
    sf::RenderWindow window;
    sf::Event event;
    vector<Shape_t>& Shapes() { return shapes; };
    vector<Vertices_t>& Vertices() { return vertices; };
    vector<Texture_t>& Texture() { return textures; };
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
        window.create(sf::VideoMode(WIDTH, HEIGHT), WindowName, sf::Style::Default, csett);
        Log << "Create window.";
        ImGui::SFML::Init(window);
        ImGui::GetIO().Fonts->Clear();
        ImGui::GetIO().Fonts->AddFontFromFileTTF("font.ttf", 18.f);
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

        camera.fov = 45.0f;
        camera.far_ = 100;
        camera.viewport = vex2f(WIDTH, HEIGHT);
        camera.near_ = 0.2;
        camera.pos = vex3f(-20, 20, 0);

        floor_shader = XsShader(floor_shader_vs, floor_shader_fs);
        setThem(0);
        t_nthm = &im::GetStyle();
        _thm = im::GetStyle();

        nw_st.name = "Shape 0";
        nw_vt.name = "Vertices 0";
        nw_tt.name = "Texture 0";
        nw_ct.name = "Coll 1";
        nw_et.name = "Effect 0";
        ImGuiFileDialog::Instance()->SetExtentionInfos(".xs.model", ImVec4(XsRed.x,XsRed.y,XsRed.z,0.9), "XS");

    };
    vector<push_t> Pushs() { return pushs; };
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

    void operator<<(XsShape& v) {
        Shape_t _t;
        _t.name = string("Shape ") + str(leftshapenum);
        _t.sh = new XsShape(v);
        shapes.push_back(_t);
        shape_name.push_back(_strdup(_t.name.c_str()));
        leftshapenum++;
        nw_st.name = string("Shape ") + to_string(leftshapenum);
        Log << "Add a 3D Shape";
    };
    void operator<<(XsVertices& v) {
        Vertices_t _t;
        _t.name = string("Vertices ") + to_string(leftvertnum);
        _t.vr = v;
        vert_name.push_back(_strdup(_t.name.c_str()));
        vertices.push_back(_t);
        leftvertnum++;
        nw_vt.name = string("Vertices ") + to_string(leftvertnum);
        Log << "Add a Vertices";
    };
    void operator<<(XsTextureSTB& v) {
        Texture_t _t;
        _t.name = string("Texture ") + to_string(lefttexnum);
        _t.tx = v;
        tex_name.push_back(_strdup(_t.name.c_str()));
        textures.push_back(_t);
        lefttexnum++;
        nw_tt.name = string("Texture ") + to_string(lefttexnum);
        Log << "Add a Texture";
    };
    /*void Add(auto& v, const char* name) {
        Shape_t _t;
        if (typeid(v).name() == "class XsShape") {
            _t.name = name;
            _t.type = "XsShape";
            _t.ptr = &v;
            shapes.push_back(_t);
        }
        else if (typeid(v).name() == "class XsShape2d") {
            _t.name = name;
            _t.type = "XsShape2d";
            _t.ptr = &v;
            shapes.push_back(_t);
        }
        else
            XsLog(XsLogRed, XsLogWhite, "Wrong Shape Type..\n");
    };
    */

    void Draw() {
        while (window.isOpen()) {
            s_fps = std::chrono::high_resolution_clock::now();
            for (auto& i : pushs)
                if (i.code == "before clear") {
                    i.push_data();
                    break;
                };
            if (them == 0)
                glClearColor(bgColorDark.x, bgColorDark.y, bgColorDark.z, 0.f);
            else if (them == 1)
                glClearColor(bgColorLight.x, bgColorLight.y, bgColorLight.z, 0.f);
            glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
            for (auto& i : pushs)
                if (i.code == "after clear" or i.code == "before process") {
                    i.push_data();
                    break;
                };
            window.pollEvent(event);
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) {
                selected.type = "none";
                selected.num = 0;
                selected_r.type = "none";
                selected_r.num = 0;
                save("new_proj.xs.save");
                Log << "Window closed";
                window.close();
                break;
            };
            mouse_pos = XsGetMousePos();
            for (auto& i : pushs)
                if (i.code == "after process" or i.code == "before camera") {
                    i.push_data();
                    break;
                };
            camera_sett();
            if (game_mode)
                drawfloor(floor_shader);

            for (auto& i : pushs)
                if (i.code == "after camera" or i.code == "normal" or i.code == "before draw") {
                    i.push_data();
                    break;
                };

            for (auto& i : shapes) {
                if (i.s_coll > 0) {
                    if (i.lock_coll_to_shape) {
                        XsColl _t = colls[i.s_coll - 1].cl;
                        _t.pos = i.sh->pos + colls[i.s_coll - 1].cl.pos;
                        if (i.show_coll)
                            XsDrawColl(_t, 0.1);
                    }
                    else
                        if (i.show_coll)
                            XsDrawColl(colls[i.s_coll - 1].cl, 0.1);
                };
                if (i.s_vert > 1) {
                    glL();
                    if (i.gl_vert == 0 and shapes[selected_r.num].s_vert > 1)
                        glPointSize(i.s_point);
                    elif(i.gl_vert == 1 and shapes[selected_r.num].s_vert > 1)
                        glLineWidth(i.w_line);
                    if (i.s_texture > 0) {
                        i.sh->draw(vertices[i.s_vert - 2].vr, textures[i.s_texture - 1].tx, f_XsEnum(i.xs_vert), f_GLenum(i.gl_vert));
                        glBindTexture(GL_TEXTURE_2D, 0);
                    }
                    else
                        i.sh->draw(vertices[i.s_vert - 2].vr, f_XsEnum(i.xs_vert), f_GLenum(i.gl_vert));
                }
                elif(i.s_vert == 1) {
                    glL();
                    if (i.s_texture > 0) {
                        textures[i.s_texture - 1].tx.bind();
                        i.sh->draw(f_SolidType(i.s_solid), f_XsEnum(i.xs_vert));
                        glBindTexture(GL_TEXTURE_2D, 0);
                    }
                    else
                        i.sh->draw(f_SolidType(i.s_solid), f_XsEnum(i.xs_vert));
                }
            };

            for (auto& i : pushs)
                if (i.code == "after draw") {
                    i.push_data();
                    break;
                };

            if (game_mode)
                xsui();

            ImGui::SFML::Update(window, imclock.restart());
            ImGuizmo::BeginFrame();

            if (game_mode) {
                ui();
                otherui();
            };

            //im::ShowDemoWindow();

            for (auto& i : pushs)
                if (i.code == "in imgui") {
                    i.push_data();
                    break;
                };
            
            window.pushGLStates();
            ImGui::SFML::Render(window);
            window.popGLStates();
            window.display();
            if (fps_tm.getMilliSeconds() > 0.1) {
                fps_tm.restart();
                fps = (float)1e9 / (float)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - s_fps).count();
            };
        };
    };
};
#include "XsEngineUI.hpp"
