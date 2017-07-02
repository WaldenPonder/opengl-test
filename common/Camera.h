#pragma once
#include "common.inner.h"

void  COMMON_API OnKeyDown(GLFWwindow* window, int key, int scancode, int action, int mode);

class COMMON_API Camera
{
public:
	static Camera* Instance();

private:
	Camera();
	~Camera();

public:
	TMat4  GetViewMatrix();
	TMat4  GetProjectionMatrix();

	void   ConfigViewMatrix(TVec3 pos, TVec3 rotation, TVec3 up);
	void   ConfigProjectionMatrix(float fovy, float aspect, float near, float far);

	void   DirtyRotation() { _dirtyRotation = true; }

public:

	/*
	glm::lookAt�Ĳ���
	*/
	TVec3  _pos;
	TVec3  _rotation;
	TVec3  _up;
	TVec3  _lookAt;

	bool   _dirtyRotation;

	/*
	glm::perspective�Ĳ���
	*/
	float  _nearClip;
	float  _farClip;
	float  _fovy;
	float  _aspect;
};
