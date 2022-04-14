#undef set
#undef op
#include <imgui_internal.h>
namespace ImGui {
	using str = std::string;
	using uint = std::uint32_t;
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
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.5f, 0.5f, 0.5f, 0.01f);

		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowPadding = ImVec2(8.00f, 8.00f);
		style.FramePadding = ImVec2(5.00f, 2.00f);
		style.CellPadding = ImVec2(6.00f, 6.00f);
		style.ItemSpacing = ImVec2(6.00f, 6.00f);
		style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
		style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
		style.IndentSpacing = 10;
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
	};
	bool SafeInputText(const str& label, str& s, auto accept_if, auto accept) {
		static bool change = false;
		bool is_accept = false;
		static str temp_str;
		if (!change)
			temp_str = s;
		if (InputText(label.c_str(), &temp_str, ImGuiInputTextFlags_EnterReturnsTrue)) {
			is_accept = accept_if(temp_str);
			if (is_accept)
				accept(temp_str);
		};
		change = IsItemActive();
		return is_accept;
	};
	void JoystickSlider(auto& _vector2f, float scale = 100.f, float b_scale = 15.f, uint bg_color = IM_COL32(0, 0, 0, 155), uint button_color = IM_COL32(215, 215, 215, 255), const uint& mouse_button = 0u) {
		namespace im = ImGui;
		ImDrawList* draw_list = im::GetWindowDrawList();
		const auto& p = im::GetCursorScreenPos();
		static bool button_clicked = false;
		const auto& mouse = im::GetIO().MousePos;
		draw_list->AddCircleFilled(ImVec2(p.x + scale, p.y + scale), scale, bg_color, 50);
		auto button_x = _vector2f.x * (scale - b_scale) + p.x + scale;
		auto button_y = _vector2f.y * (scale - b_scale) + p.y + scale;
		static float toward = 0.f;
		im::ButtonBehavior(ImRect({ button_x - b_scale, button_y - b_scale}, { button_x + b_scale, button_y + b_scale }), im::GetCurrentWindow()->ID, nullptr, nullptr, 0);
		if (sqrtf(pow(mouse.x - button_x, 2) + pow(mouse.y - button_y, 2)) < b_scale)
			if (im::GetIO().MouseClicked[mouse_button])
				button_clicked = true;
		if (!im::GetIO().MouseDown[mouse_button])
			button_clicked = false;
		if (button_clicked) {
			button_x = mouse.x;
			button_y = mouse.y;
		};
		toward = -atan2(button_x - p.x - scale, button_y - p.y - scale);
		if (sqrtf(pow(p.x - button_x + scale, 2) + pow(p.y - button_y + scale, 2)) > scale - b_scale) {
			button_x = p.x + scale + cos(toward - 0.5f * 3.14f) * -(scale-b_scale);
			button_y = p.y + scale + sin(toward - 0.5f * 3.14f) * -(scale-b_scale);
		};
		draw_list->AddCircleFilled(ImVec2(button_x, button_y), b_scale, button_color, 25);
		im::Dummy(ImVec2(scale*2, scale*2));
		_vector2f.x = (button_x - p.x - scale) / (scale - b_scale);
		_vector2f.y = (button_y - p.y - scale) / (scale - b_scale);
	};
	/*
	void JoystickSlider(float& _x, float& _y, float scale = 100.f, float b_scale = 15.f, uint bg_color = IM_COL32(0, 0, 0, 155), uint button_color = IM_COL32(215, 215, 215, 255), const uint& mouse_button = 0u) {
		namespace im = ImGui;
		ImDrawList* draw_list = im::GetWindowDrawList();
		const auto& p = im::GetCursorScreenPos();
		static bool button_clicked = false;
		const auto& mouse = im::GetIO().MousePos;
		draw_list->AddCircleFilled(ImVec2(p.x + scale, p.y + scale), scale, bg_color, 50);
		auto button_x = _x * (scale - b_scale) + p.x + scale;
		auto button_y = _y * (scale - b_scale) + p.y + scale;
		static float toward = 0.f;
		im::ButtonBehavior(ImRect({ button_x - b_scale, button_y - b_scale}, { button_x + b_scale, button_y + b_scale }), im::GetCurrentWindow()->ID, nullptr, nullptr, 0);
		if (sqrtf(pow(mouse.x - button_x, 2) + pow(mouse.y - button_y, 2)) < b_scale)
			if (im::GetIO().MouseClicked[mouse_button])
				button_clicked = true;
		if (!im::GetIO().MouseDown[mouse_button])
			button_clicked = false;
		if (button_clicked) {
			button_x = mouse.x;
			button_y = mouse.y;
		};
		toward = -atan2(button_x - p.x - scale, button_y - p.y - scale);
		if (sqrtf(pow(p.x - button_x + scale, 2) + pow(p.y - button_y + scale, 2)) > scale - b_scale) {
			button_x = p.x + scale + cos(toward - 0.5f * 3.14f) * -(scale-b_scale);
			button_y = p.y + scale + sin(toward - 0.5f * 3.14f) * -(scale-b_scale);
		};
		draw_list->AddCircleFilled(ImVec2(button_x, button_y), b_scale, button_color, 25);
		im::Dummy(ImVec2(scale*2, scale*2));
		_x = (button_x - p.x - scale) / (scale - b_scale);
		_y = (button_y - p.y - scale) / (scale - b_scale);
	};
	*/
	bool RedButton(const str& label) {
		auto them = &ImGui::GetStyle();
		const auto c1 = them->Colors[ImGuiCol_Button];
		const auto c2 = them->Colors[ImGuiCol_ButtonActive];
		const auto c3 = them->Colors[ImGuiCol_ButtonHovered];
		them->Colors[ImGuiCol_Button] = ImVec4(Xs.Color.Red.x, Xs.Color.Red.y, Xs.Color.Red.z, 0.726);
		them->Colors[ImGuiCol_ButtonActive] = ImVec4(Xs.Color.Red.x, Xs.Color.Red.y, Xs.Color.Red.z, 0.886);
		them->Colors[ImGuiCol_ButtonHovered] = ImVec4(Xs.Color.Red.x, Xs.Color.Red.y, Xs.Color.Red.z, 0.986);
		const bool& b = ImGui::Button(label.c_str());
		them->Colors[ImGuiCol_Button] = c1;
		them->Colors[ImGuiCol_ButtonActive] = c2;
		them->Colors[ImGuiCol_ButtonHovered] = c3;
		return b;
	};
};
void XsInfo(XsTexture& v, const str& name = "") {
	if (!name.empty()) im::Begin(name.c_str());
	im::SafeInputText("Tag", v.tag, [](const str& new_tag) { return !new_tag.empty(); }, [&](const str& new_tag) { v.tag = new_tag; });
	if (v.isLoad()) {
		im::Image((void*)v.data, ImVec2(im::GetWindowSize().x - 25, im::GetWindowSize().x * v3f(v.scale()).normalize().y - 25), ImVec2(0, 0), ImVec2(1, 1));
		if (!v.fileName().empty()) im::Text(("File Name: "s + v.fileName()).c_str());
	im::Text(("Size: X = "s + std::to_string(v.scale().x) + ", Y = " + std::to_string(v.scale().y)).c_str());
	};
	if (im::Button("Load From File")) {
		const auto& s = pfd::open_file::open_file("Select File", std::filesystem::current_path().string(), { "Image Files", "*.png *.jpg *.jpeg *.gif" }, pfd::opt::none).result();
		if (!s.empty()) v.load(s[0]);
	};
	if (!name.empty()) im::End();
};
void XsInfo(XsLight& v, const str& name = "") {
	if (!name.empty()) im::Begin(name.c_str());
	im::SafeInputText("Tag", v.tag, [](const str& new_tag) { return !new_tag.empty(); }, [&](const str& new_tag) { v.tag = new_tag; });
	im::DragFloat3("Position", *v.pos, 0.01f, -FLT_MAX, FLT_MAX);
	im::DragFloat("Power", &v.power, 0.01f, 0, FLT_MAX);
	vex3f _color = (vex3f() << v.color) / 255.f;
	im::ColorPicker3("Color", *_color);
	v.color = vex4ub(_color * 255.f, 255);
	if (!name.empty()) im::End();
}
void XsInfo(XsShape& v, const str& name = "") {
	if (!name.empty()) im::Begin((name+"##"+std::to_string(v.id)).c_str());
	im::SafeInputText("Tag", v.tag, [](const str& new_tag) { return !new_tag.empty(); }, [&](const str& new_tag) { v.tag = new_tag; });
	im::DragFloat3("Position", *v.pos, 0.01f, -FLT_MAX, FLT_MAX);
	im::DragFloat3("Rotation", *v.rot, 1.f, -FLT_MAX, FLT_MAX);
	im::DragFloat3("Scale", *v.scale, 0.01f, -FLT_MAX, FLT_MAX);
	im::DragFloat3("Origin", *v.origin, 0.01f, -FLT_MAX, FLT_MAX);
	vex4f _color = (vex4f)v.color / 255.f;
	static const auto& color_flags = ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_DisplayHSV | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_PickerHueWheel;// | ImGuiColorEditFlags_NoSidePreview;
	im::ColorPicker4("Color", *_color, color_flags);
	v.color = vex4ub(_color * 255.f);
	im::Checkbox("Froze", &v.froze);
	im::Checkbox("Hide", &v.hide);
	if (im::TreeNode("Material")) {
		im::DragFloat3("Ambient", *v.ambient, 0.01f, -FLT_MAX, FLT_MAX);
		im::DragFloat3("Diffuse", *v.diffuse, 0.01f, -FLT_MAX, FLT_MAX);
		im::DragFloat3("Specular", *v.specular, 0.01f, -FLT_MAX, FLT_MAX);
		im::DragFloat("Shininess", &v.shininess, 0.01f, -FLT_MAX, FLT_MAX);
		im::TreePop();
	};
	if (im::TreeNode("Texture")) {
		if (v.tex != nullptr) {
			XsInfo(*v.tex);
			im::SameLine(im::GetWindowSize().x-110, 50);
			im::RedButton("Delete");
			if (im::IsItemClicked() and im::GetIO().MouseDoubleClicked[0]) {
				//eng.destroy(*v.tex);
				v.tex = nullptr;
			};
		}
		else {
			enum class tex_t : byte { none, flat, checker, gradient, noise };
			using enum tex_t;
			static tex_t tex = none;
			static XsTexture t_tex;
			if (im::Button("Create"))
				im::OpenPopup("sss");
			bool open = false;
			if (im::BeginPopup("sss")) {
				if (im::MenuItem("Load From File")) {
					const auto& s = pfd::open_file::open_file("Select File", std::filesystem::current_path().string(), { "Image Files", "*.png *.jpg *.jpeg *.gif" }, pfd::opt::none).result();
					if (!s.empty()) {
						if (s.back().ends_with(".gif")) {
							auto& temp_anim = eng.create(new XsAnim(), v.tag + " Anim");
							temp_anim.loadFromGIF(s.back());
							v.tex = &temp_anim.current();
						}
						else
							v.tex = &eng.create(new XsTexture(t_tex.load(s[0])), v.tag + " Texture");
					}
				};
				if (im::MenuItem("Flat Color")) {
					tex = flat;
					open = true;
				};
				if (im::MenuItem("Checker")) {
					tex = checker;
					open = true;
				};
				if (im::MenuItem("Gradient")) {
					tex = gradient;
					open = true;
				};
				if (im::MenuItem("Noise")) {
					tex = noise;
					open = true;
				};
				im::EndPopup();
			};
			if (open)
				im::OpenPopup("Modal window");
			if (ImGui::BeginPopupModal("Modal window", (bool*)0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize)) {
				static vex2i size = 50;
				static vex4f color1 = 1.f, color2 = 1.f;
				im::InputInt("Scale X", &size.x, 1, 100);
				im::InputInt("Scale Y", &size.y, 1, 100);
				size.x = if_else(size.x < 1, 1, size.x);
				size.y = if_else(size.y < 1, 1, size.y);
				if (tex == flat) {
					im::ColorEdit4("Color", *color1);
					if (im::Button("Create")) {
						v.tex = &eng.create(new XsTexture(t_tex.create(size.x, size.y, color1)), v.tag + " Texture");
						im::CloseCurrentPopup();
					};
				}
				else if (tex == checker) {
					im::ColorEdit4("First Color", *color1);
					im::ColorEdit4("Second Color", *color2);
					if (im::Button("Create")) {
						v.tex = &eng.create(new XsTexture(t_tex.createCheckerA(size.x, size.y, color1, color2)), v.tag + " Texture");
						im::CloseCurrentPopup();
					};
				}
				else if (tex == gradient) {
					static bool y_axis = false;
					im::ColorEdit4("First Color", *color1);
					im::ColorEdit4("Second Color", *color2);
					im::Checkbox("Y Axis", &y_axis);
					if (im::Button("Create")) {
						v.tex = &eng.create(new XsTexture(if_else(y_axis, t_tex.createGradientY(size.x, size.y, color1, color2), t_tex.createGradientX(size.x, size.y, color1, color2))), v.tag + " Texture");
						im::CloseCurrentPopup();
					};
				}
				else if (tex == noise) {
					static float _max = 1, _min = 0;
					im::DragFloat("Min", &_min, 0.01f, 0, _max-0.01f);
					im::DragFloat("Max", &_max, 0.01f, _min+0.01f, 1);
					if (im::Button("Create")) {
						v.tex = &eng.create(new XsTexture(t_tex.createNoise(size.x, size.y, color1)), v.tag + " Texture");
						im::CloseCurrentPopup();
					};
				}
				im::SameLine(im::GetWindowSize().x-110, 50);
				if (im::RedButton("Cancel"))
					im::CloseCurrentPopup();
				im::EndPopup();
			}
		};
		im::TreePop();
	};
	if (im::TreeNode("Mesh")) {
		if (v.mesh == nullptr) {
			if (im::Button("Create"))
				im::OpenPopup("sss");
			if (im::BeginPopup("sss")) {
				if (im::MenuItem("Load From OBJ")) {
					auto s = pfd::open_file::open_file("Select File", std::filesystem::current_path().string(), { "Obj", "*.obj" }, pfd::opt::none).result();
					if (!s.empty()) v.mesh = &eng.create(new XsMesh(Xs.LoadOBJ(s[0])));
				};
				if (im::MenuItem("Plane")) {
					v.mesh = &eng.create(new XsMesh(Xs.Mesh.Plane), v.tag + " Mesh");
				};
				if (im::MenuItem("Cube")) {
					v.mesh = &eng.create(new XsMesh(Xs.Mesh.Cube), v.tag + " Mesh");
				};
				im::EndPopup();
			};
		}
		else {
			int temp_s = (v.mesh->poly == Xs.Enum.Point) ? 0 : (v.mesh->poly == Xs.Enum.Line) ? 1 : (v.mesh->poly == Xs.Enum.Triangle) ? 2 : (v.mesh->poly == Xs.Enum.Quad) ? 3 : (v.mesh->poly == Xs.Enum.Polygon) ? 4 : 0;
			im::Combo("Poly", &temp_s, Xs.Values.PolyNames, 5);
			v.mesh->poly = (temp_s == 0) ? Xs.Enum.Point : (temp_s == 1) ? Xs.Enum.Line : (temp_s == 2) ? Xs.Enum.Triangle : (temp_s == 3) ? Xs.Enum.Quad : Xs.Enum.Polygon;
			if (im::Button("Load From OBJ")) {
				auto s = pfd::open_file::open_file("Select File", std::filesystem::current_path().string(), { "Obj", "*.obj" }, pfd::opt::none).result();
				if (!s.empty()) *v.mesh = Xs.LoadOBJ(s[0]);
			};
			im::SameLine(im::GetWindowSize().x-110, 50);
			im::RedButton("Delete");
			if (im::IsItemClicked() and im::GetIO().MouseDoubleClicked[0]) {
				//eng.destroy(*v.mesh);
				v.mesh = nullptr;
			};
		};
		im::TreePop();
	};
	if (!name.empty()) im::End();
};