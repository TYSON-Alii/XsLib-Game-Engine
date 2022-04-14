class XsShader {
public:
    uint ID = 0;
    XsShader(const str& _vertex, const str& _fragment) {
        const char* vShaderCode = _vertex.c_str();
        const char* fShaderCode = _fragment.c_str();
        uint vertex, fragment;
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    };
    inline void use() const { glUseProgram(ID); };
    static inline void dis() { glUseProgram(0); };
    inline void operator()(const str& name, bool value)                         const { glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);}
    inline void operator()(const str& name, int value)                          const { glUniform1i(glGetUniformLocation(ID, name.c_str()), value);}
    inline void operator()(const str& name, float value)                        const { glUniform1f(glGetUniformLocation(ID, name.c_str()), value);}
    inline void operator()(const str& name, const vex2f& value)                 const { glUniform2f(glGetUniformLocation(ID, name.c_str()), value.x, value.y);}
    inline void operator()(const str& name, float x, float y)                   const { glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);}
    inline void operator()(const str& name, const vex3f& value)                 const { glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);}
    inline void operator()(const str& name, float x, float y, float z)          const { glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);}
    inline void operator()(const str& name, const vex4f& value)                 const { glUniform4f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z, value.w);}
    inline void operator()(const str& name, float x, float y, float z, float w) const { glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);}
    inline void operator()(const str& name, const glm::mat2& mat)               const { glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);}
    inline void operator()(const str& name, const glm::mat3& mat)               const { glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);}
    inline void operator()(const str& name, const glm::mat4& mat)               const { glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);}
private:
    void checkCompileErrors(GLuint shader, str type) {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            };
        }
        else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            };
        };
    };
};