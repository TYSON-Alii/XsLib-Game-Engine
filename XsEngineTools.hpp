void XsLib::tools() {
    ImGui::Begin("dsafbdjagvfa", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoTitleBar);
    ImGui::SetWindowPos({ camera.viewport.x - (r_panel ? (camera.viewport.x / 5.f) : 0.f) - 55, -5 });
    ImGui::SetWindowSize({ 100, 100 });
    if (ImGui::Button("Tools")) {
        if (selected.type == "tools")
            selected.type = "none";
        else
            selected.type = "tools";
    };
    ImGui::End();

    bool _sthem = false;
    if (selected.type == "tools") {
        ImGui::Begin("Tools ", (bool*)0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        if (ImGui::GetWindowPos().x < camera.viewport.x / left_panel_size.x)
            ImGui::SetWindowPos({ camera.viewport.x / left_panel_size.x + 1, ImGui::GetWindowPos().y });
        elif(ImGui::GetWindowPos().x > camera.viewport.x - camera.viewport.x / right_panel_size.x)
            ImGui::SetWindowPos({ camera.viewport.x - camera.viewport.x / right_panel_size.x, ImGui::GetWindowPos().y });
        ImGui::SetWindowSize({ 250, 300 });
        if (ImGui::Button("Calculator", { 230, 0 })) {
            selected.type = "calculator";
        };
        if (ImGui::Button("Notepad", { 230, 0 })) {
            selected.type = "notepad";
        };
        if (ImGui::Button("Them", { 230, 0 }))
            _sthem = true;
        t_nthm->Colors[ImGuiCol_Button] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.726);
        t_nthm->Colors[ImGuiCol_ButtonActive] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.886);
        t_nthm->Colors[ImGuiCol_ButtonHovered] = ImVec4(XsRed.x, XsRed.y, XsRed.z, 0.986);
        if (ImGui::Button("Cancel", { 230, 0 })) {
            selected.type = "none";
        };
        *t_nthm = _thm;
        tool_pos = v2f(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y);
        ImGui::End();
    };
    if (selected.type == "notepad") {
        ImGui::Begin("Notepad  ", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        ImGui::SetWindowPos({ camera.viewport.x / 2 - (ImGui::GetWindowSize().x / 2), camera.viewport.y / 2 - (ImGui::GetWindowSize().y / 2) });
        ImGui::SetWindowSize({ 300, 200 });
        ImGui::InputTextMultiline("Notepad  ", &_notepad);
        ImGui::End();
    };
    if (_sthem) {
        setThem(them == 0 ? 1 : 0);
        _thm = ImGui::GetStyle();
        _sthem = false;
    };
};
