void XsLib::Start() {
    while (window.isOpen()) {
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
        ImGui::SFML::ProcessEvent(event);
        window.pollEvent(event);
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
        if (!game_mode)
        for (auto& i : pushs)
            if (i.code == "after process" or i.code == "before camera") {
                i.push_data();
                break;
            };
        camera_sett();
        if (game_mode)
            drawfloor(floor_shader);

        if (!game_mode)
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
                glLoadIdentity();
                if (i.gl_vert == 0 and shapes[selected_r.num].s_vert > 1)
                    glPointSize(i.s_point);
                elif(i.gl_vert == 1 and shapes[selected_r.num].s_vert > 1)
                    glLineWidth(i.w_line);
                if (i.arr.use == false) {
                    if (i.s_texture > 0) {
                        i.sh->draw(*vertices[i.s_vert - 2].vr, *textures[i.s_texture - 1].tx, f_XsEnum(i.xs_vert), f_GLenum(i.gl_vert));
                        glBindTexture(GL_TEXTURE_2D, 0);
                    }
                    else
                        i.sh->draw(*vertices[i.s_vert - 2].vr, f_XsEnum(i.xs_vert), f_GLenum(i.gl_vert));
                }
                else {
                    if (i.s_texture > 0) {
                        textures[i.s_texture - 1].tx->bind();
                        const XsEnum _xs = f_XsEnum(i.xs_vert);
                        const GLenum _gl = f_GLenum(i.gl_vert);
                        const XsShape _ts = *i.sh;
                        for (volatile size_t j = 0; j < i.arr.limit; j++) {
                            i.sh->pos += i.arr.pos.x;
                            i.sh->rot += i.arr.rot.x;
                            i.sh->scale += i.arr.scale.x;
                            glLoadIdentity();
                            i.sh->draw(*vertices[i.s_vert - 2].vr, _xs, _gl);
                        }
                        *i.sh = _ts;
                        glBindTexture(GL_TEXTURE_2D, 0);
                    }
                    else {
                        const XsEnum _xs = f_XsEnum(i.xs_vert);
                        const GLenum _gl = f_GLenum(i.gl_vert);
                        const XsShape _ts = *i.sh;
                        for (volatile size_t j = 0; j < i.arr.limit; j++) {
                            i.sh->pos += i.arr.pos.x;
                            i.sh->rot += i.arr.rot.x;
                            i.sh->scale += i.arr.scale.x;
                            glLoadIdentity();
                            i.sh->draw(*vertices[i.s_vert - 2].vr, _xs, _gl);
                        }
                        *i.sh = _ts;
                    }
                }
            }
            elif(i.s_vert == 1) {
                glLoadIdentity();
                if (i.arr.use == false)
                    if (i.s_texture > 0) {
                        textures[i.s_texture - 1].tx->bind();
                        i.sh->draw(f_SolidType(i.s_solid), f_XsEnum(i.xs_vert));
                        glBindTexture(GL_TEXTURE_2D, 0);
                    }
                    else
                        i.sh->draw(f_SolidType(i.s_solid), f_XsEnum(i.xs_vert));
                else {
                    if (i.s_texture > 0) {
                        textures[i.s_texture - 1].tx->bind();
                        const XsEnum _xs = f_XsEnum(i.xs_vert);
                        const XsShape _ts = *i.sh;
                        for (volatile size_t j = 0; j < i.arr.limit; j++) {
                            i.sh->pos += i.arr.pos.x;
                            i.sh->rot += i.arr.rot.x;
                            i.sh->scale += i.arr.scale.x;
                            glLoadIdentity();
                            i.sh->draw(f_SolidType(i.s_solid), f_XsEnum(i.xs_vert));
                        }
                        *i.sh = _ts;
                        glBindTexture(GL_TEXTURE_2D, 0);
                    }
                    else {
                        const XsEnum _xs = f_XsEnum(i.xs_vert);
                        const XsShape _ts = *i.sh;
                        for (volatile size_t j = 0; j < i.arr.limit; j++) {
                            i.sh->pos += i.arr.pos.x;
                            i.sh->rot += i.arr.rot.x;
                            i.sh->scale += i.arr.scale.x;
                            glLoadIdentity();
                            i.sh->draw(f_SolidType(i.s_solid), f_XsEnum(i.xs_vert));
                        }
                        *i.sh = _ts;
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

        ImGui::SFML::Update(window, imclock.restart());

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
        ImGui::SetWindowPos({ camera.viewport.x / 2, -5 });
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