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

struct DirectionalLight {
	vec3 color;
	vec3 direction;
};

struct PointLight {    
    vec3 color;
    vec3 position;
    
    float k0;
    float k1;
    float k2;  

}; 

struct SpotLight {
	vec3 color;
	vec3 position;
	vec3 direction;

	float cutOff;
	float outerCutOff;

	float k0;
	float k1;
	float k2;

};


uniform Material material;

#define NO_POINT_LIGHTS 10
#define NO_SPOT_LIGHTS 10
#define NO_DIRECTIONAL_LIGHTS 10

uniform int u_NoPointLights;
uniform int u_NoSpotLights;
uniform int u_NoDirectionalLights;

uniform PointLight pointLights[NO_POINT_LIGHTS];
uniform SpotLight spotLights[NO_SPOT_LIGHTS];
uniform DirectionalLight directionalLights[NO_DIRECTIONAL_LIGHTS];



in vec3 v_Position;
void main()
{
	color = vec4(material.ambient * directionalLights[0].color, 1.0);
}