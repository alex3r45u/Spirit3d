#version 330 core
			
layout(location = 0) out vec4 color;

struct Material {
	vec3 ambient;
	vec3 deffuse;
	vec3 specular;
	sampler2D ambientTex;
	sampler2D deffuseTex;
	sampler2D specularTex;
};


uniform Material material;



in vec3 v_Position;
void main()
{
	color = vec4(0.0, 1.0, 1.0, 1.0);
}