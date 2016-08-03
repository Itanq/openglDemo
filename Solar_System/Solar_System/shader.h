
#ifndef SHADER_H
#define SHADER_H


#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<GL/glew.h>
using namespace std;

class Shader
{
public:
	GLuint Program;
	Shader(){}
	Shader(const GLchar *vertexPath, const GLchar *fragmentPath)
	{
		string vertexCode;
		string fragmentCode;
		try
		{
			// ���ļ�
			ifstream vertexFile(vertexPath);
			ifstream fragmentFile(fragmentPath);

			stringstream vertexStream, fragmentStream;

			// ��ȡ�ļ����嵽��
			vertexStream << vertexFile.rdbuf();
			fragmentStream << fragmentFile.rdbuf();

			// �ر��ļ����
			vertexFile.close();
			fragmentFile.close();

			// ����ת��Ϊ�ַ�����
			vertexCode = vertexStream.str();
			fragmentCode = fragmentStream.str();

		}
		catch (exception e)
		{
			cout << "ERROR::THE_FILE_OF_VERTER_OR_FRAGMENT_SHADER_OPEN_FAILD\n";
		}

		GLint success;
		GLchar infoLog[512];

		// ���ַ�����ת��c�����ַ���
		const GLchar* vertexSource = vertexCode.c_str();
		const GLchar* fragmentSource = fragmentCode.c_str();

		// ������ɫ��
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSource, NULL);
		glCompileShader(vertexShader);
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			cout << "ERROR::VERTEX_SHADER_COMPILED_FAILED\n" << infoLog << endl;
		}

		// ������ɫ��
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			cout << "ERROR::FRAGMENT_SHADER_COMPILED_FAILED\n" << infoLog << endl;
		}

		// ��ɫ������
		this->Program = glCreateProgram();
		glAttachShader(this->Program, fragmentShader);
		glAttachShader(this->Program, vertexShader);
		
		glLinkProgram(this->Program);
		glGetProgramiv(this->Program, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
			cout << "ERROR::LINK_PROGRAM_FAILED\n" << infoLog << endl;
		}

		// ɾ����ɫ��
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	void Use()
	{
		glUseProgram(this->Program);
	}
};
#endif
