#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	//! 程序ID
	unsigned int ID;

	//! 构造器读取并构建着色器
	Shader(const char *vertexPath, const char *fragmentPath);

	//! 使用/激活程序
	void use() const;

	//! uniform工具函数
	[[maybe_unused]]
	void setBool(const std::string &name, bool value) const;

	[[maybe_unused]]
	void setInt(const std::string &name, int value) const;

	[[maybe_unused]]
	void setFloat(const std::string &name, float value) const;

	[[maybe_unused]]
	void setVec2(const std::string &name, const glm::vec2 &value) const;

	[[maybe_unused]]
	void setVec2(const std::string &name, float x, float y) const;

	[[maybe_unused]]
	void setVec3(const std::string &name, const glm::vec3 &value) const;

	[[maybe_unused]]
	void setVec3(const std::string &name, float x, float y, float z) const;

	[[maybe_unused]]
	void setVec4(const std::string &name, const glm::vec4 &value) const;

	[[maybe_unused]]
	void setVec4(const std::string &name, float x, float y, float z, float w) const;

	[[maybe_unused]]
	void setMat2(const std::string &name, const glm::mat2 &mat) const;

	[[maybe_unused]]
	void setMat3(const std::string &name, const glm::mat3 &mat) const;

	[[maybe_unused]]
	void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
	static void checkCompileErrors(unsigned int shader, const std::string &type, const char *path);
};

#endif //SHADER_H
