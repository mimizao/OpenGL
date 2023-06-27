#ifndef INC_03_SHADERS_SHADER_H
#define INC_03_SHADERS_SHADER_H

#include <glad/glad.h>
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

private:
    static void checkCompileErrors(unsigned int shader, const std::string &type);
};

#endif //INC_03_SHADERS_SHADER_H
