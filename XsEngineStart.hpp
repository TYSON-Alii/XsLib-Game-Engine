void XsLib::Start() {
    while (Window.isOpen()) {
        s_fps = std::chrono::high_resolution_clock::now();
        if (!game_mode)
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
        if (!game_mode)
            for (auto& i : pushs)
                if (i.code == "after clear" or i.code == "before process") {
                    i.push_data();
                    break;
                };
        ImGui::SFML::ProcessEvent(Event);
        Window.pollEvent(Event);
        if (Event.type == sf::Event::Closed) {
            Log << "Window closed";
            Window.close();
            break;
        };
        mouse_pos = XsGetMousePos();
        if (!game_mode)
            for (auto& i : pushs)
                if (i.code == "after process" or i.code == "before camera") {
                    i.push_data();
                    break;
                };
        camera_sett();
        if (use_skybox) {
            skybox.color.w = 1;
            skybox.position = Camera.pos;
            skybox.draw(XS_SPHERE);
            glBindTexture(GL_TEXTURE_2D, 0);
        };
        if (game_mode and show_floor)
            drawfloor(floor_shader);

        if (!game_mode)
        for (auto& i : pushs)
            if (i.code == "after camera" or i.code == "normal" or i.code == "before draw") {
                i.push_data();
                break;
            };

        for (auto& i : shapes) {
            if (i._selected_coll > 0) {
                if (i.isLockColl()) {
                    XsColl _t = colls[i._selected_coll - 1].cl;
                    _t.pos = i.Shape().pos + colls[i._selected_coll - 1].cl.pos;
                    if (i.isShowColl())
                        XsDrawColl(_t, 0.1);
                }
                else
                    if (i.isShowColl())
                        XsDrawColl(colls[i._selected_coll - 1].cl, 0.1);
            };
            if (i._selected_vert > 1) {
                glLoadIdentity();
                if (i._gl_vert == 0 and shapes[selected_r.num]._selected_vert > 1)
                    glPointSize(i.pointScale());
                elif(i._gl_vert == 1 and shapes[selected_r.num]._selected_vert > 1)
                    glLineWidth(i.lineWidth());
                if (i.Array.use == false) {
                    if (i._selected_tex > 0) {
                        i.Shape().draw(*vertices[i._selected_vert - 2].vr, *textures[i._selected_tex - 1].tx, f_XsEnum(i._xs_vert), f_GLenum(i._gl_vert));
                        glBindTexture(GL_TEXTURE_2D, 0);
                    }
                    else
                        i.Shape().draw(*vertices[i._selected_vert - 2].vr, f_XsEnum(i._xs_vert), f_GLenum(i._gl_vert));
                }
                else {
                    if (i._selected_tex > 0) {
                        textures[i._selected_tex - 1].tx->bind();
                        const XsEnum _xs = f_XsEnum(i._xs_vert);
                        const GLenum _gl = f_GLenum(i._gl_vert);
                        const XsShape _ts = i.Shape();
                        for (volatile size_t j = 0; j < i.Array.limit; j++) {
                            i.Shape().pos += i.Array.pos;
                            i.Shape().rot += i.Array.rot;
                            i.Shape().scale += i.Array.scale;
                            glLoadIdentity();
                            i.Shape().draw(*vertices[i._selected_vert - 2].vr, _xs, _gl);
                        }
                        i.Shape() = _ts;
                        glBindTexture(GL_TEXTURE_2D, 0);
                    }
                    else {
                        const XsEnum _xs = f_XsEnum(i._xs_vert);
                        const GLenum _gl = f_GLenum(i._gl_vert);
                        const XsShape _ts = i.Shape();
                        for (volatile size_t j = 0; j < i.Array.limit; j++) {
                            i.Shape().pos += i.Array.pos;
                            i.Shape().rot += i.Array.rot;
                            i.Shape().scale += i.Array.scale;
                            glLoadIdentity();
                            i.Shape().draw(*vertices[i._selected_vert - 2].vr, _xs, _gl);
                        }
                        i.Shape() = _ts;
                    }
                }
            }
            elif(i._selected_vert == 1) {
                glLoadIdentity();
                if (i.Array.use == false)
                    if (i._selected_tex > 0) {
                        textures[i._selected_tex - 1].tx->bind();
                        i.Shape().draw(f_SolidType(i._selected_solid), f_XsEnum(i._xs_vert));
                        glBindTexture(GL_TEXTURE_2D, 0);
                    }
                    else
                        i.Shape().draw(f_SolidType(i._selected_solid), f_XsEnum(i._xs_vert));
                else {
                    if (i._selected_tex > 0) {
                        textures[i._selected_tex - 1].tx->bind();
                        const XsEnum _xs = f_XsEnum(i._xs_vert);
                        const XsShape _ts = i.Shape();
                        for (volatile size_t j = 0; j < i.Array.limit; j++) {
                            i.Shape().pos += i.Array.pos;
                            i.Shape().rot += i.Array.rot;
                            i.Shape().scale += i.Array.scale;
                            glLoadIdentity();
                            i.Shape().draw(f_SolidType(i._selected_solid), f_XsEnum(i._xs_vert));
                        }
                        i.Shape() = _ts;
                        glBindTexture(GL_TEXTURE_2D, 0);
                    }
                    else {
                        const XsEnum _xs = f_XsEnum(i._xs_vert);
                        const XsShape _ts = i.Shape();
                        for (volatile size_t j = 0; j < i.Array.limit; j++) {
                            i.Shape().pos += i.Array.pos;
                            i.Shape().rot += i.Array.rot;
                            i.Shape().scale += i.Array.scale;
                            glLoadIdentity();
                            i.Shape().draw(f_SolidType(i._selected_solid), f_XsEnum(i._xs_vert));
                        }
                        i.Shape() = _ts;
                    };
                }
            }
        };

        if (!game_mode)
        for (auto& i : pushs)
            if (i.code == "after draw") {
                i.push_data();
                break;
            };

        if (game_mode)
            xsui();

        ImGui::SFML::Update(Window, imclock.restart());

        if (game_mode) {
            ui();
            tools();
        };

        //im::ShowDemoWindow();

        if (!game_mode)
        for (auto& i : pushs)
            if (i.code == "in imgui") {
                i.push_data();
                break;
            };

        ImGui::Begin("RunButton", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoTitleBar);
        ImGui::SetWindowPos({ Camera.viewport.x / 2, -5 });
        ImGui::SetWindowSize({ 70, 70 });
        if (game_mode) {
            t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsDarkGreen.x, XsDarkGreen.y, XsDarkGreen.z, 0.726);
            t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsDarkGreen.x, XsDarkGreen.y, XsDarkGreen.z, 0.886);
            t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsDarkGreen.x, XsDarkGreen.y, XsDarkGreen.z, 0.986);
        }
        else {
            t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.726);
            t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.886);
            t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.986);
        };
        if (ImGui::Button(game_mode ? "Play" : "Stop"))
            game_mode = !game_mode;
        *t_nthm = _thm;
        ImGui::End();

        Window.pushGLStates();
        ImGui::SFML::Render(Window);
        Window.popGLStates();
        Window.display();
        if (fps_tm.getMilliSeconds() > 0.1) {
            fps_tm.restart();
            fps = (float)1e9 / (float)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - s_fps).count();
        };
    };
};
