void XsLib::ui() {
    ImGui::Begin("general settings", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoTitleBar);
    ImGui::SetWindowPos({ Camera.viewport.x / left_panel_size.x, -5 });
    ImGui::SetWindowSize({ 300, 200 });
    ImGui::Text(WindowName);
    if (show_cam_info) {
        ImGui::Text(std::string(std::string("pos x: ") + std::to_string(int(Camera.pos.x)) + " y: " + std::to_string(int(Camera.pos.y)) + " z: " + std::to_string(int(Camera.pos.z))).c_str());
        ImGui::Text(std::string(std::string("rot x: ") + std::to_string(Camera.rot.x) + " y: " + std::to_string(Camera.rot.y) + " z: " + std::to_string(Camera.rot.z)).c_str());
    };
    if (show_cam_speed)
        ImGui::Text(std::string(std::string("camera speed: ") + str(speed_x)).c_str());
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(XsYellow.x, XsYellow.y, XsYellow.z, 0.76));
    ImGui::Text(std::string(std::string("fps: ") + std::to_string(int(fps))).c_str());
    ImGui::PopStyleColor();
    ImGui::End();

    ImGui::Begin(WindowName, (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoBringToFrontOnFocus);
    t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 1.00f);
    t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 0.70f);
    t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 0.60f);
    ImGui::BeginMenuBar();
    if (ImGui::MenuItem("Environment"))
        l_panel_menu = 0;
    if (ImGui::MenuItem("File"))
        l_panel_menu = 1;
    ImGui::EndMenuBar();
    ImGui::SetWindowPos({ 0, 0 });
    *t_nthm = _thm;
    ImGui::SetWindowSize({ Camera.viewport.x / left_panel_size.x, Camera.viewport.y });
    if (l_panel_menu == 0) {
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(0.12f, 0.10f, 0.21f, 1.00f);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(0.45f, 0.31f, 0.85f, 1.00f);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.37f, 0.17f, 0.69f, 1.00f);
        if (ImGui::Button("New", { Camera.viewport.x / left_panel_size.x - 15, 0 })) {
            selected.type = "new";
            ImGuiFileDialog::Instance()->Close();
            selected.num = -1;
        };
        *t_nthm = _thm;
        if (selected_r.type == "none")
            r_panel = false;
        else
            r_panel = true;
        if (ImGui::Selectable("Settings", &Sett))
            selected_r.type = (selected_r.type == "sett") ? "none" : "sett";
        if (shapes.size() > 0) {
            if (ImGui::TreeNode("Shapes")) {
                for (size_t i = 0; i < shapes.size(); i++) {
                    (i != selected_r.num) ? ImGui::SetNextTreeNodeOpen(i == selected_r.num) : void();
                    if (selected_r.type == "sett") ImGui::SetNextTreeNodeOpen(false);
                    if (ImGui::TreeNode(shapes[i].name.c_str()/*, (i == selected_r.num and selected_r.type == "shape") ? true : false)*/)) {
                        selected_r.type = "shape";
                        Sett = false;
                        if (i != selected_r.num) {
                            selected_r.num = i;
                            ImGuiFileDialog::Instance()->Close();
                            Log << "Select a 3D Shape";
                        }
                        if (shapes[i]._selected_vert > 1)
                            if (ImGui::Selectable(std::string(std::string((selected.num == shapes[i]._selected_vert - 2 and selected.type == "vert") ? "+ " : "- ") + vertices[shapes[i]._selected_vert - 2].name).c_str())) {
                                if (selected.type == "vert" and selected.num == shapes[i]._selected_vert - 2) {
                                    selected.type = "none";
                                    selected.num = 0;
                                }
                                else {
                                    selected.type = "vert";
                                    selected.num = shapes[i]._selected_vert - 2;
                                }
                            };
                        if (shapes[i]._selected_tex > 0)
                            if (ImGui::Selectable(std::string(std::string((selected.num == shapes[i]._selected_tex - 1 and selected.type == "tex") ? "+ " : "- ") + textures[shapes[i]._selected_tex - 1].name).c_str())) {
                                if (selected.type == "tex" and selected.num == shapes[i]._selected_tex - 1) {
                                    selected.type = "none";
                                    selected.num = 0;
                                }
                                else {
                                    selected.type = "tex";
                                    selected.num = shapes[i]._selected_tex - 1;
                                }
                            };
                        if (shapes[i]._selected_coll > 0)
                            if (ImGui::Selectable(std::string(std::string((selected.num == shapes[i]._selected_coll - 1 and selected.type == "coll") ? "+ " : "- ") + colls[shapes[i]._selected_coll - 1].name).c_str())) {
                                if (selected.type == "coll" and selected.num == shapes[i]._selected_coll - 1) {
                                    selected.type = "none";
                                    selected.num = 0;
                                }
                                else {
                                    selected.type = "coll";
                                    selected.num = shapes[i]._selected_coll - 1;
                                }
                            };
                        ImGui::TreePop();
                    }
                }
                ImGui::TreePop();
            }
        }
        if (ImGui::TreeNode("Environments")) {
            if (vertices.size() > 0) {
                if (ImGui::TreeNode("Vertices")) {
                    for (size_t i = 0; i < vertices.size(); i++)
                        if (ImGui::Selectable(std::string(str((i == selected.num and selected.type == "vert") ? "+ " : "- ") + vertices[i].name).c_str(), (i == selected.num and selected.type == "vert") ? true : false)) {
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
                    ImGui::TreePop();
                }
            }
            if (textures.size() > 0) {
                if (ImGui::TreeNode("Textures")) {
                    for (size_t i = 0; i < textures.size(); i++)
                        if (ImGui::Selectable(std::string(str((i == selected.num and selected.type == "tex") ? "+ " : "- ") + textures[i].name).c_str(), (i == selected.num and selected.type == "tex") ? true : false)) {
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
                    ImGui::TreePop();
                }
            }
            if (colls.size() > 0) {
                if (ImGui::TreeNode("Colls")) {
                    for (size_t i = 0; i < colls.size(); i++)
                        if (ImGui::Selectable(std::string(str((i == selected.num and selected.type == "coll") ? "+ " : "- ") + colls[i].name).c_str(), (i == selected.num and selected.type == "coll") ? true : false)) {
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
                    ImGui::TreePop();
                }
            }
            if (shaders.size() > 0) {
                if (ImGui::TreeNode("Shaders")) {
                    for (size_t i = 0; i < shaders.size(); i++)
                        if (ImGui::Selectable(std::string(str((i == selected.num and selected.type == "shader") ? "+ " : "- ") + shaders[i].name).c_str(), (i == selected.num and selected.type == "shader") ? true : false)) {
                            if (i != selected.num) {
                                selected.type = "shader";
                                ImGuiFileDialog::Instance()->Close();
                                selected.num = i;
                            }
                            else {
                                selected.type = "none";
                                selected.num = -1;
                            }
                        };
                    ImGui::TreePop();
                }
            }
            ImGui::TreePop();
        };
    }
    elif(l_panel_menu == 1) {
        ImGui::InputText("File Name", &loaded_file);
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(0.12f, 0.10f, 0.21f, 0.60f);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(0.45f, 0.31f, 0.85f, 0.60f);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.37f, 0.17f, 0.69f, 0.60f);
        if (ImGui::Button("Open File Diolog  ", { ImGui::GetWindowSize().x - 15, 0 }))
            ImGuiFileDialog::Instance()->OpenDialog("SaveFile", "Choose File", ".save,.xs.save", ".");
        *t_nthm = _thm;
        if (ImGui::Button("Save", { ImGui::GetWindowSize().x - 15, 0 }))
            if (loaded_file != "")
                Save(loaded_file.c_str());
            else
                ImGuiFileDialog::Instance()->OpenDialog("SaveFile", "Choose File", ".save,.xs.save", ".");
        if (ImGui::Button("Load File", { ImGui::GetWindowSize().x - 15, 0 }))
            ImGuiFileDialog::Instance()->OpenDialog("LoadFile", "Choose File", ".save,.xs.save", ".");
        if (ImGuiFileDialog::Instance()->Display("SaveFile"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                loaded_file = ImGuiFileDialog::Instance()->GetFilePathName();
                Save(loaded_file.c_str());
            };
            ImGuiFileDialog::Instance()->Close();
            if (XsIsKeyPressed(XS_KEY_ESC))
                ImGuiFileDialog::Instance()->Close();
        }
        if (ImGuiFileDialog::Instance()->Display("LoadFile"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                loaded_file = ImGuiFileDialog::Instance()->GetFilePathName();
                Load(loaded_file.c_str());
            };
            ImGuiFileDialog::Instance()->Close();
            if (XsIsKeyPressed(XS_KEY_ESC))
                ImGuiFileDialog::Instance()->Close();
        }
    };
    ImGui::End();
    if (selected.type == "delete") {
        ImGui::Begin(std::string(std::string(WindowName) + "    ").c_str(), (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        ImGui::SetWindowPos({ Camera.viewport.x / 2 - (ImGui::GetWindowSize().x / 2), Camera.viewport.y / 2 - (ImGui::GetWindowSize().y / 2) });
        ImGui::SetWindowSize({ 350, 130 });
        ImGui::Text("A shape will be deleted, do you confirm?");
        ImGui::Text(" ");
        ImGui::Text(" ");
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 0.986);
        if (ImGui::Button("Nop   "))
            selected.type = "none";
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.986);
        ImGui::SameLine(ImGui::GetWindowSize().x - 50, -100);
        if (ImGui::Button("Yep    ")) {
            shape_name.erase(shape_name.begin() + selected_r.num + 1);
            shapes.erase(shapes.begin() + selected_r.num);
            selected_r.type = "none";
            selected.type = "none";
        };
        *t_nthm = _thm;
        ImGui::End();
    };
    if (selected_r.type == "shape") {
        ImGui::Begin(shapes[selected_r.num].name.c_str(), (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
        ImGui::SetWindowPos({ Camera.viewport.x - ImGui::GetWindowSize().x, 0 });
        ImGui::SetWindowSize({ Camera.viewport.x / right_panel_size.x, Camera.viewport.y });
        ImGui::InputText("Name", &shapes[selected_r.num].name);
        XsInfo(shapes[selected_r.num].Shape());
        if (vertices.size() > 0) {
            _tsv = &vert_name[0];
            ImGui::Combo("Vertices", &shapes[selected_r.num]._selected_vert, _tsv, vert_name.size());
            if (shapes[selected_r.num]._selected_vert > 1) {
                ImGui::Combo("Xs Mode", &shapes[selected_r.num]._xs_vert, xs_vert_types, 4);
                ImGui::Combo("GL Mode", &shapes[selected_r.num]._gl_vert, gl_vert_types, 5);
            }
            elif(shapes[selected_r.num]._selected_vert == 1) {
                ImGui::Combo("Solid Type", &shapes[selected_r.num]._selected_solid, solid_types, 10);
                ImGui::Combo("Xs Mode", &shapes[selected_r.num]._xs_vert, xs_vert_types, 4);
            };
            if (shapes[selected_r.num]._gl_vert == 0 and shapes[selected_r.num]._selected_vert > 1)
                ImGui::DragFloat("Point Size", &shapes[selected_r.num].pointScale(), 0.01f, 0.01f, 10);
            elif(shapes[selected_r.num]._gl_vert == 1 and shapes[selected_r.num]._selected_vert > 1)
                ImGui::DragFloat("Line Width", &shapes[selected_r.num].lineWidth(), 0.01f, 0.01f, 10);
        };
        if (textures.size() > 0) {
            _tsv = &tex_name[0];
            ImGui::Combo("Texture", &shapes[selected_r.num]._selected_tex, _tsv, tex_name.size());
            if (shapes[selected_r.num]._selected_tex > 0)
                XsInfo(*textures[shapes[selected_r.num]._selected_tex - 1].tx);
        };
        if (ImGui::CollapsingHeader("Advanced")) {
            if (colls.size() > 0) {
                _tsv = &coll_name[0];
                ImGui::Combo("Collission", &shapes[selected_r.num]._selected_coll, _tsv, coll_name.size());
                if (shapes[selected_r.num]._selected_coll > 0) {
                    ImGui::Checkbox("Lock Shape", &shapes[selected_r.num].isLockColl());
                    ImGui::Checkbox("Show", &shapes[selected_r.num].isShowColl());
                    ImGui::DragFloat3("position ", colls[shapes[selected_r.num]._selected_coll - 1].cl.pos, 0.01f, -FLT_MAX, FLT_MAX);
                    ImGui::DragFloat3("scale ", colls[shapes[selected_r.num]._selected_coll - 1].cl.scale, 0.01f, -FLT_MAX, FLT_MAX);
                    //if (ImGui::Button((shapes[selected_r.num].lock_coll_to_shape == false) ? "Lock" : "Un-Lock", { ImGui::GetWindowSize().x - 20, 0 }))
                    //    shapes[selected_r.num].lock_coll_to_shape = !shapes[selected_r.num].lock_coll_to_shape;
                    //if (ImGui::Button("Show", { ImGui::GetWindowSize().x - 20, 0 }))
                    //    shapes[selected_r.num].show_coll = !shapes[selected_r.num].show_coll;
                };
            };
            ImGui::Checkbox("Array", &shapes[selected_r.num].Array.use);
            if (shapes[selected_r.num].Array.use) {
                if (shapes[selected_r.num]._selected_vert > 1)
                    if (ImGui::Button("Export Vertices", { ImGui::GetWindowSize().x - 15, 0 })) {
                        selected.type = "export array";
                        selected.num = shapes[selected_r.num]._selected_vert;
                    };
                ImGui::DragInt("Limit", &shapes[selected_r.num].Array.limit, 1, 0, INT_MAX);
                ImGui::DragFloat3("Pos", shapes[selected_r.num].Array.pos, 0.001f, -FLT_MAX, FLT_MAX);
                ImGui::DragFloat3("Rot", shapes[selected_r.num].Array.rot, 0.001f, -FLT_MAX, FLT_MAX);
                ImGui::DragFloat3("Scale", shapes[selected_r.num].Array.scale, 0.001f, -FLT_MAX, FLT_MAX);
            };
        }
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.986);
        if (ImGui::Button("Delete")) {
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
        ImGui::End();
    }
    elif(selected_r.type == "sett") {
        ImGui::Begin("Settings", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
        ImGui::SetWindowPos({ Camera.viewport.x - ImGui::GetWindowSize().x, 0 });
        ImGui::SetWindowSize({ Camera.viewport.x / right_panel_size.x, Camera.viewport.y });
        ImGui::DragFloat3("Cam Position", Camera.pos, 0.01f, -FLT_MAX, FLT_MAX);
        ImGui::DragFloat2("Cam Rotation", cam_rot, 0.1f, -FLT_MAX, FLT_MAX);
        ImGui::DragFloat("Cam Far Panel", &Camera.far_, 0.01f, -FLT_MAX, FLT_MAX);
        ImGui::Checkbox("Show Floor", &show_floor);
        ImGui::ColorPicker3("Background Color", them == 0 ? bgColorDark : bgColorLight);
        if (ImGui::Button("Reset Background Color", { ImGui::GetWindowSize().x - 15, 0 }))
            if (them == 0)
                bgColorDark = v3f(0.05f, 0.05f, 0.075f);
            else
                bgColorLight = v3f(0.85f, 0.85f, 0.875f);
        ImGui::Checkbox("Use Skybox", &use_skybox);
        if (use_skybox) {
            if (skybox.texture.isLoad())
                XsInfo(skybox.texture);
            skybox.color = them == 0 ? bgColorDark : bgColorLight;
            ImGui::DragFloat2("Sky Rot", sky_rot, 0.1f, -FLT_MAX, FLT_MAX);
            skybox.rotation.x = cos(glm::radians(sky_rot.x)) * cos(glm::radians(sky_rot.y));
            skybox.rotation.y = -sin(glm::radians(sky_rot.y));
            skybox.rotation.z = sin(glm::radians(sky_rot.x)) * cos(glm::radians(sky_rot.y));
            ImGui::InputText("Image Path", &sky_img_path);
            ImGui::Combo("Filter", &sky_fl, p_filter_types, 2);
            ImGui::Combo("Wrapping", &sky_w, p_wrap_types, 4);
            ImGui::Combo("Format", &sky_f, p_format_types, 3);
            if (ImGui::Button("Load"))
                if (sky_img_path != "")
                    skybox.texture = XsTextureSTB(sky_img_path.c_str(), sky_f == 0 ? GL_RGB : sky_f == 1 ? GL_RGBA : GL_SRGB, sky_fl == 0 ? GL_NEAREST : GL_LINEAR, sky_w == 0 ? GL_REPEAT : sky_w == 1 ? GL_MIRRORED_REPEAT : sky_w == 2 ? GL_CLAMP_TO_EDGE : GL_CLAMP_TO_BORDER);
            ImGui::SameLine(50, -50);
            if (ImGui::ImageButton(folder_icon, { 20, 18 }))
                ImGuiFileDialog::Instance()->OpenDialog("SkyImg", "Choose File", ".png", ".");
        };
        ImGui::End();

        if (ImGuiFileDialog::Instance()->Display("SkyImg"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                sky_img_path = ImGuiFileDialog::Instance()->GetFilePathName();
            }
            ImGuiFileDialog::Instance()->Close();
            if (XsIsKeyPressed(XS_KEY_ESC))
                ImGuiFileDialog::Instance()->Close();
        }
    };
    if (selected.type == "vert") {
        ImGui::Begin(vertices[selected.num].name.c_str(), (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        ImGui::SetWindowPos({ Camera.viewport.x / 2 - (ImGui::GetWindowSize().x / 2), Camera.viewport.y / 2 - (ImGui::GetWindowSize().y / 2) });
        ImGui::SetWindowSize({ 250, 150 });
        ImGui::InputText("Filename", &input_text);
        if (ImGui::Button("Open File Browser", { 230, 0 })) {
            ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".obj,.xs.model", ".");
        };
        ImGui::Combo("Xs Mode", &vert_load_format, xs_vert_types, 4);
        if (ImGui::Button("Load!")) {
            if (std::string(input_text.end() - 3, input_text.end()) == "obj" or std::string(input_text.end() - 3, input_text.end()) == "OBJ" or std::string(input_text.end() - 3, input_text.end()) == "Obj")
                *vertices[selected.num].vr = XsOBJLoader(input_text.c_str(), f_XsEnum(vert_load_format));
            elif(std::string(input_text.end() - 8, input_text.end()) == "xs.model")
                *vertices[selected.num].vr = XsModelLoader(input_text.c_str());
        };
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.986);
        ImGui::SameLine(ImGui::GetWindowSize().x - 60, -100);
        if (ImGui::Button("Delete")) {
            for (auto& i : shapes) {
                if (i._selected_vert == selected.num + 2)
                    i._selected_vert = 0;
            }
            vertices.erase(vertices.begin() + selected.num);
            vert_name.erase(vert_name.begin() + selected.num + 2);
            selected.type = "none";
            selected.num = -1;
        };
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 0.986);
        ImGui::SameLine(ImGui::GetWindowSize().x - 110, -100);
        if (ImGui::Button("Close  ")) {
            selected.type = "none";
            selected.num = -1;
        }
        *t_nthm = _thm;
        ImGui::End();
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
        ImGui::Begin(textures[selected.num].name.c_str(), (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        ImGui::SetWindowPos({ Camera.viewport.x / 2 - (ImGui::GetWindowSize().x / 2), Camera.viewport.y / 2 - (ImGui::GetWindowSize().y / 2) });
        if (textures[selected.num].tx->isLoad()) {
            ImGui::SetWindowSize({ 250, 510 });
            XsInfo(*textures[selected.num].tx);
        }
        else
            ImGui::SetWindowSize({ 250, 210 });
        ImGui::InputText("Filename", &input_text);
        if (ImGui::Button("Open File Browser", { 230, 0 })) {
            ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKeyt", "Choose File", ".png", ".");
        };
        ImGui::Combo("Filter", &lt_f, p_filter_types, 2);
        ImGui::Combo("Wrapping", &lt_w, p_wrap_types, 4);
        ImGui::Combo("Format", &lt_t, p_format_types, 3);
        if (ImGui::Button("Load.")) {
            *textures[selected.num].tx = XsTextureSTB(input_text.c_str(), lt_t == 0 ? GL_RGB : lt_t == 1 ? GL_RGBA : GL_SRGB, lt_f == 0 ? GL_NEAREST : GL_LINEAR, lt_w == 0 ? GL_REPEAT : lt_w == 1 ? GL_MIRRORED_REPEAT : lt_w == 2 ? GL_CLAMP_TO_EDGE : GL_CLAMP_TO_BORDER);
        };
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.986);
        ImGui::SameLine(ImGui::GetWindowSize().x - 60, -100);
        if (ImGui::Button("Delete")) {
            for (auto& i : shapes)
                if (i._selected_tex == selected.num + 1) {
                    i._selected_tex = 0;
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
        ImGui::SameLine(ImGui::GetWindowSize().x - 110, -100);
        if (ImGui::Button("Close  ")) {
            selected.type = "none";
            selected.num = -1;
        }
        *t_nthm = _thm;
        ImGui::End();
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
        //        if (!preview_loaded and first_preview_file.find(".") != std::std::string::npos) {
        //            last_preview_file = ImGuiFileDialog::Instance()->GetFilePathName();
        //            preview_tex.loadFromFile(last_preview_file.c_str());
        //            tex_preview_timer.restart();
        //        }
        //        else {
        //            if (ImGui::GetIO().WantCaptureMouse) {
        //                ImGui::Begin("Image Preview", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration);
        //                ImGui::SetWindowPos({ ImGui::GetIO().MousePos.x + 15, ImGui::GetIO().MousePos.y + 15 });
        //                v2f _t = v2f(float(preview_tex.getSize().x), float(preview_tex.getSize().y));
        //                _t.normalize();
        //                ImGui::SetWindowSize({ _t.x * 350, _t.y * 350 });
        //                ImGui::Image(preview_tex, { _t.x * 350, _t.y * 350 });
        //                ImGui::End();
        //            };
        //        };
        //    };
        //};
    }
    elif(selected.type == "coll") {
        ImGui::Begin(colls[selected.num].name.c_str(), (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        ImGui::SetWindowPos({ Camera.viewport.x / 2 - (ImGui::GetWindowSize().x / 2), Camera.viewport.y / 2 - (ImGui::GetWindowSize().y / 2) });
        ImGui::SetWindowSize({ 250, 120 });
        XsInfo(colls[selected.num].cl);
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.986);
        if (ImGui::Button("Delete")) {
            for (auto& i : shapes)
                if (i._selected_coll == selected.num + 1) {
                    i._selected_coll = 0;
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
        ImGui::SameLine(ImGui::GetWindowSize().x - 60, -100);
        if (ImGui::Button("Close  ")) {
            selected.type = "none";
            selected.num = -1;
        }
        *t_nthm = _thm;
        ImGui::End();
    }
    elif(selected.type == "shader") {
        ImGui::Begin(shaders[selected.num].name.c_str(), (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        ImGui::SetWindowPos({ Camera.viewport.x / 2 - (ImGui::GetWindowSize().x / 2), Camera.viewport.y / 2 - (ImGui::GetWindowSize().y / 2) });
        ImGui::SetWindowSize({ 250, 240 });
        ImGui::InputText("File Name vs", &shaders[selected.num].file_name_vs);
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(0.12f, 0.10f, 0.21f, 0.60f);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(0.45f, 0.31f, 0.85f, 0.60f);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.37f, 0.17f, 0.69f, 0.60f);
        if (ImGui::Button("Open File Diolog  ", { 235, 0 }))
            ImGuiFileDialog::Instance()->OpenDialog("VertexShader", "Choose File", ".txt,.vs,.glsl", ".");
        ImGui::InputText("File Name fs", &shaders[selected.num].file_name_fs);
        if (ImGui::Button("Open File Diolog   ", { 235, 0 }))
            ImGuiFileDialog::Instance()->OpenDialog("FragmentShader", "Choose File", ".txt,.fs,.glsl", ".");
        *t_nthm = _thm;
        if (ImGui::Button("Load", { 235, 0 }))
            shaders[selected.num].sd = XsShader(shaders[selected.num].file_name_vs.c_str(), shaders[selected.num].file_name_fs.c_str());
        if (ImGui::Button("Open Files", { 235, 0 })) {
            std::thread vs_notepad(open_with_notepad, shaders[selected.num].file_name_vs.c_str());
            vs_notepad.join();
            std::thread fs_notepad(open_with_notepad, shaders[selected.num].file_name_fs.c_str());
            fs_notepad.join();
        };
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.986);
        if (ImGui::Button("Delete")) {
            //for (auto& i : shapes)
            //    if (i.s_coll == selected.num + 1) {
            //        i.s_coll = 0;
            //        break;
            //    };
            //colls.erase(colls.begin() + selected.num);
            //coll_name.erase(coll_name.begin() + selected.num + 1);
            selected.type = "none";
            selected.num = -1;
        };
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 0.986);
        ImGui::SameLine(ImGui::GetWindowSize().x - 60, -100);
        if (ImGui::Button("Close  ")) {
            selected.type = "none";
            selected.num = -1;
        }
        *t_nthm = _thm;
        ImGui::End();
        if (ImGuiFileDialog::Instance()->Display("VertexShader"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                shaders[selected.num].file_name_vs = ImGuiFileDialog::Instance()->GetFilePathName();
            }
            ImGuiFileDialog::Instance()->Close();
            if (XsIsKeyPressed(XS_KEY_ESC))
                ImGuiFileDialog::Instance()->Close();
        }
        if (ImGuiFileDialog::Instance()->Display("FragmentShader"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                shaders[selected.num].file_name_fs = ImGuiFileDialog::Instance()->GetFilePathName();
            }
            ImGuiFileDialog::Instance()->Close();
            if (XsIsKeyPressed(XS_KEY_ESC))
                ImGuiFileDialog::Instance()->Close();
        }
    }
    elif(selected.type == "export array") {
        ImGui::Begin("Array to Vert", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        ImGui::SetWindowPos({ Camera.viewport.x / 2 - (ImGui::GetWindowSize().x / 2), Camera.viewport.y / 2 - (ImGui::GetWindowSize().y / 2) });
        ImGui::SetWindowSize({ 250, 90 });
        ImGui::InputText("Name", &export_array_name);
        if (ImGui::Button("Create")) {
            const XsShape _sh = shapes[selected_r.num].Shape();
            const XsEnum _xs = f_XsEnum(shapes[selected_r.num]._xs_vert);
            Vertices_t new_vert;
            XsVertices _tv = *vertices[shapes[selected_r.num]._selected_vert - 2].vr;
            new_vert.name = export_array_name;
            for (volatile size_t j = 0; j < shapes[selected_r.num].Array.limit; j++) {
                XsOrigin(_tv, _xs, shapes[selected_r.num].Array.pos + _sh.pos);
                //XsRotate(_tv, _xs, shapes[selected_r.num].arr.rot + _sh.rot);
                XsScale(_tv, _xs, shapes[selected_r.num].Array.scale + _sh.scale);
                XsJoin(*new_vert.vr, _xs, _tv, _xs);
            }
            vertices.push_back(new_vert);
            vert_name.push_back(_strdup(new_vert.name.c_str()));
            selected.type = "none";
            selected.num = -1;
        };
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.986);
        ImGui::SameLine(ImGui::GetWindowSize().x - 60, -100);
        if (ImGui::Button("Cancel")) {
            selected.type = "none";
            selected.num = -1;
        };
        *t_nthm = _thm;
        ImGui::End();
    }
    logpanel();
    if (selected.type == "new") {
        ImGui::Begin("New ", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        ImGui::SetWindowPos({ Camera.viewport.x / 2 - (ImGui::GetWindowSize().x / 2), Camera.viewport.y / 2 - (ImGui::GetWindowSize().y / 2) });
        ImGui::SetWindowSize({ 250, 205 });
        if (ImGui::Button("3D Shape  ", { 235, 0 })) {
            if (XsIsKeyPressed(XS_KEY_SHIFT)) {
                Shape_t _t;
                _t.Shape() = XsShape();
                _t.name = std::string("Shape ") + str(leftshapenum);
                shape_name.push_back(_strdup(_t.name.c_str()));
                shapes.push_back(_t);
                Log << "Create a 3D Shape";
                leftshapenum++;
                nw_st.name = std::string("Shape ") + str(leftshapenum);
            }
            else
                selected.type = "new shape";
        };
        if (ImGui::Button("Vertices  ", { 235, 0 })) {
            if (XsIsKeyPressed(XS_KEY_SHIFT)) {
                Vertices_t _t;
                _t.name = std::string("Vertices ") + str(leftvertnum);
                vert_name.push_back(_strdup(_t.name.c_str()));
                vertices.push_back(_t);
                leftvertnum++;
                nw_st.name = std::string("Vertices ") + str(leftvertnum);
                Log << "Create a Vertices";
                leftvertnum++;
                nw_st.name = std::string("Vertices ") + std::to_string(leftvertnum);
            }
            else
                selected.type = "new vert";
        };
        if (ImGui::Button("Texture  ", { 235, 0 })) {
            selected.type = "new tex";
        };
        if (ImGui::Button("Collission  ", { 235, 0 })) {
            selected.type = "new coll";
        };
        if (ImGui::Button("Shader  ", { 235, 0 })) {
            selected.type = "new shader";
        };
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.986);
        if (ImGui::Button("Cancel"))
            selected.type = "none";
        *t_nthm = _thm;
        ImGui::End();
    };
    if (selected.type == "new shape") {
        ImGui::Begin("New 3D Shape", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        ImGui::SetWindowPos({ Camera.viewport.x / 2 - (ImGui::GetWindowSize().x / 2), Camera.viewport.y / 2 - (ImGui::GetWindowSize().y / 2) });
        ImGui::SetWindowSize({ 250, 160 });
        ImGui::InputText("Name", &nw_st.name);
        _tsv = &shape_name[0];
        ImGui::Combo("Copy From", &s_ns, _tsv, shape_name.size());
        if (ImGui::Button("Create")) {
            const char* temp_copy_name = nw_st.name.c_str();
            if (s_ns != 0)
                nw_st = shapes[s_ns - 1];
            else
                nw_st._shape = new XsShape();
            nw_st.name = temp_copy_name;
            shape_name.push_back(_strdup(nw_st.name.c_str()));
            shapes.push_back(nw_st);
            Log << "Create a 3D Shape";
            selected.type = "none";
            leftshapenum++;
            nw_st.name = std::string("Shape ") + std::to_string(leftshapenum);
        };
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.986);
        if (ImGui::Button("Cancel"))
            selected.type = "none";
        *t_nthm = _thm;
        ImGui::End();
    }
    elif(selected.type == "new vert") {
        ImGui::Begin("New Vertices", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        ImGui::SetWindowPos({ Camera.viewport.x / 2 - (ImGui::GetWindowSize().x / 2), Camera.viewport.y / 2 - (ImGui::GetWindowSize().y / 2) });
        ImGui::SetWindowSize({ 250, 160 });
        ImGui::InputText("Name", &nw_vt.name);
        _tsv = new char* [vert_name.size() - 1];
        _tsv[0] = _strdup("none");
        for (size_t i = 2; i < vert_name.size(); i++)
            _tsv[i - 1] = vert_name[i];
        ImGui::Combo("Copy From", &s_nv, _tsv, vert_name.size() - 1);
        if (ImGui::Button("Create")) {
            Vertices_t _t;
            _t = (s_nv == 0) ? _t : vertices[s_nv - 1];
            _t.name = nw_vt.name;
            vert_name.push_back(_strdup(_t.name.c_str()));
            vertices.push_back(_t);
            Log << "Create a Vertices";
            selected.type = "none";
            leftvertnum++;
            nw_vt.name = std::string("Vertices ") + std::to_string(leftvertnum);
        }
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.986);
        if (ImGui::Button("Cancel"))
            selected.type = "none";
        *t_nthm = _thm;
        ImGui::End();
    }
    elif(selected.type == "new tex") {
        ImGui::Begin("New Texture", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        ImGui::SetWindowPos({ Camera.viewport.x / 2 - (ImGui::GetWindowSize().x / 2), Camera.viewport.y / 2 - (ImGui::GetWindowSize().y / 2) });
        ImGui::SetWindowSize({ 250, 160 });
        ImGui::InputText("Name", &nw_tt.name);
        _tsv = &tex_name[0];
        ImGui::Combo("Copy From", &s_nt, _tsv, tex_name.size());
        if (ImGui::Button("Create")) {
            Texture_t _t;
            _t = s_nt == 0 ? _t : textures[s_nt - 1];
            _t.name = nw_tt.name;
            tex_name.push_back(_strdup(_t.name.c_str()));
            textures.push_back(_t);
            Log << "Create a Texture";
            selected.type = "none";
            lefttexnum++;
            nw_tt.name = std::string("Texture ") + std::to_string(lefttexnum);
        }
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.986);
        if (ImGui::Button("Cancel"))
            selected.type = "none";
        *t_nthm = _thm;
        ImGui::End();
    }
    elif(selected.type == "new coll") {
        ImGui::Begin("New Collission");
        ImGui::SetWindowPos({ Camera.viewport.x / 2 - (ImGui::GetWindowSize().x / 2), Camera.viewport.y / 2 - (ImGui::GetWindowSize().y / 2) });
        ImGui::SetWindowSize({ 250, 160 });
        ImGui::InputText("Name", &nw_ct.name);
        _tsv = &coll_name[0];
        ImGui::Combo("Copy From", &s_nc, _tsv, coll_name.size());
        if (ImGui::Button("Create")) {
            Coll_t _t;
            _t = s_nc == 0 ? _t : colls[s_nc - 1];
            _t.name = nw_ct.name;
            coll_name.push_back(_strdup(_t.name.c_str()));
            colls.push_back(_t);
            Log << "Create a Collission";
            selected.type = "none";
            leftcollnum++;
            nw_ct.name = std::string("Coll ") + std::to_string(leftcollnum);
        };
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.986);
        if (ImGui::Button("Cancel"))
            selected.type = "none";
        *t_nthm = _thm;
        ImGui::End();
    }
    elif(selected.type == "new shader") {
        Shader_t _t;
        _t.name = "Shader";
        shader_name.push_back(_strdup(_t.name.c_str()));
        shaders.push_back(_t);
        Log << "Create a Shader";
        selected.type = "none";
    };
}
