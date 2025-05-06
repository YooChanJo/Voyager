#pragma once

#include "pch.h"

namespace Voyager {

        
    struct ShaderProgramSource {
        std::string vertexSource;
        std::string fragmentSource;
    };

    class OpenGLShader {
    private:
        unsigned int m_RendererID;
        std::string m_FilePath;
        ShaderProgramSource m_Source;
        std::unordered_map<std::string, int> m_UniformLocationCache;
        public:
        OpenGLShader();
        OpenGLShader(const std::string& filepath);
        OpenGLShader(const ShaderProgramSource& source); // not a reference
        ~OpenGLShader();

        void Generate();
        
        inline std::string GetFilePath() const { return m_FilePath; }
        inline ShaderProgramSource GetSource() const { return m_Source; }

        // called by the renderer --> needs context current
        void Bind() const;
        void Unbind() const;

        // set uniforms + needs extensions
        void SetUniform1i(const std::string& name, int value);
        void SetUniform1f(const std::string& name, float value);
        void SetUniform2f(const std::string& name, float v0, float v1);
        void SetUniform3f(const std::string& name, float v0, float v1, float v2);
        void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    
        void SetUniform1iv(const std::string& name, int count, const int* values);
        void SetUniform1fv(const std::string& name, int count, const float* values);
        void SetUniform2fv(const std::string& name, int count, const float* values);
        void SetUniform3fv(const std::string& name, int count, const float* values);
        void SetUniform4fv(const std::string& name, int count, const float* values);
    
        void SetUniformMat2f(const std::string& name, const glm::mat2& matrix);
        void SetUniformMat3f(const std::string& name, const glm::mat3& matrix);
        void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
    private:
        static ShaderProgramSource ParseShader(const std::string& filePath);
        static unsigned int CompileShader(unsigned int type, const std::string& source);
        static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
        int GetUniformLocation(const std::string& name);
    };
}