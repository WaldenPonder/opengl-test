
/*
Phong����
*/

#include "stdafx.h"
#include "../common/common.out.h"

GLfloat cubePts[288];

void setUpScene(OUT vector<glm::mat4>& modelMats)
{
	TMat4 identy(1.0);

	TVec3 v(50, 1, 50);
	auto TMP = glm::scale(identy, v);
	TMP = glm::rotate(TMP, 60.0f, X_AXIS);
	modelMats.push_back(TMP);

	TMP = glm::translate(identy, TVec3(20, 20, 0));
	modelMats.push_back(TMP);

	TMP = glm::translate(identy, TVec3(5, 3, 1));
	modelMats.push_back(TMP);

	TMP = glm::translate(identy, TVec3(6, 4, 8));
	modelMats.push_back(TMP);

	TMP = glm::translate(identy, TVec3(9, 4, 4));
	TMP = glm::scale(TMP, TVec3(10, 10, 10));
	modelMats.push_back(TMP);
}

void createVAO(OUT GLuint& VAO, OUT GLuint& VBO)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubePts), cubePts, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * FLOAT_SIZE, (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * FLOAT_SIZE, (void*)(3 * FLOAT_SIZE));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * FLOAT_SIZE, (void*)(5 * FLOAT_SIZE));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int _tmain(int argc, _TCHAR* argv[])
{

	Utility::GetCubePts_withTextureNormal(cubePts);

	GLFWwindow* window;
	PREPARE_GLFW_WINDOW(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, OnKeyDown);
	g_Mat4 = glm::mat4(1.0);

	GLuint VAO, VBO;
	createVAO(VAO, VBO);

	GLuint texture = Utility::CreateTexture("../common/src/floor.jpg");
	Shader shader("vert005.glsl", "frag005.glsl");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	vector<glm::mat4> modelMats;
	setUpScene(modelMats);

	TVec3 lightPos(50, 30, 0);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(CLEAR_COLOR);

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);

		TMat4 view = Camera::Instance()->GetViewMatrix();
		TMat4 projection = Camera::Instance()->GetProjectionMatrix();
		//Camera::Instance()->_pMoveVale = &lightPos;
		//Camera::Instance()->_moveFactor = 50;
		if (Camera::Instance()->_bNeedRotation)
		    lightPos = TMat3(glm::rotate(glm::mat4(1.0), 0.5f, Y_AXIS)) * lightPos;

		for (auto Mat : modelMats)
		{
			glEnable(GL_DEPTH_TEST);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			shader.Use();
			shader.setUniformMat4f("uModel", Mat);
			shader.setUniformMat4f("uView", view);
			shader.setUniformMat4f("uProjection", projection);
		
			shader.setUniformTexture2D("uSAMP", texture, 0);
			shader.setUniformVec3f("uLightColor", 1, 1, 1);
			shader.setUniformVec3f("uLightPos", lightPos);
			shader.setUniformVec3f("uViewPos", CameraPos);

			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);
		}

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}