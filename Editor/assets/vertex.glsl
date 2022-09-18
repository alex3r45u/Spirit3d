#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec3 a_Tex;

uniform mat4 u_ViewPerspective;
uniform mat4 u_Model;

out vec3 WorldPos;
out vec3 v_Normal;
out vec3 v_Tex;
void main()
{
	WorldPos = vec3(u_Model * vec4(a_Position, 1.0));
	v_Normal = a_Normal;
	v_Tex = a_Tex;
	gl_Position = u_ViewPerspective *  vec4(WorldPos, 1.0);
}