class XsPhysics {
private:
    unsigned int id = 0u;
public:
    XsPhysics() = default;
    XsPhysics(const XsPhysics&) = default;
    bool sleep = false, istouch = false;
    inline unsigned int& operator()() { return id; };
    vex3f pos = 0.f;
    vex3f vel = 0.f;
    vex3f bouncy = 0.f;
    vex3f scale = 1.f;
};

class XsPhysicsWorld {
private:
    std::vector<XsPhysics*> _meshs;
public:
    XsPhysicsWorld() = default;
    XsPhysicsWorld(const XsPhysicsWorld&) = default;
    vex3f gravity = vex3f(0.f, -9.8f, 0.f);
    inline XsPhysicsWorld& operator<<(XsPhysics& v) { _meshs.push_back(&v); return *this; };
    //XsPhysicsWorld& operator>>(XsPhysics& v) {
    //    for (size_t i = 0u; i < _meshs.size(); i++)
    //        if (*(_meshs[i]) == v) {
    //            _meshs.erase(_meshs.begin() + i);
    //            break;
    //        };
    //    return *this;
    //};
    inline std::vector<XsPhysics*>& meshs() { return _meshs; };

    void step() {
        for (size_t i = 0u; i < _meshs.size(); i++) {
            if (!(*_meshs[i]).sleep) {
                (*_meshs[i]).vel += gravity / 1000.f;
                (*_meshs[i]).vel *= 0.98f;
                (*_meshs[i]).pos += (*_meshs[i]).vel;
            };
            for (size_t j = 0u; j < _meshs.size(); j++) {
                if ((*_meshs[i]).pos.x + (*_meshs[i]).scale.x > (*_meshs[j]).pos.x - (*_meshs[j]).scale.x && (*_meshs[i]).pos.x - (*_meshs[i]).scale.x < (*_meshs[j]).pos.x + (*_meshs[j]).scale.x &&
                    (*_meshs[i]).pos.y + (*_meshs[i]).scale.y > (*_meshs[j]).pos.y - (*_meshs[j]).scale.y && (*_meshs[i]).pos.y - (*_meshs[i]).scale.y < (*_meshs[j]).pos.y + (*_meshs[j]).scale.y &&
                    (*_meshs[i]).pos.z + (*_meshs[i]).scale.z > (*_meshs[j]).pos.z - (*_meshs[j]).scale.z && (*_meshs[i]).pos.z - (*_meshs[i]).scale.z < (*_meshs[j]).pos.z + (*_meshs[j]).scale.z) {
                    (*_meshs[i]).istouch = true;
                    (*_meshs[j]).istouch = true;
                    if (fabs(((*_meshs[i]).pos.x + (*_meshs[i]).scale.x) - ((*_meshs[j]).pos.x - (*_meshs[j]).scale.x)) <
                        fabs(((*_meshs[i]).pos.y + (*_meshs[i]).scale.y) - ((*_meshs[j]).pos.y - (*_meshs[j]).scale.y)) &&
                        fabs(((*_meshs[i]).pos.x + (*_meshs[i]).scale.x) - ((*_meshs[j]).pos.x - (*_meshs[j]).scale.x)) <
                        fabs(((*_meshs[i]).pos.z + (*_meshs[i]).scale.z) - ((*_meshs[j]).pos.z - (*_meshs[j]).scale.z))) {
                        if ((*_meshs[i]).pos.x > (*_meshs[j]).pos.x) {
                            if (!(*_meshs[i]).sleep) {
                                (*_meshs[i]).vel.x = 0;
                                (*_meshs[i]).pos.x = (*_meshs[j]).pos.x + (*_meshs[j]).scale.x + (*_meshs[i]).scale.x;
                            }
                            if (!(*_meshs[j]).sleep) {
                                (*_meshs[j]).vel.x = 0;
                                (*_meshs[j]).pos.x = (*_meshs[i]).pos.x - (*_meshs[i]).scale.x - (*_meshs[j]).scale.x;
                            }
                        }
                        else {
                            if (!(*_meshs[i]).sleep) {
                                (*_meshs[i]).vel.x = 0;
                                (*_meshs[i]).pos.x = (*_meshs[j]).pos.x - (*_meshs[j]).scale.x - (*_meshs[i]).scale.x;
                            }
                            if (!(*_meshs[j]).sleep) {
                                (*_meshs[j]).vel.x = 0;
                                (*_meshs[j]).pos.x = (*_meshs[i]).pos.x + (*_meshs[i]).scale.x + (*_meshs[j]).scale.x;
                            }
                        };
                    }
                    else if (fabs(((*_meshs[i]).pos.y + (*_meshs[i]).scale.y) - ((*_meshs[j]).pos.y - (*_meshs[j]).scale.y)) <
                        fabs(((*_meshs[i]).pos.z + (*_meshs[i]).scale.z) - ((*_meshs[j]).pos.z - (*_meshs[j]).scale.z))) {
                        if ((*_meshs[i]).pos.y > (*_meshs[j]).pos.y) {
                            if (!(*_meshs[i]).sleep) {
                                (*_meshs[i]).vel.y = 0;
                                (*_meshs[i]).pos.y = (*_meshs[j]).pos.y + (*_meshs[j]).scale.y + (*_meshs[i]).scale.y;
                            }
                            if (!(*_meshs[j]).sleep) {
                                (*_meshs[j]).vel.y = 0;
                                (*_meshs[j]).pos.y = (*_meshs[i]).pos.y - (*_meshs[i]).scale.y - (*_meshs[j]).scale.y;
                            }
                        }
                        else {
                            if (!(*_meshs[i]).sleep) {
                                (*_meshs[i]).vel.y = 0;
                                (*_meshs[i]).pos.y = (*_meshs[j]).pos.y - (*_meshs[j]).scale.y - (*_meshs[i]).scale.y;
                            }
                            if (!(*_meshs[j]).sleep) {
                                (*_meshs[j]).vel.y = 0;
                                (*_meshs[j]).pos.y = (*_meshs[i]).pos.y + (*_meshs[i]).scale.y + (*_meshs[j]).scale.y;
                            }
                        };
                    }
                    else {
                        if ((*_meshs[i]).pos.z > (*_meshs[j]).pos.z) {
                            if (!(*_meshs[i]).sleep) {
                                (*_meshs[i]).vel.z = 0;
                                (*_meshs[i]).pos.z = (*_meshs[j]).pos.z + (*_meshs[j]).scale.z + (*_meshs[i]).scale.z;
                            }
                            if (!(*_meshs[j]).sleep) {
                                (*_meshs[j]).vel.z = 0;
                                (*_meshs[j]).pos.z = (*_meshs[i]).pos.z - (*_meshs[i]).scale.z - (*_meshs[j]).scale.z;
                            }
                        }
                        else {
                            if (!(*_meshs[i]).sleep) {
                                (*_meshs[i]).vel.z = 0;
                                (*_meshs[i]).pos.z = (*_meshs[j]).pos.z - (*_meshs[j]).scale.z - (*_meshs[i]).scale.z;
                            }
                            if (!(*_meshs[j]).sleep) {
                                (*_meshs[j]).vel.z = 0;
                                (*_meshs[j]).pos.z = (*_meshs[i]).pos.z + (*_meshs[i]).scale.z + (*_meshs[j]).scale.z;
                            }
                        };
                    };
                }
                else {
                    (*_meshs[i]).istouch = false;
                    (*_meshs[j]).istouch = false;
                };
            };
        };
    };
};