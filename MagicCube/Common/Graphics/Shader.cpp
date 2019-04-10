#include "Shader.h"
#include "../../ThreeParty/GLAD/glad.h"

#include <fstream> 
#include <sstream> 

Shader::Shader(string vertexShaderPath, string fragmentShaderPath)
{
	this->vertexShaderPath = vertexShaderPath;
	this->fragmentShaderPath = fragmentShaderPath;

	unsigned int vertexShader = LoadShader(this->vertexShaderPath, GL_VERTEX_SHADER);
	unsigned int fragmentShader = LoadShader(this->fragmentShaderPath, GL_FRAGMENT_SHADER);

	shaderProgramId = glCreateProgram();

	glAttachShader(shaderProgramId, vertexShader);
	glAttachShader(shaderProgramId, fragmentShader);
	glLinkProgram(shaderProgramId);

	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgramId, 512, NULL, infoLog);
		std::cout << "ERROR::Program::FAILED\n" << infoLog << std::endl;
	}
	else
	{
		std::cout << "shader success!" << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Use()
{
	glUseProgram(shaderProgramId);
}

void Shader::SetBool(string name, bool value)
{
	glUniform1i(glGetUniformLocation(shaderProgramId, name.c_str()), (int)value);
}

void Shader::SetInt(string name, int value)
{
	glUniform1i(glGetUniformLocation(shaderProgramId, name.c_str()), value);
}

void Shader::SetFloat(string name, float value)
{
	glUniform1f(glGetUniformLocation(shaderProgramId, name.c_str()), value);
}

void Shader::SetVector4(string name, float value0, float value1, float value2, float value3)
{
	glUniform4f(glGetUniformLocation(shaderProgramId, name.c_str()), value0, value1, value2, value3);
}

void Shader::SetMatrix4(string name, const mat4& matrix4)
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramId, name.c_str()), 1, GL_FALSE, &matrix4[0][0]);
}

unsigned int Shader::LoadShader(string shaderPath, unsigned int shaderType)
{
	string vertexCode;
	ifstream vShaderFile;
	// 保证ifstream对象可以抛出异常：
	vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	try
	{
		// 打开文件
		vShaderFile.open(shaderPath);
		stringstream vShaderStream;
		// 读取文件的缓冲内容到数据流中
		vShaderStream << vShaderFile.rdbuf();
		// 关闭文件处理器
		vShaderFile.close();
		// 转换数据流到string
		vertexCode = vShaderStream.str();
	}
	catch (ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();

	unsigned int vertex;
	int success;
	char infoLog[512];

	// 顶点着色器
	vertex = glCreateShader(shaderType);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	// 打印编译错误（如果有的话）
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};
	return vertex;
}
