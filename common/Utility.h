#pragma once
#include "common.inner.h"
#include "include/FreeImage/FreeImage.h"

COMMON_API extern glm::mat4 g_Mat4;

namespace tools
{
	COMMON_API GLuint  CreateTexture(char* path, GLuint wrapModel = GL_REPEAT, GLuint filterModel = GL_LINEAR);

	COMMON_API void CreateFBO(GLuint& frambuffer, GLuint& texColorBuffer,
		GLuint filterModel = GL_LINEAR, GLuint wrapModel = GL_CLAMP_TO_EDGE, 
		GLuint width = WINDOW_WIDTH, GLuint height = WINDOW_HEIGHT);

	//���180�������͵�����, ���������
	COMMON_API void  GetCubePts_withTexture(GLfloat* arr);
	
	//���288�������͵�����, ����/����/����
	COMMON_API void  GetCubePts_withTextureNormal(GLfloat* arr);

	COMMON_API void  default_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
}