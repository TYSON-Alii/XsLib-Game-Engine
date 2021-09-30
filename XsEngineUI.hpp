void XsLib::ui() {
    im::Begin("general settings", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoTitleBar);
    im::SetWindowPos({ camera.viewport.x / left_panel_size.x, -5 });
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

    im::Begin(WindowName, (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 1.00f);
    t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 0.70f);
    t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsGrey.x, XsGrey.y, XsGrey.z, 0.60f);
    if (im::Button("Environment", { im::GetWindowSize().x / 2, 0 }))
        r_panel_menu = 0;
    im::SameLine(im::GetWindowSize().x / 2 + 10, -50);
    if (im::Button("File", { im::GetWindowSize().x / 2 - 15, 0 }))
        r_panel_menu = 1;
    im::SetWindowPos({ 0, 0 });
    *t_nthm = _thm;
    im::SetWindowSize({ camera.viewport.x / left_panel_size.x, camera.viewport.y });
    if (r_panel_menu == 0) {
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(0.12f, 0.10f, 0.21f, 1.00f);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(0.45f, 0.31f, 0.85f, 1.00f);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.37f, 0.17f, 0.69f, 1.00f);
        if (im::Button("New", { camera.viewport.x / left_panel_size.x - 15, 0 })) {
            selected.type = "new";
            ImGuiFileDialog::Instance()->Close();
            selected.num = -1;
        };
        *t_nthm = _thm;
        if (shapes.size() > 0) {
            if (im::TreeNode("Shapes")) {
                for (size_t i = 0; i < shapes.size(); i++) {
                    i != selected_r.num ? im::SetNextTreeNodeOpen(i == selected_r.num) : void();
                    if (im::TreeNode(shapes[i].name.c_str()/*, (i == selected_r.num and selected_r.type == "shape") ? true : false)*/)) {
                        if (i != selected_r.num) {
                            selected_r.type = "shape";
                            selected_r.num = i;
                            ImGuiFileDialog::Instance()->Close();
                            Log << "Select a 3D Shape";
                        }
                        if (shapes[i].s_vert > 1)
                            if (im::Selectable(string(string((selected.num == shapes[i].s_vert - 2 and selected.type == "vert") ? "+ " : "- ") + vertices[shapes[i].s_vert - 2].name).c_str())) {
                                if (selected.type == "vert" and selected.num == shapes[i].s_vert - 2) {
                                    selected.type = "none";
                                    selected.num = 0;
                                }
                                else {
                                    selected.type = "vert";
                                    selected.num = shapes[i].s_vert - 2;
                                }
                            };
                        if (shapes[i].s_texture > 0)
                            if (im::Selectable(string(string((selected.num == shapes[i].s_texture - 1 and selected.type == "tex") ? "+ " : "- ") + textures[shapes[i].s_texture - 1].name).c_str())) {
                                if (selected.type == "tex" and selected.num == shapes[i].s_texture - 1) {
                                    selected.type = "none";
                                    selected.num = 0;
                                }
                                else {
                                    selected.type = "tex";
                                    selected.num = shapes[i].s_texture - 1;
                                }
                            };
                        if (shapes[i].s_coll > 0)
                            if (im::Selectable(string(string((selected.num == shapes[i].s_coll - 1 and selected.type == "coll") ? "+ " : "- ") + colls[shapes[i].s_coll - 1].name).c_str())) {
                                if (selected.type == "coll" and selected.num == shapes[i].s_coll - 1) {
                                    selected.type = "none";
                                    selected.num = 0;
                                }
                                else {
                                    selected.type = "coll";
                                    selected.num = shapes[i].s_coll - 1;
                                }
                            };
                        im::TreePop();
                    }
                }
                im::TreePop();
            }
        }
        if (im::TreeNode("Environments")) {
            if (vertices.size() > 0) {
                if (im::TreeNode("Vertices")) {
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
                    im::TreePop();
                }
            }
            if (textures.size() > 0) {
                if (im::TreeNode("Textures")) {
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
                    im::TreePop();
                }
            }
            if (colls.size() > 0) {
                if (im::TreeNode("Colls")) {
                    for (size_t i = 0; i < colls.size(); i++)
                        if (im::Selectable(string(str((i == selected.num and selected.type == "coll") ? "+ " : "- ") + colls[i].name).c_str(), (i == selected.num and selected.type == "coll") ? true : false)) {
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
                    im::TreePop();
                }
            }
            if (shaders.size() > 0) {
                if (im::TreeNode("Shaders")) {
                    for (size_t i = 0; i < shaders.size(); i++)
                        if (im::Selectable(string(str((i == selected.num and selected.type == "shader") ? "+ " : "- ") + shaders[i].name).c_str(), (i == selected.num and selected.type == "shader") ? true : false)) {
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
                    im::TreePop();
                }
            }
            im::TreePop();
        };
    }
    elif(r_panel_menu == 1) {
        im::InputText("File Name", &loaded_file);
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(0.12f, 0.10f, 0.21f, 0.60f);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(0.45f, 0.31f, 0.85f, 0.60f);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.37f, 0.17f, 0.69f, 0.60f);
        if (im::Button("Open File Diolog  ", { im::GetWindowSize().x - 15, 0 }))
            ImGuiFileDialog::Instance()->OpenDialog("SaveFile", "Choose File", ".save,.xs.save", ".");
        *t_nthm = _thm;
        if (im::Button("Save", { im::GetWindowSize().x - 15, 0 }))
            if (loaded_file != "")
                save(loaded_file.c_str());
            else
                ImGuiFileDialog::Instance()->OpenDialog("SaveFile", "Choose File", ".save,.xs.save", ".");
        if (im::Button("Load File", { im::GetWindowSize().x - 15, 0 }))
            ImGuiFileDialog::Instance()->OpenDialog("LoadFile", "Choose File", ".save,.xs.save", ".");
        if (ImGuiFileDialog::Instance()->Display("SaveFile"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                loaded_file = ImGuiFileDialog::Instance()->GetFilePathName();
                save(loaded_file.c_str());
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
                load(loaded_file.c_str());
            };
            ImGuiFileDialog::Instance()->Close();
            if (XsIsKeyPressed(XS_KEY_ESC))
                ImGuiFileDialog::Instance()->Close();
        }
    };
    im::End();
    if (selected.type == "delete") {
        im::Begin(WindowName, (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        im::SetWindowPos({ camera.viewport.x / 2 - (ImGui::GetWindowSize().x / 2), camera.viewport.y / 2 - (ImGui::GetWindowSize().y / 2) });
        im::SetWindowSize({ 350, 130 });
        im::Text("A shape will be deleted, do you confirm?");
        im::Text(" ");
        im::Text(" ");
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
        im::SetWindowSize({ camera.viewport.x / right_panel_size.x, camera.viewport.y });
        im::InputText("Name", &shapes[selected_r.num].name);
        XsInfo(*shapes[selected_r.num].sh);
        if (vertices.size() > 0) {
            _tsv = &vert_name[0];
            im::Combo("Vertices", &shapes[selected_r.num].s_vert, _tsv, vert_name.size());
            if (shapes[selected_r.num].s_vert > 1) {
                im::Combo("Xs Mode", &shapes[selected_r.num].xs_vert, xs_vert_types, 4);
                im::Combo("GL Mode", &shapes[selected_r.num].gl_vert, gl_vert_types, 5);
            }
            elif(shapes[selected_r.num].s_vert == 1) {
                im::Combo("Solid Type", &shapes[selected_r.num].s_solid, solid_types, 10);
                im::Combo("Xs Mode", &shapes[selected_r.num].xs_vert, xs_vert_types, 4);
            };
            if (shapes[selected_r.num].gl_vert == 0 and shapes[selected_r.num].s_vert > 1)
                im::DragFloat("Point Size", &shapes[selected_r.num].s_point, 0.01f, 0.01f, 10);
            elif(shapes[selected_r.num].gl_vert == 1 and shapes[selected_r.num].s_vert > 1)
                im::DragFloat("Line Width", &shapes[selected_r.num].w_line, 0.01f, 0.01f, 10);
        };
        if (textures.size() > 0) {
            _tsv = &tex_name[0];
            im::Combo("Texture", &shapes[selected_r.num].s_texture, _tsv, tex_name.size());
            if (shapes[selected_r.num].s_texture > 0)
                XsInfo(textures[shapes[selected_r.num].s_texture - 1].tx);
        };
        if (im::CollapsingHeader("Advanced")) {
            if (colls.size() > 0) {
                _tsv = &coll_name[0];
                im::Combo("Collission", &shapes[selected_r.num].s_coll, _tsv, coll_name.size());
                if (shapes[selected_r.num].s_coll > 0) {
                    ImGui::DragFloat3("position ", colls[shapes[selected_r.num].s_coll - 1].cl.pos, 0.01f, -FLT_MAX, FLT_MAX);
                    ImGui::DragFloat3("scale ", colls[shapes[selected_r.num].s_coll - 1].cl.scale, 0.01f, -FLT_MAX, FLT_MAX);
                    //if (im::Button((shapes[selected_r.num].lock_coll_to_shape == false) ? "Lock" : "Un-Lock", { im::GetWindowSize().x - 20, 0 }))
                    //    shapes[selected_r.num].lock_coll_to_shape = !shapes[selected_r.num].lock_coll_to_shape;
                    //if (im::Button("Show", { im::GetWindowSize().x - 20, 0 }))
                    //    shapes[selected_r.num].show_coll = !shapes[selected_r.num].show_coll;
                    im::Checkbox("Lock Shape", &shapes[selected_r.num].lock_coll_to_shape);
                    im::Checkbox("Show", &shapes[selected_r.num].show_coll);
                };
            };
            im::Checkbox("Array", &shapes[selected_r.num].arr.use);
            if (shapes[selected_r.num].arr.use) {
                im::Checkbox("X", &shapes[selected_r.num].arr.axis.x);
                im::SameLine(50, -50);
                im::Checkbox("Y", &shapes[selected_r.num].arr.axis.y);
                im::SameLine(100, -100);
                im::Checkbox("Z", &shapes[selected_r.num].arr.axis.z);
                if (shapes[selected_r.num].arr.axis.x)
                    im::DragInt("Limit X", &shapes[selected_r.num].arr.limit.x);
                if (shapes[selected_r.num].arr.axis.y)
                    im::DragInt("Limit Y", &shapes[selected_r.num].arr.limit.y);
                if (shapes[selected_r.num].arr.axis.z)
                    im::DragInt("Limit Z", &shapes[selected_r.num].arr.limit.z);
                if (im::TreeNode("X Axis")) {
                    if (shapes[selected_r.num].arr.axis.x) {
                        im::DragFloat3("Pos", shapes[selected_r.num].arr.pos.x, 0.001f, -FLT_MAX, FLT_MAX);
                    };
                    if (shapes[selected_r.num].arr.axis.x) {
                        im::DragFloat3("Rot", shapes[selected_r.num].arr.rot.x, 0.001f, -FLT_MAX, FLT_MAX);
                    };
                    if (shapes[selected_r.num].arr.axis.x) {
                        im::DragFloat3("Scale", shapes[selected_r.num].arr.scale.x, 0.001f, -FLT_MAX, FLT_MAX);
                    };
                    im::TreePop();
                };
                if (shapes[selected_r.num].arr.axis.y) {
                    im::InputFloat("Y Axis Pos X", &shapes[selected_r.num].arr.pos.y.x, 0.001f, 0.05f);
                    im::InputFloat("Y Axis Pos Y", &shapes[selected_r.num].arr.pos.y.y, 0.001f, 0.05f);
                    im::InputFloat("Y Axis Pos Z", &shapes[selected_r.num].arr.pos.y.z, 0.001f, 0.05f);
                };
                if (shapes[selected_r.num].arr.axis.y) {
                    im::InputFloat("Y Axis Rot X", &shapes[selected_r.num].arr.rot.y.x, 0.001f, 0.05f);
                    im::InputFloat("Y Axis Rot Y", &shapes[selected_r.num].arr.rot.y.y, 0.001f, 0.05f);
                    im::InputFloat("Y Axis Rot Z", &shapes[selected_r.num].arr.rot.y.z, 0.001f, 0.05f);
                };
                if (shapes[selected_r.num].arr.axis.y) {
                    im::InputFloat("Y Axis Scale X", &shapes[selected_r.num].arr.scale.y.x, 0.001f, 0.05f);
                    im::InputFloat("Y Axis Scale Y", &shapes[selected_r.num].arr.scale.y.y, 0.001f, 0.05f);
                    im::InputFloat("Y Axis Scale Z", &shapes[selected_r.num].arr.scale.y.z, 0.001f, 0.05f);
                };
                if (shapes[selected_r.num].arr.axis.z) {
                    im::InputFloat("Z Axis Pos X", &shapes[selected_r.num].arr.pos.z.x, 0.001f, 0.05f);
                    im::InputFloat("Z Axis Pos Y", &shapes[selected_r.num].arr.pos.z.y, 0.001f, 0.05f);
                    im::InputFloat("Z Axis Pos Z", &shapes[selected_r.num].arr.pos.z.z, 0.001f, 0.05f);
                };
                if (shapes[selected_r.num].arr.axis.z) {
                    im::InputFloat("Z Axis Rot X", &shapes[selected_r.num].arr.rot.z.x, 0.001f, 0.05f);
                    im::InputFloat("Z Axis Rot Y", &shapes[selected_r.num].arr.rot.z.y, 0.001f, 0.05f);
                    im::InputFloat("Z Axis Rot Z", &shapes[selected_r.num].arr.rot.z.z, 0.001f, 0.05f);
                };
                if (shapes[selected_r.num].arr.axis.z) {
                    im::InputFloat("Z Axis Scale X", &shapes[selected_r.num].arr.scale.z.x, 0.001f, 0.05f);
                    im::InputFloat("Z Axis Scale Y", &shapes[selected_r.num].arr.scale.z.y, 0.001f, 0.05f);
                    im::InputFloat("Z Axis Scale Z", &shapes[selected_r.num].arr.scale.z.z, 0.001f, 0.05f);
                };
            };
        }
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
        im::Begin(colls[selected.num].name.c_str(), (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        im::SetWindowPos({ camera.viewport.x / 2 - (ImGui::GetWindowSize().x / 2), camera.viewport.y / 2 - (ImGui::GetWindowSize().y / 2) });
        im::SetWindowSize({ 250, 120 });
        XsInfo(colls[selected.num].cl);
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
    elif(selected.type == "shader") {
        im::Begin(shaders[selected.num].name.c_str(), (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        im::SetWindowPos({ camera.viewport.x / 2 - (ImGui::GetWindowSize().x / 2), camera.viewport.y / 2 - (ImGui::GetWindowSize().y / 2) });
        im::SetWindowSize({ 250, 240 });
        im::InputText("File Name vs", &shaders[selected.num].file_name_vs);
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(0.12f, 0.10f, 0.21f, 0.60f);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(0.45f, 0.31f, 0.85f, 0.60f);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.37f, 0.17f, 0.69f, 0.60f);
        if (im::Button("Open File Diolog  ", {235, 0}))
            ImGuiFileDialog::Instance()->OpenDialog("VertexShader", "Choose File", ".txt,.vs,.glsl", ".");
        im::InputText("File Name fs", &shaders[selected.num].file_name_fs);
        if (im::Button("Open File Diolog   ", { 235, 0 }))
            ImGuiFileDialog::Instance()->OpenDialog("FragmentShader", "Choose File", ".txt,.fs,.glsl", ".");
        *t_nthm = _thm;
        if (im::Button("Load", { 235, 0 }))
            shaders[selected.num].sd = XsShader(shaders[selected.num].file_name_vs.c_str(), shaders[selected.num].file_name_fs.c_str());
        if (im::Button("Open Files", { 235, 0 })) {
            std::thread vs_notepad(open_with_notepad, shaders[selected.num].file_name_vs.c_str());
            vs_notepad.join();
            std::thread fs_notepad(open_with_notepad, shaders[selected.num].file_name_fs.c_str());
            fs_notepad.join();
        };
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.986);
        if (im::Button("Delete")) {
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
        im::SameLine(ImGui::GetWindowSize().x - 60, -100);
        if (im::Button("Close  ")) {
            selected.type = "none";
            selected.num = -1;
        }
        *t_nthm = _thm;
        im::End();
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

    im::Begin("Log", (bool*)0, ImGuiWindowFlags_NoMove);
    im::SetWindowPos({ camera.viewport.x / left_panel_size.x, camera.viewport.y - (ImGui::GetWindowSize().y) + 20 });
    im::SetWindowSize({ selected_r.type == "shape" ? (camera.viewport.x - camera.viewport.x / left_panel_size.x - camera.viewport.x / right_panel_size.x) : (camera.viewport.x - camera.viewport.x / left_panel_size.x), (ImGui::GetWindowSize().y > camera.viewport.y / 1.01) ? float(camera.viewport.y / 1.01) : float(ImGui::GetWindowSize().y) });
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
        im::SetWindowSize({ 250, 205 });
        if (im::Button("3D Shape  ", { 235, 0 })) {
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
        if (im::Button("Vertices  ", { 235, 0 })) {
            if (XsIsKeyPressed(XS_KEY_SHIFT)) {
                Vertices_t _t;
                _t.name = string("Vertices ") + str(leftvertnum);
                vert_name.push_back(_strdup(_t.name.c_str()));
                vertices.push_back(_t);
                leftvertnum++;
                nw_st.name = string("Vertices ") + str(leftvertnum);
                Log << "Create a Vertices";
                leftvertnum++;
                nw_st.name = string("Vertices ") + to_string(leftvertnum);
            }
            else
                selected.type = "new vert";
        };
        if (im::Button("Texture  ", { 235, 0 })) {
            selected.type = "new tex";
        };
        if (im::Button("Collission  ", { 235, 0 })) {
            selected.type = "new coll";
        };
        if (im::Button("Shader  ", { 235, 0 })) {
            selected.type = "new shader";
        };
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
        im::SetWindowSize({ 250, 160 });
        im::InputText("Name", &nw_st.name);
        _tsv = &shape_name[0];
        im::Combo("Copy From", &s_ns, _tsv, shape_name.size());
        if (im::Button("Create")) {
            const char* temp_copy_name = nw_st.name.c_str();
            if (s_ns != 0)
                nw_st = shapes[s_ns - 1];
            else
                nw_st.sh = new XsShape();
            nw_st.name = temp_copy_name;
            shape_name.push_back(_strdup(nw_st.name.c_str()));
            shapes.push_back(nw_st);
            Log << "Create a 3D Shape";
            selected.type = "none";
            leftshapenum++;
            nw_st.name = string("Shape ") + to_string(leftshapenum);
        };
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
        im::SetWindowSize({ 250, 160 });
        im::InputText("Name", &nw_vt.name);
        _tsv = new char* [vert_name.size() - 1];
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
            leftvertnum++;
            nw_vt.name = string("Vertices ") + to_string(leftvertnum);
        }
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
        im::SetWindowSize({ 250, 160 });
        im::InputText("Name", &nw_tt.name);
        _tsv = &tex_name[0];
        im::Combo("Copy From", &s_nt, _tsv, tex_name.size());
        if (im::Button("Create")) {
            Texture_t _t;
            _t = s_nt == 0 ? _t : textures[s_nt - 1];
            _t.name = nw_tt.name;
            tex_name.push_back(_strdup(_t.name.c_str()));
            textures.push_back(_t);
            Log << "Create a Texture";
            selected.type = "none";
            lefttexnum++;
            nw_tt.name = string("Texture ") + to_string(lefttexnum);
        }
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.986);
        if (im::Button("Cancel"))
            selected.type = "none";
        *t_nthm = _thm;
        im::End();
    }
    elif(selected.type == "new coll") {
        im::Begin("New Collission");
        im::SetWindowPos({ camera.viewport.x / 2 - (ImGui::GetWindowSize().x / 2), camera.viewport.y / 2 - (ImGui::GetWindowSize().y / 2) });
        im::SetWindowSize({ 250, 160 });
        im::InputText("Name", &nw_ct.name);
        _tsv = &coll_name[0];
        im::Combo("Copy From", &s_nc, _tsv, coll_name.size());
        if (im::Button("Create")) {
            Coll_t _t;
            _t = s_nc == 0 ? _t : colls[s_nc - 1];
            _t.name = nw_ct.name;
            coll_name.push_back(_strdup(_t.name.c_str()));
            colls.push_back(_t);
            Log << "Create a Collission";
            selected.type = "none";
            leftcollnum++;
            nw_ct.name = string("Coll ") + to_string(leftcollnum);
        };
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.986);
        if (im::Button("Cancel"))
            selected.type = "none";
        *t_nthm = _thm;
        im::End();
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
        im::Begin("Tools ", (bool*)0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        if (im::GetWindowPos().x < camera.viewport.x / left_panel_size.x)
            im::SetWindowPos({ camera.viewport.x / left_panel_size.x + 1, im::GetWindowPos().y });
        elif (im::GetWindowPos().x > camera.viewport.x - camera.viewport.x / right_panel_size.x)
            im::SetWindowPos({ camera.viewport.x - camera.viewport.x / right_panel_size.x, im::GetWindowPos().y });
        im::SetWindowSize({ 250, 300 });
        if (im::Button("Calculator", { 230, 0 })) {
            selected.type = "calculator";
        };
        if (im::Button("Notepad", { 230, 0 })) {
            selected.type = "notepad";
        };
        if (im::Button("Them", { 230, 0 }))
            _sthem = true;
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.986);
        if (im::Button("Cancel", { 230, 0 })) {
            selected.type = "none";
        };
        *t_nthm = _thm;
        tool_pos = v2f(im::GetWindowPos().x, im::GetWindowPos().y);
        im::End();
    };
    if (selected.type == "notepad") {
        im::Begin("Notepad  ", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        im::SetWindowPos({ camera.viewport.x / 2 - (ImGui::GetWindowSize().x / 2), camera.viewport.y / 2 - (ImGui::GetWindowSize().y / 2) });
        im::SetWindowSize({ 300, 200 });
        im::InputTextMultiline("Notepad  ", &_notepad);
        im::End();
    };
    if (_sthem) {
        setThem(them == 0 ? 1 : 0);
        _thm = im::GetStyle();
        _sthem = false;
    };
};
