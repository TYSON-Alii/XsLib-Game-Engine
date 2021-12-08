class XsShader {
public:
    unsigned int ID;
    XsShader() = default;
    XsShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr) {
        std::string vertexCode;
        std::string fragmentCode;
        std::string geometryCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        std::ifstream gShaderFile;
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            vShaderFile.close();
            fShaderFile.close();
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
            if (geometryPath != nullptr)
            {
                gShaderFile.open(geometryPath);
                std::stringstream gShaderStream;
                gShaderStream << gShaderFile.rdbuf();
                gShaderFile.close();
                geometryCode = gShaderStream.str();
            }
        }
        catch (std::ifstream::failure& e) {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        };
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
        unsigned int vertex, fragment;
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        unsigned int geometry;
        if (geometryPath != nullptr) {
            const char* gShaderCode = geometryCode.c_str();
            geometry = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometry, 1, &gShaderCode, NULL);
            glCompileShader(geometry);
            checkCompileErrors(geometry, "GEOMETRY");
        }
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        if (geometryPath != nullptr)
            glAttachShader(ID, geometry);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        if (geometryPath != nullptr)
            glDeleteShader(geometry);
    };
    XsShader(std::string _vertex, std::string _fragment) {
        const char* vShaderCode = _vertex.c_str();
        const char* fShaderCode = _fragment.c_str();
        unsigned int vertex, fragment;
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
    XsShader(strinx _vertex, strinx _fragment) {
        const char* vShaderCode = _vertex.c_str();
        const char* fShaderCode = _fragment.c_str();
        unsigned int vertex, fragment;
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
    void Create(std::string _vertex, std::string _fragment) {
        const char* vShaderCode = _vertex.c_str();
        const char* fShaderCode = _fragment.c_str();
        unsigned int vertex, fragment;
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
    inline void use() { glUseProgram(ID); };
    inline void disuse() { glUseProgram(0); };
    inline void operator()(strinx name, bool value)                                     const { glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); }
    inline void operator()(strinx name, int value)                                      const { glUniform1i(glGetUniformLocation(ID, name.c_str()), value); }
    inline void operator()(strinx name, float value)                                    const { glUniform1f(glGetUniformLocation(ID, name.c_str()), value); }
    inline void operator()(strinx name, const glm::vec2& value)                         const { glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); }
    inline void operator()(strinx name, const vex2f& value)                             const { glUniform2f(glGetUniformLocation(ID, name.c_str()), value.x, value.y); }
    inline void operator()(strinx name, float x, float y)                               const { glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y); }
    inline void operator()(strinx name, const glm::vec3& value)                         const { glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); }
    inline void operator()(strinx name, const vex3f& value)                             const { glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z); }
    inline void operator()(strinx name, float x, float y, float z)                      const { glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); }
    inline void operator()(strinx name, const glm::vec4& value)                         const { glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); }
    inline void operator()(strinx name, const vex4f& value)                             const { glUniform4f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z, value.w); }
    inline void operator()(strinx name, float x, float y, float z, float w)             const { glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w); }
    inline void operator()(strinx name, const glm::mat2& mat)                           const { glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]); }
    inline void operator()(strinx name, const glm::mat3& mat)                           const { glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]); }
    inline void operator()(strinx name, const glm::mat4& mat)                           const { glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]); }
    inline void operator()(const char* name, bool value)                                const { glUniform1i(glGetUniformLocation(ID, name), (int)value);}
    inline void operator()(const char* name, int value)                                 const { glUniform1i(glGetUniformLocation(ID, name), value);}
    inline void operator()(const char* name, float value)                               const { glUniform1f(glGetUniformLocation(ID, name), value);}
    inline void operator()(const char* name, const glm::vec2& value)                    const { glUniform2fv(glGetUniformLocation(ID, name), 1, &value[0]);}
    inline void operator()(const char* name, const vex2f& value)                        const { glUniform2f(glGetUniformLocation(ID, name), value.x, value.y);}
    inline void operator()(const char* name, float x, float y)                          const { glUniform2f(glGetUniformLocation(ID, name), x, y);}
    inline void operator()(const char* name, const glm::vec3& value)                    const { glUniform3fv(glGetUniformLocation(ID, name), 1, &value[0]);}
    inline void operator()(const char* name, const vex3f& value)                        const { glUniform3f(glGetUniformLocation(ID, name), value.x, value.y, value.z);}
    inline void operator()(const char* name, float x, float y, float z)                 const { glUniform3f(glGetUniformLocation(ID, name), x, y, z);}
    inline void operator()(const char* name, const glm::vec4& value)                    const { glUniform4fv(glGetUniformLocation(ID, name), 1, &value[0]);}
    inline void operator()(const char* name, const vex4f& value)                        const { glUniform4f(glGetUniformLocation(ID, name), value.x, value.y, value.z, value.w);}
    inline void operator()(const char* name, float x, float y, float z, float w)        const { glUniform4f(glGetUniformLocation(ID, name), x, y, z, w);}
    inline void operator()(const char* name, const glm::mat2& mat)                      const { glUniformMatrix2fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &mat[0][0]);}
    inline void operator()(const char* name, const glm::mat3& mat)                      const { glUniformMatrix3fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &mat[0][0]);}
    inline void operator()(const char* name, const glm::mat4& mat)                      const { glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &mat[0][0]);}
    inline void operator()(const std::string& name, bool value)                         const { glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);}
    inline void operator()(const std::string& name, int value)                          const { glUniform1i(glGetUniformLocation(ID, name.c_str()), value);}
    inline void operator()(const std::string& name, float value)                        const { glUniform1f(glGetUniformLocation(ID, name.c_str()), value);}
    inline void operator()(const std::string& name, const glm::vec2& value)             const { glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);}
    inline void operator()(const std::string& name, const vex2f& value)                 const { glUniform2f(glGetUniformLocation(ID, name.c_str()), value.x, value.y);}
    inline void operator()(const std::string& name, float x, float y)                   const { glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);}
    inline void operator()(const std::string& name, const glm::vec3& value)             const { glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);}
    inline void operator()(const std::string& name, const vex3f& value)                 const { glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);}
    inline void operator()(const std::string& name, float x, float y, float z)          const { glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);}
    inline void operator()(const std::string& name, const glm::vec4& value)             const { glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);}
    inline void operator()(const std::string& name, const vex4f& value)                 const { glUniform4f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z, value.w);}
    inline void operator()(const std::string& name, float x, float y, float z, float w) const { glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);}
    inline void operator()(const std::string& name, const glm::mat2& mat)               const { glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);}
    inline void operator()(const std::string& name, const glm::mat3& mat)               const { glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);}
    inline void operator()(const std::string& name, const glm::mat4& mat)               const { glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);}
private:
    void checkCompileErrors(GLuint shader, std::string type) {
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