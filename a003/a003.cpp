#include "stdafx.h"
#include "../common/common.out.h"

/*

fragment����������

VAO VBO EBO   ����
*/
using namespace std;

float color1 = 0.1;
float color2 = 0.1;
float color3 = 0.1;

int g_size = WINDOW_WIDTH * WINDOW_HEIGHT * 4;

void screenCapture();

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_1)
	{
		color1 = float(rand() % 255) / 255.0;
	}
	else if (key == GLFW_KEY_2)
	{
		color2 = float(rand() % 255) / 255.0;
	}
	else if (key == GLFW_KEY_3)
	{
		color3 = float(rand() % 255) / 255.0;
	}
	else if (key == GLFW_KEY_4)
	{
		screenCapture();
	}
}

GLuint createVao()
{
	GLuint VBO, VAO, EBO;
	float val = 0.95f;
	GLfloat pts[] =
	{
		val, val, 0.0f, 1, 0, 0, 1.0f, 1.0f,  // ���Ͻ�
		val, -val, 0.0f, 0, 1, 0, 1.0f, 0.0f,  // ���½�
		-val, -val, 0.0f, 0, 0, 1, 0.0f, 0.0f,  // ���½�
		-val, val, 0.0f, 1, 1, 0, 0.0f, 1.0f  // ���Ͻ�
	};

	GLuint indices[] =
	{ // ע��������0��ʼ!
		0, 1, 3, // ��һ��������
		1, 2, 3  // �ڶ���������
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pts), pts, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * FLOAT_SIZE, (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * FLOAT_SIZE, (void*)(3 * FLOAT_SIZE));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * FLOAT_SIZE, (void*)(6 * FLOAT_SIZE));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	return VAO;
}

GLuint createFBO(int w, int  h)
{
	GLuint fbo, renderBuffer[2];

	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);

	glGenRenderbuffers(2, renderBuffer);
	{
		glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer[0]);  //color
		glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, w, h);

		glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer[1]); //depth
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, w, h);
	}
	
	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderBuffer[0]);
	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffer[1]);

	glEnable(GL_DEPTH_TEST);

	GLenum status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
	if (status == GL_FRAMEBUFFER_COMPLETE)
	{
		cout << "fbo ��ȷ " << endl;
	}
	else
	{   
		/*
		   #define GL_FRAMEBUFFER_COMPLETE 0x8CD5
		   #define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT 0x8CD6
		   #define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 0x8CD7
		   #define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER 0x8CDB
		   #define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER 0x8CDC
		   #define GL_FRAMEBUFFER_UNSUPPORTED 0x8CDD
		*/
		cout << "fbo ����ȷ " << endl;
	}

	return fbo;
}

void screenCapture()
{
	unsigned char *mpixels = new unsigned char[g_size];
#if 0
	glReadBuffer(GL_FRONT);
	glReadPixels(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, mpixels);
	glReadBuffer(GL_BACK);
#else
	glReadBuffer(GL_ONE);
	glReadPixels(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	unsigned char* PTR = (unsigned char*)glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);
	memcpy(mpixels, PTR, g_size);
	glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
#endif

	for (int i = 0; i < g_size; i += 4)
	{
		mpixels[i] ^= mpixels[i + 2] ^= mpixels[i] ^= mpixels[i + 2];
	}
	FIBITMAP* bitmap = FreeImage_Allocate(WINDOW_WIDTH, WINDOW_HEIGHT, 32, 8, 8, 8);

	for (int y = 0; y < FreeImage_GetHeight(bitmap); y++)
	{
		BYTE *bits = FreeImage_GetScanLine(bitmap, y);
		for (int x = 0; x < FreeImage_GetWidth(bitmap); x++)
		{
			bits[0] = mpixels[(y * WINDOW_WIDTH + x) * 4 + 0];
			bits[1] = mpixels[(y * WINDOW_WIDTH + x) * 4 + 1];
			bits[2] = mpixels[(y * WINDOW_WIDTH + x) * 4 + 2];
			bits[3] = 255;
			bits += 4;

		}
	}
	bool bSuccess = FreeImage_Save(FIF_PNG, bitmap, "ABC.png", PNG_DEFAULT);
	FreeImage_Unload(bitmap);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "learn opengl", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glewInit();

	int w, h;
	glfwGetFramebufferSize(window, &w, &h);
	glViewport(0, 0, w, h);
	glfwSetKeyCallback(window, key_callback);
	srand((unsigned)time(nullptr));

	Shader shader("verta003.glsl", "fraga003.glsl");

	GLuint VAO = createVao();
	GLuint FBO = createFBO(w, h);

	GLuint tex = Utility::CreateTexture("../common/src/tt.jpg");
	GLuint tex2 = Utility::CreateTexture("../common/src/container.jpg");


	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO);

		glClearColor(CLEAR_COLOR);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GLfloat time = glfwGetTime();
		GLfloat color_g = sin(time) / 2.0 + 0.5;
		GLfloat color_b = sin(time) / 2.0 + 0.4;

		shader.setUniformVec4f("myColor", 0.0f, color_g, color_b, 1.0f);
		shader.setUniformTexture2D("sampler", tex, 0);
		shader.setUniformTexture2D("sampler2", tex2, 1);
		shader.Use();

		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		///////////////////////////////
#if 1
		glBindFramebuffer(GL_READ_FRAMEBUFFER, FBO);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

		glClearColor(CLEAR_COLOR);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//	glBlitFramebuffer(0, 0, w, h, 0, 0, w * .5, h * .5, GL_COLOR_BUFFER_BIT, GL_NEAREST);

		glBlitFramebuffer(0, 0, w, h, w, h, 0, 0, GL_COLOR_BUFFER_BIT, GL_NEAREST);
#endif								

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}