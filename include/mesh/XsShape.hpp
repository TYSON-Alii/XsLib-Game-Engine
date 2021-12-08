struct XsMesh {
	inline XsMesh(const std::string& _name) { name = _name; };
	std::string name;
	XsVerts data;
	XsEnum mode = Xs.Enum.Vertex;
	XsEnum poly = Xs.Enum.Triangle;
	inline XsMesh& operator<<(XsVerts verts) { data = verts; return *this; };
};

struct XsShape {
	inline XsShape(const std::string& _name) { name = _name; };
	std::string name;
	bool hide = false;
	float lineWidth = 1.f, pointSize = 1.f;
	inline static const size_t npos = std::string::npos;
	size_t tex = npos;
	size_t mesh = npos;
	inline XsMesh& getMesh() const;
	inline XsTexture& getTexture() const;
	XsMesh& setMesh(const std::string& name);
	XsTexture& setTexture(const std::string& name);
	vex3f pos = 0.f, rot = 0.f, scale = 1.f, origin = 0.f;
	vex4f color = 1.f;
	inline vex3f& move(float x, float y, float z)			{ return pos += vex3f(x, y, z); };
	template <typename T> inline vex3f& move(vex4<T> xyz)	{ return pos += xyz;			};
	template <typename T> inline vex3f& move(vex3<T> xyz)	{ return pos += xyz;			};
	template <typename T> inline vex3f& move(vex2<T> xy)	{ return pos += xy;				};
	friend std::ostream& operator<<(std::ostream& os, const XsShape& v);
};