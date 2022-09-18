#version 330 core
			
layout(location = 0) out vec4 FragColor;

struct Material {
	vec3 Albedo;
	float Metallic;
    float Roughness;
    float AO;
	//TODO maps
};

struct BaseLight {
	vec3 Color;
	float Intensity;
};


struct DirectionalLight {
    BaseLight Light;
    vec3 Direction;
};

struct PointLight {
    BaseLight Light;
    vec3 Position;
    float Radius;
};

struct SpotLight {
    BaseLight Light;
    vec3 Position;
    vec3 Direction;
    float Angle;
    float Range;
};


uniform Material u_Material;

#define NO_POINT_LIGHTS 100
#define NO_SPOT_LIGHTS 100
#define NO_DIRECTIONAL_LIGHTS 10

uniform int u_NoPointLights;
uniform int u_NoSpotLights;
uniform int u_NoDirectionalLights;

uniform PointLight u_PointLights[NO_POINT_LIGHTS];
uniform SpotLight u_SpotLights[NO_SPOT_LIGHTS];
uniform DirectionalLight u_DirectionalLights[NO_DIRECTIONAL_LIGHTS];

uniform vec3 u_ViewPos;

in vec3 WorldPos;
in vec3 v_Normal;
in vec3 v_Tex;





const float PI = 3.14159265359;
// ----------------------------------------------------------------------------
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}
// ----------------------------------------------------------------------------
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}




void main()
{
    vec3 albedo = u_Material.Albedo;
    float roughness = u_Material.Roughness;
    float metallic = u_Material.Metallic;
    float ao = u_Material.AO;


	vec3 N = normalize(v_Normal);
	vec3 V = normalize(u_ViewPos - WorldPos);

	// calculate reflectance at normal incidence; if dia-electric (like plastic) use F0 
    // of 0.04 and if it's a metal, use the albedo color as F0 (metallic workflow)    
    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metallic);

    vec3 Lo = vec3(0.0);
    for(int i = 0; i < u_NoPointLights; i++) 
    {
        // calculate per-light radiance
        vec3 L = normalize(u_PointLights[i].Position - WorldPos);
        vec3 H = normalize(V + L);
        float cosTheta = max(dot(N, L), 0.0);
        float distance = length(u_PointLights[i].Position - WorldPos);
        float attenuation = clamp(1.0 - distance*distance/(u_PointLights[i].Radius*u_PointLights[i].Radius), 0.0, 1.0);
        vec3 radiance =  u_PointLights[i].Light.Color * attenuation  * max(dot(N, L), 0.0) * u_PointLights[i].Light.Intensity;



        float NDF = DistributionGGX(N, H, roughness);   
        float G   = GeometrySmith(N, V, L, roughness);      
        vec3 F    = fresnelSchlick(clamp(dot(H, V), 0.0, 1.0), F0);
           
        vec3 numerator    = NDF * G * F; 
        float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001; // + 0.0001 to prevent divide by zero
        vec3 specular = numerator / denominator;
        
        // kS is equal to Fresnel
        vec3 kS = F;
        // for energy conservation, the diffuse and specular light can't
        // be above 1.0 (unless the surface emits light); to preserve this
        // relationship the diffuse component (kD) should equal 1.0 - kS.
        vec3 kD = vec3(1.0) - kS;
        // multiply kD by the inverse metalness such that only non-metals 
        // have diffuse lighting, or a linear blend if partly metal (pure metals
        // have no diffuse light).
        kD *= 1.0 - metallic;	  

        // add to outgoing radiance Lo
        Lo += (kD * albedo / PI + specular) * radiance;  // note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again
    } 
    
    for(int i = 0; i < u_NoDirectionalLights; i++) 
    {
    
        vec3 L = normalize(-u_DirectionalLights[i].Direction);
        vec3 H = normalize(V + L);
        vec3 radiance =  u_DirectionalLights[i].Light.Color * max(dot(N, L), 0.0) * u_DirectionalLights[i].Light.Intensity;



        float NDF = DistributionGGX(N, H, roughness);   
        float G   = GeometrySmith(N, V, L, roughness);      
        vec3 F    = fresnelSchlick(clamp(dot(H, V), 0.0, 1.0), F0);
           
        vec3 numerator    = NDF * G * F; 
        float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001; // + 0.0001 to prevent divide by zero
        vec3 specular = numerator / denominator;
        
        // kS is equal to Fresnel
        vec3 kS = F;
        // for energy conservation, the diffuse and specular light can't
        // be above 1.0 (unless the surface emits light); to preserve this
        // relationship the diffuse component (kD) should equal 1.0 - kS.
        vec3 kD = vec3(1.0) - kS;
        // multiply kD by the inverse metalness such that only non-metals 
        // have diffuse lighting, or a linear blend if partly metal (pure metals
        // have no diffuse light).
        kD *= 1.0 - metallic;	  
       

        // add to outgoing radiance Lo
        Lo += (kD * albedo / PI + specular) * radiance;  // note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again
    } 
    
    // ambient lighting (note that the next IBL tutorial will replace 
    // this ambient lighting with environment lighting).
    vec3 ambient = vec3(0.03) * albedo * ao;

    vec3 color = ambient + Lo;

    // HDR tonemapping
    color = color / (color + vec3(1.0));
    // gamma correct
    color = pow(color, vec3(1.0/2.2)); 
    FragColor = vec4(color, 1.0);
    
}


