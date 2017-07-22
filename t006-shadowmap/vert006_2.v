#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aCoor;
layout (location = 1) in vec3 aNormal;

uniform mat4 uModel;
uniform mat4 uLightSpace;

void main()
{
	gl_Position = uLightSpace * uModel * vec4(aPosition, 1.0);
}