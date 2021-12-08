class XsShapeDynamic;
class XsPhysx {
protected:
	PxDefaultAllocator		gAllocator;
	PxDefaultErrorCallback	gErrorCallback;
	PxDefaultCpuDispatcher* gDispatcher = NULL;
	PxFoundation* gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);
	physx::PxPhysics* gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, NULL);
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	physx::PxScene* gScene = nullptr;
public:
	XsPhysx() = delete;
	XsPhysx(vex3f gravity) {
		sceneDesc.gravity = PxVec3(gravity.x, gravity.y, gravity.z);
		gDispatcher = PxDefaultCpuDispatcherCreate(1);
		sceneDesc.cpuDispatcher = gDispatcher;
		sceneDesc.filterShader = PxDefaultSimulationFilterShader;
		gScene = gPhysics->createScene(sceneDesc);
	};
};
class XsShapeDynamic {
protected:
	vex3f _pos = 0.f, _rot = 0.f, _scale = 1.f, _origin = 0.f;
	vex4f _color = 1.f;
public:
	struct {
		physx::PxMaterial*		material = nullptr;
		physx::PxRigidDynamic*	body	 = nullptr;
		physx::PxShape*			shape	 = nullptr;
	} physics;
	XsShapeDynamic() = delete;
	XsShapeDynamic(physx::PxGeometry* geo, float v1, float v2, float v3) {  };
	//XsShapeDynamic(const std::string& loadfrom);
	void load(const std::string& loadfrom);
	XsVerts* vert = nullptr;
	decltype(Xs.Enum)::Enum_t mode = Xs.Enum.Vertex;
	GLenum glmode = GL_TRIANGLES;
	XsTexture* tex = nullptr;
	XsShader* shader = nullptr;
	vex3f pos() const { return pos; };
	vex3f pos(vex3f xyz) { return (pos = xyz); };
	vex3f pos(const float& v) { return (pos = v); };
	vex3f pos(const float& x, const float& y, const float& z) { return (pos = vex3f(x, y, z)); };
	vex3f pos(const float& x, const float& y) { return (pos = vex2f(x, y)); };
	vex3f rot() const { return rot; };
	vex3f rot(vex3f xyz) { return (rot = xyz); };
	vex3f rot(const float& v) { return (rot = v); };
	vex3f rot(const float& x, const float& y, const float& z) { return (rot = vex3f(x, y, z)); };
	vex3f rot(const float& x, const float& y) { return (rot = vex2f(x, y)); };
	vex3f& scale() const { return scale; };
	vex3f& scale(vex3f xyz) { return (scale = xyz); };
	vex3f& scale(const float& v) { return (scale = v); };
	vex3f& scale(const float& x, const float& y, const float& z) { return (scale = vex3f(x, y, z)); };
	vex3f& scale(const float& x, const float& y) { return (scale = vex2f(x, y)); };
	vex3f& origin() const { return origin; };
	vex3f& origin(vex3f xyz) { return (origin = xyz); };
	vex3f& origin(const float& v) { return (origin = v); };
	vex3f& origin(const float& x, const float& y, const float& z) { return (origin = vex3f(x, y, z)); };
	vex3f& origin(const float& x, const float& y) { return (origin = vex2f(x, y)); };
	vex3f& color() const { return _color; };
	vex3f& color(vex4f rgba) { return (_color = rgba); };
	vex3f& color(vex3f rgb) { return (_color = rgb); };
	vex3f& color(const float& rgba) { return (_color = rgba); };
	vex3f& color(const float& r, const float& g, const float& b) { return (color = vex3f(r, g, b)); };
	vex3f& color(const float& r, const float& g, const float& b, const float& a) { return (color = vex4f(r, g, b, a)); };

	void draw(const bool& _reset_matrix = true) {
		if (_reset_matrix)
			glLoadIdentity();
		glTranslatef(pos);
		Xs.Math.Limit(rot, vex3f(0.f), vex3f(360.f));
		glRotatef(rot);
		glScalef(scale);
		glTranslatef(origin);
		glColor4f(color);
		if (vert != nullptr) {
			if (tex != nullptr)
				tex->bind();
			else
				glBindTexture(GL_TEXTURE_2D, 0);
			if (shader != nullptr) shader->use();
			Xs.Draw(*vert, mode, glmode);
			if (shader != nullptr) glUseProgram(0);
		};
	};
	void save(const std::string& filename) const;
	operator strinx() const;
	friend std::ostream& operator<<(std::ostream& os, const XsShape& v);
};