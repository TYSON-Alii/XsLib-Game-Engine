#define __VEX2IM_FUNCS__														\
operator ImVec2() const { return ImVec2(x, y); };								\
operator ImVec4() const { return ImVec4(x, y, NULL, NULL); };					\
vex2<T>& operator=(ImVec2 v)  { x  = T(v.x); y  = T(v.y); return *this; };		\
vex2<T>& operator=(ImVec4 v)  { x  = T(v.x); y  = T(v.y); return *this; };		\
vex2<T>& operator-=(ImVec2 v) { x -= T(v.x); y -= T(v.y); return *this; };		\
vex2<T>& operator-=(ImVec4 v) { x -= T(v.x); y -= T(v.y); return *this; };		\
vex2<T>& operator+=(ImVec2 v) { x += T(v.x); y += T(v.y); return *this; };		\
vex2<T>& operator+=(ImVec4 v) { x += T(v.x); y += T(v.y); return *this; };		\
vex2<T>& operator*=(ImVec2 v) { x *= T(v.x); y *= T(v.y); return *this; };		\
vex2<T>& operator*=(ImVec4 v) { x *= T(v.x); y *= T(v.y); return *this; };		\
vex2<T>& operator/=(ImVec2 v) { x /= T(v.x); y /= T(v.y); return *this; };		\
vex2<T>& operator/=(ImVec4 v) { x /= T(v.x); y /= T(v.y); return *this; };		\
vex2<T> operator-(ImVec2 v) const { return vex2<T>(x - T(v.x), y - T(v.y)); };	\
vex2<T> operator-(ImVec4 v) const { return vex2<T>(x - T(v.x), y - T(v.y)); };	\
vex2<T> operator+(ImVec2 v) const { return vex2<T>(x + T(v.x), y + T(v.y)); };	\
vex2<T> operator+(ImVec4 v) const { return vex2<T>(x + T(v.x), y + T(v.y)); };	\
vex2<T> operator*(ImVec2 v) const { return vex2<T>(x * T(v.x), y * T(v.y)); };	\
vex2<T> operator*(ImVec4 v) const { return vex2<T>(x * T(v.x), y * T(v.y)); };	\
vex2<T> operator/(ImVec2 v) const { return vex2<T>(x / T(v.x), y / T(v.y)); };	\
vex2<T> operator/(ImVec4 v) const { return vex2<T>(x / T(v.x), y / T(v.y)); };	\
bool operator==(ImVec2 v) const { return x == T(v.x) && y == T(v.y); };			\
bool operator==(ImVec4 v) const { return x == T(v.x) && y == T(v.y); };			\
bool operator!=(ImVec2 v) const { return x != T(v.x) && y != T(v.y); };			\
bool operator!=(ImVec4 v) const { return x != T(v.x) && y != T(v.y); };

#define __VEX3IM_FUNCS__																		\
operator ImVec2() const { return ImVec2(x, y); };											\
operator ImVec4() const { return ImVec4(x, y, z, NULL); };									\
vex3<T>& operator=(ImVec2 v)  { x  = T(v.x); y  = T(v.y); return *this; };					\
vex3<T>& operator=(ImVec4 v)  { x  = T(v.x); y  = T(v.y); z  = T(v.z); return *this; };		\
vex3<T>& operator-=(ImVec2 v) { x -= T(v.x); y -= T(v.y); return *this; };					\
vex3<T>& operator-=(ImVec4 v) { x -= T(v.x); y -= T(v.y); z -= T(v.z); return *this; };		\
vex3<T>& operator+=(ImVec2 v) { x += T(v.x); y += T(v.y); return *this; };					\
vex3<T>& operator+=(ImVec4 v) { x += T(v.x); y += T(v.y); z += T(v.z); return *this; };		\
vex3<T>& operator*=(ImVec2 v) { x *= T(v.x); y *= T(v.y); return *this; };					\
vex3<T>& operator*=(ImVec4 v) { x *= T(v.x); y *= T(v.y); z *= T(v.z); return *this; };		\
vex3<T>& operator/=(ImVec2 v) { x /= T(v.x); y /= T(v.y); return *this; };					\
vex3<T>& operator/=(ImVec4 v) { x /= T(v.x); y /= T(v.y); z /= T(v.z); return *this; };		\
vex3<T> operator-(ImVec2 v) const { return vex3<T>(x - T(v.x), y - T(v.y)); };				\
vex3<T> operator-(ImVec4 v) const { return vex3<T>(x - T(v.x), y - T(v.y), z - T(v.z)); };	\
vex3<T> operator+(ImVec2 v) const { return vex3<T>(x + T(v.x), y + T(v.y)); };				\
vex3<T> operator+(ImVec4 v) const { return vex3<T>(x + T(v.x), y + T(v.y), z + T(v.z)); };	\
vex3<T> operator*(ImVec2 v) const { return vex3<T>(x * T(v.x), y * T(v.y)); };				\
vex3<T> operator*(ImVec4 v) const { return vex3<T>(x * T(v.x), y * T(v.y), z * T(v.z)); };	\
vex3<T> operator/(ImVec2 v) const { return vex3<T>(x / T(v.x), y / T(v.y)); };				\
vex3<T> operator/(ImVec4 v) const { return vex3<T>(x / T(v.x), y / T(v.y), z / T(v.z)); };	\
bool operator==(ImVec2 v) const { return x == T(v.x) && y == T(v.y); };						\
bool operator==(ImVec4 v) const { return x == T(v.x) && y == T(v.y) && z == T(v.z); };		\
bool operator!=(ImVec2 v) const { return x != T(v.x) && y != T(v.y); };						\
bool operator!=(ImVec4 v) const { return x != T(v.x) && y != T(v.y) && z != T(v.z); };

#define __VEX4IM_FUNCS__																				\
operator ImVec2() const { return ImVec2(x, y); };														\
operator ImVec4() const { return ImVec4(x, y, z, w); };													\
vex4<T>& operator=(ImVec2 v)  { x  = T(v.x); y  = T(v.y); return *this; };								\
vex4<T>& operator=(ImVec4 v)  { x  = T(v.x); y  = T(v.y); z  = T(v.z); w  = T(v.w); return *this; };	\
vex4<T>& operator-=(ImVec2 v) { x -= T(v.x); y -= T(v.y); return *this; };								\
vex4<T>& operator-=(ImVec4 v) { x -= T(v.x); y -= T(v.y); z -= T(v.z); w -= T(v.w); return *this; };	\
vex4<T>& operator+=(ImVec2 v) { x += T(v.x); y += T(v.y); return *this; };								\
vex4<T>& operator+=(ImVec4 v) { x += T(v.x); y += T(v.y); z += T(v.z); w += T(v.w); return *this; };	\
vex4<T>& operator*=(ImVec2 v) { x *= T(v.x); y *= T(v.y); return *this; };								\
vex4<T>& operator*=(ImVec4 v) { x *= T(v.x); y *= T(v.y); z *= T(v.z); w *= T(v.w); return *this; };	\
vex4<T>& operator/=(ImVec2 v) { x /= T(v.x); y /= T(v.y); return *this; };								\
vex4<T>& operator/=(ImVec4 v) { x /= T(v.x); y /= T(v.y); z /= T(v.z); w /= T(v.w); return *this; };	\
vex4<T> operator-(ImVec2 v) const { return vex3<T>(x - T(v.x), y - T(v.y)); };							\
vex4<T> operator-(ImVec4 v) const { return vex3<T>(x - T(v.x), y - T(v.y), z - T(v.z), w - T(v.w)); };	\
vex4<T> operator+(ImVec2 v) const { return vex3<T>(x + T(v.x), y + T(v.y)); };							\
vex4<T> operator+(ImVec4 v) const { return vex3<T>(x + T(v.x), y + T(v.y), z + T(v.z), w + T(v.w)); };	\
vex4<T> operator*(ImVec2 v) const { return vex3<T>(x * T(v.x), y * T(v.y)); };							\
vex4<T> operator*(ImVec4 v) const { return vex3<T>(x * T(v.x), y * T(v.y), z * T(v.z), w * T(v.w)); };	\
vex4<T> operator/(ImVec2 v) const { return vex3<T>(x / T(v.x), y / T(v.y)); };							\
vex4<T> operator/(ImVec4 v) const { return vex3<T>(x / T(v.x), y / T(v.y), z / T(v.z), w / T(v.w)); };	\
bool operator==(ImVec2 v) const { return x == T(v.x) && y == T(v.y); };									\
bool operator==(ImVec4 v) const { return x == T(v.x) && y == T(v.y) && z == T(v.z) && w == T(v.w); };	\
bool operator!=(ImVec2 v) const { return x != T(v.x) && y != T(v.y); };									\
bool operator!=(ImVec4 v) const { return x != T(v.x) && y != T(v.y) && z != T(v.z) && w != T(v.w); };

#define __XSIMFUNCS__                                                                                                                                                 \
namespace ImGui {                                                                                                                                                     \
    inline void InputFloat(const std::string& label, vex2f& v, const char* format = "%.3f", ImGuiInputTextFlags flags = 0) { InputFloat2(label.c_str(), *v, format, flags); }; \
    inline void InputFloat(const std::string& label, vex3f& v, const char* format = "%.3f", ImGuiInputTextFlags flags = 0) { InputFloat3(label.c_str(), *v, format, flags); }; \
    inline void InputFloat(const std::string& label, vex4f& v, const char* format = "%.3f", ImGuiInputTextFlags flags = 0) { InputFloat4(label.c_str(), *v, format, flags); }; \
    inline void InputInt(const std::string& label, vex2i& v, ImGuiInputTextFlags flags = 0) { InputInt2(label.c_str(), *v, flags); };                                          \
    inline void InputInt(const std::string& label, vex3i& v, ImGuiInputTextFlags flags = 0) { InputInt3(label.c_str(), *v, flags); };                                          \
    inline void InputInt(const std::string& label, vex4i& v, ImGuiInputTextFlags flags = 0) { InputInt4(label.c_str(), *v, flags); };                                          \
    inline void Input(const std::string& label, vex2f& v, const char* format = "%.3f", ImGuiInputTextFlags flags = 0) { InputFloat2(label.c_str(), *v, format, flags); };      \
    inline void Input(const std::string& label, vex3f& v, const char* format = "%.3f", ImGuiInputTextFlags flags = 0) { InputFloat3(label.c_str(), *v, format, flags); };      \
    inline void Input(const std::string& label, vex4f& v, const char* format = "%.3f", ImGuiInputTextFlags flags = 0) { InputFloat4(label.c_str(), *v, format, flags); };      \
    inline void Input(const std::string& label, vex2i& v, ImGuiInputTextFlags flags = 0) { InputInt2(label.c_str(), *v, flags); };                                             \
    inline void Input(const std::string& label, vex3i& v, ImGuiInputTextFlags flags = 0) { InputInt3(label.c_str(), *v, flags); };                                             \
    inline void Input(const std::string& label, vex4i& v, ImGuiInputTextFlags flags = 0) { InputInt4(label.c_str(), *v, flags); };                                             \
    inline void DragFloat(const std::string& label, vex2f& v, float v_speed, float _min, float _max) { DragFloat2(label.c_str(), *v, v_speed, _min, _max); };                  \
    inline void DragFloat(const std::string& label, vex3f& v, float v_speed, float _min, float _max) { DragFloat3(label.c_str(), *v, v_speed, _min, _max); };                  \
    inline void DragFloat(const std::string& label, vex4f& v, float v_speed, float _min, float _max) { DragFloat4(label.c_str(), *v, v_speed, _min, _max); };                  \
    inline void DragInt(const std::string& label, vex2i& v, int v_speed, int _min, int _max) { DragInt2(label.c_str(), *v, v_speed, _min, _max); };                            \
    inline void DragInt(const std::string& label, vex3i& v, int v_speed, int _min, int _max) { DragInt3(label.c_str(), *v, v_speed, _min, _max); };                            \
    inline void DragInt(const std::string& label, vex4i& v, int v_speed, int _min, int _max) { DragInt4(label.c_str(), *v, v_speed, _min, _max); };                            \
    inline void Drag(const std::string& label, vex2f& v, float v_speed, float _min, float _max) { DragFloat2(label.c_str(), *v, v_speed, _min, _max); };                       \
    inline void Drag(const std::string& label, vex3f& v, float v_speed, float _min, float _max) { DragFloat3(label.c_str(), *v, v_speed, _min, _max); };                       \
    inline void Drag(const std::string& label, vex4f& v, float v_speed, float _min, float _max) { DragFloat4(label.c_str(), *v, v_speed, _min, _max); };                       \
    inline void Drag(const std::string& label, vex2i& v, int v_speed, int _min, int _max) { DragInt2(label.c_str(), *v, v_speed, _min, _max); };                               \
    inline void Drag(const std::string& label, vex3i& v, int v_speed, int _min, int _max) { DragInt3(label.c_str(), *v, v_speed, _min, _max); };                               \
    inline void Drag(const std::string& label, vex4i& v, int v_speed, int _min, int _max) { DragInt4(label.c_str(), *v, v_speed, _min, _max); };                               \
    inline void SliderFloat(const std::string& label, vex2f& v, float _min, float _max) { SliderFloat2(label.c_str(), *v, _min, _max); };                                      \
    inline void SliderFloat(const std::string& label, vex3f& v, float _min, float _max) { SliderFloat3(label.c_str(), *v, _min, _max); };                                      \
    inline void SliderFloat(const std::string& label, vex4f& v, float _min, float _max) { SliderFloat4(label.c_str(), *v, _min, _max); };                                      \
    inline void SliderInt(const std::string& label, vex2i& v, int _min, int _max) { SliderInt2(label.c_str(), *v, _min, _max); };                                              \
    inline void SliderInt(const std::string& label, vex3i& v, int _min, int _max) { SliderInt3(label.c_str(), *v, _min, _max); };                                              \
    inline void SliderInt(const std::string& label, vex4i& v, int _min, int _max) { SliderInt4(label.c_str(), *v, _min, _max); };                                              \
    inline void Slider(const std::string& label, vex2f& v, float _min, float _max) { SliderFloat2(label.c_str(), *v, _min, _max); };                                           \
    inline void Slider(const std::string& label, vex3f& v, float _min, float _max) { SliderFloat3(label.c_str(), *v, _min, _max); };                                           \
    inline void Slider(const std::string& label, vex4f& v, float _min, float _max) { SliderFloat4(label.c_str(), *v, _min, _max); };                                           \
    inline void Slider(const std::string& label, vex2i& v, int _min, int _max) { SliderInt2(label.c_str(), *v, _min, _max); };                                                 \
    inline void Slider(const std::string& label, vex3i& v, int _min, int _max) { SliderInt3(label.c_str(), *v, _min, _max); };                                                 \
    inline void Slider(const std::string& label, vex4i& v, int _min, int _max) { SliderInt4(label.c_str(), *v, _min, _max); };                                                 \
};