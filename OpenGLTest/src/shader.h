#pragma once
#ifndef SHADER_H
#define SHADER_H

#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>


class Shader {
public:
	unsigned int ID;
	void readFile(std::string& srcCode, const char* filePath) {
		std::ifstream File;
		File.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			File.open(filePath);

			std::stringstream shaderStream;
			// 读取文件缓冲内容到数据流中
			shaderStream << File.rdbuf();
			// 关闭文件处理器
			File.close();
			srcCode = shaderStream.str();
		}
		catch (std::ifstream::failure e) {
			std::cout << "ERROR:Shader was not successfully read" << std::endl;
		}
	}
	static unsigned int ComileShader(unsigned int type, const std::string& source) {
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);

		glCompileShader(id);
		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) { // 检错
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);
			std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!!!" << std::endl;
			std::cout << message << std::endl;
			glDeleteShader(id);
			return 0;
		}

		return id;
	}
	Shader(const char* vertexPath, const char* fragmentPath) {

		// 文件读写
		std::string vertexCode;
		std::string fragmentCode;
		readFile(vertexCode, vertexPath);
		readFile(fragmentCode, fragmentPath);


		
		// 编译着色器
		unsigned int program = glCreateProgram();

		unsigned int vs = ComileShader(GL_VERTEX_SHADER, vertexCode);
		unsigned int fs = ComileShader(GL_FRAGMENT_SHADER, fragmentCode);

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);

		int result;
		glGetProgramiv(program, GL_LINK_STATUS, &result);
		if (result == GL_FALSE) { // 检错
			int length;
			glGetShaderiv(program, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char));
			glGetProgramInfoLog(program, length, &length, message);
			std::cout << "Failed to Link " << std::endl;
			std::cout << message << std::endl;
		}
		glDeleteShader(vs);
		glDeleteShader(fs);
		ID = program;
	}
	void use() {
		glValidateProgram(ID);
		glUseProgram(ID);
	}
	void Delete() {
		glDeleteProgram(ID);
	}
	void setBool(const std::string& name, bool value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void setInt(const std::string& name, int value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);

	}
	void setFloat(const std::string& name, float value) const {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
};


#endif // !SHADER_H

