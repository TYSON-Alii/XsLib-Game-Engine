namespace px = physx;
px::PxTriangleMeshGeometry* XsPxTriangleMesh(const XsMesh& mesh);
enum XsRigidType { XsDynamic, XsStatic };
template <XsRigidType> class XsRigid;
template <> class XsRigid<XsDynamic> : public XsMaterial {
private:
    px::PxShape* sh;
    px::PxRigidDynamic* bd;
    px::PxMaterial* mt;
    vex3b l_lockAxis = false;
    vex3b a_lockAxis = false;
public:
    XsRigid(px::PxGeometry* geom, vex3f mat);
    XsMesh* mesh = nullptr;
    XsTexture* tex = nullptr;
    vex3f scale = 1.f, origin = 0.f;
    inline vex3b lockLinAxis() const { return l_lockAxis; };
    inline vex3b lockAngAxis() const { return a_lockAxis; };
    inline vex3b lockLinAxis(const vex3b& axis_xyz) {
        if (axis_xyz.x)
            bd->setRigidDynamicLockFlag(px::PxRigidDynamicLockFlag::eLOCK_LINEAR_X, true);
        if (axis_xyz.y)
            bd->setRigidDynamicLockFlag(px::PxRigidDynamicLockFlag::eLOCK_LINEAR_Y, true);
        if (axis_xyz.z)
            bd->setRigidDynamicLockFlag(px::PxRigidDynamicLockFlag::eLOCK_LINEAR_Z, true);
        return l_lockAxis = axis_xyz;
    };
    inline vex3b lockAngAxis(const vex3b& axis_xyz) {
        if (axis_xyz.x)
            bd->setRigidDynamicLockFlag(px::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X, true);
        if (axis_xyz.y)
            bd->setRigidDynamicLockFlag(px::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y, true);
        if (axis_xyz.z)
            bd->setRigidDynamicLockFlag(px::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z, true);
        return l_lockAxis = axis_xyz;
    };
    inline vex3f mass() const { return bd->getMass(); };
    inline vex3f mass(const float& v) { bd->setMass(v); return mass(); };
    inline auto operator*() { return this; };
    inline vex3f pos() const { return vex3f(bd->getGlobalPose().p.x, bd->getGlobalPose().p.y, bd->getGlobalPose().p.z); };
    inline vex3f pos(const vex3f& v) { bd->setGlobalPose(px::PxTransform(v.x, v.y, v.z)); return v; };
    inline vex3f pos(const float& v_x, const float& v_y, const float& v_z) { bd->setGlobalPose(px::PxTransform(v_x, v_y, v_z)); return vex3f(v_x, v_y, v_z); };
    inline vex3f rot() { return vex3f(bd->getGlobalPose().q.rotate(px::PxVec3(1)).x, bd->getGlobalPose().q.rotate(px::PxVec3(1)).y, bd->getGlobalPose().q.rotate(px::PxVec3(1)).z); };
    inline void force(const vex3f& v) { bd->addForce(px::PxVec3(v.x,v.y,v.z),px::PxForceMode::eACCELERATION); };
    inline void hit(const vex3f& v) { bd->addForce(px::PxVec3(v.x, v.y, v.z), px::PxForceMode::eIMPULSE); }
    inline vex3f velLin() const { return vex3f(bd->getLinearVelocity().x, bd->getLinearVelocity().y, bd->getLinearVelocity().z); };
    inline void velLin(const vex3f& v) { bd->setLinearVelocity(physx::PxVec3(v.x, v.y, v.z)); };
    inline void velLin(const float& _v1, const float& _v2, const float& _v3) { bd->setLinearVelocity(physx::PxVec3(_v1, _v2, _v3)); };
    inline vex3f velAng() const { return vex3f(bd->getAngularVelocity().x, bd->getAngularVelocity().y, bd->getAngularVelocity().z); };
    inline void velAng(const vex3f& _v) { bd->setAngularVelocity(physx::PxVec3(_v.x, _v.y, _v.z)); };
    inline void velAng(const float& _v1, const float& _v2, const float& _v3) { bd->setAngularVelocity(physx::PxVec3(_v1, _v2, _v3)); };
    inline void sleep() { bd->putToSleep(); };
    inline void wakeUp() { bd->wakeUp(); };
    inline void setFlag(px::PxActorFlag::Enum v) { bd->setActorFlag(v, true); };
    inline void setFlag(px::PxActorFlag::Enum v, const bool& b) { bd->setActorFlag(v, b); };
    inline void setFlag(px::PxRigidBodyFlag::Enum v) { bd->setRigidBodyFlag(v, true); };
    inline void setFlag(px::PxRigidBodyFlag::Enum v, const bool b) { bd->setRigidBodyFlag(v, b); };
    virtual void loop() { };
    inline glm::mat4 matrix() const {
        const px::PxMat44 m(physx::PxShapeExt::getGlobalPose(*sh, *bd));
        return glm::scale(glm::mat4(1.f), (glm::vec3)scale) * glm::translate(glm::mat4(1.f), (glm::vec3)origin) * glm::mat4(m.column0.x, m.column0.y, m.column0.z, m.column0.w, m.column1.x, m.column1.y, m.column1.z, m.column1.w, m.column2.x, m.column2.y, m.column2.z, m.column2.w, m.column3.x, m.column3.y, m.column3.z, m.column3.w);
    };
    void draw(XsEngine* eng);
};
template <> class XsRigid<XsStatic> : public XsMaterial {
private:
    px::PxShape* sh;
    px::PxRigidStatic* bd;
    px::PxMaterial* mt;
public:
    XsRigid(px::PxGeometry* geom, vex3f mat);
    XsMesh* mesh = nullptr;
    XsTexture* tex = nullptr;
    vex3f scale = 1.f, origin = 0.f;
    auto operator*() { return this; };
    inline vex3f pos() const { return vex3f(bd->getGlobalPose().p.x, bd->getGlobalPose().p.y, bd->getGlobalPose().p.z); };
    inline vex3f pos(const vex3f& v) { bd->setGlobalPose(px::PxTransform(v.x, v.y, v.z)); return v; };
    inline vex3f pos(const float& v_x, const float& v_y, const float& v_z) { bd->setGlobalPose(px::PxTransform(v_x, v_y, v_z)); return vex3f(v_x, v_y, v_z); };
    vex3f rot() { return vex3f(bd->getGlobalPose().q.rotate(px::PxVec3(1)).x, bd->getGlobalPose().q.rotate(px::PxVec3(1)).y, bd->getGlobalPose().q.rotate(px::PxVec3(1)).z); };
    virtual void loop() { };
    inline glm::mat4 matrix() const {
        const physx::PxMat44 m(physx::PxShapeExt::getGlobalPose(*sh, *bd));
        return glm::scale(glm::mat4(1.f), (glm::vec3)scale) * glm::translate(glm::mat4(1.f), (glm::vec3)origin) * (*static_cast<glm::mat4*>((void*)&m.column0.x));
    };
    void draw(XsEngine* eng);
};
#define PX_RELEASE(x)	if(x)	{ x->release(); x = NULL;	}
#define MAX_NUM_ACTOR_SHAPES 128
struct {
    px::PxDefaultAllocator		gAllocator;
    px::PxDefaultErrorCallback	gErrorCallback;
    px::PxDefaultCpuDispatcher* gDispatcher = NULL;
    px::PxFoundation* gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);
    px::PxPhysics* gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, px::PxTolerancesScale(), true, NULL);
    px::PxSceneDesc sceneDesc = [&]() -> px::PxSceneDesc {
        px::PxSceneDesc s(gPhysics->getTolerancesScale());
        s.gravity = px::PxVec3(0.0f, -9.81f, 0.0f);
        gDispatcher = px::PxDefaultCpuDispatcherCreate(1);
        s.cpuDispatcher = gDispatcher;
        s.filterShader = px::PxDefaultSimulationFilterShader;
        return s;
    }();
    px::PxCooking* gCook = PxCreateCooking(PX_PHYSICS_VERSION, *gFoundation, px::PxCookingParams(px::PxTolerancesScale()));
    px::PxScene* gScene = gPhysics->createScene(sceneDesc);
    struct {
        inline auto Box(const vex3f& scale) { return new px::PxBoxGeometry(scale.x, scale.y, scale.z); };
        inline auto Box(const float& scale_x, const float& scale_y, const float& scale_z) { return new px::PxBoxGeometry(scale_x, scale_y, scale_z); };
        inline auto Sphere(const float& radius) { return new px::PxCapsuleGeometry(radius, radius); };
        inline auto Capsule(const float& radius, const float& half_height) { return new px::PxCapsuleGeometry(radius, half_height); };
        inline auto TriangleMesh(const XsMesh& mesh) { return XsPxTriangleMesh(mesh); };
    } Geom;
    void operator()() {
        gScene->simulate(2.0f / Xs.Fps);
        gScene->fetchResults(true);
    };
} XsPhysx;
px::PxTriangleMeshGeometry* XsPxTriangleMesh(const XsMesh& mesh) {
    px::PxTriangleMeshDesc desc;
    desc.points.count = mesh.pos.size();
    desc.points.stride = sizeof(vex3f);
    desc.points.data = mesh.pos.data();
    px::PxDefaultMemoryOutputStream _wb;
    XsPhysx.gCook->cookTriangleMesh(desc, _wb);
    px::PxDefaultMemoryInputData _rb(_wb.getData(), _wb.getSize());
    return new px::PxTriangleMeshGeometry(XsPhysx.gPhysics->createTriangleMesh(_rb));
};
XsRigid<XsDynamic>::XsRigid(px::PxGeometry* geom, vex3f sfric_dfric_res) {
    bd = XsPhysx.gPhysics->createRigidDynamic(px::PxTransform(0, 0, 0));
    mt = XsPhysx.gPhysics->createMaterial(sfric_dfric_res.x, sfric_dfric_res.y, sfric_dfric_res.z);
    sh = XsPhysx.gPhysics->createShape(*geom, *mt);
    bd->attachShape(*sh);
    XsPhysx.gScene->addActor(*bd);
};
XsRigid<XsStatic>::XsRigid(px::PxGeometry* geom, vex3f sfric_dfric_res) {
    bd = XsPhysx.gPhysics->createRigidStatic(px::PxTransform(0, 0, 0));
    mt = XsPhysx.gPhysics->createMaterial(sfric_dfric_res.x, sfric_dfric_res.y, sfric_dfric_res.z);
    sh = XsPhysx.gPhysics->createShape(*geom, *mt);
    bd->attachShape(*sh);
    XsPhysx.gScene->addActor(*bd);
};
typedef XsRigid<XsDynamic> XsRigidDynamic;
typedef XsRigid<XsStatic> XsRigidStatic;