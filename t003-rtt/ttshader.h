
#ifndef SHADER_H
#define SHADER_H


#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include "../common/include/gl/glew.h"
using namespace std;

class Shader
{
public:
	GLuint Program;
	Shader(const GLchar *vertexPath, const GLchar *fragmentPath, const GLchar *geometryPath=NULL)
	{
		string vertexCode;
		string fragmentCode;
		string geometryCode;
		try
		{
			// 打开文件
			ifstream vertexFile(vertexPath);
			ifstream fragmentFile(fragmentPath);
			ifstream geometryFile;
			if (geometryPath)
				geometryFile.open(geometryPath);

			stringstream vertexStream, fragmentStream, geometryStream;

			// 读取文件缓冲到流
			vertexStream << vertexFile.rdbuf();
			fragmentStream << fragmentFile.rdbuf();
			if (geometryPath)
				geometryStream << geometryFile.rdbuf();

			// 关闭文件句柄
			vertexFile.close();
			fragmentFile.close();
			if (geometryPath)
				geometryFile.close();

			// 把流转化为字符串流
			vertexCode = vertexStream.str();
			fragmentCode = fragmentStream.str();
			if(geometryPath)
				geometryCode = geometryStream.str();

		}
		catch (exception e)
		{
			cout << "ERROR::THE_FILE_OF_VERTER_OR_FRAGMENT_SHADER_OPEN_FAILD\n";
		}

		GLint success;
		GLchar infoLog[512];

		// 将字符串流转化c风格的字符串
		const GLchar* vertexSource = vertexCode.c_str();
		const GLchar* fragmentSource = fragmentCode.c_str();

		// 顶点着色器
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSource, NULL);
		glCompileShader(vertexShader);
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			cout << "ERROR::VERTEX_SHADER_COMPILED_FAILED\n" << infoLog << endl;
		}
		// 像素着色器
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			cout << "ERROR::FRAGMENT_SHADER_COMPILED_FAILED\n" << infoLog << endl;
		}

		// 着色器对象
		this->Program = glCreateProgram();

		if (geometryPath)
		{
			const GLchar* geometrySource = geometryCode.c_str();
			GLuint geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometryShader, 1, &geometrySource, NULL);
			glCompileShader(geometryShader);
			glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(geometryShader, 512, NULL, infoLog);
				cout << "ERROR::GEOMETRY_SAHDER_COMPILTED_FAILED\n" << infoLog << endl;
			}
			glAttachShader(this->Program, geometryShader);
		}

	
		glAttachShader(this->Program, fragmentShader);
		glAttachShader(this->Program, vertexShader);
		
		glLinkProgram(this->Program);
		glGetProgramiv(this->Program, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
			cout << "ERROR::LINK_PROGRAM_FAILED\n" << infoLog << endl;
		}

		// 删除着色器
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	void Use()
	{
		glUseProgram(this->Program);
	}
};
#endif

