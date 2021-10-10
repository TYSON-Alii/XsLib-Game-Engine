void XsLib::operator<<(XsShape& v) {
    Shape_t _t(*this);
    _t.name = std::string("Shape ") + str(leftshapenum);
    _t._shape = &v;
    shapes.push_back(_t);
    shape_name.push_back(_strdup(_t.name.c_str()));
    leftshapenum++;
    nw_st.name = std::string("Shape ") + std::to_string(leftshapenum);
    Log << "Add a 3D Shape";
};
void XsLib::operator<<(XsVertices& v) {
    Vertices_t _t;
    _t.name = std::string("Vertices ") + std::to_string(leftvertnum);
    _t.vr = &v;
    vert_name.push_back(_strdup(_t.name.c_str()));
    vertices.push_back(_t);
    leftvertnum++;
    nw_vt.name = std::string("Vertices ") + std::to_string(leftvertnum);
    Log << "Add a Vertices";
};
void XsLib::operator<<(XsTextureSTB& v) {
    Texture_t _t;
    _t.name = std::string("Texture ") + std::to_string(lefttexnum);
    _t.tx = &v;
    tex_name.push_back(_strdup(_t.name.c_str()));
    textures.push_back(_t);
    lefttexnum++;
    nw_tt.name = std::string("Texture ") + std::to_string(lefttexnum);
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
void XsLib::Save(const char* file_name) {
    file = new XsSaver(file_name);
    file->clear();
    file->add(WindowName, "window_name");
    file->add(cam_rot, "cam_rot");
    file->add(speed_x, "speed_x");
    file->add(them, "them");
    file->add(input_text, "input_text");
    file->add(vert_load_format, "vert_load_format");
    file->add(Camera.pos, "cam_pos");
    file->add(Camera.rot, "cam_rot");
    file->add(Camera.viewport, "cam_viewp");
    file->add(Camera.near_, "cam_near");
    file->add(Camera.far_, "cam_far");
    file->add(Camera.fov, "cam_fov");
    loaded_file = file_name;
};
void XsLib::Load(const char* file_name) {
    file = new XsSaver(file_name);
    WindowName = file->getcstr("window_name");
    cam_rot = file->getv2f("cam_rot");
    speed_x = file->getf("speed_x");
    them = file->geti("them");
    input_text = file->getstr("input_text");
    vert_load_format = file->geti("vert_load_format");
    Camera.pos = file->getv3f("cam_pos");
    Camera.rot = file->getv3f("cam_rot");
    Camera.viewport = file->getv2f("cam_viewp");
    Camera.near_ = file->getf("cam_near");
    Camera.far_ = file->getf("cam_far");
    Camera.fov = file->getf("cam_fov");
    loaded_file = file_name;
};
void XsLib::Create(const char* window_name) {
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
    ImGuiFileDialog::Instance()->SetExtentionInfos(".xs.model", ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.9), "XS");
};
void XsLib::setThem(int v) {
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
        colors[ImGuiCol_Text] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
        colors[ImGuiCol_TextDisabled] = ImVec4(0.40f, 0.39f, 0.38f, 0.77f);
        colors[ImGuiCol_WindowBg] = ImVec4(0.92f, 0.91f, 0.88f, 0.70f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.92f, 0.91f, 0.88f, 0.92f);
        colors[ImGuiCol_Border] = ImVec4(0.84f, 0.83f, 0.80f, 0.65f);
        colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
        colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 0.98f, 0.95f, 1.00f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.99f, 1.00f, 0.40f, 0.78f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 1.00f, 0.00f, 1.00f);
        colors[ImGuiCol_TitleBg] = ImVec4(1.00f, 0.98f, 0.95f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
        colors[ImGuiCol_MenuBarBg] = ImVec4(1.00f, 0.98f, 0.95f, 0.47f);
        colors[ImGuiCol_ScrollbarBg] = ImVec4(1.00f, 0.98f, 0.95f, 1.00f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.00f, 0.00f, 0.00f, 0.21f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.90f, 0.91f, 0.00f, 0.78f);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
        colors[ImGuiCol_CheckMark] = ImVec4(0.25f, 1.00f, 0.00f, 0.80f);
        colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 0.00f, 0.00f, 0.14f);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
        colors[ImGuiCol_Button] = ImVec4(0.00f, 0.00f, 0.00f, 0.14f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.99f, 1.00f, 0.22f, 0.86f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
        colors[ImGuiCol_Header] = ImVec4(0.25f, 1.00f, 0.00f, 0.76f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 1.00f, 0.00f, 0.86f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
        colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.04f);
        colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.25f, 1.00f, 0.00f, 0.78f);
        colors[ImGuiCol_ResizeGripActive] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
        colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
        colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
        colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
        them = 1;
    };
};
void XsLib::xsui() {
    //    p_sett.screenSize = camera.viewport;
    //    p_sett.begin();
    //    glLoadIdentity();
    //    glColor3f(XsRed);
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
void XsLib::camera_sett() {
    Camera.viewport = vex2f(Window.getSize().x, Window.getSize().y);
    if (game_mode) {
        if (XsIsKeyPressed(XS_MOUSE_RIGHT)) {
            if (Event.type == sf::Event::MouseWheelMoved) {
                speed_x += (float)Event.mouseWheel.delta * 10;
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
                speed += Camera.rot * (1.f / speed_x);
            else if (XsIsKeyPressed(XS_KEY_S) && !XsIsKeyPressed(XS_KEY_SPACE))
                speed -= Camera.rot * (1.f / speed_x);
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
        Camera.pos += speed;
        cam_vel *= 0.88;
        cam_rot += cam_vel;
    }
    XsFPSCamera(Camera, cam_rot - vex2f(0, 300), 0.3);
};
void XsLib::drawfloor(XsShader& v) {
    glDepthFunc(GL_ALWAYS);
    glDepthMask(GL_FALSE);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
    glLoadIdentity();
    v.use();
    v("projection", Camera.projectionMatrix());
    v("view", Camera.viewMatrix);
    if (them == 1)
        v("color", bgColorDark);
    else if (them == 0)
        v("color", bgColorLight);
    v("cam_y", Camera.pos.y);
    if (3 > fabs(Camera.pos.y))
        glLineWidth(4.1 - fabs(Camera.pos.y));
    else
        glLineWidth(1);
    glTranslatef(ceil(Camera.pos.x / 2) * 2, 0, ceil(Camera.pos.z / 2) * 2);
    glBegin(GL_LINES);
    rep(m_ldis.x * m_fdis.z, 2.f)
        if ((ceil(Camera.pos.z / 2) * 2) + m_fdis.z - i != 0)
            drawline(m_fdis.x, 0, m_fdis.z - i, -m_fdis.x, 0, m_fdis.z - i);
    glEnd();

    glBegin(GL_LINES);
    rep(m_ldis.z * m_fdis.x, 2.f)
        if ((ceil(Camera.pos.x / 2) * 2) + m_fdis.x - i != 0)
            drawline(m_fdis.x - i, 0, m_fdis.z, m_fdis.x - i, 0, -m_fdis.z);
    glEnd();

    glLoadIdentity();
    if (4 > fabs(Camera.pos.y))
        glLineWidth(5.1 - fabs(Camera.pos.y));
    else
        glLineWidth(2);
    v("color", blue);
    glBegin(GL_LINES);
    drawline(0, 0, m_fdis.z + Camera.pos.z, 0, 0, -m_fdis.z + Camera.pos.z);
    glEnd();
    v("color", red);
    glBegin(GL_LINES);
    drawline(m_fdis.x + Camera.pos.x, 0, 0, -m_fdis.x + Camera.pos.x, 0, 0);
    glEnd();
    v("color", green);
    glBegin(GL_LINES);
    drawline(0, m_fdis.y + Camera.pos.y, 0, 0, -m_fdis.y + Camera.pos.y, 0);
    glEnd();

    v.disuse();
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
};
