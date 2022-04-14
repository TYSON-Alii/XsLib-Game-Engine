#ifndef _XSLIB2_
#define _XSLIB2_
#include <Windows.h>
#include <format>
#include <GL/glew.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>
using glm::mat4;
#include <ext.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <ImGui/imgui.h>
#include <ImGui/imgui-SFML.h>
#include <ImGui/imgui_stdlib.h>
#include <ImGui/ImGuiFileDialog.h>
//#include <PxPhysXConfig.h>
//#include <PxShape.h>
//#include <PxRigidDynamic.h>
//#include <PxPhysics.h>
//#include <PxPhysicsAPI.h>
#include <librarys/json.hpp>
#include <librarys/magic_enum.hpp>
#include <librarys/EasyGifReader.h>
#include <librarys/portable-file-dialogs.h>
//#include <librarys/ofbx.h>
#include <GLM-Vex.hpp>
#include <ImGui-Vex.hpp>
#include <Vex.hpp>
#include <Random.hpp>
#include <Utilityx.hpp>
#undef then
#undef end
#undef in
#undef temp
#undef none
#undef None
using namespace std::string_literals;
using json = nlohmann::json;
typedef uint XsTexData;
namespace im = ImGui;
using XsId = u64;
class XsEngine;
struct XsVertex {
	list<vex3f> pos, normal;
	list<vex2f> tex;
};
struct XsMesh;
namespace __xs_solid_meshs {
	const list<vex3f> cube_pos = {
		{-1, -1, -1},{-1, 1, -1},{-1, -1, 1},{-1, -1, 1},{-1, 1, -1},{-1, 1, 1},
		{1, -1, -1 },{1, 1, -1 },{1, -1, 1 },{1, -1, 1 },{1, 1, -1 },{1, 1, 1 },
		{-1, -1, -1},{1, -1, -1},{-1, -1, 1},{-1, -1, 1},{1, -1, -1},{1, -1, 1},
		{-1, 1, -1 },{1, 1, -1 },{-1, 1, 1 },{-1, 1, 1 },{1, 1, -1 },{1, 1, 1 },
		{-1, -1, -1},{1, -1, -1},{-1, 1, -1},{-1, 1, -1},{1, -1, -1},{1, 1, -1},
		{-1, -1, 1 },{1, -1, 1 },{-1, 1, 1 },{-1, 1, 1 },{1, -1, 1 },{1, 1, 1 }
	};
	const list<vex2f> cube_tex = {
		{0, 0},{1, 0},{0, 1},{0, 1},{1, 0},{1, 1},
		{0, 0},{1, 0},{0, 1},{0, 1},{1, 0},{1, 1},
		{0, 0},{1, 0},{0, 1},{0, 1},{1, 0},{1, 1},
		{0, 0},{1, 0},{0, 1},{0, 1},{1, 0},{1, 1},
		{0, 0},{1, 0},{0, 1},{0, 1},{1, 0},{1, 1},
		{0, 0},{1, 0},{0, 1},{0, 1},{1, 0},{1, 1}
	};
	const list<vex3f> cube_normal = {
		{1, 0, 0 },{1, 0, 0 },{1, 0, 0 },{0, 0, -1 },{0, 0, -1 },{0, 0, -1 },
		{-1, 0, 0},{-1, 0, 0},{-1, 0, 0},{0, -0, 1 },{0, -0, 1 },{0, -0, 1 },
		{0, 1, 0 },{0, 1, 0 },{0, 1, 0 },{0, -1, -0},{0, -1, -0},{0, -1, -0},
		{1, 0, 0 },{1, 0, 0 },{1, 0, 0 },{0, 0, -1 },{0, 0, -1 },{0, 0, -1 },
		{-1, 0, 0},{-1, 0, 0},{-1, 0, 0},{0, -0, 1 },{0, -0, 1 },{0, -0, 1 },
		{0, 1, 0 },{0, 1, 0 },{0, 1, 0 },{0, -1, -0},{0, -1, -0},{0, -1, -0}
	};
	const list<vex3f> plane_pos = {
		{  1, 0,  1 },
		{ -1, 0, -1 },
		{ -1, 0,  1 },
		{  1, 0,  1 },
		{  1, 0, -1 },
		{ -1, 0, -1 }
	};
	const list<vex2f> plane_tex = {
		{ 1, 0 },
		{ 0, 1 },
		{ 0, 0 },
		{ 1, 0 },
		{ 1, 1 },
		{ 0, 1 }
	};
	const list<vex3f> plane_normal = {
		{ 0, 1, 0 },
		{ 0, 1, 0 },
		{ 0, 1, 0 },
		{ 0, 1, 0 },
		{ 0, 1, 0 },
		{ 0, 1, 0 }
	};
};
struct {
	f32 Fps = 60.f;
	sf::Event Event;
	struct {
		vex3f Red = vex3f(0.976f, 0.117f, 0.265f);
		vex3f DarkGreen = vex3f(0.000f, 0.386f, 0.265f);
		vex3f Blue = vex3f(0.000f, 0.703f, 0.917f);
		vex3f Pink = vex3f(1.000f, 0.867f, 0.894f);
		vex3f DarkBlue = vex3f(0.359f, 0.289f, 0.890f);
		vex3f Grey = vex3f(0.230f, 0.226f, 0.289f);
		vex3f Purple = vex3f(0.564f, 0.04f, 0.65f);
		vex3f LightPurple = vex3f(0.576f, 0.439f, 0.858f);
		vex3f Orange = vex3f(1.00f, 0.36f, 0.09f);
		vex3f Yellow = vex3f(0.91f, 1.00f, 0.21f);
		vex3f Lime = vex3f(0.55f, 0.90f, 0.06f);
		struct {
			vex3ub Red = vex3ub(248, 29, 67);
			vex3ub DarkGreen = vex3ub(0, 98, 67);
			vex3ub Blue = vex3ub(0, 179, 233);
			vex3ub Pink = vex3ub(255, 221, 227);
			vex3ub DarkBlue = vex3ub(91, 73, 226);
			vex3ub Grey = vex3ub(58, 57, 73);
			vex3ub Purple = vex3ub(143, 10, 165);
			vex3ub LightPurple = vex3ub(146, 112, 218);
			vex3ub Orange = vex3ub(255, 91, 23);
			vex3ub Yellow = vex3ub(232, 255, 53);
			vex3ub Lime = vex3ub(140, 229, 15);
		} Rgb256;
	} Color;
	struct {
		enum XsEnum_t {
			Point = GL_POINTS,
			Line = GL_LINES,
			Triangle = GL_TRIANGLES,
			Quad = GL_QUADS,
			Polygon = GL_POLYGON
		};
	} Enum;
	struct {
		enum Key_t {
			A = 65, B = 66, C = 67, D = 68, E = 69, F = 70, G = 71, H = 72, I = 73, J = 74, K = 75, L = 76, M = 77, N = 78, O = 79, P = 80, Q = 81, R = 82, S = 83, T = 84, U = 85, V = 86, W = 87, X = 88, Y = 89, Z = 90,
			Num0 = 48, Num1 = 49, Num2 = 50, Num3 = 51, Num4 = 52, Num5 = 53, Num6 = 54, Num7 = 55, Num8 = 56, Num9 = 57,
			Space = 32,
			Escape = 27,
			Delete = 8,
			Tab = 9,
			Up = 38,
			Down = 40,
			Right = 39,
			Left = 37,
			Shift = 16,
			Enter = 13
		};
		inline static bool Pressed(const byte& key) { return (GetKeyState((int)key) & 0x800); };
	} Key;
	struct {
		inline static vex2i Pos() {
			POINT p;
			GetCursorPos(&p);
			return vex2i(p.x, p.y);
		};
		enum Button_t {
			Left = 1,
			Right = 2,
			Middle = 16
		};
		inline static bool Pressed() { return (GetKeyState((int)Button_t::Left) & 0x800) or (GetKeyState((int)Button_t::Right) & 0x800) or (GetKeyState((int)Button_t::Middle) & 0x800); };
	} Mouse;
	struct {
		template <typename T1, typename T2>
		inline static T1 Distance(const vex2<T1>& v1, const vex2<T2>& v2) { return std::sqrt(std::pow(v1.x-v2.x, 2) + std::pow(v1.y - v2.y, 2)); };
		template <typename T1, typename T2>
		inline static T1 Distance(const vex3<T1>& v1, const vex3<T2>& v2) { return std::sqrt(std::pow(v1.x - v2.x, 2) + std::pow(v1.y - v2.y, 2) + std::pow(v1.z - v2.z, 2)); };
		inline void Limit(float& v, float min, float max, const bool& restart = false) { if (v > max) v = restart ? min : max; else if (v < min) v = restart ? max : min; };
	} Math;
	struct {
		const XsVertex Cube = { __xs_solid_meshs::cube_pos, __xs_solid_meshs::cube_normal, __xs_solid_meshs::cube_tex };
		const XsVertex Plane = { __xs_solid_meshs::plane_pos, __xs_solid_meshs::plane_normal, __xs_solid_meshs::plane_tex };
	} Mesh;
	struct {
		const char* PolyNames[5]{ "Point", "Line", "Triangle", "Quad", "Polygon"};
	} Values;
	XsMesh LoadOBJ(const str& filename);
	struct {
		vex3f BackGround = 0.f;
		vex2ui WindowSize = vex2ui(1200, 700);
	} Sett;
	struct {
		struct {
			vex3f Speed = 0.f;
			vex3f Speed_v = 0.1f;
			vex2f Rot = 0.f;
			vex2f RotVel = 0.f;
		} Cam;
	} Editor;
} Xs;
typedef decltype(decltype(Xs)::Enum)::XsEnum_t XsEnum;
typedef decltype(decltype(Xs)::Key)::Key_t XsKey;
class XsEntity {
public:
	XsEntity(const str& _tag = "") : tag(_tag) { };
	virtual const type_info& info() final { return typeid(self); };
	virtual void start() { };
	virtual void loop() { };
	bool froze = false;
	XsId id;
	str tag;
};
struct XsMesh : public XsEntity, public XsVertex {
	XsMesh() = default;
	XsMesh(const XsMesh&) = default;
	inline XsMesh(const str& _tag) : XsEntity(_tag) { };
	inline XsMesh(XsVertex v, const str& _tag = "") : XsEntity(_tag) {
		pos = v.pos;
		tex = v.tex;
		normal = v.normal;
	};
	inline auto Scale(const vex3f& new_scale) const {
		XsMesh t = *this;
		auto b = t.pos.begin();
		const auto& e = t.pos.end();
		while (b != e) {
			*b *= new_scale;
			b++;
		};
		return t;
	};
	inline auto Origin(const vex3f& new_origin) const {
		XsMesh t = *this;
		auto b = t.pos.begin();
		const auto& e = t.pos.end();
		while (b != e) {
			*b += new_origin;
			b++;
		};
		return t;
	};
	vex3f findMax() const {
		vex3f t = 0;
		auto b = pos.begin();
		const auto& e = pos.end();
		while (b != e) {
			if ((*b).x > t.x) t.x = (*b).x;
			if ((*b).y > t.y) t.y = (*b).y;
			if ((*b).z > t.z) t.z = (*b).z;
			b++;
		};
		return t;
	};
	vex3f findMin() const {
		vex3f t = 0;
		auto b = pos.begin();
		const auto& e = pos.end();
		while (b != e) {
			if ((*b).x < t.x) t.x = (*b).x;
			if ((*b).y < t.y) t.y = (*b).y;
			if ((*b).z < t.z) t.z = (*b).z;
			b++;
		};
		return t;
	};
	inline void add(vex3f _pos = 0.f, vex2f _tex = 0.f, vex3f _normal = 0.f) { pos.push_back(_pos); tex.push_back(_tex); normal.push_back(_normal); };
	XsEnum poly = Xs.Enum.Triangle;
};
inline void glColor3(const vex3f& v) { glColor3f(v.x, v.y, v.z); };
inline void glColor4(const vex3f& v) { glColor4f(v.x, v.y, v.z, 1); };
inline void glColor4(const vex4f& v) { glColor4f(v.x, v.y, v.z, v.w); };
inline void glTranslate(const vex3f& v) { glTranslatef(v.x, v.y, v.z); };
inline void glRotate(const vex3f& v) { glRotatef(v.x, 1, 0, 0); glRotatef(v.y, 0, 1, 0); glRotatef(v.z, 0, 0, 1); };
inline void glScale(const vex3f& v) { glScalef(v.x, v.y, v.z); };
inline void glVertex3(const vex3f& v) { glVertex3f(v.x, v.y, v.z); };
inline void glVertex2(const vex2f& v) { glVertex2f(v.x, v.y); };
static sf::ContextSettings contextSettings = sf::ContextSettings(24,8,0,3,3,false);
sf::Context context;
static sf::Clock __IMCLOCK__;
static auto _XS_FPS_START = std::chrono::high_resolution_clock::now();
static const bool& _xs_init = [&]() -> bool { glewInit(); return true; }();

#include <system/XsClock.hpp>

#include <system/XsCamera.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <librarys/stb.h>
#include <librarys/stb_image.h>

#include <mesh/XsTexture.hpp>

#include <system/XsShader.hpp>

#include <mesh/XsShape.hpp>

#include <mesh/XsOBJLoader.hpp>

#include <mesh/XsAnim.hpp>

//#include <mesh/XsPhysx.hpp>

#define XsStart(_Eng, _Name) for(([&]() -> void {										\
_Eng.Window.create(sf::VideoMode(Xs.Sett.WindowSize.x, Xs.Sett.WindowSize.y), _Name, sf::Style::Default, contextSettings);\
ImGui::SFML::Init(_Eng.Window);																	\
glEnable(GL_TEXTURE_2D);																	\
glEnable(GL_SCISSOR_TEST);																	\
glEnable(GL_DEPTH_TEST);																	\
glEnable(GL_NORMALIZE);																		\
glDepthFunc(GL_LESS);		\
glShadeModel(GL_SMOOTH);																	\
glEnable(GL_BLEND);glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);															\
glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);					\
glBlendEquation(GL_FUNC_ADD);																\
glLoadIdentity();																			\
}());																						\
																							\
([&]() -> bool {																			\
_XS_FPS_START = std::chrono::high_resolution_clock::now();									\
glClearColor(Xs.Sett.BackGround.x, Xs.Sett.BackGround.y, Xs.Sett.BackGround.z, 1.0);		\
glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);											\
while (_Eng.Window.pollEvent(Xs.Event)) {														\
	ImGui::SFML::ProcessEvent(Xs.Event);													\
	if (Xs.Event.type == sf::Event::Closed)													\
		_Eng.Window.close();																	\
};																							\
return false;																				\
}() || _Eng.Window.isOpen());																	\
																							\
([&]() -> void { _Eng.Window.display(); Xs.Fps = (float)1e9 / (float)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - _XS_FPS_START).count(); }()))

static bool __FxsIm = true;
#define ImBlock(_Window) for([&](){ ImGui::SFML::Update(_Window, __IMCLOCK__.restart()); __FxsIm = true; }();__FxsIm;[&](){ _Window.pushGLStates(); ImGui::SFML::Render(_Window); _Window.popGLStates(); __FxsIm = false;}())

#include <Engine/XsEngine.hpp>
#include <system/XsImGui.hpp>
using Engine = XsEngine;
using Entity = XsEntity;
using Shape = XsShape;
using Color = XsColor;
using Transform = XsTransform;
using Material = XsMaterial;
using Texture = XsTexture;
using Anim = XsAnim;
using Mesh = XsMesh;
using Vertex = XsVertex;
using Light = XsLight;
using Shader = XsShader;
using Camera = XsCamera;
using Chrono = XsChrono;
#endif