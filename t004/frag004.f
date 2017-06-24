#version 330 core
out vec4 color;

in vec3 vert_color;
in vec2 texCoor;

uniform sampler2D SAMP;

void main()
{
	color = texture(SAMP, texCoor);
}