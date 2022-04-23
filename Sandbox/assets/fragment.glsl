#version 330 core
			
layout(location = 0) out vec4 color;

struct Material {
	vec3 ambient;
	vec3 deffuse;
	vec3 specular;
	float shininess;
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

uniform vec3 u_ViewPos;

in vec3 v_Position;
in vec3 v_Normal;

vec3 CalcDirLight(DirectionalLight light, vec3 norm, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 norm, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 norm, vec3 viewDir);

void main()
{

	vec3 norm = normalize(v_Normal);
	vec3 viewDir = normalize(u_ViewPos - v_Position);

	vec3 result;

	for(int i = 0; i < u_NoDirectionalLights; i++) {
		result += CalcDirLight(directionalLights[i], norm, viewDir);
	}

	for(int i = 0; i < u_NoPointLights; i++) {
		result += CalcPointLight(pointLights[i], norm, viewDir);
	}

	for(int i = 0; i < u_NoSpotLights; i++) {
		result += CalcSpotLight(spotLights[i], norm, viewDir);
	}
	

	color = vec4(result, 1.0);
}


vec3 CalcDirLight(DirectionalLight light, vec3 norm, vec3 viewDir)
{
    vec3 ambient = light.color * material.ambient;

	// diffuse
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.color * (material.deffuse * diff);

	// specular
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess * 128);
	vec3 specular = light.color * (material.specular * spec);

	return vec3(ambient + diffuse + specular);
}


vec3 CalcPointLight(PointLight light, vec3 norm, vec3 viewDir) {
	// ambient
	vec3 ambient = light.color * material.ambient;

	// diffuse
	vec3 lightDir = normalize(light.position - v_Position);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.color * (diff * material.deffuse);

	// specular
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess * 128);
	vec3 specular = light.color * (spec * material.specular);

	// calculate attenuation
	float dist = length(light.position - v_Position);
	float attenuation = 1.0 / (light.k0 + light.k1 * dist + light.k2 * (dist * dist));

	// apply attenuation
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return vec3(ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 norm, vec3 viewDir) {
	vec3 lightDir = normalize(light.position - v_Position);
	float theta = dot(lightDir, normalize(-light.direction));

	// ambient
	vec3 ambient = light.color * material.ambient;

	if (theta > light.outerCutOff) {

		// diffuse
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = light.color * (diff * material.deffuse);

		// specular
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess * 128);
		vec3 specular = light.color * (spec * material.specular);

		// calculate Intensity
		float intensity = clamp((theta - light.outerCutOff) / (light.cutOff - light.outerCutOff), 0.0, 1.0);
		diffuse *= intensity;
		specular *= intensity;

		// calculate attenuation
		float dist = length(light.position - v_Position);
		float attenuation = 1.0 / (light.k0 + light.k1 * dist + light.k2 * (dist * dist));

		// apply attenuation
		ambient *= attenuation;
		diffuse *= attenuation;
		specular *= attenuation;

		return vec3(ambient + diffuse + specular);
	}
	else {
		// render just ambient
		return ambient;
	}
}