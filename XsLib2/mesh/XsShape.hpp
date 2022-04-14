struct XsColor : vex4ub {
	using vex4ub::vex4;
	XsColor() : vex4ub(255) { };
	XsColor(const XsColor&) = default;
	XsColor& operator=(const XsColor& v) { x = v.x; y = v.y; z = v.z; w = v.w; return *this; };
	inline operator int() const { return (int(r)<<16) + (int(g)<<8) + int(b); }
	inline operator std::string() const {
		return ::str("R: ") + std::to_string(r) +
			", G: " + std::to_string(g) +
			", B: " + std::to_string(b) +
			", A: " + std::to_string(a);
	};
	inline operator vex4f() const { return to_rgb32(); };
	inline operator vex4d() const { return to_rgb64(); };
	byte &r = vex4ub::x, &g = vex4ub::y, &b = vex4ub::z, &a = vex4ub::w;
	inline XsColor& hex(int hex_code) { return self = XsColor((hex_code >> 16) & 0xff, (hex_code >> 8) & 0xff, (hex_code) & 0xff); };
	inline XsColor& hex(const ::str& hex_code) { return hex(std::stoi(hex_code, nullptr, 16)); };
	XsColor& hsv(const vex3f& _hsv) {
		const auto [H, S, V] = _hsv;
		float s = S / 100.f, v = V / 100.f, C = s * v;
		float X = C * (1.f - fabs(fmod(H / 60.f, 2) - 1.f));
		const float& m = v - C;
		float r, g, b;
		if (H >= 0 && H < 60) { r = C, g = X, b = 0; }
		else if (H >= 60 && H < 120) { r = X, g = C, b = 0; }
		else if (H >= 120 && H < 180) { r = 0, g = C, b = X; }
		else if (H >= 180 && H < 240) { r = 0, g = X, b = C; }
		else if (H >= 240 && H < 300) { r = X, g = 0, b = C; }
		else { r = C, g = 0, b = X; };
		self.r = byte(r + m) * 255;
		self.g = byte(g + m) * 255;
		self.b = byte(b + m) * 255;
	};
	vex3f to_hsv() const {
		const auto& rgb = *this;
		vex3f hsv;
		byte rgbMin = min(rgb), rgbMax = max(rgb);
		hsv.z = rgbMax;
		if (hsv.z == 0) return hsv = 0;
		hsv.y = 255 * long(rgbMax - rgbMin) / hsv.z;
		if (hsv.y == 0) {
			hsv.x = 0;
			return hsv;
		};
		if (rgbMax == rgb.r) hsv.x = 0 + 43 * (rgb.g - rgb.b) / (rgbMax - rgbMin);
		else if (rgbMax == rgb.g) hsv.x = 85 + 43 * (rgb.b - rgb.r) / (rgbMax - rgbMin);
		else hsv.x = 171 + 43 * (rgb.r - rgb.g) / (rgbMax - rgbMin);
		return hsv;
	};
	inline ::str to_hex() const {
		std::stringstream stream;
		stream << std::setfill('0') << std::setw(6) << std::hex << int(*this);
		return stream.str();
	};
	inline vex4f to_rgb32() const { return (vex4f() << self) / 255.f; };
	inline vex4d to_rgb64() const { return (vex4d() << self) / 255.0; };
};
struct XsMaterial {
	XsMaterial() = default;
	XsMaterial(const XsMaterial&) = default;
	vex3f ambient = 0.0f;
	vex3f diffuse = 1.f;
	vex3f specular = 0.25f;
	f32 shininess = 2.5f;
	XsColor color = 255;
};
class XsLight : public XsEntity {
public:
	XsLight() = default;
	XsLight(const XsLight&) = default;
	XsLight(const vex3f& _pos, const XsColor& _color, const f32& _power = 1.f) { pos = _pos; color = _color; power = _power; };
	vex3f pos = 0.f;
	XsColor color = 255;
	f32 power = 1.f;
};
struct XsTransform {
	XsTransform() = default;
	vex3f pos = 0.f, rot = 0.f, scale = 1.f, origin = 0.f;
	inline vex3f& move(const vex3f& xyz) { return pos += xyz; };
	inline vex3f& move(const f32& x = 0.f, const f32& y = 0.f, const f32& z = 0.f) { return pos += vex3f(x, y, z); };
	//inline vex3<scalar>& lookAt(const vex3<scalar>& _at) { return (rot << glm::eulerAngles(glm::quat_cast(glm::lookAt(((glm::vec3)pos), ((glm::vec3)pos)+((glm::vec3)_at), glm::vec3(0, 1, 0))))) *= (180.f / 3.14); };
	XsTransform& reset() { return self = XsTransform(); };
	inline mat4 matrix() const {
		return
			glm::translate(glm::mat4(1.f), (glm::vec3)pos)*
			glm::rotate(glm::mat4(1.f), rot.x/180.f*3.14f, glm::vec3(1, 0, 0))*
			glm::rotate(glm::mat4(1.f), rot.y/180.f*3.14f, glm::vec3(0, 1, 0))*
			glm::rotate(glm::mat4(1.f), rot.z/180.f*3.14f, glm::vec3(0, 0, 1))*
			glm::scale(glm::mat4(1.f), (glm::vec3)scale)*
			glm::translate(glm::mat4(1.f), (glm::vec3)origin);
	};
};
class XsShape : public XsEntity, public XsMaterial, public XsTransform {
public:
	XsShape(const str& _tag = "") : XsEntity(_tag) { };
	void Destroy();
	bool hide = false;
	XsMesh* mesh = nullptr;
	XsTexture* tex = nullptr;
};