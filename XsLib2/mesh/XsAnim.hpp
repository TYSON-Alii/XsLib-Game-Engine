class XsAnim : public XsEntity {
private:
    void gif_load(const str& filename) {
        EasyGifReader gifReader = EasyGifReader::openFile(filename.c_str());
        const auto& frameCount = gifReader.frameCount();
        const auto& x = gifReader.width();
        const auto& y = gifReader.height();
        duration = gifReader.begin()->duration().seconds();
        for (EasyGifReader::Frame frame : gifReader) {
            XsTexture t;
            t.loadFromMemory((ptr)frame.pixels(), x, y, true);
            self.frame(t);
        };
    };
    XsChrono clk;
    list<XsTexture> tex_data;
    XsTexture c_frame;
    uint current_index = 0;
public:
    XsAnim() = default;
    XsAnim(const XsAnim&) = default;
    XsAnim(const str& gif_file) { gif_load(gif_file); };
    inline void loadFromGIF(const str& filename) { gif_load(filename); };
    inline void frame(const XsTexture& tex) { tex_data.push_back(tex); };
    inline XsTexture& frame(const uint& at) { return tex_data[at]; };
    inline XsTexture frame(const uint& at) const { return tex_data[at]; };
    auto& frames() { return tex_data; };
    auto frames() const { return tex_data; };
    inline void remove(const uint& at) { tex_data.erase(tex_data.begin()+at); };
    inline void clear() {
        clk.restart();
        current_index = 0;
        c_frame = XsTexture();
        tex_data.clear();
    };
    inline void reset() {
        c_frame = if_else(!tex_data.empty(), tex_data.front(), XsTexture());
        current_index = 0;
        clk.restart();
    };
    bool move_reverse = false;
    f32 duration = 1.f;
    inline XsTexture& current() { return c_frame; };
    inline XsTexture current() const { return c_frame; };
    void step() {
        if (tex_data.size() > 1 and XsLimiter(clk, duration)) {
            if (move_reverse) {
                if (current_index == 0) current_index = tex_data.size();
                current_index--;
                c_frame = tex_data[current_index];
                clk.restart();
            }
            else {
                current_index++;
                if (current_index == tex_data.size()) current_index = 0;
                c_frame = tex_data[current_index];
                clk.restart();
            };
        };
    };
};