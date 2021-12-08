#define _XSLIB2_
#include <iostream>
#include <utility>
#include <algorithm>
#include <Windows.h>
#include <fstream>
#include <GL/glew.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <ImGui/imgui.h>
#include <ImGui/imgui-SFML.h>
#include <ImGui/imgui_stdlib.h>
#include <ImGui/ImGuiFileDialog.h>
#include <PxPhysXConfig.h>
#include <PxShape.h>
#include <PxRigidDynamic.h>
#include <PxPhysics.h>
#include <PxPhysicsAPI.h>
#include <librarys/json.hpp>
#include <librarys/magic_enum.hpp>
#include <librarys/portable-file-dialogs.h>
#include <Strinx.hpp>
#include <Vex.hpp>
#include <Random.hpp>
#include <Utilityx.hpp>
using namespace std::string_literals;
using json = nlohmann::json;
#define XS_PI 3.141592f
#define XS_HALF_PI 1.570796f
#define XS_TWO_PI 6.283185f
#define XS_FI 1.618033f
typedef std::vector<GLfloat> XsVerts;
typedef unsigned int XsTexData;
struct {
	strinx LogStx;
	float Fps = 1.0f;
	struct {
		struct {
			typedef unsigned char Color_t;
			Color_t Black = 0, White = 15;
			Color_t DarkBlue = 1, DarkGreen = 2, DarkCyan = 3, DarkRed = 4, DarkMagenta = 5, DarkYellow = 6, Dark_grey = 8;
			Color_t Grey = 7, Blue = 9, Green = 10, Cyan = 11, Red = 12, Purple = 13, Yellow = 14;
		} Color;
		void operator<<(const char* error) {
			Xs.LogStx += error;
			Xs.LogStx += '\n';
		};
	} Log;
	struct {
		vex3f Red			= vex3f(0.976f, 0.117f, 0.265f);
		vex3f DarkGreen		= vex3f(0.000f, 0.386f, 0.265f);
		vex3f Blue			= vex3f(0.000f, 0.703f, 0.917f);
		vex3f Pink			= vex3f(1.000f, 0.867f, 0.894f);
		vex3f DarkBlue		= vex3f(0.359f, 0.289f, 0.890f);
		vex3f Grey			= vex3f(0.230f, 0.226f, 0.289f);
		vex3f Purple		= vex3f(0.564f, 0.04f, 0.65f);
		vex3f LightPurple	= vex3f(0.576f, 0.439f, 0.858f);
		vex3f Orange		= vex3f(1.00f, 0.36f, 0.09f);
		vex3f Yellow		= vex3f(0.91f, 1.00f, 0.21f);
		vex3f Lime			= vex3f(0.55f, 0.90f, 0.06f);
		struct {
			vex3i Red			= vex3i(248, 29, 67);
			vex3i DarkGreen		= vex3i(0, 98, 67);
			vex3i Blue			= vex3i(0, 179, 233);
			vex3i Pink			= vex3i(255, 221, 227);
			vex3i DarkBlue		= vex3i(91, 73, 226);
			vex3i Grey			= vex3i(58, 57, 73);
			vex3i Purple		= vex3i(143, 10, 165);
			vex3i LightPurple	= vex3i(146, 112, 218);
			vex3i Orange		= vex3i(255, 91, 23);
			vex3i Yellow		= vex3i(232, 255, 53);
			vex3i Lime			= vex3i(140, 229, 15);
		} Rgb256;
		struct {
			int Red			= 0xf81d43;
			int DarkGreen	= 0x006243;
			int Blue		= 0x00b3e9;
			int Pink		= 0xffdde3;
			int DarkBlue	= 0x5b49e2;
			int Grey		= 0x3a3949;
			int Purple		= 0x8e0aa5;
			int LightPurple	= 0x9270da;
			int Orange		= 0xff5b17;
			int Yellow		= 0xe8ff35;
			int Lime		= 0x8ce50f;
			struct {
				strinx Red			= "f81d43";
				strinx DarkGreen	= "006243";
				strinx Blue			= "00b3e9";
				strinx Pink			= "ffdde3";
				strinx DarkBlue		= "5b49e2";
				strinx Grey			= "3a3949";
				strinx Purple		= "8e0aa5";
				strinx LightPurple	= "9270da";
				strinx Orange		= "ff5b17";
				strinx Yellow		= "e8ff35";
				strinx Lime			= "8ce50f";
			} Stx;
		} Hex;
		struct {
			vex3f HexToRGB(int hex)		{ return vex3f(((hex >> 16) & 0xff) / 255.f, ((hex >> 8) & 0xff) / 255.f, ((hex) & 0xff) / 255.f); };
			vex3i HexToRGB256(int hex)	{ return vex3i(((hex >> 16) & 0xff), ((hex >> 8) & 0xff), ((hex) & 0xff)); };
		} Convert;
	} Color;
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
	} Key;
	struct {
		enum Enum_t {
			Point = GL_POINTS,
			Line = GL_LINES,
			Triangle = GL_TRIANGLES,
			Quad = GL_QUADS,
			Polygon = GL_POLYGON,
			Int = 0x05,
			Float = 0x06,
			Double = 0x07,
			Bool = 0x08,
			String = 0x09,
			Char = 0x0a,
			All = 0x0b,
			Vertex = 0x0c,
			Normal = 0x0d,
			Texture = 0x0e,
			VertexAndTexture = 0x0f,
			VertexAndNormal = 0x10,
			Ceil = 0x11,
			Trunc = 0x12,
			Floor = 0x13,
			Repeat = 0x14,
			Reverse = 0x15,
			Smooth = 0x16,
			Hard = 0x17,
		};
	} Enum;
	struct {
		enum Solid_t {
			Cube = 0x01,
			Prism = 0x02,
			Sphere = 0x03,
			Cylinder = 0x04,
			Cone = 0x05,
			Monke = 0x06,
			Icosphere = 0x07,
			Torus = 0x08,
			Square = 0x09,
			Teapot = 0x0a,
			Star = 0x0b,
			Polygone = 0x0c,
			Box = 0x0d
		};
	} Solid;
	struct {
		struct {
			XsVerts Default{
				-1.f, -1.f, 0.f,
				-1.f, 1.f, 0.f,
				1.f, 1.f, 0.f,
				1.f, -1.f, 0.f
			};
			XsVerts Textured{
				-1.f, -1.f, 0.f,  0.f, 0.f,
				-1.f, 1.f, 0.f,  0.f, 1.f,
				1.f, 1.f, 0.f,  1.f, 1.f,
				1.f, -1.f, 0.f,  1.f, 0.f
			};
		} Plane;
		struct {
			XsVerts Default{
				-1.f, -1.f, -1.f,
				-1.f,  1.f, -1.f,
				-1.f, -1.f,  1.f,
				-1.f, -1.f,  1.f,
				-1.f,  1.f, -1.f,
				-1.f,  1.f,  1.f,

				 1.f, -1.f, -1.f,
				 1.f,  1.f, -1.f,
				 1.f, -1.f,  1.f,
				 1.f, -1.f,  1.f,
				 1.f,  1.f, -1.f,
				 1.f,  1.f,  1.f,

				-1.f, -1.f, -1.f,
				 1.f, -1.f, -1.f,
				-1.f, -1.f,  1.f,
				-1.f, -1.f,  1.f,
				 1.f, -1.f, -1.f,
				 1.f, -1.f,  1.f,

				-1.f,  1.f, -1.f,
				 1.f,  1.f, -1.f,
				-1.f,  1.f,  1.f,
				-1.f,  1.f,  1.f,
				 1.f,  1.f, -1.f,
				 1.f,  1.f,  1.f,

				-1.f, -1.f, -1.f,
				 1.f, -1.f, -1.f,
				-1.f,  1.f, -1.f,
				-1.f,  1.f, -1.f,
				 1.f, -1.f, -1.f,
				 1.f,  1.f, -1.f,

				-1.f, -1.f,  1.f,
				 1.f, -1.f,  1.f,
				-1.f,  1.f,  1.f,
				-1.f,  1.f,  1.f,
				 1.f, -1.f,  1.f,
				 1.f,  1.f,  1.f
			};
		} Cube;
	} Vert;
	bool KeyPressed(unsigned char key) { return (GetKeyState(key) & 0x800); };
	struct {
		vex2i Pos() {
			POINT p;
			GetCursorPos(&p);
			return vex2i(p.x, p.y);
		};
		template <typename T> void Pos(vex2<T>& v) {
			POINT p;
			GetCursorPos(&p);
			v = vex2<T>(p.x, p.y);
		};
		template <typename T> void Pos(vex3<T>& v) {
			POINT p;
			GetCursorPos(&p);
			v = vex2<T>(p.x, p.y);
		};
		template <typename T> void Pos(vex4<T>& v) {
			POINT p;
			GetCursorPos(&p);
			v = vex2<T>(p.x, p.y);
		};
		struct {
			enum Button_t {
				Left = 1,
				Right = 2,
				Middle = 16
			};
		} Button;
	} Mouse;
	struct {
		template <typename T1, typename T2>
		vex2<T1> Distance(vex2<T1> v1, vex2<T2> v2) { return std::sqrt(std::pow(v1.x-v2.x, 2) + std::pow(v1.y - v2.y, 2)); };
		template <typename T1, typename T2>
		vex3<T1> Distance(vex3<T1> v1, vex3<T2> v2) { return std::sqrt(std::pow(v1.x - v2.x, 2) + std::pow(v1.y - v2.y, 2) + std::pow(v1.z - v2.z, 2)); };
		inline void Limit(float& v, float limit, float restart_n = 0.f) { if (v > limit) v = restart_n; };
		//void Limit(float& v, float min, float max) { if (v > max) v = min; else if (v < min) v = max; };
		void Limit(vex2f& v, vex2f min, vex2f max) {
			if (v.x > max.x) v.x = min.x; else if (v.x < min.x) v.x = max.x;
			if (v.y > max.y) v.y = min.y; else if (v.y < min.y) v.y = max.y;
		};
		void Limit(vex3f& v, vex3f min, vex3f max) {
			if (v.x > max.x) v.x = min.x; else if (v.x < min.x) v.x = max.x;
			if (v.y > max.y) v.y = min.y; else if (v.y < min.y) v.y = max.y;
			if (v.z > max.z) v.z = min.z; else if (v.z < min.z) v.z = max.z;
		};
		void Limit(vex4f& v, vex4f min, vex4f max) {
			if (v.x > max.x) v.x = min.x; else if (v.x < min.x) v.x = max.x;
			if (v.y > max.y) v.y = min.y; else if (v.y < min.y) v.y = max.y;
			if (v.z > max.z) v.z = min.z; else if (v.z < min.z) v.z = max.z;
			if (v.w > max.w) v.w = min.w; else if (v.w < min.w) v.w = max.w;
		};
	} Math;
	struct {
		const char* XsModeNames[4]{ "Vertex", "Vertex and Texture", "Vertex and Normal", "All" };
		const char* GlModeNames[5]{ "Point", "Line", "Triangle", "Quad", "Polygon"};
	} Values;
	sf::Event Event;
	XsVerts LoadOBJ(const char* filename, decltype(Enum)::Enum_t mode);
	void Draw(XsVerts vert, decltype(Enum)::Enum_t mode, GLenum glmode);
	bool LoadTexture(const char* filename, unsigned int& _tex_data, GLenum _filter);
	void Line(float x1, float y1, float z1, float x2, float y2, float z2) { glVertex3f(x1, y1, z1); glVertex3f(x2, y2, z2); };
	void Line(vex3f v1, vex3f v2) { glVertex3f(v1.x, v1.y, v1.z); glVertex3f(v2.x, v2.y, v2.z); };
	void Cube(vex3f scale) {};
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
typedef decltype(decltype(Xs)::Enum)::Enum_t XsEnum;
typedef decltype(decltype(Xs)::Key)::Key_t XsKey;
typedef decltype(decltype(Xs)::Solid)::Solid_t XsSolidType;

#include <system/XsShader.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <librarys/stb.h>
#include <librarys/stb_image.h>
#include <mesh/XsTexture.hpp>

#include <mesh/XsShape.hpp>

#include <system/XsCamera.hpp>

#include <system/XsClock.hpp>

#include <mesh/XsOBJLoader.hpp>

#include <system/XsImgui.hpp>

#define XsSetup void __ENGINE_START_FUNC__()
#define XsLoop void __ENGINE_LOOP_FUNC__()
#define XsImgui void __ENGINE_IMGUI_FUNC__()
void __ENGINE_START_FUNC__();
void __ENGINE_LOOP_FUNC__();
void __ENGINE_IMGUI_FUNC__();
#include <Engine/XsEngine.hpp>