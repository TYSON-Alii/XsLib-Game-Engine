void XsLib::ui() {
    im::Begin("general settings", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoTitleBar);
    im::SetWindowPos({ camera.viewport.x / 10, -5 });
    im::SetWindowSize({ 300, 200 });
    im::Text(WindowName);
    if (show_cam_info) {
        im::Text(string(string("pos x: ") + to_string(int(camera.pos.x)) + " y: " + to_string(int(camera.pos.y)) + " z: " + to_string(int(camera.pos.z))).c_str());
        im::Text(string(string("rot x: ") + to_string(camera.rot.x) + " y: " + to_string(camera.rot.y) + " z: " + to_string(camera.rot.z)).c_str());
    };
    if (show_cam_speed)
        im::Text(string(string("camera speed: ") + str(speed_x)).c_str());
    im::PushStyleColor(ImGuiCol_Text, ImVec4(XsYellow.x, XsYellow.y, XsYellow.z, 0.76));
    im::Text(string(string("fps: ") + to_string(int(fps))).c_str());
    im::PopStyleColor();
    im::End();

    im::Begin("Environment", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    im::SetWindowPos({ 0, 0 });
    im::SetWindowSize({ camera.viewport.x / 10, camera.viewport.y });

    if (im::Selectable("New")) {
        selected.type = "new";
        ImGuiFileDialog::Instance()->Close();
        selected.num = -1;
    };
    if (im::CollapsingHeader("Shapes")) {
        for (size_t i = 0; i < shapes.size(); i++)
            if (im::Selectable(string(str((i == selected_r.num and selected_r.type == "shape") ? "+ " : "- ") + shapes[i].name).c_str(), (i == selected_r.num and selected_r.type == "shape") ? true : false)) {
                if (i != selected_r.num) {
                    selected_r.type = "shape";
                    selected_r.num = i;
                    ImGuiFileDialog::Instance()->Close();
                    Log << "Select a 3D Shape";
                }
                else {
                    selected_r.type = "none";
                    selected_r.num = -1;
                    Log << "Un-Select 3D Shape";
                };
            };
    }
    if (im::CollapsingHeader("Vertices")) {
        for (size_t i = 0; i < vertices.size(); i++)
            if (im::Selectable(string(str((i == selected.num and selected.type == "vert") ? "+ " : "- ") + vertices[i].name).c_str(), (i == selected.num and selected.type == "vert") ? true : false)) {
                if (i != selected.num) {
                    selected.type = "vert";
                    ImGuiFileDialog::Instance()->Close();
                    selected.num = i;
                }
                else {
                    selected.type = "none";
                    selected.num = -1;
                }
            };
    }
    if (im::CollapsingHeader("Textures")) {
        for (size_t i = 0; i < textures.size(); i++)
            if (im::Selectable(string(str((i == selected.num and selected.type == "tex") ? "+ " : "- ") + textures[i].name).c_str(), (i == selected.num and selected.type == "tex") ? true : false)) {
                if (i != selected.num) {
                    selected.type = "tex";
                    ImGuiFileDialog::Instance()->Close();
                    selected.num = i;
                }
                else {
                    selected.type = "none";
                    selected.num = -1;
                }
            };
    }
    if (im::CollapsingHeader("Colls")) {
        for (size_t i = 0; i < colls.size(); i++)
            if (im::Selectable(string(str((i == selected.num and selected.type == "coll") ? "+ " : "- ") + textures[i].name).c_str(), (i == selected.num and selected.type == "coll") ? true : false)) {
                if (i != selected.num) {
                    selected.type = "coll";
                    ImGuiFileDialog::Instance()->Close();
                    selected.num = i;
                }
                else {
                    selected.type = "none";
                    selected.num = -1;
                }
            };
    }
    if (im::CollapsingHeader("Effects")) {
        for (size_t i = 0; i < effects.size(); i++)
            if (im::Selectable(string(str((i == selected.num and selected.type == "eff") ? "+ " : "- ") + textures[i].name).c_str(), (i == selected.num and selected.type == "eff") ? true : false)) {
                if (i != selected.num) {
                    selected.type = "eff";
                    ImGuiFileDialog::Instance()->Close();
                    selected.num = i;
                }
                else {
                    selected.type = "none";
                    selected.num = -1;
                }
            };
    }
    im::End();
    if (selected.type == "delete") {
        im::Begin(WindowName, (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        im::SetWindowPos({ camera.viewport.x / 2 - (ImGui::GetWindowSize().x / 2), camera.viewport.y / 2 - (ImGui::GetWindowSize().y / 2) });
        im::SetWindowSize({ 350, 130 });
        im::Text("A shape will be deleted, do you confirm?");
        im::Text(" ");
        im::Text(" ");
        auto t_nthm = &im::GetStyle();
        auto _thm = im::GetStyle();
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 0.986);
        if (im::Button("Nop   "))
            selected.type = "none";
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.986);
        im::SameLine(ImGui::GetWindowSize().x - 50, -100);
        if (im::Button("Yep    ")) {
            shape_name.erase(shape_name.begin() + selected_r.num + 1);
            shapes.erase(shapes.begin() + selected_r.num);
            selected_r.type = "none";
            selected.type = "none";
        };
        *t_nthm = _thm;
        im::End();
    };
    if (selected_r.type == "shape") {
        im::Begin(shapes[selected_r.num].name.c_str(), (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
        im::SetWindowPos({ camera.viewport.x - ImGui::GetWindowSize().x, 0 });
        im::SetWindowSize({ camera.viewport.x / 5.f, camera.viewport.y });
        im::InputText("Name", &shapes[selected_r.num].name);
        XsInfo(*shapes[selected_r.num].sh);
        char** _tsv = &vert_name[0];
        im::Combo("Vertices", &shapes[selected_r.num].s_vert, _tsv, vert_name.size());
        if (shapes[selected_r.num].s_vert > 1) {
            im::Combo("Xs Mode", &shapes[selected_r.num].xs_vert, xs_vert_types, 4);
            im::Combo("GL Mode", &shapes[selected_r.num].gl_vert, gl_vert_types, 5);
        }
        elif(shapes[selected_r.num].s_vert == 1) {
            im::Combo("Solid Type", &shapes[selected_r.num].s_solid, solid_types, 10);
            im::Combo("Xs Mode", &shapes[selected_r.num].xs_vert, xs_vert_types, 4);
        };
        _tsv = &tex_name[0];
        im::Combo("Texture", &shapes[selected_r.num].s_texture, _tsv, tex_name.size());
        if (shapes[selected_r.num].s_texture > 0)
            XsInfo(textures[shapes[selected_r.num].s_texture - 1].tx);
        _tsv = &tex_name[0];
        im::Combo("Collission", &shapes[selected_r.num].s_coll, _tsv, coll_name.size());
        if (shapes[selected_r.num].s_coll > 0) {
            XsInfo(colls[shapes[selected_r.num].s_coll - 1].cl);
            if (im::Button("Show", {im::GetWindowSize().x - 20, 0}))
                shapes[selected_r.num].show_coll = !shapes[selected_r.num].show_coll;
        };
        auto t_nthm = &im::GetStyle();
        auto _thm = im::GetStyle();
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.986);
        if (im::Button("Delete")) {
            if (XsIsKeyPressed(XS_KEY_SHIFT)) {
                shapes.erase(shapes.begin() + selected_r.num - 1);
                shape_name.erase(shape_name.begin() + selected_r.num);
                selected_r.type = "none";
                selected_r.num = -1;
            }
            else
                selected.type = "delete";
        }
        *t_nthm = _thm;
        im::End();
    }
    if (selected.type == "vert") {
        im::Begin(vertices[selected.num].name.c_str(), (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        im::SetWindowPos({ camera.viewport.x / 2 - (ImGui::GetWindowSize().x / 2), camera.viewport.y / 2 - (ImGui::GetWindowSize().y / 2) });
        im::SetWindowSize({ 250, 150 });
        im::InputText("Filename", &input_text);
        if (ImGui::Button("Open File Browser", { 230, 0 })) {
            ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".obj,.xs.model", ".");
        };
        im::Combo("Xs Mode", &vert_load_format, xs_vert_types, 4);
        if (im::Button("Load!")) {
            if (string(input_text.end() - 3, input_text.end()) == "obj" or string(input_text.end() - 3, input_text.end()) == "OBJ" or string(input_text.end() - 3, input_text.end()) == "Obj")
                vertices[selected.num].vr = XsOBJLoader(input_text.c_str(), f_XsEnum(vert_load_format));
            elif(string(input_text.end() - 8, input_text.end()) == "xs.model")
                vertices[selected.num].vr = XsModelLoader(input_text.c_str());
        };
        auto t_nthm = &im::GetStyle();
        auto _thm = im::GetStyle();
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.986);
        im::SameLine(ImGui::GetWindowSize().x - 60, -100);
        if (im::Button("Delete")) {
            for (auto& i : shapes) {
                if (i.s_vert == selected.num + 2)
                    i.s_vert = 0;
            }
            vertices.erase(vertices.begin() + selected.num);
            vert_name.erase(vert_name.begin() + selected.num + 2);
            selected.type = "none";
            selected.num = -1;
        };
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 0.986);
        im::SameLine(ImGui::GetWindowSize().x - 110, -100);
        if (im::Button("Close  ")) {
            selected.type = "none";
            selected.num = -1;
        }
        *t_nthm = _thm;
        im::End();
        if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                input_text = ImGuiFileDialog::Instance()->GetFilePathName();
            }
            ImGuiFileDialog::Instance()->Close();
            if (XsIsKeyPressed(XS_KEY_ESC))
                ImGuiFileDialog::Instance()->Close();
        }
    }
    elif(selected.type == "tex") {
        im::Begin(textures[selected.num].name.c_str(), (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        im::SetWindowPos({ camera.viewport.x / 2 - (ImGui::GetWindowSize().x / 2), camera.viewport.y / 2 - (ImGui::GetWindowSize().y / 2) });
        if (textures[selected.num].tx.isLoad()) {
            im::SetWindowSize({ 250, 510 });
            XsInfo(textures[selected.num].tx);
        }
        else
            im::SetWindowSize({ 250, 210 });
        im::InputText("Filename", &input_text);
        if (ImGui::Button("Open File Browser", { 230, 0 })) {
            ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKeyt", "Choose File", ".png", ".");
        };
        im::Combo("Filter", &lt_f, p_filter_types, 2);
        im::Combo("Wrapping", &lt_w, p_wrap_types, 4);
        im::Combo("Format", &lt_t, p_format_types, 3);
        if (im::Button("Load.")) {
            textures[selected.num].tx = XsTextureSTB(input_text.c_str(), lt_t == 0 ? GL_RGB : lt_t == 1 ? GL_RGBA : GL_SRGB, lt_f == 0 ? GL_NEAREST : GL_LINEAR, lt_w == 0 ? GL_REPEAT : lt_w == 1 ? GL_MIRRORED_REPEAT : lt_w == 2 ? GL_CLAMP_TO_EDGE : GL_CLAMP_TO_BORDER);
        };
        auto t_nthm = &im::GetStyle();
        auto _thm = im::GetStyle();
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.986);
        im::SameLine(ImGui::GetWindowSize().x - 60, -100);
        if (im::Button("Delete")) {
            for (auto& i : shapes)
                if (i.s_texture == selected.num + 1) {
                    i.s_texture = 0;
                    break;
                };
            textures.erase(textures.begin() + selected.num);
            tex_name.erase(tex_name.begin() + selected.num + 1);
            selected.type = "none";
            selected.num = -1;
        };
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 0.986);
        im::SameLine(ImGui::GetWindowSize().x - 110, -100);
        if (im::Button("Close  ")) {
            selected.type = "none";
            selected.num = -1;
        }
        *t_nthm = _thm;
        im::End();
        if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKeyt"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                input_text = ImGuiFileDialog::Instance()->GetFilePathName();
            }
            ImGuiFileDialog::Instance()->Close();
            if (XsIsKeyPressed(XS_KEY_ESC))
                ImGuiFileDialog::Instance()->Close();
        };
        //if (ImGuiFileDialog::Instance()->IsOpened()) {
        //    first_preview_file = ImGuiFileDialog::Instance()->GetFilePathName();
        //    preview_loaded = first_preview_file == last_preview_file;
        //    if (tex_preview_timer.getMilliSeconds() > 2) {
        //        if (!preview_loaded and first_preview_file.find(".") != std::string::npos) {
        //            last_preview_file = ImGuiFileDialog::Instance()->GetFilePathName();
        //            preview_tex.loadFromFile(last_preview_file.c_str());
        //            tex_preview_timer.restart();
        //        }
        //        else {
        //            if (im::GetIO().WantCaptureMouse) {
        //                im::Begin("Image Preview", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration);
        //                im::SetWindowPos({ im::GetIO().MousePos.x + 15, im::GetIO().MousePos.y + 15 });
        //                v2f _t = v2f(float(preview_tex.getSize().x), float(preview_tex.getSize().y));
        //                _t.normalize();
        //                im::SetWindowSize({ _t.x * 350, _t.y * 350 });
        //                im::Image(preview_tex, { _t.x * 350, _t.y * 350 });
        //                im::End();
        //            };
        //        };
        //    };
        //};
    }
    elif(selected.type == "coll") {
        im::Begin(textures[selected.num].name.c_str(), (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        im::SetWindowPos({ camera.viewport.x / 2 - (ImGui::GetWindowSize().x / 2), camera.viewport.y / 2 - (ImGui::GetWindowSize().y / 2) });
        im::SetWindowSize({ 250, 210 });
        XsInfo(colls[selected.num].cl);
        auto t_nthm = &im::GetStyle();
        auto _thm = im::GetStyle();
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.986);
        if (im::Button("Delete")) {
            for (auto& i : shapes)
                if (i.s_coll == selected.num + 1) {
                    i.s_coll = 0;
                    break;
                };
            colls.erase(colls.begin() + selected.num);
            coll_name.erase(coll_name.begin() + selected.num + 1);
            selected.type = "none";
            selected.num = -1;
        };
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 0.986);
        im::SameLine(ImGui::GetWindowSize().x - 60, -100);
        if (im::Button("Close  ")) {
            selected.type = "none";
            selected.num = -1;
        }
        *t_nthm = _thm;
        im::End();
    }

    im::Begin("Log", (bool*)0, ImGuiWindowFlags_NoMove);
    im::SetWindowPos({ camera.viewport.x / 10, camera.viewport.y - (ImGui::GetWindowSize().y) + 20 });
    im::SetWindowSize({ selected_r.type == "shape" ? (camera.viewport.x - camera.viewport.x / 10 - camera.viewport.x / 5) : (camera.viewport.x - camera.viewport.x / 10), (ImGui::GetWindowSize().y > camera.viewport.y / 1.01) ? float(camera.viewport.y / 1.01) : float(ImGui::GetWindowSize().y) });
    for (auto& i : Log.data) {
        if (them == 0) {
            im::PushStyleColor(ImGuiCol_Text, ImVec4(i.color.x, i.color.y, i.color.z, 1));
            im::Text(i.text_cstr());
            im::PopStyleColor();
        }
        else {
            im::PushStyleColor(ImGuiCol_Text, i.color == 1.f ? ImVec4(0, 0, 0, 1) : ImVec4(i.color.x, i.color.y, i.color.z, 1));
            im::Text(i.text_cstr());
            im::PopStyleColor();
        };
    };
    im::End();

    if (selected.type == "new") {
        im::Begin("New ", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        im::SetWindowPos({ camera.viewport.x / 2 - (ImGui::GetWindowSize().x / 2), camera.viewport.y / 2 - (ImGui::GetWindowSize().y / 2) });
        im::SetWindowSize({ 250, 140 });
        if (im::Button("3D Shape  ")) {
            if (XsIsKeyPressed(XS_KEY_SHIFT)) {
                Shape_t _t;
                _t.sh = new XsShape();
                _t.name = string("Shape ") + str(leftshapenum);
                shape_name.push_back(_strdup(_t.name.c_str()));
                shapes.push_back(_t);
                Log << "Create a 3D Shape";
                leftshapenum++;
                nw_st.name = string("Shape ") + str(leftshapenum);
            }
            else
                selected.type = "new shape";
        };
        if (im::Button("Vertices  ")) {
            if (XsIsKeyPressed(XS_KEY_SHIFT)) {
                Vertices_t _t;
                _t.name = string("Vertices ") + str(leftvertnum);
                vert_name.push_back(_strdup(_t.name.c_str()));
                vertices.push_back(_t);
                leftvertnum++;
                nw_st.name = string("Vertices ") + str(leftvertnum);
                Log << "Create a Vertices";
            }
            else
                selected.type = "new vert";
        };
        if (im::Button("Texture  ")) {
            selected.type = "new tex";
        };
        if (im::Button("Collission  ")) {
            selected.type = "new coll";
        };
        if (im::Button("Effect  ")) {
            selected.type = "new eff";
        };
        auto t_nthm = &im::GetStyle();
        auto _thm = im::GetStyle();
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.986);
        if (im::Button("Cancel"))
            selected.type = "none";
        *t_nthm = _thm;
        im::End();
    };
    if (selected.type == "new shape") {
        im::Begin("New 3D Shape", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        im::SetWindowPos({ camera.viewport.x / 2 - (ImGui::GetWindowSize().x / 2), camera.viewport.y / 2 - (ImGui::GetWindowSize().y / 2) });
        im::SetWindowSize({ 250, 130 });
        im::InputText("Name", &nw_st.name);
        char** _tsv = &shape_name[0];
        im::Combo("Copy From", &s_ns, _tsv, shape_name.size());
        if (im::Button("Create")) {
            const char* temp_copy_name = nw_st.name.c_str();
            nw_st = (s_ns == 0) ? nw_st : shapes[s_ns - 1];
            nw_st.name = temp_copy_name;
            shape_name.push_back(_strdup(nw_st.name.c_str()));
            shapes.push_back(nw_st);
            Log << "Create a 3D Shape";
            selected.type = "none";
        };
        auto t_nthm = &im::GetStyle();
        auto _thm = im::GetStyle();
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.986);
        if (im::Button("Cancel"))
            selected.type = "none";
        *t_nthm = _thm;
        im::End();
    }
    elif(selected.type == "new vert") {
        im::Begin("New Vertices", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        im::SetWindowPos({ camera.viewport.x / 2 - (ImGui::GetWindowSize().x / 2), camera.viewport.y / 2 - (ImGui::GetWindowSize().y / 2) });
        im::SetWindowSize({ 250, 130 });
        im::InputText("Name", &nw_vt.name);
        char** _tsv = new char* [vert_name.size() - 1];
        _tsv[0] = _strdup("none");
        for (size_t i = 2; i < vert_name.size(); i++)
            _tsv[i - 1] = vert_name[i];
        im::Combo("Copy From", &s_nv, _tsv, vert_name.size() - 1);
        if (im::Button("Create")) {
            Vertices_t _t;
            _t = (s_nv == 0) ? _t : vertices[s_nv - 1];
            _t.name = nw_vt.name;
            vert_name.push_back(_strdup(_t.name.c_str()));
            vertices.push_back(_t);
            Log << "Create a Vertices";
            selected.type = "none";
        }
        auto t_nthm = &im::GetStyle();
        auto _thm = im::GetStyle();
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.986);
        if (im::Button("Cancel"))
            selected.type = "none";
        *t_nthm = _thm;
        im::End();
    }
    elif(selected.type == "new tex") {
        im::Begin("New Texture", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        im::SetWindowPos({ camera.viewport.x / 2 - (ImGui::GetWindowSize().x / 2), camera.viewport.y / 2 - (ImGui::GetWindowSize().y / 2) });
        im::SetWindowSize({ 250, 130 });
        im::InputText("Name", &nw_tt.name);
        char** _tsv = &tex_name[0];
        im::Combo("Copy From", &s_nt, _tsv, tex_name.size());
        if (im::Button("Create")) {
            Texture_t _t;
            _t = s_nt == 0 ? _t : textures[s_nt - 1];
            _t.name = nw_tt.name;
            tex_name.push_back(_strdup(_t.name.c_str()));
            textures.push_back(_t);
            Log << "Create a Texture";
            selected.type = "none";
        }
        auto t_nthm = &im::GetStyle();
        auto _thm = im::GetStyle();
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.986);
        if (im::Button("Cancel"))
            selected.type = "none";
        *t_nthm = _thm;
        im::End();
    }
    elif(selected.type == "new coll") {
        Coll_t _t;
        _t.name = "Collission";
        coll_name.push_back(_strdup(_t.name.c_str()));
        colls.push_back(_t);
        Log << "Create a Collission";
        selected.type = "none";
    }
    elif(selected.type == "new eff") {
        Effect_t _t;
        _t.name = "Effect";
        effect_name.push_back(_strdup(_t.name.c_str()));
        effects.push_back(_t);
        Log << "Create a Effect";
        selected.type = "none";
    };
}

void XsLib::otherui() {
    im::Begin("dsafbdjagvfa", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoTitleBar);
    im::SetWindowPos({ camera.viewport.x - ((selected_r.type == "shape") ? (camera.viewport.x / 5.f) : 0.f) - 55, -5});
    im::SetWindowSize({ 100, 100 });
    if (im::Button("Tools")) {
        if (selected.type == "tools")
            selected.type = "none";
        else
            selected.type = "tools";
    };
    im::End();

    bool _sthem = false;
    if (selected.type == "tools") {
        im::Begin("Tools ", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        im::SetWindowPos({ camera.viewport.x / 2 - (ImGui::GetWindowSize().x / 2), camera.viewport.y / 2 - (ImGui::GetWindowSize().y / 2) });
        im::SetWindowSize({ 250, 300 });
        if (im::Button("Calculator", { 230, 0 })) {
            selected.type = "calculator";
        };
        if (im::Button("Notepad", { 230, 0 })) {
            selected.type = "notepad";
        };
        if (im::Button("Them", { 230, 0 }))
            _sthem = true;
        auto t_nthm = &im::GetStyle();
        auto _thm = im::GetStyle();
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.986);
        if (im::Button("Cancel", { 230, 0 })) {
            selected.type = "none";
        };
        *t_nthm = _thm;
        im::End();
    };
    if (selected.type == "notepad") {
        im::Begin("Notepad  ", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        im::SetWindowPos({ camera.viewport.x / 2 - (ImGui::GetWindowSize().x / 2), camera.viewport.y / 2 - (ImGui::GetWindowSize().y / 2) });
        im::SetWindowSize({ 300, 180 });
        im::InputTextMultiline("Notepad  ", &_notepad);
        im::End();
    };
    if (_sthem) {
        setThem(them == 0 ? 1 : 0);
        _sthem = false;
    };
};
