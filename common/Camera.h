#pragma once
#include "common.inner.h"

#define CameraPos   (Camera::Instance()->_eye)

void  COMMON_API OnKeyDown(GLFWwindow* window, int key, int scancode, int action, int mode);

//TODO: �任����������
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

	void   ConfigViewMatrix(TVec3 pos, TQuat rotation, TVec3 up);
	void   ConfigProjectionMatrix(float fovy, float aspect, float near, float far);

	void   DirtyRotation() { _dirtyRotation = true; }
	
	//	����	axis ��ת���
	void   MakeRotation(TVec3 axis, float angle);

	//v��ת_rotation���ֵ
	TVec3  RotationFrom(const TVec3& v);
public:

	TVec3* _pMoveVale;
	float  _moveFactor;

	/*
	glm::lookAt�Ĳ���
	*/
	TVec3  _eye;
	TVec3  _up;
	TVec3  _center;

	TQuat  _rotation;

	bool   _dirtyRotation;

	/*
	glm::perspective�Ĳ���
	*/
	float  _nearClip;
	float  _farClip;
	float  _fovy;
	float  _aspect;

public:
	bool _bNeedRotation;
};
