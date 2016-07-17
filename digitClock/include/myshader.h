#pragma once

#ifndef MYSHADER_H
#define MYSHADER_H
#include<cstdio>
#include<fstream>
#include<sstream>
#include<iostream>
#include<GL/glew.h>
using namespace std;

typedef GLint Int;
typedef GLuint Uint;
typedef GLchar Char;

class Shader
{
public:
	Uint Program;
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
	{
		string vertexCode;
		string fragmentCode;
		try
		{
			ifstream vertexFile(vertexPath);
			ifstream fragmentFile(fragmentPath);

			stringstream vertexStream, fragmentStream;
			
			vertexStream << vertexFile.rdbuf();
			fragmentStream << fragmentFile.rdbuf();

			vertexCode = vertexStream.str();
			fragmentCode = fragmentStream.str();

			vertexFile.close();
			fragmentFile.close();
		}
		catch (exception e)
		{
			cout << "ERROR::THE_FILE_OF_SHADER_OPEN_FAILED\n";
		}

		Int success;
		Char infoLog[512];

		const Char* vertexSource = vertexCode.c_str();
		const Char* fragmentSource = fragmentCode.c_str();

		// 创建顶点着色器
		Uint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSource, NULL);
		glCompileShader(vertexShader);
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			cout << "ERROR::VERTEX_SHADER_COMPILED_FAILED\n" << infoLog << endl;
		}

		// 像素着色器
		Uint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
		glCompileShader(fragmentShader);
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			cout << "ERROR::FRAGMENT_SHADER_COMPILED_FAILED\n" << infoLog << endl;
		}

		this->Program = glCreateProgram();
		glAttachShader(this->Program, vertexShader);
		glAttachShader(this->Program, fragmentShader);
		glLinkProgram(this->Program);
		glGetProgramiv(this->Program, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
			cout << "ERROR::PROGRAM_COMPILED_FAILED\n" << infoLog << endl;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void Use()
	{
		glUseProgram(this->Program);
	}
};
#endif
