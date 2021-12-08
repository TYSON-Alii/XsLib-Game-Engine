#include <XsLib.hpp>
#include <deque>
#include <filesystem>

using namespace std;
namespace im = ImGui;

static sf::ContextSettings contextSettings;
static sf::Context context;
static sf::Clock __IMCLOCK__;
static auto _XS_FPS_START = std::chrono::high_resolution_clock::now();

#define XsStart(_Window, _Name) for(([&]() -> void {										\
contextSettings.depthBits = 24;																\
contextSettings.stencilBits = 8;															\
contextSettings.antialiasingLevel = 0;														\
contextSettings.majorVersion = 3;															\
contextSettings.minorVersion = 3;															\
contextSettings.sRgbCapable = false;														\
_Window.create(sf::VideoMode(Xs.Sett.WindowSize.x, Xs.Sett.WindowSize.y), _Name, sf::Style::Default, contextSettings);\
ImGui::SFML::Init(_Window);																	\
glewExperimental = GL_TRUE;																	\
glewInit();																					\
glEnable(GL_TEXTURE_2D);																	\
glEnable(GL_SCISSOR_TEST);																	\
glEnable(GL_DEPTH_TEST);																	\
glEnable(GL_NORMALIZE);																		\
glDepthFunc(GL_LESS);																		\
glShadeModel(GL_SMOOTH);																	\
glBlendFunc(GL_ZERO, GL_SRC_COLOR);															\
glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);					\
glBlendEquation(GL_FUNC_ADD);																\
glLoadIdentity();																			\
}());																						\
																							\
([&]() -> bool {																			\
_XS_FPS_START = std::chrono::high_resolution_clock::now();									\
glClearColor(Xs.Sett.BackGround.x, Xs.Sett.BackGround.y, Xs.Sett.BackGround.z, 1.0);		\
glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);											\
while (_Window.pollEvent(Xs.Event)) {														\
	ImGui::SFML::ProcessEvent(Xs.Event);													\
	if (Xs.Event.type == sf::Event::Closed)													\
		_Window.close();																	\
};																							\
return false;																				\
}() || _Window.isOpen());																	\
																							\
([&]() -> void { _Window.display(); Xs.Fps = (float)1e9 / (float)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - _XS_FPS_START).count(); }()))

static bool __FxsIm = true;
#define ImBlock(_Window) for([&](){ ImGui::SFML::Update(_Window, __IMCLOCK__.restart()); __FxsIm = true; }();__FxsIm;[&](){ _Window.pushGLStates(); ImGui::SFML::Render(_Window); _Window.popGLStates(); __FxsIm = false;}())

/*
if (ImGui::IsItemHovered()) {
    ImGui::BeginTooltip();
    ImGui::Text("I am a fancy tooltip");
    static float arr[] = { 0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f };
    ImGui::PlotLines("Curve", arr, IM_ARRAYSIZE(arr));
    ImGui::EndTooltip();
}
*/

sf::RenderWindow window;
class App {
public:
    App() = default;
    class Camera {
    private:
        glm::mat4 _viewMatrix = glm::mat4(1.f);
    public:
        Camera() = default;
        vex3f pos = 0;
        vex3f rot = 0;
        inline glm::mat4 projectionMatrix() const { return glm::perspective(45.f, (float)window.getSize().x / (float)window.getSize().y, 0.2f, 100.f); };
        inline glm::mat4 viewMatrix() const { return _viewMatrix; };
        inline glm::mat4& viewMatrix() { return _viewMatrix; };
    };
    Camera cam;
    string last_load_filename;
    void SaveProj(const std::string& filename) {
        json j;
        for (auto& i : XsEngine.Camera.__data__())
            j["Cameras"][i.name] = { {"name", i.name}, {"pos", {i.pos.x, i.pos.y, i.pos.z}},{"rot", {i.rot.x, i.rot.y, i.rot.z}} };
        for (auto& i : XsEngine.Shape())
            j["Shapes"][i.name] = { {"name", i.name}, {"pos", {i.pos.x, i.pos.y, i.pos.z}},{"rot", {i.rot.x, i.rot.y, i.rot.z}},{"scale", {i.scale.x,i.scale.y,i.scale.z}},{"origin",{i.origin.x,i.origin.y,i.origin.z}},{"color",{i.color.x,i.color.y,i.color.z,i.color.w}},{"line width", i.lineWidth},{"point size",i.pointSize},{"hide", i.hide},{"mesh",i.npos},{"tex",i.npos} };
        std::ofstream o(filename);
        o << std::setw(4) << j;
        o.close();
        log << "Project Saved. ("s + filename + ')';
    };
    void LoadProj(const std::string& filename) {
        std::ifstream i(filename);
        if (i.is_open()) {
            json j;
            i >> j;
            for (auto& i : j["Shapes"]) {
                XsShape t(i["name"]);
                t.pos = vex3f(float(i["pos"][0]), float(i["pos"][1]), float(i["pos"][2]));
                t.rot = vex3f(float(i["rot"][0]), float(i["rot"][1]), float(i["rot"][2]));
                t.scale = vex3f(float(i["scale"][0]), float(i["scale"][1]), float(i["scale"][2]));
                t.origin = vex3f(float(i["origin"][0]), float(i["origin"][1]), float(i["origin"][2]));
                t.color = vex4f(float(i["color"][0]), float(i["color"][1]), float(i["color"][2]), float(i["color"][3]));
                t.hide = bool(i["hide"]);
                t.lineWidth = float(i["line width"]);
                t.pointSize = float(i["point size"]);
                t.mesh = size_t(i["mesh"]);
                t.tex = size_t(i["tex"]);
                XsEngine.Shape.New(t.name) = t;
            };
            for (auto& i : j["Cameras"]) {
                XsCamera t(i["name"]);
                t.pos = vex3f(float(i["pos"][0]), float(i["pos"][1]), float(i["pos"][2]));
                t.rot = vex3f(float(i["rot"][0]), float(i["rot"][1]), float(i["rot"][2]));
                XsEngine.Camera.New(t);
            };
            last_load_filename = filename;
            log << "Project Load. ("s + filename + ')';
        }
        else {
            std::cerr << "Project Cannot Load.";
            log << "Project Cannot Load.";
        };
    };
    XsShader floor_shader;
    const std::string floor_shader_vs = R"(
#version 400
layout(location = 0) in vec3 aPos;

void main() {
    gl_Position = ftransform();
};)";
    const std::string floor_shader_fs = R"(
#version 400
out vec4 FragColor;

float near = 0.20;
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
    vex3b show_axis = true;
    bool show_floor = true;
    bool show_extra_tex = true;
    const vex3f axis_color_blue = vex3f(34.f, 207.f, 230.f) / 255.f;
    const vex3f axis_color_red = vex3f(238.f, 23.f, 23.f) / 255.f;
    const vex3f axis_color_green = Xs.Color.DarkGreen;
    const ImVec4 im_axis_color_blue = ImVec4(axis_color_blue.x, axis_color_blue.y, axis_color_blue.z, 1.f);
    const ImVec4 im_axis_color_red = ImVec4(axis_color_red.x, axis_color_red.y, axis_color_red.z, 1.f);
    const ImVec4 im_axis_color_green = ImVec4(axis_color_green.x, axis_color_green.y, axis_color_green.z, 1.f);
    const vex3f m_fdis = 110.f;
    const vex3f m_ldis = 2.f;
    void draw_floor(XsShader& v) {
        glDisable(GL_TEXTURE_2D);
        glDepthFunc(GL_ALWAYS);
        glDepthMask(GL_FALSE);
        glLoadIdentity();
        v.use();
        v("projection", cam.projectionMatrix());
        v("view", cam.viewMatrix());
        v("color", vex3f(0.85f, 0.85f, 0.875f));
        v("cam_y", cam.pos.y);
        if (3 > fabs(cam.pos.y))
            glLineWidth(4.1 - fabs(cam.pos.y));
        else
            glLineWidth(1);
        if (show_floor) {
            glTranslatef(ceil(cam.pos.x / 2) * 2, 0, ceil(cam.pos.z / 2) * 2);
            glBegin(GL_LINES);
            rep(m_ldis.x * m_fdis.z, 2.f)
                if ((ceil(cam.pos.z / 2) * 2) + m_fdis.z - i != 0 or !show_axis.x)
                    Xs.Line(m_fdis.x, 0, m_fdis.z - i, -m_fdis.x, 0, m_fdis.z - i);
            glEnd();

            glBegin(GL_LINES);
            rep(m_ldis.z * m_fdis.x, 2.f)
                if ((ceil(cam.pos.x / 2) * 2) + m_fdis.x - i != 0 or !show_axis.y)
                    Xs.Line(m_fdis.x - i, 0, m_fdis.z, m_fdis.x - i, 0, -m_fdis.z);
            glEnd();
        };

        glLoadIdentity();
        if (4 > fabs(cam.pos.y))
            glLineWidth(5.1 - fabs(cam.pos.y));
        else
            glLineWidth(2);
        if (show_axis.z) {
            v("color", axis_color_blue);
            glBegin(GL_LINES);
            Xs.Line(0, 0, m_fdis.z + cam.pos.z, 0, 0, -m_fdis.z + cam.pos.z);
            glEnd();
        }
        if (show_axis.x) {
            v("color", axis_color_red);
            glBegin(GL_LINES);
            Xs.Line(m_fdis.x + cam.pos.x, 0, 0, -m_fdis.x + cam.pos.x, 0, 0);
            glEnd();
        }
        if (show_axis.y) {
            v("color", axis_color_green);
            glBegin(GL_LINES);
            Xs.Line(0, m_fdis.y + cam.pos.y, 0, 0, -m_fdis.y + cam.pos.y, 0);
            glEnd();
        }
        v.disuse();
        glEnable(GL_TEXTURE_2D);
        glDepthFunc(GL_LESS);
        glDepthMask(GL_TRUE);
    };
    void DefaultCamera(XsCamera& cam) {
        glViewport(0, 0, wn_size.x, wn_size.y);
        glScissor(0, 0, wn_size.x, wn_size.y);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glm::mat4 pmx = glm::perspective(45.f, (float)wn_size.x / (float)wn_size.y, 0.2f, 100.f);
        glm::mat4 tmx = glm::translate(glm::mat4(1.f), glm::vec3(-cam.pos.x, -cam.pos.y + 1.f, -cam.pos.z));
        glm::vec3 position = glm::normalize(glm::vec3(0.f, 1.f, 0.f));
        glm::vec3 t_rot;
        t_rot.x = cam.rot.x;
        t_rot.y = cam.rot.y;
        t_rot.z = cam.rot.z;
        const glm::vec3 rott = glm::normalize(t_rot);
        const glm::vec3 right = glm::normalize(glm::cross(rott, position));
        const glm::vec3 up = glm::normalize(glm::cross(right, rott));
        XsEngine.Camera().viewMatrix() = glm::lookAt(position, position + rott, up);
        const glm::mat4 _ftransform = pmx * XsEngine.Camera().viewMatrix() * tmx;
        glLoadMatrixf(&_ftransform[0][0]);
        glMatrixMode(GL_MODELVIEW);
    };
    void FPSCamera(Camera& cam, vex2f _mouse_pos, float _sensivity) {
        float _yaw = _mouse_pos.x * _sensivity;
        float _pitch = (_mouse_pos.y * _sensivity > 89.9f) ? 89.9f : (_mouse_pos.y * _sensivity < -89.9f) ? -89.9f : (_mouse_pos.y * _sensivity);
        glViewport(0, 0, wn_size.x, wn_size.y);
        glScissor(0, 0, wn_size.x, wn_size.y);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glm::mat4 pmx = glm::perspective(45.f, (float)wn_size.x / (float)wn_size.y, 0.2f, 100.f);
        glm::mat4 tmx = glm::translate(glm::mat4(1.f), glm::vec3(-cam.pos.x, -cam.pos.y + 1, -cam.pos.z));
        glm::vec3 position = glm::normalize(glm::vec3(0, 1, 0));
        glm::vec3 t_rot = glm::vec3(0, 0, 0);
        t_rot.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
        t_rot.y = -sin(glm::radians(_pitch));
        t_rot.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
        glm::vec3 rott = glm::normalize(t_rot);
        glm::vec3 right = glm::normalize(glm::cross(rott, position));
        glm::vec3 up = glm::normalize(glm::cross(right, rott));
        cam.viewMatrix() = glm::lookAt(position, position + rott, up);
        glm::mat4 xs_fullTransform_ = pmx * cam.viewMatrix() * tmx;
        cam.rot.x = t_rot.x;
        cam.rot.y = t_rot.y;
        cam.rot.z = t_rot.z;
        glLoadMatrixf(&xs_fullTransform_[0][0]);
        glMatrixMode(GL_MODELVIEW);
    };
    void EditorCamera(Camera& cam, const float sensivity = 0.3f) {
        static vex2f last_mouse_pos = 0.f;
        static bool mouse_press = false;
        if (Xs.KeyPressed(Xs.Mouse.Button.Right)) {
            if (Xs.Event.type == 8) {
                if (Xs.Event.mouseWheelScroll.delta == 1)	Xs.Editor.Cam.Speed_v += 0.0001f;
                else if (Xs.Event.mouseWheelScroll.delta == -1)	Xs.Editor.Cam.Speed_v -= 0.0001f;

                if (Xs.Editor.Cam.Speed_v < 0.0001f) Xs.Editor.Cam.Speed_v = 0.0001f;
            }
            if (Xs.KeyPressed(Xs.Key.W) && !Xs.KeyPressed(Xs.Key.Space))
                Xs.Editor.Cam.Speed += cam.rot * (Xs.Editor.Cam.Speed_v);
            else if (Xs.KeyPressed(Xs.Key.S) && !Xs.KeyPressed(Xs.Key.Space))
                Xs.Editor.Cam.Speed -= cam.rot * (Xs.Editor.Cam.Speed_v);
            const vex2f f_pos = Xs.Mouse.Pos() - last_mouse_pos;
            const vex2f sm_pos = Xs.Editor.Cam.Rot + f_pos;
            Xs.Editor.Cam.RotVel = (sm_pos - Xs.Editor.Cam.Rot) / 17.5;
            last_mouse_pos += Xs.Editor.Cam.RotVel;
        }
        else
            mouse_press = false;
        if (mouse_press == false) {
            last_mouse_pos = Xs.Mouse.Pos();
            mouse_press = true;
        };
        if (!Xs.KeyPressed(Xs.Key.S) && !Xs.KeyPressed(Xs.Key.W))
            Xs.Editor.Cam.Speed *= 0.95;
        if (Xs.KeyPressed(Xs.Key.Space))
            Xs.Editor.Cam.Speed *= 0.75f;
        cam.pos += Xs.Editor.Cam.Speed;
        Xs.Editor.Cam.RotVel *= 0.88;
        Xs.Editor.Cam.Rot += Xs.Editor.Cam.RotVel;
        FPSCamera(cam, Xs.Editor.Cam.Rot, sensivity);
    };
    void cam_sett() {
        if (preview_c)
            DefaultCamera(*preview_cam);
        else
            EditorCamera(cam, 0.3f);
    };
    void once() {
        ImGui::GetIO().Fonts->Clear();
        ImGui::GetIO().Fonts->AddFontFromFileTTF("data/font.ttf", 18.f);
        ImGui::SFML::UpdateFontTexture();
        glEnable(GL_BLEND);
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_POINT_SMOOTH);
        Xs.Sett.BackGround = vex3f(0.05f, 0.05f, 0.075f);
        Xs.Editor.Cam.Speed_v = 0.03f;
        cam.pos = 10;
        for (const auto& i : std::filesystem::directory_iterator(path))
            directorys.push_back(Dir_t(i.path().string(), i.is_directory()));
        textfile_icon.loadFromFile("data/textfile.png");
        folder_icon.loadFromFile("data/folder.png");
        imagefile_icon.loadFromFile("data/imagefile.png");
        model_icon.loadFromFile("data/3dmodel.png");
        defaultfile_icon.loadFromFile("data/defaultfile.png");
        updir_icon.loadFromFile("data/updir.png");
        floor_shader = XsShader(floor_shader_vs, floor_shader_fs);
        im::StyleXsDark();
        them = &im::GetStyle();
        cthem = ImGui::GetStyle();
        mesh_names[0] = strdup_None;
        log << "Start Engine.";
    };
    vex2i wn_size = 0;
    inline void im_wsize(float x, float y) { im::SetWindowSize({ x, y }); };
    inline void im_wsize(vex2f v) { im::SetWindowSize({v.x, v.y}); };
    inline vex2f im_wsize() { return vex2f(im::GetWindowSize().x, im::GetWindowSize().y); };
    inline void im_wpos(float x, float y) { im::SetWindowPos({ x, y }); };
    inline void im_wpos(vex2f v) { im::SetWindowPos({ v.x, v.y }); };
    inline vex2f im_wpos() { return vex2f(im::GetWindowPos().x, im::GetWindowPos().y); };
    float im_wlog = 0.f, im_rpanel = 0.f, im_hlog = 0.f;
    enum Selected_t { NONE, SHAPE, CAMERA, TEXTURE, MESH };
    struct {
        vector<string> data;
        inline auto& operator()() { return data; };
        void operator<<(const string& text) { data.push_back(text); };
    } log;
    struct {
        Selected_t s = NONE;
        int num = 0;
        inline Selected_t& operator()() { return s; };
    } Sel;
    size_t left_camera = 0u, left_shape = 0u, left_tex = 0u, left_mesh = 0u;
    char* strdup_None = _strdup("None");
    char* strdup_Create_New = _strdup("Create New++");
    char** mesh_names = new char* [1u];
    std::string name_str;
    bool change_name = false, change_cam_name = false, change_mesh_name = false;
    XsEnum __XS_last_load_vert_mode__ = Xs.Enum.Vertex;
    std::string __XS_last_load_vert_filename__ = "";
    ImGuiStyle* them = nullptr;
    ImGuiStyle cthem;
    bool redButton(const std::string& label) {
        them->Colors[ImGuiCol_Button] = ImVec4(Xs.Color.Red.x, Xs.Color.Red.y, Xs.Color.Red.z, 0.726);
        them->Colors[ImGuiCol_ButtonActive] = ImVec4(Xs.Color.Red.x, Xs.Color.Red.y, Xs.Color.Red.z, 0.886);
        them->Colors[ImGuiCol_ButtonHovered] = ImVec4(Xs.Color.Red.x, Xs.Color.Red.y, Xs.Color.Red.z, 0.986);
        const bool b = im::Button("Delete");
        *them = cthem;
        return b;
    };
    void info_shape(XsShape& v) {
        if (!change_name)
            name_str = v.name;
        if (im::InputText("Name", &name_str, ImGuiInputTextFlags_EnterReturnsTrue))
            if (std::find(XsEngine.Shape.Names().begin(), XsEngine.Shape.Names().end(), name_str.data()) == XsEngine.Shape.Names().end())
                v.name = name_str;
        change_name = im::IsItemActive();
        im::DragFloat3("Position", v.pos, 0.01f, -FLT_MAX, FLT_MAX);
        im::DragFloat3("Rotation", v.rot, 0.5f, -FLT_MAX, FLT_MAX);
        im::DragFloat3("Scale", v.scale, 0.01f, -FLT_MAX, FLT_MAX);
        im::DragFloat3("Origin", v.origin, 0.01f, -FLT_MAX, FLT_MAX);
        im::ColorPicker4("Color", v.color);
        if (v.mesh != v.npos and v.getMesh().poly == GL_LINES)
            im::SliderFloat("Line Width", &v.lineWidth, 0.01f, 10.f);
        else if (v.mesh != v.npos and v.getMesh().poly == GL_POINTS)
            im::SliderFloat("Point Size", &v.pointSize, 0.01f, 10.f);
        im::Checkbox("Hide", &v.hide);

        if (im::TreeNode("Mesh")) {
            int _XSIMVERTC_ = (v.mesh == v.npos) ? 0 : v.mesh + 1u;
            vector<char*> _t;
            _t.push_back(strdup_None);
            _t.insert(_t.end(), XsEngine.Mesh.Names().begin(), XsEngine.Mesh.Names().end());
            _t.push_back(strdup_Create_New);
            const auto& _tsv = &_t[0];
            if (im::Combo("Mesh ", &_XSIMVERTC_, _tsv, _t.size())) {
                if (_XSIMVERTC_ == _t.size() - 1u) {
                    XsEngine.Mesh.New("Mesh "s + to_string(left_mesh++));
                    v.mesh = XsEngine.Mesh().size() - 1u;
                }
                else
                    v.mesh = (_XSIMVERTC_ == 0) ? v.npos : _XSIMVERTC_ - 1u;
            };
            if (v.mesh != v.npos) {
                auto& m = v.getMesh();
                _XSIMVERTC_ = (m.mode == Xs.Enum.Vertex) ? 0 : (m.mode == Xs.Enum.VertexAndTexture) ? 1 : (m.mode == Xs.Enum.VertexAndNormal) ? 2 : (m.mode == Xs.Enum.All) ? 3 : 0;
                im::Combo("Xs Mode", &_XSIMVERTC_, Xs.Values.XsModeNames, 4);
                m.mode = (_XSIMVERTC_ == 0) ? Xs.Enum.Vertex : (_XSIMVERTC_ == 1) ? Xs.Enum.VertexAndTexture : (_XSIMVERTC_ == 2) ? Xs.Enum.VertexAndNormal : (_XSIMVERTC_ == 3) ? Xs.Enum.All : Xs.Enum.Vertex;
                _XSIMVERTC_ = (m.poly == GL_POINTS) ? 0 : (m.poly == GL_LINES) ? 1 : (m.poly == GL_TRIANGLES) ? 2 : (m.poly == GL_QUADS) ? 3 : (m.poly == GL_POLYGON) ? 4 : 0;
                im::Combo("GL Mode", &_XSIMVERTC_, Xs.Values.GlModeNames, 5);
                m.poly = (_XSIMVERTC_ == 0) ? Xs.Enum.Point : (_XSIMVERTC_ == 1) ? Xs.Enum.Line : (_XSIMVERTC_ == 2) ? Xs.Enum.Triangle : (_XSIMVERTC_ == 3) ? Xs.Enum.Quad : Xs.Enum.Polygon;
                if (im::TreeNode("Load")) {
                    _XSIMVERTC_ = (__XS_last_load_vert_mode__ == Xs.Enum.Vertex) ? 0 : (__XS_last_load_vert_mode__ == Xs.Enum.VertexAndTexture) ? 1 : (__XS_last_load_vert_mode__ == Xs.Enum.VertexAndNormal) ? 2 : (__XS_last_load_vert_mode__ == Xs.Enum.All) ? 3 : 0;
                    ImGui::Combo("Load Mode", &_XSIMVERTC_, Xs.Values.XsModeNames, 4);
                    __XS_last_load_vert_mode__ = (_XSIMVERTC_ == 0) ? Xs.Enum.Vertex : (_XSIMVERTC_ == 1) ? Xs.Enum.VertexAndTexture : (_XSIMVERTC_ == 2) ? Xs.Enum.VertexAndNormal : (_XSIMVERTC_ == 3) ? Xs.Enum.All : Xs.Enum.Vertex;
                    ImGui::InputText("File Name", &__XS_last_load_vert_filename__);
                    if (ImGui::Button("Open File Dialog")) {
                        auto s = pfd::open_file::open_file("Select File", filesystem::current_path().string(), { "Obj", "*.obj" }, pfd::opt::none).result();
                        if (!s.empty())
                            __XS_last_load_vert_filename__ = s[0];
                    };
                    if (ImGui::Button("Load")) {
                        m.data = Xs.LoadOBJ(__XS_last_load_vert_filename__.c_str(), __XS_last_load_vert_mode__);
                        m.mode = __XS_last_load_vert_mode__;
                    };
                    im::TreePop();
                };
            };
            im::TreePop();
        };
        if (im::TreeNode("Texture")) {
            int _XSIMVERTC_ = (v.tex == v.npos) ? 0 : v.tex + 1u;
            vector<char*> _t;
            _t.push_back(strdup_None);
            _t.insert(_t.end(), XsEngine.Texture.Names().begin(), XsEngine.Texture.Names().end());
            _t.push_back(strdup_Create_New);
            const auto& _tsv = &_t[0];
            if (im::Combo("Texture ", &_XSIMVERTC_, _tsv, _t.size())) {
                if (_XSIMVERTC_ == _t.size()-1u) {
                    XsEngine.Texture.New("Texture "s + to_string(left_tex++));
                    v.tex = XsEngine.Texture().size() - 1u;
                }
                else
                    v.tex = (_XSIMVERTC_ == 0) ? v.npos : _XSIMVERTC_ - 1u;
            }
            if (v.tex != v.npos) {
                auto& m = v.getTexture();
                if (m.isLoad()) {
                    vex2f _t = m.scale();
                    _t.normalize();
                    ImGui::Image((void*)m.data, ImVec2(ImGui::GetWindowSize().x * 0.4f, ImGui::GetWindowSize().x * _t.y * 0.4f));
                    ImGui::Text(("File Name: "s + m.fileName()).c_str());
                    ImGui::Text(("Size: x = "stx + m.scale().x + ", y = " + m.scale().y).c_str());
                };
                if (ImGui::Button("Load")) {
                    auto s = pfd::open_file::open_file("Select File", filesystem::current_path().string(), { "Image Files", "*.png *.jpg *.jpeg *.gif" }, pfd::opt::none).result();
                    if (!s.empty())
                        m.load(s[0]);
                };
            };
            im::TreePop();
        };
        redButton("Delete");
        if (im::IsItemClicked() and im::GetIO().MouseDoubleClicked[0]) {
            const auto n = v.name;
            if (XsEngine.Shape.Del(Sel.num)) {
                Sel() = NONE;
                Sel.num = 0u;
                log << "Delete Shape. ("s + n + ')';
            };
        };
    }
    XsCamera* preview_cam = nullptr;
    bool preview_c = false;
    void info_cam(XsCamera& v) {
        if (!change_cam_name)
            name_str = v.name;
        if (im::InputText("Name", &name_str, ImGuiInputTextFlags_EnterReturnsTrue))
            if (std::find(XsEngine.Camera.Names().begin(), XsEngine.Camera.Names().end(), name_str.data()) == XsEngine.Camera.Names().end())
                v.name = name_str;
        change_cam_name = im::IsItemActive();
        im::DragFloat3("Position", v.pos, 0.01f, -FLT_MAX, FLT_MAX);
        im::DragFloat3("Rotation", v.rot, 0.5f, -FLT_MAX, FLT_MAX);
        
        im::BeginMenuBar();
        if (im::BeginMenu("Set")) {
            if (im::MenuItem("Look")) {
                v.pos = cam.pos;
                v.rot = cam.rot;
            };
            if (im::BeginMenu("Cameras")) {
                for (const auto& i : XsEngine.Camera.__data__())
                    if (im::MenuItem(i.name.c_str()))
                        v = i;
                ImGui::EndMenu();
            };
            im::EndMenu();
        };
        im::EndMenuBar();

        //if (im::GetIO().MouseClicked[1] and mouse_pos.x > wn_size.x - im::GetWindowSize().x)// and im::IsWindowFocused())
        //    im::OpenPopup("dfsfdsf");
        //if (im::BeginPopup("dfsfdsf")) {
        //    if (im::BeginMenu("Copy From")) {
        //        if (im::BeginMenu("Cameras")) {
        //            for (const auto& i : XsEngine.Camera.__data__())
        //                if (im::MenuItem(i.name.c_str()))
        //                    v = i;
        //            ImGui::EndMenu();
        //        };
        //        ImGui::EndMenu();
        //    }
        //    ImGui::EndPopup();
        //};
        redButton("Delete");
        if (im::IsItemClicked() and im::GetIO().MouseDoubleClicked[0]) {
            const auto n = v.name;
            if (XsEngine.Camera.Del(Sel.num)) {
                Sel() = NONE;
                Sel.num = 0u;
                log << "Delete Shape. ("s + n + ')';
            };
        };
    };
    void info_mesh(XsMesh& v) {
        if (!change_mesh_name)
            name_str = v.name;
        if (im::InputText("Name", &name_str, ImGuiInputTextFlags_EnterReturnsTrue))
            if (std::find(XsEngine.Mesh.Names().begin(), XsEngine.Mesh.Names().end(), name_str.data()) == XsEngine.Mesh.Names().end())
                v.name = name_str;
        change_mesh_name = im::IsItemActive();

        im::BeginMenuBar();
        if (im::BeginMenu("Solid")) {
            if (im::MenuItem("Plane")) {
                v.data = Xs.Vert.Plane.Default;
                v.mode = Xs.Enum.Vertex;
                v.poly = Xs.Enum.Quad;
            }
            if (im::MenuItem("Cube")) {
                v.data = Xs.Vert.Cube.Default;
                v.mode = Xs.Enum.Vertex;
                v.poly = Xs.Enum.Triangle;
            }
            if (im::MenuItem("Single Point")) {
                v.data = { 0.f,0.f,0.f };
                v.mode = Xs.Enum.Vertex;
                v.poly = Xs.Enum.Point;
            }
            im::EndMenu();
        };
        im::EndMenuBar();

        int _XSIMVERTC_ = (v.mode == Xs.Enum.Vertex) ? 0 : (v.mode == Xs.Enum.VertexAndTexture) ? 1 : (v.mode == Xs.Enum.VertexAndNormal) ? 2 : (v.mode == Xs.Enum.All) ? 3 : 0;
        im::Combo("Xs Mode", &_XSIMVERTC_, Xs.Values.XsModeNames, 4);
        v.mode = (_XSIMVERTC_ == 0) ? Xs.Enum.Vertex : (_XSIMVERTC_ == 1) ? Xs.Enum.VertexAndTexture : (_XSIMVERTC_ == 2) ? Xs.Enum.VertexAndNormal : (_XSIMVERTC_ == 3) ? Xs.Enum.All : Xs.Enum.Vertex;
        _XSIMVERTC_ = (v.poly == GL_POINTS) ? 0 : (v.poly == GL_LINES) ? 1 : (v.poly == GL_TRIANGLES) ? 2 : (v.poly == GL_QUADS) ? 3 : (v.poly == GL_POLYGON) ? 4 : 0;
        im::Combo("Poly Mode", &_XSIMVERTC_, Xs.Values.GlModeNames, 5);
        v.poly = (_XSIMVERTC_ == 0) ? Xs.Enum.Point : (_XSIMVERTC_ == 1) ? Xs.Enum.Line : (_XSIMVERTC_ == 2) ? Xs.Enum.Triangle : (_XSIMVERTC_ == 3) ? Xs.Enum.Quad : Xs.Enum.Polygon;
        if (im::TreeNode("Load")) {
            _XSIMVERTC_ = (__XS_last_load_vert_mode__ == Xs.Enum.Vertex) ? 0 : (__XS_last_load_vert_mode__ == Xs.Enum.VertexAndTexture) ? 1 : (__XS_last_load_vert_mode__ == Xs.Enum.VertexAndNormal) ? 2 : (__XS_last_load_vert_mode__ == Xs.Enum.All) ? 3 : 0;
            ImGui::Combo("Load Mode", &_XSIMVERTC_, Xs.Values.XsModeNames, 4);
            __XS_last_load_vert_mode__ = (_XSIMVERTC_ == 0) ? Xs.Enum.Vertex : (_XSIMVERTC_ == 1) ? Xs.Enum.VertexAndTexture : (_XSIMVERTC_ == 2) ? Xs.Enum.VertexAndNormal : (_XSIMVERTC_ == 3) ? Xs.Enum.All : Xs.Enum.Vertex;
            ImGui::InputText("File Name", &__XS_last_load_vert_filename__);
            if (ImGui::Button("Open File Dialog! ")) {
                auto s = pfd::open_file::open_file("Select File", filesystem::current_path().string(), { "Obj", "*.obj" }, pfd::opt::none).result();
                if (!s.empty())
                    __XS_last_load_vert_filename__ = s[0];
            };
            if (ImGui::Button("Load!")) {
                v.data = Xs.LoadOBJ(__XS_last_load_vert_filename__.c_str(), __XS_last_load_vert_mode__);
                v.mode = __XS_last_load_vert_mode__;
            };
            im::TreePop();
        };

        redButton("Delete");
        if (im::IsItemClicked() and im::GetIO().MouseDoubleClicked[0]) {
            const auto n = v.name;
            if (XsEngine.Mesh.Del(Sel.num)) {
                Sel() = NONE;
                Sel.num = 0u;
                log << "Delete Shape. ("s + n + ')';
            };
        };
    };
    void sf_gui() {
        static sf::RectangleShape cam_rect(sf::Vector2f(50.f, 50.f));
        static sf::Texture cam_tex0, cam_tex1;
        Once(cdsfsdfsfsd) {
            cam_tex0.loadFromFile("data/cam_icon0.png");
            cam_tex1.loadFromFile("data/cam_icon1.png");
            cam_rect.setTexture(&cam_tex0);
            vex2f s(cam_tex0.getSize().x, cam_tex0.getSize().y);
            s.normalize() *= 25.f;
            cam_rect.setSize({s.x, s.y});
        };
        if (Sel() == CAMERA) {
            cam_rect.setPosition({ im_wlog + 15, 15 });
            if (mouse_pos.x > im_wlog + 15 and mouse_pos.x < im_wlog + 40 and mouse_pos.y > 15 and mouse_pos.y < 40)
                if (im::GetIO().MouseClicked[0])
                    if (preview_c) {
                        preview_cam = nullptr;
                        preview_c = false;
                        cam_rect.setTexture(&cam_tex0);
                    }
                    else {
                        preview_cam = &XsEngine.Camera[Sel.num];
                        preview_c = true;
                        cam_rect.setTexture(&cam_tex1);
                    };
            window.pushGLStates();
            window.draw(cam_rect);
            window.popGLStates();
        };
    };
    void cli(const std::string& command) {
        stringstream ss;
        ss << command;
        vector<string> coms;
        string t;
        while (ss >> t)
            coms.push_back(t);
        const auto& len = coms.size();
        if (len != 0u) {
            const auto& first = coms[0u];
            if (len == 1u) {
                if (first == "exit") {
                    SaveProj(last_load_filename);
                    window.close();
                }
                else if (first == "abort")
                    window.close();
                else if (first == "save")
                    if (last_load_filename.size() > 0u)
                        SaveProj(last_load_filename);
            }
            //else{
            //    if (first == "set") {
            //        if (coms[1u] == "shape")
            //            if (XsEngine.Shape.Check(coms[2u])) {
            //                if (coms[3u] == "pos") {
            //                    auto& s = XsEngine.Shape[coms[2u]].pos;
            //                }
            //                else if (coms[3u] == "rot") {
            //                    auto& s = XsEngine.Shape[coms[2u]].rot;
            //                }
            //                else if (coms[3u] == "scale") {
            //                    auto& s = XsEngine.Shape[coms[2u]].rot;
            //                }
            //                else if (coms[3u] == "origin") {
            //                    auto& s = XsEngine.Shape[coms[2u]].rot;
            //                }
            //                else if (coms[3u] == "color") {
            //                    auto& s = XsEngine.Shape[coms[2u]].rot;
            //                }
            //            }
            //    }
            //};
        }
    };
    XsChrono fps_timer;
    int view_fps = 0;
    short alt_panel = 0; // 0 log, 1 file browser
    struct Dir_t {
        Dir_t() {};
        Dir_t(std::string p, bool d) {
            path = p;
            is_directory = d;
        };
        std::string path;
        bool is_directory;
    };
    vector<Dir_t> directorys;
    string path = filesystem::current_path().string(), path_str;
    bool change_path = false;
    sf::Texture folder_icon, model_icon, imagefile_icon, textfile_icon, defaultfile_icon, updir_icon;
    float icon_size = 1.f;
    bool preview = false;
    sf::Texture* preview_tex = nullptr;
    bool type_load = false;
    string load_filepath;
    /*
    struct icon_type{
        icon_type(const std::string& _format, sf::Texture _tex) {
            format = _format;
            tex = _tex;
        };
        string format;
        sf::Texture tex;
    };
    vector<icon_type> file_icons = { {".png", imagefile_icon}, {".obj", model_icon} };
    void yarrak(string& _path, float _icon_size, sf::Texture* up_directory_icon = nullptr, sf::Texture* folder_icon = nullptr, sf::Texture* default_file_icon = nullptr, vector<icon_type> icons = {}) {
        static sf::Texture white_tex;
        static string path_str;
        static bool change_path = false;
        if (ImGui::ImageButton((up_directory_icon == nullptr) ? white_tex : *up_directory_icon, { 20, 20 })) {
            _path = _path.substr(0, _path.find_last_of("/\\"));
            directorys.clear();
            for (const auto& i : std::filesystem::directory_iterator(_path))
                directorys.push_back(Dir_t(i.path().string(), i.is_directory()));
        };
        ImGui::SameLine(48, -50);
        ImGui::ImageButton(folder_icon, { 20, 20 });
        ImGui::SameLine(80, -100);
        if (!change_path)
            path_str = path;
        if (im::InputText("Path", &path_str, ImGuiInputTextFlags_EnterReturnsTrue)) {
            DWORD ftyp = GetFileAttributesA(path_str.c_str());
            if (ftyp != INVALID_FILE_ATTRIBUTES && (ftyp & FILE_ATTRIBUTE_DIRECTORY)) {
                path = path_str;
                directorys.clear();
                for (const auto& i : std::filesystem::directory_iterator(path))
                    directorys.push_back(Dir_t(i.path().string(), i.is_directory()));
            }
        }
        change_path = im::IsItemActive();
        int j = 0;
        for (const auto& i : directorys) {
            if (i.is_directory) {
                ImGui::ImageButton(folder_icon, { 93 * icon_size, 90 * icon_size });
                if (ImGui::IsItemHovered()) {
                    if (ImGui::IsMouseDoubleClicked(0)) {
                        path = i.path;
                        directorys.clear();
                        for (const auto& i : std::filesystem::directory_iterator(path))
                            directorys.push_back(Dir_t(i.path().string(), i.is_directory()));
                    }
                    else {
                        ImGui::BeginTooltip();
                        ImGui::Text(path.c_str());
                        ImGui::EndTooltip();
                    };
                }
            }
            else {
                ImGui::ImageButton(i.path.ends_with(".png") ? imagefile_icon : i.path.ends_with(".obj") ? model_icon : textfile_icon, { 93 * icon_size, 90 * icon_size });
                if (ImGui::IsItemHovered()) {
                    ImGui::BeginTooltip();
                    ImGui::Text(path.c_str());
                    ImGui::EndTooltip();
                };
            }
            j++;
            if ((50 * icon_size * j + (5 * (j + 1))) > ImGui::GetWindowSize().x - (50 * icon_size * (j + 1) + (5 * ((j + 1) + 1))))
                j = 0;
            if (j != 0)
                ImGui::SameLine(50 * icon_size * j + (5 * (j + 1)) + 3, 50 * icon_size * j);
        }
    }
    */
    void ui() {
        if (show_extra_tex) {
            im::Begin("general settings", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoTitleBar);
            im::SetWindowPos({ im_wlog, -5 });
            im::SetWindowSize({ 300, 200 });
            if (true) {
                const auto& s = "pos x: "stx + int(cam.pos.x) + " y: " + int(cam.pos.y) + " z: " + int(cam.pos.z);
                const auto& sr = "rot x: "stx + cam.rot.x + " y: " + cam.rot.y + " z: " + cam.rot.z;
                im::Text(s.c_str());
                im::Text(sr.c_str());
            };
            if (XsLimiter(fps_timer, 0.1f))
                view_fps = int(Xs.Fps);
            im::PushStyleColor(ImGuiCol_Text, ImVec4(Xs.Color.Yellow.x, Xs.Color.Yellow.y, Xs.Color.Yellow.z, 0.76));
            im::Text(("fps: "s + std::to_string(view_fps)).c_str());
            im::PopStyleColor();
            im::End();
        };

        im::Begin("sdfsdfdsfds", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar);
        im::BeginMenuBar();
        if (im::BeginMenu("File")) {
            if (im::MenuItem("Save", "crtl + s", false, last_load_filename != ""))
                SaveProj(last_load_filename);
            if (im::MenuItem("Save As")) {
                const auto d = pfd::save_file("Select a file", filesystem::current_path().string(), { "Xs Project Files", "*.xs" }, pfd::opt::none).result();
                if (!d.empty()) {
                    SaveProj(d);
                    last_load_filename = d;
                };
            }
            if (im::MenuItem("Open", "crtl + o")) {
                const auto s = pfd::open_file::open_file("Select File", filesystem::current_path().string(), { "Xs Project Files", "*.xs" }, pfd::opt::none).result();
                if (!s.empty()) {
                    type_load = true;
                    load_filepath = s[0];
                };
                //ImGuiFileDialog::Instance()->OpenDialog("Load Project", "Choose File", ".xs", ".");
            };
            im::EndMenu();
        };
        if (im::BeginMenu("New")) {
            if (im::MenuItem("Camera")) {
                XsEngine.Camera.New("Camera "s + to_string(left_camera++));
                log << "Create New Camera. ("s + "Camera " + to_string(left_camera) + ')';
            };
            if (im::MenuItem("Shape")) {
                XsEngine.Shape.New("Shape "s + to_string(left_shape++));
                log << "Create New Shape. ("s + "Shape " + to_string(left_shape) + ')';
            };
            if (im::MenuItem("Texture")) {
                XsEngine.Texture.New("Texture "s + to_string(left_tex++));
                log << "Create New Texture. ("s + "Texture " + to_string(left_tex) + ')';
            };
            if (im::MenuItem("Mesh")) {
                XsEngine.Mesh.New("Mesh "s + to_string(left_mesh++));
                log << "Create New Mesh. ("s + "Mesh " + to_string(left_mesh) + ')';
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
            im::Checkbox("Extra Text", &show_extra_tex);
            im::SliderFloat("Icon Size", &icon_size, 0.1f, 1.5f);
            im::EndMenu();
        };
        im::EndMenuBar();
        im_wlog = im_wsize().x;
        im_wsize(im_wlog, wn_size.y);
        im_wpos(0, 0);
        {
            if (XsEngine.Camera.__data__().size() > 0u and im::TreeNode("Cameras")) {
                size_t j = 0;
                for (const auto& i : XsEngine.Camera.__data__()) {
                    const bool is_selected = (Sel() == CAMERA and Sel.num == j);
                    if (im::Selectable(i.name.c_str(), is_selected)) {
                        if (is_selected) {
                            Sel() = NONE;
                            Sel.num = 0;
                        }
                        else {
                            Sel() = CAMERA;
                            Sel.num = j;
                        };
                    };
                    j++;
                };
                im::TreePop();
            };
            if (XsEngine.Shape().size() > 0u and im::TreeNode("Shapes")) {
                size_t j = 0;
                for (const auto& i : XsEngine.Shape()) {
                    const bool is_selected = (Sel() == SHAPE and Sel.num == j);
                    if (im::Selectable(i.name.c_str(), is_selected)) {
                        if (is_selected) {
                            Sel() = NONE;
                            Sel.num = 0;
                        }
                        else {
                            Sel() = SHAPE;
                            Sel.num = j;
                        };
                    };
                    j++;
                };
                im::TreePop();
            };
            if (XsEngine.Mesh().size() > 0u and im::TreeNode("Meshs")) {
                size_t j = 0;
                for (const auto& i : XsEngine.Mesh()) {
                    const bool is_selected = (Sel() == MESH and Sel.num == j);
                    if (im::Selectable(i.name.c_str(), is_selected)) {
                        if (is_selected) {
                            Sel() = NONE;
                            Sel.num = 0;
                        }
                        else {
                            Sel() = MESH;
                            Sel.num = j;
                        };
                    };
                    j++;
                };
                im::TreePop();
            };
            if (XsEngine.Texture().size() > 0u and im::TreeNode("Textures")) {
                size_t j = 0;
                for (const auto& i : XsEngine.Texture()) {
                    const bool is_selected = (Sel() == TEXTURE and Sel.num == j);
                    if (im::Selectable(i.name.c_str(), is_selected)) {
                        if (is_selected) {
                            Sel() = NONE;
                            Sel.num = 0;
                        }
                        else {
                            Sel() = TEXTURE;
                            Sel.num = j;
                        };
                    };
                    j++;
                };
                im::TreePop();
            };
        }
        im::End();
        if (Sel() != NONE) {
            im::Begin("dsfdfds", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar);
            im_rpanel = im_wsize().x;
            im_wsize(im_rpanel, wn_size.y);
            im_wpos(wn_size.x - im_wsize().x, 0);
            switch (Sel()) {
            case SHAPE:
                info_shape(XsEngine.Shape[Sel.num]);
                break;
            case CAMERA:
                info_cam(XsEngine.Camera[Sel.num]);
                break;
            case MESH:
                info_mesh(XsEngine.Mesh[Sel.num]);
                break;
            case TEXTURE:
                break;
            };
            im::End();
        };
// //////////////// SETTINGS ///////////////////// //
        //im::Begin("sefdsfsdf", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar);
        //im_wsize(500, 1000);
        //im_wpos(wn_size().x - ((Sel() == NONE) ? (510) : (510 + im_rpanel)), 0);
        //
        //im::End();
// /////////////// LOG PANEL ///////////////////// //
        im::Begin("Log panelsddfds", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar);
        Once(fsdfdsfsdfdfdsfad)
            im_wsize(im_wsize().x, 100);
        im::BeginMenuBar();
        if (im::MenuItem("Log"))
            alt_panel = 0;
        if (im::MenuItem("File"))
            alt_panel = 1;
        im::EndMenuBar();
        
        im_wsize(wn_size().x - ((Sel() == NONE) ? (im_wlog) : (im_wlog + im_rpanel)), im_wsize().y);
        im_wpos(im_wlog, wn_size().y - im_wsize().y);
        im_hlog = im_wsize().y;
        if (alt_panel == 0)
            for (const auto& i : log())
                im::Text(i.c_str());
        else if (alt_panel == 1) {
            if (ImGui::ImageButton(updir_icon, {20, 20})) {
                path = path.substr(0, path.find_last_of("/\\"));
                directorys.clear();
                for (const auto& i : std::filesystem::directory_iterator(path))
                    directorys.push_back(Dir_t(i.path().string(), i.is_directory()));
            };

            ImGui::SameLine(45, -50);
            ImGui::ImageButton(folder_icon, { 20, 20 });

            ImGui::SameLine(80, -100);
            if (!change_path)
                path_str = path;
            if (im::InputText("Path", &path_str, ImGuiInputTextFlags_EnterReturnsTrue)) {
                DWORD ftyp = GetFileAttributesA(path_str.c_str());
                if (ftyp != INVALID_FILE_ATTRIBUTES && (ftyp & FILE_ATTRIBUTE_DIRECTORY)) {
                    path = path_str;
                    directorys.clear();
                    for (const auto& i : std::filesystem::directory_iterator(path))
                        directorys.push_back(Dir_t(i.path().string(), i.is_directory()));
                }
            }
            change_path = im::IsItemActive();

            int j = 0;
            for (const auto& i : directorys) {
                if (i.is_directory) {
                    ImGui::ImageButton(folder_icon, { 93 * icon_size, 90 * icon_size });
                    if (ImGui::IsItemHovered()) {
                        if (ImGui::IsMouseDoubleClicked(0)) {
                            path = i.path;
                            directorys.clear();
                            for (const auto& i : std::filesystem::directory_iterator(path))
                                directorys.push_back(Dir_t(i.path().string(), i.is_directory()));
                        }
                        else {
                            ImGui::BeginTooltip();
                            ImGui::Text(i.path.c_str());
                            ImGui::EndTooltip();
                        };
                    }
                }
                else {
                    ImGui::ImageButton((i.path.ends_with(".png") or i.path.ends_with(".jpg") or i.path.ends_with(".jpeg")) ? imagefile_icon : i.path.ends_with(".obj") ? model_icon : i.path.ends_with(".txt") ? textfile_icon : defaultfile_icon, { 93 * icon_size, 90 * icon_size });
                    if (ImGui::IsItemHovered()) {
                        if (ImGui::IsMouseDoubleClicked(0)) {
                            if (i.path.ends_with(".txt"))
                                ShellExecuteA(NULL, "open", i.path.c_str(), NULL, NULL, SW_SHOWDEFAULT);
                            else if (i.path.ends_with(".png") or i.path.ends_with(".jpg") or i.path.ends_with(".jpeg")) {
                                preview = true;
                                preview_tex = new sf::Texture();
                                preview_tex->loadFromFile(i.path);
                            };
                        }
                        ImGui::BeginTooltip();
                        ImGui::Text(i.path.c_str());
                        ImGui::EndTooltip();
                    };
                }
                j++;
                if ((50 * icon_size * j + (5 * (j + 1))) > ImGui::GetWindowSize().x - (50 * icon_size * (j + 1) + (5 * ((j + 1) + 1))))
                    j = 0;
                if (j != 0)
                    ImGui::SameLine(50 * icon_size * j + (5 * (j + 1)) + 3, 50 * icon_size * j);
            }
        }
        im::End();
// /////////////// LOG PANEL ///////////////////// //
        if (preview) {
            im::Begin("dsfsfdsaf", (bool*)0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
            vex2f _t(preview_tex->getSize().x, preview_tex->getSize().y);
            _t.normalize();
            im::Image(*preview_tex, sf::Vector2f(300, 300 * _t.y));
            im_wsize(300, 300 * _t.y);
            if (im_wpos().x < im_wlog)
                im_wpos(im_wlog + 2, im_wpos().y);
            else if ((wn_size.x - ((Sel() == NONE) ? 0 : im_rpanel)) < im_wpos().x + im_wsize().x)
                im_wpos(wn_size.x - im_wsize().x - ((Sel() == NONE) ? 0 : im_rpanel), im_wpos().y);
            if (im_wpos().y + im_wsize().y > wn_size.y - im_hlog)
                im_wpos(im_wpos().x, wn_size.y - im_hlog - im_wsize().y - 2);
            else if (im_wpos().y < 0)
                im_wpos(im_wpos().x, 2);
            if (im::IsWindowFocused() and im::GetIO().MouseClicked[1])
                im::OpenPopup("close preview");
            if (im::BeginPopup("close preview")) {
                if (im::MenuItem("Close")) {
                    preview = false;
                    preview_tex = nullptr;
                };
                im::EndPopup();
            };
            im::End();
        };
    };
    vex2f mouse_pos = 0.f;
    void run() {
        XsStart(window, "XsEngine (BETA)") {
            Once(sfdsfsdf)
                once();
            wn_size = vex2i(window.getSize().x, window.getSize().y);
            const auto& m = sf::Mouse::getPosition(window);
            mouse_pos = vex2f(m.x, m.y);

            cam_sett();
            draw_floor(floor_shader);

            for (const auto& i : XsEngine.Shape()) {
                if (i.hide == false and i.mesh != i.npos) {
                    glLoadIdentity();
                    const auto& mesh = i.getMesh();
                    if (mesh.poly == GL_POINT) glPointSize(i.pointSize);
                    else if (mesh.poly == GL_LINES) glLineWidth(i.lineWidth);
                    glTranslatef(i.pos.x, i.pos.y, i.pos.z);
                    //Xs.Math.Limit(i.rot, vex3f(0.f), vex3f(360.f));
                    glRotatef(i.rot.x, 1.f, 0.f, 0.f);
                    glRotatef(i.rot.y, 0.f, 1.f, 0.f);
                    glRotatef(i.rot.z, 0.f, 0.f, 1.f);
                    glScalef(i.scale.x, i.scale.y, i.scale.z);
                    glTranslatef(i.origin.x, i.origin.y, i.origin.z);
                    glColor4f(i.color.x, i.color.y, i.color.z, i.color.w);
                    if (i.tex != i.npos) {
                        const auto& tex = i.getTexture();
                        glBindTexture(GL_TEXTURE_2D, tex.data);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, tex.filter);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, tex.filter);
                    }
                    else
                        glBindTexture(GL_TEXTURE_2D, 0);
                    if (mesh.data.size() > 0u)
                        switch (mesh.mode) {
                        case XsEnum::Vertex:
                            if (mesh.data.size() % 3 == 0) {
                                glEnableClientState(GL_VERTEX_ARRAY);
                                glDisableClientState(GL_NORMAL_ARRAY);
                                glDisableClientState(GL_TEXTURE_COORD_ARRAY);
                                glVertexPointer(3, GL_FLOAT, 3 * sizeof(GLfloat), &mesh.data[0]);
                                glDrawArrays(mesh.poly, 0, mesh.data.size() / 3);
                                glDisableClientState(GL_VERTEX_ARRAY);
                            };
                            break;
                        case XsEnum::VertexAndTexture:
                            if (mesh.data.size() % 5 == 0) {
                                glEnableClientState(GL_VERTEX_ARRAY);
                                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                                glDisableClientState(GL_NORMAL_ARRAY);
                                glVertexPointer(3, GL_FLOAT, 5 * sizeof(GLfloat), &mesh.data[0]);
                                glTexCoordPointer(2, GL_FLOAT, 5 * sizeof(GLfloat), &mesh.data[0] + 3);
                                glDrawArrays(mesh.poly, 0, mesh.data.size() / 5);
                                glDisableClientState(GL_VERTEX_ARRAY);
                                glDisableClientState(GL_TEXTURE_COORD_ARRAY);
                            };
                            break;
                        case XsEnum::VertexAndNormal:
                            if (mesh.data.size() % 6 == 0) {
                                glEnableClientState(GL_VERTEX_ARRAY);
                                glDisableClientState(GL_TEXTURE_COORD_ARRAY);
                                glEnableClientState(GL_NORMAL_ARRAY);
                                glVertexPointer(3, GL_FLOAT, 6 * sizeof(GLfloat), &mesh.data[0]);
                                glNormalPointer(GL_FLOAT, 6 * sizeof(GLfloat), &mesh.data[0] + 3);
                                glDrawArrays(mesh.poly, 0, mesh.data.size() / 6);
                                glDisableClientState(GL_VERTEX_ARRAY);
                                glDisableClientState(GL_NORMAL_ARRAY);
                            };
                            break;
                        case XsEnum::All:
                            if (mesh.data.size() % 8 == 0) {
                                glEnableClientState(GL_VERTEX_ARRAY);
                                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                                glEnableClientState(GL_NORMAL_ARRAY);
                                glVertexPointer(3, GL_FLOAT, 8 * sizeof(GLfloat), &mesh.data[0]);
                                glTexCoordPointer(2, GL_FLOAT, 8 * sizeof(GLfloat), &mesh.data[0] + 3);
                                glNormalPointer(GL_FLOAT, 8 * sizeof(GLfloat), &mesh.data[0] + 5);
                                glDrawArrays(mesh.poly, 0, mesh.data.size() / 8);
                                glDisableClientState(GL_VERTEX_ARRAY);
                                glDisableClientState(GL_NORMAL_ARRAY);
                                glDisableClientState(GL_TEXTURE_COORD_ARRAY);
                            };
                            break;
                        default:
                            if (mesh.data.size() % 3 == 0) {
                                glEnableClientState(GL_VERTEX_ARRAY);
                                glDisableClientState(GL_NORMAL_ARRAY);
                                glDisableClientState(GL_TEXTURE_COORD_ARRAY);
                                glVertexPointer(3, GL_FLOAT, 3 * sizeof(GLfloat), &mesh.data[0]);
                                glDrawArrays(mesh.poly, 0, mesh.data.size() / 3);
                                glDisableClientState(GL_VERTEX_ARRAY);
                            };
                            break;
                        };
                    if (mesh.poly == GL_POINT) glPointSize(1.f);
                    else if (mesh.poly == GL_LINES) glLineWidth(1.f);
                };
            };

            //window.clear();
            //sf_gui();

            ImBlock(window) {
                im::ShowDemoWindow();
                ui();
                //if (ImGuiFileDialog::Instance()->Display("Load Project")) {
                //    if (ImGuiFileDialog::Instance()->IsOk())
                //        LoadProj(ImGuiFileDialog::Instance()->GetFilePathName());
                //    ImGuiFileDialog::Instance()->Close();
                //    if (Xs.KeyPressed(Xs.Key.Escape))
                //        ImGuiFileDialog::Instance()->Close();
                //};
            };

            if (type_load) {
                LoadProj(load_filepath);
                type_load = false;
            };
        };
    };
};

int main() {
    App app;
    app.run();
};
