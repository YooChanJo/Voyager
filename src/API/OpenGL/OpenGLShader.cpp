// OpenGL
#include <Glad/glad.h>
#include <GLFW/glfw3.h>

// STD Headers
#include "pch.h"

#include "OpenGLShader.h"
#include "Core/Log.h"

namespace Voyager {

    ShaderProgramSource OpenGLShader::ParseShader(const std::string& filePath) {
        if(!std::filesystem::exists(filePath)) {
            VG_CORE_ERROR("OpenGLShader file does not exist: {0}", filePath);
            return { "", "" };
        }
        
        std::ifstream stream(filePath);

        enum class ShaderType {
            NONE = -1,
            VERTEX = 0,
            FRAGMENT = 1,
        };

        std::string line;
        std::stringstream ss[2];
        ShaderType type = ShaderType::NONE;
        while(getline(stream, line)) {
            if(line.find("#shader") != std::string::npos) { // found syntax
                if(line.find("vertex") != std::string::npos) {
                    type = ShaderType::VERTEX;
                    
                } else if(line.find("fragment") != std::string::npos) {
                    type = ShaderType::FRAGMENT;
                    
                }
            } else {
                ss[(int)type] << line << "\n";
            }
        }
        stream.close();
        
        return { ss[0].str(), ss[1].str() };
    }

    unsigned int OpenGLShader::CompileShader(unsigned int type, const std::string& source) {
        unsigned int id = glCreateShader(type);
        const char* src = source.c_str(); // this source should exist
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        // error handling
        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if(result == GL_FALSE) {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* message = (char *)alloca(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);
            VG_CORE_ERROR("Failed to compile {0} shader: {1}", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"), message);
            glDeleteShader(id);
            return 0; 
        }
        glGetShaderiv(id, GL_LINK_STATUS, &result);
        if(result == GL_FALSE) {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* message = (char *)alloca(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);
            VG_CORE_ERROR("Failed to link {0} shader: {1}", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"), message);
            glDeleteShader(id);
            return 0; 
        }
        glGetShaderiv(id, GL_VALIDATE_STATUS, &result);
        if(result == GL_FALSE) {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* message = (char *)alloca(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);
            VG_CORE_ERROR("Failed to validate {0} shader: {1}", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"), message);
            glDeleteShader(id);
            return 0; 
        }

        return id;
    }

    unsigned int OpenGLShader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
        unsigned int program = glCreateProgram();
        unsigned int vs  = CompileShader(GL_VERTEX_SHADER, vertexShader);
        unsigned int fs  = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
        
        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vs); // should technically calling detach shader
        glDeleteShader(fs);
        
        return program;
    }


    OpenGLShader::OpenGLShader(): m_RendererID(0) {}
    OpenGLShader::OpenGLShader(const std::string& filepath)
        : m_FilePath(filepath), m_RendererID(0)
    {
        m_Source = ParseShader(filepath);
    }    
    OpenGLShader::OpenGLShader(const ShaderProgramSource& source)
        : m_Source(source), m_RendererID(0) {}

    OpenGLShader::~OpenGLShader() {
        if(m_RendererID != 0) glDeleteProgram(m_RendererID);
    }

    void OpenGLShader::Generate() {
        if(m_RendererID != 0) return;
        m_RendererID = CreateShader(m_Source.vertexSource, m_Source.fragmentSource);
    }

    void OpenGLShader::Bind() const {
        glUseProgram(m_RendererID);
    }    
    void OpenGLShader::Unbind() const {
        glUseProgram(0);
    }    

    // set uniforms
    void OpenGLShader::SetUniform1i(const std::string& name, int value) {
        glUniform1i(GetUniformLocation(name), value);
    }
    
    void OpenGLShader::SetUniform1f(const std::string& name, float value) {
        glUniform1f(GetUniformLocation(name), value);
    }
    
    void OpenGLShader::SetUniform2f(const std::string& name, float v0, float v1) {
        glUniform2f(GetUniformLocation(name), v0, v1);
    }
    
    void OpenGLShader::SetUniform3f(const std::string& name, float v0, float v1, float v2) {
        glUniform3f(GetUniformLocation(name), v0, v1, v2);
    }
    
    void OpenGLShader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
        glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
    }
    
    void OpenGLShader::SetUniform1iv(const std::string& name, int count, const int* values) {
        glUniform1iv(GetUniformLocation(name), count, values);
    }
    
    void OpenGLShader::SetUniform1fv(const std::string& name, int count, const float* values) {
        glUniform1fv(GetUniformLocation(name), count, values);
    }
    
    void OpenGLShader::SetUniform2fv(const std::string& name, int count, const float* values) {
        glUniform2fv(GetUniformLocation(name), count, values);
    }
    
    void OpenGLShader::SetUniform3fv(const std::string& name, int count, const float* values) {
        glUniform3fv(GetUniformLocation(name), count, values);
    }
    
    void OpenGLShader::SetUniform4fv(const std::string& name, int count, const float* values) {
        glUniform4fv(GetUniformLocation(name), count, values);
    }
    
    void OpenGLShader::SetUniformMat2f(const std::string& name, const glm::mat2& matrix) {
        glUniformMatrix2fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
    }
    
    void OpenGLShader::SetUniformMat3f(const std::string& name, const glm::mat3& matrix) {
        glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
    }
    
    void OpenGLShader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix) {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
    }
    

    int OpenGLShader::GetUniformLocation(const std::string& name) {
        if(m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) return m_UniformLocationCache[name];
        int location =  glGetUniformLocation(m_RendererID, name.c_str());
        
        if(location == -1) VG_CORE_WARN("Uniform {0} does not exist", name);
        
        m_UniformLocationCache[name] = location;
        return location;
    }    
}
