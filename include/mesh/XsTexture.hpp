class XsTexture {
private:
    vex2i _scale;
    bool _isl = false;
    std::string file_name;
public:
    std::string name;
    inline XsTexture(const std::string& _name) { name = _name; };
    XsTexData data = 0u;
    GLenum filter = GL_NEAREST;
    vex2i scale() { return _scale; };
    std::string fileName() { return file_name; };
    bool isLoad() { return _isl; };
    void load(const std::string& _file_name);
};
void XsTexture::load(const std::string& _file_name) {
    file_name = _file_name;
    glGenTextures(1, &data);
    glBindTexture(GL_TEXTURE_2D, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    int _widthh, _heightt, _nrChannels;
    auto __data = stbi_load(_file_name.c_str(), &_widthh, &_heightt, &_nrChannels, 0);
    if (__data) {
        _scale = vex2i(_widthh, _heightt);
        glTexImage2D(GL_TEXTURE_2D, 0, (_nrChannels == 4) ? GL_RGBA : GL_RGB, _widthh, _heightt, 0, (_nrChannels == 4) ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, __data);
        //glGenerateMipmap(GL_TEXTURE_2D);
        _isl = true;
    }
    else {
        std::cout << "Failed to Load \""s + file_name + '"' + " Image.\n";
        Xs.Log << ("Failed to Load \""s + file_name + '"' + " Image.\n").c_str();
    };
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(__data);
};