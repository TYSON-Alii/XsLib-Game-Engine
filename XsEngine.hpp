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
    v3f m_fdis = 110;
    v3f m_ldis = 2;
    v3f blue = v3f(34.f / 255.f, 207.f / 255.f, 230.f / 255.f);
    v3f red = v3f(238.f / 255.f, 23.f / 255.f, 23.f / 255.f);
    v3f green = v3f(XsDarkGreen);
    v3f white = v3f(0.8f, 0.8f, 0.8f);
    std::string floor_shader_vs = "\
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
        glEnable(GL_LINE_SMOOTH);
        glL();
        v.use();
        v("projection", camera.projectionMatrix());
        v("view", camera.viewMatrix);
        v("color", white);
        v("cam_y", camera.pos.y);
        if (3 > fabs(camera.pos.y))
            glLineWidth(3.1 - fabs(camera.pos.y));
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
            glLineWidth(4.1 - fabs(camera.pos.y));
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
        XsFPSCamera(camera, cam_rot - vex2f(0, 300), 0.3);
    };

    XsPopUpSett popup_sett;
    bool b_shape = false;
    int s_shape = -1;
    sf::Clock imclock; 

    void ui() {
        im::Begin("Envirament");
        im::SetWindowPos({ 0,0 });
        im::SetWindowSize({camera.viewport.x / 10, camera.viewport.y});
        if (b_shape) {
            im::Selectable("> Shapes", &b_shape);
        }
        else
            im::Selectable("Shapes", &b_shape);
        im::End();
        if (s_shape > -1) {
        };
    };
    vector<push_t> pushs;
public:
    XsCamera camera;
    sf::RenderWindow window;
    sf::Event event;
    XsLib(const char* window_name) {
        srand(time(NULL));
        sf::ContextSettings csett;
        csett.depthBits = 24;
        csett.stencilBits = 8;
        csett.antialiasingLevel = 0;
        csett.majorVersion = 3;
        csett.minorVersion = 3;
        csett.sRgbCapable = false;
        window.create(sf::VideoMode(WIDTH, HEIGHT), window_name, sf::Style::Default, csett);
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
    vector<XsLib::push_t> Pushs() { return pushs; };
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
    void Push(void (*push_v)(void), const char* code = "normal") { pushs.push_back(push_t(push_v, code)); };

    void operator<<(auto& v) {
        //Shape_t _t;
        //if (string(typeid(v).name()) == "class XsShape") {
        //    _t.name = string("Shape ") + str(leftshapenum);
        //    _t.type = "XsShape";
        //    _t.ptr = &v;
        //    shapes.push_back(_t);
        //    leftshapenum++;
        //}
        //else if (typeid(v).name() == "class XsShape2d") {
        //    _t.name = string("Shape2d ") + str(leftshapenum);
        //    _t.type = "XsShape2d";
        //    _t.ptr = &v;
        //    shapes.push_back(_t);
        //    leftshapenum++;
        //}
        //else
        //    XsLog(XsLogRed, XsLogWhite, "Wrong Shape Type..\n");
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
            for (auto& i : pushs)
                if (i.code == "after camera" or i.code == "normal" or i.code == "before draw") {
                    i.push_data();
                    break;
                };

            drawfloor(floor_shader);

            for (auto& i : pushs)
                if (i.code == "after draw") {
                    i.push_data();
                    break;
                };
            ImGui::SFML::Update(window, imclock.restart());

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



