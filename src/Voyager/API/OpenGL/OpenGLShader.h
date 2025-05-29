#pragma once
#include "Renderer/Shader.h"

typedef unsigned int GLenum;

namespace Voyager {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;
		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) override;

		virtual const std::string& GetName() const override { return m_Name; }

	private:
		static GLenum ShaderTypeFromString(const std::string& type);
		static unsigned int CompileShader(unsigned int type, const std::string& source);
		/* Read entire file string */
		static std::string ReadFile(const std::string& filepath);
		/* Part the file string to shader sources */
		static std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);

		/* Created program and assigns m_RendererID */
		void CreateProgram();
	private:
		unsigned int m_RendererID;
		std::string m_FilePath;
		std::string m_Name;

		std::unordered_map<GLenum, std::string> m_ShaderSourceCode;
	};

}
