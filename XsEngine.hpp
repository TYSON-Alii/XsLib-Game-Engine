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
    v3f white = v3f(0.8f, 0.8f, 0.8f);
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
        glL();
        v.use();
        v("projection", camera.projectionMatrix());
        v("view", camera.viewMatrix);
        v("color", white);
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
                    cout << speed_x << '\n';
                    speed_x += (float)event.mouseWheel.delta * 10;
                    if (speed_x < 20)
                        speed_x = 20;
                    b_c_speed = true;
                    c_speed.restart();
                }
                else {
                    if (c_speed.getMilliSeconds() > 2.f)
                        b_c_speed = false;
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

                b_c_move = true;
                c_move.restart();
            }
            else {
                if (c_move.getMilliSeconds() > 2.f)
                    b_c_move = false;
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

    XsPopUpSett popup_sett;
    bool b_shape = false;
    int s_shape = -1;
    sf::Clock imclock;
    int leftshapenum = 0;
    int leftvertnum = 0;

    struct Vertices_t {
        XsVertices vr;
        string name;
    };
    struct Texture_t {
        XsTextureSTB tx;
        string name;
    };
    struct Shape_t {
        XsShape sh;
        Vertices_t vert;
        int s_vert = 0;
        int xs_vert = 0;
        int gl_vert = 0;
        int s_texture = 0;
        int s_solid = 0;
        float s_point = 1;
        float w_line = 1;
        string name;
    };
    struct Shape2d_t {
        XsShape2d sh;
        string name;
    };
    vector<Shape_t> shapes;
    bool b_vert = false;
    int s_vert = -1;
    vector<Vertices_t> vertices;
    vector<char*> vert_name = {_strdup("none"), _strdup("solid")};

    const const char* xs_vert_types[4]{ "vertex", "vertex and texture", "vertex and normal", "all" };
    const const char* gl_vert_types[5]{ "points", "lines", "triangles", "quads", "polygon" };
    const const char* solid_types[10]{ "cube", "prism", "sphere", "cylinder", "cone", "ico sphere", "torus", "teapot", "star", "monke", };
    
    string input_text;
    const const char* file_format[3]{ "default", "obj", "xs.model" };
    int c_file_format = 0;

    float fps = 1.f;
    std::chrono::high_resolution_clock::time_point s_fps;

    XsChrono c_speed;
    bool b_c_speed = false;

    XsChrono c_move;
    bool b_c_move = false;
    
    bool s_del = false;
    void ui() {
        im::Begin("general settings", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoTitleBar);
        im::SetWindowPos({ camera.viewport.x / 10, -5 });
        im::SetWindowSize({ 300, 200 });
        im::Text(WindowName);
        if (b_c_move) {
            im::Text(string(string("pos x: ") + to_string(int(camera.pos.x)) + " y: " + to_string(int(camera.pos.y)) + " z: " + to_string(int(camera.pos.z))).c_str());
            im::Text(string(string("rot x: ") + to_string(camera.rot.x) + " y: " + to_string(camera.rot.y) + " z: " + to_string(camera.rot.z)).c_str());
        };
        if (b_c_speed)
            im::Text(string(string("camera speed: ") + str(speed_x)).c_str());
        im::PushStyleColor(ImGuiCol_Text, ImVec4(XsYellow.x, XsYellow.y, XsYellow.z, 0.76));
        im::Text(string(string("fps: ") + to_string(int(fps))).c_str());
        im::PopStyleColor();
        im::End();

        im::Begin("Environment", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
        im::SetWindowPos({ 0, 0 });
        im::SetWindowSize({camera.viewport.x / 10, camera.viewport.y + 20});

        if (im::CollapsingHeader("New")) {
            if (im::Selectable("3D Shape")) {
                Shape_t _t;
                _t.name = string("Shape ") + str(leftshapenum);
                _t.sh = XsShape();
                shapes.push_back(_t);
                leftshapenum++;
                Log << "Create a 3D Shape";
            };
            if (im::Selectable("Vertices  ")) {
                Vertices_t _t;
                _t.name = string("Vertices ") + str(leftvertnum);
                vertices.push_back(_t);
                leftvertnum++;
                Log << "Create a Vertices";
            };
        };
        if (im::CollapsingHeader("Shapes")) {
            for (size_t i = 0; i < shapes.size(); i++)
                if (im::Selectable(string(str(i == s_shape ? "+ " : "- ") + shapes[i].name).c_str(), i == s_shape ? true : false)) {
                    if (i != s_shape) {
                        s_shape = i;
                        Log << "Select a 3D Shape";
                    }
                    else {
                        s_shape = -1;
                        Log << "Un-Select 3D Shape";
                    };
                    s_vert = -1;
                };
        }
        if (im::CollapsingHeader("Vertices")) {
            for (size_t i = 0; i < vertices.size(); i++)
                if (im::Selectable(string(str(i == s_vert ? "+ " : "- ") + vertices[i].name).c_str(), i == s_vert ? true : false)) {
                    if (i != s_vert)
                        s_vert = i;
                    else
                        s_vert = -1;
                    s_shape = -1;
                };
        }
        im::End();
        if (s_shape > -1) {
            im::Begin(shapes[s_shape].name.c_str(), (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
            im::SetWindowPos({ camera.viewport.x - ImGui::GetWindowSize().x, 0 });
            im::SetWindowSize({ camera.viewport.x / 5.f, camera.viewport.y + 20 });
            im::InputText("Name", &shapes[s_shape].name);
            XsInfo(shapes[s_shape].sh);
            char** _tsv = &vert_name[0];
            im::Combo("Vertices", &shapes[s_shape].s_vert, _tsv, vert_name.size());
            if (shapes[s_shape].s_vert > 1) {
                im::Combo("Xs Mode", &shapes[s_shape].xs_vert, xs_vert_types, 4);
                im::Combo("GL Mode", &shapes[s_shape].gl_vert, gl_vert_types, 5);
            }
            elif (shapes[s_shape].s_vert == 1) {
                im::Combo("Solid Type", &shapes[s_shape].s_solid, solid_types, 10);
                im::Combo("Xs Mode", &shapes[s_shape].xs_vert, xs_vert_types, 4);
            };
            auto t_nthm = &im::GetStyle();
            auto _thm = im::GetStyle();
            t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.726);
            t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.886);
            t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.986);
            if (im::Button("Delete")) {
                if (XsIsKeyPressed(XS_KEY_SHIFT)) {
                    shapes.erase(shapes.begin() + s_shape);
                    s_shape = -1;
                }
                else
                    s_del = true;
            }
            *t_nthm = _thm;
            im::End();
            
            if (s_del) {
                s_vert = -1;
                im::Begin(WindowName, (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
                im::SetWindowPos({ camera.viewport.x / 2 - (ImGui::GetWindowSize().x / 2), camera.viewport.y / 2 - (ImGui::GetWindowSize().y / 2) });
                im::SetWindowSize({ 350, 105 });
                im::Text("A shape will be deleted, do you confirm?");
                im::Text(" ");
                im::Text(" ");
                auto t_nthm = &im::GetStyle();
                auto _thm = im::GetStyle();
                t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 0.726);
                t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 0.886);
                t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 0.986);
                if (im::Button("Nop   "))
                    s_del = false;

                t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.726);
                t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.886);
                t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.986);
                im::SameLine(ImGui::GetWindowSize().x - 50, -100);
                if (im::Button("Yep    ")) {
                    shapes.erase(shapes.begin() + s_shape);
                    s_del = false;
                    s_shape = -1;
                };
                *t_nthm = _thm;
                im::End();
            };
        }
        elif(s_vert > -1) {
            im::Begin(vertices[s_vert].name.c_str(), (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
            im::SetWindowPos({ camera.viewport.x / 2 - (ImGui::GetWindowSize().x / 2), camera.viewport.y / 2 - (ImGui::GetWindowSize().y / 2)});
            im::SetWindowSize({ 250, 100 });
            im::InputText("Filename", &input_text);
            im::Combo("Xs Mode", &c_file_format, xs_vert_types, 4);
            if (im::Button("Load!")) {
                if (string(input_text.end() - 3, input_text.end()) == "obj" or string(input_text.end() - 3, input_text.end()) == "OBJ" or string(input_text.end() - 3, input_text.end()) == "Obj")
                    vertices[s_vert].vr = XsOBJLoader(input_text.c_str(), f_XsEnum(c_file_format));
                elif (string(input_text.end() - 8, input_text.end()) == "xs.model")
                    vertices[s_vert].vr = XsModelLoader(input_text.c_str());
            };
            im::End();
        }

        im::Begin("Log", (bool*)0, ImGuiWindowFlags_NoMove);
        im::SetWindowPos({ camera.viewport.x / 10, camera.viewport.y - (ImGui::GetWindowSize().y) + 20 });
        im::SetWindowSize({ s_shape != -1 ? camera.viewport.x - camera.viewport.x / 10 - camera.viewport.x / 5 : camera.viewport.x - camera.viewport.x / 10, (ImGui::GetWindowSize().y > camera.viewport.y / 1.01) ? float(camera.viewport.y / 1.01) : float(ImGui::GetWindowSize().y) });
        for (auto& i : Log.data) {
            im::PushStyleColor(ImGuiCol_Text, ImVec4(i.color.x, i.color.y, i.color.z, 1));
            im::Text(i.text_cstr());
            im::PopStyleColor();
        };
        im::End();

        //im::Begin("fdsfvdsagfa", (bool*)0, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);
        //
        //im::End();
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
public:
    XsCamera camera;
    sf::RenderWindow window;
    sf::Event event;
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
        glewInit();
        glEnable(GL_SCISSOR_TEST);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
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
    
        ImVec4 im_pink =    ximColor(XsHexToRGB(0xd94e6a));
        ImVec4 im_pink2 =   ximColor(XsHexToRGB(0xc23e64));
        ImVec4 im_blue =    ximColor(XsHexToRGB(0x4a7a96));
        ImVec4 im_blue2 =   ximColor(XsHexToRGB(0x333f58));
        ImVec4 im_black =   ximColor(XsHexToRGB(0x292831));
        ImVec4 im_purple =  ximColor(XsHexToRGB(0x1f1935));
        ImVec4 im_dred =    ximColor(XsHexToRGB(0x49111c));
        ImVec4 im_dred2 =   ximColor(XsHexToRGB(0x6c1d2d));
        ImVec4 im_purple2 = ximColor(XsHexToRGB(0x5e2baf));
        ImVec4 im_purple3 = ximColor(XsHexToRGB(0x734ed9));
        {
            ImGuiStyle* style = &im::GetStyle();
            style->Colors[ImGuiCol_TitleBg] = im_black;
            style->Colors[ImGuiCol_TitleBgActive] = im_black;
            style->Colors[ImGuiCol_TitleBgCollapsed] = im_black;
            style->Colors[ImGuiCol_Button] = im_dred;
            style->Colors[ImGuiCol_ButtonActive] = im_dred2;
            style->Colors[ImGuiCol_ButtonHovered] = im_dred2;
            style->Colors[ImGuiCol_FrameBg] = im_purple;
            style->Colors[ImGuiCol_FrameBgActive] = im_purple3;
            style->Colors[ImGuiCol_FrameBgHovered] = im_purple2;
            style->Colors[ImGuiCol_SliderGrab] = im_purple3;
            style->Colors[ImGuiCol_SliderGrabActive] = im_purple2;
            style->Colors[ImGuiCol_Header] = im_purple;
            style->Colors[ImGuiCol_HeaderActive] = im_purple3;
            style->Colors[ImGuiCol_HeaderHovered] = im_purple2;
            style->Colors[ImGuiCol_CheckMark] = ImVec4(0.82f, 0.42f, 0.48f, 1.00f);
            style->Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.91f, 0.52f, 0.64f, 0.78f);
            style->Colors[ImGuiCol_SeparatorActive] = ImVec4(0.67f, 0.64f, 0.81f, 1.00f);
            style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.02f, 0.04f, 0.20f);
            style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.41f, 0.41f, 0.41f, 0.67f);
            style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.35f, 0.35f, 0.35f, 0.95f);
            style->Colors[ImGuiCol_Tab] = ImVec4(0.28f, 0.17f, 0.44f, 0.86f);
            style->Colors[ImGuiCol_TabHovered] = ImVec4(0.28f, 0.16f, 0.71f, 0.80f);
            style->Colors[ImGuiCol_TabActive] = ImVec4(0.10f, 0.06f, 0.24f, 1.00f);
            style->Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.30f, 0.26f, 0.39f, 1.00f);
            style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.64f, 0.78f, 0.94f, 0.35f);
            style->Colors[ImGuiCol_NavHighlight] = ImVec4(0.69f, 0.79f, 0.90f, 1.00f);
            style->Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 0.98f);
            style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 0.91f);
            style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.56f);
            style->Colors[ImGuiCol_TitleBg] = ImVec4(0.16f, 0.16f, 0.19f, 0.94f);
            style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.16f, 0.19f, 0.96f);
            style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.16f, 0.16f, 0.19f, 0.98f);
            style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.64f, 0.78f, 0.94f, 0.35f);
            style->Colors[ImGuiCol_NavHighlight] = ImVec4(0.69f, 0.79f, 0.90f, 1.00f);
        }
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

    void operator<<(XsShape& v) {
        Shape_t _t;
        _t.name = string("Shape ") + str(leftshapenum);
        _t.sh = v;
        shapes.push_back(_t);
        leftshapenum++;
        Log << "Add a 3D Shape";
    };
    void operator<<(XsVertices& v) {
        Vertices_t _t;
        _t.name = string("Vertices ") + str(leftvertnum);
        _t.vr = v;
        vert_name.push_back(_strdup(_t.name.c_str()));
        vertices.push_back(_t);
        leftvertnum++;
        Log << "Add a Vertices";
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
            glClearColor(0.05f, 0.05f, 0.075f, 0.f);
            glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
            for (auto& i : pushs)
                if (i.code == "after clear" or i.code == "before process") {
                    i.push_data();
                    break;
                };
            window.pollEvent(event);
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) {
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
                if (i.s_vert > 1) {
                    glL();
                    i.sh.draw(vertices[i.s_vert - 2].vr, f_XsEnum(i.xs_vert), f_GLenum(i.gl_vert));
                }
                elif(i.s_vert == 1) {
                    glL();
                    i.sh.draw(f_SolidType(i.s_solid), f_XsEnum(i.xs_vert));
                }
            };

            for (auto& i : pushs)
                if (i.code == "after draw") {
                    i.push_data();
                    break;
                };
            ImGui::SFML::Update(window, imclock.restart());

            if (game_mode)
                ui();

            for (auto& i : pushs)
                if (i.code == "in imgui") {
                    i.push_data();
                    break;
                };

            window.pushGLStates();
            ImGui::SFML::Render(window);
            window.popGLStates();
            window.display();
            fps = (float)1e9 / (float)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - s_fps).count();
        };
    };
};



