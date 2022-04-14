class XsTexture : public XsEntity {
protected:
    vex2ui _scale = 0;
    bool _isl = false;
    static const GLenum filter = GL_NEAREST;
    str path_, filename_;
public:
    XsTexture() = default;
    XsTexture(const str& _f) { load(_f); };
    XsTexData data = 0;
    inline vex2ui scale() const { return _scale; };
    inline str filePath() const { return path_; };
    inline str fileName() const { return filename_; };
    inline bool isLoad() const { return _isl; };
    auto& loadFromMemory(ptr _data, const uint& x, const uint& y, const bool& alpha = false) {
        glGenTextures(1, &data);
        glBindTexture(GL_TEXTURE_2D, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
        if (_data) {
            _scale = vex2ui(x, y);
            const auto& format = alpha ? GL_RGBA : GL_RGB;
            glTexImage2D(GL_TEXTURE_2D, 0, format, x, y, 0, format, GL_UNSIGNED_BYTE, _data);
            _isl = true;
        }
        glBindTexture(GL_TEXTURE_2D, 0);
        return *this;
    };
    XsTexture& load(const str& _file_name) {
        path_ = _file_name;
        filename_ = path_.substr(path_.find_last_of("/\\") + 1);
        glGenTextures(1, &data);
        glBindTexture(GL_TEXTURE_2D, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
        int _widthh, _heightt, _nrChannels;
        auto __data = stbi_load(_file_name.c_str(), &_widthh, &_heightt, &_nrChannels, 0);
        if (__data) {
            _scale = vex2ui(_widthh, _heightt);
            glTexImage2D(GL_TEXTURE_2D, 0, (_nrChannels == 4) ? GL_RGBA : GL_RGB, _widthh, _heightt, 0, (_nrChannels == 4) ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, __data);
            _isl = true;
        }
        else
            std::cerr << "Failed to Load \"" << path_ << '"' << " Image.\n";
        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(__data);
        return *this;
    };
    auto& create(const uint& x, const u32& y, const vex3f& color) {
        std::vector<vex4<unsigned char>> _data(x * y, vex4<unsigned char>(color * 255, 255));
        loadFromMemory((void*)_data.data(), x, y, true);
        return *this;
    };
    auto& create(const u32& x, const u32& y, const vex4f& color) {
        std::vector<vex4<unsigned char>> _data(x * y, vex4<unsigned char>(color * 255));
        loadFromMemory((void*)_data.data(), x, y, true);
        return *this;
    };
    auto& createChecker(const u32& x = 2u, const u32& y = 2u, const vex3f& first_color = 1, const vex3f& second_color = 0) {
        std::vector<vex4<unsigned char>> _data(x * y, vex4<unsigned char>(0,0,0,255));
        bool s = false, l = false;
        u32 j = 0u;
        const vex3<unsigned char>& fc = first_color * 255;
        const vex3<unsigned char>& sc = second_color * 255;
        for (auto& i : _data) {
            i = s ? fc : sc;
            s = !s;
            j++;
            if (j == x) {
                s = l = !l;
                j = 0u;
            };
        };
        loadFromMemory((void*)_data.data(), x, y, true);
        return *this;
    };
    auto& createCheckerA(const u32& x = 2u, const u32& y = 2u, const vex4f& first_color = 1, const vex4f& second_color = { 0,0,0,1 }) {
        std::vector<vex4<unsigned char>> _data(x * y);
        bool s = false, l = false;
        u32 j = 0u;
        const vex4<unsigned char>& fc = first_color * 255;
        const vex4<unsigned char>& sc = second_color * 255;
        for (auto& i : _data) {
            i = s ? fc : sc;
            s = !s;
            j++;
            if (j == x) {
                s = l = !l;
                j = 0u;
            };
        };
        loadFromMemory((void*)_data.data(), x, y, true);
        return *this;
    };
    auto& createNoise(const u32& x = 250u, const u32& y = 250u, const vex3f& max = 1, const vex3f& min = 0) {
        std::vector<vex4<unsigned char>> _data(x * y, vex4<unsigned char>(0,0,0,255));
        const auto& b = max - min;
        for (auto& i : _data) {
            i = vex3<unsigned char>(
                (std::fmod((float)std::rand() / (float)RAND_MAX, b.x) + min.x) * 255,
                (std::fmod((float)std::rand() / (float)RAND_MAX, b.y) + min.y) * 255,
                (std::fmod((float)std::rand() / (float)RAND_MAX, b.z) + min.z) * 255);
        };
        loadFromMemory((void*)_data.data(), x, y, true);
        return *this;
    }
    auto& createNoiseA(const u32& x = 250u, const u32& y = 250u, const vex4f& max = 1, const vex4f& min = { 0,0,0,1 }) {
        std::vector<vex4<unsigned char>> _data(x * y);
        const auto& b = max - min;
        for (auto& i : _data) {
            i = vex4<unsigned char>(
                (std::fmod((float)std::rand() / (float)RAND_MAX, b.x) + min.x) * 255,
                (std::fmod((float)std::rand() / (float)RAND_MAX, b.y) + min.y) * 255,
                (std::fmod((float)std::rand() / (float)RAND_MAX, b.z) + min.z) * 255,
                (std::fmod((float)std::rand() / (float)RAND_MAX, b.w) + min.w) * 255);
        };
        loadFromMemory((void*)_data.data(), x, y, true);
        return *this;
    }
    auto& createGradientY(const u32& x = 250u, const u32& y = 250u, const vex4f& first_color = 1, const vex4f& second_color = { 0,0,0,1 }) {
        std::vector<vex4<unsigned char>> _data(x * y);
        u32 j = 0u;
        const vex4<unsigned char>& fc = first_color * 255;
        const vex4<unsigned char>& sc = second_color * 255;
        vex4f color = fc;
        const auto& t = vex4f(fc) - vex4f(sc);
        const vex4f& mc = std::abs(t / y);
        const auto& m = t < 0;
        for (auto& i : _data) {
            i = vex4<unsigned char>(color);
            j++;
            if (j == x) {
                color(m,color + mc);
                color(!m, color - mc);
                j = 0u;
            };
        };
        loadFromMemory((void*)_data.data(), x, y, true);
        return *this;
    };
    auto& createGradientX(const u32& x = 250u, const u32& y = 250u, const vex4f& first_color = 1, const vex4f& second_color = { 0,0,0,1 }) {
        std::vector<vex4<unsigned char>> _data(x * y);
        u32 j = 0u;
        const vex4<unsigned char>& fc = first_color * 255;
        const vex4<unsigned char>& sc = second_color * 255;
        vex4f color = fc;
        const auto& t = vex4f(fc) - vex4f(sc);
        const vex4f& mc = std::abs(t / x);
        const auto& m = t < 0;
        for (auto& i : _data) {
            i = vex4<unsigned char>(color);
            j++;
            color(m, color + mc);
            color(!m, color - mc);
            if (j == x) {
                color = fc;
                j = 0u;
            };
        };
        loadFromMemory((void*)_data.data(), x, y, true);
        return *this;
    };
    void bind() const {
        glBindTexture(GL_TEXTURE_2D, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    }
};