namespace ImGui {
	void DragFloat2(const char* label, vex2f& v, float v_speed, float _min, float _max) {
		auto _v = v.arr();
		ImGui::DragFloat2(label, _v, v_speed, _min, _max);
		v.x = _v[0];
		v.y = _v[1];
	};
	void DragFloat3(const char* label, vex3f& v, float v_speed, float _min, float _max) {
		auto _v = v.arr();
		ImGui::DragFloat3(label, _v, v_speed, _min, _max);
		v.x = _v[0];
		v.y = _v[1];
		v.z = _v[2];
	};
	void DragFloat4(const char* label, vex4f& v, float v_speed, float _min, float _max) {
		auto _v = v.arr();
		ImGui::DragFloat4(label, _v, v_speed, _min, _max);
		v.x = _v[0];
		v.y = _v[1];
		v.z = _v[2];
		v.w = _v[3];
	};
	void SliderFloat2(const char* label, vex2f& v, float _min, float _max) {
		auto _v = v.arr();
		ImGui::SliderFloat2(label, _v, _min, _max);
		v.x = _v[0];
		v.y = _v[1];
	};
	void SliderFloat3(const char* label, vex3f& v, float _min, float _max) {
		auto _v = v.arr();
		ImGui::SliderFloat3(label, _v, _min, _max);
		v.x = _v[0];
		v.y = _v[1];
		v.z = _v[2];
	};
	void SliderFloat4(const char* label, vex4f& v, float _min, float _max) {
		auto _v = v.arr();
		ImGui::SliderFloat4(label, _v, _min, _max);
		v.x = _v[0];
		v.y = _v[1];
		v.z = _v[2];
		v.w = _v[3];
	};
	void DragInt2(const char* label, vex2i& v, float v_speed, int _min, int _max) {
		auto _v = v.arr();
		ImGui::DragInt2(label, _v, v_speed, _min, _max);
		v.x = _v[0];
		v.y = _v[1];
	};
	void DragInt3(const char* label, vex3i& v, float v_speed, int _min, int _max) {
		auto _v = v.arr();
		ImGui::DragInt3(label, _v, v_speed, _min, _max);
		v.x = _v[0];
		v.y = _v[1];
		v.z = _v[2];
	};
	void DragInt4(const char* label, vex4i& v, float v_speed, int _min, int _max) {
		auto _v = v.arr();
		ImGui::DragInt4(label, _v, v_speed, _min, _max);
		v.x = _v[0];
		v.y = _v[1];
		v.z = _v[2];
		v.w = _v[3];
	};
	void DragInt2(const char* label, vex2ui& v, float v_speed, size_t _min, size_t _max) {
		int _v[2]{ v.x, v.y };
		ImGui::DragInt2(label, _v, v_speed, _min, _max);
		v.x = _v[0];
		v.y = _v[1];
	};
	void DragInt3(const char* label, vex3ui& v, float v_speed, size_t _min, size_t _max) {
		int _v[3]{ v.x, v.y, v.z };
		ImGui::DragInt3(label, _v, v_speed, _min, _max);
		v.x = _v[0];
		v.y = _v[1];
		v.z = _v[2];
	};
	void DragInt4(const char* label, vex4ui& v, float v_speed, size_t _min, size_t _max) {
		int _v[4]{ v.x, v.y, v.z, v.w };
		ImGui::DragInt4(label, _v, v_speed, _min, _max);
		v.x = _v[0];
		v.y = _v[1];
		v.z = _v[2];
		v.w = _v[3];
	};
	void SliderInt2(const char* label, vex2i& v, int _min, int _max) {
		int _v[4]{ v.x, v.y };
		ImGui::SliderInt2(label, _v, _min, _max);
		v.x = _v[0];
		v.y = _v[1];
	};
	void SliderInt3(const char* label, vex3i& v, int _min, int _max) {
		auto _v = v.arr();
		ImGui::SliderInt3(label, _v, _min, _max);
		v.x = _v[0];
		v.y = _v[1];
		v.z = _v[2];
	};
	void SliderInt4(const char* label, vex4i& v, int _min, int _max) {
		auto _v = v.arr();
		ImGui::SliderInt4(label, _v, _min, _max);
		v.x = _v[0];
		v.y = _v[1];
		v.z = _v[2];
		v.w = _v[3];
	};
	void ColorPicker4(const char* label, vex4f& v) {
		auto _v = v.arr();
		ImGui::ColorPicker4(label, _v);
		v.x = _v[0];
		v.y = _v[1];
		v.z = _v[2];
		v.w = _v[3];
	};
	void ColorPicker3(const char* label, vex3f& v) {
		auto _v = v.arr();
		ImGui::ColorPicker3(label, _v);
		v.x = _v[0];
		v.y = _v[1];
		v.z = _v[2];
	};

	void DragFloat2(const char* label, sf::Vector2f& v, float v_speed, float _min, float _max) {
		float _v[2];
		_v[0] = v.x;
		_v[1] = v.y;
		ImGui::DragFloat2(label, _v, v_speed, _min, _max);
		v.x = _v[0];
		v.y = _v[1];
	};
	void SliderFloat2(const char* label, sf::Vector2f& v, float _min, float _max) {
		float _v[2];
		_v[0] = v.x;
		_v[1] = v.y;
		ImGui::SliderFloat2(label, _v, _min, _max);
		v.x = _v[0];
		v.y = _v[1];
	};
	void DragInt2(const char* label, sf::Vector2i& v, float v_speed, int _min, int _max) {
		int _v[2];
		_v[0] = v.x;
		_v[1] = v.y;
		ImGui::DragInt2(label, _v, v_speed, _min, _max);
		v.x = _v[0];
		v.y = _v[1];
	};
	void SliderInt2(const char* label, sf::Vector2i& v, int _min, int _max) {
		int _v[2];
		_v[0] = v.x;
		_v[1] = v.y;
		ImGui::SliderInt2(label, _v, _min, _max);
		v.x = _v[0];
		v.y = _v[1];
	};
	void InputInt3(const char* label, vex3i& v) {
		auto _v = v.arr();
		ImGui::InputInt3(label, _v);
		v.x = _v[0];
		v.y = _v[1];
		v.z = _v[2];
	};
	void InputFloat3(const char* label, vex3f& v) {
		auto _v = v.arr();
		ImGui::InputFloat3(label, _v);
		v.x = _v[0];
		v.y = _v[1];
		v.z = _v[2];
	};
	void StyleXsDark() {
		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 0.28f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
		colors[ImGuiCol_Border] = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.89f, 0.46f, 0.54f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
		colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
		colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.f, 0.f, 0.f, 0.f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.f, 0.f, 0.f, 0.f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.f, 0.f, 0.f, 0.f);
		colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_TableHeaderBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_TableBorderStrong] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_TableBorderLight] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
		colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
		colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);

		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowPadding = ImVec2(8.00f, 8.00f);
		style.FramePadding = ImVec2(5.00f, 2.00f);
		style.CellPadding = ImVec2(6.00f, 6.00f);
		style.ItemSpacing = ImVec2(6.00f, 6.00f);
		style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
		style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
		style.IndentSpacing = 25;
		style.ScrollbarSize = 11;
		style.GrabMinSize = 10;
		style.WindowBorderSize = 1;
		style.ChildBorderSize = 1;
		style.PopupBorderSize = 1;
		style.FrameBorderSize = 1;
		style.TabBorderSize = 1;
		style.WindowRounding = 0;
		style.ChildRounding = 0;
		style.FrameRounding = 3;
		style.PopupRounding = 3;
		style.ScrollbarRounding = 0;
		style.GrabRounding = 3;
		style.LogSliderDeadzone = 4;
		style.TabRounding = 3;

		/*
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
		*/
	};
};
