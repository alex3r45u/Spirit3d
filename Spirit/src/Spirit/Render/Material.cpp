#include "sppch.h"
#include "Material.h"


void Spirit::Render::Material::SetUniforms(const std::shared_ptr<Shader>& shader)
{
    shader->SetFloat3("material.ambient", Ambient.x, Ambient.y, Ambient.z);
    shader->SetFloat3("material.deffuse", Deffuse.x, Deffuse.y, Deffuse.z);
    shader->SetFloat3("material.specular", Specular.x, Specular.y, Specular.z);
    shader->SetFloat("material.shininess", Shininess);
}
