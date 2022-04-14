#include <XsLib.hpp>
#define win ::eng.Window
#define cam ::eng.Cam
#define wn_size ::eng.Cam.viewport
namespace fs = std::filesystem;
class App {
public:
    bool mouse_safe = true;
    vex2f mouse;
    vex3b show_axis = true;
    bool show_floor = true;
    float line_width = 1.f;
    ImGuiStyle* them = nullptr;
    ImGuiStyle cthem;
    u8 alt_panel = 0;
    bool preview = false;
    Texture* preview_tex = nullptr;
    Anim* preview_anim = nullptr;
    struct Dir_t {
        Dir_t() = default;
        Dir_t(const str& p, bool d) : path(p), is_directory(d) { };
        str path;
        bool is_directory = false;
    };
    list<Dir_t> dirs;
    str path = fs::current_path().string(), path_str;
    bool change_path = false;
    sf::Texture folder_icon, model_icon, imagefile_icon, textfile_icon, xsproj_icon, header_icon, source_icon, csource_icon, defaultfile_icon, updir_icon;
    float icon_size = 1.f;
    enum class Selected_t : byte { NONE, SHAPE, CAMERA, TEXTURE, ANIM, MESH, LIGHT };
    using enum Selected_t;
    struct {
        Selected_t s = NONE;
        uint num = 0;
        inline Selected_t& operator()() { return s; };
    } Sel, drag_s;
    bool drag_start = false, file_drag_start = false, fdrag_press = false;
    str drag_path;
    inline void update_dir() {
        for (const auto& i : fs::directory_iterator(path))
            if (i.is_directory())
                dirs.push_back(Dir_t(i.path().string(), i.is_directory()));
        for (const auto& i : fs::directory_iterator(path))
            if (!i.is_directory())
                dirs.push_back(Dir_t(i.path().string(), i.is_directory()));
    };
    void env() {
        glBindTexture(GL_TEXTURE_2D, 0);
        glDepthFunc(GL_ALWAYS);
        glDepthMask(GL_FALSE);
        glLoadIdentity();
        floor_shader.use();
        floor_shader("projection", cam.projectionMatrix());
        floor_shader("view", cam.viewMatrix());
        floor_shader("color", vex3f(0.85f, 0.85f, 0.875f));
        floor_shader("cam_y", cam.pos.y);
        const auto& n = 2.f * line_width;
        glLineWidth(if_else(3 > abs(cam.pos.y), 4.1 - abs(cam.pos.y), 1));
        if (show_floor) {
            glTranslatef(ceil(cam.pos.x / n) * n, 0, ceil(cam.pos.z / n) * n);
            glBegin(GL_LINES);
            rep(i, m_ldis.x * m_fdis.z, n)
                if ((ceil(cam.pos.z / n) * n) + m_fdis.z - i != 0 or !show_axis.x)
                    Line(m_fdis.x, 0, m_fdis.z - i, -m_fdis.x, 0, m_fdis.z - i);
            glEnd();

            glBegin(GL_LINES);
            rep(i, m_ldis.z * m_fdis.x, n)
                if ((ceil(cam.pos.x / n) * n) + m_fdis.x - i != 0 or !show_axis.z)
                    Line(m_fdis.x - i, 0, m_fdis.z, m_fdis.x - i, 0, -m_fdis.z);
            glEnd();
        };

        glLoadIdentity();
        glLineWidth(if_else(4 > fabs(cam.pos.y), 5.1 - fabs(cam.pos.y), 2));
        if (show_axis.z) {
            floor_shader("color", axis_color_blue);
            glBegin(GL_LINES);
            Line(0, 0, m_fdis.z + cam.pos.z, 0, 0, -m_fdis.z + cam.pos.z);
            glEnd();
        }
        if (show_axis.x) {
            floor_shader("color", axis_color_red);
            glBegin(GL_LINES);
            Line(m_fdis.x + cam.pos.x, 0, 0, -m_fdis.x + cam.pos.x, 0, 0);
            glEnd();
        }
        if (show_axis.y) {
            floor_shader("color", axis_color_green);
            glBegin(GL_LINES);
            Line(0, m_fdis.y + cam.pos.y, 0, 0, -m_fdis.y + cam.pos.y, 0);
            glEnd();
        }
        glDepthFunc(GL_LESS);
        glDepthMask(GL_TRUE);
    };
    void tex_info(XsTexture& tex) {
        im::SafeInputText("Tag", tex.tag, [](const str& new_tag) { return !new_tag.empty(); }, [&](const str& new_tag) { tex.tag = new_tag; });
        if (tex.isLoad()) {
            im::Image((void*)tex.data, ImVec2(im::GetWindowSize().x - 25, im::GetWindowSize().x * v3f(tex.scale()).normalize().y - 25), ImVec2(0, 0), ImVec2(1, 1));
            if (!tex.fileName().empty()) im::Text(("File Name: "s + tex.fileName()).c_str());
            im::Text(("Size: X = "s + to_string(tex.scale().x) + ", Y = " + to_string(tex.scale().y)).c_str());
        };
        enum class tex_t : byte { none, flat, checker, gradient, noise };
        using enum tex_t;
        static tex_t ttex = none;
        if (im::Button("Create"))
            im::OpenPopup("sss");
        bool open = false;
        if (im::BeginPopup("sss")) {
            if (im::MenuItem("Load From File")) {
                const auto& s = pfd::open_file::open_file("Select File", std::filesystem::current_path().string(), { "Image Files", "*.png *.jpg *.jpeg *.gif" }, pfd::opt::none).result();
                if (!s.empty()) tex.load(s[0]);
            };
            if (im::MenuItem("Flat Color")) {
                ttex = flat;
                open = true;
            };
            if (im::MenuItem("Checker")) {
                ttex = checker;
                open = true;
            };
            if (im::MenuItem("Gradient")) {
                ttex = gradient;
                open = true;
            };
            if (im::MenuItem("Noise")) {
                ttex = noise;
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
            if (ttex == flat) {
                im::ColorEdit4("Color", *color1);
                if (im::Button("Create")) {
                    tex.create(size.x, size.y, color1);
                    im::CloseCurrentPopup();
                };
            }
            else if (ttex == checker) {
                im::ColorEdit4("First Color", *color1);
                im::ColorEdit4("Second Color", *color2);
                if (im::Button("Create")) {
                    tex.createCheckerA(size.x, size.y, color1, color2);
                    im::CloseCurrentPopup();
                };
            }
            else if (ttex == gradient) {
                static bool y_axis = false;
                im::ColorEdit4("First Color", *color1);
                im::ColorEdit4("Second Color", *color2);
                im::Checkbox("Y Axis", &y_axis);
                if (im::Button("Create")) {
                    if (y_axis)
                        tex.createGradientY(size.x, size.y, color1, color2);
                    else
                        tex.createGradientX(size.x, size.y, color1, color2);
                    im::CloseCurrentPopup();
                };
            }
            else if (ttex == noise) {
                static float _max = 1, _min = 0;
                im::DragFloat("Min", &_min, 0.01f, 0, _max - 0.01f);
                im::DragFloat("Max", &_max, 0.01f, _min + 0.01f, 1);
                if (im::Button("Create")) {
                    tex.createNoise(size.x, size.y, color1);
                    im::CloseCurrentPopup();
                };
            }
            im::SameLine(im::GetWindowSize().x - 110, 50);
            if (im::RedButton("Cancel"))
                im::CloseCurrentPopup();
            im::EndPopup();
        };
        im::SameLine(im::GetWindowSize().x-110, 50);
        im::RedButton("Delete");
        if (im::IsItemClicked() and im::GetIO().MouseDoubleClicked[0]) {
            for (auto& i : eng.shapes) if (i.value->tex == &tex) i.value->tex = nullptr;
            eng.destroy(tex);
            Sel() = NONE;
            Sel.num = 0;
        };
    };
    void mesh_info(XsMesh& mesh) {
        im::SafeInputText("Tag", mesh.tag, [](const str& new_tag) { return !new_tag.empty(); }, [&](const str& new_tag) { mesh.tag = new_tag; });
        int temp_s = (mesh.poly == Xs.Enum.Point) ? 0 : (mesh.poly == Xs.Enum.Line) ? 1 : (mesh.poly == Xs.Enum.Triangle) ? 2 : (mesh.poly == Xs.Enum.Quad) ? 3 : (mesh.poly == Xs.Enum.Polygon) ? 4 : 0;
        im::Combo("Poly", &temp_s, Xs.Values.PolyNames, 5);
        mesh.poly = (temp_s == 0) ? Xs.Enum.Point : (temp_s == 1) ? Xs.Enum.Line : (temp_s == 2) ? Xs.Enum.Triangle : (temp_s == 3) ? Xs.Enum.Quad : Xs.Enum.Polygon;
        if (im::Button("Create"))
            im::OpenPopup("sss");
        if (im::BeginPopup("sss")) {
            if (im::MenuItem("Load From OBJ")) {
                auto s = pfd::open_file::open_file("Select File", std::filesystem::current_path().string(), { "Obj", "*.obj" }, pfd::opt::none).result();
                if (!s.empty()) mesh = Xs.LoadOBJ(s[0]);
            };
            if (im::MenuItem("Plane")) {
                mesh = Xs.Mesh.Plane;
            };
            if (im::MenuItem("Cube")) {
                mesh = Xs.Mesh.Cube;
            };
            im::EndPopup();
        };
        im::SameLine(im::GetWindowSize().x - 110, 50);
        im::RedButton("Delete");
        if (im::IsItemClicked() and im::GetIO().MouseDoubleClicked[0]) {
            for (auto& i : eng.shapes) if (i.value->mesh == &mesh) i.value->mesh = nullptr;
            eng.destroy(mesh);
            Sel() = NONE;
            Sel.num = 0;
        };
    };
    void anim_info(XsAnim& anim) {
        im::SafeInputText("Tag", anim.tag, [](const str& new_tag) { return !new_tag.empty(); }, [&](const str& new_tag) { anim.tag = new_tag; });
        if (!anim.frames().empty()) {
            im::Image((void*)anim.current().data, ImVec2(im::GetWindowSize().x - 25, im::GetWindowSize().x * v3f(anim.current().scale()).normalize().y - 25));
            im::Text(("Size: X = "s + to_string(anim.current().scale().x) + ", Y = " + to_string(anim.current().scale().y)).c_str());
            static int p_tex = 0;
            im::Checkbox("Froze", &anim.froze);
            im::InputInt(("Frame "s + to_string(p_tex)).c_str(), &p_tex);
            if (p_tex < 0)
                p_tex = anim.frames().size() - 1;
            else if (p_tex >= anim.frames().size())
                p_tex = 0;
            im::Image((void*)anim.frames()[p_tex].data, ImVec2(im::GetWindowSize().x - 25, im::GetWindowSize().x * v3f(anim.frames()[p_tex].scale()).normalize().y - 25));
            if (im::IsItemHovered() and im::GetIO().MouseClicked[1])
                im::OpenPopup("ext");
            if (im::BeginPopup("ext")) {
                if (im::MenuItem("Extract Frame"))
                    eng.create(new XsTexture(anim.frames()[p_tex]), anim.tag + ' ' + to_string(p_tex));
                im::EndPopup();
            };
        };
        if (im::Button("Create"))
            im::OpenPopup("sss");
        if (im::BeginPopup("sss")) {
            if (im::MenuItem("Load From GIF")) {
                auto s = pfd::open_file::open_file("Select File", fs::current_path().string(), { "Gif", "*.gif" }, pfd::opt::none).result();
                if (!s.empty()) {
                    anim.clear();
                    anim.loadFromGIF(s.back());
                };
            };
            im::EndPopup();
        };
        im::SameLine(im::GetWindowSize().x - 110, 50);
        im::RedButton("Delete");
        if (im::IsItemClicked() and im::GetIO().MouseDoubleClicked[0]) {
            for (auto& i : eng.shapes) if (i.value->tex == &anim.current()) i.value->tex = nullptr;
            eng.destroy(anim);
            Sel() = NONE;
            Sel.num = 0;
        };
    };
    inline void e_info(auto& data, const str& name, const Selected_t& sel_t) {
        if (!data.empty() and im::TreeNode(name.c_str())) {
            size_t j = 0;
            for (const auto&[k,v] : data) {
                const bool is_selected = (Sel() == sel_t and Sel.num == j);
                im::PushID((void*)k);
                im::Bullet();
                if (im::Selectable(v->tag.c_str(), is_selected)) {
                    if (is_selected) {
                        Sel() = NONE;
                        Sel.num = 0;
                    }
                    else {
                        Sel() = sel_t;
                        Sel.num = j;
                    };
                };
                im::PopID();
                static constexpr const ImGuiDragDropFlags src_flags = ImGuiDragDropFlags_SourceNoDisableHover | ImGuiDragDropFlags_SourceNoHoldToOpenOthers;
                if (ImGui::BeginDragDropSource(src_flags)) {
                    if constexpr (!(src_flags & ImGuiDragDropFlags_SourceNoPreviewTooltip))
                        ImGui::Text("Moving '%s'", v->tag.c_str());
                    drag_s.num = j;
                    drag_s() = sel_t;
                    drag_start = true;
                    ImGui::EndDragDropSource();
                }
                j++;
            };
            im::TreePop();
        };
    }
    void sol_taraftaki() {
        e_info(eng.shapes, "Shapes", SHAPE);
        e_info(eng.meshs, "Meshs", MESH);
        e_info(eng.texs, "Textures", TEXTURE);
        e_info(eng.anims, "Anims", ANIM);
        e_info(eng.lights, "Lights", LIGHT);
    };
    void sol_menu() {
        im::BeginMenuBar();
        if (im::BeginMenu("File")) {
            if (im::MenuItem("Save", "crtl + s"))
                pass;
            if (im::MenuItem("Save As"))
                pass;
            if (im::MenuItem("Open", "crtl + o"))
                pass;
            im::EndMenu();
        };
        if (im::BeginMenu("New")) {
            if (im::MenuItem("Camera"))
                pass;
            if (im::MenuItem("Shape")) {
                eng.create(new Shape("Shape "s + to_string(eng.shapes.size())));
                Sel() = SHAPE;
                Sel.num = eng.shapes.size()-1;
            };
            if (im::MenuItem("Texture")) {
                eng.create(new Texture(), "Texture "s + to_string(eng.texs.size()));
                Sel() = TEXTURE;
                Sel.num = eng.texs.size()-1;
            };
            if (im::MenuItem("Anim")) {
                eng.create(new Anim(), "Anim "s + to_string(eng.anims.size()));
                Sel() = ANIM;
                Sel.num = eng.anims.size()-1;
            };
            if (im::MenuItem("Mesh")) {
                eng.create(new Mesh(), "Mesh "s + to_string(eng.meshs.size()));
                Sel() = MESH;
                Sel.num = eng.meshs.size()-1;
            };
            if (im::MenuItem("Light")) {
                eng.create(new Light(0, 1), "Light "s + to_string(eng.lights.size()));
                Sel() = LIGHT;
                Sel.num = eng.lights.size()-1;
            };
            im::EndMenu();
        };
        if (im::BeginMenu("Sett")) {
            im::Checkbox("Floor", &show_floor);
            im::Text("Axis: ");
            im::SameLine(50, -50);
            im::PushStyleColor(ImGuiCol_Text, im_axis_color_red);
            im::Checkbox("X", &show_axis.x);
            im::PopStyleColor();
            im::SameLine(100, -50);
            im::PushStyleColor(ImGuiCol_Text, im_axis_color_green);
            im::Checkbox("Y", &show_axis.y);
            im::PopStyleColor();
            im::SameLine(150, -50);
            im::PushStyleColor(ImGuiCol_Text, im_axis_color_blue);
            im::Checkbox("Z", &show_axis.z);
            im::PopStyleColor();
            im::SliderFloat("Icon Size", &icon_size, 0.1f, 1.5f);
            im::EndMenu();
        };
        im::EndMenuBar();
    };
    void alt_tarafki() {
        im::BeginMenuBar();
        if (im::MenuItem("Log"))
            alt_panel = 0;
        if (im::MenuItem("File"))
            alt_panel = 1;
        im::EndMenuBar();
        if (alt_panel == 0)
            pass
        else if (alt_panel == 1) {
            if (im::ImageButton(updir_icon, {20, 20})) {
                path = path.substr(0, path.find_last_of("/\\"));
                dirs.clear();
                update_dir();
            };
            im::SameLine(45, -50);
            im::ImageButton(folder_icon, { 20, 20 });
            im::SameLine(80, -100);
            /*
            if (!change_path)
                path_str = path;
            if (im::InputText("Path", &path_str, ImGuiInputTextFlags_EnterReturnsTrue)) {
                const auto& ftyp = GetFileAttributesA(path_str.c_str());
                if (ftyp != INVALID_FILE_ATTRIBUTES && (ftyp & FILE_ATTRIBUTE_DIRECTORY)) {
                    path = path_str;
                    dirs.clear();
                    update_dir();
                };
            };
            change_path = im::IsItemActive();
            */
            im::SafeInputText("Path", path,
                      [&](const str& path_str) {
                          const auto& ftyp = GetFileAttributesA(path_str.c_str());
                          return (ftyp != INVALID_FILE_ATTRIBUTES && (ftyp & FILE_ATTRIBUTE_DIRECTORY));
                      },
                      [&](const str& path_str) {
                          path = path_str;
                          dirs.clear();
                          update_dir();
                      });
            int j = 0;
            for (const auto& i : dirs) {
                if (i.is_directory) {
                    ImGui::ImageButton(folder_icon, { 93 * icon_size, 90 * icon_size });
                    if (ImGui::IsItemHovered()) {
                        if (im::IsMouseDoubleClicked(0)) {
                            path = i.path;
                            dirs.clear();
                            update_dir();
                        }
                        else {
                            ImGui::BeginTooltip();
                            ImGui::Text(i.path.c_str());
                            ImGui::EndTooltip();
                        };
                    }
                }
                else {
                    const auto& i_path = i.path;
                    enum class file_type : byte { no, png, jpg, jpeg, gif, obj, txt, xs, hpp, h, hxx, cpp, c, cxx };
                    using enum file_type;
                    file_type f_type = no;
                    if (i_path.ends_with(".png"))       f_type = png;
                    else if (i_path.ends_with(".jpg"))  f_type = jpg;
                    else if (i_path.ends_with(".jpeg")) f_type = jpeg;
                    else if (i_path.ends_with(".gif"))  f_type = gif;
                    else if (i_path.ends_with(".obj"))  f_type = obj;
                    else if (i_path.ends_with(".txt"))  f_type = txt;
                    else if (i_path.ends_with(".xs"))   f_type = xs;
                    else if (i_path.ends_with(".hpp"))  f_type = hpp;
                    else if (i_path.ends_with(".h"))    f_type = h;
                    else if (i_path.ends_with(".hxx"))  f_type = hxx;
                    else if (i_path.ends_with(".cpp"))  f_type = cpp;
                    else if (i_path.ends_with(".c"))    f_type = c;
                    else if (i_path.ends_with(".cxx"))  f_type = cxx;
                    const auto& is_image = (f_type == png) or (f_type == jpg) or (f_type == jpeg) or (f_type == gif);
                    sf::Texture* icon = &defaultfile_icon;
                    if (is_image)
                        icon = &imagefile_icon;
                    else {
                        switch (f_type) {
                        case obj: icon = &model_icon; break;
                        case txt: icon = &textfile_icon; break;
                        case xs: icon = &xsproj_icon; break;
                        case c: icon = &csource_icon; break;
                        case cpp: case cxx: icon = &source_icon; break;
                        case hpp: case h: case hxx: icon = &header_icon; break;
                        };
                    };
                    im::ImageButton(*icon, { 93 * icon_size, 90 * icon_size });
                    if (im::IsItemClicked())
                        drag_path = i.path;
                    if (im::IsItemHovered()) {
                        if (im::IsMouseDoubleClicked(0)) {
                            if (f_type == txt)
                                ShellExecuteA(NULL, "open", i_path.c_str(), NULL, NULL, SW_SHOWDEFAULT);
                            else if (is_image) {
                                preview = true;
                                preview_tex = new XsTexture(i.path);
                            };
                        };
                        im::BeginTooltip();
                        im::Text(i.path.c_str());
                        im::EndTooltip();
                    };
                    static constexpr const ImGuiDragDropFlags src_flags = ImGuiDragDropFlags_SourceNoDisableHover | ImGuiDragDropFlags_SourceNoHoldToOpenOthers;
                    if (im::BeginDragDropSource(src_flags)) {
                        if constexpr (!(src_flags & ImGuiDragDropFlags_SourceNoPreviewTooltip))
                            ImGui::Text("Importing '%s'", drag_path.c_str());
                        file_drag_start = true;
                        im::EndDragDropSource();
                    };
                };
                j++;
                //const auto& l_c = int(im_wsize().x / (icon_size * 93));
                //const auto& l = (im_wsize().x - l_c * (icon_size * 93)) / l_c / 2;
                if ((50 * icon_size * j + (5 * (j + 1))) > im_wsize().x - (50 * icon_size * (j + 1) + (5 * ((j + 1) + 1)))) {
                    j = 0;
                }
                if (j != 0) {
                    im::SameLine(50 * icon_size * j + (5 * (j + 1))/* + ((l - 1) * j)*/, 50 * icon_size * j);
                };
            }
        }
        if (preview) {
            im::Begin("dsfsfdsaf", (bool*)0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_AlwaysAutoResize);
            vex2f _t = preview_tex->scale().y;
            _t.normalize();
            if (preview_anim != nullptr) preview_anim->step();
            im::Image((void*)preview_tex->data, { 300, 300 * _t.y });
            if (mouse.x > im_wpos().x and mouse.x < im_wpos().x + im_wsize().x and mouse.y > im_wpos().y and mouse.y < im_wpos().y + im_wsize().y)
                if (im::GetIO().MouseClicked[1])
                    im::OpenPopup("close preview");
            if (im::BeginPopup("close preview")) {
                if (im::MenuItem("Close")) {
                    preview = false;
                    if (preview_anim != nullptr) {
                        preview_tex = nullptr;
                        delete preview_anim;
                    }
                    else
                        delete preview_tex;
                };
                im::EndPopup();
            };
            im::End();
        };
    }
    void sag_taraftaki() {
        if (Sel() != NONE) {
            switch (Sel()) {
            case SHAPE:
                XsInfo(*eng.shapes.at(Sel.num).value);
                break;
            case TEXTURE:
                tex_info(*eng.texs.at(Sel.num).value);
                break;
            case MESH:
                mesh_info(*eng.meshs.at(Sel.num).value);
                break;
            case ANIM:
                anim_info(*eng.anims.at(Sel.num).value);
                break;
            case LIGHT:
                XsInfo(*eng.lights.at(Sel.num).value);
                break;
            };
        };
    };
    float point_size = 10.f, gizmo_scale = 2.f;
    void gizmo(vex3f& point, const mat4& vmatrix, const mat4& pmatrix, const vex3f& cam_pos, const float& scale = 2.f, const float& point_size = 10.f, const float scalar = 1.f) {
        static vex2b move_x = false, move_y = false, move_z = false;
        const auto& max = point < cam_pos;
        const auto& distance = Xs.Math.Distance(point, cam_pos) / 10.f;
        const vex3f& v = glm::projectNO(glm::vec3(point), vmatrix, pmatrix, glm::vec4(0.0f, 0.0f, wn_size.x, wn_size.y));
        if ((v.z - 1.f) * 0.5f < 0.f) {
            const vex3f& x1 = glm::project(glm::vec3(point + vex3f(scale, 0, 0)), vmatrix, pmatrix, glm::vec4(0.f, 0.f, wn_size.x, wn_size.y));
            const vex3f& y1 = glm::project(glm::vec3(point + vex3f(0, scale, 0)), vmatrix, pmatrix, glm::vec4(0.f, 0.f, wn_size.x, wn_size.y));
            const vex3f& z1 = glm::project(glm::vec3(point + vex3f(0, 0, scale)), vmatrix, pmatrix, glm::vec4(0.f, 0.f, wn_size.x, wn_size.y));
            const vex3f& x2 = glm::project(glm::vec3(point - vex3f(scale, 0, 0)), vmatrix, pmatrix, glm::vec4(0.f, 0.f, wn_size.x, wn_size.y));
            const vex3f& y2 = glm::project(glm::vec3(point - vex3f(0, scale, 0)), vmatrix, pmatrix, glm::vec4(0.f, 0.f, wn_size.x, wn_size.y));
            const vex3f& z2 = glm::project(glm::vec3(point - vex3f(0, 0, scale)), vmatrix, pmatrix, glm::vec4(0.f, 0.f, wn_size.x, wn_size.y));
            const auto& mouse = vex2f(this->mouse.x, wn_size.y - this->mouse.y);
            if (im::GetIO().MouseClicked[0]) {
                if (circle_col(x1, point_size, mouse))
                    move_x[0] = true;
                else if (circle_col(x2, point_size, mouse))
                    move_x[1] = true;
                else if (circle_col(y1, point_size, mouse))
                    move_y[0] = true;
                else if (circle_col(y2, point_size, mouse))
                    move_y[1] = true;
                else if (circle_col(z1, point_size, mouse))
                    move_z[0] = true;
                else if (circle_col(z2, point_size, mouse))
                    move_z[1] = true;
            };
            const auto& ss = scalar / 100.f * distance;
            if (move_x[0] or move_x[1]) {
                if (max.z)
                    point.x += (im::GetIO().MouseDelta.x - im::GetIO().MouseDelta.y) * ss;
                else
                    point.x -= (im::GetIO().MouseDelta.x - im::GetIO().MouseDelta.y) * ss;
                if (!Xs.Mouse.Pressed())
                    move_x = false;
            };
            if (move_y[0] or move_y[1]) {
                point.y -= im::GetIO().MouseDelta.y * ss;
                if (!Xs.Mouse.Pressed())
                    move_y = false;
            };
            if (move_z[0] or move_z[1]) {
                if (max.x)
                    point.z -= (im::GetIO().MouseDelta.x - im::GetIO().MouseDelta.y) * ss;
                else
                    point.z += (im::GetIO().MouseDelta.x - im::GetIO().MouseDelta.y) * ss;
                if (!Xs.Mouse.Pressed())
                    move_z = false;
            };
            const auto& fixed_psize = point_size / distance * 2.f;
            const auto& point_size2 = fixed_psize * 1.5f;
            glBindTexture(GL_TEXTURE_2D, 0);
            mLine(x1, x2, v4f(axis_color_red * 0.3f, 0.4f), 2);
            mLine(y1, y2, v4f(axis_color_green * 0.3f, 0.4f), 2);
            mLine(z1, z2, v4f(axis_color_blue * 0.3f, 0.4f), 2);
            Point(1, 10.f / distance, v);
            Point(axis_color_red, if_else(move_x[0], point_size2, fixed_psize), x1);
            Point(axis_color_red, if_else(move_x[1], point_size2, fixed_psize), x2);
            Point(axis_color_green, if_else(move_y[0], point_size2, fixed_psize), y1);
            Point(axis_color_green, if_else(move_y[1], point_size2, fixed_psize), y2);
            Point(axis_color_blue, if_else(move_z[0], point_size2, fixed_psize), z1);
            Point(axis_color_blue, if_else(move_z[1], point_size2, fixed_psize), z2);
            glColor3f(1, 1, 1);
        };
    };
    /*
    void Dragx(const std::string& label, float& v, const float& speed = 0.1f, const float& min = 0.f, const float& max = 0.f, const bool& hide_mouse = true, const bool& loop_mouse = true) {
        im::DragFloat(label.c_str(), &v, speed, min, max);
        static float first_v = v;
        if (im::IsItemClicked())
            first_v = v;
        if (im::IsItemActive()) {
            if (hide_mouse)
                im::SetMouseCursor(ImGuiMouseCursor_::ImGuiMouseCursor_None);
            if (loop_mouse)
                if (im::GetIO().MousePos.x > im::GetWindowPos().x + im::GetWindowSize().x) {
                    v += first_v*2;
                    sf::Mouse::setPosition({(int)im::GetWindowPos().x, (int)mouse.y}, win);
                }
                else if (im::GetIO().MousePos.x < im::GetWindowPos().x)
                    sf::Mouse::setPosition({(int)im::GetWindowPos().x + (int)im::GetWindowSize().x, (int)mouse.y}, win);
        };
    };
    */
    void gui() {
        static const auto& panel_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoBringToFrontOnFocus;
        static const auto& spanel_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus;
        float sag_x = 0;
        if (Sel() != NONE) {
            im::Begin("sag taraf", (bool*)0, spanel_flags);
            Once(im_wsize(500, wn_size.y));
            im_wsize(im_wsize().x, wn_size.y);
            if (im_wsize().x > 500) im_wsize(500, wn_size.y);
            im_wpos(wn_size.x - im_wsize().x, 0);
            sag_x = im_wsize().x;
            sag_taraftaki();
            if (drag_start and !Xs.Mouse.Pressed()) {
                if ((wn_size.x - sag_x) < mouse.x and mouse.y > 0 and mouse.y < win.getSize().y) {
                    if (Sel() == SHAPE) {
                        auto& sh = *eng.shapes.at(Sel.num).value;
                        switch (drag_s()) {
                        case TEXTURE:
                            sh.tex = eng.texs.at(drag_s.num).value;
                            break;
                        case MESH:
                            sh.mesh = eng.meshs.at(drag_s.num).value;
                            break;
                        case ANIM:
                            sh.tex = &eng.anims.at(drag_s.num).value->current();
                            break;
                        };
                    };
                };
                drag_start = false;
            };
            im::End();
        };

        im::Begin("sol taraf", (bool*)0, panel_flags);
        Once(im_wsize(500, wn_size.y));
        im_wpos(0, 0);
        im_wsize(im_wsize().x, wn_size.y);
        if (im_wsize().x > 500) im_wsize(500, wn_size.y);
        const auto& sol_x = im_wsize().x;
        sol_menu();
        sol_taraftaki();
        im::End();

        im::Begin("alt taraf", (bool*)0, panel_flags);
        Once(im_wsize(1000, 500));
        im_wsize(wn_size().x - sol_x - sag_x, im_wsize().y);
        if (im_wsize().y > wn_size.y) im_wsize(im_wsize().x, wn_size.y);
        im_wpos(sol_x, wn_size.y - im_wsize().y);
        mouse_safe = (sol_x < mouse.x) and ((wn_size.x - sag_x) > mouse.x) and (wn_size.y - im_wsize().y > mouse.y);
        alt_tarafki();
        im::End();

        if (file_drag_start and (mouse_safe or (wn_size.x - sag_x) > mouse.x) and !Xs.Mouse.Pressed()) {
            if (drag_path.ends_with(".png") or drag_path.ends_with(".jpg") or drag_path.ends_with(".jpeg")) {
                eng.create(new XsTexture(drag_path), drag_path.substr(drag_path.find_last_of("/\\") + 1));
                if (Sel() == SHAPE and (wn_size.x - sag_x) > mouse.x) {
                    eng.shapes.at(Sel.num).value->tex = eng.texs.back().value;
                }
                else {
                    Sel() = TEXTURE;
                    Sel.num = eng.texs.size() - 1u;
                };
            }
            else if (drag_path.ends_with(".gif")) {
                eng.create(new XsAnim(drag_path), drag_path.substr(drag_path.find_last_of("/\\") + 1));
                if (Sel() == SHAPE and (wn_size.x - sag_x) > mouse.x) {
                    eng.shapes.at(Sel.num).value->tex = &eng.anims.back().value->current();
                }
                else {
                    Sel() = ANIM;
                    Sel.num = eng.anims.size() - 1u;
                };
            }
            else if (drag_path.ends_with(".obj")) {
                eng.create(new XsMesh(Xs.LoadOBJ(drag_path)), drag_path.substr(drag_path.find_last_of("/\\") + 1));
                if (Sel() == SHAPE and (wn_size.x - sag_x) > mouse.x) {
                    eng.shapes.at(Sel.num).value->mesh = eng.meshs.back().value;
                }
                else {
                    Sel() = MESH;
                    Sel.num = eng.meshs.size() - 1u;
                };
            };
            file_drag_start = false;
        };

        im::Begin("debug");
        im::DragFloat("point size", &point_size, 0.1f, 100.f);
        im::DragFloat("gizmo scale", &gizmo_scale, 0.1f, 100.f);
        im::DragFloat("line width", &line_width, 0.1f, 100.f);
        im::ColorPicker3("bg color", *Xs.Sett.BackGround);
        im::DragFloat2("cam rot", *Xs.Editor.Cam.Rot);
        im::DragFloat2("cam spd", *Xs.Editor.Cam.Speed_v, 0.001f);
        static float bg_scale = 100.f, b_scale = 15.f;
        static vex2f v;
        im::JoystickSlider(v, bg_scale, b_scale);
        im::DragFloat("bg scale", &bg_scale, 0.5f, b_scale + 5, 500.f);
        im::DragFloat("b scale", &b_scale, 0.5f, 2, bg_scale - 5);
        im::Text("%f, %f", v.x, v.y);
        im::End();
    };
    void _3d_init() {
        glLoadIdentity();
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glShadeModel(GL_SMOOTH);
    };
    void _2d_init() {
        glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, wn_size.x, 0, wn_size.y, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);
    };
    void Rect(const vex2i& pos, const float& scale) {
        glBegin(GL_QUADS);
        glColor3f(1, 1, 1);
        glTexCoord2f(1, 1);
        glVertex2i(pos.x - scale, pos.y - scale);
        glTexCoord2f(0, 1);
        glVertex2i(pos.x + scale, pos.y - scale);
        glTexCoord2f(0, 0);
        glVertex2i(pos.x + scale, pos.y + scale);
        glTexCoord2f(1, 0);
        glVertex2i(pos.x - scale, pos.y + scale);
        glEnd();
    };
    Texture bulb_tex;
    void bulb_icon(const vex3f& pos) {
        const vex3f& v = glm::projectNO(glm::vec3(pos), cam.viewMatrix(), cam.projectionMatrix(), glm::vec4(0.0f, 0.0f, wn_size.x, wn_size.y));
        const auto& distance = Xs.Math.Distance(pos, cam.pos) / 25.f;
        if ((v.z - 1.f) * 0.5f < 0.f) {
            bulb_tex.bind();
            Rect(v, 25.f / distance);
        };
    };
    void once_start() {
        im::StyleXsDark();
        them = &im::GetStyle();
        cthem = ImGui::GetStyle();
        cam.pos = 10.f;
        Xs.Editor.Cam.Rot = vex2f(-450, 75);
        sf::Image win_icon;
        win_icon.loadFromFile("media/xslogo.png");
        win.setIcon(win_icon.getSize().x, win_icon.getSize().y, win_icon.getPixelsPtr());
        ImGui::GetIO().Fonts->Clear();
        ImGui::GetIO().Fonts->AddFontFromFileTTF("media/font.ttf", 18.f);
        ImGui::SFML::UpdateFontTexture();
        update_dir();
        bulb_tex.load("media/bulb.png");
        textfile_icon.loadFromFile("media/textfile.png");
        folder_icon.loadFromFile("media/folder.png");
        imagefile_icon.loadFromFile("media/imagefile.png");
        model_icon.loadFromFile("media/3dmodel.png");
        defaultfile_icon.loadFromFile("media/defaultfile.png");
        updir_icon.loadFromFile("media/updir.png");
        xsproj_icon.loadFromFile("media/xsproj.png");
        header_icon.loadFromFile("media/header.png");
        source_icon.loadFromFile("media/source.png");
        csource_icon.loadFromFile("media/c_source.png");
        glEnable(GL_BLEND);
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_POINT_SMOOTH);
        Xs.Sett.BackGround = vex3f(0.05f, 0.05f, 0.075f);
        Xs.Editor.Cam.Speed_v = 0.03f;
        eng.create(new Light({-10,10,-10}, XsColor(), 500.f), "Light");
    };
    void play() {
        XsStart(eng, "HELLO WORLD !!") {
            Once(once_start());
            mouse << sf::Mouse::getPosition(win);
            cam.viewport << win.getSize();
            _3d_init();
            /*if (mouse_safe)*/ cam.editor();
            cam.use();
            env();
            eng.play();
            _2d_init();
            XsShader::dis();
            for (const auto& [id, l] : eng.lights)
                bulb_icon(l->pos);
            if (Sel() == SHAPE and !eng.shapes.empty())
                gizmo(eng.shapes.at(Sel.num).value->pos, cam.viewMatrix(), cam.projectionMatrix(), cam.pos, gizmo_scale, point_size, 2.f);
            glLoadIdentity();
            ImBlock(win) {
                im::ShowDemoWindow();
                gui();
            };
        };
    };
private:
    const vex3f& m_fdis = 120.f;
    const vex3f& m_ldis = 2.f;
    const vex3f& axis_color_blue = vex3f(34.f, 207.f, 230.f) / 255.f;
    const vex3f& axis_color_red = vex3f(238.f, 23.f, 23.f) / 255.f;
    const vex3f& axis_color_green = Xs.Color.DarkGreen;
    const ImVec4& im_axis_color_blue = ImVec4(axis_color_blue.x, axis_color_blue.y, axis_color_blue.z, 1.f);
    const ImVec4& im_axis_color_red = ImVec4(axis_color_red.x, axis_color_red.y, axis_color_red.z, 1.f);
    const ImVec4& im_axis_color_green = ImVec4(axis_color_green.x, axis_color_green.y, axis_color_green.z, 1.f);
    inline void Line(const float& x1, const float& y1, const float& z1, const float& x2, const float& y2, const float& z2) { glVertex3f(x1, y1, z1); glVertex3f(x2, y2, z2); };
    inline void Line(const vex3f& v1, const vex3f& v2) { glVertex3f(v1.x, v1.y, v1.z); glVertex3f(v2.x, v2.y, v2.z); };
    inline void Line(const vex2f& v1, const vex2f& v2) { glVertex2f(v1.x, v1.y); glVertex2f(v2.x, v2.y); };
    inline void mLine(const vex2f& v1, const vex2f& v2, const vex4f& color, const float& line_w) {
        glLineWidth(line_w);
        glColor4(color);
        glBegin(GL_LINES);
        Line(v1, v2);
        glEnd();
    };
    inline void mLine(const vex3f& v1, const vex3f& v2, const vex4f& color, const float& line_w) {
        glLineWidth(line_w);
        glColor4(color);
        glBegin(GL_LINES);
        Line(v1, v2);
        glEnd();
    };
    inline void im_wsize(const float& x, const float& y) { im::SetWindowSize({ x, y }); };
    inline void im_wsize(const vex2f& v) { im::SetWindowSize({v.x, v.y}); };
    inline vex2f im_wsize() { return { im::GetWindowSize().x, im::GetWindowSize().y }; };
    inline void im_wpos(const float& x, const float& y) { im::SetWindowPos({ x, y }); };
    inline void im_wpos(const vex2f& v) { im::SetWindowPos({ v.x, v.y }); };
    inline vex2f im_wpos() { return { im::GetWindowPos().x, im::GetWindowPos().y }; };
    inline bool circle_col(const vex2f& point, const float& r, const vex2f& point2) { return sqrtf(pow(point2.x - point.x, 2) + pow(point2.y - point.y, 2)) < r; };
    inline float avg(auto v) { return (v.x + v.y) / 2.f; };
    inline void Point(const vex3f& color, const float& size, const vex3f& pos) {
        glColor3(color);
        glPointSize(size);
        glBegin(GL_POINTS);
        glVertex2(pos);
        glEnd();
    };
    const str& floor_shader_vs = R"(
#version 400
layout(location = 0) in vec3 aPos;

void main() {
    gl_Position = ftransform();
};)";
    const str& floor_shader_fs = R"(
#version 400
out vec4 FragColor;

float near = 0.05f;
float far = 100.0;
float p = 100.0;
uniform vec3 color;
uniform float cam_y;

float linearizeDepth(float depth) {
    float z = depth * 2.0 - 1.0;
    return (2.0 * near * p) / (p + near - z * (p - near));
};

void main() {
    p = far - (far - abs(cam_y));
    float alpha = linearizeDepth(gl_FragCoord.z) / p;
    FragColor = vec4(color, 1 - alpha);
};)";
    XsShader floor_shader = XsShader(floor_shader_vs, floor_shader_fs);
};

auto main() -> int {
    App app;
    app.play();
};
