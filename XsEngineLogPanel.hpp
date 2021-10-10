void XsLib::logpanel() {
    bool item_hovered = false;
    std::string item_path;
    ImGui::Begin("Logdsf", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoBringToFrontOnFocus);
    ImGui::SetWindowPos({ Camera.viewport.x / left_panel_size.x, Camera.viewport.y - (ImGui::GetWindowSize().y) });
    ImGui::SetWindowSize({ r_panel ? (Camera.viewport.x - Camera.viewport.x / left_panel_size.x - Camera.viewport.x / right_panel_size.x) : (Camera.viewport.x - Camera.viewport.x / left_panel_size.x), (ImGui::GetWindowSize().y > Camera.viewport.y / 1.01) ? float(Camera.viewport.y / 1.01) : float(ImGui::GetWindowSize().y) });
    log_y = ImGui::GetWindowSize().y;
    ImGui::BeginMenuBar();
    if (ImGui::MenuItem("Log"))
        selected_a = "log";
    if (ImGui::MenuItem("File"))
        selected_a = "file";
    ImGui::EndMenuBar();
    if (selected_a == "log")
        for (auto& i : Log.data) {
            if (them == 0) {
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(i.color.x, i.color.y, i.color.z, 1));
                ImGui::Text(i.text_cstr());
                ImGui::PopStyleColor();
            }
            else {
                ImGui::PushStyleColor(ImGuiCol_Text, i.color == 1.f ? ImVec4(0, 0, 0, 1) : ImVec4(i.color.x, i.color.y, i.color.z, 1));
                ImGui::Text(i.text_cstr());
                ImGui::PopStyleColor();
            };
        }
    elif(selected_a == "file") {
        int j = 0;
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 1.00f);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 0.70f);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 0.60f);
        if (ImGui::ImageButton(updir_icon, { 28, 20 })) {
            path = path.substr(0, path.find_last_of("/\\"));
            dir_iterator.clear();
            for (const auto& i : std::filesystem::directory_iterator(path))
                dir_iterator.push_back(Dir_t(i.path().string(), i.is_directory()));
        }
        ImGui::SameLine(48, -50);
        ImGui::ImageButton(folder_icon, { 20, 20 });
        ImGui::SameLine(80, -100);
        ImGui::InputText("Path", &path);
        for (const auto& i : dir_iterator) {
            if (i.is_directory) {
                t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 1.00f);
                t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 0.70f);
                t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 0.60f);
                ImGui::ImageButton(folder_icon, { 93, 90 });
                if (ImGui::IsItemHovered()) {
                    if (ImGui::IsMouseDoubleClicked(0)) {
                        path = i.path;
                        dir_iterator.clear();
                        for (const auto& i : std::filesystem::directory_iterator(path))
                            dir_iterator.push_back(Dir_t(i.path().string(), i.is_directory()));
                    }
                    else {
                        item_hovered = true;
                        item_path = i.path;
                    }
                }
            }
            else {
                if (i.path == preview_path)
                    t_nthm->Colors[ImGuiCol_Button] = ImVec4(0.45f, 0.31f, 0.85f, 1.00f);
                else
                    t_nthm->Colors[ImGuiCol_Button] = ImVec4(0.12f, 0.10f, 0.21f, 1.00f);
                t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(0.45f, 0.31f, 0.85f, 1.00f);
                t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.37f, 0.17f, 0.69f, 1.00f);
                ImGui::ImageButton(i.path.ends_with(".png") ? imagefile_icon : (i.path.ends_with(".obj") or i.path.ends_with(".xs.model")) ? model_icon : textfile_icon, { 93, 90 });
                if (ImGui::IsItemClicked()) {
                    is_drop = true;
                    drop_path = i.path;
                    if (i.path.ends_with(".png")) {
                        if (i.path != preview_path) {
                            preview_path = i.path;
                            preview_tex.loadFromFile(preview_path.c_str());
                            preview_filename = std::filesystem::path(i.path).filename().string();
                            im_preview = true;
                            preview_tm.restart();
                        }
                        else {
                            preview_path.clear();
                            im_preview = false;
                        };
                    }
                };
                if (ImGui::IsItemHovered()) {
                    if (ImGui::IsMouseDoubleClicked(0)) {
                        open_with_notepad(i.path.c_str());
                    };
                    item_hovered = true;
                    item_path = i.path;
                }
            }
            j++;
            if ((50 * j + (5 * (j + 1))) > ImGui::GetWindowSize().x - (50 * (j + 1) + (5 * ((j + 1) + 1))))
                j = 0;
            if (j != 0)
                ImGui::SameLine(50 * j + (5 * (j + 1)) + 3, 50 * j);
        }
        *t_nthm = _thm;
    };
    ImGui::End();

    if (im_preview) {
        if (preview_tm.getMilliSeconds() > 2) {
            ImGui::Begin(preview_filename.c_str(), (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
            vex2f _t = vex2f(preview_tex.getSize().x, preview_tex.getSize().y);
            _t.normalize();
            ImGui::SetWindowSize({ 350.f, 350.f * _t.y + 50 });
            ImGui::SetWindowPos({ r_panel ? (Camera.viewport.x - ImGui::GetWindowSize().x - (Camera.viewport.x / right_panel_size.x)) : (Camera.viewport.x - ImGui::GetWindowSize().x), Camera.viewport.y - ImGui::GetWindowSize().y - log_y });
            ImGui::Image(preview_tex, sf::Vector2f(ImGui::GetWindowSize().x, (ImGui::GetWindowSize().x) * _t.y));
            ImGui::End();
        };
    };

    if (item_hovered == true and is_drop == false) {
        ImGui::Begin("hoveredsdfa", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoTitleBar);
        ImGui::SetWindowPos({ ImGui::GetIO().MousePos.x + 15, ImGui::GetIO().MousePos.y + 15 });
        ImGui::SetWindowSize({ 200, 200 });
        ImGui::Text(std::filesystem::path(item_path).filename().string().c_str());
        ImGui::End();
    };

    if (!XsIsKeyPressed(XS_MOUSE_LEFT)) {
        if (ImGui::GetIO().MousePos.x > Camera.viewport.x / left_panel_size.x and ImGui::GetIO().MousePos.y < Camera.viewport.y - log_y and (ImGui::GetIO().MousePos.y < (r_panel ? (Camera.viewport.x - (Camera.viewport.x / right_panel_size.x)) : (Camera.viewport.x))))
            if (drop_path != "") {
                if (drop_path.ends_with(".png")) {
                    Texture_t _t;
                    _t.name = std::string("Texture ") + std::to_string(lefttexnum);
                    _t.tx->load(drop_path.c_str());
                    tex_name.push_back(_strdup(_t.name.c_str()));
                    textures.push_back(_t);
                    lefttexnum++;
                    nw_tt.name = std::string("Texture ") + std::to_string(lefttexnum);
                    Log << "Add a Texture";
                    input_text = drop_path;
                }
                elif(drop_path.ends_with(".obj")) {
                    Vertices_t _t;
                    _t.name = std::string("Vertices ") + std::to_string(leftvertnum);
                    *_t.vr = XsOBJLoader(drop_path.c_str(), XS_VERTEX);
                    vert_name.push_back(_strdup(_t.name.c_str()));
                    vertices.push_back(_t);
                    leftvertnum++;
                    nw_vt.name = std::string("Vertices ") + std::to_string(leftvertnum);
                    Log << "Add a Vertices";
                    input_text = drop_path;
                }
                elif(drop_path.ends_with(".xs.model")) {
                    Vertices_t _t;
                    _t.name = std::string("Vertices ") + std::to_string(leftvertnum);
                    *_t.vr = XsModelLoader(drop_path.c_str());
                    vert_name.push_back(_strdup(_t.name.c_str()));
                    vertices.push_back(_t);
                    leftvertnum++;
                    nw_vt.name = std::string("Vertices ") + std::to_string(leftvertnum);
                    Log << "Add a Vertices";
                    input_text = drop_path;
                };
            };
        is_drop = false;
        drop_path.clear();
    }
    else {
        if (is_drop) {
            im_preview = false;
            ImGui::Begin("gfhgfgfg", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoTitleBar);
            ImGui::SetWindowPos({ ImGui::GetIO().MousePos.x + 15, ImGui::GetIO().MousePos.y + 15 });
            ImGui::SetWindowSize({ 200, 200 });
            ImGui::Text(std::string("+" + std::filesystem::path(drop_path).filename().string()).c_str());
            ImGui::End();
        }
    };
}
