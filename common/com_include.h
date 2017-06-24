// common.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include <stdlib.h>  
#include<stdio.h>  
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>

#include "../common/Shader.h"
#include "../common/include/SOIL/SOIL.h"

#if 1
#define use_glfw3

#include "../common/include/gl/glew.h"
#ifndef use_glfw3
#include "../common/include/gl/glfw.h"
#else
#include "../common/include/glfw/glfw3.h"
#endif
#include "../common/include/glut/glut.h"
#endif

#include "../common/include/glm/glm.hpp"
#include "../common/include/glm/gtc/matrix_transform.hpp"
#include "../common/include/glm/gtc/type_ptr.hpp"
#include "../common/Utility.h"

#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "common.lib")

#ifndef use_glfw3
#pragma comment(lib, "GLFW.lib")
#else
#pragma comment(lib, "glfw3.lib")
#endif

#pragma comment(lib, "SOIL_s.lib")
