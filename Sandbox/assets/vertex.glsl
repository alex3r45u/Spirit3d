#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec3 a_Tex;

uniform mat4 u_ViewPerspective;
uniform mat4 u_Model;

out vec3 v_Position;
void main()
{
	v_Position = a_Position;
	gl_Position = u_ViewPerspective * u_Model * vec4(a_Position, 1.0);
}