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

    v2f cam_rot = 300;
    v2f cam_vel = 0;
    v2f last_mouse_pos = 0, plast_mouse_pos = 0;
    bool mouse_press = false;
    v2f m_sayac = 0;

    vex3f speed = 0;
    vex2f mouse_pos = 0;

    void camera_sett() {
        camera.viewport = vex2f(window.getSize().x, window.getSize().y);
        if (game_mode) {
            if (XsIsKeyPressed(XS_MOUSE_RIGHT)) {
                if (XsIsKeyPressed(XS_KEY_W) && !XsIsKeyPressed(XS_KEY_SPACE))
                    speed += camera.rot * 0.01f;
                else if (XsIsKeyPressed(XS_KEY_S) && !XsIsKeyPressed(XS_KEY_SPACE))
                    speed -= camera.rot * 0.01f;
                if (mouse_press == false) {
                    last_mouse_pos = mouse_pos;
                    mouse_press = true;
                }
                v2f f_pos = mouse_pos - last_mouse_pos;
                v2f sm_pos = cam_rot + f_pos;
                cam_vel = (sm_pos - cam_rot) / 17.5;
                last_mouse_pos += cam_vel;
            }
            else {
                mouse_press = false;
            }
            if (!XsIsKeyPressed(XS_KEY_S) && !XsIsKeyPressed(XS_KEY_W))
                speed *= 0.95;
            if (XsIsKeyPressed(XS_KEY_SPACE))
                speed *= 0.75f;
            camera.pos += speed;
            cam_vel *= 0.88;
            cam_rot += cam_vel;
        };
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
    vector<char*> vert_name = {_strdup("none")};

    const const char* xs_vert_types[4]{ "vertex", "vertex and texture", "vertex and normal", "all" };
    const const char* gl_vert_types[5]{ "points", "lines", "triangles", "quads", "polygon" };
    
    string input_text;
    const const char* file_format[3]{ "default", "obj", "xs.model" };
    int c_file_format = 0;

    void ui() {
        im::Begin("Environment", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
        im::SetWindowPos({ 0, 0 });
        im::SetWindowSize({camera.viewport.x / 10, camera.viewport.y + 20});
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
            im::Begin(shapes[s_shape].name.c_str(), (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
            im::SetWindowPos({ camera.viewport.x - ImGui::GetWindowSize().x, 0 });
            im::SetWindowSize({ camera.viewport.x / 5.f, camera.viewport.y + 20 });
            im::InputText("Name", &shapes[s_shape].name);
            XsInfo(shapes[s_shape].sh);
            char** _tsv = &vert_name[0];
            im::Combo("Vertices", &shapes[s_shape].s_vert, _tsv, vert_name.size());
            if (shapes[s_shape].s_vert != 0) {
                im::Combo("Xs Mode", &shapes[s_shape].xs_vert, xs_vert_types, 4);
                im::Combo("GL Mode", &shapes[s_shape].gl_vert, gl_vert_types, 5);
            };

            im::End();
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

        im::Begin("Log", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
        im::SetWindowPos({ camera.viewport.x / 10, camera.viewport.y - (ImGui::GetWindowSize().y) + 20 });
        im::SetWindowSize({ s_shape != -1 ? camera.viewport.x - camera.viewport.x / 10 - camera.viewport.x / 5 : camera.viewport.x - camera.viewport.x / 10, ImGui::GetWindowSize().y });
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

    const char* WindowName = "";
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
        Log << "Add Vertices";
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
                if (i.s_vert != 0) {
                    glL();
                    i.sh.draw(vertices[i.s_vert - 1].vr, f_XsEnum(i.xs_vert), f_GLenum(i.gl_vert));
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
        };
    };
};



