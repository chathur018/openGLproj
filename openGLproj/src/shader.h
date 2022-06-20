#pragma once

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

struct shaderProgramSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

class shader
{
private:
	std::string m_filePath;
	unsigned int m_rendererID;
	std::unordered_map<std::string, int> m_uniformLocCache;

	shaderProgramSource parseShader(const std::string& filepath);
	unsigned int compileShader(unsigned int type, const std::string& source);
	unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);

	unsigned int getUniformLocation(const std::string& name);

public:
	shader(const std::string& filepath);
	~shader();

	void bind() const;
	void unbind() const;

	//setting uniforms
	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void setUniform1f(const std::string& name, float i0);
	void setUniform1i(const std::string& name, int i0);
	void setUniformMat4f(const std::string& name, const glm::mat4& matrix);
};