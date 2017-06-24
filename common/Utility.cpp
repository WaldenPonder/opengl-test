#include "stdafx.h"
#include "Utility.h"
#include "include/SOIL/SOIL.h"

#pragma comment(lib, "SOIL_s.lib")

namespace tools
{
	
	GLuint CreateTexture(char* path, GLuint param1, GLuint param2)
	{
		GLuint  texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, param1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, param1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param2);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param2);

		try
		{
			int width, height;
			unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(GL_TEXTURE_2D);
			SOIL_free_image_data(image);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		catch (...)
		{
			std::cout << "鍥剧墖璇诲彇澶辫触  Utility.cpp  CreateTexture " << std::endl;
		}


		return texture;
	}

	void GetCubePts(GLfloat* arr)
	{
		GLfloat pts[] =
		{
			// 涓?
			-0.5, 0.5, -0.5, 0, 1,
			-0.5, 0.5, 0.5, 0, 0,
			0.5, 0.5, -0.5, 1, 1,
			-0.5, 0.5, 0.5, 0, 0,
			0.5, 0.5, 0.5, 1, 0,
			0.5, 0.5, -0.5, 1, 1,

			//涓?
			-0.5, -0.5, -0.5, 0, 1,
			0.5, -0.5, -0.5, 1, 1,
			0.5, -0.5, 0.5, 1, 0,
			-0.5, -0.5, -0.5, 0, 1,
			0.5, -0.5, 0.5, 1, 0,
			-0.5, -0.5, 0.5, 0, 0,

			//宸?
			0.5, 0.5, 0.5, 0, 1,
			0.5, -0.5, 0.5, 0, 0,
			0.5, -0.5, -0.5, 1, 0,
			0.5, 0.5, 0.5, 0, 1,
			0.5, -0.5, -0.5, 1, 0,
			0.5, 0.5, -0.5, 1, 1,

			//鍙?
			-0.5, 0.5, 0.5, 0, 1,
			-0.5, 0.5, -0.5, 1, 1,
			-0.5, -0.5, -0.5, 1, 0,
			-0.5, 0.5, 0.5, 0, 1,
			-0.5, -0.5, -0.5, 1, 0,
			-0.5, -0.5, 0.5, 0, 0,

			//鍓?
			-0.5, 0.5, 0.5, 0, 1,
			0.5, -0.5, 0.5, 1, 0,
			0.5, 0.5, 0.5, 1, 1,
			-0.5, 0.5, 0.5, 0, 1,
			-0.5, -0.5, 0.5, 0, 0,
			0.5, -0.5, 0.5, 1, 0,

			//鍚?
			-0.5, 0.5, -0.5, 0, 1,
			0.5, 0.5, -0.5, 1, 1,
			0.5, -0.5, -0.5, 1, 0,
			-0.5, 0.5, -0.5, 0, 1,
			0.5, -0.5, -0.5, 1, 0,
			-0.5, -0.5, -0.5, 0, 0
		};

		for (int i = 0; i < 180; i++)
		{
			arr[i] = pts[i];
		}
	}

	GLFWwindow* COMMON_API PrepareGlfwWindow(int w /*= 1200*/, int h /*= 900*/,
		const char* title /*= "learn opengl"*/, GLFWkeyfun cbfun /*= nullptr*/)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		GLFWwindow* window = glfwCreateWindow(w, h, title, nullptr, nullptr);
		glfwMakeContextCurrent(window);
		glewInit();

		int nW, nH;
		glfwGetFramebufferSize(window, &nW, &nH);
		glViewport(0, 0, nW, nH);

		if (cbfun)
		   glfwSetKeyCallback(window, cbfun);

		return window;
	}
}